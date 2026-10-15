#include <iostream>
#include <string>
#include <cstdlib>
#include <new>
#include <ctime>

using namespace std;

// ================================================================
// CLASE BASE: CRIATURA
// ================================================================
class Criatura {
private: // ==================== ENCAPSULAMIENTO (Atributos de OBJETO) ====================
    // ATRIBUTOS DE OBJETO (Instancia): Cada objeto tiene su propia copia en memoria.
    string nombre;
    int vida;
    int energia;

    // ATRIBUTO DE CLASE (static): Existe una sola variable compartida por todas las instancias.
    static int contadorCriaturas;

public:
    // ================================================================
    // CONSTRUCTORES Y DESTRUCTOR (Miembros de OBJETO)
    // ================================================================
    Criatura() {
        this->nombre = "Criatura";
        this->vida = 100;
        this->energia = 50;
        
        // Modifica el atributo de CLASE (compartido)
        contadorCriaturas++;
    }

    Criatura(string nombre, int vida, int energia) {
        this->nombre = nombre;
        this->vida = vida;
        this->energia = energia;
        
        // Modifica el atributo de CLASE (compartido)
        contadorCriaturas++;
    }

    ~Criatura() {
        // Modifica el atributo de CLASE (compartido)
        contadorCriaturas--;
    }

    // ================================================================
    // GETTERS Y SETTERS (Métodos de OBJETO)
    // ================================================================
    string getNombre() const { return nombre; }
    int getVida() const { return vida; }
    int getEnergia() const { return energia; }

    void setNombre(const string& nombre) { this->nombre = nombre; }
    void setVida(int vida) { this->vida = (vida < 0) ? 0 : vida; }
    void setEnergia(int energia) { this->energia = (energia < 0) ? 0 : energia; }

    // ================================================================
    // MÉTODOS DE CLASE (static)
    // ================================================================
    // MÉTODOS DE CLASE: No reciben puntero 'this' y solo acceden a miembros static.
    static int cuantasHay() {
        return contadorCriaturas;
    }

    // ================================================================
    // MÉTODOS DE OBJETO (Operaciones de Instancia)
    // ================================================================
    void atacar(Criatura &enemigo) {
        int dano = 10 + rand() % 16;
        cout << this->nombre << " ataca a " << enemigo.nombre << endl;
        cout << "Daño realizado: " << dano << endl;
        enemigo.recibirDanio(dano);
    }

    void atacar(Criatura &enemigo, int extra) {
        int danoBase = 10 + rand() % 16;
        int danoTotal = danoBase + extra;
        cout << this->nombre << " realiza un ATAQUE POTENCIADO a " << enemigo.nombre << " (Extra: +" << extra << ")" << endl;
        cout << "Daño total realizado: " << danoTotal << endl;
        enemigo.recibirDanio(danoTotal);
    }

    void curar() {
        int vidaResultante = this->vida + 10;
        if (vidaResultante > 100) vidaResultante = 100;
        this->vida = vidaResultante;
        cout << this->nombre << " se curó 10 puntos de vida." << endl;
    }

    void curar(int cantidad) {
        int vidaResultante = this->vida + cantidad;
        if (vidaResultante > 100) vidaResultante = 100;
        this->vida = vidaResultante;
        cout << this->nombre << " se curó " << cantidad << " puntos de vida." << endl;
    }

    void recibirDanio(int dano) {
        this->vida -= dano;
        if (this->vida < 0) this->vida = 0;
    }

    void descansar() {
        this->energia += 20;
        if (this->energia > 100) this->energia = 100;
        cout << this->nombre << " descansó y recuperó energía." << endl;
    }

    void mostrar() const {
        cout << "Nombre: " << this->nombre 
             << " | Vida: " << this->vida 
             << " | Energía: " << this->energia << endl;
    }

    bool estaViva() const {
        return this->vida > 0;
    }
};

// ================================================================
// DEFINICIÓN DEL ATRIBUTO STATIC (Miembro de CLASE fuera de la clase)
// ================================================================
int Criatura::contadorCriaturas = 0;

// ================================================================
// CLASE DERIVADA 1: GUERRERO
// ================================================================
class Guerrero : public Criatura {
private:
    int fuerza; // ATRIBUTO DE OBJETO (Exclusivo de Guerrero)

public:
    Guerrero(string nombre, int vida, int energia, int fuerza) 
        : Criatura(nombre, vida, energia) {
        this->fuerza = fuerza;
    }

    // MÉTODO DE OBJETO (Propio de Guerrero)
    void golpePotente(Criatura &enemigo) {
        int danoTotal = 15 + this->fuerza;
        // Accede al nombre heredado usando el getter (getNombre) por ser atributo 'private'
        cout << getNombre() << " asesta un GOLPE POTENTE a " << enemigo.getNombre() 
             << " usando su fuerza de " << this->fuerza << "!" << endl;
        cout << "Daño realizado: " << danoTotal << endl;
        enemigo.recibirDanio(danoTotal);
    }
};

// ================================================================
// CLASE DERIVADA 2: MAGO
// ================================================================
class Mago : public Criatura {
private:
    int mana; // ATRIBUTO DE OBJETO (Exclusivo de Mago)

public:
    Mago(string nombre, int vida, int energia, int mana) 
        : Criatura(nombre, vida, energia) {
        this->mana = mana;
    }

    // MÉTODO DE OBJETO (Propio de Mago)
    void hechizo(Criatura &enemigo) {
        if (this->mana >= 20) {
            this->mana -= 20;
            int danoMagico = 35;
            // Accede al nombre heredado usando el getter (getNombre) por ser atributo 'private'
            cout << getNombre() << " lanza un HECHIZO DE FUEGO a " << enemigo.getNombre() 
                 << " consumiendo 20 de maná (Maná restante: " << this->mana << ")." << endl;
            cout << "Daño mágico realizado: " << danoMagico << endl;
            enemigo.recibirDanio(danoMagico);
        } else {
            cout << getNombre() << " intentó lanzar un hechizo pero no tiene suficiente maná (" 
                 << this->mana << "/20)." << endl;
        }
    }
};

// ==========================================
// MALLOC Y PLACEMENT NEW
// ==========================================
Criatura* crear_criatura(const string& nombre, int vida, int energia) {
    Criatura* c = (Criatura*) malloc(sizeof(Criatura));
    if (c == nullptr) return nullptr;

    new (c) Criatura(nombre, vida, energia);
    return c;
}

void liberar_criatura(Criatura* c) {
    if (c == nullptr) return;

    c->~Criatura();
    free(c);
}

void mostrarEstado(const Criatura &c1, const Criatura &c2) {
    cout << "\n================================" << endl;
    cout << "          ESTADO ACTUAL" << endl;
    cout << "================================" << endl;
    c1.mostrar();
    c2.mostrar();
    cout << "================================" << endl;
}

void menuBatalla(Criatura &jugador, Criatura &enemigo) {
    int opcion;

    while (jugador.estaViva() && enemigo.estaViva()) {
        cout << "\n================================" << endl;
        cout << "        BATALLA DE CRIATURAS" << endl;
        cout << "================================" << endl;
        cout << "1. Atacar normal" << endl;
        cout << "2. Atacar con potencia extra (+15)" << endl;
        cout << "3. Curar +10" << endl;
        cout << "4. Curar cantidad personalizada" << endl;
        cout << "5. Descansar" << endl;
        cout << "6. Ver estado" << endl;
        cout << "7. Salir" << endl;
        cout << "\nSelecciona una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                jugador.atacar(enemigo);
                if (enemigo.estaViva()) {
                    cout << "\nTurno del enemigo..." << endl;
                    enemigo.atacar(jugador);
                }
                break;

            case 2:
                jugador.atacar(enemigo, 15);
                if (enemigo.estaViva()) {
                    cout << "\nTurno del enemigo..." << endl;
                    enemigo.atacar(jugador);
                }
                break;

            case 3:
                jugador.curar();
                break;

            case 4: {
                int cantidad;
                cout << "Cuántos puntos quieres curar: ";
                cin >> cantidad;
                jugador.curar(cantidad);
                break;
            }

            case 5:
                jugador.descansar();
                break;

            case 6:
                mostrarEstado(jugador, enemigo);
                break;

            case 7:
                cout << "\nHas salido de la batalla." << endl;
                return;

            default:
                cout << "\nOpción no válida." << endl;
        }

        if (opcion >= 1 && opcion <= 5) {
            mostrarEstado(jugador, enemigo);
        }
    }

    cout << "\n================================" << endl;
    cout << "         FIN DE BATALLA" << endl;
    cout << "================================" << endl;

    if (jugador.estaViva()) {
        cout << jugador.getNombre() << " ha ganado la batalla!" << endl;
    } else {
        cout << enemigo.getNombre() << " ha ganado la batalla!" << endl;
    }
}

// ==========================================
// MAIN
// ==========================================
int main() {
    srand(time(nullptr));

    cout << "========================================" << endl;
    cout << "  PRACTICA DE SOBRECARGA Y STATIC C++   " << endl;
    cout << "========================================" << endl;

    // 1. Invocar Método de CLASE (static) mediante resolución de ámbito (Criatura::)
    cout << "\n[MÉTODO DE CLASE] Criaturas activas al inicio: " << Criatura::cuantasHay() << endl;

    // 2. Creación de Objetos (Miembros de OBJETO en uso)
    cout << "\n--- Creando criaturas en el stack ---" << endl;
    Criatura criatura1;                                
    Criatura criatura2("Dragón", 100, 80);             
    Criatura criatura3("Goblin", 100, 30);             

    // Invocación del método static de clase
    cout << "[MÉTODO DE CLASE] Criaturas activas tras instanciar 3: " << Criatura::cuantasHay() << endl;

    // 3. Métodos de OBJETO en acción (Sobrecarga de atacar)
    cout << "\n--- Prueba de Sobrecarga de atacar() ---" << endl;
    criatura2.atacar(criatura3);       
    criatura2.atacar(criatura3, 20);   

    // 4. Instanciación de Clases Derivadas (Guerrero y Mago)
    cout << "\n--- Prueba de Herencia y Encapsulamiento ---" << endl;
    Guerrero guerrero("Thorin", 120, 60, 25); 
    Mago mago("Gandalf", 90, 100, 50);        

    cout << "\n1. Uso de Métodos de OBJETO Heredados (mostrar):" << endl;
    cout << "  [Guerrero] "; guerrero.mostrar(); 
    cout << "  [Mago]     "; mago.mostrar();     

    cout << "\n2. Uso de Métodos de OBJETO Propios:" << endl;
    cout << "  -> Golpe del Guerrero:" << endl;
    guerrero.golpePotente(criatura3); 

    cout << "  -> Hechizo del Mago:" << endl;
    mago.hechizo(criatura3);          

    // Comprobar nuevamente el método de CLASE (static)
    cout << "\n[MÉTODO DE CLASE] Criaturas activas (incluyendo Guerrero y Mago): " << Criatura::cuantasHay() << endl;

    // 5. Creación dinámica de un objeto
    cout << "\n--- Creando criatura dinámica ---" << endl;
    Criatura* orco = crear_criatura("Orco", 100, 70);
    
    if (orco == nullptr) {
        cerr << "Error al reservar memoria." << endl;
        return 1;
    }

    cout << "[MÉTODO DE CLASE] Criaturas activas tras crear Orco dinámicamente: " << Criatura::cuantasHay() << endl;

    // 6. Destrucción por ámbito para comprobar decremento del contador de CLASE
    cout << "\n--- Destruyendo criatura1 (por salida de ámbito) ---" << endl;
    {
        Criatura criaturaTemporal("Temporal", 10, 10);
        cout << "  [Bloque interno] Criaturas activas con 'Temporal': " << Criatura::cuantasHay() << endl;
    } 
    cout << "  [Fuera del bloque] Criaturas activas tras destruir 'Temporal': " << Criatura::cuantasHay() << endl;

    // 7. Batalla interactiva
    cout << "\n--- Iniciar Batalla ---" << endl;
    menuBatalla(criatura2, *orco);

    // 8. Liberación de memoria dinámica y revisión final del contador static
    cout << "\n--- Liberando memoria del Orco ---" << endl;
    liberar_criatura(orco);
    cout << "[MÉTODO DE CLASE] Criaturas activas tras liberar al Orco: " << Criatura::cuantasHay() << endl;

    cout << "\nPrograma finalizado correctamente." << endl;
    return 0;
}