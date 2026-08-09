#include <Arduino.h>
#include <Modulino.h>
#include <ArduinoGraphics.h>
#include <Arduino_LED_Matrix.h>
#include "RoomData.h"
#include "LedController.h"

using std::string;

// Create object instances
ModulinoThermo thermo;
ArduinoLEDMatrix matrix;
ModulinoPixels leds;
ModulinoButtons buttons;

RoomData roomData;

float temperature = 0.0;
float humidity = 0.0;
int timesPressed = 0;

// Declare functions definitions
void handleButtonPressed();
void printTempAndHumidity();
void showTempLEDs();
void setLEDsColor(ModulinoColor color);


void setup() {
    Serial.begin(9600);
    delay(1500);

    matrix.begin();

    // Call all necessary .begin() functions
    Modulino.begin();
    thermo.begin();
    leds.begin();
    buttons.begin();
    buttons.setLeds(true, false, false);
}

void loop() {
// Assign environmental reading to variables. 'temperature' is a cloud variable.
  roomData.temperature = thermo.getTemperature();
  roomData.humidity = thermo.getHumidity();

  handleButtonPressed();
  printTempAndHumidity();
  // printMatrixText();
  // showTempLEDs();
  toggleLEDs(leds);
  delay(500);
}

void handleButtonPressed() {
  if (buttons.update()) {
    if (buttons.isPressed(0)) {
      Serial.println("Button A pressed!");
      timesPressed++;
    }
  }
  Serial.println("Button pressed " + String(timesPressed) + " times.");
}

void showTempLEDs() {
  if (roomData.temperature < 20) {
    setLEDsColor(GREEN);
  } else if (roomData.temperature <= 30) {
    setLEDsColor(BLUE);
  } else {
    setLEDsColor(RED);
  }
  leds.show();
}

void setLEDsColor(ModulinoColor color) {
  for (int i = 0; i < 8; i++) {
    leds.set(i, color, 15);
  }
}

void showTempLED() {
  for (int i = 0; i < 8; i++) {
    leds.set(i, WHITE, 15);
  }
  leds.show();
}

void printMatrixText() {
  // Convert numbers and assign them to strings
  String temperatureText = "Temp: " + String(roomData.temperature, 2) + "°C";
  String humidityText    = "Humid: " + String(roomData.humidity, 2) + "%";

  // Settings for the LED Matrix
  matrix.beginDraw();
  matrix.stroke(0xFFFFFFFF);
  matrix.textScrollSpeed(50);

  // Add the text
  matrix.textFont(Font_5x7);
  matrix.beginText(0, 1, 0xFFFFFF);
  matrix.println("    " + temperatureText + "    " + humidityText);
  matrix.endText(SCROLL_LEFT);
  matrix.endDraw();
}

void printTempAndHumidity() {
  // Print the temperature and humidity values to Serial
  Serial.print("Temperature = ");
  Serial.print(roomData.temperature);
  Serial.print("°C");

  Serial.print ("          ");

  Serial.print("Humidity    = ");
  Serial.print(roomData.humidity);
  Serial.println("%");
}
