// Подключение библиотек
#include <SPI.h>
#include <MFRC522.h>
#include "pitches.h"
#include <TroykaDHT.h>
// создаём объект класса DHT
// передаём номер пина к которому подключён датчик и тип датчика
// типы сенсоров: DHT11, DHT21, DHT22

#include <Servo.h>


#define RST_PIN 8
#define SS_PIN 9
#define humS 6
#define LED 7
#define gasS A0
DHT dht(4, DHT11);
// Инициализация MFRC522
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
// константы подключения контактов SS и RST
// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

int signalization[] = {
  NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4
};

byte accessCard[4] = {134, 29,  163, 185};
boolean isValid = false;

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};
int humSValue = 0;
int gasSValue = 0;

void setup()
{
Serial.begin(9600); // инициализация последовательного порта
SPI.begin(); // инициализация SPI
mfrc522.PCD_Init(); // инициализация MFRC522
myservo.attach(11);  // attaches the servo on pin 11 to the servo object
pinMode(LED, OUTPUT);
pinMode(humS, INPUT);
dht.begin();
pinMode(gasS, INPUT);

}
void loop()
{

  readTempHumData();
  //dht.getHumidity();
  humSValue = 0;

if ( ! mfrc522.PICC_IsNewCardPresent())
return;
// чтение карты
if ( ! mfrc522.PICC_ReadCardSerial())
return;
// показать результат чтения UID и тип метки
Serial.print(F("Card UID:"));
dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
if(isValid == true){

  activateSound(melody);
    Serial.print("1:");
    Serial.println(humSValue);
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

  turnLights();
  
//  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
//    myservo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15ms for the servo to reach the position
//  }
}
digitalWrite(LED, LOW);

Serial.println();
Serial.print(F("PICC type: "));
byte piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
Serial.println(mfrc522.PICC_GetTypeName(piccType));


delay(2000);
}
// Вывод результата чтения данных в HEX-виде
void dump_byte_array(byte *buffer, byte bufferSize)
{
  int count=0;
for (byte i = 0; i < bufferSize; i++)
{
if(buffer[i] == accessCard[i]){
  count++;
  isValid = true;
  //i--;
}else{
  isValid = false;
  count = 0;
}

Serial.print(buffer[i] < 0x10 ? " 0" : " ");
Serial.print(buffer[i], HEX);

if(count == 4 && isValid == true){
  return;
}


//byte accessCard = buffer
}


}

void activateSound(int sound[]){
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(10, sound[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(10);
}

void readTempHumData(){
  dht.read();
  switch(dht.getState()) {
    // всё OK
    case DHT_OK:
      // выводим показания влажности и температуры
      
      Serial.print("Temperature = ");
      Serial.print(dht.getTemperatureC());
      Serial.println(" C \t");
      
      Serial.print("Humidity = ");
      Serial.print(dht.getHumidity());
      Serial.println(" %");
      
      if(dht.getTemperatureC() == 30 || dht.getHumidity() == 70){
        activateSound(signalization);
      }
      break;
    // ошибка контрольной суммы
    case DHT_ERROR_CHECKSUM:
      Serial.println("Checksum error");
      break;
    // превышение времени ожидания
    case DHT_ERROR_TIMEOUT:
      Serial.println("Time out error");
      break;
    // данных нет, датчик не реагирует или отсутствует
    case DHT_ERROR_NO_REPLY:
      Serial.println("Sensor not connected");
      break;
  }
  delay(200);
}

void turnLights(){
  humSValue = digitalRead(humS);
  Serial.print("2:");
  Serial.println(humSValue);
  if(humSValue == 1){
    digitalWrite(LED, HIGH);
    delay(1000);
  }else{
    digitalWrite(LED, LOW);
  }
}
}

