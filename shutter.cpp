/* Not finished yet, in development. */

/* PINs */
const int motorUpPin = 2;
const int motorDownPin = 3;

const int isSomeonePresentPin = 4;
const int isLightSufficientPin = 5;

const int outerTemperatureAnalogPin = 0;
const int innerTemperatureAnalogPin = 1;

/* VALUES */
int outerTemperature = 0;
int innerTemperature = 0;

/* Values got from analog read of temperatures have constant described here */
int sevenDegrees = 431;
int sixteenDegrees = 448;
int twentytwoDegrees = 461;
int twentysevenDegrees = 471;

int sevenDegreesMax = sevenDegrees + ((sixteenDegrees - sevenDegrees) / 2);
int sevenDegreesMin = sevenDegrees - ((sixteenDegrees - sevenDegrees) / 2);

int sixteenDegreesMax = sixteenDegrees + ((twentytwoDegrees - sixteenDegrees) / 2);
int sixteenDegreesMin = sixteenDegrees - ((sixteenDegrees - sevenDegrees) / 2);

int twentytwoDegreesMax = twentytwoDegrees + ((twentysevenDegrees - twentytwoDegrees) / 2);
int twentytwoDegreesMin = twentytwoDegrees - ((twentytwoDegrees - sixteenDegrees) / 2);

int twentysevenDegreesMax = twentysevenDegreesMax + ((twentysevenDegrees - twentytwoDegrees) / 2);
int twentysevenDegreesMin = twentysevenDegreesMax + ((twentysevenDegrees - twentytwoDegrees) / 2);

int waitOnSwitchingShutterInMS = 3000;

int isSomeonePresent = LOW;
int isLightSufficient = LOW;

short shutterState = 1; // 1 -> UP ; 0 -> DOWN ; -1 -> UNKNOWN

bool isSevenDegrees(int degree)
{
  int max = sevenDegrees + 8;
  int min = sevenDegrees - 8;
  return degree < max && degree > min;
}

bool isSixteenDegrees(int degree)
{
  int max = sixteenDegrees + 6;
  int min = sixteenDegrees - 8;
  return degree < max && degree > min;
}

bool isTwentytwoDegrees(int degree)
{
  int max = twentytwoDegrees + 5;
  int min = sixteenDegrees - 6;
  return degree < max && degree > min;
}

bool isTwentysevenDegrees(int degree)
{
  int max = twentysevenDegrees + 6;
  int min = twentysevenDegrees - 6;
  return degree < max && degree > min;
}

void updateDatas()
{
  isSomeonePresent = digitalRead(isSomeonePresentPin);
  isLightSufficient = digitalRead(isLightSufficientPin);
  
  outerTemperature = analogRead(outerTemperatureAnalogPin);
  innerTemperature = analogRead(innerTemperatureAnalogPin);
}

void openShutter()
{
  if(shutterState == 1)
  {
    return;
  }
  
  digitalWrite(motorUpPin, HIGH);
  delay(waitOnSwitchingShutterInMS);
  digitalWrite(motorUpPin, LOW);
  
  shutterState = 1;
}

void closeShutter()
{ 
  if(shutterState == 0)
  {
    return;
  }
  
  digitalWrite(motorDownPin, HIGH);
  delay(waitOnSwitchingShutterInMS);
  digitalWrite(motorDownPin, LOW);
  
  shutterState = 0;
}

void openShutterToGetSufficientLux()
{
  if(shutterState == -1)
  {
    return;
  }
  
  if(isLightSufficient == HIGH)
  {
    digitalWrite(motorDownPin, HIGH);
    
    while(true)
    {
      delay(50);
      
      isLightSufficient = digitalRead(isLightSufficientPin);
      
      if(isLightSufficient == LOW)
      {
        digitalWrite(motorDownPin, LOW);
        break;
      }
    }
  }
  else if(isLightSufficient == LOW)
  {
    digitalWrite(motorUpPin, HIGH);
    
    while(true)
    {      
      delay(50);
      
      isLightSufficient = digitalRead(isLightSufficientPin);
      
      if(isLightSufficient == HIGH)
      {
        digitalWrite(motorUpPin, LOW);
        break;
      }
    }
  }
  
  shutterState = -1;
}

void setup() {
  pinMode(motorUpPin, OUTPUT);
  pinMode(motorDownPin, OUTPUT);
  
  pinMode(isSomeonePresentPin, INPUT);
  pinMode(isLightSufficientPin, INPUT);
}

void loop() {
  updateDatas();
  
  if(outerTemperature <= twentysevenDegreesMax && outerTemperature >= sevenDegreesMin)
  {
    openShutter();
  }
  else if(outerTemperature < sevenDegreesMax)
  {
    closeShutter();
  }
  else if(outerTemperature > twentysevenDegreesMin)
  {
    if(isSomeonePresent == HIGH)
    {  
      openShutterToGetSufficientLux();
    }
    else
    {
      closeShutter(); 
    }  
  }
  
  if(innerTemperature >= sixteenDegreesMin && innerTemperature <= twentytwoDegreesMax)
  {
    openShutter();
  }
  else if(innerTemperature < sixteenDegreesMax)
  {
    closeShutter();
  }
  else if(innerTemperature > twentytwoDegreesMin)
  {
    if(isSomeonePresent == HIGH)
    {
      openShutterToGetSufficientLux();
    }
    else
    {
      closeShutter();
    }
  }
  
  delay(1000);
}
