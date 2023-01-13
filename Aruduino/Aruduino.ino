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
  
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    digitalWrite(13, LOW);
    return;
  }
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

  // UID & info of cards with access ---- to sub these info to the card with the id
  if (content.substring(1) == "E9 9C B0 E3" ) //UID --- Please change to whatever id the physical tag carries
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

