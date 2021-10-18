## add
**Análisis de complejidad temporal**

El nuevo elemento se añade como árbol BST, por lo cual se va a un solo lado (izquierdo a derecho) para posteriormente reacomodarlo en la raíz, de modo que el peor de los casos, su complejidad sería O(log(n)) <-- Logarítmica, ya que nunca se recorrería todo el árbol o siempre los mismos pasos.

## remove

**Análisis de complejidad temporal**

Se busca primero que el valor si exista viendo si está en la derecha o izquierda, partiendo el árbol, para su posterior eliminación y reacomodo, de modo que su complejidad en el peor de los casos es O(log(n)) <-- Logarítmica.

## find

**Análisis de complejidad temporal**

Como los elementos más buscados o más recientes se encontrarán más cerca de la raíz, los tiempos son más cortos, de modo que en peor de los casos, simplemente se irá diviendo en dos partes hasta encontrar el valor deseado, de modo que su complejidad en el peor de los casos es O(log(n)) <-- Logarítmica
## size

**Análisis de complejidad temporal**

Ésta función simplemente retorna el tamaño del Splay Tree al momento de ir agregando nodos, de modo que su complejidad en el peor de los casos es O(1) <-- Constante.
Solo realiza un paso siempre.
