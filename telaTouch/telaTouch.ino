//Bibliotecas inclusas
#include <Adafruit_GFX.h>    
#include <Adafruit_TFTLCD.h> 
#include <TouchScreen.h>

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

//Definição das cores
#define WHITE          0xFFFF
#define YELLOW         0xFFE0
#define RED            0xF800
#define BLUE           0x001F
#define BLACK          0x0000

#define LIGADO         0x07E0
#define DESLIGADO      0xF800

#define MINPRESSURE 10
#define MAXPRESSURE 1000


//Dados a serem alterados conforme a calibragem!
#define YP A1
#define XM A2
#define YM 7
#define XP 6

#define TS_LEFT 167
#define TS_RT   906
#define TS_TOP  955
#define TS_BOT  200

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

int X, Y;
long corBot[3] = {DESLIGADO, DESLIGADO, DESLIGADO};

Point waitTouch() {
  Point p;
  do {
    p = ts.getPoint();
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
  } while ((p.z < MINPRESSURE ) || (p.z > MAXPRESSURE));
  
  p.x = map(p.x, TS_LEFT, TS_RT, 0, 240);
  p.y = map(p.y, TS_BOT, TS_TOP, 0, 320);
  
  return p;
}

void setup() {
  Serial.begin(9600);
  
  tft.reset();
  
  //Altere aqui o código do seu display!
  tft.begin(0x9341); 
  
  //setRotation define modo Retrato e Paisagem
  //1 para modo paisagem
  //2 para modo retrato
  tft.setRotation(2);

  //fillScreen define a cor de fundo da tela
  tft.fillScreen(BLACK);

  IntroScreen();
  draw_Buttons(0);
}

void loop() {
  Point p = waitTouch();
  X = p.x; Y = p.y;

  DetectButtons();

  delay(100);
}



//FUNÇÕES:

//Função que implementa a lógica dos botões
void DetectButtons() {

  if (X < 200 && X > 40) {

    if (Y > 220 && Y < 300) { // LOGICA PARA O BOTAO 1
      Serial.println ("Button 1");
      if (corBot[0] == LIGADO) corBot[0] = DESLIGADO;
      else corBot[0] = LIGADO;
      draw_Buttons(1);
    }


    if (Y > 120 && Y < 200) { // LOGICA PARA O BOTAO 2
      Serial.println ("Button 2");
      if (corBot[1] == LIGADO) corBot[1] = DESLIGADO;
      else corBot[1] = LIGADO;
      draw_Buttons(2);
    }

    if (Y > 20 && Y < 100) { // LOGICA PARA O BOTAO 3
      Serial.println ("Button 3");
      if (corBot[2] == LIGADO) corBot[2] = DESLIGADO;
      else corBot[2] = LIGADO;
      draw_Buttons(3);
    }

  }

}

//Função que implementa a tela inicial
//Considere a tela como 240x320 para Orientação Retrato e 320x240 para Orientação Paisagem
void IntroScreen() {

  //Função setCursor seleciona onde será renderizado o próximo item,
  //O primeiro parametro eixo x, segundo parametro eixo y, valores em pixels
  tft.setCursor (65, 50);
  //Função para tamanho do texto do próximo item a ser renderizado (Valor entre 0 e 30)
  tft.setTextSize (4);
  //Função para seleção da cor do próximo item a ser renderizado
  tft.setTextColor(WHITE);
  //Função para imprimir o texto na tela (utilize \n para quebra de linha)
  tft.println("Tela");
    tft.setCursor (35, 100);
  tft.println("Inicial");

  //definição de tempo para exibir a tela inicial
  delay(5000);

  //fillScreen 
  tft.fillScreen(BLACK);
}


//Função que desenha os botões na tela
void draw_Buttons(int type) {
  switch (type) {
    case 1:
      //fillRect desenha a caixa que seria o botão com os pixels
      //40, 20 seta o cursor, entre o pixel 40 do eixo X e 20 do eixo Y
      //160, 80 determina que a caixa teria 160 pixels de largura com 80 de altura
      tft.fillRect  (40, 20 , 160, 80, corBot[0]);

      tft.setTextColor(WHITE);
      tft.setTextSize (3);
      tft.setCursor(60, 50);
      tft.println("BOTAO 1");
      break;

    case 2:
      tft.fillRect  (40, 120, 160, 80, corBot[1]);

      tft.setTextColor(WHITE);
      tft.setTextSize (3);
      tft.setCursor(60, 150);
      tft.println("BOTAO 2");
      break;

    case 3:
      tft.fillRect  (40, 220, 160, 80, corBot[2]);

      tft.setTextColor(WHITE);
      tft.setTextSize (3);
      tft.setCursor(60, 250);
      tft.println("BOTAO 3");
      break;

//DEFINE O VALOR INICIAL DE CADA UM DOS BOTÕES
    default:
      tft.fillRect  (40, 20 , 160, 80, corBot[0]);
      tft.fillRect  (40, 120, 160, 80, corBot[1]);
      tft.fillRect  (40, 220, 160, 80, corBot[2]);

      tft.setTextColor(WHITE);
      tft.setTextSize (3);

      tft.setCursor(60, 50);
      tft.println("BOTAO 1");

      tft.setCursor(60, 150);
      tft.println("BOTAO 2");

      tft.setCursor(60, 250);
      tft.println("BOTAO 3");
  }

}