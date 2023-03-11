
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>


#define FIREBASE_HOST "*****" // RTDB link without https:// 
#define FIREBASE_AUTH "*****" // Database Secret Key
#define WIFI_SSID "*****" 
#define WIFI_PASSWORD "*****"
// RGB Led pins
#define redPin D5 
#define greenPin D6
#define bluePin D7

//Firebase Data Object
FirebaseData fbdo;


void setup()
{

  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.println("Connected");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();


  //Begining Firebase Connection

 Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  //Allowing Reconnecting wifi when lost
 Firebase.reconnectWiFi(true);
 pinMode(redPin,OUTPUT);
 pinMode(greenPin,OUTPUT);
 pinMode(bluePin,OUTPUT);
 digitalWrite(redPin, LOW);
 digitalWrite(greenPin, LOW);
 digitalWrite(bluePin, LOW);

}

void loop()
{

  if(Firebase.getString(fbdo, "/red")) // Getting the keyword value
  {
   
    Serial.print("Red Value : ");
    Serial.println(fbdo.stringData());
    int redValue = fbdo.stringData().toInt(); // Converting string to integer
    analogWrite(redPin, redValue);

    
    

  }
  if(Firebase.getString(fbdo, "/green")) 
  {
 
    Serial.print("Green Value :  ");
    Serial.println(fbdo.stringData());
    int greenValue = fbdo.stringData().toInt();
    analogWrite(greenPin, greenValue);

    
    

  }
  if(Firebase.getString(fbdo, "/blue")) 
  {

    Serial.print("Blue Value : ");
    Serial.println(fbdo.stringData());
    int blueValue = fbdo.stringData().toInt();
    analogWrite(bluePin, blueValue);

    
    

  }
  else{

    Serial.print("Could not get the data : ");
    Serial.println(fbdo.errorReason());
  }
}
