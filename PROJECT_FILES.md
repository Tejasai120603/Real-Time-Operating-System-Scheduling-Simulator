# 📁 RTS Project Files Overview

## ⭐ Core Project Files (Essential)

### 1. **rts_simulation.c**
- **Purpose**: Main RTS simulation implementation
- **Size**: ~700 lines
- **Contains**:
  - SensorTask (Periodic, Medium Priority)
  - ControlTask (Periodic, High Priority)
  - LoggerTask (Aperiodic, Low Priority)
  - MonitorTask (Periodic, Medium Priority)
  - Synchronization primitives (mutexes, semaphores)
  - Performance metrics (latency, jitter, response time)
  - Real-time statistics collection

### 2. **build_rts.bat**
- **Purpose**: Build and run script for Windows
- **Features**:
  - Checks for MSYS2/MinGW64 installation
  - Compiles with GCC
  - Links pthread library
  - Automatically runs the simulation
  - Error handling

### 3. **RTS_PROJECT_README.md**
- **Purpose**: Complete project documentation
- **Sections**:
  - Project overview and objectives
  - System architecture
  - Task configuration
  - Features demonstrated
  - Build instructions
  - Expected output
  - Performance metrics
  - Code highlights
  - Customization guide

### 4. **QUICK_START.md**
- **Purpose**: Fast setup guide
- **Contents**:
  - 3-step quick start
  - Essential commands
  - Expected output samples
  - Troubleshooting tips
  - Success checklist

### 5. **cleanup_demos.bat**
- **Purpose**: Remove old demo files
- **Removes**:
  - Old demo C files (7 files)
  - Old executables (7 files)
  - Old build scripts (11 files)
- **Keeps**:
  - Core RTS project files
  - FreeRTOS libraries
  - Required directories

### 6. **PROJECT_FILES.md** (This file)
- **Purpose**: Project structure documentation
- **Contents**: File listing and descriptions

---

## 📚 Required Libraries (Do Not Remove)

### FreeRTOS-Kernel/
- FreeRTOS real-time kernel source code
- Required for RTOS functionality
- **Size**: ~796 items

### FreeRTOS-Plus-POSIX/
- POSIX wrapper for FreeRTOS
- Provides pthread, semaphore, mutex APIs
- **Size**: ~46 items

### include/
- Header files for FreeRTOS and POSIX
- Required for compilation
- **Size**: ~12 items

---

## 🗑️ Files to Remove (Optional)

Run `cleanup_demos.bat` to remove these:

### Old Demo Files:
- `basic_threading_demo.c`
- `final_freertos_posix_demo.c`
- `simple_posix_demo.c`
- `simple_working_demo.c`
- `windows_posix_demo.c`
- `working_posix_demo.c`
- `test_minimal.c`

### Old Executables:
- `basic_threading_demo.exe`
- `final_freertos_posix_demo.exe`
- `simple_posix_demo.exe`
- `simple_working_demo.exe`
- `windows_posix_demo.exe`
- `working_posix_demo.exe`
- `test_minimal.exe`

### Old Build Scripts:
- `build_basic_threading.bat`
- `build_demo.bat`
- `build_demo.ps1`
- `build_final_demo.bat`
- `build_simple_posix.bat`
- `build_simple_working.bat`
- `build_windows_posix.bat`
- `build_with_msys2.bat`
- `build_working_demo.bat`
- `run_demo.bat`
- `test_minimal.bat`

### Old Directories (Optional):
- `demo/` - Contains old demo files
- `test/` - Contains old test files
- `build/` - Empty build directory
- `build_wsl/` - WSL-specific build files

---

## 📊 Project Statistics

### Code Metrics:
- **Main Code**: ~700 lines (rts_simulation.c)
- **Documentation**: ~500 lines (README + guides)
- **Build Scripts**: ~150 lines

### Task Breakdown:
- **4 Real-Time Tasks**: Sensor, Control, Logger, Monitor
- **4 Mutexes**: For data protection
- **3 Semaphores**: For signaling
- **Multiple Data Structures**: SensorData, ControlCommand, SystemStats, LogEntry

### Performance Features:
- Latency measurement
- Response time tracking
- Jitter calculation
- Throughput monitoring
- Real-time statistics

---

## 🎯 File Usage Guide

### To Build and Run:
```cmd
build_rts.bat
```

### To Clean Up:
```cmd
cleanup_demos.bat
```

### To Read Documentation:
1. Quick start: `QUICK_START.md`
2. Full docs: `RTS_PROJECT_README.md`
3. File list: `PROJECT_FILES.md` (this file)

### To Modify Code:
Edit `rts_simulation.c` with your preferred editor

### To Customize:
Change constants in `rts_simulation.c`:
- `SIMULATION_DURATION_SEC`
- `SENSOR_PERIOD_MS`
- `CONTROL_PERIOD_MS`
- `MONITOR_PERIOD_MS`
- `CRITICAL_TEMP_THRESHOLD`
- `CRITICAL_PRESSURE_THRESHOLD`

---

## ✅ Minimal Project Structure

After running `cleanup_demos.bat`, your project will have:

```
Lab-Project-FreeRTOS-POSIX-main/
├── rts_simulation.c          ⭐ Main code
├── rts_simulation.exe        (Generated after build)
├── build_rts.bat             ⭐ Build script
├── cleanup_demos.bat         ⭐ Cleanup script
├── RTS_PROJECT_README.md     ⭐ Full documentation
├── QUICK_START.md            ⭐ Quick guide
├── PROJECT_FILES.md          ⭐ This file
├── FreeRTOS-Kernel/          (Required library)
├── FreeRTOS-Plus-POSIX/      (Required library)
├── include/                  (Required headers)
├── .git/                     (Git repository)
├── .github/                  (GitHub config)
├── .gitmodules               (Git submodules)
├── .vscode/                  (VS Code config)
├── LICENSE                   (License file)
├── README.md                 (Original README)
└── SETUP_GUIDE.md            (Original setup guide)
```

**⭐ = Core RTS project files**

---

## 🔍 Quick Reference

| Need to... | Use this file |
|------------|---------------|
| Build and run | `build_rts.bat` |
| Quick start | `QUICK_START.md` |
| Full documentation | `RTS_PROJECT_README.md` |
| Clean up | `cleanup_demos.bat` |
| Understand structure | `PROJECT_FILES.md` |
| Modify code | `rts_simulation.c` |

---

## 📝 Notes

- Keep `FreeRTOS-Kernel/` and `FreeRTOS-Plus-POSIX/` - they are required
- The `include/` directory contains necessary headers
- Generated `.exe` files can be deleted and rebuilt
- Git-related files (`.git/`, `.github/`, `.gitmodules`) are for version control
- VS Code config (`.vscode/`) is optional

---

## 🎓 For Submission

### Essential Files to Submit:
1. `rts_simulation.c` - Your implementation
2. `RTS_PROJECT_README.md` - Documentation
3. `build_rts.bat` - Build script
4. `QUICK_START.md` - Quick guide
5. Screenshot/output of simulation run

### Optional (if required):
- FreeRTOS libraries (if not assumed to be pre-installed)
- Project report/presentation
- Performance analysis graphs

---

**Last Updated**: Project creation date  
**Project**: RTS - Real-Time Task Scheduling using FreeRTOS+POSIX  
**Course**: B.Tech 4th Year - Real-Time Systems
