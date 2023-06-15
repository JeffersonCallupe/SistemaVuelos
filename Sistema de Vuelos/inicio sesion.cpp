#include <cstdlib>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include "stdio.h"

using namespace std;
 //SISTEMA DE REGISTRO DE USUARIOS 

//CONSTANTES
const char FINCAD = char(0);
const int MAXCAD = 20;

const char SP = ' ';
char contrasena;
int i;
int contador=0;

//TIPOS
typedef char TCadena[MAXCAD+1]; // MAXCAD caracteres + FINCAD
struct Persona_R{
 TCadena PASS;
};


// CABECERA DE PROCEDIMIENTOS Y FUNCIONES
void pausa();
void finalizar_programa();
void Ingresar_PASS(Persona_R &p);
void confirmar_PASS(Persona_R &p);

// Algoritmos de Manejo de Ficheros de Texto
void insertarPersonaTXT(TCadena nombreFichero, Persona_R p);
void EscribePersonaFicheroTXT(ofstream &fichero, Persona_R p);
void verificar_existencia_fichero(TCadena nombreFichero);
void verificar_existencia_de_usuario(TCadena nombreFichero);
void verificar_contrasena(TCadena nombreFichero,Persona_R &password);

void menuIniciarSesion();
void selecOpcionInicio(TCadena nombreFichero,Persona_R &password,Persona_R &p);


// PROGRAMA PRINCIPAL
int main(){
	Persona_R p;
    Persona_R password;
    TCadena nombre_usuario_registrado;
	selecOpcionInicio(nombre_usuario_registrado,password,p);
	return 0;
}


void menuIniciarSesion(){
	cout << "\t\t\t==============================================" << endl;
	cout << "\n\t\t\t      **** SISTEMA DE VUELOS AEREOS ****" << endl;
	cout << "\n\t\t\t==============================================" << endl;
	cout << "\t\t1. Iniciar sesion" << endl;
	cout << "\t\t2. Registrarse" << endl;
	cout << "\t\t0. Salir del Programa." << endl;	
}

void selecOpcionInicio(TCadena nombreFichero,Persona_R &password,Persona_R &p){
	TCadena nombre_usuario_registrado;
	char opcion;
	int num;
	bool fin,encontrado;
	int opc_iniciar;
	do{
	menuIniciarSesion();
	cout <<"\nDigite una opcion:  ";cin >> opc_iniciar;
	if((opc_iniciar<0)||(opc_iniciar>2)){        
		try {        system("cls");		            
		             cout<<"\n\n\t\t\t | ERROR. OPCION INCORRECTA |\n\n\n\n";		                
		             system("pause");
		             system("cls"); 		                
		    }
		    catch(...){
				cout << "\n UN ERROR HA OCURRIDO " << endl; 
				} 
		}  
	
	switch(opc_iniciar){
		
		case 1: {
				cout << "\nDigite su Nombre de Usuario:     ";cin >> nombre_usuario_registrado; //INGRESAR COMO USUARIO
				verificar_existencia_fichero(nombre_usuario_registrado);
				verificar_contrasena(nombre_usuario_registrado,password);	//confirmar_PASS(password);
				cout<<"\n\tBIENVENIDO"<<endl;
				break;
		}
	
		case 2:{
				cout<<"\nEscriba su nombre de Usuario:    ";cin >> nombre_usuario_registrado;//REGISTRO
				verificar_existencia_de_usuario(nombre_usuario_registrado);
				Ingresar_PASS(p);
				insertarPersonaTXT(nombre_usuario_registrado,p);
				system("cls");
				system("pause");
			break;
		} 	
	}
	}while(opc_iniciar!=0);
}


// IMPLEMENTACIÓN DE PROCEDIMIENTOS Y FUNCIONES

void Ingresar_PASS(Persona_R &p){
	cout << "Escriba su contraseña:                 " ;cin >> p.PASS;
	cout<<"\nSE HA REGISTRADO CORRECTAMENTE"<<endl; Sleep(2500); 
}
void confirmar_PASS(Persona_R &password){
	cout << "Escriba su contraseña:                " ;cin >> password.PASS;
}

// Algoritmos de Manejo de Ficheros de Texto
void insertarPersonaTXT(TCadena nombreFichero, Persona_R p){
	ofstream out;
	out.open(nombreFichero,ios::app);
	// Abro el fichero para añadir
	if (out.bad()){
		// El fichero no existe ... lo creo
		out.open(nombreFichero);
	}	
	EscribePersonaFicheroTXT(out,p);
	out.close();
}

void EscribePersonaFicheroTXT(ofstream &fichero,Persona_R p){
fichero << p.PASS << SP;
}

void verificar_existencia_fichero(TCadena nombreFichero) {
	
	ifstream archivo(nombreFichero); 
    if (!archivo){    
          cout<<"\n\tUsuario no registrado\n"<<endl; Sleep(1000);    
          system("cls");
          main();
    }
    else {
		cout<<"\n\tNombre de Usuario CORRECTO\n"<<endl;Sleep(1000);
		} 
}

void verificar_existencia_de_usuario(TCadena nombreFichero){
    ifstream archivo(nombreFichero); 
    if (!archivo){
        cout<<"\n\tNombre de Usuario disponible\n"<<endl;Sleep(1000);
    }
    else {
        cout<<"\n\tNombre de Usuario no disponible. Vuelva a intentarlo"<<endl; Sleep(1000); 
		system("cls");
          main();     
    }   
}

void verificar_contrasena(TCadena nombreFichero,Persona_R &password){
	string cadena;
	string contrase;
	cout << "Escriba su PASS:                 " ;cin >> password.PASS;
	ifstream fichero(nombreFichero,ios::in);	
	   
	   while(!fichero.eof()) {                 
	      fichero >> cadena;   
	      //cadena = strstr (fichero,"simple");
	  }
	  if(cadena!=password.PASS){
	  cout<<"\nContraseña incorrecta. INTENTELO DE NUEVO\n"<<endl;Sleep(2000);
	  fichero.close();
	  }
	if(cadena==password.PASS){
	cout<<"\n\t\tContraseña correcta. \n"<<endl; Sleep(1000);
	}
	system("cls");
	system("pause");
}



