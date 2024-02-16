

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define HOST "192.168.31.52"          // Enter HOST URL without "http:// "  and "/" at the end of URL

#define WIFI_SSID "My_Station"            // WIFI SSID here                                   
#define WIFI_PASSWORD "myhome@123"
 
 String URL = "http://192.168.31.52/demo1/index.php";

int val;


const int trigPin = 12;
const int echoPin = 14;
const int vcc = 13;
long duration ;
int distanceCm;

String sendval,postData;

void setup(void)
{ Serial.begin(115200); 
Serial.println("Communication Started \n\n");  
delay(1000);
  WiFi.mode(WIFI_STA);           
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
Serial.print("Connecting to ");
Serial.print(WIFI_SSID);
while (WiFi.status() != WL_CONNECTED) 
{ Serial.print(".");
    delay(500); }

Serial.println();
Serial.print("Connected to ");
Serial.println(WIFI_SSID);
Serial.print("IP Address is : ");
Serial.println(WiFi.localIP());    //print local IP address

delay(30);

pinMode(LED_BUILTIN, OUTPUT);
  
pinMode(trigPin,OUTPUT);
pinMode(echoPin,INPUT);
pinMode(vcc,OUTPUT);
  delay(700);

}

void loop() {
 digitalWrite(vcc,HIGH);
  // put your main code here, to run repeatedly:
 digitalWrite(trigPin,LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin,HIGH);
 delayMicroseconds(2);
 digitalWrite(trigPin,LOW);

 duration = pulseIn(echoPin,HIGH);
 distanceCm = duration*0.034/2;
 Serial.println(distanceCm);


    int h = distanceCm;    
    
  delay(800);
  HTTPClient http;    // http object of clas HTTPClient
WiFiClient client;

// Convert integer variables to string
sendval = String(h);  


 
postData = "sendval=" + sendval ;

http.begin(client,URL);              // Connect to host where MySQL databse is hosted
http.addHeader("Content-Type", "application/x-www-form-urlencoded");            //Specify content-type header

  
 
int httpCode = http.POST(postData);   // Send POST request to php file and store server response code in variable named httpCode
Serial.println("Values are, sendval = " + sendval );


// if connection eatablished then do this
if (httpCode == 200) { Serial.println("Values uploaded successfully."); Serial.println(httpCode); 
String webpage = http.getString();    // Get html webpage output and store it in a string
Serial.println(webpage + "\n"); 
}

// if failed to connect then return and restart

else { 
  Serial.println(httpCode); 
  Serial.println("Failed to upload values. \n"); 
  http.end(); 
  return; }


delay(3000); 
digitalWrite(LED_BUILTIN, LOW);
delay(3000);
digitalWrite(LED_BUILTIN, HIGH);
}














