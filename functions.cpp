#include <string.h>
#include "functions.h"

void printInitialMessage()
{
	lcd.setCursor(0, 0);
	lcd.print("Put your fin");
	lcd.write((byte) 2);
	lcd.print("er");
	lcd.setCursor(0, 1);
	lcd.print("on the sensor:)");
}

void printStartMeasuringMessage()
{
	lcd.clear();
	lcd.setCursor(2, 0);
	lcd.print("Measurin");
	lcd.write((byte) 2);
	lcd.print("...");
}

void printHeartRate()
{
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("BPM: ");
	lcd.setCursor(6, 0);
	lcd.write((byte) 0);
	lcd.print(heartRate / relevantReads);
}

void printSpO2()
{
	lcd.setCursor(0, 5);
	lcd.print("SpO");
	lcd.write((byte) 1);
	lcd.print(": ");
	lcd.setCursor(6, 5);
	lcd.print(spo2 / relevantReads);
	lcd.print("%");
}

void writeDataToSD()
{
	myFile = SD.open("heart.txt", FILE_WRITE);

	if (myFile) {
		char text[20] = "BPM: ";
		float result = heartRate / relevantReads;
		char buffer[6];
		dtostrf(result, 5, 2, buffer);
		strncat(text, buffer, sizeof(buffer));
		strncat(text, " - SPO2: ", sizeof(" - SPO2: "));
		result = spo2 / relevantReads;
		dtostrf(result, 3, 0, buffer);
		strncat(text, buffer, sizeof(buffer));
		strncat(text, "%", sizeof("%"));
		
		myFile.println(text);
		myFile.close();
	}
}

void resetValues()
{
	relevantReads = 0;
	failures = 0;
	heartRate = 0.0;
	spo2 = 0;
}

void startMeasuring()
{
	firstRead = 0;
	printStartMeasuringMessage();
}

void goToFirstRead()
{
	// If there is data to be stored, write it to the SD card
	if (relevantReads > 0) {
		writeDataToSD();
	}

	// Make the sensor start from the beginning
	firstRead = 1;
	resetValues();
	resetM = 0;
}

void addValuesToSum(float currHeartRate, uint8_t currSpO2)
{
	heartRate += currHeartRate;
	spo2 += min(currSpO2, 100);
}
