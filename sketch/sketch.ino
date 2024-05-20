int gasSensor = A0;  // gas sensor input
int gasBuzzer = 11;  // gas buzzer output
int G_led = 8;       // green led output
int R_led = 9;       // red led output

const int doorSensor = 4; // door sensor input
const int doorBuzzer = 3; // door buzzer output

unsigned long doorOpenedTime = 0;
bool doorOpen = false;

void setup() {
  pinMode(gasSensor, INPUT);
  // pinMode(doorSensor, INPUT);
  pinMode(doorSensor, INPUT_PULLUP);

  pinMode(gasBuzzer, OUTPUT);
  pinMode(doorBuzzer, OUTPUT);
  pinMode(R_led, OUTPUT);
  pinMode(G_led, OUTPUT);

  Serial.begin(9600);  // Start serial communication at 9600 bps
}

void loop() {
  int gasValue = analogRead(gasSensor);
  int doorState = digitalRead(doorSensor);

  // print sensor values
  Serial.print("Gas Sensor Value: ");
  Serial.println(gasValue);
  Serial.print("Door Sensor State: ");
  Serial.println(doorState);

  Serial.print("R_led: ");
  Serial.println(digitalRead(R_led));
  Serial.print("G_led: ");
  Serial.println(digitalRead(G_led));


  if(gasValue<300 && doorState==LOW){   // default state
    digitalWrite(G_led, HIGH);
    digitalWrite(R_led, LOW);
    noTone(gasBuzzer);
    noTone(doorBuzzer);
  }
  else{
    digitalWrite(G_led, LOW);
    digitalWrite(R_led, HIGH);
  }

  // gas sensor condition
  if(gasValue>250){
    tone(gasBuzzer, 1000, 500);
    Serial.println("Gas detected! Gas Buzzer ON");
  }  

  // door sensor condition
  if(doorState == HIGH) {
    if (!doorOpen) {
      doorOpenedTime = millis();  // current time in milliseconds
      doorOpen = true;
    } 
    else {
      if (millis() - doorOpenedTime >= 10000) { // door was open for 10 seconds
        tone(doorBuzzer, 1000);
        Serial.println("Door opened for 10 seconds! Door Buzzer ON");
      }
    }
  } 
  else {  // Door closed
    doorOpen = false;
    noTone(doorBuzzer);
    doorOpenedTime = 0; // Reset the timer
    Serial.println("Door closed. Door Buzzer OFF");
  }

  delay(100);
}