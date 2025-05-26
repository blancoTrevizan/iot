#include <WiFi.h> 
#include "PubSubClient.h"
#define ID_MQTT "SENAI_IOT01"                      //Informe um ID qualquer 
#define pubSensor1IotSenai "Sensor1IotSenai77"       //Informe um Tópico qualquer para publicar
#define pubStatusLed1IotSenai "StatusLed1IotSenai77" //Informe um Tópico qualquer para publicar
#define subLed1IotSenai "Led1Iot77"             //Informe um Tópico qualquer para assinar.
bool sensor1=0;   // Armazenar leitura do botao 1
bool _sensor1=0;  // Utilizado na logica acionamento do botao
bool statusSensor=0; 
bool led1=0;
bool _led1=0;
const char* SSID = "Wokwi-GUEST";  // Nome da rede WiFi que deseja se conectar
const char* PASSWORD = "";         // Senha da rede WiFi que deseja se conectar
WiFiClient wifiClient;                        
const char* BROKER_MQTT = "mqtt-dashboard.com"; //URL do broker MQTT que se deseja utilizar
int BROKER_PORT = 1883;                         // Porta do Broker MQTT
PubSubClient MQTT(wifiClient);  // Instancia o Cliente MQTT 
//----------------------Declaração das Funções
void AtualizaConexoes();// Atualiza conexoes com WiFi e MQTT Broker.
void ConectaWiFi();     // Faz conexão com WiFi
void ConectaMQTT();     // Faz conexão com Broker MQTT
void EnviaPacote();     //
void RecebePacote(char* topic, byte* payload, unsigned int length);


const int potPin = A0;
const int ledPin = 2;

float temperatura;
//-----------------------------------------------
void setup()
{
  //pinMode(4, INPUT_PULLUP);// Declara pino 4 como entrada e resistores PullUp Ativados.  
  pinMode(4, INPUT);         // Declara pino 4 como entrada e resistores PullUp Ativados.  
  pinMode(2,OUTPUT);         // Declara Pino 2 saída.    
  Serial.begin(115200);      // Inicializa comunicação serial 
  ConectaWiFi();
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);  
  MQTT.setCallback(RecebePacote);  
}
//-----------------------------------------------
void loop()
{
  AtualizaConexoes();
  EnviaPacote();
  MQTT.loop();
  
  // Simula uma variação aleatória suave
  int variacao = random(-2, 10); // Varia entre -2 e +2 graus
  temperatura += variacao;

  // Limita a faixa entre 0 e 50
  if (temperatura < 0) temperatura = 0;
  if (temperatura > 50) temperatura = 50;

  Serial.print("Temperatura simulada: ");
  Serial.print(temperatura);
  Serial.println(" °C");

  if (temperatura > 30) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

   if (temperatura >= 50) temperatura = 20;


    // Converter temperatura para string
  char temperaturaStr[10];
  dtostrf(temperatura, 4, 2, temperaturaStr);

  // Publicar no tópico
  MQTT.publish(pubSensor1IotSenai, temperaturaStr);
  Serial.print("Temperatura publicada com sucesso!");
  
  delay(1000);
}
//------------------------------------------------
void AtualizaConexoes()
{
    if (!MQTT.connected()) 
    {
       ConectaMQTT(); 
    }
    ConectaWiFi(); //se não há conexão com o WiFI, a conexão é refeita
}
//------------------------------------------------
void ConectaWiFi()
{
  if (WiFi.status() == WL_CONNECTED) 
  {
     return;
  }
  Serial.print("Conectando-se na rede: ");
  Serial.print(SSID);
  Serial.println("  Aguarde!");
  WiFi.begin(SSID, PASSWORD); // Conecta na rede WI-FI  
  while (WiFi.status() != WL_CONNECTED) 
  {
      delay(100);
      Serial.print(".");
  }
  Serial.println();
  Serial.print("Conectado com sucesso, na rede: ");
  Serial.print(SSID);  
  Serial.print("  IP obtido: ");
  Serial.println(WiFi.localIP()); 
}
//------------------------------------------------
void ConectaMQTT()
{ 
  while (!MQTT.connected()) 
  {
    Serial.print("Conectando ao Broker MQTT: ");
    Serial.println(BROKER_MQTT);
    if (MQTT.connect(ID_MQTT))
    {
      Serial.println("Conectado ao Broker com sucesso!");
      MQTT.subscribe(subLed1IotSenai);
    } 
    else
    {
      Serial.println("Nao foi possivel se conectar ao broker.");
      Serial.println("Nova tentatica de conexao em 10s");
      delay(10000);
    }
  }
}
//------------------------------------------------
void EnviaPacote() 
{
  sensor1=digitalRead(4); // Efetua leitura do sonsor conectado ao pino 4 
  if(sensor1==1 && _sensor1==0)
  {
    _sensor1=1;
    Serial.println("Mudança de estado do sensor");  
    statusSensor=!statusSensor;
    if (statusSensor==1)
    {
      MQTT.publish(pubSensor1IotSenai, "1");
      Serial.println("Sensor1 Ativado. Payload enviado.");   
    }
    else
    {
      MQTT.publish(pubSensor1IotSenai, "0");
      Serial.println("Sensor1 Desativado. Payload enviado.");   
    }
  }
  if(sensor1==0) _sensor1=0;

  if (led1==1 && _led1==0)
  {
    _led1=1;
    MQTT.publish(pubStatusLed1IotSenai, "1");
    Serial.println("Led 1 Ligado. Payload enviado.");    
  }
  if (led1==0 && _led1==1)
  {
    _led1=0;
    MQTT.publish(pubStatusLed1IotSenai, "0");
    Serial.println("Led 1 Desligado. Payload enviado.");    
  }
  
}
//-----------------------------------------------------------------
void RecebePacote(char* topic, byte* payload, unsigned int length) 
{
  String msg;
  for(int i = 0; i < length; i++)//obtem a string do payload recebido
  {
    char c = (char)payload[i];
    msg += c;
  }
  if (msg == "0") 
  {
    led1=0;
    digitalWrite(2,LOW); // Desliga pino 2 LED
  }
  if (msg == "1") 
  {
    led1=1;
    digitalWrite(2,HIGH);// Liga pino 2 LED
  }
   Serial.println(msg); // Imprime a mensagem na porta serial
}
