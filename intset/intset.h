#ifndef INTSET_H_
#define INTSET_H_

#include <list>

// Esta clase implementa la estructura set de integers: `IntSet`.
//
// Como todo set, `IntSet` permite agregar elementos (`int`)
// si no están ya presentes.
// En otras palabras el set no permite duplicados.
//
// Ademas podremos preguntar si un `int` esta o no en el set
// y podemos iterar sobre los elementos del set.
//
// Nota de implementación:
//
// `IntSet` esta basado en un binary tree no-balanceado. En el caso feliz
// tendrá una performance O(log n) pero en el peor caso, por ser no-balanceado,
// sera O(n).
//
// La implementación de `IntSet` es pobrísima en comparación a la implementación
// de `std::set` (basado en binary trees balanceados) o de `std::unordered_set`
// (basado en hashes), ambos de la librería estándar de C++.
//
// Sin mencionar q `IntSet` tiene una implementación con bugs puestos
// a propósito. Estas para practicar debugging, no?!
//
// En otras palabras, *no* uses esta lib, usa la librería estándar.
//
// Para mayor info de que podes hacer con la lib estándar, te dejo
// los links a la doc de referencia:
//
// [`std::set`](https://cplusplus.com/reference/set/set/)
// [`std::unordered_set`](https://cplusplus.com/reference/unordered_set/unordered_set/)
class IntSet {
    private:
        // Esta estructura es interna a Set y no debería
        // ser usada afuera, por eso la dejamos en la sección private.
        struct node_t {
            int value;
            struct node_t *left;
            struct node_t *right;
        };

        // El node principal, raíz del árbol
        node_t *root;

        // Cuantos elementos hay en el set
        size_t count_;

        // Buscamos un nodo dentro del árbol para el valor dato.
        //
        // Si el valor ya esta presente en el árbol entonces:
        //
        //  ```
        //  (*find_node_for(X))->value == X
        //  ```
        //
        // Si el valor no esta presente entonces:
        //
        //  ```
        //  (*find_node_for(X)) == nullptr
        //  ```
        //
        // Al estar retornando un puntero doble, podrás allocar
        // un nodo nuevo para guardar el valor en el árbol en
        // caso de quererlo.
        node_t* const* find_node_for(int val) const;

    public:
        IntSet();

        // Retorna true si el int ya esta en el árbol, false de otro modo
        bool has(int val) const;

        // Agrega un elemento al set, retorna si ya estaba presente o no
        bool add(int val);

        // Retorna una lista ordenada de menor a mayor con los ints
        // de este set.
        std::list<int> as_list() const;

        // Elimina el set dejándolo vacío
        void clear();

        // Retorna cuantos elementos hay en el set
        size_t count() const;

        // Retorna si el el set esta vacío o no
        bool empty() const;

        ~IntSet();
};

#endif
