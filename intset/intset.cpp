
#include "intset.h"

#include <list>
#include <stack>

#include <cassert>

IntSet::node_t* const* IntSet::find_node_for(int val) const {
    if (!root)
        return &root;

    node_t* const* current = &root;

    while (*current) {
        if ((unsigned)(*current)->value == (unsigned)val)
            return current;
        else if ((unsigned)(*current)->value > (unsigned)val)
            current = &(*current)->left;
        else
            current = &(*current)->right;
    }

    return current;
}

IntSet::IntSet() : root(nullptr), count_(0) {}

bool IntSet::has(int val) const {
    node_t* const* n = find_node_for(val);
    return (*n) == nullptr;
}

bool IntSet::add(int val) {
    // `IntSet::find_node_for` es un método constante (no modifica a la estructura)
    // y por ello retorna un puntero constante a un puntero a nodo
    // (`node_t* const*`).
    //
    // Pero `IntSet::add` *debe* modificar a la estructura por lo que
    // tenemos que remover el `const` haciendo un `const_cast<node_t**>`
    // para transformar (`node_t* const*`) en un (`node_t**`).
    //
    // Nótese que hacer `const_cast` es *muy atípico* y es signo
    // de que algo no esta bien usado. Pensá varias veces antes de usarlo.
    //
    // En este caso el uso de `const_cast` esta justificado ya
    // que `IntSet::add` *realmente* necesita de modificar
    // el objeto y queremos *reutilizar* `IntSet::find_node_for`
    node_t **n = const_cast<node_t**>(find_node_for(val));
    if (*n)
        return true; // ya estaba presente

    (*n) = new node_t {val, nullptr, nullptr};
    count_ += 1;
    return false;
}

std::list<int> IntSet::as_list() const {
    std::list<int> result;

    // Set vació, lista vacía
    if (!root)
        return result;

    // Haremos un recorrido en pre-order, o sea,
    // intentaremos ir al nodo mas a la izquierda (left)
    // primero siempre.
    std::stack<node_t*> stack;
    stack.push(root);

    node_t *current = root->left;

    while (!stack.empty()) {

        // Buscamos el `int` mas chico (left)
        while (current) {
            stack.push(current);
            current = current->left;
        }

        current = stack.top();
        stack.pop();

        result.push_back(current->value);

        // Vamos para la derecha solo un pase y luego empezamos
        // el while-loop principal una vez más
        current = current->right;
    }

    return result;
}

void IntSet::clear() {
    std::list<node_t*> to_remove;
    to_remove.push_back(root);

    while (!to_remove.empty()) {
        node_t *current = to_remove.back();
        to_remove.pop_back();

        // Los asserts son para chequear invariantes de nuestros TDAs:
        // *"cosas que jamas deberian fallar"*
        //
        // En este caso es un invariante que `to_remove` no puede
        // tener punteros `null`.
        //
        // Yo estoy *super seguro* q no habrá nulls y si los hubiese
        // todo el programa debería frenar ya que hay un bug.
        // Por eso pongo un `assert`.
        assert (current != nullptr);

        if (current->left)
            to_remove.push_back(current->left);

        if (current->right)
            to_remove.push_back(current->right);

        delete current;
    }

    root = nullptr;
    count_ = 0;
}

size_t IntSet::count() const {
    return count_;
}

bool IntSet::empty() const {
    return count_ == 0;
}

IntSet::~IntSet() {
    clear();
}

