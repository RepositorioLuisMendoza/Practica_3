#include <cabecera.h>
#include <fstream>
using namespace std;



/*

void escribir_texto()
{
    ofstream texto;
    texto.open("Prueba.txt",ios::out);//Abrir el archivo
    if (texto.fail()){
        texto<<"No se puede abrir este texto"<<endl;
        exit(1);

    }

    texto<<"Hola mi nombre es prueba de texto fdnvjkegfcuyqgeucbgewryuvgfeywrfbgyuerg ";
    texto.close();
}

void leer_texto()
{
    ifstream archivo;
    ofstream salida;
    string texto;


    archivo.open("Prueba.txt",ios::in);//Abrimos el archivo de texto


    if (archivo.fail())
    {
        cout<<"No se puede abrir este archivo: Lo mas probable es que no exista"<<endl;//verificar que existe
        exit(1);
    }

    while (!archivo.eof())//mientras no sea el final del archivo
    {
    getline(archivo,texto);
    cout<<texto<<endl;
    }
    archivo.close();

}

void conver_binary()

{
    int bit;
       int divisor=128;
       char caracter;
       cout<<"ingrese el caracter que quiere convertir a binario"<<endl;
       cin>>caracter;
       for (int i = 7;i>=0;i--)
       {
           if (caracter>=divisor)
           {
               bit=1;
               cout<<bit;
               caracter=caracter-divisor;

           }

           else
           {
               bit=0;
               cout<<bit;

           }
       divisor=divisor/2;

       }

}

*/

int bynarioo()

{
       int bit;
       char arreglo[]={"chetooo"};
       int n= sizeof(arreglo) / sizeof(arreglo[0]);

       for (int i = 0;i<n;i++)
       {
           int divisor=128;
           char c=arreglo[i];
          for (int j=7;j>=0;j--)
           {
                if (c>=divisor)
                {
                  bit=1;
                  cout<<bit;
                  c=c-divisor;

                }

                else
                {
                    bit=0;
                    cout<<bit;

                }
               divisor=divisor/2;

            }
       }

}

