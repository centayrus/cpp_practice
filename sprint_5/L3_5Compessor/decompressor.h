#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

inline bool DecodeRLE(const std::string& src_name, const std::string& dst_name) {
    std::ifstream in(src_name, std::ios::binary);
    if (!in) {
        return false;
    }
    unsigned char header;
   // int i = 0;
    std::ofstream out(dst_name, std::ios::binary);
    do {
        header = in.get();
      //  std::cout << i++ << std::endl;
        int block_type = (header & 1);
        int data_size = (header >> 1) + 1;
       // std::cout << "data_size: "s << data_size << std::endl;
        std::vector<char> buf(data_size);
        // распаковка НЕ сжатого содержимого, записываем все содержимое
        if (!block_type) {
            in.read(buf.data(), data_size);
         // std::cout << "НЕ сжато: "s << buf.data() << std::endl; 
            out.write(buf.data(),in.gcount());
            out.flush();
            // распаковка сжатого содержимого
        } else {
            char buffer;
            // проверка наличия данных для чтения
            if (!in.good()) {
                continue;
            }
            // читаем следующий байт
            buffer = in.get();
          //  cout << "buffer: "s << buffer << std::endl;
            // записываем его data_size раз в string data_size раз
            std::string expression(data_size, buffer);
          // std::cout << "Cжато: "s << expression << std::endl;
            out << expression;
            out.flush();
        }
    } while (in);
    out.close();
    return true;
}