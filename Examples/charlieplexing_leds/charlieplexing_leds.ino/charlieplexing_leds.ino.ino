
#define PIN_1 27
#define PIN_2 26
#define PIN_3 25

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

  pinMode(PIN_1, OUTPUT);
  digitalWrite(PIN_1, LOW);
  pinMode(PIN_2, OUTPUT);
  digitalWrite(PIN_2, HIGH);
  pinMode(PIN_3, INPUT);
//   digitalWrite(PIN_3, LOW);

//delay(5);
  
    pinMode(PIN_1, OUTPUT);
  digitalWrite(PIN_1, HIGH);
  pinMode(PIN_2, OUTPUT);
  digitalWrite(PIN_2, LOW);
  pinMode(PIN_3, INPUT);
//   digitalWrite(PIN_3, LOW);

delay(5);

}



