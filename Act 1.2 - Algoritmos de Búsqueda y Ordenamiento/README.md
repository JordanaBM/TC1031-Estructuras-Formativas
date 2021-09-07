## ordenaSeleccion

**Análisis de complejidad temporal**

El ordenamiento está compuesto de dos ciclos, el primero donde se recorre hasta el final del vector y el segundo donde se van comparando
los números y colocando el mínimo en la primera posición, por lo cual su complejidad es O(n^2) en el peor de los casos.

## ordenaBurbuja

**Análisis de complejidad temporal**

El ordenamiento de igual forma está compuesto de dos ciclos, uno donde reccore todo el vector y otro que va a comparando los números y 
cambiando su posición, por lo cual su complejidad es O(n^2) en el peor de los casos.

## ordenaMerge

**Análisis de complejidad temporal**

El ordenamiento usa recursivadad, de modo que va diviendiendo el array en dos partes, creando un árbol hasta llegar a un sólo número, por lo 
cual su complejidad es O( n log (n)) en el peor de los casos. <--(ya que no es lineal (no hace n pasos), ni constante(no realiza siempre el mismo número))

## busqSecuencial

**Análisis de complejidad temporal**

Para encontrar un elemento, éste algoritmo recorre las n posiciones hasta toparse con el elemento deseado, por lo cual su complejidad es
O(n) en el peor de los casos.

## busqBinaria

**Análisis de complejidad temporal**

Para encontrar un elemento, éste algoritmo recorre divide el vector en dos cada vez que da una vuelta recursiva, cabe destacar que tiene
que estar ordenado para poder decidir si parte en dos la izquierda o derecha, por lo cual su complejidad es de O( n log (n)) en el peor de
los casos <-- (ya que no es lineal (no hace n pasos), ni constante(no realiza siempre el mismo número))
