// Comments on Mapping
// A4(SDA), A5(SCL)


// Files to Include
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <dht.h>

// DEFINITIONS
#define outputA 6
#define outputB 7
#define SCREEN_WIDTH 128     // OLED display width
#define SCREEN_HEIGHT 64     // OLED display height
#define OLED_RESET -1        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define DISP_UPDATE_INTERVAL 500
#define DHT11_PIN 5
#define DEBOUNCE_DELAY 200
#define buttonPin 4

// Global Variables
double curr_time, prev_time,but_change_time;
int sen_humidity = 40;
int exp_humidity = 60;
float temperature = 30;
int aState;
int aLastState;

dht DHT;
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

static const unsigned char PROGMEM logo_bmp[] = { 0b00000000, 0b11000000,
                                                  0b00000001, 0b11000000,
                                                  0b00000001, 0b11000000,
                                                  0b00000011, 0b11100000,
                                                  0b11110011, 0b11100000,
                                                  0b11111110, 0b11111000,
                                                  0b01111110, 0b11111111,
                                                  0b00110011, 0b10011111,
                                                  0b00011111, 0b11111100,
                                                  0b00001101, 0b01110000,
                                                  0b00011011, 0b10100000,
                                                  0b00111111, 0b11100000,
                                                  0b00111111, 0b11110000,
                                                  0b01111100, 0b11110000,
                                                  0b01110000, 0b01110000,
                                                  0b00000000, 0b00110000 };

void setup() {
  humidifier_init();
  oled_init();
  prev_time = millis();
}
void loop() {
  curr_time = millis();
  encoder_check();
  if (abs(curr_time - prev_time) > DISP_UPDATE_INTERVAL) {
    sensor_update();
    main_disp_config();
    prev_time = curr_time;
  }
}

void humidifier_init() {
  Serial.begin(9600);

  // ENCODER PINS INIT
  pinMode(outputA, INPUT);
  pinMode(outputB, INPUT);
  aLastState = digitalRead(outputA);

  // OLED INIT
  if (!oled.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }
}