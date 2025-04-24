#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

const byte linhas = 4;
const byte colunas = 4;

const char matriz[linhas][colunas] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

const byte pinosLinhas[linhas] = {9, 8, 7, 6};
const byte pinosColunas[colunas] = {5, 4, 3, 2};

Keypad teclado = Keypad(makeKeymap(matriz), pinosLinhas, pinosColunas, linhas, colunas);

const int pushButton = 11;
const int sliderButton1 = A2;
const int sliderButton2 = A3;
const int sensorMovimento1 = A0;
const int sensorMovimento2 = A1;
const int led = 13;
const int buzzer = 12;
const String senha = "1234";
char keypad;
String pad = "";
bool estadoPorta;
bool estadoJanela;
bool estadoButton;
bool sensorValue1;
bool sensorValue2;
bool alarmeAtivado = false;

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  pinMode(sliderButton1, INPUT);
  pinMode(sliderButton2, INPUT);
  pinMode(sensorMovimento1, INPUT);
  pinMode(sensorMovimento2, INPUT);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(pushButton, INPUT);

  lcd.begin(20, 4);
  lcd.init();
  lcd.backlight();
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sistema de Alarme");
  lcd.setCursor(0, 1);
  lcd.print("Pressione A p ativar");
  
  Serial.begin(9600);
}

void loop() {
  keypad = teclado.getKey();
  
  if (keypad) {
    processarTeclado();
  }
  
  if (alarmeAtivado) {
    monitorarSensores();
  }
}

void processarTeclado() {
  if (keypad == 'A' && !alarmeAtivado) {
    ativarAlarme();
    return;
  }
  
  if (keypad >= '0' && keypad <= '9' || keypad == '*' || keypad == '#') {
    if (keypad == '*') {
      pad = "";
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Digite a senha:");
      return;
    }
    
    if (keypad == '#') {
      verificarSenha();
      return;
    }
    
    pad += String(keypad);
    lcd.setCursor(0, 1);
    lcd.print(pad);
  }
}

void verificarSenha() {
  lcd.setCursor(0, 2);
  
  if (pad == senha) {
    lcd.print("ACESSO LIBERADO");
    desativarAlarme();
  } else {
    lcd.print("ACESSO NEGADO");
    for (int i = 0; i < 3; i++) {
      digitalWrite(led, HIGH);
      tone(buzzer, 500);
      delay(100);
      digitalWrite(led, LOW);
      noTone(buzzer);
      delay(100);
    }
  }
  
  pad = "";
  delay(1000);
  
  if (alarmeAtivado) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Digite a senha:");
  }
}

void ativarAlarme() {
  alarmeAtivado = true;
  
  digitalWrite(led, HIGH);
  tone(buzzer, 1000, 500);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ALARME ATIVADO");
  delay(1000);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Digite a senha:");
  
  noTone(buzzer);
  digitalWrite(led, LOW);
}

void desativarAlarme() {
  alarmeAtivado = false;
  
  digitalWrite(led, LOW);
  noTone(buzzer);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ALARME DESATIVADO");
  lcd.setCursor(0, 1);
  lcd.print("Pressione A p ativar");
}

void monitorarSensores() {
  bool dispararAlarme = false;
  String sensorDisparado = "";

  estadoPorta = digitalRead(sliderButton1);
  if (estadoPorta == HIGH) {
    dispararAlarme = true;
    sensorDisparado = "Porta";
  }

  estadoJanela = digitalRead(sliderButton2);
  if (estadoJanela == HIGH) {
    dispararAlarme = true;
    sensorDisparado = "Janela";
  }

  estadoButton = digitalRead(pushButton);
  if (estadoButton == HIGH) {
    dispararAlarme = true;
    sensorDisparado = "Emergencia";
  }

  sensorValue1 = digitalRead(sensorMovimento1);
  if (sensorValue1 == HIGH) {
    dispararAlarme = true;
    sensorDisparado = "Sensor 1";
  }

  sensorValue2 = digitalRead(sensorMovimento2);
  if (sensorValue2 == HIGH) {
    dispararAlarme = true;
    sensorDisparado = "Sensor 2";
  }
  
  if (dispararAlarme) {
    dispararAlerta(sensorDisparado);
  }
}

void dispararAlerta(String sensor) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ALERTA: " + sensor);
  lcd.setCursor(0, 1);
  lcd.print("Digite a senha:");

  tone(buzzer, 1000);
  digitalWrite(led, HIGH);
  delay(500);
  noTone(buzzer);
  digitalWrite(led, LOW);
  delay(500);
}