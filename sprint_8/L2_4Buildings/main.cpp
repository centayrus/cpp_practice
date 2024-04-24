// buildings.h

#include <vector>

namespace buildings {
struct Materials {};

Materials GetMaterials();

class Skyscraper {
    struct Floor {
        /* 1 */ buildings::Materials materials;
        int number;
    };

    Floor BuildFloor(/* 2 */ buildings::Materials materials);
    void BuildRoof(buildings::Materials materials);
    int GetMaterials(buildings::Materials source);

    bool IsComplete() const {
        return static_cast<int>(floors_.size()) < total_floors_;
    }

public:
    void Build() {
        while (!IsComplete()) {
            auto materials = /* 3 */ buildings::GetMaterials();
            floors_.push_back(BuildFloor(std::move(materials)));
        }
    }

private:
    int total_floors_ = 100;
    std::vector<Floor> floors_;
    /* 4 */ buildings::Materials roof_;
};
}  // namespace buildings

// buildings.cpp
#include "buildings.h"

using namespace std;

/* 5 */ buildings::Skyscraper::Floor /* 6 */ buildings::Skyscraper::BuildFloor(/* 7 */ buildings::Materials materials) {
    /* 8 */ buildings::Materials materials_copy = move(materials);
    return Floor{move(materials_copy), static_cast<int>(floors_.size())};
}

namespace buildings {
void /* 9 */ buildings::Skyscraper::BuildRoof(/* 10 */ buildings::Materials materials) {
    /* 11 */ buildings::Materials materials_copy = move(materials);
    roof_ = move(materials_copy);
}
}  // namespace buildings