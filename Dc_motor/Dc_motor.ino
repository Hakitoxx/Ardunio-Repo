// --- Güncellenmiş Kararlı Kod ---
const int butonArtir = 2;
const int butonDur = 3;
const int led1 = 4; 
const int led2 = 5; 
const int led3 = 6; 
const int motorHizPin = 9; 
const int motorYon1 = 8;
const int motorYon2 = 7;

int vites = 0; 

void setup() {
  pinMode(butonArtir, INPUT_PULLUP);
  pinMode(butonDur, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(motorYon1, OUTPUT);
  pinMode(motorYon2, OUTPUT);
  
  digitalWrite(motorYon1, HIGH);
  digitalWrite(motorYon2, LOW);
  
  hizAyarla(); 
}

void loop() {
  // ARTIRMA BUTONU
  if (digitalRead(butonArtir) == LOW) { 
    delay(50); // Titreşimi (debouncing) engellemek için kısa bekleme
    if (digitalRead(butonArtir) == LOW) { // Hala basılı mı?
      vites++;
      if (vites > 3) vites = 3; 
      hizAyarla();
      
      // ELİNİ ÇEKENE KADAR BURADA BEKLE
      // Bu sayede vites sadece 1 tane artar, fırlamaz.
      while(digitalRead(butonArtir) == LOW); 
      delay(50); // Bırakma anındaki paraziti engelle
    }
  }

  // DURDURMA BUTONU
  if (digitalRead(butonDur) == LOW) {
    delay(50);
    vites = 0;
    hizAyarla();
    
    // ELİNİ ÇEKENE KADAR BEKLE
    while(digitalRead(butonDur) == LOW); 
    delay(50);
  }
}

void hizAyarla() {
  // Vites durumuna göre LED ve Motor Kontrolü
  if (vites == 0) {
    analogWrite(motorHizPin, 0);
    digitalWrite(led1, LOW); digitalWrite(led2, LOW); digitalWrite(led3, LOW);
  } else if (vites == 1) {
    analogWrite(motorHizPin, 140); // 130 yerine 140 yaptım, motor daha rahat kalkar
    digitalWrite(led1, HIGH); digitalWrite(led2, LOW); digitalWrite(led3, LOW);
  } else if (vites == 2) {
    analogWrite(motorHizPin, 200);
    digitalWrite(led1, HIGH); digitalWrite(led2, HIGH); digitalWrite(led3, LOW);
  } else if (vites == 3) {
    analogWrite(motorHizPin, 255);
    digitalWrite(led1, HIGH); digitalWrite(led2, HIGH); digitalWrite(led3, HIGH);
  }
}
