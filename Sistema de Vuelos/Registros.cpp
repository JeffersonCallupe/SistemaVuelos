#include <cstdlib>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include "stdio.h"

using namespace std;

//Estructuras para listas

struct pasajero{
	string nombre;
	string apellido;
	string tipoDoc; //DNI - Carnet de de extranjería
	string documento;
	int edad;
	string telefono;
	struct pasajero *sgte;
	struct pasajero *ant; 	
};

struct date{
	int dia;
	int mes;
	int anio;
};

struct vuelo{
	int idVuelo;
	string destino;
	date fecha;
	int hora;
	int clase; // 0: Economica, 1: Ejecutiva, 2: Primera clase
	double precio;
	int cantBoletos;
	pasajero pasajeros;//Lista de pasajeros para un vuelo
	struct vuelo *sgte;
	struct vuelo *ant;  	
};











//Definiendo tipos de datos

typedef struct pasajero *TpPasajero;
typedef struct vuelo *TpVuelo;


// Fuciones de registro de vuelo 
TpVuelo AgregarVuelo();
void InsertarVuelo(TpVuelo &vuelo);
void mostrarVuelos(TpVuelo vuelo);






void menu();
void selecOpc(TpPasajero &listaPasajero, TpVuelo &vuelo);
TpPasajero crearNodoPasajero();
string consistenciarDocumento(string opciones, string op1, string op2);
void InsertarPasajero(TpPasajero &listaPasajero);
void mostrarListaPasajeros(TpPasajero listaPasajero);







// CONSTANTES
const char FINCAD = char(0);
const int MAXCAD = 20;

const char SP = ' ';
char contrasena;
int i;
int contador = 0;

// TIPOS
typedef char TCadena[MAXCAD + 1]; // MAXCAD caracteres + FINCAD
struct Persona_R {
    TCadena PASS;
};

// CABECERA DE PROCEDIMIENTOS Y FUNCIONES
void pausa();
void finalizar_programa();
void Ingresar_PASS(Persona_R &p);
void confirmar_PASS(Persona_R &p);
void getPassword(char* password, int maxLength);
void insertarPersonaTXT(TCadena nombreFichero, Persona_R p);
void EscribePersonaFicheroTXT(ofstream &fichero, Persona_R p);
void verificar_existencia_fichero(TCadena nombreFichero);
void verificar_existencia_de_usuario(TCadena nombreFichero);
void verificar_contrasena(TCadena nombreFichero, Persona_R &password);
void menuIniciarSesion();
void selecOpcionInicio(TCadena nombreFichero, Persona_R &password, Persona_R &p, TpPasajero &listaPasajero, TpVuelo &vuelo);

// PROGRAMA PRINCIPAL
int main() {
	TpPasajero listaPasajero=NULL;
	TpVuelo vuelo=NULL;
    Persona_R p;
    Persona_R password;
    TCadena nombre_usuario_registrado;
    selecOpcionInicio(nombre_usuario_registrado,password,p, listaPasajero, vuelo);
    return 0;
}

void menuIniciarSesion() {
    cout << "\t\t\t==============================================" << endl;
    cout << "\n\t\t\t      **** SISTEMA DE VUELOS AEREOS ****" << endl;
    cout << "\n\t\t\t==============================================" << endl;
    cout << "\t\t1. Iniciar sesion" << endl;
    cout << "\t\t2. Registrarse" << endl;
    cout << "\t\t0. Salir del Programa." << endl;
}

void selecOpcionInicio(TCadena nombreFichero, Persona_R &password, Persona_R &p, TpPasajero &listaPasajero, TpVuelo &vuelo) {
    TCadena nombre_usuario_registrado;
    char opcion;
    int num;
    bool fin, encontrado;
    int opc_iniciar;
    do {
        menuIniciarSesion();
        cout << "\nDigite una opcion:  ";
        cin >> opc_iniciar;
        if ((opc_iniciar < 0) || (opc_iniciar > 2)) {
            try {
                system("cls");
                cout << "\n\n\t\t\t | ERROR. OPCION INCORRECTA |\n\n\n\n";
                system("pause");
                system("cls");
            } catch (...) {
                cout << "\n UN ERROR HA OCURRIDO " << endl;
            }
        }

        switch (opc_iniciar) {

        case 1: {
            cout << "\nDigite su Nombre de Usuario:     ";
            cin >> nombre_usuario_registrado; // INGRESAR COMO USUARIO
            verificar_existencia_fichero(nombre_usuario_registrado);
            verificar_contrasena(nombre_usuario_registrado, password); // confirmar_PASS(password);
            Sleep(2500);
            cout<<"\n\t--------- BIENVENIDO ---------"<<endl;
			system("cls");
			system("pause");
			selecOpc(listaPasajero, vuelo);
            break;
        }

        case 2: {
            cout << "\nEscriba su nombre de Usuario:    ";
            cin >> nombre_usuario_registrado; // REGISTRO
            verificar_existencia_de_usuario(nombre_usuario_registrado);
            Ingresar_PASS(p);
            insertarPersonaTXT(nombre_usuario_registrado, p);
            system("cls");
            system("pause");
            break;
        }
        }
    } while (opc_iniciar != 0);
}


void menu(){
	system("cls");
	cout << "\t\tSISTEMA DE GESTION DE VIAJES" << endl;
	cout << "\t1. Registrar vuelo." << endl;
	cout << "\t2. Modificar vuelo." << endl;
	cout << "\t3. Mostrar vuelos programados." << endl;
	cout << "\t4. Registrar pasajero." << endl;
	cout << "\t5. Realizar reserva de vuelo." << endl;
	cout << "\t6. Reportes." << endl;
	cout << "\t0. Salir" << endl;
	cout << "Seleccione una opcion: ";
}


void selecOpc(TpPasajero &listaPasajero, TpVuelo &vuelo){
	int opcion;
	do{
		menu();
		cin >> opcion;
		system("cls");
		switch(opcion){
			case 1: {
				InsertarVuelo(vuelo);
				mostrarVuelos(vuelo);
				break;
			}	
				
			case 2:
			
				break;
			case 3:
				mostrarVuelos(vuelo);
				break;
			case 4:{
				InsertarPasajero(listaPasajero);
				mostrarListaPasajeros(listaPasajero);
				break;
			}
			case 5:
			
				break;
			case 6:
				break;
			case 0:
				break;
			default:
				cout << "Opcion no valida." << endl; 
		}
		system("pause");
	}while(opcion != 0);	
}

TpVuelo AgregarVuelo(){
 	TpVuelo nuevo = NULL;
 	nuevo = new(struct vuelo);
 	cout << "Ingresar destino:\n -> "; cin>>nuevo->destino;
	cout << "Ingresar id de vuelo:\n -> "; cin>>nuevo->idVuelo;
	cout << "Ingresar fecha:\n - Dia: "; cin>>nuevo->fecha.dia;
	cout << " - Mes: "; cin >> nuevo->fecha.mes;
	cout << " - A\xA4o: "; cin >> nuevo->fecha.anio;
	cout << "Ingresar hora de salida:\n -> "; cin>>nuevo->hora;
	cout << "Ingresar clase:\n -> "; cin>>nuevo->clase;
	cout << "Ingresar precio:\n -> "; cin>>nuevo->precio;
	cout << "Ingresar cantidad de asientos:\n -> "; cin>>nuevo->cantBoletos;
	nuevo->sgte = NULL;
 	return nuevo;
  }
  
  
//Se inserta al final, el vuelo a una lista doblemente enlazada  
void InsertarVuelo(TpVuelo &vuelo){
 	TpVuelo q = NULL, p = vuelo;
	q = AgregarVuelo();
	if(vuelo == NULL)
		vuelo = q;
	else{
		while(p->sgte != NULL)
			p = p->sgte;
		p->sgte = q;	
		q->ant=p;
	}
	
	cout << "\t\tVUELO REGISTRADO  "<<endl;	
}

void mostrarVuelos(TpVuelo vuelo){
	int i=0;
	while(vuelo != NULL){
		cout << "\n---------------------------------" << endl;
		cout<< " "<<i+1<<")  "<<vuelo->destino<<" - "<<vuelo->idVuelo<<"-"<<vuelo->fecha.dia<<"-"<<vuelo->fecha.mes <<""<< endl;
		cout<<"\t\tVUELO "<<i+1<<")"<<endl;
		cout<<"\t\tDestino"<<vuelo->destino<<endl;
		cout<<"\t\tID"<<vuelo->idVuelo<<endl;
		cout<<"\t\tFecha: "<<vuelo->fecha.dia<<"/"<<vuelo->fecha.mes<<"/"<<vuelo->fecha.anio<<endl;
		cout<<"\t\tHora de salida :"<<vuelo->hora<<endl;
		cout<<"\t\tClase: "<<vuelo->clase<<endl;
		cout<<"\t\tPrecio: "<<vuelo->precio<<endl;
		cout<<"\t\tCantidad de asientos: "<<vuelo->cantBoletos;
		cout << "---------------------------------" << endl;
		vuelo=vuelo->sgte;
		i++;
		cout<<"\n\n";	
	}
}






TpPasajero crearNodoPasajero(){
	int doc;
	TpPasajero nuevo=NULL;
	nuevo =  new (struct pasajero);
	nuevo->tipoDoc = consistenciarDocumento("Tipo de documento: ", "DNI", "Carnet de extranjeria");
	cout <<"\nIngrese el numero de su documento: "; cin >> nuevo->documento;

	cout<<"\nIngresar nombres: ";cin>>nuevo->nombre;
	fflush(stdin);
	cout<<"\nIngresar apellidos: ";cin>>nuevo->apellido;
	fflush(stdin);
	cout<<"\nIngresar edad: ";cin>>nuevo->edad;
	cout<<"\nIngresar telefono: ";cin>>nuevo->telefono;
	cout<<endl;

	nuevo->sgte=NULL;
	nuevo->ant=NULL;
	return nuevo;
}

string consistenciarDocumento(string opciones, string op1, string op2){  //Reduccion de codigo.
	string opcion;
	int op;
	do{ 
		cout << "Seleccionar " << opciones << "\n 1) "<<op1 << "\n 2)"<< op2 << "\n -> ";
		cin >> op;
		if (op != 1 && op != 2)
			cout << "Intente de nuevo. Fuera de rango" << endl;
	}while(op != 1 && op != 2);
	if (op == 1)
		opcion = op1;
	else
		opcion = op2;
		
	return opcion;
}

void InsertarPasajero(TpPasajero &listaPasajero){   //Se inserta al final mediante lista doblemente enlazada
	TpPasajero nuevo=NULL, p=listaPasajero;
	nuevo=crearNodoPasajero();
	if(listaPasajero == NULL)
		listaPasajero = nuevo;
	else{
		while(p->sgte != NULL)
				p=p->sgte;
		p->sgte = nuevo;
		nuevo->ant =p;		
	}
	
	cout<<"\t\tPASAJERO REGISTRADO"<<endl;	
	// system("pause");
}


void mostrarListaPasajeros(TpPasajero listaPasajero) {
    TpPasajero actual = listaPasajero;
    cout<<endl;
    if (actual == NULL) {
        cout << "La lista de pasajeros está vacía." << endl;
    } else {
        // Buscar el último nodo de la lista
        while (actual->sgte != NULL) {
            actual = actual->sgte;
        }
        
        cout << "Lista de Pasajeros:" << endl;
        while (actual != NULL) {
            cout << "---------------------------------" << endl;
            cout << "Tipo de documento: " << actual->tipoDoc << endl;
            cout << "Numero de documento: " << actual->documento << endl;
            cout << "Nombres: " << actual->nombre << endl;
            cout << "Apellidos: " << actual->apellido << endl;
            cout << "Edad: " << actual->edad << endl;
            cout << "Telefono: " << actual->telefono << endl;
            cout << "---------------------------------" << endl;
            actual = actual->ant; // Avanzar hacia el nodo anterior
        }
    }
    system("pause");
}
































void Ingresar_PASS(Persona_R &p) {
    cout << "Escriba su password: ";
    Sleep(1000);
    getPassword(p.PASS, MAXCAD);
    cout << endl;
    cout << "\nSE HA REGISTRADO CORRECTAMENTE" << endl;
    Sleep(2500);
}

void getPassword(char* password, int maxLength) {
    int index = 0;
    char ch;
    while (index < maxLength - 1) {
        ch = _getch(); // Lee el carácter sin mostrarlo en pantalla
        if (ch == '\r') {
            break; // Salir del bucle al presionar Enter
        } else if (ch == '\b') {
            if (index > 0) {
                // Retroceso: borrar el carácter anterior
                cout << "\b \b";
                index--;
            }
        } else {
            // Mostrar asterisco y almacenar el carácter en el arreglo de contraseñas
            cout << "*";
            password[index] = ch;
            index++;
        }
    }
    password[index] = '\0'; // Agregar el carácter de fin de cadena al final
}

void confirmar_PASS(Persona_R &password) {
    cout << "Escriba su password: ";
    getPassword(password.PASS, MAXCAD);
    Sleep(1500);
}

void insertarPersonaTXT(TCadena nombreFichero, Persona_R p) {
    ofstream out;
    out.open(nombreFichero, ios::app);
    // Abro el fichero para añadir
    if (out.bad()) {
        // El fichero no existe ... lo creo
        out.open(nombreFichero);
    }
    EscribePersonaFicheroTXT(out, p);
    out.close();
}

void EscribePersonaFicheroTXT(ofstream &fichero, Persona_R p) {
    fichero << p.PASS << SP;
}

void verificar_existencia_fichero(TCadena nombreFichero) {

    ifstream archivo(nombreFichero);
    if (!archivo) {
        cout << "\n\tUsuario no registrado\n" << endl;
        Sleep(1000);
        system("cls");
        main();
    } else {
        cout << "\n\tNombre de Usuario CORRECTO\n" << endl;
        Sleep(1000);
    }
}

void verificar_existencia_de_usuario(TCadena nombreFichero) {
    ifstream archivo(nombreFichero);
    if (!archivo) {
        cout << "\n\tNombre de Usuario disponible\n" << endl;
        Sleep(1000);
    } else {
        cout << "\n\tNombre de Usuario no disponible. Vuelva a intentarlo" << endl;
        Sleep(1000);
        system("cls");
        main();
    }
}

void verificar_contrasena(TCadena nombreFichero, Persona_R &password) {
    string cadena;
    string contrase;
    cout << "Escriba su password: ";
    getPassword(password.PASS, MAXCAD);
    ifstream fichero(nombreFichero, ios::in);

    while (!fichero.eof()) {
        fichero >> cadena;
    }
    if (cadena != password.PASS) {
        cout << "\nContraseña incorrecta. INTENTELO DE NUEVO\n" << endl;
        Sleep(2000);
        fichero.close();
    }
    if (cadena == password.PASS) {
        cout << "\n\n\t\tCPassword correcto. \n" << endl;
        Sleep(1500);
    }
    system("cls");
    system("pause");
}

