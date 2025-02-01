#include <Arduino.h>
#include "movements.h"  // Fonctions de déplacement (définies dans movements.h / movements.cpp)
#include "sensors.h"    // Fonctions de gestion des capteurs (définies dans sensors.h / sensors.cpp)
#include <LiquidCrystal.h>

// LCD Pins Configuration
const int rs = 4, en = 6, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int buzzer = A4;  //the pin of the active buzzer
// 😑 Half Blink
byte halfBlink[8] = { B00000, B01110, B00000, B01110, B00000, B00000, B00000, B00000 };

void displayFaceById(int faceId, const char* message, int duration) {
    lcd.clear();

    switch (faceId) {
        case 1:  // 😄 Visage joyeux
            lcd.setCursor(6, 0);
            lcd.write(byte(7));  
            lcd.setCursor(8, 0);
            lcd.write(byte(7));
            lcd.setCursor(6, 1);
            lcd.write(byte(11)); 
            lcd.setCursor(8, 1);
            lcd.write(byte(11));
            break;

        case 2:  // 😠 Visage en colère
            lcd.setCursor(6, 0);
            lcd.write(byte(8));  
            lcd.setCursor(8, 0);
            lcd.write(byte(8));
            lcd.setCursor(6, 1);
            lcd.write(byte(10)); 
            lcd.setCursor(8, 1);
            lcd.write(byte(10));
            break;

        case 3:  // 😱 Visage effrayé
            for (int i = 0; i < 5; i++) {  
                lcd.setCursor(6, 0);
                lcd.write(byte(4));
                lcd.setCursor(8, 0);
                lcd.write(byte(4));
                lcd.setCursor(6, 1);
                lcd.write(byte(10));
                lcd.setCursor(8, 1);
                lcd.write(byte(10));
                lcd.setCursor(2, 1);
                lcd.print(message);
                delay(300);

                lcd.setCursor(6, 0);
                lcd.write(byte(5));  
                lcd.setCursor(8, 0);
                lcd.write(byte(5));
                delay(300);
            }
            lcd.clear();
            return;

        case 4:  // 😈 Visage maléfique
            lcd.setCursor(6, 0);
            lcd.write(byte(6));  
            lcd.setCursor(8, 0);
            lcd.write(byte(6));
            break;

        default:
            lcd.setCursor(4, 0);
            lcd.print("Face not found");
            delay(2000);
            lcd.clear();
            return;
    }

    lcd.setCursor(3, 1);
    lcd.print(message);
    delay(duration);
    lcd.clear();
}

// --- (Optionnel) Fonctions de gestion d'actions --- //
void handleZombie() {
  Serial.println("Action ZOMBIEN lancée.");
}

void handleIndividu() {
  Serial.println("Action INDIVIDU lancée.");
}


void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);  //initialize the buzzer pin as an output

  // Initialisation des capteurs (mouvement, son, température)
  initSensors();

  // Initialisation des moteurs
  initMotors();
}

bool waitForSoundDetection() {
  bool soundDetected = false;
  unsigned long startTime = millis();

  // Échantillonne pendant 2 secondes
  while (millis() - startTime < 2000) {
    soundDetected = checkSound();  // Vérifie l'état du capteur de son
    if (soundDetected) {
      break;  // Si un son est détecté, sortir immédiatement de la boucle
    }
    delay(10);  // Petite pause pour éviter une boucle trop rapide
  }

  return soundDetected;
}

bool waitForHighTemperature() {
  unsigned long startTimeTemp = millis();
  bool tempHighDetected = false;

  // Boucle d'échantillonnage sur 5 secondes
  while (millis() - startTimeTemp < 5000) {  // 5000 ms = 5 secondes
    if (checkTemperature()) {
      Serial.println("Température élevée détectée pendant l'analyse !");
      displayFaceById(3,"Température élevée détectée pendant l'analyse !",2000);
      
      tempHighDetected = true;
      break;  // Sortir dès qu'une température élevée est détectée
    }
    delay(100);  // Attendre 100 ms entre chaque vérification (à ajuster selon vos besoins)
  }

  return tempHighDetected;
}

void loop() {

  moveForward();  // Avance
  delay(2000);    // Temps pour atteindre le coin
  stopMotors();   // Arrêt au coin
  delay(2000);    // Pause avant vérification

  // Détection de mouvement
  if (detectMotion()) {
    Serial.println("Mouvement détecté pendant la vérification !");
    displayFaceById(3,"Mouvement détecté pendant la vérification !",2000);

    // Affichage et prise de décision en fonction du résultat de la détection sonore
    if (waitForSoundDetection()) {
      Serial.println("Son détecté !");
      // 😄 Happy Face
      displayFaceById(3,"Son détecté !",2000);
      if (waitForHighTemperature()) {
        // Boucle infinie affichant "ZOMBIE"
        for ( int i = 0; i < 80; i++)

        {

          digitalWrite(buzzer, HIGH);

          delay(1);  //wait for 1ms

          digitalWrite(buzzer, LOW);

          delay(1);  //wait for 1ms
        }
        while (true) {
          Serial.println("ZOMBIE");
          displayFaceById(3,"ZOMBIE !!!!!",2000);

          delay(1000);
        }
      } else {
          displayFaceById(3,"AUTRE",2000);
        
      }
    } else {
      Serial.println("Aucun son détecté pendant 2 sec.");
      displayFaceById(3,"Aucun son détecté pendant 2 sec.",2000);
      Serial.println("INDIVIDU");
    }
  }
  turnRightWide();  // Tourne à droite pour le prochain côté
  delay(1000);      // Temps pour tourner
  delay(100);       // Délai global pour la boucle (à ajuster)
}
