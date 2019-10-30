# Informe II: Arboles de Juego

## Integrantes

* Christian Oliveros 13-11000
* Yuni Quintero 14-10880

## Othello

Para arreglar la implementación dada de Othello, primero notamos que esta aprovecha que las 4 piezas centrales nunca pueden estar libres por la regla de inicialización del juego, por lo que sólo se necesitan 32 bits para representar cuáles espacios están libres y 32 bits para representar el color. Luego notamos que el algoritmo de flanqueo utiliza filas y columnas precomputadas por posición que puede estar libre, para calcular si una jugada puede flanquear a otra ficha. Por lo tanto, reparar el código fue solo agregar la iteración sobre ambas diagonales.

Para la iteración sobre los hijos de un tablero, decidimos hacer los ciclos explícitos para evitar incurrir en uso de memoria en vectores que contengan los hijos. Esto hizo cambiar un poco el código de los algoritmos, dado que hay que manejar el caso de que un jugador pase (que sólo ocurre si no puede hacer nada), pero esta modificación fue pequeña en los algoritmos.

## Resultados

Se ejecutaron los algoritmos con un timeout de 15 minutos debido a limitaciones con el tiempo de computo. No se esperaba que estos pudiesen terminar de correr en un corto plazo, sin embargo a los 15 minutos se puede analizar cuales algoritmos lograron alcanzar la mayor cantidad de jugadas.

### Como ejecutar los algoritmos:

1. Situarse en la carpeta principal del proyecto
2. `make`
3. `./<numero respectivo del algoritmo>`

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

| Play | Moves: | Value |     Expanded     |     Generated     |     Seconds    | Generated/second        |
|:--:|:------------:|:--------:|:-------------------:|:--------------------:|:----------------:|-------------------------------|
| 34 | White | -4 |    0     |     0     |     0    | -nan        |
| 33 | Black | -4 |    1     |     1     |     0    | inf         |
| 32 | White | -4 |    4     |     4     |     0    | inf         |
| 31 | Black | -4 |    5     |     5     |     0    | inf         |
| 30 | White | -4 |    12    |     12    |     0    | inf         |
| 29 | Black | -4 |    13    |     13    |     0    | inf         |
| 28 | White | -4 |    26    |     26    |     0    | inf         |
| 27 | Black | -4 |   81    |    81    |     0    | inf         |
| 26 | White | -4 |   237   |    237   |     0    | inf         |
| 25 | Black | -4 |   1000   |    1000   |     0    | inf         |
| 24 | White | -4 |  1510   |   1510   | 0 | inf      |
| 23 | Black | -4 |  4171   |   4171   |  0  | inf |
| 22 | White | -4 |  8672  |   8672  |  0.015625 | 555008  |
| 21 | Black | -4 | 98117  |  98117  |   0.078125  | 1.2559e+06 |
| 20 | White | -4 | 128839 |  128839 |  0.125 | 1.03071e+06 |
| 19 | Black | -4 | 275405 |  275405 |  0.25 | 1.10162e+06  |
| 18 | White | -4 |1240399 | 1240399 |  1.04688 | 1.18486e+06 |
| 17 | Black | -4 |2035473 | 2035473 |  1.73438 | 1.17361e+06 |
| 16 | White | -4 |29089491 | 29089491 |  24.5312 | 1.18581e+06 |
| 15 | Black | -4 |44357525 | 44357525 |  36.5156 | 1.21475e+06 |
| 14 | White | -4 |108945024 | 108945024 |  90.4062 | 1.20506e+06 |
| 13 | Black | -4 |416778848 | 416778848 |  328.469 | 1.26885e+06 |

### Scout

| Play | Moves: | Value |     Expanded     |     Generated     |     Seconds    | Generated/second        |
|:--:|:------------:|:--------:|:-------------------:|:--------------------:|:----------------:|-------------------------------|
| 34 | White | -4 |    0     |     0     |     0    | -nan        |
| 33 | Black | -4 |    1     |     1     |     0    | inf         |
| 32 | White | -4 |    2     |     3     |     0    | inf         |
| 31 | Black | -4 |    3     |     4     |     0    | inf         |
| 30 | White | -4 |    10    |     11    |     0    | inf         |
| 29 | Black | -4 |    11    |     12    |     0    | inf         |
| 28 | White | -4 |    12    |     15    |     0    | inf         |
| 27 | Black | -4 |   13    |    17    |     0    | inf         |
| 26 | White | -4 |   51   |    72   |     0    | inf         |
| 25 | Black | -4 |   194   |    281   |     0.001196    | 234950         |
| 24 | White | -4 |  250   |   365   | 0.001912 | 190900      |
| 23 | Black | -4 |  307   |   449   |  0.003694  | 121548 |
| 22 | White | -4 |  525  |   755  |  0.004694 | 160844  |
| 21 | Black | -4 | 1799  |  2449  |   0.021086  | 116143 |
| 20 | White | -4 | 2520 |  3618 |  0.038563 | 93820.5 |
| 19 | Black | -4 | 3231 |  4776 |  0.085237 | 56032  |
| 18 | White | -4 |7380 | 10276 |  0.26152 | 39293.4 |
| 17 | Black | -4 |8422 | 11993 |  0.491172 | 24417.1 |
| 16 | White | -4 |41260 | 57988 |  3.18967 | 18179.9 |
| 15 | Black | -4 |90051 | 128035 |  12.5984 | 10162.8 |
| 14 | White | -4 |133591 | 188872 |  29.0234 | 6507.57 |
| 13 | Black | -4 |280257 | 399568 |  112.153 | 3562.69 |
| 12 | White | -4 |952914 | 1335978 |  303.67 | 4399.45 |

Es relevante mencionar la diferencia entre los nodos expandidos y generados. En Scout se hace pruning usando test, por lo tanto no se expande todo lo generado.

### Negascout

| Play | Moves: | Value |     Expanded     |     Generated     |     Seconds    | Generated/second        |
|:--:|:------------:|:--------:|:-------------------:|:--------------------:|:----------------:|-------------------------------|
| 34 | White | -4 |    0     |     0     |     1.99978e-06    | 0        |
| 33 | Black | -4 |    1     |     1     |     2.00002e-06    | 499996         |
| 32 | White | -4 |    4     |     4     |     5.00004e-06    | 799994         |
| 31 | Black | -4 |    5     |     5     |     4.00003e-06    | 1.24999e+06         |
| 30 | White | -4 |    17    |     17    |     1.29999e-05    | 1.30771e+06         |
| 29 | Black | -4 |    18    |     18    |     1.30001e-05    | 1.3846e+06         |
| 28 | White | -4 |    31    |     31    |     2.19999e-05    | 1.4091e+06         |
| 27 | Black | -4 |   81    |    81    |     4.99999e-05    | 1.62e+06         |
| 26 | White | -4 |   389   |    389   |     0.00024    | 1.62083e+06         |
| 25 | Black | -4 |   1633   |    1633   |     0.001099    | 1.4859e+06         |
| 24 | White | -4 |  2408   |   2408   | 0.00178 | 1.35281e+06      |
| 23 | Black | -4 |  3827   |   3827   |  0.00184  | 2.07989e+06 |
| 22 | White | -4 |  9751  |   9751  |  0.004699 | 2.07512e+06  |
| 21 | Black | -4 | 46141  |  46141  |   0.020384  | 2.26359e+06 |
| 20 | White | -4 | 85449 |  85449 |  0.037684 | 2.26751e+06 |
| 19 | Black | -4 | 189734 |  189734 |  0.082067 | 2.31194e+06  |
| 18 | White | -4 |572996 | 572996 |  0.247376 | 2.3163e+06 |
| 17 | Black | -4 |1115311 | 1115311 |  0.487386 | 2.28835e+06 |
| 16 | White | -4 |7142244 | 7142244 |  3.21027 | 2.22481e+06 |
| 15 | Black | -4 |25706086 | 25706086 |  11.5093 | 2.23351e+06 |
| 14 | White | -4 |61505888 | 61505888 |  26.496 | 2.32133e+06 |
| 13 | Black | -4 |240389629 | 240389629 |  98.7573 | 2.43414e+06 |
| 12 | White | -4 |622049286 | 622049286 |  259.743 | 2.39486e+06 |

Se puede concluir que el mejor algoritmo para realizar la busqueda sobre el arbol correspondiente al juego Othello es Negascout, como se puede observar es el que llego a la mayor profundidad en menor tiempo: 259.743 segundos, comparado a Scout que tambien llego a la jugada 12, no obstante en 303.67 segundos. 