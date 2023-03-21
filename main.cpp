#include <iostream>
#include <cabecera.h>
#include<fstream>

using namespace std;

int main()
{
    string texto,binario,codi;

    texto=leer_texto();
    cout<<texto<<endl;
    binario=caracter_binario(texto);
    cout<<binario<<endl;
    cout<<'\n'<<'\n'<<'\n'<<endl;
    codi=codificacion_met1(binario);
    cout<<codi<<endl;
return 0;
}
