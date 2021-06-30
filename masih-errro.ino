#include <ESP8266HTTPClient.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
WiFiClient wifiClient;

//BUAT WIFINYA
const char* ssid = "localhost";
const char* password = "27BF7F16";
int status = WL_IDLE_STATUS;
//BUAT HOSTNYA
const char* serverName = "http://127.0.0.1/sensor/send.php";
const char htmlHeader[] = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/html\r\n"
                        "Connection: close\r\n\r\n"
                        "<!DOCTYPE HTML>\r\n"
                        "<html>\r\n";
                        
const int relay = D5;      
const int sensorPin = A0;
int nilai;

int yourarduinodata = 999;
String yourdatacolumn = "kelembapan=";
String yourdata;
String buatRelay = ("OFF","ON");

const int trigPin = D6;
const int echoPin = D7;
const int buzzer = D4;
long duration;
int distance;

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  //koneksi wifi
  WiFi.hostname("NODEMCU");
  WiFi.begin(ssid, password);
  lcd.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  lcd.print(".");
  //KALO BISA KONEK
  lcd.print("BERHASIL KONEKSI");
  Serial.println("BERHASIL KONEKSI");
  }
  pinMode(sensorPin, INPUT);
  pinMode(relay, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
}

void loop() {
  int nilai = analogRead(sensorPin);
  lcd.init();
//  Buat Level Air
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH); 
  distance = duration*0.034/2;

    
  if(nilai > 700)
  {
    lcd.setCursor(0, 0);
    lcd.print("Kelembapan = ");
    lcd.print(nilai);
    lcd.setCursor(0, 1);
    lcd.print("Tanah Kering");
    delay(1000);
    lcd.clear();
    digitalWrite(relay, LOW);
  }
  else if(nilai > 350 && nilai < 700)
  {
    lcd.setCursor(0, 0);
    lcd.print("Kelembapan = ");
    lcd.print(nilai);
    lcd.setCursor(0, 1);
    lcd.print("Tanah Normal");
    delay(1000);
    lcd.clear();
    digitalWrite(relay, HIGH);
  }
  else
    lcd.setCursor(0, 0);
    lcd.print("Kelembapan = ");
    lcd.print(nilai);
    lcd.setCursor(0, 1);
    lcd.print("Tanah Lembab");
    delay(1000);
    lcd.clear();
    digitalWrite(relay, HIGH);
    
    if (distance < 5)
    {
    lcd.setCursor(0,0);
    lcd.print("Distance: ");
    lcd.print(distance);
    lcd.print(" cm");
    lcd.setCursor(0,1);
    lcd.print("Air dikit WOY");
    digitalWrite(buzzer, HIGH);
    delay (1000);
}
    else if(distance >= 6 )
{
    lcd.setCursor(0,0);
    lcd.print("Distance: ");
    lcd.print(distance);
    lcd.print(" cm");
    lcd.setCursor(0,1);
    lcd.print("Air masih banyak");
    digitalWrite(buzzer, LOW);
    delay (100);
}

////kirim data ke server
//  WiFiClient client;
//  //inisialisasi port 80
//  const int httpPort = 80;
//  if( !client.connect(server, httpPort)){
//    lcd.print("Koneksi Gagal");
//    Serial.println("Koneksi Gagal");
//    return;
//  }
//Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
    // Your Domain name with URL path or IP address with path
    http.begin(wifiClient,"http://127.0.0.1/sensor/send.php");
    
    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Prepare your HTTP POST request data
    String httpRequestData = "?kelembapan=" + String(nilai) + "&waterlevel=" + String(distance) +"&menyiram=" + String(buatRelay) +"";

    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
    // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);
    // If you need an HTTP request with a content type: text/plain
    http.addHeader("Content-Type", "text/plain");
    //int httpResponseCode = http.POST("Hello, World!");
    // If you need an HTTP request with a content type: application/json, use the following:
    http.addHeader("Content-Type", "application/json");
    //int httpResponseCode = http.POST("{\"value1\":\"19\",\"value2\":\"67\",\"value3\":\"78\"}");
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  delay(5000);
}
