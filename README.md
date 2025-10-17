# sudoPWNED - Sudo Vulnerability Scanner

A lightweight command-line tool to detect vulnerable sudo versions on Unix systems.

```
                 .___                                    .___
  ________ __  __| _/____ ________  _  ______   ____   __| _/
 /  ___/  |  \/ __ |/  _ \\____ \ \/ \/ /    \_/ __ \ / __ | 
 \___ \|  |  / /_/ (  <_> )  |_> >     /   |  \  ___// /_/ | 
/____  >____/\____ |\____/|   __/ \/\_/|___|  /\___  >____ | 
     \/           \/      |__|              \/     \/     \/ 
```

---

## Features

- **Automatic sudo version detection**
- **CVE-2021-3156** (Baron Samedit) detection
- **CVE-2025-32463** (chroot bypass) detection

---

## Installation

### Prerequisites
- C++ compiler with C++17 support (g++, clang++)
- make
- Linux system with sudo installed

### Build from Source

```bash
# Clone or download the project
cd sudoPWNED

# Compile
make

# The binary will be created as 'sudopwned'
```

---

## Usage

### Check Sudo Version

```bash
./sudopwned version
```

**Example Output:**
```
Sudo version: 1.8.31
```

### Scan for Vulnerabilities

```bash
./sudopwned scan
```

**Example Output:**
```
Sudo Version: 1.8.31

[*] Scanning for CVE-2025-32463 (chroot bypass)...
NOT vulnerable to CVE-2025-32463

[*] Scanning for CVE-2021-3156 (Baron Samedit)...
[!] VULNERABLE to CVE-2021-3156
```

### Help

```bash
./sudopwned
```

Shows usage information.

---

## Building and Development

### Clean Build

```bash
make clean
make
```

### Rebuild

```bash
make rebuild
```

---

## Examples

### Scenario 1: Vulnerable System

```bash
$ ./sudopwned scan

                 .___                                    .___
  ________ __  __| _/____ ________  _  ______   ____   __| _/
 /  ___/  |  \/ __ |/  _ \\____ \ \/ \/ /    \_/ __ \ / __ | 
 \___ \|  |  / /_/ (  <_> )  |_> >     /   |  \  ___// /_/ | 
/____  >____/\____ |\____/|   __/ \/\_/|___|  /\___  >____ | 
     \/           \/      |__|              \/     \/     \/ 

                  Sudo Vulnerability Scanner v1.0
                      Author: c0d3Ninja
========================================================================

Sudo Version: 1.8.31

[*] Scanning for CVE-2025-32463 (chroot bypass)...
NOT vulnerable to CVE-2025-32463

[*] Scanning for CVE-2021-3156 (Baron Samedit)...
[!] VULNERABLE to CVE-2021-3156
```

### Scenario 2: Patched System

```bash
$ ./sudopwned scan

Sudo Version: 1.9.10

[*] Scanning for CVE-2025-32463 (chroot bypass)...
NOT vulnerable to CVE-2025-32463

[*] Scanning for CVE-2021-3156 (Baron Samedit)...
NOT vulnerable to CVE-2021-3156
```

---

## References

- [sudo Official Website](https://www.sudo.ws/)
- [National Vulnerability Database](https://nvd.nist.gov/)
- [CVE-2021-3156 Details](https://nvd.nist.gov/vuln/detail/CVE-2021-3156)
- [CVE-2025-32463 Details](https://nvd.nist.gov/vuln/detail/CVE-2025-32463)
- [Qualys Baron Samedit Analysis](https://blog.qualys.com/vulnerabilities-threat-research/2021/01/26/cve-2021-3156-heap-based-buffer-overflow-in-sudo-baron-samedit)


