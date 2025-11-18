#include<iostream>
#include<string>
using namespace std;

struct Vertice{
	string etiqueta;
	Vertice *sig;
	
	int etiquetaDijkstra = -1;
	string origenEtiqueta = "";
	
	bool etiquetaPermanente = false;
	
	Vertice(string n): etiqueta(n), sig(nullptr){}
	Vertice(): etiqueta(""), sig(nullptr){}
};

struct Arista{
	int peso;
	Vertice *vertice1;
	Vertice *vertice2;
	Arista* sig;
	
	Arista(Vertice *vertice1, Vertice *vertice2): vertice1(vertice1), vertice2(vertice2), sig(nullptr){}
	Arista(): vertice1(nullptr), vertice2(nullptr), sig(nullptr){}
};

struct ConjuntoVertices{
	Vertice *inicio = nullptr;
	
	void insertar(string etiqueta){
		Vertice* nuevo = new Vertice;
		nuevo->etiqueta = etiqueta;
	
		if(inicio == nullptr){
			inicio = nuevo;
		}else{
			Vertice* aux = inicio;
			while(aux->sig != nullptr){
				aux = aux->sig;
			}
		aux->sig = nuevo;
		}
	}
	
	int contarVertices(){
		Vertice *aux=inicio;
		int contador = 0;
	
		if(inicio){
			while(aux!=nullptr){
				contador++;
				aux=aux->sig;
			}	
		}
		return contador;
	}
	
	void imprimirVertices(){
		for(Vertice* aux = inicio; aux != nullptr; aux = aux->sig){
			cout<<aux->etiqueta<<" ";
		}
		cout<<endl;
	}
	
	Vertice* devolverVertice(string referencia){
		Vertice* aux = inicio;
		while(aux!=nullptr && aux->etiqueta!=referencia){
			aux = aux->sig;
		}
		return aux;
	}
	
	bool existeVertice(string referencia){
		bool existe = false;
		Vertice* aux = inicio;
		while(aux!=nullptr && !existe){
			if(aux->etiqueta==referencia){
				existe = true;
			}else{
				aux = aux->sig;		
			}	
		}
		return existe;
	}
};

struct ConjuntoAristas{
	Arista *inicio = nullptr;
	
	void insertar(int peso, Vertice *vertice1, Vertice *vertice2){
		Arista* nuevo = new Arista;
		nuevo->peso = peso;
		nuevo->vertice1 = vertice1;
		nuevo->vertice2 = vertice2;
	
		if(inicio == nullptr){
			inicio = nuevo;
		}else{
			Arista* aux = inicio;
			while(aux->sig != nullptr){
				aux = aux->sig;
			}
		aux->sig = nuevo;
		}
	}
	
	void imprimirAristas(){
		for(Arista* aux = inicio; aux != nullptr; aux = aux->sig){
			cout<<aux->vertice1->etiqueta<<"---";
			cout<<aux->peso<<"---";
			cout<<aux->vertice2->etiqueta<<endl<<endl;
		}
		cout<<endl;
	}
};

struct Grafica{
	ConjuntoVertices V;
	ConjuntoAristas E;
	
	void AgregarVertice(string etiqueta){
		V.insertar(etiqueta);	
	}
	
	void MostrarVertices(){
		if(V.inicio==nullptr){
			cout<<"No hay ningun vertice todavia"<<endl;
		}else{
			V.imprimirVertices();
		}
	}
	
	void MostrarAristas(){
		if(E.inicio==nullptr){
			cout<<"No hay ninguna arista todavia"<<endl;
		}else{
			E.imprimirAristas();
		}
	}
	
	bool VAdyacente(Vertice *vertice1, Vertice *vertice2){
		bool adyacente = false;
		Arista* aux = E.inicio; 
		while(aux != nullptr && !adyacente){
			if((aux->vertice1 == vertice1 && aux->vertice2 == vertice2) || (aux->vertice1 == vertice2 && aux->vertice2 == vertice1)){
				adyacente = true;
			}
			aux = aux->sig;
		}
		return adyacente;
	}
	
	void etiquetarV(Vertice *vertice1, Vertice *vertice2){
		bool etiquetado = false;
		Arista* aux = E.inicio;
		while(aux != nullptr && !etiquetado){
			if((aux->vertice1 == vertice1 && aux->vertice2 == vertice2) || (aux->vertice1 == vertice2 && aux->vertice2 == vertice1)){
				if(vertice2->etiquetaDijkstra==-1 || vertice2->etiquetaDijkstra > (aux->peso + vertice1->etiquetaDijkstra)){
					vertice2->etiquetaDijkstra = (aux->peso + vertice1->etiquetaDijkstra);
					vertice2->origenEtiqueta = vertice1->etiqueta;
					etiquetado = true;
				}
			}
			aux = aux->sig;
		}	
	}
	
	void dijkstra(Vertice* origen, Vertice* destino){
		origen->etiquetaDijkstra = 0;
		
		for(Vertice* aux = V.inicio; aux != nullptr; aux = aux->sig){
			aux->etiquetaPermanente = false;
			aux->origenEtiqueta = "";
			if(aux!=origen){
				aux->etiquetaDijkstra = -1;
			}		
		}
		
		Vertice* actual = origen;
		
		while(!destino->etiquetaPermanente){
			
			for(Vertice* aux = V.inicio; aux != nullptr; aux = aux->sig){
				if(VAdyacente(actual, aux) && !aux->etiquetaPermanente){
					etiquetarV(actual, aux);
				}
			}
		
			actual->etiquetaPermanente = true;
		
			Vertice* menorAdyacente = nullptr;
		
			for(Vertice* aux = V.inicio; aux != nullptr; aux = aux->sig){
				if(!aux->etiquetaPermanente && aux->etiquetaDijkstra!=-1){
					if(!menorAdyacente){
						menorAdyacente = aux;
					}else if(aux->etiquetaDijkstra < menorAdyacente->etiquetaDijkstra){
						menorAdyacente = aux;
					}
				}
			}
			actual = menorAdyacente;
		}
		
		Vertice *aux2 = destino;
		
		string ruta = destino->etiqueta;
		
		while(aux2->origenEtiqueta!=""){
			ruta = aux2->origenEtiqueta + "->" + ruta;
			aux2 = V.devolverVertice(aux2->origenEtiqueta);
		}
		
		cout<<"Una ruta mas corta desde "<<origen->etiqueta<<" a "<<destino->etiqueta<<" es "<<ruta<<endl;
	}
};

void vaciarListaVertices(Vertice *&inicio){
	Vertice *aux = inicio;
	while(aux!=nullptr){
		inicio = inicio->sig;
		delete aux;
		aux = inicio;
	}
}

void vaciarListaAristas(Arista *&inicio){
	Arista *aux = inicio;
	while(aux!=nullptr){
		inicio = inicio->sig;
		delete aux;
		aux = inicio;
	}
}

int main(){
	
	Grafica G;
	
	int opcion;
	
	do{
		system("cls");
		cout<<"Menu de grafica para algoritmo de DIJKSTRA"<<endl;
		cout<<"1. Agregar vertice"<<endl;
		cout<<"2. Agregar arista"<<endl;
		cout<<"3. Mostrar vertices"<<endl;
		cout<<"4. Mostrar Aristas"<<endl;
		cout<<"5. Ejecutar algoritmo de una ruta mas corta de DIJKSTRA"<<endl;
		cout<<"99. Salir"<<endl;
		cout<<endl<<">";
		
		cin>>opcion;	
		string etiqueta;
		int peso;
		string primerVertice, segundoVertice;
		
		switch(opcion){
			
			case 1:
				cout<<"Ingrese la etiqueta del vertice (texto): ";
				cin.ignore();
				getline(cin, etiqueta);
				G.AgregarVertice(etiqueta);
				cout<<endl<<"Vertice agregado"<<endl;
				break;
				
			case 2:
				if(G.V.contarVertices()<1){
					cout<<"No hay vertices"<<endl;
				}else{
					cout<<"Ingrese el peso de la arista (entero): ";
					cin>>peso;
					cout<<endl<<"Seleccione el primer vertice a conectar a la arista: "<<endl;
					G.MostrarVertices();
					cin.ignore();
					getline(cin, primerVertice);
					while(!G.V.existeVertice(primerVertice)){
						cout<<endl<<"El vertice ingresado no existe"<<endl<<"Seleccione el primer vertice a conectar a la arista: "<<endl;
						G.MostrarVertices();
						getline(cin, primerVertice);
					}
					cout<<endl<<"Seleccione el segundo vertice a conectar a la arista: "<<endl;
					G.MostrarVertices();
					getline(cin, segundoVertice);
					while(!G.V.existeVertice(segundoVertice)){
						cout<<endl<<"El vertice ingresado no existe"<<endl<<"Seleccione el segundo vertice a conectar a la arista: "<<endl;
						G.MostrarVertices();
						getline(cin, segundoVertice);
					}
					G.E.insertar(peso, G.V.devolverVertice(primerVertice), G.V.devolverVertice(segundoVertice));
					cout<<"Arista agregada"<<endl;
				}
				break;
				
			case 3:
				G.MostrarVertices();
				break;
				
			case 4:
				G.MostrarAristas();
				break;
				
			case 5:
				if(G.V.contarVertices()<2){
					cout<<"No hay suficientes vertices"<<endl;
				}else{
					cout<<"Seleccione el origen:"<<endl;
					cin.ignore();
					G.MostrarVertices();
					getline(cin, primerVertice);
					while(!G.V.existeVertice(primerVertice)){
						cout<<endl<<"El vertice ingresado no existe"<<endl<<"Seleccione el origen: "<<endl;
						G.MostrarVertices();
						getline(cin, primerVertice);
					}
					cout<<"Seleccione el destino:"<<endl;
					getline(cin, segundoVertice);
					while(!G.V.existeVertice(segundoVertice)){
						cout<<endl<<"El vertice ingresado no existe"<<endl<<"Seleccione el destino: "<<endl;
						G.MostrarVertices();
						getline(cin, segundoVertice);
					}
					G.dijkstra(G.V.devolverVertice(primerVertice), G.V.devolverVertice(segundoVertice));
				}
				break;

			case 99:
				vaciarListaVertices(G.V.inicio);
				vaciarListaAristas(G.E.inicio);
				break;
				
			default:
				cout<<"Ingrese una opcion valida"<<endl;
				break;
		}
		system("pause");
	}while(opcion != 99);
	
	
	return 0;
}