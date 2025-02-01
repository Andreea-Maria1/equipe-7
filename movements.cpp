#include "movements.h"
#include <Arduino.h>

// Fonction d'initialisation des moteurs : configure les broches et arrête les moteurs
void initMotors() {
  // Configurer les broches de direction et d'activation (enable) comme sorties
  pinMode(LEFT_DIRECTION_PIN, OUTPUT);
  pinMode(RIGHT_DIRECTION_PIN, OUTPUT);
  pinMode(LEFT_ENABLE_PIN, OUTPUT);
  pinMode(RIGHT_ENABLE_PIN, OUTPUT);
  
  // Arrêt initial des moteurs
  digitalWrite(LEFT_DIRECTION_PIN, LOW);
  digitalWrite(RIGHT_DIRECTION_PIN, LOW);
  analogWrite(LEFT_ENABLE_PIN, 0);
  analogWrite(RIGHT_ENABLE_PIN, 0);
  
  Serial.println("Moteurs initialisés.");
}

// Fonction pour avancer en ligne droite
void moveForward() {
  // Définir la direction "avant" pour les deux moteurs
  digitalWrite(LEFT_DIRECTION_PIN, LOW);
  digitalWrite(RIGHT_DIRECTION_PIN, LOW);
  
  // Appliquer la vitesse maximale aux deux moteurs
  analogWrite(LEFT_ENABLE_PIN, fullSpeed);
  analogWrite(RIGHT_ENABLE_PIN, fullSpeed);
}

// Fonction pour faire tourner le robot
void moveBackward() {
  digitalWrite(LEFT_DIRECTION_PIN, HIGH);
  digitalWrite(RIGHT_DIRECTION_PIN, HIGH);
  
  analogWrite(LEFT_ENABLE_PIN, fullSpeed);
  analogWrite(RIGHT_ENABLE_PIN, fullSpeed);
}

// Virage à gauche large : réduire la vitesse du moteur gauche
void turnLeftWide() {
  // Les deux moteurs avancent
  digitalWrite(LEFT_DIRECTION_PIN, LOW);
  digitalWrite(RIGHT_DIRECTION_PIN, LOW);
  
  analogWrite(LEFT_ENABLE_PIN, 0); // Vitesse réduite pour le moteur gauche
  analogWrite(RIGHT_ENABLE_PIN, fullSpeed);     // Pleine vitesse pour le moteur droit
}

// Virage à droite large : réduire la vitesse du moteur droit
void turnRightWide() {
 // Les deux moteurs avancent
  digitalWrite(LEFT_DIRECTION_PIN, LOW);
  digitalWrite(RIGHT_DIRECTION_PIN, LOW);
  
  analogWrite(LEFT_ENABLE_PIN, fullSpeed);       // Pleine vitesse pour le moteur gauche
  analogWrite(RIGHT_ENABLE_PIN, 0);   // Vitesse réduite pour le moteur droit
}

// Fonction pour la patrouille (ronde)
void patrol() {
  // Insérez ici votre code de patrouille
  Serial.println("Le robot patrouille");
}


// Arrêter les moteurs
void stopMotors() {
  analogWrite(LEFT_ENABLE_PIN, 0);
  analogWrite(RIGHT_ENABLE_PIN, 0);
}
