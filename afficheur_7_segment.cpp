/* Ce programme permet de faire un compteur qui compte de 0 à 1023 et qui reprend à zéro une fois 1023 atteind. */
/* Montage :   - De 2 à 5 branché à un décodeur sn74ls47n et un afficheur 7 segment associé. L'information sortie est un compteur binaire
                qui va de 0 à 9 sur les sorties 2 à 5.
*/

const int led1 = 2;
const int led2 = 3;
const int led3 = 4;
const int led4 = 5;

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
}

void loop() {
  delay(500);
  ++count;
  
  if(count == 10)
  {
    count = 0;
  }
  
  for(int i=led1; i <= led4; ++i)
  {
    digitalWrite(i, LOW);
  }
  
  buffer = 0;
  decimalToBinaryOnLed(count, led1);
  
}
