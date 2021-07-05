#include <ESP8266HTTPClient.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
WiFiClient wifiClient;

//BUAT WIFINYA
const char* ssid = "localhost";
const char* password = "";
int status = WL_IDLE_STATUS;
//BUAT HOSTNYA
const char* serverName = "http://192.168.1.9/sensor/send.php";
                        
const int relay = D5;      
const int sensorPin = A0;
int nilai;
int buatRelay;
int buatAir;
String stRelay;
String stAir;
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
    stRelay = "ON";
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
    stRelay = "OFF";
    digitalWrite(relay, HIGH);
  }
  else if(nilai < 350){
    lcd.setCursor(0, 0);
    lcd.print("Kelembapan = ");
    lcd.print(nilai);
    lcd.setCursor(0, 1);
    lcd.print("Tanah Lembab");
    delay(1000);
    lcd.clear();
    digitalWrite(relay, HIGH);
    stRelay = "OFF";
  } 
    if (distance > 16)
    {
    lcd.setCursor(0,0);
    lcd.print("Sisa Air Kurang");
    lcd.setCursor(0,1);
    lcd.print("Dari 6 cm");
    digitalWrite(buzzer, HIGH);
    delay (1000);
    stAir = "Air Tersisa Kurang dari 6 cm";
}
    else if(distance > 6 && distance < 16)
{
    lcd.setCursor(0,0);
    lcd.print("Sisa Air");
    lcd.setCursor(0,1);
    lcd.print("Masih Cukup");
    digitalWrite(buzzer, LOW);
    delay (1000);
    stAir = "Air Tersisa Setengah";
}
    else if(distance < 6 )
{
    lcd.setCursor(0,0);
    lcd.print(" Air");
    lcd.setCursor(0,1);
    lcd.print("Masih Penuh");
    digitalWrite(buzzer, LOW);
    delay (1000);
    stAir = "Air Masih Penuh";
}
//Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){
    Serial.println(stRelay);
    Serial.println(stAir);
    HTTPClient http;
    // Your Domain name with URL path or IP address with path
    http.begin(wifiClient,serverName);
    
    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Prepare your HTTP POST request data
    String httpRequestData = "kelembapan=" + String(nilai) + "&waterlevel=" + stAir +"&menyiram=" + stRelay +"";

    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
    
    // Send HTTP POST request 
    int httpResponseCode = http.POST(httpRequestData);
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
