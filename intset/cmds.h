#include <iostream>
#include "intset.h"

// Este TDA lee de un stream de entrada (como `std::cin`)
// comandos para controlar un `IntSet` y ver los resultados
// (como en `std::cout`).
//
// Estos tipos de TDAs son útiles para hacer partes de un programa
// interactivos (aunque es mas divertido con programas mas grandes
// que este simple demo).
//
// Hacer partes interactivas permite **testearlas** por separado
// y como veras, no es muy complicado.
class IntSetController {
    private:
        IntSet set;

        std::istream &in;
        std::ostream &out;
        std::ostream &err;

    public:
        // Por conveniencia permitiremos usar cualquier stream de entrada/salida
        //
        // Podría ser `std::cin`, `std::cout` and `std:cerr` o podría
        // ser un `std::ifstream` / `std::ofstream` para usar archivos.
        IntSetController(std::istream &in, std::ostream &out, std::ostream &err);

        // Procesa los comandos leídos del stream <in>
        // e imprime los resultados en el stream <out>.
        // Errores van al stream <err>.
        //
        // El procesamiento termina hasta que se procesen <limit> comandos
        // o bien hasta llegar el fin de archivo.
        //
        // Si <limit> es cero o negativo, se procesa todo el archivo.
        int process(int limit=0);
};
