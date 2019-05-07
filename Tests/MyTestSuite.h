#include <cxxtest/TestSuite.h>
#include "../Bloques/bloque_metal.h"
#include "../ElementosBloque/boton.h"

class MyTestSuite : public CxxTest::TestSuite
{
public:
    /* TESTS BLOQUE METAL */
    void testBloqueMetalOcupadoDespuesDeColocarElemento( void ) {
        Posicion posicion(0, 0);
        BloqueMetal bloque(posicion);
        Boton boton(posicion);
        bloque.setElemento(std::move(boton));
        TS_ASSERT(bloque.tieneElemento());
    }
};