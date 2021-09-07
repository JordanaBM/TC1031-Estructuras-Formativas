/*
 * sorts.h
 *
 *  Created on: 07/09/2021
 *  Author: Jordana Betancourt Menchca A01707434
 */

#ifndef SORTS_H_
#define SORTS_H_

#include <iostream>
#include <sstream>
#include <vector>
#include <list>

using namespace std;


template <class T>
class Sorts {
private:
	void swap(vector<T>&, int, int);
	void copiarVector(vector<T>&,vector<T>&, int, int);
	void mergeVector(vector<T>&, vector<T>&, int, int, int);
	void mergeSplit(vector<T>&, std::vector<T>&, int, int);
public:
	void ordenaBurbuja(vector<T>&);
	void ordenaSeleccion(vector<T>&);
	void ordenaMerge(vector<T>&);
	
	int busqSecuencial(const vector<T>&, int val);
	int busqBinaria(const vector<T>&, int val);
	int bb_aux(vector<T> v, int low, int high, int val);
};


/*
 * swap
 *
 * @param vector<T> por referencia, int i, int j
 * @return 
 * 
 * Cambio de valores en un vector
 * 
*/
template <class T>
void Sorts<T> ::swap(vector<T> &v, int i, int j) {
	T aux = v[i];
	v[i] = v[j];
	v[j] = aux;
}


/*
 * ordenaBurbuja
 *
 * @param vector<T> con referencia
 * @return 
 * 
*/
template <class T>
void Sorts<T>::ordenaBurbuja(vector<T> &v) {
	for(int i = 0; i<v.size(); i++) {
  		for(int j = i+1; j<v.size(); j++){   
     		 if(v[j] < v[i]) {  //Si la posición anterior es mayor que la actual
		  		swap(v, i, j);  //Realizo un swap
			}
		}
	}
	
}

/*
 * ordenaSeleccion
 *
 * @param vector<T> con referencia
 * @return 
 * 
*/
template <class T>
void Sorts<T>::ordenaSeleccion(vector<T> &v) {
	for(int i = 0; i<v.size()-1; i++) {
      int imin;
	  imin = i;   //Tomamos el índice mínimo
      for(int j = i+1; j<v.size(); j++){
         if(v[j] < v[imin]) //Si el número en el que voy es menor que el imin
            imin = j;       //Ese es mi nuevo número menor 
         
	    }
     swap(v,imin, i); //Colocamos en el orden correcto
	  
	  
	}

}


//Merge Sort
/*
 * ordenaMerge
 *
 * @param vector<T> con referencia
 * @return 
 * 
*/
template <class T>
void Sorts<T>::ordenaMerge(vector<T> &v) {
	vector<T> tmp(v.size()); //Creamos un vector temporal

	mergeSplit(v, tmp, 0, v.size() - 1);
	
}

/*
 * copiarVector
 *
 * @param vector<T> con referencia
 * @return 
 * 
*/
template <class T>
void Sorts<T>::copiarVector(vector<T> &A, vector<T> &B, int low, int high) {
	for (int i = low; i <= high; i++) {
		A[i] = B[i]; //Copiamos todos los valores del vector temporal a A
	}
}


/*
 * mergeVector
 *
 * @param vector<T> &A, vector<T> &B, int low, int mid, int high
 * @return 
 * 
 * Se encarga de acomodar el vector y agregar los valores al temporal
 * 
*/
template <class T>
void Sorts<T>::mergeVector(vector<T> &A,vector<T> &B, int low, int mid, int high) {
	int i, j, k;

	i = low;
	j = mid + 1;
	k = low;

//Mientras la posición low sea menor a la mitad del vector y el high mayor a la 
//mitad, se copiarán directamente los números al vector temporal.
	while (i <= mid &&j <= high) { 
		if (A[i] < A[j]) {
			B[k] = A[i];
			i++;
		} else {
			B[k] = A[j];
			j++;
		}
		k++;
	}
	//Si el low es mayor que la mitad, copio todo lo que sobro de la mitad en adelante
	if (i > mid) {
		for (; j <= high; j++) {
			B[k++] = A[j];
		}
	//Si el high es mayor que la mitad, copio todo lo que sobro de low a la mitad
	} else {
		for (; i <= mid; i++) {
			B[k++] = A[i];
		}
	}
}

template <class T>
void Sorts<T>::mergeSplit(vector<T> &A,vector<T> &B, int low, int high) {
	int mid;

	if ( (high - low) < 1 ) {
		return; //Topamos con el caso base cuando ya solo sea un número
	}
	mid = (high + low) / 2;
	mergeSplit(A, B, low, mid);//Para partir el vector a la derecha
	mergeSplit(A, B, mid + 1, high);//Para partir el vector en la izquierda
	mergeVector(A, B, low, mid, high);//Para realizar operaciones después de 
	                                 //llegar al caso base
	copiarVector(A, B, low, high);//Copiar el vector temporal en el original
}


/*
 * busqSecuencial
 *
 * @param vector<T> con referencia, int valor
 * @return int
 * 
*/
template <class T>
int Sorts<T>::busqSecuencial(const vector<T> &source, int val) {
	vector<T> v(source);
	//Recorro todo el arreglo hasta encontrar el valor deseado
	for (int i = 0; i < v.size() ; i++) { 
		if (val == v[i]) {
			return i; //Si lo encuentro, retorno su posición
		}
	}
	return -1; //Si no existe en el vector, retorno -1
}


/*
 * busqBinaria
 *
 * @param vector<T> con referencia, int valor
 * @return int
 * 
*/
template <class T>
int Sorts<T>::busqBinaria(const vector<T> &source, int val) {
	vector<T> v(source);
	return bb_aux(v, 0, v.size() - 1, val);
}

//Busqueda binaria auxiliar
/*
 * bb_aux
 *
 * @param vector<T>, int low, int high, int val
 * @return int
 * 
*/
template <class T>
int Sorts<T>::bb_aux(vector<T> v, int low, int high, int val) {
	int mid;

	if (low <= high) {
		mid = (high + low) / 2;
		if (val == v[mid]) {//Si el valor buscado está en la mitad del vector
			return mid;     //Regreso el índice de la mitad
		} else if (val < v[mid]) { //Si el valor buscado es menor que el de la mitad
			return bb_aux(v, low, mid - 1, val); //Parto hacía la derecha
		} else if (val > v[mid]) {
			return bb_aux(v, mid + 1, high, val); //De otra forma parto a la izquierda
		}
	}
	return -1; //Si no se encuentra, retorna -1
}
#endif