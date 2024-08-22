#include <cassert>
#include <iostream> 
#include <stdexcept>
#include <string>

using namespace std;

class House {
public:
    House(int len, int wid, int hei) : length(len), width(wid), heith(hei) {
    }
    int GetLength() const {
        return length;
    }
    int GetWidth() const {
        return width;
    }
    int GetHeight() const {
        return heith;
    }

private:
    int length;
    int width;
    int heith;
};

class Resources {
public:
    Resources(int bricks) : brick_count(bricks) {
      //  std::cout << "Resources is created" << '\n';
    };
    void TakeBricks(int count) {
        if (count < 0 || count > brick_count) {
            throw std::out_of_range("out of bound"s);
        }
        brick_count -= count;
        
    }
    int GetBrickCount() const {
        return brick_count;
    }

private:

    int brick_count;
};

struct HouseSpecification {
    int length = 0;
    int width = 0;
    int height = 0;
};

class Builder {
public:
    Builder(Resources &res)
        : resources(&res) {};
    House BuildHouse(HouseSpecification spec) {
        House house(spec.length, spec.width, spec.height);
        int brick_cou = (2*(house.GetLength() + house.GetWidth())*4)*(house.GetHeight()*8);
        if (((*resources).GetBrickCount() - brick_cou) < 0) {
            throw std::runtime_error("bricks lose"s);
        }
        (*resources).TakeBricks(brick_cou);
        return house;
    };

private:
    Resources* resources;
};

int main() {
    Resources resources{10000};
    Builder builder1{resources};
    Builder builder2{resources};
    House house1 = builder1.BuildHouse(HouseSpecification{12, 9, 3});

    assert(house1.GetLength() == 12);
    assert(house1.GetWidth() == 9);
    assert(house1.GetHeight() == 3);
    cout << resources.GetBrickCount() << " bricks left"s << endl;

    House house2 = builder2.BuildHouse(HouseSpecification{8, 6, 3});
    assert(house2.GetLength() == 8);
    cout << resources.GetBrickCount() << " bricks left"s << endl;

    House banya = builder1.BuildHouse(HouseSpecification{4, 3, 2});
    assert(banya.GetHeight() == 2);
    cout << resources.GetBrickCount() << " bricks left"s << endl;
}