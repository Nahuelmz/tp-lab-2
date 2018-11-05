#include "libreria.h"

void menuPrincipal()
{
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
            altaUsuarios();
            break;
        case 2:
            loginUser();
            break;
        case 3:
            loguinadm();
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
    if(validarUsuExisteNombre(nombreaux))
{
    printf("\n\tINGRESE SU PASSWORD\n\n");
        fflush(stdin);
        gets(passaux);
        login=validacionPass(arregloUsuActivos, nombreaux, passaux);
        int pos=buscarPosicionUsuario(nombreaux);
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
        printf("Nombre de usuario incorrecto\n");
        system("pause");

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

//        case 2:
//            subMenuListados();
//            break;

//        case 3:
//            stPelicula auxPeli=verPelicula(); ///Revisar funciones ABM peliculas
//            if(auxPeli)
//            {
////                cargarPeliAUser(arregloUsuActivos, nombreUsuario, crearNodoPeli(auxPeli)); ///Verificar validaciones
//            }
//            break;

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

//        case 1:
//            menuAdminPelis();
//            break;

        case 2:
            menuAdminUsuarios();
            break;

        default:
            exit(1);
        }
    }
    while(repetir==1);
}
//
//
////void menuAdminPelis()
////{
////
////    int opcion=0,repetir=0;
////    do
////    {
////        system("cls");
////        printf("\n");
////        printf("\n*****************************************************");
////        printf("\n\tMENU DE GESTION DE PELICULAS");
////        printf("\n*****************************************************");
////        printf("\n");
////        printf("\n\t 1) ALTA DE PELICULAS");
////        printf("\n\t 2) BAJA DE PELICULAS");
////        printf("\n\t 3) MODIFICACION DE PELICULAS");
////        printf("\n\t 4) CONSULTA DE PELICULAS");
////        printf("\n\t 5) LISTADOS DE PELICULAS");
////        printf("\n\t 0) SALIR DEL PROGRAMA");
////        printf("\n\n\t INGRESE SU OPCION: ");
////        scanf("%i", &opcion);
////
////        switch(opcion)
////        {
////
////        case 0:
////            repetir=0;
////            break;
////
////        case 1:
////            altaPelicula();
////            repetir=1;
////            break;
////
////        case 2:
////            bajaPelicula();
////            repetir=1;
////            break;
////
////        case 3:
////            mostrarPeliParaModif();
////            repetir=1;
////            break;
////
////        case 4:
////            consultaPeliAdmin();
////            repetir=1;
////            break;
////
////        case 5:
////            subMenuListados();
////            repetir=1;
////            break;
////
////        default:
////            exit(1);
////        }
////    }
////    while(repetir==1);
////}
//
void menuAdminUsuarios()
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
            altaUsuarios();
            break;

        case 2:
            bajaUsuario(ARCHIUSU);
            break;

        case 3:
            menumodif(ARCHIUSU);
            break;

        case 4:
            consultarUsuario();
            break;

        case 5:
            mostrarUsuariosActivos();
            system("pause");
            break;

        default:
            exit(1);
        }
    }
    while(repetir==1);
}


//void subMenuListados()
//{
//    int opcionlistados=0;
//    char control='s';
//    do
//    {
//        system("cls");
//        printf("\n");
//        printf("\n*****************************************************");
//        printf("\n\t L I S T A D O S\t\t");
//        printf("\n*****************************************************");
//        printf("\n");
//        printf("\n\t 1) ORDENADOS POR TITULO");
//        printf("\n\t 2) ORDENADOS POR GENERO");
//        printf("\n\t 0) VOLVER AL MENU ANTERIOR");
//        scanf("%i", &opcionlistados);
//
//        switch(opcionlistados)
//        {
//
//        case 1:
//
//            ordenarTitulo();
//            printf("\n\t Desea ver otro listado? s/n : \n");
//            scanf("%c", &control);
//            break;
//
//        case 2:
//
//            ordenarGenero();
//            printf("\n\t Desea ver otro listado? s/n : \n");
//            scanf("%c", &control);
//            break;
//
//        }
//
//    }
//    while(control=='s');
//}
//
//

/// MODIFICADO VALE - NO tocar por favor
void menumodif(char archiUsu[])//Menu para administrador para seleccion de campo a modificar
{
    int id=modificarUsuario(archiUsu);
    int pos=buscarPosUsuarioPorId(id);


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

        case 1:
            continuar=cambiarNombreUsu(archiUsu, id, pos);
            break;
        case 2:
            continuar=cambiarPassUsu(archiUsu, id, pos);
            break;
        case 3:
            continuar=cambiarAnioUsu(archiUsu, id, pos);
            break;
        case 4:
            continuar=cambiarGeneroUsu(archiUsu, id, pos);
            break;
        case 5:
            continuar=cambiarPaisUsu(archiUsu, id, pos);
            break;
        case 6:
            continuar=cambiarEstadoUsu(archiUsu, id, pos);
            break;
        case 7:
            continuar=cambiarPermisosUsu(archiUsu, id, pos);
            break;
        default:
            exit(1);
            break;
        }

    }
    while(resp!=0&&continuar==1);
}


//
//int menuModifPelis()//Menu para administrador para seleccion de campo a modificar
//{
//    int resp;
//
//    do
//    {
//
//        system("CLS");
//        printf("\n\n\n\t INGRESE EL CAMPO A MODIFICAR \n\n\t[1]- Nombre:\n\t[2]- Director:\n\t");
//        printf("[3]- Anio de Filmacion:\n\t[4]- Genero:\n\t[5]- Pais de origen:\n\t[6]- Valoracion:\n\t[7]- Clasificacion:\n\t[8]- Estado en catalogo:\n\t[0]- Salir\n\t");
//        scanf("%i", &resp);
//
//    }
//    while (0>resp && resp <6);
//
//    return resp;
//}


