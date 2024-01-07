#include "wall.h"

class Painter {
public:
    Wall::Color Paint(Wall &wall, Wall::Color clr) {
        wall.SetColor(clr);
        return wall.GetColor();
    }
};