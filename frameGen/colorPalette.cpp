#include <vector>
#include "colorPalette.h"

// Conversion constructor
ColorPalette::ColorPalette(Uint8 red, Uint8 green, Uint8 blue):
{
    // Reserve space for palette choices.
    r.reserve(5);
    g.reserve(5);
    b.reserve(5);
}

// Copy constructor
ColorPalette::ColorPalette
