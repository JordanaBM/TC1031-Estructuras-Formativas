/*
 * DList.h
 *
 *  Created on: 27/09/2021
 *      Author: Jordana Betancourt Menchaca A01707434
 */

#include <iostream>
#include <sstream>
#include <cstring>
#include <string>


#ifndef DLIST_H_
#define DLIST_H_

template <class T> class List;
template <class T> class ListIterator;

using namespace std;

template <class T> class DList;
template <class T> class DListIterator;

template <class T>
class DLink {
private:
	DLink(T);
	DLink(T, DLink<T>*, DLink<T>*);
	
	T	    value;
	DLink<T> *previous;
	DLink<T> *next;

	friend class DList<T>;
	friend class DListIterator<T>;
};

template <class T>
DLink<T>::DLink(T val) : value(val), previous(0), next(0) {}

template <class T>
DLink<T>::DLink(T val, DLink *prev, DLink* nxt) : value(val), previous(prev), next(nxt) {}


//Class DList
template <class T>
class DList {
public:

	DList();
	void insertion(T);
    void FirstInsertion(T);
    int search(T);
    void update(int,T);
    T removeFirst();
    T deleteAt(int);
   	string toStringBackward();
    string toStringForward();
    bool empty();
	

private:
	DLink<T> *head;
	DLink<T> *tail;
	int 	 size;

	friend class ListIterator<T>;
};


/*
 * Constructor Default
 *
 * @param 
 * @return 
 * 
 * Para manejo de nodos
 * 
*/
template <class T>
DList<T>::DList() : head(0), tail(0), size(0) {}


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
bool DList<T>::empty() {
	return (head == 0 && tail == 0);
}

/*
 * toStringForward
 *
 * @param 
 * @return string
 * 
 * Para tranformar la lista a string de adelante hacia atrás
 * 
*/
template <class T>
	string DList<T>::toStringForward()  {
		stringstream aux;
		DLink<T> *p;

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
 * toStringBackward
 *
 * @param 
 * @return string
 * 
 * Para tranformar la lista a string de atrás hacia delante
 * 
*/
	template <class T>
	string DList<T>::toStringBackward() {
		std::stringstream aux;
		DLink<T> *p;

		p = tail;
		aux << "[";
		while (p != 0) {
			aux << p->value;
			if (p->previous != 0) {
				aux << ", ";
			}
			p = p->previous;
		}
		aux << "]";
		return aux.str();
	}



/*
 * insertion
 *
 * @param T val
 * @return 
 * 
 * Inserta el primer nodo en caso de que la lista no tenga ninguno, después
 * los inserta al final de la lista
 * 
*/
template <class T>
void DList<T>::insertion(T val) {
    DLink<T> *newLink;

	newLink = new DLink<T>(val);
	if (newLink == 0) {
		cout<<"OutOfMemory";
	}
    //Si nuestra lista esta vacía
	if (empty()) {
        //La cabeza y cola de la lista se encuentan en el mismo nodo
		head = newLink;
		tail = newLink;
	} else {
        //De otra forma insertamos el nuevo nodo al final
		tail->next = newLink;
        //Le colocamos su nuevo apuntador previo 
		newLink->previous = tail;
        //Y asignamos nueva cola
		tail = newLink;
	}
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
int DList<T>::search(T val)  {
	DLink<T> *aux;

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
void DList<T>::update(int pos, T val)  {
     DLink<T> *aux;
	DLink<T> *auxhead;
    DLink<T> *auxtail;
    aux = head;
	auxhead = head;
    auxtail = tail;
    int counter = 0;
    int mid; 
    mid = size/2;
    
    // if (pos < mid){
    //     if (counter == pos) {

    //     }
    // }
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
 * removeFirst
 *
 * @param 
 * @return T val
 * 
 * Cambia el valor de un nodo a partir de su posición en la lista
 * 
*/
template <class T>
T DList<T>::removeFirst() {
	T val;
	DLink<T> *p;

    //Si está vacía no se puede eliminar ningún elemento
	if (empty()) {
		cout<<"NoSuchElement";
	}

	p = head;
	val = p->value;

    //Si la cabeza es igual a la cola, solo hay un elemento, por tanto, al 
    // eliminar ese nodo ambos apuntadores serían nulos
	if (head == tail) {
		head = 0;
		tail = 0;
    //De otra forma la cabeza pasa a ser el apuntador del nodo siguiente y 
    // el previo ahora es nulo
	} else {
		head = p->next;
		p->next->previous = 0;
	}
	delete p;
	size--;

	return val;
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
T DList<T>::deleteAt(int index) {
    int pos;
	T val;
	DLink<T> *p;
    
    //Por si el index pasa de los límites de la lista
	if (index < 0 || index >= size) {
		cout<<"IndexOutOfBounds";
	}

    // Si el nodo a eliminar es el primero
	if (index == 0) {
		return removeFirst();
	}

    //Para nodos después del primero
    p = head;
	pos = 0;
	while (pos != index) {
		p = p->next;
		pos++;
	}

    //Si el elemento a eliminar es el último 
    if (p->next != 0) {
		p->next->previous = p->previous;
	}

    //Para cualquier nodo que no sea el primero ni último
	val = p->value;
    //Enlazamos para que el nodo anterior del eliminado tenga como nodo 
    // siguiente al que sigue del nodo que se quiere eliminar
	p->previous->next = p->next;

    //Decrementamos el tamaño, eliminamos el nodo y retornamos el valor que 
    // tenía ese nodo
	size--;
	delete p;
	return val;
}

#endif