/**

   startFade.c
   Continuously fades the RGB LED light strip into pleasing, pseudorandom colors.

*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pigpio.h>
#include <time.h>

#define RED_PIN 17
#define GREEN_PIN 22
#define BLUE_PIN 24

int main(int argc, char* argv[]) {

  // PRINT DEBUG MESSAGES
  int debug = 0;

  // INITIALIZATION
  gpioTerminate(); // in case the previous instance exited uncleanly
  if (gpioInitialise() < 0) {
    printf("pigpio initialisation failed.\n");
    return 1;
  }
  else { // pigpio initialised successfully
    
    // color value vars
    int newRed;
    int newGreen;
    int newBlue;
    int steadyPin;
    
    // Seed pseudorandom num generator
    srand(time(NULL));

    // Initialize the pins as being in the PWM output state
    gpioPWM(RED_PIN, 0);
    gpioPWM(GREEN_PIN, 0);
    gpioPWM(BLUE_PIN, 0);

    // For various (terrible) reasons, we kill this program by reading a text file
    FILE* killMe = fopen("killme", "r");
    char killChar = getc(killMe);
    if (debug == 1) {
      printf("killChar: %c", killChar);
    }

    // OUTER LOOP
    // Loop through different colors, until killme file contains "1"
    while( (killChar) == '0' ) {

      // reopen killme so we can check again later
      freopen ("killme", "r", killMe);
      
      // Randomize a new target color
      newRed = rand() % 256;
      newGreen = rand() % 256;
      newBlue = rand() % 256;

      // For better variation, make ~3/4 colors composed of only two from RGB
      steadyPin = rand() % 4;
      switch (steadyPin) {
      case 0:
	newRed = 0;
	break;
      case 1:
	newGreen = 0;
	break;
      case 2:
	newBlue = 0;
	break;
      default:
	break;
      }

      // DEBUG: print target colors
      if (debug == 1) {
	time_t mytime = time(NULL);
	printf("%s New colors: %d %d %d\n",
	       ctime(&mytime), newRed, newGreen, newBlue);
      }

      int currentRed;
      int currentGreen;
      int currentBlue;
      
      // INNER LOOP: gradually adjust to the new color, break when done      

      while( (killChar = getc(killMe)) == '0' ) {
	// reopen killme so we can check again later
	freopen ("killme", "r", killMe);

	// get the current levels so we can compare to target and adjust
	currentRed = gpioGetPWMdutycycle(RED_PIN);
	currentGreen = gpioGetPWMdutycycle(GREEN_PIN);
	currentBlue = gpioGetPWMdutycycle(BLUE_PIN);

	// Gradually bring the colors one level at a time to target
	if (newRed != currentRed) {
	  gpioPWM(RED_PIN,
		  currentRed + (newRed - currentRed) / abs(newRed - currentRed));
	}
	if (newGreen != currentGreen) {
	  gpioPWM(GREEN_PIN,
		  currentGreen
		  + (newGreen - currentGreen) / abs(newGreen - currentGreen));
	}
	if (newBlue != currentBlue) {
	  gpioPWM(BLUE_PIN,
		  currentBlue
		  + (newBlue - currentBlue) / abs(newBlue - currentBlue));
	}
	
	// Break if we've reached the target color
	if (newRed == currentRed
	    && newGreen == currentGreen
	    && newBlue == currentBlue) {
	  if (debug == 1) {
	    printf("Target color reached!\n");
	  }
	  //sleep(3); // pause 3 secs when reached target
	  break;
	}
	usleep(100000); // 0.1 sec
      }      
    }// end loops


    // TERMINATION
    gpioPWM(RED_PIN, 0);
    gpioPWM(GREEN_PIN, 0);
    gpioPWM(BLUE_PIN, 0);
    if (debug == 1) {
      printf("Calling gpioTerminate()\n");
    }
    gpioTerminate();
    return 0;
  }
  
}
