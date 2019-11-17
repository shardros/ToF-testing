#include <ComponentObject.h>
#include <RangeSensor.h>
#include <SparkFun_VL53L1X.h>
#include <vl53l1x_class.h>
#include <vl53l1_error_codes.h>

/*
  Reading distance from the laser based VL53L1X
  By: Nathan Seidle
  SparkFun Electronics
  Date: April 4th, 2018
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  SparkFun labored with love to create this code. Feel like supporting open source hardware?
  Buy a board from SparkFun! https://www.sparkfun.com/products/14667

  This example prints the distance to an object.

  Are you getting weird readings? Be sure the vacuum tape has been removed from the sensor.
*/

#include <Wire.h>
#include "SparkFun_VL53L1X.h"

//Optional interrupt and shutdown pins.
#define POWER_PIN 13
#define INTERRUPT_PIN 3

#define SAMPLE_SIZE 10

SFEVL53L1X distanceSensor;
//Uncomment the following line to use the optional shutdown and interrupt pins.
//SFEVL53L1X distanceSensor(Wire, SHUTDOWN_PIN, INTERRUPT_PIN);

uint32_t distance;
uint16_t distances[25];
uint32_t mean;
uint32_t var;
float sd;

void setup(void)
{
  Wire.begin();

  pinMode(POWER_PIN, OUTPUT);    // sets the digital pin 13 as output
  digitalWrite(POWER_PIN, HIGH); // sets the digital pin 13 on

  Serial.begin(115200);
  Serial.println("VL53L1X Qwiic Test");

  if (distanceSensor.begin() == 0) //Begin returns 0 on a good init
  {
    Serial.println("Sensor online!");
  }
}

void loop(void)
{
  for (uint8_t i = 0; i < SAMPLE_SIZE; i++) {

    Serial.print("Array pointer ");
    Serial.print(i);

    distanceSensor.startRanging(); //Write configuration bytes to initiate measurement
    distance = distanceSensor.getDistance(); //Get the result of the measurement from the sensor
    distanceSensor.stopRanging();

    Serial.print(" distance: ");
    Serial.print(distance);

    /** distances[i] = distance;

    mean = 0;
    for(uint8_t n = 0; n < SAMPLE_SIZE; n++ ) {
      mean += distances[n];
    }

    mean /= SAMPLE_SIZE;

    var = 0;
    for(uint8_t n = 0; n < SAMPLE_SIZE; n++ ) {
      var += (distances[n] - mean) * (distances[n] - mean);
    }
    var /= SAMPLE_SIZE;
    sd = sqrt(var);

    Serial.print(" var: ");
    Serial.print(var);

    Serial.print(" sd: ");
    Serial.print(sd);**/

    Serial.println();

  }

}
