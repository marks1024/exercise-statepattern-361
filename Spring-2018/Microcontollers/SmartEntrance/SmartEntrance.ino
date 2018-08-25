// Подключение библиотек
#include <SPI.h>
#include <MFRC522.h>
#include "pitches.h"
#include <TroykaDHT.h>
// create an object of class DHT
// передаём номер пина к которому подключён датчик и тип датчика
// sensor types: DHT11, DHT21, DHT22

#include <Servo.h>

#define RST_PIN 8
#define SS_PIN 9
#define humS 6
#define LED 7
#define SERV 11
#define gasS A0
#define pin1 45
#define pin2 44
#define pin3 43

DHT dht(4, DHT11);
// Initialization of MFRC522
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.

byte accessCard[4] = {134, 29,  163, 185}; //valid access card
boolean isValid = false;

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
int pos = 0;    // variable to store the servo position

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
}; // for opening the homeentrance door

int signalization[] = {
  NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4
}; //for alarm due to fire, flooding, or excess of gas

int door[] = {
  NOTE_A3, NOTE_C4, NOTE_B3, NOTE_E3, NOTE_G3, NOTE_E3, NOTE_A3, NOTE_C3
}; //for opening the door to the apartments

int burglar[] = {
  NOTE_B2, NOTE_B2, NOTE_B2, NOTE_B2, NOTE_B2, NOTE_B2, NOTE_B2, NOTE_B2
}; //when the password was entered incorrectly 3 times

int pins[8] = {22, 23 ,24, 25, 26, 27, 28, 29}; // pins for 7Segment legs

int A[10][8] = { //to numbers decoding
  {0, 0, 0, 0, 0, 0, 1, 1},
  {1, 0, 0, 1, 1, 1, 1, 1},
  {0, 0, 1, 0, 0, 1, 0, 1},
  {0, 0, 0, 0, 1, 1, 0, 1},
  {1, 0, 0, 1, 1, 0, 0, 1},
  {0, 1, 0, 0, 1, 0, 0, 1},
  {0, 1, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 1, 1, 1, 1, 1},
  {0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 1, 0, 0, 1},
  };

    int pin1Value;
    int pin2Value;
    int pin3Value;
    int number[4] = {0, 0, 0, 0 };
    int current[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int password[4] = {1, 2, 3, 4};
    int currentn;
    int count;
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};
int humSValue = 0;
int gasSValue = 4;

void setup()
{
Serial.begin(9600); // инициализация последовательного порта
SPI.begin(); // инициализация SPI
mfrc522.PCD_Init(); // инициализация MFRC522
myservo.attach(SERV);  // attaches the servo on pin 11 to the servo object
pinMode(LED, OUTPUT);
pinMode(humS, INPUT);
dht.begin();
pinMode(gasS, INPUT);
  for(int i = 0; i < 8; i++){
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], HIGH); //7-segment is turmed off
  }
  
  pinMode(pin1, INPUT);
   pinMode(pin2, INPUT);
   pinMode(pin3, INPUT);
}

void loop()
{
  humSValue = 0;

if ( ! mfrc522.PICC_IsNewCardPresent())
return;
// reading the card
if ( ! mfrc522.PICC_ReadCardSerial())
return;
// show the result of reading UID and the type
Serial.print(F("Card UID:"));
dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);

Serial.println();
Serial.print(F("PICC type: "));
byte piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
Serial.println(mfrc522.PICC_GetTypeName(piccType));
  
if(isValid == true){


  activateSound(melody);
  openDoor();

  readGasValue();
  readTempHumData();
  
  turnLights();
  

  writeDigit(0);

  
  currentn=0;
  count=0;
  
  enterPassword(currentn, count);


}
readGasValue();
readTempHumData();
digitalWrite(LED, LOW); // turn off the light after entering the apartment
delay(2000);
}


//print the results in hexadecimal notation.
void dump_byte_array(byte *buffer, byte bufferSize)  
{
  int count=0;

    /*Check if the RFID key is valid for the door*/
  for (byte i = 0; i < bufferSize; i++){
      if(buffer[i] == accessCard[i]){
      count++;
      isValid = true;
  }else{
      isValid = false;
      count = 0;
  }

  Serial.print(buffer[i] < 0x10 ? " 0" : " ");
  Serial.print(buffer[i], HEX);

  if(count == 4 && isValid == true){
      return;
   }
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
}

void openDoor(){
  /* Servo motor opens the door rotating through 180 degrees.*/
  int i = 1;
    while(i > 0.5){
      for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
   }
  i--;
 }

}

void readTempHumData(){
  for(int i = 0; i < 100; i++){
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
     
      if(dht.getTemperatureC() >= 34 || dht.getHumidity() >= 40){
        activateSound(signalization);
        return;
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
 
}

void turnLights(){
  /*Turn the light when a person enters building*/
  do{
    humSValue = digitalRead(humS);
    Serial.print("HumS:");
  Serial.println(humSValue);
  }while(humSValue!=1);
  Serial.println(humSValue);
  if(humSValue == 1){
    digitalWrite(LED, HIGH);
    delay(1000);
  }else{
    digitalWrite(LED, LOW);
  }
}

void enterPassword(int currentn, int count){
    int wrongCount = 0;
      while(count!=4){
    do {
      pin1Value = digitalRead(pin1); //increment button
      pin2Value = digitalRead(pin2); //enter button
      pin3Value =digitalRead(pin3); //decrement button
      delay(200);
      
    }
    while(!(pin1Value || pin2Value || pin3Value)); // read until one of the buttons is pressed
//    
    
    if(pin1Value){ // if the last element on the 7 segment Display was 9 then count starts from zero for incrementor
      if(currentn==0){
        writeDigit(9);
        currentn=9;
      }
      
      else {
        writeDigit(currentn-1); 
        currentn--;
      }
    }
    else if(pin3Value){ //if the last element on the 7 segment Display was 0 then count sets to 9 for deccrementor
      if(currentn==9){
        writeDigit(0);
        currentn=0;
      }
      
      else {
        writeDigit(currentn+1);
        currentn++;
      }
    }
    else { 
      
      number[count] = currentn; //stores entered password digit by digit
      Serial.println(number[count]);
      Serial.println(count);
      count++;
      writeDigit(0);
      currentn=0;
    }

    if(count == 4){
      int correct=1;
for(int k=0; k<4; k++){
  if(password[k]!=number[k]){
    Serial.println("wrong");
    
    correct = 0;
    count = 0;
  }
}
if(correct){
  Serial.println("CORRECT!");
  activateSound(door);
}else{
  activateSound(burglar);
    wrongCount++;
    if(wrongCount == 3){
      for(int i = 0; i < 8; i++){
      digitalWrite(pins[i], HIGH);
  }
      delay(10000);
        for(int i = 0; i < 8; i++){
      digitalWrite(pins[i], LOW);
  }
    }
}
    }

  
}

}
void readGasValue(){
  Serial.print("Gas sensor: ");
  gasSValue = analogRead(gasS);
  Serial.println(gasSValue);
  if(gasSValue > 590){
    activateSound(signalization); //activate signalization when the value read by gas sensor exceeds 500
  }
}

  
void writeDigit(int x){
  for(int k=0; k< 8; k++){
     digitalWrite(pins[k], A[x][k]);
  
  }
  delay(100);
}
