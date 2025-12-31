#include "snake.h"

using namespace std;

int main() {
    // Activation du mode ANSI pour que les couleurs s'affichent correctement sous Windows
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    char choix;
    do {
        system("cls"); // Nettoyage de l'écran pour une nouvelle partie
        Setup(); // Préparation du jeu

        while (!gameOver) {
            Draw(); // Affichage
            Input(); // Touches clavier
            Logic(); // Mouvements et règles
            Sleep(150); // Pause de 150ms pour contrôler la vitesse
        }

        // Affichage du menu après avoir perdu
        cout << ROUGE << "\n--- GAME OVER ! ---" << RESET << endl;
        cout << BLEU << "Voulez-vous rejouer ? (O/N) : " << RESET;
        cin >> choix;

    } while (choix == 'o' || choix == 'O');

    cout << JAUNE << "\nMerci d'avoir joue ! Record final : " << highScore << RESET << endl;
    return 0;
}
