#include <FastLED.h>

#define LED_PIN A1             // Define the digital pin connected to DIN (Data Input)
#define NUM_LEDS 204           // Define the total number of LEDs in your strip
#define NUM_SECTIONS 4         // Define the number of sections
#define TARGET_BRIGHTNESS 51   // Target brightness (20% of the maximum brightness)
#define DELAY_BETWEEN_LEDS 20 // Delay between each LED turning on in milliseconds

CRGB leds[NUM_LEDS];

// Define the number of LEDs in each section
int ledsPerSection = NUM_LEDS / NUM_SECTIONS;

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(30); // Start with 25% brightness (adjust as needed)
  FastLED.show();           // Initialize all LEDs to 'off'
}

void loop() {
  // Define the color as white
  CRGB whiteColor = CRGB::White;

  // Turn on every LED in each section with a delay
  for (int ledIndex = 0; ledIndex < ledsPerSection; ledIndex++) {
    for (int section = 0; section < NUM_SECTIONS; section++) {
      int i = section * ledsPerSection + ledIndex;
      leds[i] = whiteColor * TARGET_BRIGHTNESS;
    }
    FastLED.show();
    delay(DELAY_BETWEEN_LEDS);
  }
}