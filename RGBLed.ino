/* 
 * IMPORTANT: When working with the RedBear Duo, you must have this line of
 * code at the top of your program. The default state is SYSTEM_MODE(AUTOMATIC);
 * however, this puts the RedBear Duo in a special cloud-based mode that we 
 * are not using. For our purposes, set SYSTEM_MODE(SEMI_AUTOMATIC) or
 * SYSTEM_MODE(MANUAL). See https://docs.particle.io/reference/firmware/photon/#system-modes
 */
SYSTEM_MODE(MANUAL); 

#define COMMON_ANODE 1

const int RGB_RED_PIN = D0;
const int RGB_GREEN_PIN  = D1;
const int RGB_BLUE_PIN  = D2;
const int POT_A0 = A0;
const int POT_A1 = A1;
const int POT_A2 = A2;

int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // the amount to fade the LED by on each step
int maxBrightness = 128; // the max allowable analogWrite value is 255
const int DELAY = 1000; // delay between changing colors

int DEBUG = 1;      // DEBUG counter; if set to 1, will write values back via serial
int potentioMeterRead = 0; // Read value from A0 pin.

// Set up the LED and potentiometer inputs and outputs
void setup()
{
  pinMode(RGB_RED_PIN, OUTPUT);   // sets the pins as output
  pinMode(RGB_GREEN_PIN, OUTPUT);   
  pinMode(RGB_BLUE_PIN, OUTPUT); 
  pinMode(POT_A0, INPUT);  // set trimpot as input.
  pinMode(POT_A1, INPUT); 
  pinMode(POT_A2, INPUT); 

  if (DEBUG) {           // If we want to see values for debugging...
    Serial.begin(9600);  // ...set up the serial ouput 
  }
}

// Main program: list the order of crossfades
void loop()
{
  setColor(
    calculateLedBrightness(POT_A0),
    calculateLedBrightness(POT_A1),
    calculateLedBrightness(POT_A2));
    delay(DELAY);
}

int calculateLedBrightness(int pin)
{
  potentioMeterRead = analogRead(pin);
  brightness = (255./4090.)*potentioMeterRead;
  Serial.println("PotentionMeter Value :");
  Serial.println(potentioMeterRead);
  Serial.println("Adjusting brightness of LEDs to :");
  Serial.println(brightness);

  return brightness;
}

void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(RGB_RED_PIN, red);
  analogWrite(RGB_GREEN_PIN, green);
  analogWrite(RGB_BLUE_PIN, blue);  
}

