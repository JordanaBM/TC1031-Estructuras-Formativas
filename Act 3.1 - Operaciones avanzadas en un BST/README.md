## visit

**Análisis de complejidad temporal**

Despliega los datos de 4 formas diferentes
1. Preorder
2. Inorder
3. Postorder
4. Level by level

Todos estos recorren el árbol completo, ya que es necesario imprimir todos sus valores, por lo cual si complejidad en el peor de los casos es O(n) <-- lineal.

## height

**Análisis de complejidad temporal**

Es necesario recorrer el árbol completo para poder calcular la altura máxima que tiene,  por lo cual su complejidad en el peor de los casos es O(n) <-- lineal.

## ancestors

**Análisis de complejidad temporal**

Se recorre siempre la "mitad del árbol", dependiendo si nuestro valor a buscar es menor o mayor, por lo cual su complejidad es n/2 normalmente, de todos modos sabemos que esto se redondea a O(n) <-- lineal, el cual es el peor de los casos.

## whatlevelamI

**Análisis de complejidad temporal**

Se recorre el árbol completo hasta encontrar el valor del cual se requiere el nivel , por lo cual el peor de los casos en donde el último nodo que se revise sea el que debemos regresar sus nivel su complejidad será de O(n) <-- lineal.
