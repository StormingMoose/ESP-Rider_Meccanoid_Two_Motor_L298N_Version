/*  This version of ESP-Rider software uses the software developed by Alex Frederiksen
    to control the Meccanoid Servo and thus the steering of the chassis.
*/

#include <Meccanoid.h>  // https://github.com/alexfrederiksen/MeccanoidForArduino 
#include <WiFi.h>
#include <WebServer.h>
#include "index.h"  //Web page header file

int chainpin = 27;
int point = 90;

Chain chain(chainpin);
MeccanoServo servo1 = chain.getServo(0); // servo with id 0
MeccanoLed led =      chain.getLed(2);   // led with id 2

int MOTOR_PWM_A = 18;//  Speed  Enable Pin
int MOTOR_DIR_A = 5; //  Direction
int MOTOR_DIR1_A = 19;//  Direction
int MOTOR_PWM_B = 23 ;//  Speed  Enable Pin
int MOTOR_DIR_B = 22; //  Direction
int MOTOR_DIR1_B = 21;//  Direction

// the actual values for "fast" and "slow" depend on the motor

#define PWM_STOP 0
#define PWM_SLOW 155 // arbitrary slow speed PWM duty cycle
#define PWM_FAST 255 // arbitrary fast speed PWM duty cycle

const int freq = 5000;
const int resolution = 8;
const int ledChannel_PWM_A = 10;
const int ledChannel_PWM_B = 11;

//Enter your desired WiFi SSID and PASSWORD 
const char* ssid = "ESP_Rider_Big_Chassis";
const char* password = "********";

WebServer server(80);

//===============================================================
// Setup
//===============================================================
void setup() {

  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting Sketch...");

  pinMode(MOTOR_PWM_A, OUTPUT);
  pinMode(MOTOR_DIR_A, OUTPUT);
  pinMode(MOTOR_DIR1_A, OUTPUT);
  pinMode(MOTOR_PWM_B, OUTPUT);
  pinMode(MOTOR_DIR_B, OUTPUT);
  pinMode(MOTOR_DIR1_B, OUTPUT);

  for (int i=1; i<20; ++i){chain.update();}
  if (servo1.isConnected()) {
       servo1.setColor(0, 1, 0)
            .setPosition(90);
      chain.update();
  }
  
  ledcSetup(ledChannel_PWM_A, freq, resolution);
  ledcSetup(ledChannel_PWM_B, freq, resolution);
 
  ledcAttachPin(MOTOR_PWM_A, ledChannel_PWM_A);
  ledcAttachPin(MOTOR_PWM_B, ledChannel_PWM_B);

  WiFi.mode(WIFI_AP); //Access Point mode
  WiFi.softAP(ssid, password);    //Password length minimum 8 char

  server.on("/", handle_OnConnect);
  server.on("/A", handle_Forward_Fast);
  server.on("/B", handle_Forward_Slow);
  server.on("/C", handle_Back_Slow);
  server.on("/D", handle_Back_Fast);
  server.on("/off", handle_Stop);
  server.on("/R", handle_Go_Righter);
  server.on("/L", handle_Go_Lefter);
  server.on("/FO", handle_Flashlight_Off);
  server.on("/Pos", handle_Steering_Slider_Input);
  server.onNotFound(handle_NotFound);

  server.begin();                  //Start server
}

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void loop(void) {

  server.handleClient();

}

void handle_NotFound () {
}

void handle_OnConnect() {
  String s = MAIN_page; //Read HTML contents
  server.send(200, "text/html", s); //Send web page
}

void handle_Steering_Slider_Input() {
  int oldpoint = point;
 
  if(server.arg("value") ){
  point = 160 - server.arg("value").toInt(); }  //    reverse direction high+low - given

  if (point-oldpoint>12){  
      servo1.setColor(0, 1, 0)
            .setPosition(point);     
      for (int i=1; i<10; ++i){chain.update();}
      }
  else if (point-oldpoint<-12){
           servo1.setColor(0, 1, 0)
                 .setPosition(point);     
           for (int i=1; i<10; ++i){chain.update();}
      }
  else {point = oldpoint;
       }

//  Serial.print("Slider Input ");  
//  Serial.println(point);
  server.send(200, "text/plain", "ok");
}

void handle_Forward_Fast() {
  ledcWrite( ledChannel_PWM_A, PWM_FAST ); // PWM speed = fast
  ledcWrite( ledChannel_PWM_B, PWM_FAST ); // PWM speed = fast
  digitalWrite(MOTOR_DIR_A, HIGH);
  digitalWrite(MOTOR_DIR1_A, LOW); 
  digitalWrite(MOTOR_DIR_B, LOW);
  digitalWrite(MOTOR_DIR1_B, HIGH); 
 
  server.send(200, "text/plain", "ok");
}

void handle_Forward_Slow() {
  ledcWrite( ledChannel_PWM_A, PWM_SLOW  ); 
  ledcWrite( ledChannel_PWM_B, PWM_SLOW  ); 
  digitalWrite(MOTOR_DIR_A,HIGH );
  digitalWrite(MOTOR_DIR1_A, LOW); 
  digitalWrite(MOTOR_DIR_B, LOW);
  digitalWrite(MOTOR_DIR1_B, HIGH); 
  
  server.send(200, "text/plain", "ok");
}

void handle_Back_Slow() {
  ledcWrite( ledChannel_PWM_A, PWM_SLOW ); 
  ledcWrite( ledChannel_PWM_B, PWM_SLOW ); 
  digitalWrite(MOTOR_DIR_A, LOW);
  digitalWrite(MOTOR_DIR1_A, HIGH); 
  digitalWrite(MOTOR_DIR_B, HIGH);
  digitalWrite(MOTOR_DIR1_B, LOW); 
  
  server.send(200, "text/plain", "ok");
}

void handle_Back_Fast() {
  ledcWrite( ledChannel_PWM_A, PWM_FAST ); 
  ledcWrite( ledChannel_PWM_B, PWM_FAST ); 
  digitalWrite(MOTOR_DIR_A, LOW);
  digitalWrite(MOTOR_DIR1_A, HIGH); 
  digitalWrite(MOTOR_DIR_B, HIGH);
  digitalWrite(MOTOR_DIR1_B, LOW); 
  server.send(200, "text/plain", "ok");
}

void handle_Stop() {
  ledcWrite( ledChannel_PWM_A, PWM_STOP );
  ledcWrite( ledChannel_PWM_B, PWM_STOP );
  digitalWrite(MOTOR_DIR_A, LOW);
  digitalWrite(MOTOR_DIR1_A, LOW); 
  digitalWrite(MOTOR_DIR_B, LOW);
  digitalWrite(MOTOR_DIR1_B, LOW); 

  server.send(200, "text/plain", "ok");
}

void handle_Go_Righter() { // Receive an HTTP GET request for steering.  Depending on the position of sg90 servo could change name to Righter
 point = point - 10;
  if (point < 50) {point = 50;}
 // if (servo1.isConnected()) {
      servo1.setColor(0, 0, 1)
            .setPosition(point);
  
  Serial.print("Righter ");  
  Serial.println(point);
  for (int i=1; i<10; ++i){chain.update();}
  //chain.update();
  //}
  server.send(200, "text/plain", "ok");
}


void handle_Go_Lefter() { // Receive an HTTP GET request for steering.  And from above comment this could be renamed Lefter instead
  point = point + 10;
  if (point > 110) { point = 110; }
  //if (servo1.isConnected()) {
    servo1.setColor(1, 0, 0)
          .setPosition(point);
   
  Serial.print("Lefter ");  
  Serial.println(point);
  for (int i=1; i<10; ++i){chain.update();}
  //chain.update();
  //}
  server.send(200, "text/plain", "ok");
}

void handle_Flashlight_Off() {
 // digitalWrite(Flight, LOW);
  server.send(200, "text/plain", "ok");
}
