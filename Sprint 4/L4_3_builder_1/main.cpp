#include "builder.h"
#include <iostream>

using namespace std;

int main() {
    Builder tom;
    Wall w(3.5, 2.45);
    cout << tom.CalcBricksNeeded(w) << endl;
    
    // Попросите Тома посчитать кирпичи для стены 3.5 х 2.45
}