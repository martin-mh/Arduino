/* Not finished yet, in development. */

/* PINs */
const int motorUpPin = 2;
const int motorDownPin = 3;

const int isSomeonePresentPin = 4;
const int isLightSufficientPin = 5;

const int outerTemperatureSensorPin = 0;
const int innerTemperatureSensorPin = 1;

/* VALUES */
int outerTemperature = 0;
int innerTemperature = 0;

int waitOnSwitchingShutterInMS = 3000;

int isSomeonePresent = LOW;
int isLightSufficient = LOW;

short shutterState = 1; // 1 -> UP ; 0 -> DOWN ; -1 -> UNKNOWN

void updateDatas()
{
  isSomeonePresent = digitalRead(isSomeonePresentPin);
  isLightSufficient = digitalRead(isLightSufficientPin);
  
  outerTemperature = analogRead(outerTemperatureSensorPin);
  innerTemperature = analogRead(innerTemperatureSensorPin);
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
  
  if(outerTemperature <= 27 && outerTemperature >= 7)
  {
    openShutter();
  }
  else if(outerTemperature < 7)
  {
    closeShutter();
  }
  else if(outerTemperature > 27)
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
  
  if(innerTemperature >= 16 && innerTemperature <= 22)
  {
    openShutter();
  }
  else if(innerTemperature < 16)
  {
    closeShutter();
  }
  else if(innerTemperature > 22)
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
