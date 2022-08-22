# `IntSet`

`IntSet` implementa la estructura de datos `set` para enteros usando un
árbol binario no-balanceado.

Es una implementación sencilla para mostrar algunas propiedades de los
`set`.

El proyecto incluye un pequeño `main` para interactuar con `IntSet`
desde la consola.

## Compilación

El proyecto esta en C++17 y usa `GCC` como compilador aunque cualquier
otro compilador debería funcionar.

Se incluye un `Makefile` para simplificar el compilado.

```shell
$ make
mkdir -p bin/
g++ -std=c++17 -pedantic -Wall -ggdb -O0 -o bin/intset intset/*.cpp
```

Nótese los flags `-O0` y `-ggdb` que le instruyen al compilador que no
optimize el código y que agregue información de debugging. Esto es
intencional para facilitar el debugging del mismo.

## Operaciones sobre `IntSet`

`bin/intset` es un pequeño programa que leerá comandos de la entrada
estándar y los ejecutara sobre un `IntSet`.

Por ejemplo el comando `a` toma un número y lo agrega al `set` mientras
el comando `h` pregunta si el número está en el `set` o no. Detrás de
escena se llaman a los métodos `IntSet::add` y `IntSet::has`
respectivamente.

```shell
$ echo "a 21 h 21 h 34" | ./bin/intset
21 added, was already in the set? false
is 21 in the set? true
is 34 in the set? false
```

Como cualquier otra implementación de `set`, `IntSet` no permite
elementos duplicados. Si un número ya en el `set`, simplemente
se retorna `false`.

```shell
$ echo "a 21 a 33 a 15 a 33 a 21" | ./bin/intset
21 added, was already in the set? false
33 added, was already in the set? false
15 added, was already in the set? false
33 added, was already in the set? true
21 added, was already in the set? true
```

El comando `l` lista el contenido del `set`. Internamente el programa
llama al método `IntSet::as_list` que retorna
los elementos del set en orden ascendente (de menor a mayor).

Agregando `l` al ejemplo anterior tenemos:

```shell
$ echo "a 21 a 33 a 15 a 33 a 21 l" | ./bin/intset
21 added, was already in the set? false
33 added, was already in the set? false
15 added, was already in the set? false
33 added, was already in the set? true
21 added, was already in the set? true
list: 15 21 33
```

Por ejemplo podemos verificar q el `IntSet` esta inicialmente vacio
listando su contenido con `l`:

```shell
$ echo "l" | ./bin/intset
list:
```

`IntSet` no soporta remover un elemento en particular pero si soporta remover
todos los elementos dejando a la estructura vacía con el método
`IntSet::clear` (comando `x`)

```shell
$ echo "a 21 a 67 l c x l c a 21 1 c" | ./bin/intset
21 added, was already in the set? false
67 added, was already in the set? false
list: 21 67
count: 2
cleared
list:
count: 0
21 added, was already in the set? false
list: 21
count: 1
```

Nótese que el comando `c` llama al método `IntSet::count` que retornar la
cantidad de elementos en el `set`. Luego de las dos primeras adiciones
la lista tiene 2 elementos (el 21 y el 67).

El comando `x` llama al método `IntSet::clear` que limpia la estructura
por lo que el listado siguiente da vacio (y `count` retorna 0).

El `set` queda en un estado perfectamente usable luego de un `clear`.
Nótese que agregar por segunda vez el 21 es posible.

Comentario adicional, `IntSet` soporta números negativos también.
En un futuro se podría refactorizar en una clase template genérica
`Set<T>` pero eso quedara para otro momento.

```shell
$ echo "a 21 a 67 a 12 a 0 a 15 a 33 a -1 a -2 l" | ./bin/intset
21 added, was already in the set? false
67 added, was already in the set? false
12 added, was already in the set? false
0 added, was already in the set? false
15 added, was already in the set? false
33 added, was already in the set? false
-1 added, was already in the set? false
-2 added, was already in the set? false
list: -2 -1 0 12 15 21 33 67
```
