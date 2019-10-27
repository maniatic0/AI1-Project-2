# Informe II: Arboles de Juego

## Integrantes

* Christian Oliveros 13-11000
* Yuni Quintero 14-10880

## Othello

Para arreglar la implementación dada de Othello, primero notamos que esta aprovecha que las 4 piezas centrales nunca pueden estar libres por la regla de inicialización del juego, por lo que sólo se necesitan 32 bits para representar cuáles espacios están libres y 32 bits para representar el color. Luego notamos que el algoritmo de flanqueo utiliza filas y columnas precomputadas por posición que puede estar libre, para calcular si una jugada puede flanquear a otra ficha. Por lo tanto, reparar el código fue solo agregar la iteración sobre ambas diagonales.

Para la iteración sobre los hijos de un tablero, decidimos hacer los ciclos explícitos para evitar incurrir en uso de memoria en vectores que contengan los hijos. Esto hizo cambiar un poco el código de los algoritmos, dado que hay que manejar el caso de que un jugador pase (que sólo ocurre si no puede hacer nada), pero esta modificación fue pequeña en los algoritmos.

## Resultados

TODO