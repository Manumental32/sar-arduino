
// Sensor YL-69
// https://www.youtube.com/watch?v=ppvKm-5BG-0

#include "DHT.h"

#define DHTTYPE DHT11   // DHT 11
// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

//const analog input ports
const int HUMIDITY_SENSOR_INPUT = A0;
const int LIGHT_SENSOR_INPUT = A1; //conectar a 3.3 volts el positivo
const int DHTPin = 3;     // temperatura y humedad ambiente, medidor analógico al lado del positivo (3 de la derecha), what digital pin we're connected to

DHT dht(DHTPin, DHTTYPE);

//const digital output ports
const int LIGHT_FLAG_MOTOR_TURN_ON = 2; //se enciende cuando debería regar (suelo seco)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LIGHT_FLAG_MOTOR_TURN_ON, OUTPUT);
  dht.begin();
}

void loop() {
  //delay(1000); //recomendado para el dht 2 seg
  
  digitalWrite(LIGHT_FLAG_MOTOR_TURN_ON, LOW); // Set the initial state of the LEDs to OFF

  int currentHumidity = analogRead(HUMIDITY_SENSOR_INPUT);
  int currentLight = analogRead(LIGHT_SENSOR_INPUT);

  float h = dht.readHumidity();
  float t = dht.readTemperature(); //en ºC
 
   if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
   }
   
  //Serial.print("DHT Humidity: ");
  //Serial.print(h);
  //Serial.println(" %\t");
  Serial.print("DHT Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");

  //Serial.print("La currentHumidity es: ");
  //Serial.println(currentHumidity);
  
  Serial.print("La currentLight es: ");
  Serial.println(currentLight);

  // currentHumiditys entre 1000 - 1023
//  if (currentHumidity >= 1000){
//    Serial.println(">> EL SENSOR ESTA DECONECTADO O FUERA DEL SUELO <<");
//  }
//  else if (currentHumidity <1000 && currentHumidity >= 600){
//    Serial.println(">> EL SUELO ESTA SECO <<");
//    //digitalWrite(LIGHT_FLAG_MOTOR_TURN_ON, HIGH); //led on
//  }
//  else if (currentHumidity < 600 && currentHumidity >= 370){
//    Serial.println(">> EL SUELO ESTA HUMEDO <<");
//  }
//  else if (currentHumidity < 370){
//    Serial.println(">> EL SENSOR ESTA PRACTICAMENTE EN AGUA <<");
//  }
  delay(2000);

  int currentHumidityPorcentaje = map(currentHumidity, 1023, 0, 0, 100); //Convirtiendo a Porcentaje

  Serial.print("La Humedad es del: ");
  Serial.print(currentHumidityPorcentaje);
  Serial.println("%");
  

  //int currentLightPorcentaje = map(currentLight, 0, 666, 0, 100); //Convirtiendo a Porcentaje

  //Serial.print("La Luminosidad es del: ");
  //Serial.print(currentLightPorcentaje);
  //Serial.println("%");

  //int currentTemperaturePorcentaje = map(currentTemperature, 0, 666, 0, 100); //Convirtiendo a Porcentaje

  //Serial.print("La Temperature es del: ");
  //Serial.print(currentTemperaturePorcentaje);
  //Serial.println("%");
}
