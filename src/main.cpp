/*
 * ESP8266 NodeMCU AJAX Demo
 * Updates and Gets data from webpage without page refresh
 */
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Header file with HTML/JS Scripts for webpage
#include "index.h"

#define LED 5

const char *ssid = "ATT7RT97i2";
const char *password = "f3y436pwzu6y";

// Create ESP8266WebServer class object | Server on port 80
ESP8266WebServer server(80);

void handleRoot()
{
  /*
      MAIN_page[] 
        - What is it
          - A constant char array that holds all the HTML/JS scripts for the webpage
          - Storing it as a seperate header file makes things "Easier" to read in the CPP/Sketch file
  */
  String s = MAIN_page;
  /*
      server.send()
        - Sends responses to the client
        - Parameters server.send(code,content_type,content);
          - code : HTTP response code
            - Can be 200 (OKAY) or 404 (NOT FOUND)
          - content_type : HTTP content, for example :
            - text/plain
            - image/png
          - content : actual concent body
  */
  server.send(200, "text/html", s); //Send web page
}

// Read ADC values from potentiometer
void handleADC()
{
  int a = analogRead(A0);
  String adcValue = String(a);

  // Send ADC value when the webpage makes a ajax request
  server.send(200, "text/plane", adcValue);
}

// Generate and send random number
void randomNum()
{
  float randomNumber;

  randomNumber = random(5);
  String randomNum_value = String(randomNumber);

  // send() command needs the value to be stored as a string
  server.send(200, "text/plane", randomNum_value);
}
// Generate and send random number
void randomNum2()
{
  float randomNumber2;

  randomNumber2 = random(75);
  String randomNum_value2 = String(randomNumber2);

  // send() command needs the value to be stored as a string
  server.send(200, "text/plane", randomNum_value2);
}
void handleLED()
{
  String ledState = "OFF";

  /*
      server.arg()
        - Returns the number of query parameters that were passed on the HTTP request
          that triggered the execution of the handling function
        - Refer  xhttp.open("GET", "setLED?LEDstate="+led, true); in index.h file
  */
  String t_state = server.arg("LEDstate");
  Serial.print("LED State : ");
  Serial.println(t_state);

  if (t_state == "1")
  {
    digitalWrite(LED, HIGH);

    // Parameter sent back to webpage
    ledState = "ON";
  }
  else
  {
    digitalWrite(LED, LOW);

    // Parameter sent back to webpage
    ledState = "OFF";
  }

  // LED state sent to webpage
  server.send(200, "text/plane", ledState);
}

void setup(void)
{
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("");

  pinMode(LED, OUTPUT);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(250);
    Serial.print(".");
  }

  // Show IP if connecting ot WiFi was successful
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Specify which routine handles what
  server.on("/", handleRoot);
  server.on("/setLED", handleLED);
  server.on("/readADC", handleADC);
  server.on("/randomNum", randomNum);
  server.on("/barADC", handleADC);

  // Start server
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void)
{
  //Handle client requests | Looks for pending requests
  server.handleClient();
}