/*
 * funciones.h
 *
 *  Created on: 23/08/2021
 *      Author: Jordana Betancourt Menchaca A01707434
 */

#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <iostream>

class Funciones{
            
    public:
    //Constructor por omisión (el compilador lo crea)
        
    //Funciones
    long sumaIterativa(int n);
    long sumaRecursiva(int n);
    long sumaDirecta(int n);
    
};


/*
*long – El formato de variable numérica de tipo extendido “long” se refiere a 
*números enteros (tipo 32 bits = 4 bytes) sin decimales que se encuentran dentro 
*del rango -2147483648 a 2147483647.
*/
long Funciones :: sumaIterativa(int n) {
    long acum = 0;
    if (n >= 1){
	    for (int i = 1; i <= n; i++) {
		    acum += i;
	    }
        return acum;
    }
    else{
        return acum;
    }
    
}

long Funciones :: sumaRecursiva(int n) {
	if (n == 1) {
		return 1;
	} 
    else if(n <=0){
        return 0;
    }
    else {
		return n + sumaRecursiva(n - 1);
	}
}

long Funciones :: sumaDirecta(int n){
    if( n >= 1){
        return (n*(n+1))/2;
    }
    else{
        return 0;
    }
}

#endif