#suma Iterativa

**Análisis de complejidad temporal**

El algoritmo recorre n pasos ya que usa un ciclo que va i = 1 hasta n, por lo que su complejidad es O(n) <-- lineal para el peor de los casos.
(Ya que sumará desde 1 hasta el número positivo que querramos.)

#suma Recursiva

**Análisis de complejidad temporal**

El algoritmo se manda a llamar así mismo n veces, por los que su complejidad es O(n) <-- lineal para el peor de los casos.
(Su paso es desde n y cada llamada se resta 1 (n-1) hasta llegar al caso base)

#suma Directa

**Análisis de complejidad temporal**
El algoritmo simplemente realiza una operación con n, por lo cual su complejidad es O(1) <-- constante para el peor de los casos
(Solo emplea la fórmula (n*(n+1))/2)
