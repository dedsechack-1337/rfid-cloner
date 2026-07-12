/*
Developed By - Amit Roy 
Github: - https://github.com/dedsechack-1337
 */

#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>



#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

uint8_t loveChar[] = {
  0x0E,
  0x15,
  0x1B,
  0x0E,
  0x0E,
  0x04,
  0x00,
  0x00


};
byte customChar[] = {
  0x11,
  0x0A,
  0x1F,
  0x0E,
  0x15,
  0x04,
  0x04,
  0x1F
};

String authorizedUIDList[] ={
  "AB526A05",
  "AED1D9D1"
  }; //Authorize UID List Entry Here

const int authorizedUIDListSize = sizeof(authorizedUIDList) / sizeof(authorizedUIDList[0]);

char mode ='N';
String uid="";
byte NEW_UID[10];   // Array to hold UID
int uidLength = 0;

void setup() {
	Serial.begin(9600);		// Initialize serial communications with the PC
	while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
	SPI.begin();			// Init SPI bus
	mfrc522.PCD_Init();		// Init MFRC522
	delay(4);				// Optional delay. Some board do need more time after init to be ready, see Readme
	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details

  pinMode(5,INPUT_PULLUP);
  pinMode(6,INPUT_PULLUP);
  pinMode(7,INPUT_PULLUP);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(8,OUTPUT);
  lcd.init();  
	lcd.backlight();
                      // initialize the lcd 

  blinkingLedIntro();
  intro(); // Show Intro of our Project on LCD 

	
}

void loop() {
  int pushButton_1 = digitalRead(5);
  int pushButton_2 = digitalRead(6);
  int pushButton_3 = digitalRead(7);
  // Serial.println(pushButton_1);
  // Serial.println(pushButton_2);
  // Serial.println(pushButton_3);
  if(pushButton_1==LOW){
    digitalWrite(2,HIGH);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Read Mode");
    lcd.setCursor(2,1);
    lcd.print("Tap Your Card");

    beepSound(1000);



    mode = 'R';
    
  }else if(pushButton_2 == LOW){
    digitalWrite(2,LOW);
    digitalWrite(3,HIGH);
    digitalWrite(4,LOW);
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Verify Mode");
    lcd.setCursor(2,1);
    lcd.print("Tap Your Card");
    beepSound(1000);

    mode = 'V';
  }else if (pushButton_3 == LOW){
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,HIGH);
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Write Mode");
    lcd.setCursor(1,1);
    lcd.print("Hold Your Card");
    beepSound(1000);
    
    mode = 'W';
  }
  switch (mode) {
    case 'R':
    // Serial.println(F("Read Mode"));
    readMode();
    uid = getUID();
    break;
    case 'W':
      // Serial.println(F("UID Write Mode"));
      writeMode();
      break;
    case 'V':
      // Serial.println(F("Verify Mode"));
      verifyMode();
    break;
    default:
      break;

  }


}



String getUID() {
  String uid = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10) uid += "0";
    uid += String(mfrc522.uid.uidByte[i], HEX);
  }
  uid.toUpperCase(); // optional
  return uid;
}



void intro(){

  lcd.createChar(0, loveChar);
  lcd.createChar(1, customChar);

		//INTRO 
	lcd.setCursor(0,0);
  lcd.print(char(0));
  lcd.print("Hello, Hackers");
  lcd.print(char(0));
  delay(3000);
  lcd.setCursor(2, 1);
  lcd.print(char(1));
  lcd.print("RFID CLONER");
  lcd.print(char(1));
  delay(3000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Brainware");
  lcd.setCursor(6,1);
  lcd.print("University");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Depertment-> CST");
  lcd.setCursor(0, 1);
  lcd.print("BSc.(Hnrs.)-ANCS");
  delay(3000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Subject: Project");
  lcd.setCursor(0, 1);
  lcd.print("Code: BNC58001");
  delay(3000);
  lcd.clear();


  lcd.setCursor(0, 0);
  lcd.print("Project Guidence");
  lcd.setCursor(0, 1);
  lcd.print("Sampat Banerjee");
  delay(3000);
  lcd.clear();

  lcd.setCursor(2, 0);
  lcd.print("Team Members");
  delay(3000);
  lcd.clear();

  lcd.setCursor(1, 0);
  lcd.print("1.Amit");
  lcd.setCursor(7, 1);
  lcd.print("2.Arpan");
  delay(3000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("3.Adrija");  
  lcd.setCursor(6, 1);
  lcd.print("4.Subhadip");
  delay(3000);
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print("-:Select Modes:-");
	lcd.setCursor(0, 1);
	lcd.print("Read/Verify/Write");

}


void blinkingLedIntro(){
  for(int i =0;i<11;i++){
  digitalWrite(2,HIGH);
  delay(250);
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
  delay(250);
  digitalWrite(3,LOW);
  digitalWrite(4,HIGH);
  delay(250);
  digitalWrite(4,LOW);
  digitalWrite(8,HIGH);
  delay(500);
  digitalWrite(8,LOW);




  }


}
void readMode(){
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks...(HOLD YOU CARD 7 SEC....)"));
  String uid = getUID();
  // Serial.println("Card UID: " + uid);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("UID:");
  lcd.setCursor(0,1);
  lcd.print(uid);
	
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
}
}

void writeMode(){
   // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle. And if present, select one.
  if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
    delay(50);
    return;
  }
  
  // Now a card is selected. The UID and SAK is in mfrc522.uid.
  
  // Dump UID
  Digital.write(8,HIGH);
  Serial.print(F("Card UID:"));
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  } 


  // Dump PICC type
//  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
//  Serial.print(F("PICC type: "));
//  Serial.print(mfrc522.PICC_GetTypeName(piccType));
//  Serial.print(F(" (SAK "));
//  Serial.print(mfrc522.uid.sak);
//  Serial.print(")\r\n");
//  if (  piccType != MFRC522::PICC_TYPE_MIFARE_MINI 
//    &&  piccType != MFRC522::PICC_TYPE_MIFARE_1K
//    &&  piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
//    Serial.println(F("This sample only works with MIFARE Classic cards."));
//    return;
//  }
  
  // Set new UID
  stringToUidArray(uid,NEW_UID,uidLength);
  if ( mfrc522.MIFARE_SetUid(NEW_UID, (byte)4, true) ) {
    Serial.println(F("Wrote new UID to card."));
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.write("Wrote new UID ");
    lcd.setCursor(0, 1);
    lcd.write("to card......");
  }
  
  // Halt PICC and re-select it so DumpToSerial doesn't get confused
  mfrc522.PICC_HaltA();
  if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
    return;
  }
  
  // Dump the new memory contents
  Serial.println(F("New UID and contents:"));
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("New UID:");
    String uid = getUID();
    lcd.print(uid);
    lcd.setCursor(0, 1);
    lcd.print("Wait 7 Sec.....");

  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  
  delay(5000);
  Digital.write(8,LOW);

}

// Convert UID string into byte array
void stringToUidArray(String uidString, byte *uidArray, int &length) {
  length = uidString.length() / 2;   // 2 hex chars = 1 byte
  for (int i = 0; i < length; i++) {
    String byteStr = uidString.substring(i * 2, i * 2 + 2);
    uidArray[i] = (byte) strtol(byteStr.c_str(), NULL, 16);
  }
}

void beepSound(int ms){
  digitalWrite(8,HIGH);
  delay(ms);
  digitalWrite(8,LOW);
}


void verifyMode(){
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
  String uid = getUID();
  Serial.println("Card UID: " + uid);
  if(isAuthorizedUID(uid)){
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("Authorized");
      lcd.setCursor(0, 1);
      lcd.print("Card ID:"+uid);
    beepSound(1000);
    digitalWrite(2,HIGH);
    delay(3000);
    digitalWrite(2,LOW);
  }else{
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Unauthorized");
      lcd.setCursor(0, 1);
      lcd.print("Card ID:"+uid);
      for(int i=0 ;i<17;i++){
      beepSound(70);
      digitalWrite(4,HIGH);
      delay(70);
      digitalWrite(4,LOW);
      delay(70);
      
      }
      delay(3000);



  }

  }
}

bool isAuthorizedUID(String input) {
  for (int i = 0; i < authorizedUIDListSize; i++) {
    if (input == authorizedUIDList[i]) {  // String class supports ==
      return true;
    }
  }
  return false;
}




