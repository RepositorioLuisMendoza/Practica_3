#include <cabecera.h>

string lectura_ (string& nombre);


int main()
{
///*

    int opcion1 = 1;
    while (opcion1 != 0)
    {
        system("cls");
        cout<<"***** Practica 3 *****\n"<<endl;
        cout<<"seleccione una opcion \n"<<endl;
        cout<<"1) Codificacion."<<endl;
        cout<<"2) Decodificacion."<<endl;
        cout<<"3) Aplicacion. "<<endl;
        cout<<"\n Presione 0 para salir"<<endl;
        cin>>opcion1;

        switch (opcion1)
        {
        case 1:
            menu_codificacion();
            break;

        case 2:
            menu_decodificacion ();
            break;

        case 3:
            menu_app();
            break;


        default:
            cout <<"La opcion ingresada no es valida\n";
            break;

        } //switch
    }//while opcion1


//*/
}



