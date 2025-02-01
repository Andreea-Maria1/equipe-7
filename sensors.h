#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include "DHT.h"

// --- Configuration du capteur DHT ---
#define DHTPIN 9          // Broche à laquelle le DHT est connecté
#define DHTTYPE DHT11     // Type de capteur (DHT11)

extern DHT dht;  // Instance du capteur DHT (définie dans sensors.cpp)

// --- Définition des broches des capteurs ---
extern const int motionSensorPin;      // Capteur de mouvement (ex. PIR)
extern const int soundSensorPin;       // Capteur de son (DO)
extern const int temperatureSensorPin;   // (Optionnel, si différent du DHT)

// --- Seuils de détection ---
extern const int soundThreshold;         // Seuil pour la détection du son (pour lecture analogique)
extern const float tempThreshold;        // Seuil pour la température "chadie"

// --- Prototypes des fonctions ---
void initSensors();
bool detectMotion();
bool checkSound();
bool checkTemperature();

#endif // SENSORS_H
