// Color palette for the console. Goes from darkest to brightest values.
#include <vector>
#include <SDL.h>

class ColorPalette
{
    public:
        
        // Default
        ColorPalette();
        // Conversion (r,g,b)
        ColorPalette(const Uint8, const Uint8, const Uint8); 
        // Copy
        ColorPalette(const ColorPalette&);


        const std::vector<Uint8> getR() const;
        const std::vector<Uint8> getG() const;
        const std::vector<Uint8> getB() const;
        void addPalette(const Uint8, const Uint8, const Uint8); // r, g, b

    private:
        std::vector <Uint8> r;
        std::vector <Uint8> g;
        std::vector <Uint8> b;
};
