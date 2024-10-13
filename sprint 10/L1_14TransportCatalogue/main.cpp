#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "json_reader.h"
#include "request_handler.h"

using namespace std;

int main() {

   // std::ostringstream out;

    std::string requests;
    while (std::getline(std::cin, line)) {
        requests += line;
    }

    JsonReader reader;
    reader.LoadData(requests);
}