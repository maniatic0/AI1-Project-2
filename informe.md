# Informe II: Arboles de Juego

## Integrantes

* Christian Oliveros 13-11000
* Yuni Quintero 14-10880

## Othello

Para arreglar la implementación dada de Othello, primero notamos que esta aprovecha que las 4 piezas centrales nunca pueden estar libres por la regla de inicialización del juego, por lo que sólo se necesitan 32 bits para representar cuáles espacios están libres y 32 bits para representar el color. Luego notamos que el algoritmo de flanqueo utiliza filas y columnas precomputadas por posición que puede estar libre, para calcular si una jugada puede flanquear a otra ficha. Por lo tanto, reparar el código fue solo agregar la iteración sobre ambas diagonales.

Para la iteración sobre los hijos de un tablero, decidimos hacer los ciclos explícitos para evitar incurrir en uso de memoria en vectores que contengan los hijos. Esto hizo cambiar un poco el código de los algoritmos, dado que hay que manejar el caso de que un jugador pase (que sólo ocurre si no puede hacer nada), pero esta modificación fue pequeña en los algoritmos.

## Resultados

### Negamax (minmax)

Extracting principal variation (PV) with 33 plays ... done!
Algorithm: Negamax (minmax version)
Moving along PV:

| Play | Moves: | Value |     Expanded     |     Generated     |     Seconds    | Generated/second        |
|:--:|:------------:|:--------:|:-------------------:|:--------------------:|:----------------:|-------------------------------|
| 34 | White | -4 |    0     |     0     |     0    | -nan        |
| 33 | Black | -4 |    1     |     1     |     0    | inf         |
| 32 | White | -4 |    4     |     4     |     0    | inf         |
| 31 | Black | -4 |    5     |     5     |     0    | inf         |
| 30 | White | -4 |    12    |     12    |     0    | inf         |
| 29 | Black | -4 |    13    |     13    |     0    | inf         |
| 28 | White | -4 |    90    |     90    |     0    | inf         |
| 27 | Black | -4 |   176    |    176    |     0    | inf         |
| 26 | White | -4 |   1047   |    1047   |     0    | inf         |
| 25 | Black | -4 |   4474   |    4474   |     0    | inf         |
| 24 | White | -4 |  11919   |   11919   | 0.015625 | 762816      |
| 23 | Black | -4 |  76009   |   76009   |  0.0625  | 1.21614e+06 |
| 22 | White | -4 |  424451  |   424451  |  0.40625 | 1.0448e+06  |
| 21 | Black | -4 | 3441360  |  3441360  |   2.875  | 1.19699e+06 |
| 20 | White | -4 | 12909985 |  12909985 |  11.5312 | 1.11957e+06 |
| 19 | Black | -4 | 89235221 |  89235221 |  74.1094 | 1.2041e+06  |
| 18 | White | -4 |865108507 | 865108507 |  673.312 | 1.28485e+06 |

### Negamax (alpha-beta)

### Scout

### Negascout