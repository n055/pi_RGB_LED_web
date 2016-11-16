/**

   setColor.c
   Sets the RGB LED light strip to a specified hexadecimal color

*/


#include <stdio.h>
#include <stdlib.h> /* strtol */
#include <string.h> /* strtok */
#include <unistd.h> /* sleep */
#include <pigpio.h>

#define RED_PIN 17
#define GREEN_PIN 22
#define BLUE_PIN 24

int main(int argc, char* argv[]) {

  int debug = 0;

  //int colorCorrect = 0; // 1: correct colors to balance human eye limitations
  int red = 0;
  int green = 0;
  int blue = 0;
  int newRed;
  int newGreen;
  int newBlue;

  FILE* killMe = fopen("killme", "r");
  FILE* color = fopen("color", "r");
  
  gpioTerminate(); // in case the previous instance exited uncleanly
  if (gpioInitialise() < 0) {
    printf("pigpio initialisation failed.\n");
    return 1;
  }
  else { // pigpio initialised successfully

    // Loop to continually update the color (if necessary)
    do {

      // READ COLOR from file
      char colorStr[9];
      fgets(colorStr, 9, color);

      // DECODE COLOR from hexadecimal to base 10
      newRed = strtol( strtok(colorStr, " "), NULL, 16);
      newGreen = strtol( strtok(NULL, " "), NULL, 16);
      newBlue = strtol( strtok(NULL, " "), NULL, 16);
      
      // IF COLOR IS DIFFERENT THAN OLD
      if (newRed != red || newGreen != green || newBlue != blue) {
	red = newRed;
	green = newGreen;
	blue = newBlue;

	if (debug == 1) {
	  printf("%d %d %d\n", red, green, blue);
	}

	// Turn on the lights to the new color
	gpioPWM(RED_PIN, red);
	gpioPWM(GREEN_PIN, green);
	gpioPWM(BLUE_PIN, blue);
      }
      
      usleep(100000); // 0.1 sec
      freopen ("color", "r", color);
      freopen ("killme", "r", killMe);
    } while (getc(killMe) == '0');
    
    // TERMINATION
    gpioPWM(RED_PIN, 0);
    gpioPWM(GREEN_PIN, 0);
    gpioPWM(BLUE_PIN, 0);
    gpioTerminate();
    return 0;
  }
}
