/* Ce programme permet de faire une horloge binaire qui supporte les secondes et les minutes. */
/* Montage :   - les 6 LEDs des secondes branchées du pin 2 à 7.
               - Les 6 LEDs des minutes branchées du pin 8 à 13.
*/

/* LED des secondes */
const int sec1 = 2;
const int sec2 = 3;
const int sec3 = 4;
const int sec4 = 5;
const int sec5 = 6;
const int sec6 = 7;

/* LED des minutes */
const int min1 = 8;
const int min2 = 9;
const int min3 = 10;
const int min4 = 11;
const int min5 = 12;
const int min6 = 13;

int seconds = 0;
int minutes = 0;

int buffer = 0;

void decimalToBinaryOnLed(int number, int min, int max) //Algo pour allumer les leds en binaire à partir d'un nombre dec
{  
  if(number%2 == 1)
  {
   digitalWrite(min+buffer, HIGH);
  }
  else
  {
    digitalWrite(min+buffer, LOW);
  }
   
   ++buffer;
   
  if (number / 2 != 0)
    decimalToBinaryOnLed(number / 2, min, max); 
}

void setup() {
  pinMode(sec1, OUTPUT);
  pinMode(sec2, OUTPUT);
  pinMode(sec3, OUTPUT);
  pinMode(sec4, OUTPUT);
  pinMode(sec5, OUTPUT);
  pinMode(sec6, OUTPUT);
  
  pinMode(min1, OUTPUT);
  pinMode(min2, OUTPUT);
  pinMode(min3, OUTPUT);
  pinMode(min4, OUTPUT);
  pinMode(min5, OUTPUT);
  pinMode(min6, OUTPUT);
}

void loop() {
  delay(1000);
  ++seconds;
  
  if(seconds == 59)
  {
    seconds = 0;
    ++minutes;
  }
  
  if(minutes == 59)
  {
    minutes = 0;
  }

    for(int i=sec1; i <= sec6; ++i)
  {
    digitalWrite(i, LOW);
  }
  
    for(int i=min1; i <= min6; ++i)
  {
    digitalWrite(i, LOW);
  }

  buffer = 0;
  decimalToBinaryOnLed(seconds, sec1, sec6);
  buffer = 0;
  decimalToBinaryOnLed(minutes, min1, min6);
}
