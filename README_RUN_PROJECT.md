# How to Run the RTS Project

## Quick Start (3 Steps)

### Step 1: Install Prerequisites

**Install MSYS2/MinGW64:**
1. Download MSYS2 from: https://www.msys2.org/
2. Install to default location: `C:\msys64`
3. Open MSYS2 terminal and run:
   ```bash
   pacman -S mingw-w64-x86_64-gcc
   ```

### Step 2: Build and Run

Open PowerShell or Command Prompt in the project directory and run:

**PowerShell:**
```powershell
.\build_rts.bat
```

**Command Prompt:**
```cmd
build_rts.bat
```

### Step 3: Watch the Simulation

The simulation will:
- Run for 30 seconds
- Show real-time task execution
- Display performance statistics
- Exit automatically

---

## Alternative: Run Pre-Built Executable

If you've already built the project once:

**PowerShell:**
```powershell
.\run_rts.bat
```

**Command Prompt:**
```cmd
run_rts.bat
```

---

## What You'll See

### 1. Task Creation
```
✅ SensorTask created
✅ ControlTask created
✅ LoggerTask created
✅ MonitorTask created
```

### 2. Real-Time Execution
```
[SensorTask] Read: Temp=45°C, Press=62 kPa, Humid=78%
[ControlTask] Command: Actuator=0, Value=50
[LoggerTask] [MEDIUM] Sensor Reading - T:45 P:62 H:78
```

### 3. Critical Event Detection
```
[ControlTask] ⚠️  HIGH TEMP DETECTED! Activating cooling (100%)
[ControlTask] ⚠️  HIGH PRESSURE DETECTED! Activating relief valve (80%)
```

### 4. Health Monitor Reports (Every 1 second)
```
╔════════════════════════════════════════════════════════════════╗
║              SYSTEM HEALTH MONITOR REPORT                      ║
╠════════════════════════════════════════════════════════════════╣
║ Sensor Reads:      30          Control Commands: 30         ║
║ Log Entries:       56          Monitor Checks:   15         ║
╠════════════════════════════════════════════════════════════════╣
║ Average Latency:   8 ms                                       ║
║ Max Latency:       46 ms                                      ║
║ Min Latency:       0 ms                                       ║
╚════════════════════════════════════════════════════════════════╝
```

### 5. Final Statistics (After 30 seconds)
```
╔════════════════════════════════════════════════════════════════╗
║                  FINAL SIMULATION STATISTICS                   ║
╠════════════════════════════════════════════════════════════════╣
║ Total Sensor Reads:        59                                 ║
║ Total Control Commands:    59                                 ║
║ Total Log Entries:         107                                ║
║ Total Monitor Checks:      29                                 ║
╠════════════════════════════════════════════════════════════════╣
║ Average Latency:           8 ms                               ║
║ Maximum Latency:           46 ms                              ║
║ Minimum Latency:           0 ms                               ║
║ Jitter (Max - Min):        46 ms                              ║
║ Total Operations:          254                                ║
╚════════════════════════════════════════════════════════════════╝
```

---

## Troubleshooting

### Problem: "gcc not recognized"
**Solution:** Install MSYS2/MinGW64 (see Step 1)

### Problem: "build_rts.bat not recognized" (PowerShell)
**Solution:** Use `.\build_rts.bat` (with `.\` prefix)

### Problem: Build fails with compilation errors
**Solution:** Make sure you have the latest code. Run `.\build_rts.bat` again.

### Problem: Simulation crashes immediately
**Solution:** Rebuild the project with `.\build_rts.bat` to ensure you have the latest executable.

---

## Project Structure

```
Lab-Project-FreeRTOS-POSIX-main/
├── rts_simulation.c          # Main RTS simulation code
├── rts_simulation.exe        # Compiled executable (after build)
├── build_rts.bat             # Build and run script
├── run_rts.bat               # Run pre-built executable
├── RTS_PROJECT_README.md     # Complete project documentation
├── README_RUN_PROJECT.md     # This file
├── QUICK_START.md            # Quick reference guide
├── FreeRTOS-Kernel/          # FreeRTOS library
├── FreeRTOS-Plus-POSIX/      # POSIX wrapper
└── include/                  # Header files
```

---

## Task Configuration

| Task Name    | Type      | Period (ms) | Priority | Function                    |
|--------------|-----------|-------------|----------|-----------------------------|
| SensorTask   | Periodic  | 500         | Medium   | Read sensor data            |
| ControlTask  | Periodic  | 200         | High     | Process and control         |
| LoggerTask   | Aperiodic | Event-driven| Low      | Log system events           |
| MonitorTask  | Periodic  | 1000        | Medium   | System health monitoring    |

---

## Performance Metrics

The simulation measures:
- **Latency**: Task execution time
- **Response Time**: Sensor-to-control delay
- **Jitter**: Timing variation (Max - Min latency)
- **Throughput**: Operations per second

---

## Customization

To modify simulation parameters, edit `rts_simulation.c`:

```c
#define SIMULATION_DURATION_SEC 30     // Simulation time (seconds)
#define SENSOR_PERIOD_MS 500           // Sensor reading frequency
#define CONTROL_PERIOD_MS 200          // Control task frequency
#define MONITOR_PERIOD_MS 1000         // Monitor check frequency
#define CRITICAL_TEMP_THRESHOLD 75     // Temperature alert (°C)
#define CRITICAL_PRESSURE_THRESHOLD 80 // Pressure alert (kPa)
```

After editing, rebuild:
```powershell
.\build_rts.bat
```

---

## Features Demonstrated

✅ **Task Creation & Scheduling** - Multiple concurrent tasks with priorities  
✅ **Inter-Task Communication** - Semaphores and mutexes  
✅ **Synchronization** - Thread-safe data sharing  
✅ **Real-Time Metrics** - Latency, jitter, response time  
✅ **Critical Event Handling** - Temperature and pressure thresholds  
✅ **System Monitoring** - Periodic health checks  

---

## System Requirements

- **OS**: Windows 10/11
- **Compiler**: GCC (via MSYS2/MinGW64)
- **Libraries**: pthread (included with MinGW64)
- **Disk Space**: ~500 MB (for MSYS2 + project)

---

## Expected Performance

Typical results from a 30-second simulation:
- **Sensor Reads**: ~59 (every 500ms)
- **Control Commands**: ~59 (every 200ms)
- **Log Entries**: ~107 (event-driven)
- **Monitor Checks**: ~29 (every 1000ms)
- **Average Latency**: 5-10 ms
- **Jitter**: 40-50 ms

---

## Additional Documentation

- **Complete Documentation**: `RTS_PROJECT_README.md`
- **Quick Start Guide**: `QUICK_START.md`
- **File Structure**: `PROJECT_FILES.md`
- **Getting Started**: `START_HERE.txt`

---

## Support

If you encounter issues:
1. Check the Troubleshooting section above
2. Verify MSYS2/MinGW64 is installed correctly
3. Ensure you're in the correct directory
4. Try rebuilding with `.\build_rts.bat`

---

## Project Information

**Title**: POSIX-Compatible Real-Time Task Scheduling using FreeRTOS  
**Course**: Real-Time Systems (RTS)  
**Level**: B.Tech 4th Year  

---

**Last Updated**: October 2025  
**Version**: 1.0
