#!/bin/bash

echo "Content-type: text/html"
echo ""

echo "1" > cgi-bin/killme
sleep 1
echo "0" > cgi-bin/killme

cd cgi-bin
screen -d -m sudo ./startFade
