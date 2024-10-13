#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "json_reader.h"
#include "request_handler.h"

using namespace std;

int main() {

    std::ostringstream out;
    TransportCatalogue catalogue;

    std::string requests;
    while (std::getline(std::cin, line)) {
        requests += line;
    }
    std::cout << out.str();

}