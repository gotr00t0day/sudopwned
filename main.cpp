#include "modules/sudopwn.h"
#include <iostream>
#include <string>

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

void banner() {
    std::cout << RED << BOLD << R"(
                 .___                                    .___
  ________ __  __| _/____ ________  _  ______   ____   __| _/
 /  ___/  |  \/ __ |/  _ \\____ \ \/ \/ /    \_/ __ \ / __ | 
 \___ \|  |  / /_/ (  <_> )  |_> >     /   |  \  ___// /_/ | 
/____  >____/\____ |\____/|   __/ \/\_/|___|  /\___  >____ | 
     \/           \/      |__|              \/     \/     \/ 
                                                                        
)" << RESET;
    std::cout << CYAN << "                  Sudo Vulnerability Scanner v1.0" << RESET << std::endl;
    std::cout << YELLOW << "                      Author: c0d3Ninja" << RESET << std::endl;
    std::cout << BOLD << "========================================================================" << RESET << std::endl;
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    banner();
    if (argc != 2) {
        std::cerr << YELLOW << "Usage: " << argv[0] << " <command>" << RESET << std::endl;
        std::cerr << "Commands:" << std::endl;
        std::cerr << "  version - Show sudo version" << std::endl;
        std::cerr << "  scan    - Scan for vulnerabilities" << std::endl;
        return 1;
    }
    
    std::string command = argv[1];
    
    if (command == "version") {
        std::string ver = sudoVersion();
        if (ver.empty()) {
            std::cout << RED << "[-] Could not detect sudo version" << RESET << std::endl;
        } else {
            std::cout << "Sudo version: " << CYAN << ver << RESET << std::endl;
        }
    } else if (command == "scan") {
        std::string ver = sudoVersion();
        if (ver.empty()) {
            std::cout << RED << "[-] Could not detect sudo version. Is sudo installed?" << RESET << std::endl;
            return 1;
        }
        std::cout << "Sudo Version: " << CYAN << ver << RESET << std::endl;
        std::cout << std::endl;
        
        // Check CVE-2025-32463
        std::cout << "[*] Scanning for CVE-2025-32463 (chroot bypass)..." << RESET << std::endl;
        if (pwnchroot()) {
            std::cout << RED << "[!] VULNERABLE to CVE-2025-32463" << RESET << std::endl;
        } else {
            std::cout << GREEN << "NOT vulnerable to CVE-2025-32463" << RESET << std::endl;
        }
        
        std::cout << std::endl;
        
        // Check CVE-2021-3156 (Baron Samedit)
        std::cout << "[*] Scanning for CVE-2021-3156 (Baron Samedit)..." << RESET << std::endl;
        if (pwnbarotsamedit()) {
            std::cout << RED << "[!] VULNERABLE to CVE-2021-3156" << RESET << std::endl;
        } else {
            std::cout << GREEN << "NOT vulnerable to CVE-2021-3156" << RESET << std::endl;
        }
        
        std::cout << std::endl;
    } else {
        std::cerr << RED << "[-] Invalid command: " << command << RESET << std::endl;
        std::cerr << "Use 'version' or 'scan'" << std::endl;
        return 1;
    }
    
    return 0;
}