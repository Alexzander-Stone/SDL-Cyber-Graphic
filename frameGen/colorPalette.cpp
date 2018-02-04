#include "colorPalette.h"

// Default
ColorPalette::ColorPalette()
{
    r.reserve(5);
    g.reserve(5);
    b.reserve(5);
}

// Conversion constructor
ColorPalette::ColorPalette(const Uint8 red, const Uint8 green, const Uint8 blue)
{
    // Reserve space for palette choices.
    r.reserve(5);
    g.reserve(5);
    b.reserve(5);

    // Place new rgb values into the vectors.
    r.push_back(red);
    g.push_back(green);
    b.push_back(blue);
}

// Copy constructor
ColorPalette::ColorPalette(const ColorPalette& palette): r(palette.r), g(palette.g), b(palette.b)
{
}

void ColorPalette::addPalette(const Uint8 red, const Uint8 green, const Uint8 blue)
{
    // Place new rgb values into the vectors.
    r.push_back(red);
    g.push_back(green);
    b.push_back(blue);
}

Uint8 ColorPalette::getR(const int index) const
{
    return r[index];
}

Uint8 ColorPalette::getG(const int index) const
{
    return g[index];
}

Uint8 ColorPalette::getB(const int index) const
{
    return b[index];
}
