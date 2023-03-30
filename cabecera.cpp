#include <cabecera.h>



/* Abrimos el archivo, lo recorremos caracter por caracter y
por ultimo retornamos la variable acumuladora*/
string lectura (string nombre)
{
    char a;
    fstream archivo;
    string texto = "";
    unsigned long long tamano_texto = 0;
    archivo.open(nombre, ios_base::in| ios_base::binary| ios_base::ate); //abrimos el archivo en modo lectura
    //comprobamos si el archivo si abrio
    if (archivo.is_open()){
        tamano_texto=archivo.tellg();
        archivo.seekg(0);
        for(unsigned long long i=0;i<tamano_texto;i++){
            archivo.get(a);
            texto+= a;
        }
    }
    else{
            cout<<"El archivo no se pudo abrir, lo mas probable es que no exista"<<endl;

        }
    archivo. close(); // cerramos el archivo
    return texto;
}

/*caracter_binario resibe un string con el texto que tenia el archivo que leimos con la funcion
 * lectura, sacamos su longitud con (length) para iterar hasta el final,cramos una copia del
 * texto, con vector usamos la notacion de base 2 para convertir a binario,
 * iteramos para crear los byte dependiendo si es mayor o menor a la posicion del vector,
 * lo pasamos a un acumulador y por ultimo lo retornamos
*/
string caracter_binario (string texto)
{
    //unsigned char k = 200;
    //cout<<int (k);
    unsigned long long  longitud_texto = texto.length();
    string binario = "";
    char letra;
    for (int i =0; i<longitud_texto;i++)
    {
        string copia= "";
        letra = texto [i];
        unsigned char num = letra, vector[8] = {128,64,32,16,8,4,2,1};

        for (int j=0; j <8;j++)
        {
            if (num >= vector [j])
            {
                copia = copia + '1';
                num -= vector[j];
            }
            else
                copia = copia + '0';
        }
        binario = binario + copia;
    }
    return binario;
}

//   el siguiente paso es codificar ese binario

/*para codificar usamos 2 metodos.
 *           METODO 1:
primero separamos todo el binario en grupos de n bits y
los negamos, luego contamos la cantidad de 1s y 0s para hacer los siguientes cambios
Si hay igual cantidad de 1s y 0s se invierte cada bit del grupo.
Si hay mayor cantidad de 0s se invierte cada 2 bits.
Si hay mayor cantidad de 1s se invierte cada 3 bits.
Ejemplo. Si se ingresa 4 y el archivo contiene AbCd.
El archivo en binario sería:
0100 0001 0110 0010 0100 0011 0110 0100
El archivo codificado sería:
1011 0100 0011 1101 0001 0110 1001 1011
*/
string codificacion (string texto, int metodo ,int semilla)
{
    string codificado = "";
    if (metodo == 1){   cout << "Metodo de codificacion 1.\n";
        string auxiliar = "";
        int repeticiones =  texto.length()/ semilla;
        int aguja = semilla,cantidad_ceros=0, cantidad_unos= 0;
        auxiliar = texto.substr(0,semilla);// tomo la primera linea con la longitud de el numero ingresado por el usuario
        for (int k=0; k<semilla ; k++){// ciclo que cuenta los 1 y 0 en cadena auxiliar del primer bloque y lo niega
            if (auxiliar [k]== '1')
                cantidad_unos++;
            if (auxiliar [k] == '0')
                cantidad_ceros++;
        }
        for (int i = 0; i < repeticiones; i++){ //for principal
            if (i>1)
            {
                cantidad_ceros=0, cantidad_unos= 0;
                // ciclo que cuenta los 1 y 0 en cadena auxiliar
                string cantidad = texto.substr((semilla*(i-1)),semilla);
                for (int k=0; k<semilla ; k++)
                {
                    if (cantidad [k]== '1')
                        cantidad_unos++;
                    if (cantidad [k] == '0')
                        cantidad_ceros++;
                }
            }
            //Si hay igual cantidad de 1s y 0s se invierte cada bit del grupo.
            if (cantidad_unos == cantidad_ceros || i == 0){
                for (int j = 0; j<semilla ; j++ ){
                    if (auxiliar [j] == '1')
                        auxiliar [j]= '0';
                    else if(auxiliar [j] == '0')
                        auxiliar [j] = '1';
                }
            } // if cantida_unos == cantidad_ceros
            // Si hay mayor cantidad de 0s se invierte cada 2 bits.
            else  if  (cantidad_ceros >cantidad_unos ){ // j = 1, 3, 5, 7, 9 .....
                for (int j = 1; j<semilla ; j=j+2){
                    if (j % 2 != 0){ //al cambiar cada 2 bits se estarian cambiando las posiciones impares de auxiliar
                        if (auxiliar [j] == '1')
                            auxiliar [j]= '0';
                        else if(auxiliar [j] == '0')
                            auxiliar [j] = '1';
                    }
                }
            } // if cantidad_ceros >cantidad_unos
            // Si hay mayor cantidad de 1s se invierte cada 3 bits
            else if (cantidad_unos > cantidad_ceros){ // else
                for (int j = 2; j<semilla; j=j+3 ){ // j = 2, 5, 8, 11, 15
                    if (auxiliar [j] == '1')
                        auxiliar [j]= '0';
                    else if(auxiliar [j] == '0')
                        auxiliar [j] = '1';
                }
            } //if cantidad_unos>cantidad_ceros
            codificado = codificado + auxiliar;
            auxiliar = "";
            auxiliar= texto.substr(aguja, semilla); // me muevo en el texto
            aguja = aguja+semilla;
        } // for repeticiones
    } // metodo 1
    /*               METODO 2
     recibimos el binario y los separamos en bloques de n bits. Cada bit dentro de un grupo se
     desplaza una posición, de manera que el primer bit del grupo codificado corresponde al
     último bit del grupo sin codificar, el segundo bit codificado corresponde al primero sin
     codificar y así sucesivamente hasta que el último corresponde al penúltimo sin codificar.
     Ejemplo: si se ingresa 4 y el archivo contiene AbCd.
     El archivo en binario sería:
     0100 0001 0110 0010 0100 0011 0110 0100
     El archivo codificado sería:
     0010 1000 0011 0001 0010 1001 0011 0010
     */
///*
    if (metodo == 2){cout << "***** Metodo de codificacion 2. *****\n";
        int repeticiones = texto.length()/ semilla,aguja = semilla;
        string auxiliar = "",copia;
        char inicio ;
        auxiliar = texto.substr(0,semilla);
// ciclo que se mueve por todo el texto tomando una cadena auxiliar de longitud semilla (ingresada por el usurio, numero de particiones )
        for (int i = 0; i< repeticiones;i++){
            copia = auxiliar;
            inicio = copia[semilla-1];
// ciclo que cambia el orden de cadena auxiliar
            for (int j = 0; j<= semilla-1;j++){
                auxiliar [j+1]=copia[j]; // 1 0 _ 2 1 _ 3 2  linea que realiza el cambio en los caracteres
                if (j==0){
                    auxiliar [0]= inicio; }
            }
            codificado = codificado + auxiliar;
            auxiliar = "";
            auxiliar = texto.substr(aguja, semilla);
            aguja = aguja+semilla;
            inicio = auxiliar [semilla-1];
        }
    } //metodo 2

//    */

    return codificado;
}

//          siguiente paso como decodificar

/*para decodificar usamos las reglas de 2 los metodos de codificacion al archivo que ya
 esta codificado en consecuencia este vuelve a su estado natural
*/
string decodificacion (string texto, int metodo, int semilla)
{
    string decodificado = "";
    if (metodo == 1)
    {
        cout << "***** Metodo de decodificacion 1. *****\n\n";
        string auxiliar = "";
        int repeticiones =  texto.length()/ semilla;
        int aguja = semilla,cantidad_ceros=0, cantidad_unos= 0;
        auxiliar = texto.substr(0,semilla);  cout << "auxiliar"<<auxiliar<<endl;
        for (int i = 0; i < repeticiones; i++)
        { //for principal
            if (cantidad_unos == cantidad_ceros || i == 0)
            {
                for (int j = 0; j<semilla ; j++ )
                    {
                        if (auxiliar [j] == '1')
                            auxiliar [j]= '0';
                        else if(auxiliar [j] == '0')
                            auxiliar [j] = '1';
                    }
                } // if cantida_unos == cantidad_ceros
            else  if  (cantidad_ceros >cantidad_unos )
            {
                for (int j = 1; j<semilla ; j=j+2)
                    {
                        if (auxiliar [j] == '1')
                            auxiliar [j]= '0';

                        else if(auxiliar [j] == '0')
                            auxiliar [j] = '1';
                    }
                } // if cantidad_ceros >cantidad_unos
            else if (cantidad_unos > cantidad_ceros) // else
            {
                for (int j = 2; j<semilla; j=j+3 )
                    {
                        if (auxiliar [j] == '1')
                            auxiliar [j]= '0';
                        else if(auxiliar [j] == '0')
                            auxiliar [j] = '1';
                    }
                } //if cantidad_unos>cantidad_ceros
                cantidad_ceros=0, cantidad_unos= 0;
                // ciclo que cuenta los 1 y 0 en cadena auxiliar
                for (int k=0; k<semilla ; k++)
                {
                    if (auxiliar [k]== '1')
                        cantidad_unos++;
                    if (auxiliar [k] == '0')
                        cantidad_ceros++;
                }
                decodificado = decodificado + auxiliar;
                auxiliar = "";
                auxiliar= texto.substr(aguja, semilla);
                aguja = aguja+semilla;
            } // for repeticiones
        } // if metodo == 1

        if (metodo == 2)
        {
            string auxiliar = "",copia="";
            int repeticiones =  texto.length()/ semilla;
            int aguja = semilla;
            auxiliar = texto.substr(0,semilla);
            copia = auxiliar;
            for (int i = 0; i < repeticiones; i++)  {
                copia = auxiliar;
                for (int j = 0; j<semilla;j++){
                    if (j != semilla-1)
                        auxiliar[j] = copia [j+1];
                    if (j == semilla-1)
                        auxiliar[j] = copia[0];
                }
                decodificado = decodificado + auxiliar;
                auxiliar = "";
                auxiliar= texto.substr(aguja, semilla);
                aguja = aguja+semilla;
            }//for principal metodo 2
        }
        return decodificado;
    }

//                 convertir los binarios a caracter
/*para convertir binarios a caracteres
*/
string binario_caracter (string texto)
{
    string auxiliar="",texto_caracter= "";  // 01000001011000100100001101100100 A: 65, b:98, C:67, d:100
    int semilla = 8, repeticiones =  texto.length()/ semilla, aguja = semilla, vector []= {128,64,32,16,8,4,2,1};
    auxiliar = texto.substr(0,semilla);
    for (int i = 0; i < repeticiones; i++){ //for principal
        int resultado=0;
        for (int j=0; j<8; j++) // 0100 0001 65   64+1 = 65
        {
            if (auxiliar[j]== '1')
                resultado = resultado+vector [j];
        }
        auxiliar = "";
        auxiliar = texto.substr(aguja, semilla);
        aguja = aguja + semilla;
        char caracter = resultado;
        texto_caracter= texto_caracter + caracter ;
    } // for repeticiones

    return texto_caracter;
}






void escritura (string nombre, string texto)
{
fstream escribir;
escribir.open(nombre,ios::out | ios::binary);

escribir.write(texto.c_str(),texto.length());
}




void menu_codificacion (){
    int metodo=0,semilla=0; string nombre="",texto="";
    system("cls");
    cout << "***** CODIFICACION *****\n"<<"Problema 1"<<endl;
    cout << "Ingrese nombre de texto a codificar:"<<endl;
    cin>>nombre;
    cout << "Ingrese numero de particiones:"<<endl;
    cin >> semilla;
    texto = lectura(nombre);
    texto = caracter_binario(texto);
    cout<<"seleccione una opcion \n"<<endl;
    cout<<"1) Codificacion metodo 1."<<endl;
    cout<<"2) Codificacion metodo 2."<<endl;
    cin >> metodo;
    texto = codificacion ( texto, metodo , semilla);
    texto = binario_caracter(texto);
    escritura(nombre,texto);
}

void menu_decodificacion (){
    int metodo=0,semilla=0; string nombre="",texto="";string verificacion = "";
    system("cls");
    cout << "***** DECODIFICACION *****\n"<<"Problema 1"<<endl;
    cout << "Ingrese nombre de texto.txt a decodificar:"<<endl;
    cin>>nombre;
    cout << "Ingrese numero de particiones:"<<endl;
    cin >> semilla;
    cout << "Ingrese metodo de decodificacion:"<<endl;
    cin >> metodo;
    texto = lectura(nombre);
    texto = caracter_binario(texto);
    texto = decodificacion ( texto, metodo,  semilla);
    texto = binario_caracter(texto);
    escritura(nombre,texto);
}

void menu_app(){
    string sudo="sudo.txt",nombre_archivo_usuario="usuario.txt";

    int opcion=1;
    while (opcion!=0)
    {
        int veri = 0;
        string archivo_sudo="", archivo_usuario="";
        cout << "***** APLICACION *****\n\n"<<endl;
        cout<<"seleccione una opcion \n"<<endl;
        cout<<"1) Inicio Administrador."<<endl;
        cout<<"2) Inicio Usuario."<<endl;
        cout<< "0) Salir.\n";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            cout << "ADMINISTRADOR\n";
            archivo_sudo = lectura(sudo);
            archivo_sudo = caracter_binario(archivo_sudo);
            archivo_sudo = decodificacion(archivo_sudo,2,4);
            archivo_sudo = binario_caracter(archivo_sudo);
            veri = inicio_sesion(archivo_sudo);

            if (veri == -1)
                cout << "usuario y contrasena errada.\n";

            if (veri != -1)
            {
                int opcion1 = 1;
                while (opcion1 !=0 ){
                    cout << "********* BIENVENIDO ADMINISTRADOR*********\n";
                    cout << "1) Ingresar nuevo usuario.\n";
                    cout << "0) Salir.\n";
                    string dato = "",nuevo = "";
                    cin >> opcion1;

                    switch (opcion1)
                    {
                    case 1:
                        cout << "Ingresar Cedula:\n";
                        cin>>dato;  dato = dato +',';
                        int verificacion = 0;
                        archivo_usuario = lectura(nombre_archivo_usuario);
                        archivo_usuario = decodificacion(archivo_usuario,2,4);
                        archivo_usuario = binario_caracter(archivo_usuario);

                        verificacion = archivo_usuario.find(dato);
                        if (verificacion == -1)
                        {
                            nuevo = dato;
                            cout << "ingrese clave y saldo separados por (,).\n";
                            cin>> dato;
                            nuevo = nuevo + dato +'.'+'\n';

                            archivo_usuario = archivo_usuario + nuevo;
                            archivo_usuario = caracter_binario(archivo_usuario);
                            archivo_usuario = codificacion(archivo_usuario,2,4);
                            escritura(nombre_archivo_usuario,archivo_usuario);

                        }//(verificacion != -1)

                        else if (verificacion != -1)
                            cout << "usuario ya se encuentra registrado.\n";
                        break;

                        /* default:
                cout << "la opcion no es valida.\n";
                break;*/

                    }//switch (opcion1)

                } // while opcion1 != 0

            }//if veri != -1
            break;

        case 2:
            /*se lee archivo usuarios.txt y se guarda en variable archivo_usuario, luego se decodifica el archivo_usuario con
             * metodo 2 y 4 particiones, archivo_usuario decodificado se pasa a caracteres, en este se busca verificacion
             * (usuario y contrasena ingresados) pertenescan a un usuario registrado,  veri me dice si el dato verificacion esta en el archivo_usuario
             * si esta se inicia sesion.
             */
            cout << "********* USUARIO ********* \n";
            archivo_usuario = lectura(nombre_archivo_usuario);
            archivo_usuario = decodificacion(archivo_usuario,2,4);
            archivo_usuario = binario_caracter(archivo_usuario);

            int veri = 0;
            string usuario="",contrasena="",verificacion = "";
            cout << "Ingrese nombre de usuario:\n";
            cin >> usuario;
            cout << "Ingrese contrasena:\n";
            cin >> contrasena;
            verificacion = usuario +','+ contrasena + ',';

            veri = archivo_usuario.find(verificacion);

            cout << archivo_usuario<<endl;

            if (veri == -1)
                cout << "usuario y contrasena errada.\n";
            if (veri != -1)
            {
                int eso = archivo_usuario.length()-verificacion.length();
                string datos_usuario,datos_antes_de_usuario="",datos_despues_de_usuario="",saldo_char;
                datos_usuario = archivo_usuario.substr(veri, eso) ;
                eso =  datos_usuario.find('.');
                datos_usuario = archivo_usuario.substr(veri,eso);
                datos_antes_de_usuario = archivo_usuario.substr(0,veri);
                datos_despues_de_usuario = archivo_usuario.substr(veri+eso,archivo_usuario.length()-(veri+eso));
                int saldo_int;
                saldo_int = datos_usuario.find(contrasena);
                saldo_int = saldo_int + contrasena.length();
                saldo_char = datos_usuario.substr(saldo_int+1);
                saldo_int = stoi (saldo_char);
                saldo_int = saldo_int -1000;

                int opcion1=1;
                while (opcion1 !=0){
                    cout << "\n********* BIENVENIDO  "<<usuario <<" *********\n";
                    cout << " 1. Consultar saldo.\n 2. Retirar dinero.\n 3. salir.\n";
                    cin>> opcion1;
                    switch (opcion1)
                    {
                    case 1:
                        cout << " 1. Consultar saldo.\n\n";
                        cout << "su saldo es:"<< saldo_int;

                        saldo_char = to_string (saldo_int);
                        datos_usuario = usuario + ','+contrasena+','+saldo_char;
                        archivo_usuario = datos_antes_de_usuario + datos_usuario + datos_despues_de_usuario;
                        archivo_usuario = caracter_binario(archivo_usuario);
                        archivo_usuario = codificacion(archivo_usuario,2,4);
                        escritura(nombre_archivo_usuario,archivo_usuario);

                        break;

                    case 2:
                        cout << "2. Retirar dinero.";
                        int retiro;
                        cout << "ingrese cantidad de dinero que desea retirar:\n";
                        cin >> retiro;
                        if (retiro>saldo_int)
                            cout << "No se puede realizar retiro \n Saldo insuficiente\n";

                        else if (retiro < saldo_int){
                            saldo_int = saldo_int - retiro;
                            saldo_int = saldo_int-1000; //presio de transaccion
                            cout << "Saldo:" << saldo_int<<endl;


                            saldo_char = to_string (saldo_int);
                            datos_usuario = usuario + ','+contrasena+','+saldo_char;
                            archivo_usuario = datos_antes_de_usuario + datos_usuario + datos_despues_de_usuario;
                            archivo_usuario = caracter_binario(archivo_usuario);
                            archivo_usuario = codificacion(archivo_usuario,2,4);
                            escritura(nombre_archivo_usuario,archivo_usuario);
                        }
                        break;

                    case 3:
                        opcion1 = 0;
                        break;

                    default:
                        cout <<"La opcion ingresada no es valida\n";
                        break;

                    } //switch

                }//  (opcion1 !=0)

            }//(veri != -1)
            break;

            /* default:
            cout <<"La opcion ingresada no es valida\n";
            break;*/
        } //switch
    } // while pricipal
}

int  inicio_sesion(string texto)
{
    int veri = 0;
    string usuario,contrasena,verificacion = "";
    cout << "Ingrese nombre de usuario:\n";
    cin >> usuario;
    cout << "Ingrese contrasena:\n";
    cin >> contrasena;
    verificacion = usuario +','+ contrasena + '\n';
    veri = texto.find_last_of(verificacion);

    string sudo = "admin1,123\nadmin2,123\nadmin3,123\nadmin4,123";
    if (sudo == texto)
        cout << "son iguales siiii"<<endl;
        cout << veri << endl;
    return veri;
}








