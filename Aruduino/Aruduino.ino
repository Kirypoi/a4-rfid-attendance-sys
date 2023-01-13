#include <SPI.h>
#include <MFRC522.h>
#include "SoftwareSerial.h"
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
SoftwareSerial ser(2,3); // RX, TX 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  ser.begin (115200);
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Put RFID Card to Scan...");
  Serial.println();

  //Setup LED Pin
  pinMode(13, OUTPUT);
 
}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) // 
  {
    return;
  }
  
  // If there is a card, read its serial
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  { 
    // Display card id
    // unsigned long uid = getID();
    // if(uid !== 0){
    // Serial.print("Card detected, UID: "); Serial.println(uid);

    digitalWrite(13, HIGH); 
    return;
  }
  //
  digitalWrite(13, HIGH);
  //Show UID on serial monitor
  String content= "";
  byte letter;
  // Check card validity
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  // If card is valid, display
  Serial.println();
  Serial.print("User No./Name:    ");
  content.toUpperCase();

  // UID & info of cards with access ---- to register the cards
  if (content.substring(1) == "E9 9C B0 E3" ) //UID --- Please change to whatever id the physical tag carries -- if dont know use getID()
  {
    Serial.println("1-Mejiro McQueen");
    ser.write(1);
    Serial.println();
    
    delay(3000);
  }
   if (content.substring(1) ==  "01 15 C9 1F" ) //UID --- Please change to whatever id the physical tag carries
  {
    Serial.println("2-Satono Diamond ");
    ser.write(2);
    Serial.println();
    
    delay(3000);
  }
}

void pinFlash(){
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100);
}

// To get card id in case not knowtt
unsigned long getID(){
  if ( ! mfrc522.PICC_ReadCardSerial()) { //Since a PICC placed get Serial and continue
    return 0;
  }
  unsigned long hex_num;
  hex_num =  mfrc522.uid.uidByte[0] << 24;
  hex_num += mfrc522.uid.uidByte[1] << 16;
  hex_num += mfrc522.uid.uidByte[2] <<  8;
  hex_num += mfrc522.uid.uidByte[3];
  mfrc522.PICC_HaltA(); // Stop reading
  return hex_num;
}


