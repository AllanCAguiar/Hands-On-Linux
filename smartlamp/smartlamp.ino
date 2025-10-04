// Defina os pinos de LED e LDR
// Defina uma variável com valor máximo do LDR (4000)
// Defina uma variável para guardar o valor atual do LED (10)

// ==== Configurações do LED ====
#define LED_CHANNEL 0
#define LED_FREQUENCY 5000
#define LED_RESOLUTION 8 // 8 bits → PWM de 0 a 255

int ledPin = 22;
int ledValue = 50;

int ldrPin = 36;
int ldrMin = 0;
int ldrMax = 4096;
int threshold = 50;

void setup()
{
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin, INPUT);
  Serial.printf("SmartLamp Conectado!\n");
}

// Função loop será executada infinitamente pelo ESP32
void loop()
{
  while (Serial.available() > 0)
  {
    String in = Serial.readStringUntil('\n');
    processCommand(in);
  }

  if (getLdrValue() >= threshold)
  {
    digitalWrite(ledPin, HIGH);
  }
  else
  {
    digitalWrite(ledPin, LOW);
  }
}

void processCommand(String command)
{
  int parameter = -1;
  int delimiter = command.indexOf(' ');
  if (delimiter != -1)
  {
    parameter = command.substring(delimiter + 1, command.length()).toInt();
    command = command.substring(0, delimiter);
  }
  //FUNCION LED
  if (command.startsWith("SET_LED"))
  {
    int spaceIndex = command.indexOf(' ');
    if (spaceIndex > 0)
    {
      String valueStr = command.substring(spaceIndex + 1);
      int value = valueStr.toInt();

      if (value >= 0 && value <= 100)
      {
        ledValue = value;
        ledUpdate();
        Serial.println("OK");
      }
      else
      {
        Serial.println("ERRO: Valor fora do intervalo (0-100)");
      }
    }
    else
    {
      Serial.println("ERRO: Comando mal formatado");
    }
  }
  else if (command == "GET_LED")
  {
    Serial.print("LED: ");
    Serial.println(ledValue);
  }
  else
  {
    Serial.println("Comando desconhecido");
  }

  //LDR
  if (command.equals("GET_LDR"))
  {
    Serial.println("Oi " + getLdrValue());
  }
  else if (command.equals("GET_THRESHOLD"))
  {
    Serial.println(getThreshold());
  }
  else if (command.startsWith("SET_THRESHOLD"))
  {
    if (parameter >= 0 && parameter <= 100)
    {
      threshold = parameter;
      Serial.println("RES SET_THRESHOLD 1");
    }
    else
    {
      Serial.println("RES SET_THRESHOLD -1");
    }
  }
  // compare o comando com os comandos possíveis e execute a ação correspondente
}

// ===============================
// Função: ledUpdate
// Atualiza intensidade PWM do LED
// ===============================
void ledUpdate()
{
  // Converte de 0-100 para 0-255
  int pwmValue = map(ledValue, 0, 100, 0, 255);
  ledcWrite(LED_CHANNEL, pwmValue);
}

// Função para ler o valor do LDR
int ldrGetValue()
{
  ldrValue = analogRead(ldrPin);
  int normalized = map(ldrValue, 0, ldrMax, 0, 100);
  if (normalized > 100)
    normalized = 100;
  if (normalized < 0)
    normalized = 0;
  return normalized;
}

int getThreshold()
{
  return threshold;
}

int getLdrValue()
{
  float value = map(analogRead(ldrPin), ldrMin, ldrMax, 0, 100.0);
  return value;
}
