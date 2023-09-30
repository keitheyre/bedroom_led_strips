#include <FastLED.h>

#define LED_PIN         6    // Digital pin connected to the LED strip
#define NUM_LEDS        96   // Total number of LEDs (3 sections * 32 LEDs)
#define LEDS_PER_SECTION 32  // Number of LEDs in each section
#define BRIGHTNESS      30   // 30% of maximum brightness

CRGB leds[NUM_LEDS];

#define SWITCH_PIN1A  A0   // Pin connected to the first limit switch in section 1
#define SWITCH_PIN1B  A1   // Pin connected to the second limit switch in section 1

#define SWITCH_PIN2A  A2   // Pin connected to the first limit switch in section 2
#define SWITCH_PIN2B  A3   // Pin connected to the second limit switch in section 2
#define SWITCH_PIN2C  A4   // Pin connected to the third limit switch in section 2

#define SWITCH_PIN3A  A5   // Pin connected to the first limit switch in section 3
#define SWITCH_PIN3B  2   // Pin connected to the second limit switch in section 3

bool switchOpen1A = true;  // Assume first switch in section 1 is open initially
bool switchOpen1B = true;  // Assume second switch in section 1 is open initially

bool switchOpen2A = true;  // Assume first switch in section 2 is open initially
bool switchOpen2B = true;  // Assume second switch in section 2 is open initially
bool switchOpen2C = true;  // Assume third switch in section 2 is open initially

bool switchOpen3A = true;  // Assume first switch in section 3 is open initially
bool switchOpen3B = true;  // Assume second switch in section 3 is open initially

bool section1On = false; // Tracks whether section 1 is on
bool section2On = false; // Tracks whether section 2 is on
bool section3On = false; // Tracks whether section 3 is on

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.show();  // Initialize all LEDs to 'off'

  pinMode(SWITCH_PIN1A, INPUT_PULLUP);  // Set the first limit switch in section 1 as input with pull-up resistor
  pinMode(SWITCH_PIN1B, INPUT_PULLUP);  // Set the second limit switch in section 1 as input with pull-up resistor

  pinMode(SWITCH_PIN2A, INPUT_PULLUP);  // Set the first limit switch in section 2 as input with pull-up resistor
  pinMode(SWITCH_PIN2B, INPUT_PULLUP);  // Set the second limit switch in section 2 as input with pull-up resistor
  pinMode(SWITCH_PIN2C, INPUT_PULLUP);  // Set the third limit switch in section 2 as input with pull-up resistor

  pinMode(SWITCH_PIN3A, INPUT_PULLUP);  // Set the first limit switch in section 3 as input with pull-up resistor
  pinMode(SWITCH_PIN3B, INPUT_PULLUP);  // Set the second limit switch in section 3 as input with pull-up resistor
}

void loop() {
  switchOpen1A = digitalRead(SWITCH_PIN1A) == HIGH;
  switchOpen1B = digitalRead(SWITCH_PIN1B) == HIGH;

  switchOpen2A = digitalRead(SWITCH_PIN2A) == HIGH;
  switchOpen2B = digitalRead(SWITCH_PIN2B) == HIGH;
  switchOpen2C = digitalRead(SWITCH_PIN2C) == HIGH;

  switchOpen3A = digitalRead(SWITCH_PIN3A) == HIGH;
  switchOpen3B = digitalRead(SWITCH_PIN3B) == HIGH;

  // Control Section 1
  if (switchOpen1A || switchOpen1B) {
    if (!section1On) {
      slowFillFromCenter(CRGB::White, LEDS_PER_SECTION, 50, 0, LEDS_PER_SECTION);
      section1On = true;
      Serial.println("Section 1 is ON");
    }
  } else {
    if (section1On) {
      slowFillFromOutside(CRGB::Black, LEDS_PER_SECTION, 50, 0, LEDS_PER_SECTION);
      section1On = false;
      Serial.println("Section 1 is OFF");
    }
  }

  // Control Section 2
  if (switchOpen2A || switchOpen2B || switchOpen2C) {
    if (!section2On) {
      slowFillFromCenter(CRGB::White, LEDS_PER_SECTION, 50, LEDS_PER_SECTION, LEDS_PER_SECTION * 2);
      section2On = true;
      Serial.println("Section 2 is ON");
    }
  } else {
    if (section2On) {
      slowFillFromOutside(CRGB::Black, LEDS_PER_SECTION, 50, LEDS_PER_SECTION, LEDS_PER_SECTION * 2);
      section2On = false;
      Serial.println("Section 2 is OFF");
    }
  }

  // Control Section 3
  if (switchOpen3A || switchOpen3B) {
    if (!section3On) {
      slowFillFromCenter(CRGB::White, LEDS_PER_SECTION, 50, LEDS_PER_SECTION * 2, LEDS_PER_SECTION * 3);
      section3On = true;
      Serial.println("Section 3 is ON");
    }
  } else {
    if (section3On) {
      slowFillFromOutside(CRGB::Black, LEDS_PER_SECTION, 50, LEDS_PER_SECTION * 2, LEDS_PER_SECTION * 3);
      section3On = false;
      Serial.println("Section 3 is OFF");
    }
  }
}

void slowFillFromCenter(CRGB color, int numLEDs, int delayTime, int startLED, int endLED) {
  int middleLED = numLEDs / 2;

  for (int i = 0; i <= middleLED; i++) {
    leds[startLED + middleLED - i] = color;
    leds[endLED - middleLED + i] = color;
    FastLED.show();
    delay(delayTime);
  }
}

void slowFillFromOutside(CRGB color, int numLEDs, int delayTime, int startLED, int endLED) {
  int middleLED = numLEDs / 2;

  for (int i = 0; i <= middleLED; i++) {
    leds[startLED + i] = color;
    leds[endLED - i] = color;
    leds[middleLED] = color;
    FastLED.show();
    delay(delayTime);
  }
}
