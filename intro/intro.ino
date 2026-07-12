//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
// Developed by Amit Roy - 
//github Profile Link: - https://github.com/dedsechack-1337
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

uint8_t loveChar[] = {
 0x11,
  0x11,
  0x0E,
  0x15,
  0x11,
  0x0E,
  0x15,
  0x04
};
void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.createChar(0, loveChar);
  lcd.backlight();


}


void loop()
{

  lcd.setCursor(0,0);
  lcd.print("Hello, Hackers");
  lcd.print(char(0));
  lcd.setCursor(2,1);
  lcd.print("RFID CLONER");
  delay(3000);
  lcd.clear();

  lcd.setCursor(4, 0);
  lcd.print("Brainware");
  lcd.setCursor(4,1);
  lcd.print("Univercity");
  delay(3000);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Amit");
  lcd.setCursor(7, 1);
  lcd.print("Arpan");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Adrija");  
  lcd.setCursor(8, 1);
  lcd.print("Subhodip");
  delay(3000);
      

}
