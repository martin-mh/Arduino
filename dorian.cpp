const int k1 = 2;
const int k2 = 3;
const int dfa = 4;
const int dfn = 5;

int dfaValue = LOW;
int dfnValue = LOW;

void setup() {
	pinMode(k1, OUTPUT);
	pinMode(K2, OUTPUT);

	pinMode(dfa, INPUT);
	pinMode(dfn, INPUT);
}

void updateDatas()
{
	dfaValue = digitalRead(dfa);
	dfnValue = digitalRead(dfn);
}

void loop() {
  updateDatas();

  if(dfnValue == HIGH)
  {
  	digitalWrite(k1, LOW);
  	digitalWrite(k2, LOW);

  	delay(50);
  	return;
  }

  if(dfaValue == HIGH)
  {
  	digitalWrite(k1, HIGH);
  	digitalWrite(k2, HIGH);
  }
  else if(dfaValue == LOW)
  {
  	digitalWrite(k1, HIGH);
  	digitalWrite(k2, HIGH);
  }

  delay(50);
}
