#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PN532.h>

// If using the breakout with SPI, define the pins for SPI communication.
#define PN532_SCK  (6)
#define PN532_MOSI (7)
#define PN532_SS   (8)
#define PN532_MISO (9)

// If using the breakout or shield with I2C, define just the pins connected
#define PN532_IRQ   (6)
#define PN532_RESET (7)  // Not connected by default on the NFC Shield

// Uncomment just _one_ line below depending on how your breakout or shield
// is connected to the Arduino:

// Use this line for a breakout with a software SPI connection (recommended):
Adafruit_PN532 nfc(PN532_SCK, PN532_MISO, PN532_MOSI, PN532_SS);

#if defined(ARDUINO_ARCH_SAMD)
// also change #define in Adafruit_PN532.cpp library file
   #define Serial SerialUSB
#endif

// Communication
const int led = 12;

void setup(void) {
  #ifndef ESP8266
    while (!Serial); // for Leonardo/Micro/Zero
  #endif

  Serial.begin(115200);
  
  pinMode(led, OUTPUT);

  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("Tidak Ditemukan");
    while (1); // halt
  }
  // configure board to read RFID tags
  nfc.SAMConfig();
  
}


void loop(void) {
  // Check the Communication
  
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        
    
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  String idNFC = "";
  if (success) {

    for(int i=0; i<uidLength  ; i++){
      idNFC += String(uid[i], HEX);
      if(i < uidLength-1){
        idNFC += ":";
      }
    }
    Serial.println(idNFC);
    
  }
  
}
