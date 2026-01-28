/* * Annen İçin Doğum Günü Hediyesi
 * 5 LED + Hoparlör + Buton (Dahili Pull-up)
 */

#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523

// Pin Tanımlamaları
int hoparlor = 8;
int buton = 2;
int ledler[] = {9, 10, 11, 12, 13}; // LED'lerin bağlı olduğu pinler

// Melodi Notaları
int melodi[] = { 
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_F4, NOTE_E4, 
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_G4, NOTE_F4, 
  NOTE_C4, NOTE_C4, NOTE_C5, NOTE_A4, NOTE_F4, NOTE_E4, NOTE_D4, 
  NOTE_AS4, NOTE_AS4, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_F4 
};

// Nota Süreleri (4: çeyrek, 8: sekizlik)
int sureler[] = { 
  4, 8, 4, 4, 4, 2, 
  4, 8, 4, 4, 4, 2, 
  4, 8, 4, 4, 4, 4, 4, 
  4, 8, 4, 4, 4, 2 
};

void setup() {
  pinMode(hoparlor, OUTPUT);
  pinMode(buton, INPUT_PULLUP); // Harici direnç gerektirmez
  
  for (int i = 0; i < 5; i++) {
    pinMode(ledler[i], OUTPUT);
  }
}

void loop() {
  // Butona basıldığında (GND'ye çekildiğinde) başla
  if (digitalRead(buton) == LOW) {
    
    // Şarkıyı çalmaya başla
    for (int i = 0; i < 25; i++) {
      int notaSuresi = 1000 / sureler[i];
      
      // Müzik çalarken rastgele bir LED seç ve yak
      int secilenLed = random(0, 5); 
      
      tone(hoparlor, melodi[i], notaSuresi);
      digitalWrite(ledler[secilenLed], HIGH); 
      
      int ara = notaSuresi * 1.30;
      delay(ara);
      
      // Notayı durdur ve TÜM LED'leri söndür (bir sonraki nota için hazırlık)
      noTone(hoparlor);
      for (int j = 0; j < 5; j++) {
        digitalWrite(ledler[j], LOW);
      }
    }
  }
}
