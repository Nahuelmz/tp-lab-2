#ifndef LIBRERIA_H_INCLUDED
#define LIBRERIA_H_INCLUDED

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
    char nombrePelicula[60];
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


// FUNCIONES QUE TRABAJAN SOBRE USUARIOS

void altaUsuario(char archiUsu[], stCelda arregloUsuActivos[]); // Da de alta a nuevos usuarios, invocando a las funciones pedidoDatosUsuario, validarUserExiste, AsignarId
void bajaUsuario(char archiUsu[]); // Modifica el campo "eliminado" con un 1 para indicar verdadero
void mostrarUserParaModif(char archiUsu[]);//Modificacion de usuario para administrador
void mostrarUser(char archiUsu[], char nombreUsuario[]);//Se Muestra info almacenada al Usuario
void encriptacionPass(char pass[], int mEncriptada[2][5]); //Funcion para encriptacion de password
void productoDeMatrices(int Mat[2][2],int Pass[2][5],int Prod[2][5]); //Funcion para Multiplicacion de Matrices
void desencriptacionPass(int mEncriptada[2][5], char pass[]);//Desencripta el pass para mostrarlo
void mostrarArrayUsuarios(stUsuario array[], int validos);//Muestra los datos de usuarios por pantalla
int cargarArrayUsuarios(char archiUsu[], stUsuario array[]);//Se pasan los datos de usuarios a un arreglo y devuelve la cantidad de registros almacenados(validos)
void listadoUsuarios(char archiUsu[]);  //Se Muestra Listado de Usuarios al Admin
void cargarIdPeliAUser(int id, char nombreUsuario[], char archiUsu[]);
void consultaUsuarioAdmin(char archiUsu[]);//Se Muestra info por ID al Admin
void consultaUsuario(char archiUsu[], char nombreUsuario[]);//Se Muestra info por Nombre al Usuario


// FUNCIONES QUE TRABAJAN SOBRE PELICULAS
void altaPelicula();
void bajaPelicula();
void mostrarPeliParaModif();
void consultaPeliAdmin();
void insertar(stPelicula arregloPelis[], int i);
int cargarArrayPeliculas(stPelicula arregloPelis[]);
void ordenarGenero ();
void ordenarTitulo();
int verPelicula();
void ordenacionSeleccion(stPelicula arregloPelis[], int validos);
int posicionMenor(stPelicula arregloPelis[], int pos, int validos);


// FUNCIONES DE VALIDACION
int validarLongPass(char pass[]); // Chequea si la contrasenia supera los 10 caracteres
int validarUserExiste(char archiUsu[], char nombreUsuario[]); // Chequea si el nombre de usuario ya existe al momento del alta
//int validarTipoAlfanumerico(char cadena[]); // Devuelve 1 si el parámetro pasado es cadena ALFANUMERICA, 0 si no lo es
//int validarTipoChar(char cadena[]);  // Devuelve 1 si el parámetro pasado es cadena de caracteres, 0 si no lo es
int validacionPass(stCelda arregloUsuActivos[], char nombre[], char pass[]); // //Funcion de validacion de password ingresado por usuario a traves de desencriptacion de matriz codificada - Retorna true or false
int validacionPassAdmin(char pass[]);//No se pasa por parametro el nombre del administrador ya que estos poseen un solo nombre de usuario - Funcion de validacion de password ingresado por administrador a traves de desencriptacion de matriz codificada - Retorna true or false
int validarPeliExiste(char nombrePeli[]);


// FUNCIONES DE SUBMENUES // Menu principal en main
void menuUsuario(char  nombreUsuario[]);
void menuAdmin();
void menuAdminPelis();
void menuAdminUsuarios();
void subMenuListados();
void loginUser();
void loguinadm();
int menumodif();//Menu para administrador para seleccion de campo a modificar
int menuModifPelis(); //Menu para administrador para seleccion de campo a modificar


// FUNCIONES AUXILIARES //

void PelisxUsuarioArchivoToADL(stCelda arregloUsu[], int idUsuario, int posicion);//Carga de Peliculas vistas por usuario a arreglo de listas
void actualizarPelisVistas(stCelda arregloUsuActivos[], int validosUsuActivos, stCelda arregloUsuInactivos[], int validosUsuInactivos);//Carga de peliculas vistas a archivo
void mostrarUsuarios(char archiUsu[]); // Muestra los datos ingresados para ir verificando el funcionamiento del programa
void mostrarPeliculas(char archiPeli[]); // Muestra los datos ingresados para ir verificando el funcionamiento del programa
void mostrarPass(int f,int c,int M[f][c]); //Funcion para mostrar matrices por pantalla (utilizada para verificacion de procesos)
void mostrarArrayPeliculas(stPelicula array[], int validos); // Usada para ver por pantalla y verificar el funcionamiento de funciones


// ***** FUNCIONES DE LISTAS ******

nodoListaPelicula* inicLista();
nodoListaPelicula* crearNodoPeli(stPelicula Peli);
nodoListaPelicula* agregarNodoPpio(nodoListaPelicula* listaPelis, nodoListaPelicula* nuevoNodo);
nodoListaPelicula* buscarUltimoNodo(nodoListaPelicula* listaPelis);
nodoListaPelicula* agregarNodoFinal(nodoListaPelicula* listaPelis, nodoListaPelicula* nuevoNodo);
nodoListaPelicula* agregarNodoEnOrden(nodoListaPelicula* listaPelis, nodoListaPelicula* nuevoNodo);
void imprimirNodoPelis(nodoListaPelicula* nodoPeli);
void mostrarNodoPelis(nodoListaPelicula* listaPelis);
nodoListaPelicula* borrarPeliPorId(nodoListaPelicula*listaPelis, int id);

// ***** FUNCIONES DE ARBOLES ******
nodoArbolPelicula * inicArbol();
nodoArbolPelicula * crearNodoArbol(stPelicula Pelicula);
nodoArbolPelicula * insertaNodoArbol(nodoArbolPelicula * Arbol,stPelicula Pelicula);
void preOrder(nodoArbolPelicula*Arbol);
void inOrder(nodoArbolPelicula*Arbol);
void postOrder(nodoArbolPelicula*Arbol);
nodoArbolPelicula*buscarPeliculaID(nodoArbolPelicula*Arbol,stPelicula Pelicula);
nodoArbolPelicula*borrarNodoArbolPeli(nodoArbolPelicula*Arbol,stPelicula P);

// ***** FUNCIONES TP2 PELICULAS ******
stPelicula verPelicula();
int buscarPelixNombre(char PeliBuscada[]);

// ***** FUNCIONES DE TP2: USUARIOS *****
int cantUsuariosActivos(char archiUsu[]);
int cantUsuariosInctivos(char archiUsu[]);
int cantUsuariosTotales(char archiUsu[]);
int cargarArchivoUsuariosActivosToArreglo(char archiUsu[], stCelda*);
stCelda* cargarArchivoUsuariosInactivosToArreglo(char archiUsu[]);
int calcularTamanioArrayUsuarios(stCelda arreglo[]);



#endif // LIBRERIA_H_INCLUDED
