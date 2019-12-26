/*
 * Created by K. Suwatchai (Mobizt)
 * 
 * Email: k_suwatchai@hotmail.com
 * 
 * Github: https://github.com/mobizt
 * 
 * Copyright (c) 2019 mobizt
 * 
 * This example is for FirebaseESP8266 Arduino library v 2.6.0 and later
 *
*/


//This example shows how to read and write database rules

//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include <SoftwareSerial.h>
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <Servo.h>

#define WIFI_SSID "ishzark"
#define WIFI_PASSWORD "1234567890"
#define FIREBASE_HOST "myclasswebsite-3eca2.firebaseio.com" 
#define FIREBASE_AUTH "LqIDz7Mh22syKqKtThQZZtlvgIMD1BVwXQIlRWoo"

//Define Firebase Data object
FirebaseData firebaseData;
FirebaseJson json;
QueryFilter query;
Servo servo;

String datanya;
int deg = 0;
int data;
int pos; 
const int white = D1;
const int green = D8;
const int red = D7;
const int button = D5;

void setup() {
  Serial.begin(115200);
  servo.attach(D6);
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(white, OUTPUT);
  pinMode(button, INPUT_PULLUP);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

}

void loop() {

  data = digitalRead(button);
  if( data == 1 ) {
    naikDeg();  
  } else {
    turunDeg();  
  }
  while(Serial.available() > 0){  
    datanya = Serial.readStringUntil('\n');
    datanya.trim();
    Serial.print("Dari Arduino : " + datanya);
    kirimData(datanya);   
  }
  delay(2000);
}

void kirimData(String idNFC ) {
  
  if (Firebase.getJSON(firebaseData, "/Users/" + idNFC, query))
{
  //Success, then try to read the JSON payload value
  Serial.println(firebaseData.jsonString());
  json.set("Status", "Dikenali");
  json.set("IdNFC", idNFC);
  
  if(Firebase.pushJSON(firebaseData, "/Log/", json)) {
    Serial.println("Log Berhasil");  
  } else {
      Serial.println("Log Gagal");  
  }
  portal();
  
} else {
  //Failed to get JSON data at defined database path, print out the error reason
  Serial.println(firebaseData.errorReason());
  if(firebaseData.errorReason() == "path not exist") {
    json.set("IdNFC", idNFC);
    json.set("Status", "Tidak Dikenali");
    
    if(Firebase.pushJSON(firebaseData, "/Log/", json)) {
      Serial.println("Log Berhasil");
    } else {
      Serial.println("Log Gagal");  
    }
    digitalWrite(red, HIGH);
    delay(3000);
    digitalWrite(red, LOW);
  }
}

//Clear all query parameters
query.clear();
  
}

void turunDeg() {
  digitalWrite(white, LOW);
  for (deg ; deg < 90; deg++) {
  servo.write(deg);
  delay(15);
  }  
}

void naikDeg() {
  digitalWrite(white, HIGH);
  for (deg; deg >= 1; deg--) {
  servo.write(deg);
  delay(15);
  }  
}

void turun() {
  for (pos = 0; pos < 90; pos ++) {
  servo.write(pos);
  delay(15);
  }
}

void naik() {
  digitalWrite(green, HIGH);
  for (pos = 90; pos >= 1; pos --) {
  servo.write(pos);
  delay(15);
  }
}

void portal() {
  naik();
  delay(5000);
  digitalWrite(green, LOW);
  turun();
}
