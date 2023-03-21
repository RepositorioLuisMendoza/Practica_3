#include <cabecera.h>
#include <fstream>
#include <iostream>

using namespace std;

string leer_texto()
{
    char texto[]={};
    string nombre;
    cout<<"ingrese un nombre"<<endl;
    cin>>nombre;
    unsigned long long tam;
    char *p;
    fstream text;
    text.open(nombre.c_str(), ios_base::in | ios_base::ate | ios_base::binary);

    if (!text.is_open()){cout<<"no se pudo abrir el archivo"<<endl;}

    else{
            tam=text.tellg(); //tamaño de texto abierto en ate
            p = new char [tam];
            text.seekg(0); //posiciona el cursor en el inicio de el texto
            text.read(p,tam); // leer texto
            for (int i=0;i<tam;i++)
                {
                //  cout<<*(p+i);
                    texto[i]={p[i]};
                }

        //cout<<texto<<endl;
        text.close();

        }
return texto;
}


string caracter_binario (string& texto)
{
    int longitud_texto = texto.length();
    string binario="";
    string bit="";
    for (int i = 0;i<longitud_texto;i++)
        {
            int divisor=128;
            char c=texto[i];
            for (int j=7;j>=0;j--)
               {
                    if (c>=divisor)
                       {
                            bit='1';
                            binario+=bit;
                        //  cout<<bit;
                            c=c-divisor;
                        }
                    else
                        {
                            bit='0';
                            binario+=bit;
                         // cout<<bit;
                        }
                   divisor=divisor/2;
                }
        }
    return binario;
}



string codificacion_met1(string& binario)
{

    int semilla=0;
    int can_ceros=0;
    int can_unos=0;
    string auxiliar="";
    string codificado="";
    cout<<"Ingrese su valor semilla"<<endl;
    cin>>semilla;
    int repeticiones=binario.length()/semilla;
    int apuntador=semilla;
    auxiliar = binario.substr(0,semilla);
    //contamos todos los 1 y 0 que hay en el primer bloque
    for (int q=0;q<semilla;q++)
        {
            if (auxiliar[q]=='1')
                {
                    can_unos++;
                }
            if (auxiliar[q]=='1')
                {
                    can_ceros++;
                }
        }
    for (int i = 0; i < repeticiones; i++){ //for principal
                if (i>1)
                {
                    can_ceros=0, can_unos= 0;
                    // ciclo que cuenta los 1 y 0 en cadena auxiliar
                    string cantidad = binario.substr((semilla*(i-1)),semilla);
                    for (int k=0; k<semilla ; k++)
                    {
                        if (cantidad [k]== '1')
                            can_unos++;
                        if (cantidad [k] == '0')
                            can_ceros++;
                    }
                }
                if (can_unos == can_ceros || i == 0)
                {
                    for (int j = 0; j<semilla ; j++ )
                    {
                        if (auxiliar [j] == '1')
                            auxiliar [j]= '0';
                        else if(auxiliar [j] == '0')
                            auxiliar [j] = '1';
                    }
                } // if cantida_unos == cantidad_ceros
                else  if  (can_ceros >can_unos )
                {
                    for (int j = 1; j<semilla ; j=j+2)
                    {
                        if (j % 2 != 0)
                        {
                            if (auxiliar [j] == '1')
                                auxiliar [j]= '0';
                            else if(auxiliar [j] == '0')
                                auxiliar [j] = '1';
                        }
                    }
                } // if cantidad_ceros >cantidad_unos
                else if (can_unos > can_ceros) // else
                {
                    for (int j = 2; j<semilla; j=j+3 )
                    {
                        if (auxiliar [j] == '1')
                            auxiliar [j]= '0';
                        else if(auxiliar [j] == '0')
                            auxiliar [j] = '1';
                    }
                } //if cantidad_unos>cantidad_ceros
                codificado = codificado + auxiliar;
                auxiliar = "";
                auxiliar= binario.substr(apuntador, semilla);
                apuntador = apuntador+semilla;
            } // for repeticiones
    return codificado;
        } // metodo 1













