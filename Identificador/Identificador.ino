#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

//Definicao de cores
#define BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0
#define WHITE           0xFFFF

void setup() {
  uint16_t ID = tft.readID();

  tft.begin(ID);
  tft.setRotation(1);
  tft.fillScreen(BLACK);
  tft.setCursor(20, 20);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("Identificador:");
  tft.setTextSize(7);
  
  tft.setTextColor(WHITE);
  tft.setCursor(80, 120);
  tft.print(ID, HEX);
}
void loop() {
}
