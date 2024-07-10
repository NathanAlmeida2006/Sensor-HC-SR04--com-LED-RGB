#define TRIG_PIN 4        // Define o pino do Trig
#define ECHO_PIN 3        // Define o pino do Echo

#define VERMELHO_PIN 12   // Define o pino do LED vermelho
#define VERDE_PIN 11      // Define o pino do LED verde
#define AZUL_PIN 10       // Define o pino do LED azul

const int DISTANCIA_VERMELHO = 10; // Distância máxima para LED vermelho
const int DISTANCIA_AMARELO = 20;  // Distância máxima para LED amarelo

void setup() {
  pinMode(TRIG_PIN, OUTPUT);  // Configura o pino do Trig como saída
  pinMode(ECHO_PIN, INPUT);   // Configura o pino do Echo como entrada
  pinMode(VERMELHO_PIN, OUTPUT);  // Configura o pino do LED vermelho como saída
  pinMode(VERDE_PIN, OUTPUT);     // Configura o pino do LED verde como saída
  pinMode(AZUL_PIN, OUTPUT);      // Configura o pino do LED azul como saída
  Serial.begin(9600);             // Inicializa a comunicação serial para depuração
}

void loop() {
  long duracao = medirDuracaoPulso(TRIG_PIN, ECHO_PIN);
  long distancia = calcularDistancia(duracao);

  imprimirDistancia(distancia);

  definirCorLED(distancia);

  delay(500); // Aguarda 500 ms antes de fazer a próxima leitura
}

// Função para medir a duração do pulso
long medirDuracaoPulso(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH);
}

// Função para calcular a distância em centímetros
long calcularDistancia(long duracao) {
  return duracao * 0.034 / 2;
}

// Função para imprimir a distância no monitor serial
void imprimirDistancia(long distancia) {
  Serial.print("Distância: ");
  Serial.print(distancia);
  Serial.println(" cm");
}

// Função para definir a cor do LED RGB com base na distância
void definirCorLED(long distancia) {
  if (distancia <= DISTANCIA_VERMELHO) {
    setColor(255, 0, 0);  // Vermelho
  } else if (distancia <= DISTANCIA_AMARELO) {
    setColor(255, 255, 0);  // Amarelo
  } else {
    setColor(0, 255, 0);  // Verde
  }
}

// Função para definir a cor do LED RGB
void setColor(int red, int green, int blue) {
  analogWrite(VERMELHO_PIN, red);
  analogWrite(VERDE_PIN, green);
  analogWrite(AZUL_PIN, blue);
}