//Biblioteki//
#include "LedControl.h"
#include "DFPlayer_Mini_Mp3.h"

//Inicjacja ekranika//
LedControl lc = LedControl(12, 11, 10, 1);

//Piny//
int noisePin = 2; //Pin czujnika dźwięku
int trigPin = 3; //Pin czujnia wstrząsów
int busyPin = 13; //Niebieski LED DFPlayera
int fotoPin = A0; //Pin czujnika światła
int forwardPin = A5; //Pin "czujnika" jazdy - do spr
int idlePin = 18; //Pin sygnału bezczynności

//Statusy//

byte busy = 0;
byte noise = 0;
int trig = 0;
int foto = 0;

//Timery//
unsigned long timer = 0;

void check() {
  busy = digitalRead(busyPin);
  noise = digitalRead(noisePin);
  trig = analogRead(trigPin);
  foto = analogRead(fotoPin);

  Serial.print("Zajętość MP3: ");
  Serial.println(busy);
  Serial.print("Hałas: ");
  Serial.println(noise);
  Serial.print("Ruch: ");
  Serial.println(trig);
  Serial.print("Światło: ");
  Serial.println(foto);
}

void glitch() {
  for (int i = 0; i <= 60; i++) {
    for (int j = 0; j <= 7; j++)
    lc.setColumn(0, j, random(B00000000, B11111111));
  }
}

void smiles (int x) {
  byte s[8] = {B00000000, B01100110, B01100110, B00000000, B00000000, B01000010, B00111100, B00000000};
  byte n[8] = {B00000000, B01100110, B01100110, B00000000, B00000000, B00000000, B01111110, B00000000};
  int b = 7;
  int c = 1;

  switch(x) {
    case 1: //Uśmiech
      for (int i = 0; i <= 7; i++) {
        lc.setColumn(0, i, s[b]);
        b -= 1;
      }
      break;
    case 2: //Neutralna mordka
      for (int i = 0; i <= 7; i++) {
        lc.setColumn(0, i, n[b]);
        b -= 1;
      }
      break;
  }
}

void piosenka () {
  mp3_play(11);
}

void setup() {
  //Wybudzenie sterownika MAX72XX//
  lc.shutdown(0, false);
  //Jasność ekraniku
  lc.setIntensity(0, 8);
  //Wyczyszczenie ekranu
  lc.clearDisplay(0);
  glitch();
  
  Serial.begin(9600);
  mp3_set_serial(Serial);
  mp3_set_volume(20);
  mp3_stop();

  //Piny
  pinMode(noisePin, INPUT);
  pinMode(trigPin, INPUT);
  pinMode(busyPin, INPUT);
  pinMode(fotoPin, INPUT_PULLUP);
  pinMode(forwardPin, INPUT);
  pinMode(idlePin, OUTPUT);

  //check();
  piosenka();
}

void loop() {
  smiles(2);
}
