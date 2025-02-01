#ifndef MOVEMENTS_H
#define MOVEMENTS_H

#include <Arduino.h>

// --- Définition des broches pour le moteur gauche ---
// Le pin de direction contrôle l'orientation (avant/arrière)
// Le pin enable (PWM) contrôle la vitesse
const int LEFT_DIRECTION_PIN = 2;   // Par exemple, utilisé pour la direction du moteur gauche
const int LEFT_ENABLE_PIN    = 3;   // PWM capable pour le contrôle de la vitesse du moteur gauche

// --- Définition des broches pour le moteur droit ---
const int RIGHT_DIRECTION_PIN = 7;  // Par exemple, utilisé pour la direction du moteur droit
const int RIGHT_ENABLE_PIN    = 5;  // PWM capable pour le contrôle de la vitesse du moteur droit

// --- Vitesse ---
const int fullSpeed   = 255;
const int reduceSpeed = 127;

// Prototypes des fonctions de mouvement
void initMotors();
void moveForward();
void moveBackward();
void turnRightWide();
void turnLeftWide();
void stopMotors();
void patrol();


#endif  // MOVEMENTS_H
