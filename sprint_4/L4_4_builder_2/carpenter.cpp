#include "carpenter.h"
#include "square_calculation.h"

int Carpenter::CalcShelves(Wall &wall) const {
    double height = wall.GetHeight();
    double width = wall.GetWidth();
    return static_cast<int>(CalcSquare(width, height) / 2);
}
