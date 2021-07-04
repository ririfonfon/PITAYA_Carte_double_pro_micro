#define DEBUG 1
/* Include the HCMAX7219 and SPI library */
#include "SPI.h"
#include "Wire.h"
#include <DigitLed72xx.h>

#define NUMBEROFDRIVERS 1
/* Set the LOAD (CS) digital pin number*/
#define LOAD_PIN 10
#define NCHIP 2

#define COMUT 5

/* Create an instance of the library */
DigitLed72xx ld = DigitLed72xx(LOAD_PIN, NCHIP);
int digi = 0;

/* Utilisation du capteur Ultrason HC-SR04 */

// définition des broches utilisées
int analogPin = A6;
int trig = 7;
int echo = 8;
long lecture_echo;
long cm;
int n = 0;
int val = 0;
int i = 0;

void sendi2c();
void reset_hcsr04();

void setup()
{
  Wire.begin();

  pinMode(COMUT, OUTPUT);
  pinMode(trig, OUTPUT);

  digitalWrite(trig, LOW);
  pinMode(echo, INPUT);
  Serial.begin(9600);

  digitalWrite(COMUT, LOW);
  delay(100);

  ld.on(2);
}

void loop()
{
  digi = digi % (NCHIP + 1);
  val = analogRead(analogPin) / 2;
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  lecture_echo = pulseIn(echo, HIGH);
  cm = lecture_echo / 58;

  sendi2c();

  if (cm == 0)
  {
    reset_hcsr04();
  }
  if (cm < val)
  {
    digitalWrite(COMUT, HIGH);
  }
  if (cm > val + 100)
  {
    i = i + 1;
  }
  if (i == 25)
  {
    i = 0;
    digitalWrite(COMUT, LOW);
  }
#ifdef DEBUG
  Serial.print("Distancem : ");
  Serial.println(cm);
#endif
  /* Clear the output buffer */
  ld.clear(digi);
  /* Write some text to the output buffer */
  ld.printDigit(cm, digi, 4);
  ld.printDigit(val, digi, 8);
  delay(10);
}

void sendi2c()
{
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write(cm);            // sends one byte
  Wire.endTransmission();    // stop transmitting
}

void reset_hcsr04()
{
  pinMode(echo, OUTPUT);
  digitalWrite(echo, LOW);
  delay(100);
  pinMode(echo, INPUT);
}
