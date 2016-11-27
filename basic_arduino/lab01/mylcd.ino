
#include "mylcd.h"

#include <LiquidCrystal.h>

enum lcd_4bit_io_map{
  LCD_RS = 12,
  LCD_EN = 11,
  LCD_D4 = 5,
  LCD_D5 = 4,
  LCD_D6 = 3,
  LCD_D7 = 2,
} lcd_4bit_io_map_t;

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void setup_lcd01(){
  lcd.begin(16, 2);
  lcd.print("Hello world");
}

void lcd01(){
  lcd.setCursor(0,1);     // move to line 2
  lcd.print(millis()/1000);
}

///////////////////////////////////////////////

void setup_lcd02(){
  lcd.begin(16, 2);
  lcd.cursor(); // set to display curser
}

void lcd02(){
  static char ch = 'a';
  switch(ch){
    case 'm':
      lcd.rightToLeft();
      break;
    case 's':
      lcd.leftToRight();
      break;
    case ('z'+1):
      lcd.clear();
      lcd.home();
      ch = 'a';
      break;
  }
  lcd.write(ch);
  delay(1000);
  ch++;
}

///////////////////////////////////////////////
// hint: https://omerk.github.io/lcdchargen/
//ohm 
byte ohm_char[8] = {
  B00000,
  B01110,
  B10001,
  B10001,
  B10001,
  B01010,
  B11011,
  B00000
};

//heart
byte heart_char[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b01110,
  0b00100
};

void setup_lcd_customchar(){
  lcd.createChar(1, ohm_char);
  lcd.createChar(2, heart_char);
  lcd.begin(16, 2);
  lcd.write(1);
  lcd.write(2);
}

void lcd_customchar(){
}

