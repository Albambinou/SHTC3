/**************************************************************************
 * Nom du Programme      : SHTC3.ino
 * Auteur                : Alban de Farcy de Pontfarcy
 * Date de création      : 11/12/2024
 * Dernière modification : 12/12/2024
 * Version               : 1.2
 * Description           :
 *   Ce programme a pour but de faire fontionner le capteur SHTC3, et d'afficher la température et l'humiditée relevée
 *
 * Pré-requis            :
 * Installer la bibliothèque Wire.h
 *
 * Copyright             :
 *   © 2024 Alban de Farcy de Pontfarcy
 **************************************************************************/

#include <Wire.h>
#define Addr 0x70

float puissance = pow(2, 16);



void setup() {
  Serial.begin(9600);
  Serial.println("///////////////");
  Serial.println("/////SHTC3/////");
  Serial.println("///////////////");
  Serial.println();
  delay(1000);
  Wire.begin();

  Wire.beginTransmission(Addr);
  Wire.write(0x80);
  Wire.write(0x5D);
   Wire.endTransmission();

  Serial.println("Allumage du capteur");

  Wire.beginTransmission(Addr);
  Wire.write(0x35);
  Wire.write(0x17);
  int error = Wire.endTransmission();

  if(error != 0){
    Serial.println("Je n'ait pas réussis à communiquer avec le capteur.");
  } else {
    Serial.println("Communication réussis");
  }
  delay(2000);
  Wire.beginTransmission(Addr);
  Wire.write(0x7C);
  Wire.write(0xA2);
  Wire.endTransmission();
  delay(2000);
  
}

void loop() {

  Wire.beginTransmission(Addr);
  Wire.write(0x35);
  Wire.write(0x17);
  Wire.endTransmission();
  delay(1000);
  Wire.beginTransmission(Addr);
  Wire.write(0x7C);
  Wire.write(0xA2);
  Wire.endTransmission();
  delay(1000);

  
  Wire.requestFrom(Addr, 6);
  Serial.print("Octets en attente de lecture: ");
  Serial.println(Wire.available());
  int T_MSB = Wire.read();
  int T_LSB = Wire.read();
  int checksum1 = Wire.read();
  int H_MSB = Wire.read();
  int H_LSB = Wire.read();
  int checksum2 = Wire.read();

  Serial.println("Affichage des données de températures brute : ");
  Serial.print("T_MSB : ");
  Serial.println(T_MSB, BIN); 
  Serial.print("T_LSB : ");
  Serial.println(T_LSB, BIN); 

  Serial.println("Affichage des données d'humidité brute : ");
  Serial.print("H_MSB : ");
  Serial.println(H_MSB, BIN); 
  Serial.print("H_LSB : ");
  Serial.println(H_LSB, BIN); 
  
  float Temp = (T_MSB*255) + T_LSB;
  Temp = -45 + 175 * (Temp/puissance);

  float Hum = (H_MSB*255) + H_LSB;
  Hum = 100 * (Hum/puissance);
  Hum = 100 + Hum;

  Serial.println();
  Serial.print("Température convertie : ");
  Serial.println(Temp);
  Serial.println();
  Serial.print("Humidité convertie : ");
  Serial.println(Hum);
  Serial.println();


  Wire.beginTransmission(Addr);
  Wire.write(0xB0);
  Wire.write(0x98);
  Wire.endTransmission();
 

  delay(2000);

  
}
