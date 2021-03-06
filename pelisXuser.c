#include "libreria.h"


//void PelisxUsuarioArchivoToADL(stCelda arregloUsu[], int idUsuario, int posicion) //Carga de peliculas vistas a arreglo de listas de peliculas
//{
//
//    FILE*archi;
//    archi=fopen(archiPelisUsu, "rb");
//
//    if(archi)
//    {
//        fseek(archi, 0, SEEK_SET);
//        while(!feof(archi))
//        {
//            stPelisVistas aux;
//            fread(&aux, sizeof(stPelisVistas), 1, archi);
//            if(!feof(archi))
//            {
//                if(aux.idUsuario==arregloUsu[posicion].usr.idUsuario)
//                {
//                    nodoArbolPelicula*auxPeli=buscarPelicula(aux.idPelicula);
//                    arregloUsu[posicion].listaPelis=agregarNodoFinal(arregloUsu[posicion].listaPelis, crearNodoPeli(auxPeli->p));
//                }
//                fread(&aux, sizeof(stPelisVistas), 1, archi);
//            }
//        }
//        fclose(archi);
//    }
//    else
//    {
//        printf("No se pudo abrir el archivo de usuarios");
//    }
//}

void actualizarPelisVistas(char archipeusu[], stCelda arregloUsuActivos[], int validosUsuActivos, stCelda arregloUsuInactivos[], int validosUsuInactivos) //Pasaje de peliculas vistas a archivo
{
    FILE*archi;
    archi=fopen(archipeusu, "wb");
    int i=0, idLocal=1;

    if(archi)
    {

        stPelisVistas aux;
        for(i=0; i<validosUsuActivos; i++)
        {
            while(arregloUsuActivos[i].listaPelis)
            {
                aux.idUsuario=arregloUsuActivos[i].usr.idUsuario;
                aux.idPelicula=arregloUsuActivos[i].listaPelis->p.idPelicula;
                aux.idPeliVista=idLocal;
                fwrite(&aux, sizeof(stPelisVistas), 1, archi);
                arregloUsuActivos[i].listaPelis=arregloUsuActivos[i].listaPelis->sig;
                idLocal++;

            }
        }
        for(i=0; i<validosUsuInactivos; i++)
        {
            while(arregloUsuInactivos[i].listaPelis)
            {
                aux.idUsuario=arregloUsuInactivos[i].usr.idUsuario;
                aux.idPelicula=arregloUsuInactivos[i].listaPelis->p.idPelicula;
                aux.idPeliVista=idLocal;
                fwrite(&aux, sizeof(stPelisVistas), 1, archi);
                arregloUsuInactivos[i].listaPelis=arregloUsuInactivos[i].listaPelis->sig;
                idLocal++;
            }
        }
        fclose(archi);
    }
    else
    {
        printf("No se pudo abrir el archivo de usuarios");
    }
}
