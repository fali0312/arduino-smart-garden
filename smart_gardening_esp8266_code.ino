/*
Name:        lightBot.ino
Created:     17/01/2018
Author:      Stefano Ledda <shurillu@tiscalinet.it>
Description: a simple example that do:
             1) parse incoming messages
             2) if "LIGHT ON" message is received, turn on the onboard LED
             3) if "LIGHT OFF" message is received, turn off the onboard LED
             4) otherwise, reply to sender with a welcome message

*/
#include "CTBot.h"
CTBot myBot;

String ssid = "Hape Fali";     // REPLACE mySSID WITH YOUR WIFI SSID
String pass = "pokemon123"; // REPLACE myPassword YOUR WIFI PASSWORD, IF ANY
String token = "1493879064:AAGtUtSGpHXFtYyQDKWGK4jmE5U1wOyNXWE";   // REPLACE myToken WITH YOUR TELEGRAM BOT TOKEN

String data = "";
String arrayData[9];


void setup() {
  // initialize the Serial
  Serial.begin(115200);

  // connect the ESP8266 to the desired access point
  myBot.wifiConnect(ssid, pass);

  // set the telegram bot token
  myBot.setTelegramToken(token);

  // check if all things are ok
  if (myBot.testConnection())
    Serial.println("\ntestConnection OK");
  else
    Serial.println("\ntestConnection NOK");

}

void loop() {
  // a variable to store telegram message data
  TBMessage msg;

  // if there is an incoming message...
  if (myBot.getNewMessage(msg)) {

    if (msg.text.equalsIgnoreCase("LAMP ON")) {              // if the received message is "LIGHT ON"...
      Serial.print ("LAMP ON");
    }
    else if (msg.text.equalsIgnoreCase("LAMP OFF")) {        // if the received message is "LIGHT OFF"...
      Serial.print ("LAMP OFF");
    }
    else if (msg.text.equalsIgnoreCase("TEMPERATURE")) {
      Serial.print ("TEMPERATURE");
    }
    else if (msg.text.equalsIgnoreCase("HUMIDITY")) {
      Serial.print ("HUMIDITY");
    }
     else if (msg.text.equalsIgnoreCase("MOISTURE")) {
      Serial.print ("MOISTURE");
    }
    else if (msg.text.equalsIgnoreCase("WATERPUMP ON")){
      Serial.print ("WATERPUMP ON");
    }     
    else if (msg.text.equalsIgnoreCase("STATUS")) {
      Serial.print ("STATUS");
    }
    else {                                                    // otherwise...
      // generate the message for the sender
      String reply;
      reply = (String)"Welcome " + msg.sender.username + (String)". The commands are : LAMP ON, LAMP OFF, TEMPERATURE, HUMIDITY, MOISTURE, WATERPUMP ON. ";
      myBot.sendMessage(msg.sender.id, reply);             // and send it
    }
  }
  
 while (Serial.available() > 0 ) {
  char c = Serial.read();
  data += c;
 } 
 
 if (data.length () > 15){
  int index = 0;
  for (int i = 0; i < data.length(); i++){
    char delimiter = '#';
    if (data[i] !=delimiter) {
    arrayData[index] += data[i];
    }
    else {
    index++; 
    }
   }

   if (index == 9){
    myBot.sendMessage(msg.sender.id,arrayData[0] + "\n" + arrayData[1] + "\n" + arrayData[2] + "\n" + arrayData[3] + "\n" + arrayData [4] + "\n" + arrayData[5] + "\n" + arrayData[6] + "\n" + arrayData[7] + "\n" + arrayData[8]);
 }
    arrayData[0] = "";
    arrayData[1] = "";
    arrayData[2] = "";
    arrayData[3] = "";
    arrayData[4] = "";
    arrayData[5] = "";
    arrayData[6] = "";
    arrayData[7] = "";
    arrayData[8] = "";



    data = ""; 
    }  
  else{
    myBot.sendMessage(msg.sender.id,data);
    data = "";

  }

}
