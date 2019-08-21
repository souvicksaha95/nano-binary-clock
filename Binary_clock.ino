#include <Wire.h>
#include "RTClib.h"

#define A 12
#define B 11
#define C 10
#define D 9
#define E 8

#define PIN_COUNT 5

#define PIN_CONFIG 0
#define PIN_STATE 1

#define LED_COUNT 20

int d = 1;
RTC_DS1307 rtc;

int matrix[LED_COUNT][2][PIN_COUNT] = {
    //              PIN_CONFIG                          PIN_STATE
    //    A       B       C      D      E         A     B    C    D    E
    { { OUTPUT, INPUT, OUTPUT, INPUT, INPUT }, { HIGH, LOW, LOW, LOW, LOW } }, // DC 5//01011
    { { OUTPUT, INPUT, OUTPUT, INPUT, INPUT }, { LOW, LOW, HIGH, LOW, LOW } }, // CD 4//01011
    { { INPUT, INPUT, OUTPUT, OUTPUT, INPUT }, { LOW, LOW, HIGH, LOW, LOW } }, // AD 14//11001
    { { INPUT, INPUT, OUTPUT, OUTPUT, INPUT }, { LOW, LOW, LOW, HIGH, LOW } }, // DA 15//11001
    { { INPUT, OUTPUT, INPUT, OUTPUT, INPUT }, { LOW, LOW, LOW, HIGH, LOW } }, // DB 13//10101
    { { INPUT, OUTPUT, INPUT, OUTPUT, INPUT }, { LOW, HIGH, LOW, LOW, LOW } }, // BD 12//10101
    { { INPUT, OUTPUT, INPUT, INPUT, OUTPUT }, { LOW, HIGH, LOW, LOW, LOW } }, // BE 16//10110
    { { INPUT, OUTPUT, INPUT, INPUT, OUTPUT }, { LOW, LOW, LOW, LOW, HIGH } }, // EB 17//10110
    { { OUTPUT, INPUT, INPUT, OUTPUT, INPUT }, { HIGH, LOW, LOW, LOW, LOW } }, // AC 8//01101
    { { OUTPUT, INPUT, INPUT, OUTPUT, INPUT }, { LOW, LOW, LOW, HIGH, LOW } }, // CA 9//01101
    { { INPUT, OUTPUT, OUTPUT, INPUT, INPUT }, { LOW, LOW, HIGH, LOW, LOW } }, // CB 3//10011
    { { INPUT, OUTPUT, OUTPUT, INPUT, INPUT }, { LOW, HIGH, LOW, LOW, LOW } }, // BC 2//10011
    { { INPUT, INPUT, INPUT, OUTPUT, OUTPUT }, { LOW, LOW, LOW, HIGH, LOW } }, // DE 6//11100
    { { INPUT, INPUT, INPUT, OUTPUT, OUTPUT }, { LOW, LOW, LOW, LOW, HIGH } }, // ED 7//11100
    { { OUTPUT, OUTPUT, INPUT, INPUT, INPUT }, { HIGH, LOW, LOW, LOW, LOW } }, // AB 0//00111
    { { OUTPUT, OUTPUT, INPUT, INPUT, INPUT }, { LOW, HIGH, LOW, LOW, LOW } }, // BA 1//00111
    { { INPUT, INPUT, OUTPUT, INPUT, OUTPUT }, { LOW, LOW, HIGH, LOW, LOW } }, // CE 10//11010
    { { INPUT, INPUT, OUTPUT, INPUT, OUTPUT }, { LOW, LOW, LOW, LOW, HIGH } }, // EC 11//11010
    { { OUTPUT, INPUT, INPUT, INPUT, OUTPUT }, { HIGH, LOW, LOW, LOW, LOW } }, // AE 18//01110
    { { OUTPUT, INPUT, INPUT, INPUT, OUTPUT }, { LOW, LOW, LOW, LOW, HIGH } }, // EA 19//01110
};

void turnOn( int led ) {
    led = led - 1;
    pinMode( A, matrix[led][PIN_CONFIG][0] );
    pinMode( B, matrix[led][PIN_CONFIG][1] );
    pinMode( C, matrix[led][PIN_CONFIG][2] );
    pinMode( D, matrix[led][PIN_CONFIG][3] );
    pinMode( E, matrix[led][PIN_CONFIG][4] );
    // set all the pin states
    digitalWrite( A, matrix[led][PIN_STATE][0] );
    digitalWrite( B, matrix[led][PIN_STATE][1] );
    digitalWrite( C, matrix[led][PIN_STATE][2] );
    digitalWrite( D, matrix[led][PIN_STATE][3] );
    digitalWrite( E, matrix[led][PIN_STATE][4] );

    delay(d);

    PORTB = B00000000;
}

void setup()
{
  Serial.begin(57600);
#ifdef AVR
  Wire.begin();
#else
  Wire1.begin();
#endif
  rtc.begin();

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
  }
}

void loop()
{
  DateTime now = rtc.now();

  int h = now.hour();
  int m = now.minute();
  int s = now.second();

    int h1 = h%10;
    h = h/10;
    switch(h1)
    {
      case 0:
      break;
      case 1:
      turnOn(10);break;
      case 2:
      turnOn(9);break;
      case 3:
      turnOn(9);turnOn(10);break;
      case 4:
      turnOn(16);break;
      case 5:
      turnOn(16);turnOn(10);break;
      case 6:
      turnOn(16);turnOn(9);break;
      case 7:
      turnOn(16);turnOn(9);turnOn(10);break;
      case 8:
      turnOn(15);break;
      case 9:
      turnOn(15);turnOn(10);break;
    }
    switch(h)
    {
      case 0:
      break;
      case 1:
      turnOn(2);break;
      case 2:
      turnOn(1);break;
    }

    int m1 = m%10;
    m = m/10;
    switch(m1)
    {
      case 0:
      break;
      case 1:
      turnOn(5);break;
      case 2:
      turnOn(6);break;
      case 3:
      turnOn(6);turnOn(5);break;
      case 4:
      turnOn(3);break;
      case 5:
      turnOn(3);turnOn(5);break;
      case 6:
      turnOn(3);turnOn(6);break;
      case 7:
      turnOn(3);turnOn(6);turnOn(5);break;
      case 8:
      turnOn(12);break;
      case 9:
      turnOn(12);turnOn(5);break;
    }
    switch(m)
    {
      case 0:
      break;
      case 1:
      turnOn(20);break;
      case 2:
      turnOn(19);break;
      case 3:
      turnOn(19);turnOn(20);break;
      case 4:
      turnOn(4);break;
      case 5:
      turnOn(4);turnOn(20);break;
    }
    int s1 = s%10;
    s = s/10;
    switch(s1)
    {
      case 0:
      break;
      case 1:
      turnOn(7);break;
      case 2:
      turnOn(8);break;
      case 3:
      turnOn(7);turnOn(8);break;
      case 4:
      turnOn(13);break;
      case 5:
      turnOn(13);turnOn(7);break;
      case 6:
      turnOn(13);turnOn(8);break;
      case 7:
      turnOn(13);turnOn(8);turnOn(7);break;
      case 8:
      turnOn(14);break;
      case 9:
      turnOn(14);turnOn(7);break;
    }
    switch(s)
    {
      case 0:
      break;
      case 1:
      turnOn(11);break;
      case 2:
      turnOn(18);break;
      case 3:
      turnOn(18);turnOn(11);break;
      case 4:
      turnOn(17);break;
      case 5:
      turnOn(17);turnOn(11);break;
    }
} 

