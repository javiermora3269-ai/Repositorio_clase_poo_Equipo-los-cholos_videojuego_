#include <iostream>
#include <string>
using namespace std;

class InterfazUsuario
{
public:

    void Output(string texto)
    {
        cout << texto;
    }
};

int main()
{
    InterfazUsuario UI;

    string texto = "Bienvenido al juego.\n"
                   "Elige una opcion para continuar.\n";

    UI.Output(texto);

    return 0;
}
