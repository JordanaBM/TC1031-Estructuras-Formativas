/*
 * heap.h
 *
 *  Created on: 14/10/2021
 *      Author: Jordana Betancourt Menchaca A01707434
 */

#ifndef HEAP_H_
#define HEAP_H_

#include <string>
#include <sstream>
#include <iostream>
#include <cstring>


using namespace std;

template <class T>
class Heap {
private:
	T *data;
	unsigned int tam;
	unsigned int count;
	unsigned int parent(unsigned int) const;
	unsigned int left(unsigned int) const;
	unsigned int right(unsigned int) const;
	void heapify(unsigned int);
	void swap(unsigned int, unsigned int);
public:
	Heap(unsigned int);
	~Heap();
    //Implementaciones
    void push(int);
    void pop();
    T top();
	bool empty() const;
    int size();

    //Extras
	bool full() const;
	void clear(); 
	std::string toString() const;
};
template <class T>

/*
 * Heap Constructor
 *
 * @param int 
 * @return 
 * 
*/
Heap<T>::Heap(unsigned int sze) {
	tam = sze;
	data = new T[tam];
	if (data == 0) {
		cout << "OutOfMemory" ;
	}
	count = 0;
}
template <class T>

/*
 * Destructor Heap
 *
 * @param 
 * @return 
 * 
*/
Heap<T>::~Heap() {
	delete [] data; data = 0;
	tam = 0; count = 0;
}

//Push
/*
 * push
 *
 * @param int val
 * @return 
 * 
*/
template <class T>
void Heap<T>::push(int val) {
	unsigned int pos;

    //Verificamos que el array no esté lleno
	if (full()) {
		cout << "Overflow";
	}

    //Creamos una variable auxiliar de la posición
	pos = count;
    //Incrementamos el tamaño en 1
	count++;
    /*Mientras la posición sea mayor a 0 y el valor que se quiere insertar sea
    menor que sus ancestros */
	while (pos > 0 && val < data[parent(pos)]) {
        //La data del ancestro va a ser la nueva data del pos
		data[pos] = data[parent(pos)];
		pos = parent(pos);
	}
	data[pos] = val;
}

//pop
/*
 * pop
 *
 * @param
 * @return 
 * 
*/
template <class T>
void Heap<T>::pop() {
    //Verificamos que se tenga al menos un elemento
	if (empty()) {
		cout <<  "NoSuchElement";
	}

    //Hacemos que en la posición 0 se pueda reescribir
   	data[0] = data[--count];
    //Después reordenamos para que el valor mínimo quede en la posición 0
	heapify(0);
	
}

//Top
/*
 * top
 *
 * @param 
 * @return T
 * 
*/
template <class T>
T Heap<T>::top() {
    //Verificamos que tengamos al menos un elemento
	if(count != 0){
        //Devolvemos el dato de la primera posición
        return data[0];
    }
    //En otro caso devolvemos 1
    return -1;
}

//Empty
/*
 * empty
 *
 * @param 
 * @return bool
 * 
*/
template <class T>
bool Heap<T>::empty() const {
    //Devuelve 1 si nuestro count es igual a 0
	return (count == 0);
}

//Size
/*
 * size
 *
 * @param 
 * @return int
 * 
*/
template <class T>
int Heap<T>::size() {
    //Regresamos el contador
	return count;
}


/*
 * full
 *
 * @param 
 * @return bool
 * 
*/
template <class T>
bool Heap<T>::full() const {
    //Devuelve uno si el contador es igual al tamaño del Heap
	return (count == tam);
}

/*
 * parent
 *
 * @param int
 * @return int
 * 
*/
template <class T>
unsigned int Heap<T>::parent(unsigned int pos) const {
    //Regresa el padre de algún dato
	return (pos - 1) / 2;
}

/*
 * left
 *
 * @param int
 * @return int
 * 
*/
template <class T>
unsigned int Heap<T>::left(unsigned int pos) const {
    //Regresa el hijo izquierdo de un dato
	return ((2 * pos) + 1);
}

/*
 * right
 *
 * @param int
 * @return int
 * 
*/
template <class T>
unsigned int Heap<T>::right(unsigned int pos) const {
    //Regresa el hijo derecho de un dato
	return ((2 * pos) + 2);
}

/*
 * swap
 *
 * @param int, int
 * @return 
 * 
*/
template <class T>
void Heap<T>::swap(unsigned int i, unsigned int j) {
    //Auxiliar con data i
	T aux = data[i];
    //Data i ahora tiene el valor de data j
	data[i] = data[j];
    //Data j tiene el valor del aux
	data[j] = aux;
}
template <class T>

/*
 * heapify
 *
 * @param int
 * @return 
 * 
*/
void Heap<T>::heapify(unsigned int pos) {
	unsigned int le = left(pos);
	unsigned int ri = right(pos);
	unsigned int min = pos;

    /*Si left es menor o igual al tamaño del array y además su data es menor que 
    el de la posición dada */
	if (le <= count && data[le] < data[min]) {
        //Tenemos un nuevo min 
		min = le;
	}
    /*Si right es menor o igual al tamaño del array y además su data es menor que 
    el de la posición dada */
	if (ri <= count && data[ri] < data[min]) {
        //Tenemos un nuevo min
		min = ri;
	}
    //Si el min es diferente a pos
	if (min != pos) {
        //Swapeamos los valores
		swap(pos, min);
        //Recursión
		heapify(min);
	}
}

/*
 * clear
 *
 * @param 
 * @return 
 * 
*/
template <class T>
void Heap<T>::clear() {
    //Se pone el contador a 0 para poder sobreescribir
	count = 0;
}

/*
 * toString
 *
 * @param 
 * @return string
 * 
*/
template <class T>
std::string Heap<T>::toString() const {
	std::stringstream aux;
    //Concatenamos todo en un auxiliar
	aux << "[";	for (unsigned int i = 0; i < count; i++) {
		if (i != 0) {
			aux << " ";
		} aux << data[i];
	} aux << "]";
	return aux.str();
}

#endif /* HEAP_H_ */