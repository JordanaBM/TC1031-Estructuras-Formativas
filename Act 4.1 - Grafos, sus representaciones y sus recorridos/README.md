## loadGraphList

**Análisis de complejidad temporal**

La función abre el archivo y recorre línea por línea de acuerdo a los nodos que desamos que tenga nuestra lista, por lo cual su complejidad es O(n) <-- lineal en el peor de los casos.

## DFS

**Análisis de complejidad temporal**

El algoritmo va eliminando el elemento que se encuentra hasta arriba del stack, por tanto, en el peor de los casos, el elemento que se encuentra hasta abajo sería del cual se quiere buscar su camino, por tanto en el peor de los casos tendría que recorrer todos los nodos(vertices) y sus edges(bordes) de modo que su complejidad es O(V +E) <-- que podría acercarse más a lineal.

## BFS

**Análisis de complejidad temporal**

El algoritmo va eliminando el elemento que se encuentra al principio del queue, por tanto, en el peor de los casos, el elemento que se encuentra hasta el final sería el que se requiere encontrar su camino, por tanto en el peor de los casos tendría que recorrer todos los nodos(vertices) y sus edges(bordes) de modo que su complejidad de igual forma es O(V +E) <-- que podría acercarse más a lineal.
