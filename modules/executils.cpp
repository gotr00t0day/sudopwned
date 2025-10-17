#include "executils.h"
#include <cstdlib>
#include <array>
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <sys/wait.h>

std::string execCommand(const std::string& cmd) {
    std::array<char, 128> buffer;
    std::string result;

    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) return "ERROR";

    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }
    pclose(pipe);
    return result;
}
