#include "sensors.h"

// --- Définition des broches ---
// (Vous pouvez modifier ces valeurs selon votre montage)
const int motionSensorPin = A2;       // Broche pour le capteur de mouvement
const int soundSensorPin = A0;      // Broche pour le capteur de son
const int temperatureSensorPin = A1;  // (Si besoin, sinon utilisez le DHT)

// --- Seuils de détection ---
const int soundThreshold = 530;  // Seuil pour la détection du son (pour analogique)
const float tempThreshold = 35;  // Seuil pour la température "chadie" en °C

// --- Instance du capteur DHT ---
DHT dht(DHTPIN, DHTTYPE);

// --- Fonctions d'initialisation des capteurs ---
void initSensors() {
  // Configurez les broches d'entrée
  pinMode(motionSensorPin, INPUT);
  pinMode(soundSensorPin, INPUT);

  // Initialisation du DHT
  dht.begin();

  Serial.println("Capteurs initialisés.");
}

// --- Détection du mouvement ---
// Retourne true si le capteur PIR détecte un mouvement.
bool detectMotion() {

  unsigned long startTime = millis();
  bool motionDetected = false;

  while (millis() - startTime < 3000) {
    if (digitalRead(motionSensorPin) == HIGH) {
      motionDetected = true;
      break;
    }
  }
  return motionDetected;
}

bool checkSound() {

  int maxValue = 0;
  unsigned long startTime = millis();

  // Échantillonne pendant 500 ms pour trouver la valeur maximale
  while (millis() - startTime < 500) {
    int currentValue = analogRead(soundSensorPin);
    if (currentValue > maxValue) {
      maxValue = currentValue;
    }
  }
  return maxValue  > soundThreshold;
}

bool checkTemperature() {
  float t = dht.readTemperature();
  Serial.print("Température : ");
  Serial.println(t);

  if (isnan(t)) {
    Serial.println("Erreur de lecture du DHT !");
    return false;
  }
  return t > tempThreshold;
}
