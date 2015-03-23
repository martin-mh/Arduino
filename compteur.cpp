/* Ce programme permet de faire un compteur qui compte de 0 à 1023 et qui reprend à zéro une fois 1023 atteind. */
/* Montage :   - 10 LEDs branchées du pin 2 à 11.
*/

/* Les 10 LEDs */
const int led1 = 2;
const int led2 = 3;
const int led3 = 4;
const int led4 = 5;
const int led5 = 6;
const int led6 = 7;
const int led7 = 8;
const int led8 = 9;
const int led9 = 10;
const int led10 = 11;

const int delayOnStartup = 200; //Delay between states on the startup animation

const int button = 8;

int count = 0;
int buffer = 0;

void decimalToBinaryOnLed(int number, int min) //Algo pour allumer les leds en binaire à partir d'un nombre dec
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
  {
    decimalToBinaryOnLed(number / 2, min);
  }
}

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
  pinMode(led8, OUTPUT);
  pinMode(led9, OUTPUT);
  pinMode(led10, OUTPUT);
  
  digitalWrite(led1, HIGH);
  delay(delayOnStartup);
  
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  delay(delayOnStartup);
  
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);
  delay(delayOnStartup);
  
  digitalWrite(led3, LOW);
  digitalWrite(led4, HIGH);
  delay(delayOnStartup);
  
  digitalWrite(led4, LOW);
  digitalWrite(led5, HIGH);
  delay(delayOnStartup);
  
  digitalWrite(led5, LOW);
  digitalWrite(led6, HIGH);
  delay(delayOnStartup);
  
  digitalWrite(led6, LOW);
  digitalWrite(led7, HIGH);
  delay(delayOnStartup);
  
  digitalWrite(led7, LOW);
  digitalWrite(led8, HIGH);
  delay(delayOnStartup);
  
  digitalWrite(led8, LOW);
  digitalWrite(led9, HIGH);
  delay(delayOnStartup);
  
  digitalWrite(led9, LOW);
  digitalWrite(led10, HIGH);
  delay(delayOnStartup);
  
  digitalWrite(led10, LOW);
  delay(delayOnStartup);
  
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led5, HIGH);
  digitalWrite(led6, HIGH);
  digitalWrite(led7, HIGH);
  digitalWrite(led8, HIGH);
  digitalWrite(led9, HIGH);
  digitalWrite(led10, HIGH);
  delay(500);
  
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led6, LOW);
  digitalWrite(led7, LOW);
  digitalWrite(led8, LOW);
  digitalWrite(led9, LOW);
  digitalWrite(led10, LOW);
  
  
}

void loop() {
  delay(1000);
  ++count;
  
  if(count == 1023)
  {
    count = 0;
  }
  
  for(int i=led1; i <= led10; ++i)
  {
    digitalWrite(i, LOW);
  }
  
  buffer = 0;
  decimalToBinaryOnLed(count, led1);
  
}
