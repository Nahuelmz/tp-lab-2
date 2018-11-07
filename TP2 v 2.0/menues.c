#include "libreria.h"

/// OJO PASAR POR PARAMETRO TODAS LAS VARIABLES NECESARIAS


void menuPrincipal(char archiUsu[],nodoArbolPelicula*ArbolPelis)
{

    stCelda* arregloUsuActivos=NULL; // Se manejan con punteros por ser estructura dinámica
//nodoArbolPelicula* ArbolPelis; // Se manejan con punteros por ser estructura dinámica
    int validos;  // Variable utilizada para los usuarios ACTIVOS

    arregloUsuActivos= cargarArchiUsuToArreglo(archiUsu,arregloUsuActivos,&validos);

//if(cargaInicial())
//{

    int opcion=0, repetir=1;
    do
    {
        system("cls");
        printf("\n");
        printf("\n*****************************************************");
        printf("\n***\t\t	MENU PRINCIPAL  \t\t  ***");
        printf("\n*****************************************************");
        printf("\n");
        printf("\n\t 1) REGISTRO DE NUEVO USUARIO");
        printf("\n\t 2) INICIAR SESION DE USUARIO");
        printf("\n\t 3) INICIAR SESION DE ADMINISTRADOR");
        printf("\n\t 0) SALIR DEL PROGRAMA");
        printf("\n\n\t INGRESE SU OPCION: ");
        scanf("%i", &opcion);
        switch(opcion)
        {
        case 0:
            exit(1);
        case 1:
            arregloUsuActivos=altaUsuarios(archiUsu, arregloUsuActivos, &validos);
            break;
        case 2:
            loginUser(arregloUsuActivos, validos);
            break;
        case 3:
            loguinadm(arregloUsuActivos, validos, ArbolPelis);
            break;
        default:
            exit(1);
        }
    }
    while(repetir==1);
//}

//else
//    printf("Error en la carga inicial de archivos");
}


////***********************************************************************************************************************************//
////                                                  FUNCIONES DE SUBMENUES / LOGIN
////***********************************************************************************************************************************//
//
void loguinadm(stCelda* arregloUsuActivos, int validos, nodoArbolPelicula*ArbolPelis)
{
    int login=0;
    char passaux[11];
    system("cls");
    printf("\n");
    printf("\n*****************************************************");
    printf("\n\t\tLOGIN DE ADMINISTRADOR");
    printf("\n*****************************************************");
    printf("\n");
    printf("\n\tINGRESE EL PASSWORD DE ADMINISTRADOR\n\n");
    fflush(stdin);
    gets(passaux);
    login=validacionPassAdmin(passaux);
    if(login==1)
    {
        menuAdmin(arregloUsuActivos,validos,ArbolPelis);
    }
    else
    {
        printf("Login incorrecto \n");
        system("pause");
    }
}


void loginUser(stCelda*arregloUsuActivos, int validos)
{
    int login=0;
    char nombreaux[30];
    char passaux[11];
    system("cls");
    printf("\n");
    printf("\n*****************************************************");
    printf("\n\t\tLOGIN DE USUARIO");
    printf("\n*****************************************************");
    printf("\n");
    printf("\n\tINGRESE SU NOMBRE DE USUARIO\n\n");

    fflush(stdin);
    gets(nombreaux);
    if(validarUsuExisteNombre(nombreaux, arregloUsuActivos, validos))
    {
        printf("\n\tINGRESE SU PASSWORD\n\n");
        fflush(stdin);
        gets(passaux);
        login=validacionPass(arregloUsuActivos,validos, nombreaux, passaux);
        int pos=buscarPosicionUsuario(nombreaux, arregloUsuActivos, validos);
        if(login==1)
        {
            imprimirUsuarioConPass(arregloUsuActivos[pos].usr);
            system("pause");
            menuUsuario(arregloUsuActivos[pos].usr);
        }
        else
        {
            printf("Login incorrecto \n");
        }
    }
    else
    {
        printf("Nombre de usuario incorrecto\n");
        system("pause");
    }


}


void menuUsuario(stUsuario usr)
{


    int opcion=0, repetir=1;

    do
    {
        system("cls");
        printf("\n");
        printf("\n*****************************************************");
        printf("\n\t\tMENU DE USUARIO");
        printf("\n*****************************************************");
        printf("\n");
        printf("\n\t 1) VER PERFIL");
        printf("\n\t 2) LISTADOS DE PELICULAS");
        printf("\n\t 3) BUSCAR PELICULA");
        printf("\n\t 4) VER PELICULAS RECOMENDADAS");

        printf("\n\t 0) VOLVER AL MENU ANTERIOR");
        printf("\n\n\t INGRESE SU OPCION: ");
        scanf("%i", &opcion);

        switch(opcion)
        {

        case 0:
            repetir=0;
            break;

        case 1:
            imprimirUsuarioConPass(usr);
            system("pause");
            break;

        case 2:
            subMenuListados();
            break;

        case 3:
            verPelicula(usr); ///Revisar funciones ABM peliculas

            break;

        case 4:

            break;

        default:
            exit(1);
        }
    }
    while(repetir==1);
}


void menuAdmin(stCelda* arregloUsuActivos, int validos, nodoArbolPelicula*ArbolPelis)
{

    int opcion=0,repetir=1;
    do
    {
        system("cls");
        printf("\n");
        printf("\n*****************************************************");
        printf("\n\t\tMENU DE ADMINISTRADOR\t\t");
        printf("\n*****************************************************");
        printf("\n");
        printf("\n\t 1) GESTIONAR PELICULAS");
        printf("\n\t 2) GESTIONAR USUARIOS");
        printf("\n\t 0) VOLVER AL MENU ANTERIOR");
        printf("\n\n\t INGRESE SU OPCION: ");
        scanf("%i", &opcion);

        switch(opcion)
        {

        case 0:
            repetir=0;
            break;

        case 1:
            menuAdminPelis(ArbolPelis);
            break;

        case 2:
            menuAdminUsuarios(arregloUsuActivos, validos);
            break;

        default:
            exit(1);
        }
    }
    while(repetir==1);
}


void menuAdminPelis(nodoArbolPelicula * ArbolPelis)
{

    int opcion=0,repetir=0;
    do
    {
        system("cls");
        printf("\n");
        printf("\n*****************************************************");
        printf("\n\tMENU DE GESTION DE PELICULAS");
        printf("\n*****************************************************");
        printf("\n");
        printf("\n\t 1) ALTA DE PELICULAS");
        printf("\n\t 2) BAJA DE PELICULAS");
        printf("\n\t 3) MODIFICACION DE PELICULAS");
        printf("\n\t 4) CONSULTA DE PELICULAS");
        printf("\n\t 5) LISTADOS DE PELICULAS");
        printf("\n\t 0) SALIR DEL PROGRAMA");
        printf("\n\n\t INGRESE SU OPCION: ");
        scanf("%i", &opcion);

        switch(opcion)
        {

        case 0:
            repetir=0;
            break;

        case 1:
            altaPelicula();
            repetir=1;
            break;

        case 2:
            bajaPelicula();
            repetir=1;
            break;

        case 3:
            mostrarPeliParaModif(ArbolPelis);
            repetir=1;
            break;

        case 4:
            consultaPeliAdmin();
            repetir=1;
            break;

        case 5:
            subMenuListados();
            repetir=1;
            break;

        default:
            exit(1);
        }
    }
    while(repetir==1);
}

void menuAdminUsuarios(stCelda* arregloUsuActivos, int validos)
{

    int opcion=0, repetir=1;
    do
    {
        system("cls");
        printf("\n");
        printf("\n*****************************************************");
        printf("\n\tMENU DE GESTION DE USUARIOS\t\t");
        printf("\n*****************************************************");
        printf("\n");
        printf("\n\t 1) ALTA DE USUARIOS");
        printf("\n\t 2) BAJA DE USUARIOS");
        printf("\n\t 3) MODIFICACION DE USUARIOS");
        printf("\n\t 4) CONSULTA DE USUARIOS");
        printf("\n\t 5) LISTADOS DE USUARIOS");
        printf("\n\t 0) VOLVER AL MENU ANTERIOR");
        printf("\n\n\t INGRESE SU OPCION: ");
        scanf("%i", &opcion);

        switch(opcion)
        {

        case 0:
            repetir=0;
            break;

        case 1:
            altaUsuarios(ARCHIUSU, arregloUsuActivos, &validos);
            break;

        case 2:
            bajaUsuario(ARCHIUSU, arregloUsuActivos, validos);
            break;

        case 3:
            menumodif(ARCHIUSU, arregloUsuActivos, validos);
            break;

        case 4:
            consultarUsuario(arregloUsuActivos,validos);
            break;

        case 5:
            mostrarUsuariosActivos(arregloUsuActivos, validos);
            system("pause");
            break;

        default:
            exit(1);
        }
    }
    while(repetir==1);
}


void subMenuListados()
{
    int opcionlistados=0;
    char control='s';
    do
    {
        system("cls");
        printf("\n");
        printf("\n*****************************************************");
        printf("\n\t L I S T A D O S\t\t");
        printf("\n*****************************************************");
        printf("\n");
        printf("\n\t 1) ORDENADOS POR TITULO");
        printf("\n\t 2) ORDENADOS POR GENERO");
        printf("\n\t 0) VOLVER AL MENU ANTERIOR");
        scanf("%i", &opcionlistados);

        switch(opcionlistados)
        {

        case 1:

            ordenarTitulo();
            printf("\n\t Desea ver otro listado? s/n : \n");
            scanf("%c", &control);
            break;

        case 2:

            ordenarGenero();
            printf("\n\t Desea ver otro listado? s/n : \n");
            scanf("%c", &control);
            break;

        }

    }
    while(control=='s');
}



/// MODIFICADO VALE - NO tocar por favor
void menumodif(char archiUsu[],stCelda*arregloUsuActivos, int validos)//Menu para administrador para seleccion de campo a modificar
{
    int id=modificarUsuario(archiUsu, arregloUsuActivos, validos);
    int pos=buscarPosUsuarioPorId(id, arregloUsuActivos, validos);


    int resp, continuar;

    do
    {
        printf("\n\n\n\t INGRESE EL CAMPO A MODIFICAR \n\n\t[1]- Nombre:\n\t[2]- Password:\n\t");
        printf("[3]- Anio Nacimiento:\n\t[4]- Genero:\n\t[5]- Pais:\n\t[6]- Estado en la base:\n\t[7]- Nivel de permisos:\n\t[0]- Salir\n\t");
        fflush(stdin);
        scanf("%i", &resp);
    }
    while (0>resp && resp <6);

    do
    {
        switch (resp)
        {

        case 0:
            menuAdminUsuarios(arregloUsuActivos, validos);
            break;
        case 1:
            continuar=cambiarNombreUsu(archiUsu, id, pos, arregloUsuActivos);
            break;
        case 2:
            continuar=cambiarPassUsu(archiUsu, id, pos, arregloUsuActivos);
            break;
        case 3:
            continuar=cambiarAnioUsu(archiUsu, id, pos, arregloUsuActivos);
            break;
        case 4:
            continuar=cambiarGeneroUsu(archiUsu, id, pos, arregloUsuActivos);
            break;
        case 5:
            continuar=cambiarPaisUsu(archiUsu, id, pos, arregloUsuActivos);
            break;
        case 6:
            continuar=cambiarEstadoUsu(archiUsu, id, pos, arregloUsuActivos);
            break;
        case 7:
            continuar=cambiarPermisosUsu(archiUsu, id, pos, arregloUsuActivos);
            break;
        default:
            exit(1);
            break;
        }

    }
    while(resp!=0&&continuar==1);
}



int menuModifPelis(nodoArbolPelicula*ArbolPelis)//Menu para administrador para seleccion de campo a modificar
{
    int resp;

    do
    {

        system("CLS");
        printf("\n\n\n\t INGRESE EL CAMPO A MODIFICAR \n\n\t[1]- Nombre:\n\t[2]- Director:\n\t");
        printf("[3]- Anio de Filmacion:\n\t[4]- Genero:\n\t[5]- Pais de origen:\n\t[6]- Valoracion:\n\t[7]- Clasificacion:\n\t[8]- Estado en catalogo:\n\t[0]- Salir\n\t");
        scanf("%i", &resp);

    }
    while (0>resp && resp <6);

    return resp;
}


