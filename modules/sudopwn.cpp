#include "sudopwn.h"
#include "../modules/executils.h"
#include <cerrno>
#include <string>
#include <regex>
#include <cstdlib>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"
#define UNDERLINE "\033[4m"

std::vector<std::string> baron_samedit = {
    "1.8.2","1.8.3","1.8.4","1.8.5","1.8.6","1.8.7","1.8.8","1.8.9","1.8.10",
    "1.8.11","1.8.12","1.8.13","1.8.14","1.8.15","1.8.16","1.8.17","1.8.18",
    "1.8.19","1.8.20","1.8.21","1.8.22","1.8.23","1.8.24","1.8.25","1.8.26",
    "1.8.27","1.8.28","1.8.29","1.8.30","1.8.31","1.8.31p1","1.8.31p2",
    "1.9.0","1.9.1","1.9.2","1.9.3","1.9.4","1.9.5","1.9.5p1"
};

std::vector<std::string> cve202532463 = {
    "1.9.14",
    "1.9.14p1",
    "1.9.14p2",
    "1.9.14p3",
    "1.9.15",
    "1.9.15p1",
    "1.9.15p2",
    "1.9.15p3",
    "1.9.16",
    "1.9.16p1",
    "1.9.16p2",
    "1.9.17"
};

static inline std::string trim(const std::string& s) {
    size_t a = 0;
    while (a < s.size() && std::isspace((unsigned char)s[a])) ++a;
    size_t b = s.size();
    while (b > a && std::isspace((unsigned char)s[b-1])) --b;
    return s.substr(a, b - a);
}

std::string parseSudoVersion(const std::string& output) {
    std::regex r(R"(Sudo\s+version\s+([^\s]+))", std::regex::icase);
    std::smatch match;
    if (std::regex_search(output, match, r)) {
        return match[1].str();
    }
    std::regex r2(R"(sudo\s+version\s+([^\s]+))", std::regex::icase);
    if (std::regex_search(output, match, r2)) {
        return trim(match[1].str());
    }
    return {};
}

std::string sudoVersion() {
    std::string sversion;
    std::string sudoV = execCommand("sudo --version 2>&1");
    auto version = parseSudoVersion(sudoV);
    if (!version.empty()) {
        sversion = version;
    }
    return sversion;
}

bool checkVulnerability(const std::string& sVersion, const std::vector<std::string>& vList) {
    std::string v = trim(sVersion);
    if (v.empty()) return false;
    return std::any_of(vList.begin(), vList.end(),
                       [&](const std::string &candidate){ return v == candidate; });
}

bool pwnchroot(){
    std::string version = sudoVersion();
    version = trim(version);
    if (version.empty()) return false;
    return checkVulnerability(version, cve202532463);
}

bool pwnbarotsamedit(){
    std::string version = sudoVersion();
    version = trim(version);
    if (version.empty()) return false;
    return checkVulnerability(version, baron_samedit);
}

