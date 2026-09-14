#include <iostream>
#include <string>
using namespace std;

void Output()
{
    string texto = "Bienvenido al juego.\n"
                   "Elige una opcion para continuar.\n";

    cout << texto;
}

int Input(int LimInferior, int LimSuperior, string Pregunta)
{
    int Opcion;

    do
    {
        cout << Pregunta;
        cin >> Opcion;

        if (Opcion < LimInferior || Opcion > LimSuperior)
        {
            cout << "Opcion no valida. Intenta de nuevo.\n";
        }

    } while (Opcion < LimInferior || Opcion > LimSuperior);

    return Opcion;
}

int main()
{
    Output();

    int opcion = Input(1, 3,
        "1. Atacar\n"
        "2. Actuar\n"
        "3. Curar\n"
        "Selecciona una opcion: ");

    cout << "Elegiste la opcion: " << opcion << endl;

    return 0;
}
