// Color palette for the console. Goes from darkest to brightest values.
#include <vector>

class ColorPalette
{
    public:

        Uint8 getR();
        Uint8 getG();
        Uint8 getB();
        const addPalette(Uint8 red, Uint8 green, Uint8 blue);

        // Conversion
        ColorPalette(Uint8 red, Uint8 green, Uint8 blue); 
        // Copy
        ColorPalette(const ColorPalette&);

    private:
        vector <Uint8> r;
        vector <Uint8> g;
        vector <Uint8> b;
};
