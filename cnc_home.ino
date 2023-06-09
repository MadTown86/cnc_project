const int controlPin1 = 2;
const int controlPin2 = 3;
const int enablePin = 9;
const int directionSwitchPin = 4;
const int onOffSwitchStateSwitchPin = 5;
const int potPin = A0;
const int proxPin = 10;
const int travelMax = 100;
const int powerUpProcedure = 11;

int homeState = 0;
int powerUpProcedureState = 0;
int previousPowerUpProcedureState = 0;
int curPosition = 0;
int onOffSwitchState = 0;
int proxSwitchState = 0;
int previousProxSwitchState = 0;
int previousOnOffSwitchState = 0;
int directionSwitchState = 0;
int previousDirectionSwitchState = 0;
int motorEnabled = 0;
int motorSpeed = 0;
int motorDirection = 1;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(powerUpProcedure, INPUT);
  pinMode(proxPin, INPUT);
  pinMode(directionSwitchPin, INPUT);
  pinMode(onOffSwitchStateSwitchPin, INPUT);
  pinMode(controlPin1, OUTPUT);
  pinMode(controlPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, LOW);

  while (homeState != HIGH)
  {

    if (digitalRead(proxPin) == HIGH)
    {
      homeState = 1;
    }
    else
    {
      while (digitalRead(proxPin) != HIGH)
      {
        /* Reverse */
        analogWrite(enablePin, 0);
        digitalWrite(controlPin1, LOW);
        digitalWrite(controlPin2, HIGH);
        analogWrite(enablePin, 150);
      }
    }
    if (digitalRead(proxPin) == HIGH)
    {
      homeState = 1;
    }
  }
}

void loop()
{
  delay(2000);
  Serial.print("\nProxPinState\n");
  Serial.print(proxSwitchState);
  Serial.print("\n");
  Serial.print("\nonOffSwitchState\n");
  Serial.print(onOffSwitchState);
  Serial.print("\n");
  Serial.print("\npreviousOnOffSwitchState\n");
  Serial.print(previousOnOffSwitchState);
  Serial.print("\n");
  Serial.print("\ndirectionSwitchState\n");
  Serial.print(directionSwitchState);
  Serial.print("\n");
  Serial.print("\npreviousDirectionSwitchState\n");
  Serial.print(previousDirectionSwitchState);
  Serial.print("\n");
  Serial.print("\nmotorEnabled\n");
  Serial.print(motorEnabled);
  Serial.print("\n");
  Serial.print("\nmotorSpeed\n");
  Serial.print(motorSpeed);
  Serial.print("\n");
  Serial.print("\nmotorDirection\n");
  Serial.print(motorDirection);
  Serial.print("\n");

  // put your main code here, to run repeatedly:
  onOffSwitchState = digitalRead(onOffSwitchStateSwitchPin);
  delay(1);
  directionSwitchState = digitalRead(directionSwitchPin);
  motorSpeed = analogRead(potPin) / 4;

  if (onOffSwitchState != previousOnOffSwitchState)
  {
    if (onOffSwitchState == HIGH)
    {
      motorEnabled = !motorEnabled;
    }
  }

  if (directionSwitchState != previousDirectionSwitchState)
  {
    if (directionSwitchState == HIGH)
    {
      motorDirection = !motorDirection;
    }
  }

  if (motorDirection == 1)
  {
    digitalWrite(controlPin1, HIGH);
    digitalWrite(controlPin2, LOW);
  }

  else
  {
    digitalWrite(controlPin1, LOW);
    digitalWrite(controlPin2, HIGH);
  }

  if (motorEnabled == 1)
  {
    analogWrite(enablePin, motorSpeed);
  }

  else
  {
    analogWrite(enablePin, 0);
  }

  previousDirectionSwitchState = directionSwitchState;
  previousOnOffSwitchState = onOffSwitchState;
}
