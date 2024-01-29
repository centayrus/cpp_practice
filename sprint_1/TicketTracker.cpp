#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
    NEW,          // новая
    IN_PROGRESS,  // в разработке
    TESTING,      // на тестировании
    DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

// struct PersonProgress {
//     string name;
//     TasksInfo progress;
// };

class TeamTasks {
   public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo& GetPersonTasksInfo(const string& person) const {
        return person_progress_.at(person);
    }

    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string& person) {
        // добавляем все статусы чтобы не пройтись итератором по всем
        person_progress_[person][TaskStatus::NEW] += 1;
        person_progress_[person][TaskStatus::IN_PROGRESS] += 0;
        person_progress_[person][TaskStatus::TESTING] += 0;
        person_progress_[person][TaskStatus::DONE] += 0;
    };

    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count) {
        TasksInfo update_tasks, untouch_tasks;
        untouch_tasks = person_progress_.at(person);
        int add_amount = 0;
        for (auto& w : person_progress_.at(person)) {
            update_tasks[w.first] = add_amount;
            if (task_count > w.second) {
                add_amount = w.second;
                task_count -= w.second;
            } else {
                add_amount = task_count;
                task_count=0;
            };
            untouch_tasks.at(w.first) -= add_amount;

            if (w.first != TaskStatus::DONE) {
            person_progress_.at(person).at(w.first) -= add_amount;
            }
        }

        for (auto& w : update_tasks) {
            person_progress_.at(person).at(w.first) += update_tasks.at(w.first);
        }
        // статус DONE не интересует
        untouch_tasks.erase(TaskStatus::DONE);
        return {update_tasks, untouch_tasks};
    };

   private:
    map<string, TasksInfo> person_progress_;
};

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь.
void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks"s
         << ", "s << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress"s
         << ", "s << tasks_info[TaskStatus::TESTING] << " tasks are being tested"s
         << ", "s << tasks_info[TaskStatus::DONE] << " tasks are done"s << endl;
}

int main() {
    TeamTasks tasks;
    tasks.AddNewTask("Ilia"s);
    for (int i = 0; i < 10; ++i) {
        tasks.AddNewTask("Ivan"s);
    }
     for (int i = 0; i < 118; ++i) {
        tasks.AddNewTask("Ilia"s);
    }

    cout << "Ilia's tasks: "s;
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"s));
    cout << "Ivan's tasks: "s;
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"s));

    TasksInfo updated_tasks, untouched_tasks;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan"s, 9);
    cout << "Updated Ivan's tasks: "s;
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: "s;
    PrintTasksInfo(untouched_tasks);

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan"s, 899);
    cout << "Updated Ivan's tasks: "s;
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: "s;
    PrintTasksInfo(untouched_tasks);
        tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan"s, 555);
    cout << "Updated Ivan's tasks: "s;
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: "s;
    PrintTasksInfo(untouched_tasks);
            tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan"s, 555);
    cout << "Updated Ivan's tasks: "s;
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: "s;
    PrintTasksInfo(untouched_tasks);
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ilia"s, 111);
    cout << "Updated Ilia's tasks: "s;
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ilia's tasks: "s;
    PrintTasksInfo(untouched_tasks);

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan"s, 111);
    cout << "Updated Ivan's tasks: "s;
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: "s;
    PrintTasksInfo(untouched_tasks);
        tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan"s, 89);
    cout << "Updated Ivan's tasks: "s;
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: "s;
    PrintTasksInfo(untouched_tasks);

        tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ilia"s, 47);
    cout << "Updated Ilia's tasks: "s;
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ilia's tasks: "s;
    PrintTasksInfo(untouched_tasks);

}