#!/bin/bash

echo "Content-type: text/html"
echo ""

COLOR=$(cat cgi-bin/color)
echo ${COLOR// }
