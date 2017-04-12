/* toHero */ 

/*********** Includes **********/
#include <Adafruit_NeoPixel.h>


/*********** Defines **********/
#define DATA            6    // Pin connected to the DataIN of the LED strip
#define BUTTON          7    // Input pin where the button is connected
#define NUMLEDS         32   // Number of LEDs in the strip
#define STARTVAL        20   // Start value for the LED cycle
#define ENDVAL          250  // End value for the LED cycle

/*********** Global variables **********/
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMLEDS, DATA, NEO_GRB + NEO_KHZ800); // Object to handle the LED strip
int cnt = STARTVAL; // Counter to increment mode value
int blue = 0; // Value for the blue LED
int red = 0;  // Value for the red LED
int green = 0;// Value for the green LED
short mode = 0; // Current displaying mode

/*********** Setup **********/
void setup() {
  pixels.begin(); // Initialize LED strip
  pinMode(BUTTON, INPUT); // Configure the button pin as an INPUT
}

/*********** Main loop **********/
void loop() {

  /* Check if the button is pressed */
  if (!digitalRead(BUTTON)) {
    if (mode < 2) {
      mode ++;
    } else {
      mode = 0;
    }

    /* Wait the release of the button */
    while(!digitalRead(BUTTON));
  }

  /* Set the color values */
  setColors(&red, &green, &blue, cnt, mode);

  /* Fill the values of each pixel */
  for (int i=0; i < NUMLEDS; i++) {
    pixels.setPixelColor(i, pixels.Color(red,green,blue));
  }

  pixels.show(); // This sends the updated pixel mode to the hardware.
  
  cnt ++;
  delay(15);

  /* If the counter is at the end of the cycle, restart a new one */
  if (cnt > (2 * ENDVAL - STARTVAL)) {
    cnt = STARTVAL;
  }
}


/*********** Functions **********/
void setColors(int* r, int* g, int* b, int count, short mod) {
  if (cnt < ENDVAL) {
    switch(mod) {
      case 0:
        *b = count;
        *r = 0;
        *g = 0;
        break;
      case 1:
        *b = count;
        *r = 0;
        *g = ENDVAL + STARTVAL - count; 
        break;
      case 2:
        *b = count;
        *r = count / 2;
        *g = 0;
        break;
      default:
        break;
      }
    } else {
      switch(mod) {
        case 0:
          *b = 2 * ENDVAL - count;
          *r = 0;
          *g = 0;
          break;
        case 1:
          *b = 2 * ENDVAL - count;
          *r = 0;
          *g = STARTVAL + count;
          break;
        case 2:
          *b = 2 * ENDVAL - count;
          *r = ENDVAL- count / 2;
          *g = 0;
          break;
        default:
          break;
      }
  }
}
