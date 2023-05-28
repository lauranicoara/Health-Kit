#include "init.h"
#include "functions.h"

void setup() {
  Serial.begin(9600);
  setupLCD();
  setupPulseOximeter();
  setupSDmodule();
}

void loop() {
  // Read from the sensor
  pox.update();

  if (firstRead == 1) {
    // Instructions for the user
    printInitialMessage();
  }

  // Grab the updated heart rate and SpO2 levels
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    // Read the values from the sensor
    float currHeartRate = pox.getHeartRate();
    uint8_t currSpO2 = pox.getSpO2();

    // When the sensor reads something for the first time 
    if (firstRead == 1) {
      // If one of the values is not 0, start measuring
      if (currHeartRate != 0.0 || currSpO2 != 0) {
        startMeasuring();
      }
    }

    // If the sensor measures 0 for both values, increment the
    // counter for resetting all values
    if (currHeartRate == 0.0 && currSpO2 == 0) {
      resetM++;
      // When the counter reaches 20, reset all values
      if (resetM == 20) {
        goToFirstRead();
      }
    } else if (currHeartRate == 0.0 || currSpO2 == 0) {
      // If one of the values isn't read correctly, increment the
      // counter for failed reads
      failures++;
      if (failures == 3) {
        // If there are 3 failed reads, reset the measurements
        resetValues();
      }
    }

    // If both values are read correctly, add them to the
    // sum of values for calculating the average afterwards
    if (currHeartRate > threshold && currSpO2 > 0) {
      addValuesToSum(currHeartRate, currSpO2);

      // Reset the counter for resetting the values
      resetM = 0;

      // Reset the counter for failed reads
      failures = 0;

      // Increment the number of relevant reads
      relevantReads++;

      // Print the values on the LCD
      printHeartRate();
      printSpO2();
    }

    tsLastReport = millis();
  }
}
