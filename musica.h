#define RESERVAR_MUSIC (Music *)malloc(sizeof(Music))
#define RESERVAR_LISTA (ListaReproduccion *)malloc(sizeof(ListaReproduccion))
#define RESERVAR_MEMORIA_LISTA (CancionesLista *)malloc(sizeof(CancionesLista))



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

struct CancionesLista
{
	int idMusic;
	CancionesLista* siguiente;
};

struct ListaReproduccion
{
	int id;
	int user;
	char nombre[30];;
	CancionesLista * ptrCancion;
	ListaReproduccion *izq, *der;
	ListaReproduccion* padre;
};


void eliminar(ListaReproduccion *arbol, int n, ListaReproduccion *&);
void eliminarNodo(ListaReproduccion *nodoEliminar, ListaReproduccion *&principal);
ListaReproduccion *minimo(ListaReproduccion *arbol);
void reemplazar(ListaReproduccion *arbol, ListaReproduccion *nuevoNodo, ListaReproduccion *&principal);
void destruirNodo(ListaReproduccion *nodo, ListaReproduccion *&principal);
void eliminarListaTotal(CancionesLista *);

/*bool inicializarMusica(Music* &nodo)
{
	FILE *archivo;
	
	archivo = fopen("datos/musica.txt", "rb");
	
	if(archivo == NULL)
	{
		return false;
	}
	else
	{
		while(fread(pMusic, sizeof(*pMusic), 1, archivo))
		{
			insertarMusic(nodo, pMusic->nombre, pMusic->duracion, GeneroArtista* artista, GeneroArtista* genero, int &id, Music* padre)
		}
	}
	fclose(archivo);
}*/

/*bool guardarMusicaArchivo(Music* nuevoNodo)
{
	FILE *archivo;
	
	archivo = fopen("datos/musica.txt", "ab");
	
	if(archivo == NULL)
	{
		return false;
	}
	fwrite(nuevoNodo,sizeof(*nuevoNodo),1,archivo);
	rewind(archivo);
	fclose(archivo);
}*/

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

	/*Music *nodo;
	strcpy(nodo->nombre, nombre);
	nodo->id = id;
	nodo->duracion = duracion;
	nodo->conteo = 0;
	nodo->idArtista = artista->id;
	nodo->idGenero = genero->id;
	guardarMusicaArchivo(nodo);*/
	return nuevoNodo;
}



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

bool buscarMusic(Music* music, char nombre[], int longitud, int &contador)
{
	
	if(music == NULL)
	{
		return contador;
	}
	else
	{

		//buscarMusic(music->izq, nombre, longitud, opcion);
		if(strncmp(music->nombre, nombre, longitud) == 0)
		{
			contador =+ 1;
			printf("\nId: %d", music->id);
			printf("\nNombre: %s", music->nombre);
			printf("Tiempo: %d\n", music->duracion);
			printf("Genero: %s", music->idGenero->nombre);
			printf("Artista: %s", music->idArtista->nombre);
			printf("Agregada: %d\n", music->conteo);
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

		//buscarMusic(music->izq, nombre, longitud, opcion);
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






