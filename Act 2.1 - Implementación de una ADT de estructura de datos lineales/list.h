/*
 * List.h
 *
 *  Created on: 20/09/2021
 *      Author: Jordana Betancourt Menchaca A01707434
 */



#include <iostream>
#include <sstream>
#include <cstring>
#include <string>


#ifndef LIST_H_
#define LIST_H_

template <class T> class List;
template <class T> class ListIterator;

using namespace std;

//Class Link
template <class T>
class Link {
private:
	Link(T);
	T	    value;
	Link<T> *next;

	friend class List<T>;
	friend class ListIterator<T>;
    
};

/*
 * Constructor
 *
 * @param T
 * @return 
 * 
 * Crea nodos
 * 
*/
template <class T>
Link<T>::Link(T val) : value(val), next(0) {}

//Class List
template <class T>
class List {
public:

	List();
	void insertion(T);
    void FirstInsertion(T);
    int search(T);
    void update(int,T);
    T deleteAt(int);
   	string toString();
    bool empty();
	

private:
	Link<T> *head;
	int 	size;

	friend class ListIterator<T>;
};


/*
 * Constructor Default
 *
 * @param 
 * @return 
 * 
 * Para manejo de apuntadores
 * 
*/
template <class T>
List<T>::List() : head(0), size(0) {};


/*
 * empty
 *
 * @param 
 * @return 
 * 
 * Para verificar si la lista no tiene ningún nodo
 * 
*/
template <class T>
bool List<T>::empty(){
	return (head == 0);
}

/*
 * toString
 *
 * @param 
 * @return string
 * 
 * Para tranformar la lista a string
 * 
*/
template <class T>
string List<T>::toString() {
	std::stringstream aux;
	Link<T> *p;
	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

/*
 * FirstInsertion
 *
 * @param T val
 * @return 
 * 
 * Inserta el primer nodo de la lista
 * 
*/
template <class T>
void List<T>::FirstInsertion(T val) {
	Link<T> *newLink;

	newLink = new Link<T>(val);
    if(newLink == 0){
        cout<<"OutOfMemory";
    }
	
	newLink->next = head;
	head = newLink;
	size++;
}

/*
 * Constructor Default
 *
 * @param T val
 * @return 
 * 
 * Inserta nodos al final de la lista, si no existen nodos llama a FirstInsertion
 * 
*/
template <class T>
void List<T>::insertion(T val) {
    Link<T> *newLink, *aux;
    newLink = new Link<T>(val);
	
	if (empty()) {
		FirstInsertion(val);
		return;
	}
    else{
	    aux = head;
	    while (aux->next != 0) 
		    aux = aux->next;
        aux->next = newLink;
	}

	newLink->next = 0;
	size++;
}

/*
 * search
 *
 * @param T val
 * @return int
 * 
 * Busca un valor en el nodo y regresa la posición en la que se encuentra dicho valor
 * 
*/
template <class T>
int List<T>::search(T val)  {
	Link<T> *aux;

	aux = head;
    int pos = 0;

    //Recorremos toda la lista 
	while (aux != 0) {
        
        //Cuando el valor del nodo auxiliar sea el buscado
		if (aux->value == val) {
            //Devolvemos la posición
			return pos;
		}
        //Si no, pasamos al siguiente nodo y aumentamos la posición
        aux = aux->next;
        pos ++;	
        
	}
    //Si el valor no existe en los nodos de la lista, se regresa -1
	return -1;
}

/*
 * update
 *
 * @param int pos ,T val
 * @return 
 * 
 * Cambia el valor de un nodo a partir de su posición en la lista
 * 
*/
template <class T>
void List<T>::update(int pos, T val)  {
	Link<T> *aux;
	aux = head;
    int counter;
    counter = 0;

    //Recorremos toda la lista
    while (aux != 0) {

        //Si el contador interno es igual a la posición de nodo del cual se 
        // quiere cambiar el valor
		if (counter == pos) {
            //Le asigno ese valor
            aux->value = val;	
		}
		//Si no, avanzo al siguiente nodo y aumento el contador
        aux = aux->next;
        counter++;
	}
	
}

/*
 * deleteAt
 *
 * @param int pos
 * @return T val
 * 
 * Para manejo de apuntadores
 * 
*/
template <class T>
T List<T>::deleteAt(int pos) {
	T val;
	
    //Eliminar primer nodo
     if (pos == 0){
        Link<T> *aux = head;
    
        val = aux->value;
        //El nuevo head de la lista será el nodo siguiente, ya que eliminamos
        //el primero
	    head = aux->next;
	    
        delete aux; 
    }
    //Eliminar otro nodo
    else {
        Link<T> *anterior = head;
        Link<T> *aux = anterior-> next;
        int index = 1;
    
        while (aux != 0) {

            if (index == pos) {
                val = aux->value;
                /* 
                * Se requieren de dos apuntadores debido a que al eliminar un 
                * nodo que esté en el centro se necesitará crear una conexión
                * entre el anterior a ese nodo y el que estaba después para
                * no alterar la lista
                */
                anterior->next = aux-> next; //Aquí se realiza la conexión
                delete aux;  
                break;
            }
            anterior = anterior->next;
            aux = aux->next;
            index ++;
        }     
    } 
	size--;  
    return val;
}

#endif