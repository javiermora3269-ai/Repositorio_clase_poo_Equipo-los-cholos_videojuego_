#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

class Evento {
private:
    int tipo;

public:
    Evento() {
        tipo = 0;
    }

    void generarEvento() {
        tipo = rand() % 4;

        cout << "\n=== EVENTO ALEATORIO ===" << endl;

        switch (tipo) {

        case 0:
            cout << "Encontraste una fuente misteriosa." << endl;
            cout << "Recuperas 20 puntos de vida." << endl;
            break;

        case 1:
            cout << "Encontraste una energia extrana." << endl;
            cout << "Recuperas 30 puntos de energia." << endl;
            break;

        case 2:
            cout << "Un enemigo aparecio de repente." << endl;
            cout << "Prepárate para luchar." << endl;
            break;

        case 3:
            cout << "Encontraste un tesoro." << endl;
            cout << "Obtuviste una recompensa." << endl;
            break;
        }
    }

    int getTipo() const {
        return tipo;
    }
};

int main() {

    srand(static_cast<unsigned int>(time(0)));

    Evento evento;

    cout << "=== EXPLORACION ===" << endl;

    for (int i = 0; i < 3; i++) {
        cout << "\nExplorando..." << endl;
        evento.generarEvento();
    }

    return 0;
}
```
