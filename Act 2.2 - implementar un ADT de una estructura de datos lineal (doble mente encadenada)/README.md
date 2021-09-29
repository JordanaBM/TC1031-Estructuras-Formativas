## insertion

**Análisis de complejidad temporal**

La insersión de elementos es en el peor de los casos lineal O(n), ya que después de insertar el primer nodo (que seria O(1)) tiene que recorrer toda la lista
ligada hasta llegar al final y añadir el nuevo nodo.

## search

**Análisis de complejidad temporal**

Al buscar un elemento se tiene que recorrer la lista ligada, en el peor de los casos (donde el elemento que quieres buscar es que se encuentra al final) 
sería lineal O(n).

## update

**Análisis de complejidad temporal**

Al actualizar nodos, el peor de los casos sería que el elemento a actualizar fuera la última posición, por lo cual en el peor de los casos se tendría que recorrer
toda la lista ligada O(n).

## deleteAt

**Análisis de complejidad temporal**

Al eliminar un nodo, de igual forma se recorre toda la lista, en el peor de los casos se tendría tiempo de O(n) lineal, donde el elemento a eliminar es el penúltimo 
de la lista, ya que para eliminar el primero o último seria constante.

