#include "init.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);
PulseOximeter pox;
File myFile;

// Symbols used for LCD display
const byte heart[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000,
  0b00000
};

const byte two[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b01100,
  0b10010,
  0b00100,
  0b01000,
  0b11110
};

const byte gLetter[8] = {
  0b00000,
  0b00000,
  0b01111,
  0b10001,
  0b10001,
  0b01111,
  0b00001,
  0b01110
};

// Flag used to mark when it's time to read the pulse oximeter sensor
bool firstRead = 1;

// Threashold value for heart rate
const float threshold = 55.0;

// Sum of valid heart rates
float heartRate;

// Sum of valid SpO2 values
int spo2;

// The number of relevant reads
int relevantReads;

// The number of irrelevant reads
int failures;

// Counter used for resetting the reads of sensor
int resetM;

// Timer used for knowing the time passed since the last report
uint32_t tsLastReport;

void setupLCD() {
	lcd.init();
	lcd.clear();
	lcd.backlight();
	lcd.createChar(0, heart);
	lcd.createChar(1, two);
	lcd.createChar(2, gLetter);
}

// Callback routine is executed when a pulse is detected
void onBeatDetected() {
  Serial.println("Beat!");
}

void setupPulseOximeter() {
	if (!pox.begin()) {
    Serial.println("FAILED");
    for(;;);
  } else {
    Serial.println("SUCCESS");
    lcd.setCursor(3, 0);
    lcd.print("BPM Monitor");
  }

  // Configure sensor to use 7.6mA for LED drive
	pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);

	// Register a callback for the beat detection
	pox.setOnBeatDetectedCallback(onBeatDetected);
}

void setupSDmodule() {
	if (!SD.begin(SD_CS_PIN)) {
		Serial.println("Card failed, or not present");
		return;
	}
}
