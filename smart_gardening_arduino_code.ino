#include <SoftwareSerial.h>
#include <dht.h>
#define DHT_PIN 11
#define DHTTYPE DHT11
SoftwareSerial mySerial(2, 3);

dht DHT;

const int led = 13;
String statusLed = "OFF";
int sensorPin = A0;
int sensorValue;
const int ldr_pin = 7;
const int relay = A5;

String data = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin (115200);
  mySerial.begin (115200);
  DHT.read11(DHT_PIN);
  pinMode(led, OUTPUT);
  pinMode(led,LOW);
  pinMode(relay, OUTPUT);
  digitalWrite(relay,HIGH);

}

void loop() {
  int value =  analogRead(soundPin);
    Serial.println(value);//print the value 
  delay(50); 
  int m = analogRead(sensorPin);
  m = map(m, 1023, 165, 0, 100);
  int h = DHT.humidity;
  int t = DHT.temperature;

  if( digitalRead( ldr_pin ) == 1){
      digitalWrite( led_pin,HIGH);
   }
   else{
      digitalWrite( led_pin , LOW);
   }
   
   Serial.println( digitalRead( ldr_pin ));
   delay(100);
}
  // put your main code here, to run repeatedly:
  while (mySerial.available() > 0) {
    char c = mySerial.read();
    data += c;
  }

  if (data.length() > 0) {
    Serial.println("Data Inputted :" + data);

    if (data == "LAMP ON") {
      digitalWrite(led,HIGH);
      mySerial.print("LAMP is ON");
    }
    else if(data == "LAMP OFF") {
      digitalWrite(led,LOW);
      mySerial.print("LAMP is OFF");
    }
    else if(data == "TEMPERATURE") {
      mySerial.print ("TEMPERATURE: " + String(t));
    }
    else if(data == "HUMIDITY") {
      mySerial.print ("HUMIDITY: " + String(h) + "%");
    }
     else if(data == "MOISTURE") {
      mySerial.print ("MOISTURE: " + String(m) + "%");
    }
    else if (data == "WATERPUMP ON"){
      digitalWrite(relay, LOW);
      delay (5000);
      digitalWrite(relay,HIGH);
      mySerial.print ("WATERPUMP IS ON FOR 5 SECONDS");
    }
    else if(data == "STATUS") {
      mySerial.print(String("LED Condition: " + statusLed + '#'
                            + "TEMPERATURE: " + t + '#'
                            + "HUMIDITY: " + h + '#'
                            + "MOISTURE: " + m));
    }
    
    data = "";
  }

}
