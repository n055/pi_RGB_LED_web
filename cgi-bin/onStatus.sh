#!/bin/bash

echo "Content-type: text/html"
echo ""

if [ $(cat cgi-bin/killme) -eq 0 ]
then
    echo "1"
else
    echo "0"
fi
