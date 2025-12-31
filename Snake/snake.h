#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>

// Définition des couleurs pour l'affichage console
#define RESET "\033[0m"
#define ROUGE "\033[31m"
#define VERT "\033[32m"
#define GRIS "\033[90m"
#define JAUNE "\033[33m"
#define BLEU "\033[34m"

// Paramètres de la zone de jeu
const int largeur = 20;
const int hauteur = 20;

// Énumération pour gérer les directions sans utiliser de chiffres confus
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };

// Variables globales partagées (extern signifie qu'elles sont définies dans le .cpp)
extern bool gameOver;
extern int x, y, fruitX, fruitY, score, highScore;
extern int tailX[100], tailY[100];
extern int nTail;
extern eDirecton dir;

// Prototypes des fonctions : les "sous-programmes"
void Setup(); // Initialisation
void Draw(); // Graphismes
void Input(); // Clavier
void Logic(); // Règles du jeu


#endif // SNAKE_H_INCLUDED
