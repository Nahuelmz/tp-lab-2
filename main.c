#include <stdio.h>
#include <stdlib.h>
#include "libreria.h"
#include "strings.h"
#include "ctype.h"
#include <conio.h>


int main()
{
    if(cargaInicial)
    {

        int opcion=0, repetir=0;
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
                altaUsuario(archiUsu, arregloUsuActivos);
                repetir=1;
                break;
            case 2:
                loginUser();
                repetir=1;
                break;
            case 3:
                loguinadm();
                repetir=1;
                break;
            default:
                exit(1);
            }
        }
        while(repetir==1);
    }
    else
        printf("Error en la carga inicial de archivos");

        return 0;
}
