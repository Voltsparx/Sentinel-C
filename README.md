# Sentinel-C v3.50 🛡️

**Author:** Voltsparx  
**Contact:** voltsparx@gmail.com  
**Language:** C/C++  
**Repo:** [https://github.com/voltsparx/Sentinel-C](https://github.com/voltsparx/Sentinel-C)  

Sentinel-C is an **Advanced Host Defense Multi-Tool** for file integrity monitoring and system security.  
It provides baseline initialization, file comparison scanning, SHA-256 hashing, and comprehensive reporting in multiple formats (CLI, HTML, JSON) — designed for cybersecurity learners, professionals, and anyone who cares about system security.

---

## ⚠️ **Ethical Use & Disclaimer**

- This tool is **only for ethical monitoring** of systems and directories you own or have permission to monitor.  
- **Do not** use it to tamper with, spy on, or attack systems you do not own.  
- The author is **not responsible for misuse**.  
- Data logged by Sentinel-C is stored locally for your convenience and **not shared anywhere**.

---

## 🛠️ **Installation**

### **Linux / Unix:**

```bash
git clone https://github.com/voltsparx/Sentinel-C.git
cd Sentinel-C
mkdir build
cd build
cmake ..
cmake --build .
```

#### Run from build folder:

```bash
./sentinel-c --help
```

Optional: Add to PATH for global use:

```bash
sudo cp sentinel-c /usr/local/bin/
```

### **Windows (CMD / PowerShell):**

```powershell
git clone https://github.com/voltsparx/Sentinel-C.git
cd Sentinel-C
mkdir build
cd build
cmake ..
cmake --build .
```

#### Run executable:

```powershell
sentinel-c.exe --help
```

---

## 📁 **Project Structure**

```
Sentinel-C/
├── src/                # Source & headers
├── CMakeLists.txt
├── README.md
├── sentinel-c-logs/    # Logs & HTML reports
│   ├── data/
│   └── reports/
```

- Folders `data/` and `reports/` are **automatically created** if missing.  
- `.sentinel.log` is stored in `data/`.  
- HTML reports are stored in `reports/`.

---

## ⚡ **Features**

- **File Integrity Monitoring** - Detect NEW, MODIFIED, and DELETED files  
- **SHA-256 Hashing** - Cryptographic verification of file contents  
- **Multi-format Reporting** - CLI text reports, HTML reports, and JSON output  
- **Baseline Comparison** - Compare current directory state against saved baseline  
- **Automatic Directory Creation** - Creates necessary log directories on first run  
- **Colored Output** - Visual indicators for file changes (green, yellow, red)  
- **Cross-platform** - Compatible with **Linux and Windows**  
- **Fast Performance** - Recursive directory scanning with efficient hashing

---

## 💻 **Commands & Usage**

```
Sentinel-C v3.50

--init <path>    Initialize baseline for a directory
--scan <path>    Scan directory and compare against baseline
--help           Show this help message
```

### **Quick Start Example:**

```bash
# Step 1: Create baseline of a directory
./sentinel-c --init /path/to/monitor

# Step 2: Modify, delete, or add files in that directory

# Step 3: Scan for changes
./sentinel-c --scan /path/to/monitor
```

### **Output Files:**

The tool generates reports in `sentinel-c-logs/` directory:

- **CLI Report:** `reports/cli/scan_<timestamp>.txt` - Plain text summary  
- **HTML Report:** `reports/html/scan_<timestamp>.html` - Formatted HTML table  
- **JSON Report:** `reports/json/scan_<timestamp>.json` - Structured JSON data  

### **Output Colors:**

- 🟢 **Green** `[+] NEW` - New files detected  
- 🟡 **Yellow** `[!] MODIFIED` - Changed files  
- 🔴 **Red** `[-] DELETED` - Missing files

---

## 🟢 **Output**

**Console Output Example:**
```
[+] NEW /path/to/newfile.txt
[!] MODIFIED /path/to/changed.cpp
[-] DELETED /path/to/removed.log
```

**Report Files Generated:**
- `sentinel-c-logs/reports/cli/scan_<timestamp>.txt` - Text summary  
- `sentinel-c-logs/reports/html/scan_<timestamp>.html` - Interactive HTML report  
- `sentinel-c-logs/reports/json/scan_<timestamp>.json` - JSON data export  

**Baseline Storage:**
- `sentinel-c-logs/data/.sentinel-baseline` - Stores file hashes and metadata

---

## ⭐ **Contribution**

- Fork and add features freely.  
- Follow ethical security guidelines.  

---

## 📄 **License**

MIT License
