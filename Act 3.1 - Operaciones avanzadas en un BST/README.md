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

Se recorre el árbol completo hasta encontrar el valor del cual se requieren los ancestros, por lo cual el peor de los casos en donde el último nodo que se revise sea el que debamos regresar sus ancentros su complejidad será O(n) <-- lineal.

## whatlevelamI

**Análisis de complejidad temporal**

Se recorre el árbol completo hasta encontrar el valor del cual se requiere el nivel , por lo cual el peor de los casos en donde el último nodo que se revise sea el que debemos regresar sus nivel su complejidad será de O(n) <-- lineal.
