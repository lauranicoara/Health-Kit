#ifndef INIT_H
#define INIT_H

#include <Wire.h>
#include <SPI.h>
#include <SD.h>

#include "LiquidCrystal_I2C.h"
#include "MAX30100_PulseOximeter.h"

// Chip select pin for the microSD module
#define SD_CS_PIN               10

// Constant to delay the measurements
#define REPORTING_PERIOD_MS     1000

// LCD display
extern LiquidCrystal_I2C lcd;

// Pulse oximeter sensor
extern PulseOximeter pox;

// microSD module
extern File myFile;

// Symbols used for LCD display
extern const byte heart[8];
extern const byte two[8];
extern const byte gLetter[8];

// Flag used to mark when it's time to read the pulse oximeter sensor
// for the first time
extern bool firstRead;

// Threshold value for heart rate
extern const float threshold;

// Sum of valid heart rates
extern float heartRate;

// Sum of valid SpO2 values
extern int spo2;

// The number of relevant reads
extern int relevantReads;

// The number of irrelevant reads
extern int failures;

// Counter used for resetting the reads of sensor
extern int resetM;

// Timer to store the time at which the last beat occurred
extern uint32_t tsLastReport;

// Initialize LCD display
void setupLCD();

// Initialize pulse oximeter sensor
void setupPulseOximeter();

// Initialize microSD module
void setupSDmodule();

#endif