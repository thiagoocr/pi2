//biblioteca para utilizar o esp 32 no IDE do arduino
#include <dummy.h>


//pinos para o ultrassom da frente do carrinho
const uint8_t trig_pin = 4;
const uint8_t echo_pin = 5;

uint32_t print_timer;

//biblioteca para capturar a distancia do objeto ao ultrassom
void distancia_ultrassom(const uint8_t trig,const uint8_t echo);

void setup() {
  //comunicaçao serial a 9600
  Serial.begin(9600); 
  //configuraçoes iniciais para os pinos do sensor ultrassom
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  digitalWrite(trig_pin, LOW);
}

void loop() {
  //biblioteca para calcular a distancia usando o sensor ultrassom 
  distancia_ultrassom(trig_pin, echo_pin);
}


void distancia_ultrassom(const uint8_t trig, const uint8_t echo) {
  // Espera 0,5s (500ms) entre medições.
  if (millis() - print_timer > 500) {
    print_timer = millis();

    // Pulso de 5V por pelo menos 10us para iniciar medição.
    digitalWrite(trig_pin, HIGH);
    delayMicroseconds(11);
    digitalWrite(trig_pin, LOW);

    /* Mede quanto tempo o pino de echo ficou no estado alto, ou seja,
      o tempo de propagação da onda. */
    uint32_t pulse_time = pulseIn(echo_pin, HIGH);

    /* A distância entre o sensor ultrassom e o objeto será proporcional a velocidade
      do som no meio e a metade do tempo de propagação. Para o ar na
      temperatura ambiente Vsom = 0,0343 cm/us. */
    //pode ser double distance tbm, mas nao ha a necessidade para este projeto
    int distance = 0.01715 * pulse_time;
    Serial.print(distance);
    Serial.println(" cm");


  }
}
