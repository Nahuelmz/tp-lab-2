#include <stdio.h>
#include <stdlib.h>
#include "libreria.h"
#include "string.h"
#include "ctype.h"
#include <conio.h>





//***********************************************************************************************************************************//
//                                                  FUNCIONES DE SUBMENUES / LOGIN
//***********************************************************************************************************************************//

void loguinadm()
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
        menuAdmin();
    }
    else
    {
        printf("Login incorrecto \n");
        system("pause");
    }
}

void loginUser()
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
    printf("\n\tINGRESE SU NOMBRE PASSWORD\n\n");
    fflush(stdin);
    gets(passaux);
    login=validacionPass(arregloUsuActivos, nombreaux, passaux);
    if(login==1)
    {
        menuUsuario(nombreaux);
    }
    else
    {
        printf("Login incorrecto \n");
        system("pause");
    }
}


void menuUsuario(char nombreUsuario[])
{


    int opcion=0, id=0,repetir=0;

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
            consultaUsuario(arregloUsuActivos, nombreUsuario);
            repetir=1;
            break;

        case 2:
            subMenuListados();
            break;

        case 3:
            stPelicula auxPeli=verPelicula(); ///Revisar funciones ABM peliculas
            if(auxPeli)
            {
                cargarPeliAUser(arregloUsuActivos, nombreUsuario, crearNodoPeli(auxPeli)); ///Verificar validaciones
            }
            repetir=1;
            break;

        case 4:

            break;

        default:
            exit(1);
        }
    }
    while(repetir==1);
}


void menuAdmin()
{

    int opcion=0,repetir=0;
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
            menuAdminPelis();
            repetir=1;
            break;

        case 2:
            menuAdminUsuarios();
            repetir=1;
            break;

        default:
            exit(1);
        }
    }
    while(repetir==1);
}


void menuAdminPelis()
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
            mostrarPeliParaModif();
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

void menuAdminUsuarios()
{

    int opcion=0, repetir=0;
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
            altaUsuario();
            repetir=1;
            break;

        case 2:
            bajaUsuario();
            repetir=1;
            break;

        case 3:
            mostrarUserParaModif();
            repetir=1;
            break;

        case 4:
            consultaUsuarioAdmin();
            repetir=1;
            break;

        case 5:
            listadoUsuarios();
            repetir=1;
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


int menumodif()//Menu para administrador para seleccion de campo a modificar
{
    int resp;

    do
    {

        system("CLS");
        printf("\n\n\n\t INGRESE EL CAMPO A MODIFICAR \n\n\t[1]- Nombre:\n\t[2]- Password:\n\t");
        printf("[3]- Anio Nacimiento:\n\t[4]- Genero:\n\t[5]- Pais:\n\t[6]- Estado en la base:\n\t[0]- Salir\n\t");
        scanf("%i", &resp);

    }
    while (0>resp && resp <6);

    return resp;
}

int menuModifPelis()//Menu para administrador para seleccion de campo a modificar
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
