#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Criatura {
private:
    int vida;
    int energia;

public:
    string nombre;

    // Constructor
    Criatura(string nombre, int vida, int energia) {
        this->nombre = nombre;
        setVida(vida);
        setEnergia(energia);

        cout << "Se creo la criatura " << this->nombre << endl;
    }

    // Destructor
    ~Criatura() {
        cout << "Se destruyo la criatura " << this->nombre << endl;
    }

    // Getter de vida
    int getVida() const {
        return vida;
    }

    // Setter de vida
    void setVida(int v) {
        if (v < 0)
            vida = 0;
        else if (v > 100)
            vida = 100;
        else
            vida = v;
    }

    // Getter de energia
    int getEnergia() const {
        return energia;
    }

    // Setter de energia
    void setEnergia(int e) {
        if (e < 0)
            energia = 0;
        else if (e > 100)
            energia = 100;
        else
            energia = e;
    }

    // Recibir daño
    void recibirDanio(int dano) {
        setVida(getVida() - dano);

        cout << nombre << " recibio "
             << dano << " puntos de dano." << endl;
    }

    // Curar
    void curar(int cantidad) {
        setVida(getVida() + cantidad);

        cout << nombre << " se curo "
             << cantidad << " puntos de vida." << endl;
    }

    // Atacar
    void atacar(Criatura &enemigo) {
        int dano = 10 + rand() % 21;

        cout << nombre << " ataca a "
             << enemigo.nombre << endl;

        enemigo.recibirDanio(dano);
    }

    // Descansar
    void descansar() {
        setEnergia(getEnergia() + 20);

        cout << nombre
             << " descanso y recupero energia." << endl;
    }

    // Mostrar datos
    void mostrar() const {
        cout << "Nombre: " << nombre << endl;
        cout << "Vida: " << getVida() << endl;
        cout << "Energia: " << getEnergia() << endl;
    }

    bool estaViva() const {
        return getVida() > 0;
    }
};

int main() {

    srand(time(0));

    cout << "=== CREACION DE CRIATURAS ===" << endl;

    // Criatura creada con new
    Criatura* criatura1 = new Criatura("Dragon", 100, 80);

    // Criatura creada normalmente
    Criatura criatura2("Orco", 90, 70);

    cout << "\n=== DATOS INICIALES ===" << endl;

    criatura1->mostrar();

    cout << endl;

    criatura2.mostrar();

    cout << "\n=== PRUEBA DE VALIDACION ===" << endl;

    cout << "Intentando asignar 150 de vida al Dragon..." << endl;

    criatura1->setVida(150);

    cout << "Vida del Dragon: "
         << criatura1->getVida() << endl;

    cout << "\nIntentando asignar -20 de vida al Orco..." << endl;

    criatura2.setVida(-20);

    cout << "Vida del Orco: "
         << criatura2.getVida() << endl;

    // Restaurar vida para continuar la interacción
    criatura2.setVida(90);

    cout << "\n=== INTERACCION ===" << endl;

    criatura1->atacar(criatura2);

    cout << "\nEstado del Orco:" << endl;

    criatura2.mostrar();

    criatura2.curar(15);

    cout << "\nDespues de curarse:" << endl;

    criatura2.mostrar();


    // =====================================================
    // MENU DINAMICO
    // =====================================================

    int opcion;

    do {
        cout << "\n============================" << endl;
        cout << "       MENU DE CRIATURAS" << endl;
        cout << "============================" << endl;
        cout << "1. Dragon ataca al Orco" << endl;
        cout << "2. Orco ataca al Dragon" << endl;
        cout << "3. Curar Dragon" << endl;
        cout << "4. Curar Orco" << endl;
        cout << "5. Descansar Dragon" << endl;
        cout << "6. Descansar Orco" << endl;
        cout << "7. Mostrar estados" << endl;
        cout << "0. Salir" << endl;
        cout << "Elige una opcion: ";
        cin >> opcion;

        cout << endl;

        switch (opcion) {

        case 1:
            if (criatura1->estaViva() && criatura2.estaViva()) {
                criatura1->atacar(criatura2);
            }
            else {
                cout << "Una de las criaturas ya no esta viva." << endl;
            }
            break;

        case 2:
            if (criatura1->estaViva() && criatura2.estaViva()) {
                criatura2.atacar(*criatura1);
            }
            else {
                cout << "Una de las criaturas ya no esta viva." << endl;
            }
            break;

        case 3:
            criatura1->curar(20);
            break;

        case 4:
            criatura2.curar(20);
            break;

        case 5:
            criatura1->descansar();
            break;

        case 6:
            criatura2.descansar();
            break;

        case 7:
            cout << "=== DRAGON ===" << endl;
            criatura1->mostrar();

            cout << "\n=== ORCO ===" << endl;
            criatura2.mostrar();
            break;

        case 0:
            cout << "Saliendo del juego..." << endl;
            break;

        default:
            cout << "Opcion invalida." << endl;
        }

    } while (opcion != 0);


    cout << "\n=== LIBERANDO MEMORIA ===" << endl;

    // Liberar la criatura creada con new
    delete criatura1;
    criatura1 = nullptr;

    cout << "Memoria liberada correctamente." << endl;

    return 0;
}

