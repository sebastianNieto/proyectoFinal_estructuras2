/* Funciones referentes al manejo de generos y artistas musicales de la aplicación. Utilizando arboles binarios
*  Fecha: 30/11/2017
*  Elaborado por: John Sebastian Nieto gil
*  Elaborado por: Ricardo Andres Villalobos
*/

#define RESERVAR_GENERO_ARTISTA (GeneroArtista *)malloc(sizeof(GeneroArtista))

//Estructura tipo lista doblemente enlazada
struct GeneroArtista
{
	int id;
	char nombre[30];
	GeneroArtista *siguiente, *anterior;
};

//Prototipo de funciones
void crearGeneroArtista(GeneroArtista *&, char []);
void mostrarGeneroArtista(GeneroArtista*);
GeneroArtista* asignarGeneroArtista(GeneroArtista*);


//Crea un nuevo nodo para la lista, puede ser para un nuevo genero o nuevo artista
void crearGeneroArtista(GeneroArtista *&lista, char generoArtista[])
{

	GeneroArtista *nuevoNodo = RESERVAR_GENERO_ARTISTA;
	strcpy(nuevoNodo->nombre, generoArtista);

	if(lista == NULL)
	{
		lista = nuevoNodo;
		nuevoNodo->siguiente = nuevoNodo;
		nuevoNodo->anterior = nuevoNodo;
		nuevoNodo->id = 1;
	}
	else
	{
		nuevoNodo->siguiente = lista;
		nuevoNodo->anterior = lista->anterior;
		nuevoNodo->id = lista->anterior->id+1;
		lista->anterior->siguiente = nuevoNodo;
		lista->anterior = nuevoNodo;
	}
}

//Muestra todos los elementos de la lista, puede ser artistas o generos
void mostrarGeneroArtista(GeneroArtista* lista)
{
	GeneroArtista* aux = lista;
	printf("\nId\tNombre\n");
	do
	{
		printf("\n%d\t%s", aux->id, aux->nombre);
		aux = aux->siguiente;
	}
	while(aux != lista);
}

//Retorna el puntero del nodo, para ser asignado a una cancion
GeneroArtista* asignarGeneroArtista(GeneroArtista* lista)
{
	int id = 0;

	GeneroArtista* aux = lista;
	system("clear");
	printf("Eliga el id correspondiente: ");
	mostrarGeneroArtista(lista);
	printf("\nId: : ");
	scanf("%d", &id);

	for(int i = 1; i < id; i++)
	{
		aux = aux->siguiente;
	}

	return aux;

}