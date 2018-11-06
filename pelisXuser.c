#include "libreria.h"


void PelisxUsuarioArchivoToADL(stCelda arregloUsu[], int idUsuario, int posicion) //Carga de peliculas vistas a arreglo de listas de peliculas
{

    FILE*archi;
    archi=fopen(ARCHIPELISUSU, "rb");

    if(archi)
    {
        fseek(archi, 0, SEEK_SET);
        while(!feof(archi))
        {
            stPelisVistas aux;
            fread(&aux, sizeof(stPelisVistas), 1, archi);
            if(!feof(archi))
            {
                if(aux.idUsuario==arregloUsu[posicion].usr.idUsuario)
                {
                    nodoArbolPelicula * auxPeli=buscarPeliculaID(ArbolPelis, aux.idPelicula);
                    arregloUsu[posicion].listaPelis=agregarNodoFinal(arregloUsu[posicion].listaPelis, crearNodoPeli(auxPeli->p));
                }
                fread(&aux, sizeof(stPelisVistas), 1, archi);
            }
        }
        fclose(archi);
    }
    else
    {
        printf("No se pudo abrir el archivo de usuarios");
    }
}

void actualizarPelisVistas(stCelda arregloUsuActivos[]) //Pasaje de peliculas vistas a archivo
{
    FILE*archi;
    archi=fopen(ARCHIPELISUSU, "ab+");
    int i=0, j, idLocal, cantReg;
    arregloPelisVistas=(stPelisVistas*)malloc(sizeof(stPelisVistas)*validos); // Reserva en memoria espacio del tamaño de validos para el arreglo dinámico de peliculas vistas por usuario para luego grabarlas en el archivo
    if(archi)
    {
        idLocal=cantRegistrosTotales();//Leemos la cantidad de registros en el archivo para saber el id
        stPelisVistas aux;
        for(i=0; i<validos; i++) //recorremos el arreglo de usuarios activos para buscar peliculas que no esten grabadas
        {
            while(arregloUsuActivos[i].listaPelis)//mientras siga teniendo peliculas seguira iterando la funcion
            {
                fread(&aux, sizeof(stPelisVistas), 1, archi);
                if(!feof(archi))
                {

                    if(arregloUsuActivos[i].usr.idUsuario==aux.idUsuario)
                    {
                        if(aux.idPelicula!=arregloUsuActivos[i].listaPelis->p.idPelicula)//en caso de no estar grabadas se pasan al arreglo de peliculas vistas
                        {
                            arregloPelisVistas[j].idUsuario=arregloUsuActivos[i].usr.idUsuario;
                            arregloPelisVistas[j].idPelicula=arregloUsuActivos[i].listaPelis->p.idPelicula;
                            arregloPelisVistas[j].idPeliVista=idLocal;
                            idLocal++;
                        }
                    }
                }
                arregloUsuActivos[i].listaPelis=arregloUsuActivos[i].listaPelis->sig;//se pasa a la siguiente pelicula del mismo usuario
            }
        }
        fseek(archi, 0, 2);
        for(i=0; i<validos; i++)//pasa las nuevas peliculas vistas del arreglo al archivo
        {
            aux=arregloPelisVistas[i];
            fwrite(&aux, sizeof(stPelisVistas), 1, archi);
        }
        fclose(archi);
    }
    else
    {
        printf("No se pudo abrir el archivo de usuarios");
    }
}

int cantRegistrosTotales() // Función utilizada para contar la cantidad total de registros guardados en el archivo
{

    int cantRegistros()=0; // Variable a retornar

    FILE*archi; //Reserva de espacio en buffer

    archi=fopen(ARCHIPELISUSU, "rb"); //Apertura de archivo como solo lectura

    if(archi) // Si se pudo abrir el archivo
    {

        fseek(archi, 0, 2); // Se lleva el cursor al final del archivo para calcular desde ahí el peso del mismo

        if(ftell(archi)==0) // Si el tamaño del archivo en bytes es igual a 0, es decir si existe pero no tiene informacion
        {
            cantRegistros=1; // Se le asigna el valor 1 al primer registro
        }
        else
        {
            cantRegistros=(ftell(archi)/sizeof(stUsuario)); // Se calcula cuantos registros hay dividiendo el tamaño del archivo por el tamaño de la estructura

        }
        fclose(archi); // Se cierra el archivo
    }
    else
    {
        printf("No se pudo abrir el archivo de usuarios"); // Si no se pudo abrir el archivo se devuelve mensaje de error
    }

    return cantRegistros; // Se devuelve la cantidad de registros totales contados
}



