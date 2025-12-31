#include "snake.h"

using namespace std;

// Définition réelle des variables globales
bool gameOver;
int x, y, fruitX, fruitY, score, highScore = 0;
int tailX[100], tailY[100];
int nTail;
eDirecton dir;

// Sous-programme : Initialise une nouvelle partie
void Setup() {
    gameOver = false;
    dir = STOP; // Le serpent ne bouge pas au départ
    x = largeur / 2;
    y = hauteur / 2;
    fruitX = rand() % largeur;
    fruitY = rand() % hauteur;
    score = 0;
    nTail = 0;
}

// Sous-programme : Gère tout l'affichage visuel
void Draw() {
    // Replace le curseur en haut à gauche pour éviter que l'écran ne clignote
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0,0});

    // Dessin du mur du haut
    cout << GRIS;
    for (int i = 0; i < largeur + 2; i++) cout << "#";
    cout << RESET << endl;

    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            if (j == 0) cout << GRIS << "#" << RESET; // Mur gauche

            if (i == y && j == x) cout << VERT << "O" << RESET; // Tête du serpent
            else if (i == fruitY && j == fruitX) cout << ROUGE << "@" << RESET; // Fruit
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << VERT << "o" << RESET; // Corps du serpent
                        print = true;
                    }
                }
                if (!print) cout << " ";
            }
            if (j == largeur - 1) cout << GRIS << "#" << RESET; // Mur droit
        }
        cout << endl;
    }

    // Dessin du mur du bas
    cout << GRIS;
    for (int i = 0; i < largeur + 2; i++) cout << "#";
    cout << RESET << endl;
    cout << JAUNE << "SCORE: " << score << " | MEILLEUR SCORE: " << highScore << RESET << " " << endl;
}

// Sous-programme : Détecte les touches pressées par le joueur
void Input() {
    if (_kbhit()) { // Si une touche a été frappée
        switch (_getch()) {
            case 'q': if(dir != RIGHT) dir = LEFT; break;
            case 'd': if(dir != LEFT) dir = RIGHT; break;
            case 'z': if(dir != DOWN) dir = UP; break;
            case 's': if(dir != UP) dir = DOWN; break;
        }
    }
}

// Sous-programme : Calcule les déplacements et les collisions
void Logic() {
    // Logique pour faire suivre la queue : chaque segment prend la place du précédent
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Déplacement selon la direction actuelle
    switch (dir) {
        case LEFT: x--; break;
        case RIGHT: x++; break;
        case UP: y--; break;
        case DOWN: y++; break;
        default: break;
    }

    // Vérification des collisions avec les murs
    if (x >= largeur || x < 0 || y >= hauteur || y < 0) gameOver = true;

    // Vérification des collisions avec son propre corps
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y) gameOver = true;

    // Vérification si le serpent mange un fruit
    if (x == fruitX && y == fruitY) {
        score += 10;
        if (score > highScore) highScore = score;
        fruitX = rand() % largeur;
        fruitY = rand() % hauteur;
        nTail++; // Le serpent grandit
    }
}
