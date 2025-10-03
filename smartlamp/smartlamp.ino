// Defina os pinos de LED e LDR
// Defina uma variável com valor máximo do LDR (4000)
// Defina uma variável para guardar o valor atual do LED (10)
int ledPin = 22;
int ledValue = 50;

int ldrPin = 36;
int ldrMin = 0;
int ldrMax = 4096;
int threshold = 50;

void setup() {
    Serial.begin(9600);
    
    pinMode(ledPin, OUTPUT);
    pinMode(ldrPin, INPUT);
    Serial.printf("SmartLamp Conectado!\n");
    
}

// Função loop será executada infinitamente pelo ESP32
void loop() {
    while(Serial.available() > 0) {
      String in = Serial.readStringUntil('\n');
      processCommand(in);    
      
    }
    
    if (getLdrValue() >= threshold) {
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }
    
}


void processCommand(String command) {
  int  parameter = -1;
  int delimiter = command.indexOf(' ');
  if (delimiter != -1) {
    parameter = command.substring(delimiter + 1, command.length()).toInt();
    command = command.substring(0, delimiter);
  }
  if (command.equals("GET_LDR")) {
    Serial.println("Oi " + getLdrValue());
  } else if (command.equals("GET_THRESHOLD")) {
    Serial.println(getThreshold());
  } else if (command.startsWith("SET_THRESHOLD")) {
    if (parameter >= 0 && parameter <= 100) {
      threshold = parameter;
      Serial.println("RES SET_THRESHOLD 1");
    } else {
      Serial.println("RES SET_THRESHOLD -1");
    }
  } 
    // compare o comando com os comandos possíveis e execute a ação correspondente      
}

// Função para atualizar o valor do LED
void ledUpdate() {
    // Valor deve convertar o valor recebido pelo comando SET_LED para 0 e 255
    // Normalize o valor do LED antes de enviar para a porta correspondente
}

// Função para ler o valor do LDR
int ldrGetValue() {
    // Leia o sensor LDR e retorne o valor normalizado entre 0 e 100
    // faça testes para encontrar o valor maximo do ldr (exemplo: aponte a lanterna do celular para o sensor)       
    // Atribua o valor para a variável ldrMax e utilize esse valor para a normalização
}

int getThreshold() {
  return threshold;  
}

int getLdrValue() {
  float value = map(analogRead(ldrPin), ldrMin, ldrMax, 0, 100.0);
  return value;
}
