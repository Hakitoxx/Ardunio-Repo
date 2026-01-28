#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <DHT.h>

// Pin Tanımlamaları
#define DHTPIN 12     // DHT11 S pini D12'de
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Nokia 5110: CLK=3, DIN=4, DC=5, CE=7, RST=6
Adafruit_PCD8544 display = Adafruit_PCD8544(3, 4, 5, 7, 6);

const int led1 = 8;
const int led2 = 9;
const int led3 = 10;
const int butonPin = 2;

bool sistemAcik = false;
int sonButonDurumu = HIGH;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(butonPin, INPUT_PULLUP);

  dht.begin();
  display.begin();
  display.setContrast(55);
  display.clearDisplay();
  display.display();
}

void loop() {
  int butonOkuma = digitalRead(butonPin);

  if (butonOkuma == LOW && sonButonDurumu == HIGH) {
    sistemAcik = !sistemAcik;
    delay(200);
  }
  sonButonDurumu = butonOkuma;

  if (sistemAcik) {
    // DHT11'den veri oku
    float nem = dht.readHumidity();

    // Veri okunamazsa hata verme
    if (isnan(nem)) {
      display.clearDisplay();
      display.setCursor(0,0);
      display.print("Sensor Hatasi");
      display.display();
      return;
    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0,0);
    display.print("HAVA NEMI:");
    
    display.setTextSize(2);
    display.setCursor(15,15);
    display.print("%");
    display.print((int)nem);

    // LED Kontrolü (Hava nemine göre)
    digitalWrite(led1, nem > 30 ? HIGH : LOW);
    digitalWrite(led2, nem > 50 ? HIGH : LOW);
    digitalWrite(led3, nem > 70 ? HIGH : LOW);

    if (nem > 70) {
      display.setTextSize(1);
      display.setCursor(0,35);
      display.print("YUKSEK NEM!");
    }
    display.display();

  } else {
    display.clearDisplay();
    display.display();
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }
  delay(100);
}
