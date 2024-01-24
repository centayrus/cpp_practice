#include "log_duration.h"

#include <fstream>
#include <string>

using namespace std;

#define PROFILE_CONCAT_INTERNAL(X, Y) X##Y
#define PROFILE_CONCAT(X, Y) PROFILE_CONCAT_INTERNAL(X, Y)
#define UNIQUE_VAR_NAME_PROFILE PROFILE_CONCAT(profileGuard, __LINE__)
#define LOG_DURATION(x) LogDuration UNIQUE_VAR_NAME_PROFILE(x)

int main() {
    ofstream out_file("ballad.txt"s);
    {
        LOG_DURATION("endl: ");
    for (int i = 0; i < 50000; ++i) {
        out_file << "С любимыми не расставайтесь"s << endl;
    }
    }
        {
        LOG_DURATION("\\n: ");
    for (int i = 0; i < 50000; ++i) {
        out_file << "С любимыми не расставайтесь\n"s;
    }
    }
    throw;
} 