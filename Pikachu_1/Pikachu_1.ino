#include <FastLED.h>

#define NUM_LEDS 61
#define DATA_PIN 21
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

char DIR_Latch   = 12;
char DIR_SER     = 8;
char DIR_CLK     = 4;

char PWM_M1     = 11;
char PWM_M2     = 3;
char PWM_M3     = 5;
char PWM_M4     = 6;

char sensor     = 10;

char estado     = 0;
char estado_mov = 0;

unsigned long tempo_arma = 0;
unsigned long tempo_mov  = 0;

int valor_b = 0;
int data_by_serial = 0;

void aciona_motor_b(int M, int S, int M_P){
  char i = 0;
  int valor_b_temp = 0;

  if (M == 1){
    analogWrite(PWM_M1, M_P);
    valor_b = valor_b & 0b11110011;
    if (S == 1){ valor_b = valor_b | 0b00000100; }
    else if (S == 2){ valor_b = valor_b | 0b00001000; }
  }
  if (M == 2){
    analogWrite(PWM_M2, M_P);
    valor_b = valor_b & 0b11101101;
    if (S == 1){ valor_b = valor_b | 0b00000010; }
    else if (S == 2){ valor_b = valor_b | 0b00010000; }
  }
  if (M == 3){
    analogWrite(PWM_M3, M_P);
    valor_b = valor_b & 0b10111110;
    if (S == 1){ valor_b = valor_b | 0b00000001; }
    else if (S == 2){ valor_b = valor_b | 0b01000000; }
  }
  if (M == 4){
    analogWrite(PWM_M4, M_P);
    valor_b = valor_b & 0b01011111;
    if (S == 1){ valor_b = valor_b | 0b00100000; }
    else if (S == 2){ valor_b = valor_b | 0b10000000; }
  }

  valor_b_temp = valor_b;
  for (i = 0; i <= 7; i++){
    analogWrite(DIR_SER, LOW);
    if ((valor_b_temp & 0b10000000) == 128){ digitalWrite(DIR_SER, HIGH); }
    delay(1);
    digitalWrite(DIR_CLK, HIGH);
    delay(1);
    digitalWrite(DIR_CLK, LOW);
    valor_b_temp = valor_b_temp * 2;
  }
  digitalWrite(DIR_Latch, HIGH);
  delay(1);
  digitalWrite(DIR_Latch, LOW);
}

void Trata_serial(void){
  estado_mov = 1;
  Serial.println(data_by_serial);
  Serial.println("A");

  if (data_by_serial == 'w'){
    Serial.println("F");
    if ((estado != 1) && (estado != 2)){
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 100));
      FastLED.show();
    }
    aciona_motor_b(1, 1, 155);
    aciona_motor_b(3, 1, 255);
  }
  if (data_by_serial == 's'){
    Serial.println("T");
    if ((estado != 1) && (estado != 2)){
      fill_solid(leds, NUM_LEDS, CRGB(100, 0, 0));
      FastLED.show();
    }
    aciona_motor_b(1, 2, 195);
    aciona_motor_b(3, 2, 255);
  }
  if (data_by_serial == 'a'){
    Serial.println("E");
    if ((estado != 1) && (estado != 2)){
      fill_solid(leds, NUM_LEDS, CRGB(0, 100, 0));
      FastLED.show();
    }
    aciona_motor_b(1, 2, 155);
    aciona_motor_b(3, 1, 255);
  }
  if (data_by_serial == 'd'){
    Serial.println("D");
    if ((estado != 1) && (estado != 2)){
      fill_solid(leds, NUM_LEDS, CRGB(100, 0, 100));
      FastLED.show();
    }
    aciona_motor_b(1, 1, 155);
    aciona_motor_b(3, 2, 255);
  }
  if (data_by_serial == 'q'){
    Serial.println("S");
    if ((estado != 1) && (estado != 2)){
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      FastLED.show();
    }
    aciona_motor_b(1, 0, 0);
    aciona_motor_b(3, 0, 0);
  }
  tempo_mov = millis();
}

void setup(){
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(100);
  fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
  FastLED.show();

  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);

  pinMode(PWM_M1, OUTPUT);
  pinMode(PWM_M2, OUTPUT);
  pinMode(PWM_M3, OUTPUT);
  pinMode(PWM_M4, OUTPUT);

  analogWrite(PWM_M1, 0);
  analogWrite(PWM_M2, 0);
  analogWrite(PWM_M3, 0);
  analogWrite(PWM_M4, 0);

  pinMode(DIR_SER, OUTPUT);
  pinMode(DIR_CLK, OUTPUT);
  pinMode(DIR_Latch, OUTPUT);

  digitalWrite(DIR_SER, LOW);
  digitalWrite(DIR_CLK, LOW);
  digitalWrite(DIR_Latch, LOW);

  pinMode(sensor, INPUT_PULLUP);

  fill_solid(leds, NUM_LEDS, CRGB(255, 255, 0));
  FastLED.show();

  Serial3.begin(9600);
  Serial.begin(9600);
  Serial.println("INICIO");
}

void loop (){
  if (Serial3.available()){
    data_by_serial = Serial3.read();
    Serial.println(data_by_serial);
    Serial3.write(data_by_serial);
    if ((data_by_serial == 'a') || (data_by_serial == 'd') || (data_by_serial == 'w') || (data_by_serial == 's') || (data_by_serial == 'q')){
      Trata_serial();
    }
  }

  if ((estado_mov == 1) && ((millis() - tempo_mov) >= 400)){
    Serial.println("K");
    aciona_motor_b(1, 0, 0);
    aciona_motor_b(3, 0, 0);
    if ((estado != 1) && (estado != 2)){
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
      FastLED.show();
    }
    estado_mov = 0;
  }

  if ((digitalRead(sensor) == 0) && (estado == 0)){
    Serial.println("A");
    estado = 1;
    tempo_arma = millis();

    fill_solid(leds, NUM_LEDS, CRGB(255, 0, 0));
    FastLED.show();

    aciona_motor_b(2, 1, 200);
    aciona_motor_b(4, 2, 200);
  }

  if ((estado == 1) && ((millis() - tempo_arma) >= 250)){
    estado = 2;
    tempo_arma = millis();
    aciona_motor_b(2, 0, 0);
    aciona_motor_b(4, 0, 0);
  }

  if ((estado == 2) && ((millis() - tempo_arma) >= 14750)){
    estado = 3;
    tempo_arma = millis();
    aciona_motor_b(2, 2, 200);
    aciona_motor_b(4, 1, 200);
  }

  if ((estado == 3) && ((millis() - tempo_arma) >= 250)){
    estado = 0;

    fill_solid(leds, NUM_LEDS, CRGB(255, 255, 0));
    FastLED.show();

    aciona_motor_b(2, 0, 0);
    aciona_motor_b(4, 0, 0);
  }
}