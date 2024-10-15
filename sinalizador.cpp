const int trigger = 8;
const int eco = 7;
const int led_verde = 2;
const int led_amarelo = 3;
const int led_vermelho = 4;
const int buzzer = 5;

int tempo = 600;
const int tempo_verde = 500;
const int tempo_amarelo = 300;
const int tempo_vermelho = 200;
const int botao = 10;
int estado=0;

long duracao;
float dist;

void setup() {
  Serial.begin(9600);

  pinMode(trigger, OUTPUT); // Configura o pino trigger como saída
  pinMode(eco, INPUT); // Configura o pino eco como entrada.

  pinMode(led_verde, OUTPUT);
  pinMode(led_amarelo, OUTPUT);
  pinMode(led_vermelho, OUTPUT);
  pinMode(botao,INPUT);

  pinMode(buzzer, OUTPUT);
  }

void apaga_leds(){
  digitalWrite(led_verde, LOW);
  digitalWrite(led_amarelo, LOW);
  digitalWrite(led_vermelho, LOW);

  }

void loop() {
  // Limpa o trigger
  digitalWrite(trigger, LOW);
  delayMicroseconds(5);

  // Configurar o trigger para nível alto para transmissão de sinais
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10); // tempo para envio do sinal
  digitalWrite(trigger, LOW);

  // Inicia contagem de tempo e lê o pino de eco
  duracao = pulseIn(eco, HIGH);

  // Calcular a distância
  dist = duracao * 0.034 / 2;

  Serial.print("Distância: ");
  Serial.print(dist);
  Serial.println(" cm");

  apaga_leds();

  if(dist > 220){
    digitalWrite(led_verde, HIGH);
    tone(buzzer, 3000);
    tempo = tempo_verde;
    } else
  if(dist < 220 && dist > 150){
    digitalWrite(led_amarelo, HIGH);
    tone(buzzer, 3000);
    tempo = tempo_amarelo;
    } else
  if(dist < 75){
    estado=digitalRead(botao);
  if(estado==0)

  {
  tone(buzzer, 3000);
  digitalWrite(led_vermelho, HIGH);
  tempo = tempo_vermelho;
  }
    else{
    noTone(buzzer);
    digitalWrite(led_vermelho, HIGH);
    tempo = 0;
    delay(2000);
    while(!digitalRead(botao)) {
    apaga_leds();
    };
  }
}

  delay(tempo);
  noTone(buzzer);
  delay(tempo);
}
