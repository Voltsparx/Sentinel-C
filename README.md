```
# Sentinel-C 🛡️

Author: Voltsparx  
Language: C/C++  
Repo: https://github.com/voltsparx/Sentinel-C  

Sentinel-C is a Host-Based File Integrity Monitor (HIDS).  
It scans directories, detects NEW, MODIFIED, or DELETED files, logs events, and generates HTML reports for easy auditing.  

---

⚠️ Ethical Use & Disclaimer

- This tool is designed for ethical security monitoring of systems and directories you own or have permission to monitor.  
- Do not use it to tamper with, spy on, or attack systems you do not own.  
- The author is not responsible for misuse.  

---

🛠️ Installation

Linux / macOS:

1. Clone the repo:
git clone https://github.com/voltsparx/Sentinel-C.git
cd Sentinel-C

2. Build with CMake:
mkdir build
cd build
cmake ..
cmake --build .

3. Run from build folder:
./sentinel-c help

Optional: Copy to PATH for global CLI:
sudo cp sentinel-c /usr/local/bin/

Windows (CMD / PowerShell):

1. Clone the repo:
git clone https://github.com/voltsparx/Sentinel-C.git
cd Sentinel-C

2. Build:
mkdir build
cd build
cmake ..
cmake --build .

3. Run executable:
sentinel-c.exe help

---

📁 Project Structure

Sentinel-C/
├── src/                # C++ source and headers
├── CMakeLists.txt
├── README.md
├── .gitignore
├── reports/            # HTML reports stored here
└── data/               # Baseline & log files stored here

Folders reports/ and data/ are automatically created if missing.  
.sentinel.log is saved in data/.  
HTML reports are saved in reports/.

---

⚡ Usage

# Show help
sentinel-c help

# Initialize baseline
sentinel-c init <directory>

# Scan directory and compare to baseline
sentinel-c scan <directory>

# Monitor continuously every N seconds
sentinel-c monitor <directory> [interval_seconds]

Example:
./sentinel-c init .
./sentinel-c scan .
./sentinel-c monitor . 10

- init creates the baseline  
- scan compares current files to baseline  
- monitor scans repeatedly and updates logs & HTML reports  

---

🟢 Output

- Colored terminal messages:
  - Green → NEW files  
  - Yellow → MODIFIED files  
  - Red → DELETED files  

- Logs: data/.sentinel.log  
- HTML report: reports/sentinel_report_<timestamp>.html

---

⭐ Contribution

- Feel free to fork and add features  
- Please respect ethical guidelines

---

📄 License

This project is released under the MIT License.
```
