/* Funciones referentes al ingreso, manejo de canciones y listas de reproducción de la aplicacion. Utilizando arboles binarios
*  Fecha: 30/11/2017
*  Elaborado por: John Sebastian Nieto gil
*  Elaborado por: Ricardo Andres Villalobos
*/

#define RESERVAR_MUSIC (Music *)malloc(sizeof(Music))
#define RESERVAR_LISTA (ListaReproduccion *)malloc(sizeof(ListaReproduccion))
#define RESERVAR_MEMORIA_LISTA (CancionesLista *)malloc(sizeof(CancionesLista))


//Estructura tipo arbol
struct Music
{
	int id;
	char nombre[30];
	int duracion; //En segundos
	int conteo;
	GeneroArtista* idGenero;
	GeneroArtista* idArtista;
	Music *izq, *der;
	Music* padre;
};

//Estructura tipo lista simplemente enlazada
struct CancionesLista
{
	int idMusic;
	CancionesLista* siguiente;
};

//Estructura tipo arbol
struct ListaReproduccion
{
	int id;
	int user;
	char nombre[30];;
	CancionesLista * ptrCancion;
	ListaReproduccion *izq, *der;
	ListaReproduccion* padre;
};

//Prototipo de funciones
Music *crearMusic(char [], int, GeneroArtista*, GeneroArtista*, int &, Music* );
void insertarMusic(Music *&, char [], int, GeneroArtista*, GeneroArtista*, int &, Music* );
ListaReproduccion *crearLista(char [], int, int &, ListaReproduccion* );
void insertarLista(ListaReproduccion *&, char [], int, int &, ListaReproduccion *);
Music *editarMusic(Music* &, char [], int, GeneroArtista*, GeneroArtista*, int &);
void ordenarMusic(Music *&, char [], int, GeneroArtista*, GeneroArtista*, int &, Music* );
void listarMusic(Music *);
void listarLista(ListaReproduccion *, int);
void ordenar(Music* , Music* &);
bool buscarMusic(Music* , char [], int, int &);
bool buscarMusicGeneroArtista(Music* , char [], int, int , int &);
bool nombreMusic(Music* , int );
bool agregarConteo(Music* , int );
void cancionEnLista(CancionesLista *&, int);
bool ingresarCancion(ListaReproduccion* &, Music* &, int , int);
bool listarCancionesLista(ListaReproduccion *, Music* , int );
bool eliminarCancionLista(ListaReproduccion *, int , int , int );
void eliminarListaTotal(CancionesLista *);
bool editarLista(ListaReproduccion* &, int );
void eliminar(ListaReproduccion *, int, ListaReproduccion *&);
void eliminarNodo(ListaReproduccion *, ListaReproduccion *&);
ListaReproduccion *minimo(ListaReproduccion *);
void reemplazar(ListaReproduccion *, ListaReproduccion *, ListaReproduccion *&);
void destruirNodo(ListaReproduccion *, ListaReproduccion *&);
void eliminarListaTotal(CancionesLista *);


//Crea un nuevo nodo para el arbol de canciones
Music *crearMusic(char nombre[], int duracion, GeneroArtista* artista, GeneroArtista* genero, int &id, Music* padre)
{
	Music *nuevoNodo = RESERVAR_MUSIC;
	id = id + 1;
	strcpy(nuevoNodo->nombre, nombre);
	nuevoNodo->id = id;
	nuevoNodo->duracion = duracion;
	nuevoNodo->conteo = 0;
	nuevoNodo->idArtista = artista;
	nuevoNodo->idGenero = genero;
	nuevoNodo->der = NULL;
	nuevoNodo->izq = NULL;
	nuevoNodo->padre = padre;
	return nuevoNodo;
}


//Inserta los elementos en el arbol de canciones, organizados por nombre
void insertarMusic(Music *&music, char nombre[], int duracion, GeneroArtista* artista, GeneroArtista* genero, int &id, Music* padre)
{
	char datoMusic[30];

	if(music == NULL)
	{
		Music *nuevoNodo = crearMusic(nombre, duracion, artista, genero, id, padre);
		music = nuevoNodo;
	}
	else
	{ 
		strcpy(datoMusic, music->nombre);

		if(strcmp(nombre, datoMusic) < 0)
		{
			insertarMusic(music->izq, nombre, duracion, artista, genero, id, music);
		}
		else
		{
			insertarMusic(music->der, nombre, duracion, artista, genero, id, music);
		}

			
	}
}

//Crea un nuevo nodo para el arbol de listas de reproduccion.
ListaReproduccion *crearLista(char nombre[], int loggin, int &id, ListaReproduccion* padre)
{
	ListaReproduccion *nuevoNodo = RESERVAR_LISTA;
	id = id + 1;
	strcpy(nuevoNodo->nombre, nombre);
	nuevoNodo->user = loggin;
	nuevoNodo->id = id;
	nuevoNodo->ptrCancion = NULL;
	nuevoNodo->padre = padre;
	nuevoNodo->izq = NULL;
	nuevoNodo->der = NULL;
	return nuevoNodo;
}


//Inserta los elementos en el arbol de listas de reproduccion, organizados por id
void insertarLista(ListaReproduccion *&listaReproduccion, char nombre[], int loggin, int &id, ListaReproduccion *padre)
{
	int dato;

	if(listaReproduccion == NULL)
	{
		ListaReproduccion *nuevoNodo = crearLista(nombre, loggin, id, padre);
		listaReproduccion = nuevoNodo;
	}
	else
	{ 
		dato = listaReproduccion->id;

		if(id < dato)
		{
			insertarLista(listaReproduccion->izq, nombre, loggin, id, listaReproduccion);
		}
		else
		{
			insertarLista(listaReproduccion->der, nombre, loggin, id, listaReproduccion);
		}

			
	}
}


Music *editarMusic(Music* &music, char nombre[], int duracion, GeneroArtista* artista, GeneroArtista* genero, int &id)
{
	id = id + 1;
	strcpy(music->nombre, nombre);
	music->id = id;
	music->duracion = duracion;
	music->conteo = 0;
	music->idArtista = artista;
	music->idGenero = genero;
	music->der = NULL;
	music->izq = NULL;
	return music;
}

//Ordena un nuevo arbol de canciones, ordenado por tiempo de la cancion
void ordenarMusic(Music *&music, char nombre[], int duracion, GeneroArtista* artista, GeneroArtista* genero, int &id, Music* padre)
{
	char datoMusic[30];
	int tiempo = 0;

	if(music == NULL)
	{
		Music *nuevoNodo = crearMusic(nombre, duracion, artista, genero, id, padre);
		music = nuevoNodo;
	}
	else
	{ 
		//strcpy(datoMusic, music->nombre);
		tiempo = music->duracion;

		if(duracion < tiempo)
		{
			ordenarMusic(music->izq, nombre, duracion, artista, genero, id, music);
		}
		else
		{
			ordenarMusic(music->der, nombre, duracion, artista, genero, id, music);
		}

			
	}
}

//Lista las canciones del arbol en inorden
void listarMusic(Music *arbol){
	if(arbol == NULL)
	{
		return;
	}
	else
	{
		listarMusic(arbol->izq);
		printf("\nId: %d", arbol->id);
		printf("\nNombre: %s", arbol->nombre);
		printf("Tiempo: %d\n", arbol->duracion);
		printf("Genero: %s", arbol->idGenero->nombre);
		printf("Artista: %s", arbol->idArtista->nombre);
		printf("Agregada: %d\n", arbol->conteo);
		listarMusic(arbol->der);
	}
}

//Muestra las listas de reproduccion por usuario
void listarLista(ListaReproduccion *arbol, int loggin){
	if(arbol == NULL)
	{
		return;
	}
	else
	{
		listarLista(arbol->izq, loggin);
		if(arbol->user == loggin)
		{
			printf("\nId: %d", arbol->id);
			printf("\nNombre: %s", arbol->nombre);
		}
		listarLista(arbol->der, loggin);
	}
}

//Recorre el arbol ordenado por nombre, para ordenar el nuevo por tiempo
void ordenar(Music* music, Music* &nuevoOrden)
{
	if(music == NULL)
	{
		return;
	}
	else
	{
		ordenar(music->izq, nuevoOrden);
		ordenarMusic(nuevoOrden, music->nombre, music->duracion, music->idArtista, music->idGenero, music->id, NULL);
		ordenar(music->der, nuevoOrden);
	}
	
}

//Lista las canciones que coinciden por el nombre de la cancion
bool buscarMusic(Music* music, char nombre[], int longitud, int &contador)
{
	
	if(music == NULL)
	{
		return contador;
	}
	else
	{

		if(strncmp(music->nombre, nombre, longitud) == 0)
		{
			contador =+ 1;
			printf("\nId: %d", music->id);
			printf("\nNombre: %s", music->nombre);
			printf("Tiempo: %d\n", music->duracion);
			printf("Genero: %s", music->idGenero->nombre);
			printf("Artista: %s", music->idArtista->nombre);
			printf("Agregada: %d\n", music->conteo);

			//Continuar con la busqueda de más posibles coincidencias
			if(music->izq != NULL)
			{
				buscarMusic(music->izq, nombre, longitud, contador);
			}
			else
			{
				buscarMusic(music->der, nombre, longitud, contador);
			}
			
		}
		else if(strncmp(music->nombre, nombre, longitud) > 0)
		{
			buscarMusic(music->izq, nombre, longitud, contador);
		}
		else
		{
			buscarMusic(music->der, nombre, longitud, contador);
		}
			
	}

}

//Buscar canciones por el genero o artista, el recorrido se realiza en sentido preOrden
bool buscarMusicGeneroArtista(Music* music, char nombre[], int longitud, int opcion, int &contador)
{
	int compara;
	
	if(music == NULL)
	{
		return contador;
	}
	else
	{
		switch(opcion)
		{

		case 1:
			compara = strncmp(music->idArtista->nombre, nombre, longitud);
			break;

		case 2:
			compara = strncmp(music->idGenero->nombre, nombre, longitud);
			break;
		}

		if(compara == 0)
		{
			contador += 1;
			printf("\nId: %d", music->id);
			printf("\nNombre: %s", music->nombre);
			printf("Tiempo: %d\n", music->duracion);
			printf("Genero: %s", music->idGenero->nombre);
			printf("Artista: %s", music->idArtista->nombre);
			printf("Agregada: %d\n", music->conteo);
			
		}

		buscarMusicGeneroArtista(music->izq, nombre, longitud, opcion, contador);
		buscarMusicGeneroArtista(music->der, nombre, longitud, opcion, contador);

			
	}

}


//Muestra los datos de una cancion que coinciden con el id recibido por la funcion,
//el recorrido es en sentido inOrden
bool nombreMusic(Music* music, int idMusic)
{
	
	if(music == NULL)
	{
		return false;
	}
	else
	{
		nombreMusic(music->izq, idMusic);
		if(music->id == idMusic)
		{
			printf("\nId: %d", music->id);
			printf("\nNombre: %s", music->nombre);
			printf("Tiempo: %d\n", music->duracion);
			printf("Genero: %s", music->idGenero->nombre);
			printf("Artista: %s", music->idArtista->nombre);
			printf("Agregada: %d\n", music->conteo);
			
		}
		nombreMusic(music->der, idMusic);	
		
			
	}

}

//Aumente el contado de veces que se agrego la cancion a una lista de reproduccion
bool agregarConteo(Music* music, int idMusic)
{
	if(music == NULL)
	{
		return false;
	}
	else
	{
		agregarConteo(music->izq, idMusic);
		if(music->id == idMusic)
		{
			music->conteo++;
			return true;
		}
		agregarConteo(music->der, idMusic);	
			
	}

}

//Crea un nuevo nodo para cada id de cancion en la lista de reproduccion
void cancionEnLista(CancionesLista *&lista, int idCancion)
{
	CancionesLista* nuevoNodo = RESERVAR_MEMORIA_LISTA;
	nuevoNodo->idMusic = idCancion;

	if(lista == NULL)
	{
		lista = nuevoNodo;
		nuevoNodo->siguiente = NULL;
	}
	else
	{
		nuevoNodo->siguiente = lista;
		lista = nuevoNodo;
	}
}

//Ingresar una nueva cancion a la lista de reproduccion
bool ingresarCancion(ListaReproduccion* &listaReproduccion, Music* &music, int idLista, int idCancion)
{
	
	if(listaReproduccion == NULL)
	{
		return true;
	}
	else
	{

		ingresarCancion(listaReproduccion->izq, music, idLista, idCancion);
		if(listaReproduccion->id == idLista)
		{
			cancionEnLista(listaReproduccion->ptrCancion, idCancion);
			agregarConteo(music, idCancion);
		}
		ingresarCancion(listaReproduccion->der, music, idLista, idCancion);
			
	}

}

//Listar las canciones de la lista de reproduccion
bool listarCancionesLista(ListaReproduccion *listaReproduccion, Music* music, int idMusic)
{

	if(listaReproduccion == NULL)
	{
		return false;
	}
	else
	{
		
		if(listaReproduccion->id == idMusic)
		{
			CancionesLista* aux = listaReproduccion->ptrCancion;
			while(aux != NULL)
			{
				nombreMusic(music, aux->idMusic);
				aux = aux->siguiente;
			}
			
		}
		else if(listaReproduccion->id > idMusic)
		{
			listarCancionesLista(listaReproduccion->izq, music, idMusic);
		}
		else
		{
			listarCancionesLista(listaReproduccion->der, music, idMusic);
		}
		
			
	}

}

//Elimina una cancion de la lista de produccion, si el parametro total es igual a uno elimina todas las canciones de la lista
bool eliminarCancionLista(ListaReproduccion *listaReproduccion, int idLista, int idMusic, int total)
{

	if(listaReproduccion == NULL)
	{
		return false;
	}
	else
	{
		
		if(listaReproduccion->id == idLista)
		{
			CancionesLista* aux = listaReproduccion->ptrCancion;
			CancionesLista* aux2 = NULL;

			if(total == 0)
			{

				while(aux != NULL)
				{
					if(aux->idMusic == idMusic)
					{
						if(aux2 == NULL) //Si el elemento es el primero de la lista
						{
							listaReproduccion->ptrCancion = aux->siguiente;
						}
						else
						{
							aux2->siguiente = aux->siguiente;
						}
						free(aux);
						break;
					}
					aux2 = aux;
					aux = aux->siguiente;
				}
			}
			else
			{
				eliminarListaTotal(listaReproduccion->ptrCancion);
			}
			
		}
		else if(listaReproduccion->id > idMusic)
		{
			eliminarCancionLista(listaReproduccion->izq, idLista, idMusic, total);
		}
		else
		{
			eliminarCancionLista(listaReproduccion->der, idLista, idMusic, total);
		}
		
			
	}

}

//Eliminar un nodo del arbol de listas de reproduccion.
//El tercer parametro es necesario para mantener el enlace principal del arbol, por si se elimina el primer elemento de la lista
void eliminar(ListaReproduccion *arbol,  int n, ListaReproduccion *&principal)
{
	if (arbol == NULL)
	{
		return;
	}
	else if(n < arbol->id)
	{
		eliminar(arbol->izq, n, principal);
	}
	else if(n > arbol->id)
	{
		eliminar(arbol->der, n, principal);
	}else
	{
		eliminarNodo(arbol, principal);
	}
}

//Comprobar si el nodo a eliminar tiene uno, dos o ningun hijo, y continua con el proceso de eliminar
void eliminarNodo(ListaReproduccion *nodoEliminar, ListaReproduccion *&principal)
{
	if(nodoEliminar->izq && nodoEliminar->der)
	{
		ListaReproduccion *menor = minimo(nodoEliminar->der);
		nodoEliminar->id=menor->id;
		strcpy(nodoEliminar->nombre, menor->nombre);
		eliminarListaTotal(nodoEliminar->ptrCancion);
		nodoEliminar->ptrCancion = menor->ptrCancion;
		eliminarNodo(menor, principal);
	}
	else if (nodoEliminar->izq)
	{//Si tiene hijo Izq
		reemplazar(nodoEliminar,nodoEliminar->izq, principal);
		destruirNodo(nodoEliminar, principal);
	}
	else if(nodoEliminar->der)
	{//Si tiene hijo Der
		reemplazar(nodoEliminar,nodoEliminar->der, principal);
		destruirNodo(nodoEliminar, principal);
	}
	else
	{//No tiene Hijo
		reemplazar(nodoEliminar,NULL, principal);
		destruirNodo(nodoEliminar, principal);
	}
}

//Obtener el nodo minio del arbol, cuando el nodo a eliminar tiene 2 hijos.
ListaReproduccion *minimo(ListaReproduccion *arbol)
{	//Si el Arbol esta vacio
	if(arbol==NULL)
	{		//Retorna nulo
		return NULL;
	}
	if(arbol->izq)
	{			//Si tiene hijo izq
		return minimo(arbol->izq);//Buscar la parte izq posible
	}
	else
	{					//Si no tiene hijo izq
		return arbol;	//Retornamos el mismo ListaReproduccion
	}
}


//Reemplazar los enlaces correspondientes del nodo a eliminar
void reemplazar(ListaReproduccion *arbol, ListaReproduccion *nuevoNodo, ListaReproduccion *&principal)
{
	eliminarListaTotal(arbol->ptrCancion);
	if(arbol->padre)
	{
		//arbol->padre hay que asignarle el nuevo hijo
		if(arbol->izq)
		{
			arbol->padre->izq=nuevoNodo;
		}
		else if(arbol->der)
		{
			arbol->padre->der=nuevoNodo;
		}
	}
	else
	{
		principal = nuevoNodo;
	}

	if(nuevoNodo)
	{
		nuevoNodo->padre=arbol->padre;
	}
}

//Destruir finalmente el nodo del arbol
void destruirNodo(ListaReproduccion *nodo, ListaReproduccion *&principal)
{
	if(nodo->padre)
	{
		if(nodo->padre->izq)
		{
			if(nodo->id == nodo->padre->izq->id)
			{
				nodo->padre->izq = NULL;
			}
		}
		if(nodo->padre->der)
		{
			if(nodo->id == nodo->padre->der->id)
			{
				nodo->padre->der = NULL;
			}
		}
	}
		
	free(nodo);
}

//Elimina toda la lista de canciones de la lista de reproduccion
void eliminarListaTotal(CancionesLista *nodo)
{
	CancionesLista* aux = nodo;

	while(nodo != NULL)
	{
		aux = nodo;
		nodo = aux->siguiente;
		free(aux);
	}
}

//Editar el nombre de la lista de reproduccion
bool editarLista(ListaReproduccion* &lista, int id)
{
	char nombre[30];
	
	if(lista == NULL)
	{
		return false;
	}
	else
	{
		
		if(lista->id == id)
		{
			printf("\nMombre de la lista: %s", lista->nombre);
			printf("\nIngrese el nuevo nombre de la lista: ");
			getchar();
			fgets(nombre, 30, stdin);
			strcpy(lista->nombre, nombre);
		}
		else if(lista->id > 0)
		{
			editarLista(lista->izq, id);
		}
		else
		{
			editarLista(lista->der, id);
		}
			
	}

}






