// Defina os pinos de LED e LDR
// Defina uma variável com valor máximo do LDR (4000)
// Defina uma variável para guardar o valor atual do LED (10)
int ledPin = 22;
int ledValue;
bool check = false;

int ldrPin = 34;
int ldrValue;
// Faça testes no sensor ldr para encontrar o valor maximo e atribua a variável ldrMax
int ldrMax;

void setup() {
    Serial.begin(9600);
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin,LOW); // Led inicia apagado.
    pinMode(ldrPin, INPUT);
    Serial.printf("SmartLamp Conectado!\n");
    delay(1000);
    
}

// Função loop será executada infinitamente pelo ESP32
void loop() {
    ldrValue = analogRead(ldrPin);
    serial.println(ldrValue);

    if(!check){
        /* Pisca 5x* e permanece apagado*/
        for(int i = 0; i < 5; i++){
            digitalWrite(ledPin,HIGH);
            delay(2000);

            digitalWrite(ledPin, LOW);
            delay(2000);
            }
            digitalWrite(ledPin,LOW);
            check = true;
    }
    delay(500);
}


void processCommand(String command) {
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
