# sudoPWNED - Sudo Vulnerability Scanner

**Author:** c0d3Ninja  
**Version:** 1.0

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

- 🔍 **Automatic sudo version detection**
- 🛡️ **CVE-2021-3156** (Baron Samedit) detection
- 🛡️ **CVE-2025-32463** (chroot bypass) detection
- 🎨 **Color-coded output** for easy readability
- ⚡ **Fast and lightweight** - written in C++
- 🔧 **Simple CLI** interface

---

## Supported Vulnerabilities

### CVE-2021-3156 - Baron Samedit (Heap-Based Buffer Overflow)

**Severity:** Critical (CVSS 7.8)  
**Affected Versions:**
- sudo 1.8.2 through 1.8.31p2
- sudo 1.9.0 through 1.9.5p1

**Description:** A heap-based buffer overflow in sudo allows local privilege escalation to root without requiring authentication.

**Impact:** Any unprivileged user can gain root access.

**References:**
- [CVE-2021-3156](https://nvd.nist.gov/vuln/detail/CVE-2021-3156)
- [Qualys Advisory](https://blog.qualys.com/vulnerabilities-threat-research/2021/01/26/cve-2021-3156-heap-based-buffer-overflow-in-sudo-baron-samedit)

---

### CVE-2025-32463 - Chroot Bypass

**Severity:** High (CVSS 7.3)  
**Affected Versions:**
- sudo 1.9.14 through 1.9.17

**Description:** A vulnerability in sudo's chroot handling allows attackers to bypass chroot restrictions.

**Impact:** Privilege escalation and container escape scenarios.

**References:**
- [CVE-2025-32463](https://nvd.nist.gov/vuln/detail/CVE-2025-32463)

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

## How It Works

1. **Version Detection:** Executes `sudo --version` and parses the output
2. **Version Comparison:** Compares detected version against known vulnerable versions
3. **Vulnerability Matching:** Uses hardcoded CVE version lists to determine exposure
4. **Result Display:** Shows color-coded results for each CVE

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

### Compiler Options

The Makefile uses the following flags:
- `-std=c++17` - C++17 standard
- `-Wall -Wextra` - All warnings enabled
- `-g` - Debug symbols included

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

## Future Enhancements

Potential features for future versions:

- [ ] JSON output for automation
- [ ] Support for additional sudo CVEs
- [ ] Exploit suggestions (for authorized testing)
- [ ] Log file generation
- [ ] Integration with security scanning frameworks
- [ ] Cross-platform support (BSD, macOS)

---

## References

- [sudo Official Website](https://www.sudo.ws/)
- [National Vulnerability Database](https://nvd.nist.gov/)
- [CVE-2021-3156 Details](https://nvd.nist.gov/vuln/detail/CVE-2021-3156)
- [CVE-2025-32463 Details](https://nvd.nist.gov/vuln/detail/CVE-2025-32463)
- [Qualys Baron Samedit Analysis](https://blog.qualys.com/vulnerabilities-threat-research/2021/01/26/cve-2021-3156-heap-based-buffer-overflow-in-sudo-baron-samedit)


