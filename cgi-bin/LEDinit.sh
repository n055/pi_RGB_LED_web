#!/bin/bash

# Start the python web server
nohup python3 -m http.server --cgi > LEDlog.log &

# Start the GPIO daemon
# nohup sudo pigpiod

# Start homebridge
nohup homebridge > LEDlog.log &

