#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

class Tower {
   public:
    // конструктор и метод SetDisks нужны, чтобы правильно создать башни
    Tower(int disks_num) {
        FillTower(disks_num);
    }

    int GetDisksNum() const {
        //  cout << disks_.size() << endl;
        return disks_.size();
    }

    void SetDisks(int disks_num) {
        FillTower(disks_num);
    }

    // добавляем диск на верх собственной башни
    // обратите внимание на исключение, которое выбрасывается этим методом
    void AddToTop(int disk) {
        int top_disk_num = disks_.size() - 1;  // порядковый номер последнего элемента
        // проверка того, что в этой башне есть элементы и что последний элемент больше пришедшего
        if (disks_.size() != 0 && disk >= disks_[top_disk_num]) {
            cout << "хуй"s;
            //  throw invalid_argument("Невозможно поместить большой диск на маленький");
        } else {
            disks_.push_back(disk);
        }
    }

    // disks_num - количество перемещаемых дисков
    // destination - конечная башня для перемещения
    // buffer - башня, которую нужно использовать в качестве буфера для дисков
    void MoveDisks(int disks_num, Tower& start, Tower& target, Tower& buffer) {
        if (disks_num != 0) {
            MoveDisks(disks_num - 1, start, buffer, target);
            target.AddToTop(start.disks_.back());
            start.disks_.pop_back();
            MoveDisks(disks_num - 1, buffer, target, start);
        }
    }

   private:
    vector<int> disks_;

    // используем приватный метод FillTower, чтобы избежать дубликации кода
    void FillTower(int disks_num) {
        for (int i = disks_num; i > 0; i--) {
            disks_.push_back(i);
        }
    }
};

void SolveHanoi(vector<Tower>& towers) {
    int disks_num = towers[0].GetDisksNum();
    // towers[0].GetDisksNum();
    // towers[2].GetDisksNum();
    towers[0].MoveDisks(disks_num, towers[0], towers[2], towers[1]);
    // towers[0].GetDisksNum();
    // towers[2].GetDisksNum();
    // допишите функцию, чтобы на towers[0] было 0 дисков,
    // на towers[1] 0 дисков,
    // и на towers[2] было disks_num дисков
}

int main() {
    int towers_num = 3;
    int disks_num = 3;
    vector<Tower> towers;
    // Добавим в вектор три пустые башни.
    for (int i = 0; i < towers_num; ++i) {
        towers.push_back(0);
    }
    // Добавим на первую башню три кольца.
    towers[0].SetDisks(disks_num);

    SolveHanoi(towers);
}