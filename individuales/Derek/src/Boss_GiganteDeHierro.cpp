#include <iostream>
#include "../lib/Class_UserInterface.hpp"
#include "../lib/bosses/Boss_GiganteDeHierro.hpp"


BossIronGiant::BossIronGiant() : Criatura("Gigante de Hierro", 350.0f, 150, 35.0f, 0.7f, "Mirar a los Ojos", true, 2, 500){
    AtaqueRandom = 0;
    AccionExlcusivaNombre = "Confrontar";
    AccionParticularNombre = "Cortar Energia";
    AccionIntentosEspecial = 0;
    AccionIntentosExclusiva = 0;
}

void BossIronGiant::MostrarDescripcion() {
    std::cout << "   >> La muralla de hierro frente a ti no para de mirarte fijamente <<\n"
                << "   >> El destello rojo en sus hojos se refleja en todo tu rostro <<\n"
                << "   >> Esta decidido a no dejar ni un solo rastro de ti <<\n";
}

void BossIronGiant::AccionEspecial() {
    if(!GetEsPerdonable()){
        switch(UI.GetOpcion()){
            case UI.OpcActuar::Especial: 
                AccionIntentosEspecial += (AccionIntentosExclusiva < 3) ? 0 : 1;
                if (AccionIntentosEspecial < 2) std::cout << "   -> La muralla plateada ni se inmuta.\n";
                else if (AccionIntentosEspecial == 2) std::cout << "   -> El Gigante comienza a ponerse nervioso.\n";
                else std::cout << "   -> El Gigante ha retirado la vista!!!\n";
                break;
            case UI.OpcActuar::Exclusiva:
                AccionIntentosExclusiva++;
                if(AccionIntentosExclusiva < 3){
                    std::cout << "   -> Has confrontado al Gigante de Hierro\n   -> Sus punios gigantes comienzan a tambalear de la furia.\n";
                } else std::cout << "   -> La seguridad en si mismo ha bajado.\n   -> Ahora, eres un digno oponente.\n";
                break;
            case UI.OpcActuar::Particular:
                if(AccionIntentosEspecial >= 2){
                    std::cout << "   -> Has apagado al Gigante de Hierro!\n   -> La muralla se sume en una profunda siesta.\n";
                    SetEsPerdonable(true);
                    Ataque = 0;
                } else {
                    std::cout << "   -> La valentia que tienes para intentar algo asi sin que este distraido es increible.\n"
                                "   -> La muralla no se lo tomo muy bien.\n";
                    if(Energia > 0) {
                        std::cout << "   -> Su ataque ha aumentado en 5%!!!\n";
                        Ataque *= 1.05f;
                        SetEnergia(-50);
                    }
                }
                break;
            default: break;
        }
    } else std::cout << "   -> No tiene energia.\n";
}

float BossIronGiant::Atacar() {
    AtaqueRandom = 1+rand()%3;
    if(!GetEsPerdonable()){
        switch(AtaqueRandom){
            case 1: 
                std::cout << "   -> El Gigante de Hierro Cierra sus punios y te ataca directamente al pecho.\n";
                return Ataque;
                break;
            case 2: 
                std::cout << "   -> La gran muralla plateada dio un pisoton frente tuyo!\n   -> La onda de choque volco hacia atras!\n"
                                "   -> Por suerte, estuviste lo suficientemente lejos para no quedar aplastado.\n";
                return Ataque*0.7f;
                break;
            case 3:
                std::cout << "   -> Sin previo aviso, el Gigante lanza una rafaja de rayos laceres a tu direccion.\n"
                                "   -> Aunque lograste cubrirte con una roca, las quemaduras aun dejaron marcas.\n";
                return Ataque*1.1f;
                break;
            default: break;
        }
    } else std::cout << "   -> ...\n";
    return 0;
}

std::string BossIronGiant::ImprimirActos() const { 
    return "3: " + GetAccionNombre() + "  |  4: " + GetAccionExclusivaNombre() + "  |  5: " + GetAccionParticularNombre();
}