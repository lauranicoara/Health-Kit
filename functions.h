#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "init.h"

// Print initial message on the LCD
void printInitialMessage();

// Print message when the sensor starts measuring
void printStartMeasuringMessage();

// Print the heart rate
void printHeartRate();

// Print the SpO2
void printSpO2();

// Write the final measurement to the SD card
void writeDataToSD();

// Reset used variables
void resetValues();

// The measurments start
void startMeasuring();

// Start the measurments from the beginning
void goToFirstRead();

// Add the values to the sum
void addValuesToSum(float currHeartRate, uint8_t currSpO2);

#endif