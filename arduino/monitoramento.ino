// Define o pino analógico conectado ao potenciômetro (não utilizado diretamente neste código, mas reservado)
const int potPin = A0;

// Define o pino digital conectado ao LED
const int ledPin = 7;

// Variável para armazenar a temperatura simulada
float temperatura;

void setup() {
  // Inicializa a comunicação serial com baud rate de 9600 bps
  Serial.begin(9600);

  // Configura o pino do LED como saída
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Gera uma variação aleatória suave na temperatura
  // Aqui, a função random() gera um número entre -2 e 10
  int variacao = random(-2, 10); 

  // Adiciona a variação à temperatura atual
  temperatura += variacao;

  // Limita o valor da temperatura entre 0 e 50 graus Celsius
  if (temperatura < 0) temperatura = 0;
  if (temperatura > 50) temperatura = 50;

  // Exibe a temperatura simulada no monitor serial
  Serial.print("Temperatura simulada: ");
  Serial.print(temperatura);
  Serial.println(" °C");

  // Se a temperatura for maior que 30 °C, acende o LED
  if (temperatura > 30) {
    digitalWrite(ledPin, HIGH);
  } else {
    // Caso contrário, apaga o LED
    digitalWrite(ledPin, LOW);
  }

  // Quando a temperatura atinge o limite superior (50 °C), reseta para 20 °C
  // Isso simula um ciclo e evita que a temperatura continue subindo indefinidamente
  if (temperatura >= 50) temperatura = 20;

  // Aguarda 1 segundo antes de repetir o ciclo
  delay(1000);
}
