#ifndef LIBRERIA_H_INCLUDED
#define LIBRERIA_H_INCLUDED
#define ARCHIUSU "usuarios.dat"
#define ARCHIPELI "peliculas.bin"
#define ARCHIPELISUSU "pelisxusu.dat"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "ctype.h"
#include <conio.h>
#include <windows.h>


// ***** ESTRUCTURAS BASICAS *****

typedef struct stUsuario
{
    int admin;
    int idUsuario;
    char nombreUsuario[15];
    char genero;
    char pais[20];
    int pass[2][5];
    int anioNacimiento;
    int eliminado;
} stUsuario;

typedef struct stPelicula
{
    int idPelicula;
    char nombrePelicula[30];
    char director[30];
    char genero[20];
    char pais[20];
    int anio;
    int valoracion;
    int pm;
    int eliminado;
} stPelicula;

typedef struct nodoListaPelicula
{
    stPelicula p;
    struct nodoListaPelicula * sig;
} nodoListaPelicula;

typedef struct stCelda
{
    stUsuario usr;
    nodoListaPelicula * listaPelis;
} stCelda;

typedef struct nodoArbolPelicula
{
    stPelicula p;
    struct nodoArbolPelicula * izq;
    struct nodoArbolPelicula * der;
} nodoArbolPelicula;

typedef struct stPelisVistas
{
    int idPeliVista;
    int idUsuario;
    int idPelicula;
} stPelisVistas;

///*************************************************************************************************************************************

// FUNCIONES DE VALIDACION
int validarLongPass(char pass[]); // Chequea si la contrasenia supera los 10 caracteres
int validarUserExiste(char archiUsu[], char nombreUsuario[]); // Chequea si el nombre de usuario ya existe al momento del alta
int validarTipoAlfanumerico(char cadena[]); // Devuelve 1 si el par�metro pasado es cadena ALFANUMERICA, 0 si no lo es
int validarTipoChar(char cadena[]);  // Devuelve 1 si el par�metro pasado es cadena de caracteres, 0 si no lo es
int validacionPass(stCelda arregloUsuActivos[], int validos, char nombre[], char pass[]); // //Funcion de validacion de password ingresado por usuario a traves de desencriptacion de matriz codificada - Retorna true or false
int validacionPassAdmin(char pass[]);//No se pasa por parametro el nombre del administrador ya que estos poseen un solo nombre de usuario - Funcion de validacion de password ingresado por administrador a traves de desencriptacion de matriz codificada - Retorna true or false
int validarPeliExiste(char nombrePeli[]);
int validarUsuExisteArrayId(int id, stCelda*arregloUsuActivos, int validos);
int validarUsuActivo(int id, stCelda*arregloUsuActivos, int validos);


// FUNCION DE CARGA INICIAL
int cargaInicial();
void menuPrincipal();

// FUNCIONES QUE TRABAJAN SOBRE USUARIOS

//void altaUsuario(char archiUsu[], stCelda arregloUsuActivos[]); // Da de alta a nuevos usuarios, invocando a las funciones pedidoDatosUsuario, validarUserExiste, AsignarId
//void bajaUsuario(char archiUsu[]); // Modifica el campo "eliminado" con un 1 para indicar verdadero
//void mostrarUserParaModif(char archiUsu[]);//Modificacion de usuario para administrador
//void mostrarUser(char archiUsu[], char nombreUsuario[]);//Se Muestra info almacenada al Usuario
void encriptacionPass(char pass[], int mEncriptada[2][5]); //Funcion para encriptacion de password
void productoDeMatrices(int Mat[2][2],int Pass[2][5],int Prod[2][5]); //Funcion para Multiplicacion de Matrices
void desencriptacionPass(int mEncriptada[2][5], char pass[]);//Desencripta el pass para mostrarlo
//void mostrarArrayUsuarios(stUsuario array[], int validos);//Muestra los datos de usuarios por pantalla
//int cargarArrayUsuarios(char archiUsu[], stUsuario array[]);//Se pasan los datos de usuarios a un arreglo y devuelve la cantidad de registros almacenados(validos)
//void listadoUsuarios(char archiUsu[]);  //Se Muestra Listado de Usuarios al Admin
//void cargarIdPeliAUser(int id, char nombreUsuario[], char archiUsu[]);
//void consultaUsuarioAdmin(char archiUsu[]);//Se Muestra info por ID al Admin
//void consultaUsuario(char archiUsu[], char nombreUsuario[]);//Se Muestra info por Nombre al Usuario


// FUNCIONES QUE TRABAJAN SOBRE PELICULAS
void altaPelicula();
void bajaPelicula();
void mostrarPeliParaModif(nodoArbolPelicula*ArbolPelis);
void consultaPeliAdmin();
void insertar(stPelicula arregloPelis[], int posicion);
int cargarArregloPeliculas(stPelicula arregloPelis[]);
void ordenarGenero();
void ordenarTitulo();
void ordenacionSeleccion(stPelicula arregloPelis[], int validosPelis);
int posicionMenor(stPelicula arregloPelis[], int pos, int validosPelis);
int validarPeliExiste(char nombrePelicula[]);

// FUNCIONES DE SUBMENUES // Menu principal en main
void menuUsuario(stUsuario);
void menuAdmin();
void menuAdminPelis();
void menuAdminUsuarios(stCelda* arregloUsuActivos, int validos);
void subMenuListados();
void loginUser(stCelda* arregloUsuActivos, int validos);
void loguinadm(stCelda* arregloUsuActivos, int validos, nodoArbolPelicula*ArbolPelis);
void menumodif(char archiUsu[],stCelda* arregloUsuActivos, int validos); // Menu de modificaci�n de usuarios
int menuModifPelis(nodoArbolPelicula*ArbolPelis); //Menu para administrador para seleccion de campo a modificar


// FUNCIONES AUXILIARES //

void PelisxUsuarioArchivoToADL(stCelda arregloUsu[], int idUsuario, int posicion,nodoArbolPelicula * ArbolPelis);//Carga de Peliculas vistas por usuario a arreglo de listas
void actualizarPelisVistas(stCelda arregloUsuActivos[], int validos);//Carga de peliculas vistas a archivo
void mostrarPeliculas(char archiPeli[]); // Muestra los datos ingresados para ir verificando el funcionamiento del programa
//void mostrarPass(int M[f][c], int f, int c); //Funcion para mostrar matrices por pantalla (utilizada para verificacion de procesos)
void mostrarArregloPelis(stPelicula arregloPelis[], int validosPelis); // Usada para ver por pantalla y verificar el funcionamiento de funciones
int PelisVistasTotales(stCelda arregloUsuActivos[], int validos);
int cantRegistrosTotales();

// ***** FUNCIONES DE LISTAS ******

nodoListaPelicula* inicLista();
nodoListaPelicula* crearNodoPeli(stPelicula Peli);
nodoListaPelicula* agregarNodoPpio(nodoListaPelicula* listaPelis, nodoListaPelicula* nuevoNodo);
nodoListaPelicula* buscarUltimoNodo(nodoListaPelicula* listaPelis);
nodoListaPelicula* agregarNodoFinal(nodoListaPelicula* listaPelis, nodoListaPelicula* nuevoNodo);
nodoListaPelicula* agregarNodoEnOrden(nodoListaPelicula* listaPelis, nodoListaPelicula* nuevoNodo);
void imprimirNodoPelis(stPelicula nodoPeli);
void mostrarNodoPelis(nodoListaPelicula* listaPelis);
nodoListaPelicula* borrarPeliPorId(nodoListaPelicula*listaPelis, int id);

// ***** FUNCIONES DE ARBOLES ******
nodoArbolPelicula * inicArbol();
nodoArbolPelicula * crearNodoArbol(stPelicula Pelicula);
nodoArbolPelicula * insertaNodoArbol(nodoArbolPelicula * Arbol,stPelicula Pelicula);
void preOrder(nodoArbolPelicula*Arbol);
void inOrder(nodoArbolPelicula*Arbol);
void postOrder(nodoArbolPelicula*Arbol);
nodoArbolPelicula*buscarPeliculaID(nodoArbolPelicula*Arbol,int id);
nodoArbolPelicula*borrarNodoArbolPeli(nodoArbolPelicula*Arbol,stPelicula P);

// ***** FUNCIONES TP2 PELICULAS ******
stPelicula verPelicula();
void cargarPeliAUser(stCelda arregloUsuActivos[],int validos, char nombreUsuario[],nodoListaPelicula* Peli);
int validarPeliExiste(char nombrePeli[]);
int buscarPelixNombre(nodoArbolPelicula* ArbolPelis, char PeliBuscada[]);
void modificarPeliEnArbol(nodoArbolPelicula * ArbolPelis,stPelicula PeliculaToModificar);


// ***** FUNCIONES DE TP2 USUARIOS *****
int cantUsuariosActivos(char archiUsu[]); // Cuenta la cantidad inicial de usuarios activos en el archivo
int cantUsuariosInactivos(char archiUsu[]); // Cuenta la cantidad inicial de usuarios inactivos en el archivo
int cantUsuariosTotales(char archiUsu[]); // Cuenta la cantidad inicial de usuarios totales en el archivo
stCelda* cargarArchiUsuToArreglo(char archiUsu[], stCelda*arregloUsuActivos, int *validos); // Pasa los registros activos del archivo al arreglo
stCelda* altaUsuarios(char archiUsu[], stCelda*arregloUsuActivos, int *validos); // Sesi�n de alta de usuarios: se ingresan los datos al arreglo y se persisten en el archivo
void bajaUsuario(char archiUsu[], stCelda*arregloUsuActivos, int validos); // Modifica el campo "Eliminado" del usuario buscado en el arreglo y se persiste en el archivo
void imprimirUsuarioConPass(stUsuario); // TP 2: Imprime en pantalla los datos del/los usuario/s pasado/s por par�metro - CON PASSWORD P/USUARIO
void imprimirUsuarioSinPass(stUsuario); // TP 2: Imprime en pantalla los datos del/los usuario/s pasado/s por par�metro - SIN PASSWORD P/ADMIN
void mostrarUsuariosActivos(); // Muestra lista de usuarios activos con sus respectivas pel�culas
int buscarPosicionUsuario(char nombreUsuario[], stCelda*arregloUsuActivos, int validos); // Retorna la posicion en el arreglo del usuario buscando por nombre de usuario
int buscarPosUsuarioPorId(int id, stCelda*arregloUsuActivos, int validos); // Retorna la posicion en el arreglo del usuario buscando por el ID del usuario
void consultarUsuario(); // Muestra por pantalla los datos del usuario consultado por ID o por nombre
int modificarUsuario(char archiUsu[], stCelda*arregloUsuActivos, int validos); // Solicita el id del usuario y verifica si existe. De existir, continua con el menu "menumodif"
int cambiarNombreUsu(char archiUsu[], int id, int pos, stCelda*arregloUsuActivos); // Funci�n invocada por el menu "menumodif" para efectuar el cambio que solicita la misma
int cambiarPassUsu(char archiUsu[], int id, int pos, stCelda*arregloUsuActivos);// Funci�n invocada por el menu "menumodif" para efectuar el cambio que solicita la misma
int cambiarAnioUsu(char archiUsu[], int id, int pos, stCelda*arregloUsuActivos);// Funci�n invocada por el menu "menumodif" para efectuar el cambio que solicita la misma
int cambiarGeneroUsu(char archiUsu[], int id, int pos, stCelda*arregloUsuActivos);// Funci�n invocada por el menu "menumodif" para efectuar el cambio que solicita la misma
int cambiarPaisUsu(char archiUsu[], int id, int pos, stCelda*arregloUsuActivos);// Funci�n invocada por el menu "menumodif" para efectuar el cambio que solicita la misma
int cambiarEstadoUsu(char archiUsu[], int id, int pos, stCelda*arregloUsuActivos);// Funci�n invocada por el menu "menumodif" para efectuar el cambio que solicita la misma
int cambiarPermisosUsu(char archiUsu[], int id, int pos, stCelda*arregloUsuActivos);// Funci�n invocada por el menu "menumodif" para efectuar el cambio que solicita la misma
int validarUsuExisteNombre(char nombre[], stCelda*arregloUsuActivos, int validos); // Funci�n que valida si el usuario existe en el arreglo recibiendo como par�metro el nombre de usuario


#endif // LIBRERIA_H_INCLUDED