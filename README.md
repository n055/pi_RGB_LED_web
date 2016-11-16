# pi_RGB_LED_web
Scripts for controlling an RGB LED strip via an rpi

This software is intended for use in conjunction with a [homebridge](https://github.com/nfarina/homebridge) installation with [homebridge-better-http-rgb](https://github.com/jnovack/homebridge-better-http-rgb) as well as a web server to host the CGI scripts. For my purposes (a single user on a LAN) the python3 built-in webserver works fine, but homebridge-better-http-rgb needs you to serve something so that it can controll the lights via a URL.

pi_RGB_LED_web contains:
- C programs for controlling the color of an RGB LED strip connected to a Raspberry Pi
- Shell scripts for interacting with the C programs and for compiling them

I use this on a Raspberry Pi running Raspbian.

## Dependencies:
- [pigpio C library](http://abyz.co.uk/rpi/pigpio/cif.html). `sudo apt-get install pigpio`

## What every file means/does
- brightness.sh
  - returns "100" according to the homebridge-better-http-rgb spec
- color
  - file containing the current color as a hex code separated by spaces
  - read by setColor.c
- color.sh
  - writes the color to "color"
  - runs setColor.c, killing existing processes if necessary
- colorStatus.sh
  - returns current color according to the homebridge-better-http-rgb spec
- killMe
  - file containing 0 if we don't want to kill the C programs, and 1 if we do
- LEDinit.sh
  - Starts python webserver, pigpio daemon, and homebridge. If you're using this you'll need to modify it to meet your needs.
- makeSC.sh, makeSF.sh
  - commands to compile setColor.c and startFade.c in GCC
- off.sh
  - Turn lights off
- on.sh
  - Turn lights on
- onStatus.sh
  - Returns whether lights are on or off, according to the homebridge-better-http-rgb spec
- setColor.c
  - Sets the RGB LED light strip to a specified hexadecimal color
- startFade.c
  - Continuously fades the RGB LED light strip into pleasing, pseudorandom colors
  
Since there are no binaries included, it should be self-explainatory that you need to compile the C programs after downloading this before the shell scripts will work to turn the RGB lights on or off.
