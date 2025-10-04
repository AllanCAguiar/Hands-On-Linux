int ledPin = 22;
int ledValue = 50;
int ldrPin = 36;
int ldrMin = 0;
int ldrMax = 4095;
int threshold = 50;
unsigned long previousTime = millis();
unsigned long currentlyTime;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin, INPUT);
  // Led inicia apagado.
  digitalWrite(ledPin,LOW); 
  Serial.printf("SmartLamp Conectado!\n");
}

void loop() {
  if(!check) {
/* Pisca 5x* e permanece apagado*/
    for(int i = 0; i < 5; i++) {
      digitalWrite(ledPin,HIGH);
      delay(2000);

      digitalWrite(ledPin, LOW);
      delay(2000);
    }
    digitalWrite(ledPin,LOW);
    check = true;
  }

  currentlyTime = millis();
  if (currentlyTime - previousTime >= 2000) {
    processCommand("GET_LDR");
    previousTime = currentlyTime;
  }
  
  while (Serial.available() > 0) {
    String in = Serial.readStringUntil('\n');
    processCommand(in);
  }

  if (getLdrValue() >= threshold) {
    ledUpdate();
  }
  else {
    analogWrite(ledPin, 0);
  }
}

void processCommand(String command) {
  int parameter = -1;
  int delimiter = command.indexOf(' ');
  if (delimiter != -1) {
    parameter = command.substring(delimiter + 1, command.length()).toInt();
    command = command.substring(0, delimiter);
  }
  if (command.startsWith("SET_LED")) {
    if (parameter >= 0 && parameter <= 100) {
      ledValue = parameter;
      ledUpdate();
      Serial.println("RES SET_LED 1");
    }
    else {
      Serial.println("RES SET_LED -1");
    }
  }
  else if (command == "GET_LED"){
    Serial.print("RES SET_LED ");
    Serial.println(ledValue);
  }
  
  else if (command.equals("GET_LDR")){
    Serial.print("RES GET_LDR ");
    Serial.println(getLdrValue());
  }
  else if (command.equals("GET_THRESHOLD")){
    Serial.print("RES GET_THRESHOLD ");
    Serial.println(getThreshold());
  }
  else if (command.startsWith("SET_THRESHOLD")){
    if (parameter >= 0 && parameter <= 100){
      threshold = parameter;
      Serial.println("RES SET_THRESHOLD 1");
    }
    else{
      Serial.println("RES SET_THRESHOLD -1");
    }
  }
  else{
    Serial.println("ERR Unknown command.");
  }
}

void ledUpdate(){
  int pwmValue = map(ledValue, 0, 100, 0, 255);
  analogWrite(ledPin, pwmValue);
}

int getThreshold(){
  return threshold;
}

int getLdrValue(){
  float value = map(analogRead(ldrPin), ldrMin, ldrMax, 0, 100.0);
  return value;
}
