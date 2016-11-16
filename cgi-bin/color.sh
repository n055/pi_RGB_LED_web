#!/bin/bash

echo "Content-type: text/html"
echo ""

# Query string contains a hex color code
red=${QUERY_STRING:0:2}
green=${QUERY_STRING:2:2}
blue=${QUERY_STRING:4:2}

# Give setColor the new color
echo "$red $green $blue" > cgi-bin/color

if [ -n "$(pgrep startFade)" ] # if startFade is running
then
    echo "1" > cgi-bin/killme # then kill startFade
fi

if [ "$(cat cgi-bin/killme)" -eq 1 ] # if setColor is NOT running
then
    # then run setColor
    echo "0" > cgi-bin/killme
    cd cgi-bin
    screen -d -m sudo ./setColor
fi
