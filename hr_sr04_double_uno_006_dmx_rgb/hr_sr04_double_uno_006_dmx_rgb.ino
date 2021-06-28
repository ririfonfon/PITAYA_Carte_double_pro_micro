#include <DMXSerial.h>
int RedList[]   = {0, 80, 100, 100, 50, 100};
int GreenList[] = {0, 80, 100, 100, 50, 100};
int BlueList[]  = {0, 80, 100, 100, 50, 100};


int RedLevel, GreenLevel, BlueLevel;

int RedNow = 0;
int GreenNow = 0;
int BlueNow = 0;

int state = 0;

int trig1 = 9;
int echo1 = 8;
long lecture_echo1;
long cm1;
int trig2 = 6;
int echo2 = 7;
long lecture_echo2;
long cm2;
int val = 400;

void setup() {
  DMXSerial.init(DMXController);

  pinMode(trig1, OUTPUT);
  digitalWrite(trig1, LOW);
  pinMode(echo1, INPUT);

  pinMode(trig2, OUTPUT);
  digitalWrite(trig2, LOW);
  pinMode(echo2, INPUT);

}

void loop()
{
  hr();

  if ((cm1 >= val) && (cm2 >= val)) {
    RedLevel = 100;
    GreenLevel = 50;
    BlueLevel = 0;


    if (RedNow < RedLevel)  RedNow++;
    if (RedNow > RedLevel)  RedNow--;
    DMXSerial.write(1, RedNow);


    if (GreenNow < GreenLevel)  GreenNow++;
    if (GreenNow > GreenLevel)  GreenNow--;
    DMXSerial.write(2, GreenNow);


    if (BlueNow < BlueLevel)  BlueNow++;
    if (BlueNow > BlueLevel)  BlueNow--;
    DMXSerial.write(3, BlueNow);

  } // cm1 et cm2 =>60

  if (cm1 <= val) {
    RedLevel = cm1 * 2;
    GreenLevel = cm1 * 2;
    BlueLevel = cm1 * 2;


    if (RedNow < RedLevel)  RedNow++;
    if (RedNow > RedLevel)  RedNow--;
    DMXSerial.write(1, RedLevel);


    if (GreenNow < GreenLevel)  GreenNow++;
    if (GreenNow > GreenLevel)  GreenNow--;
    DMXSerial.write(2, GreenLevel);


    if (BlueNow < BlueLevel)  BlueNow++;
    if (BlueNow > BlueLevel)  BlueNow--;
    DMXSerial.write(3, BlueLevel);
  }

  if (cm2 <= val / 2) {
    RedLevel = 0;
    GreenLevel = 0;
    BlueLevel = cm2 * 2;


    if (RedNow < RedLevel)  RedNow++;
    if (RedNow > RedLevel)  RedNow--;
    DMXSerial.write(1, RedNow);


    if (GreenNow < GreenLevel)  GreenNow++;
    if (GreenNow > GreenLevel)  GreenNow--;
    DMXSerial.write(2, GreenNow);


    if (BlueNow < BlueLevel)  BlueNow++;
    if (BlueNow > BlueLevel)  BlueNow--;
    DMXSerial.write(3, BlueNow);
  }

  /*
    Serial.print("Left 1 : ");
    Serial.print(cm1); // CM or INC
    Serial.print(" cm     " );

    Serial.print("Right 2 : ");
    Serial.print(cm2); // CM or INC
    Serial.println(" cm" );
  */
} // loop

void hr() {
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);
  lecture_echo1 = pulseIn(echo1, HIGH);
  cm1 = lecture_echo1 / 58;

  digitalWrite(trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);
  lecture_echo2 = pulseIn(echo2, HIGH);
  cm2 = lecture_echo2 / 58;
} // hr


