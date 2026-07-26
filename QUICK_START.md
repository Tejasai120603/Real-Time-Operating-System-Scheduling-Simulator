# 🚀 Quick Start Guide - RTS Simulation Project

## ⚡ Fast Setup (3 Steps)

### 1️⃣ Build and Run
```cmd
build_rts.bat
```
That's it! The simulation will compile and run automatically.

---

## 📂 Essential Files

| File | Purpose |
|------|---------|
| `rts_simulation.c` | Main RTS simulation code |
| `build_rts.bat` | Build and run script |
| `RTS_PROJECT_README.md` | Complete documentation |
| `cleanup_demos.bat` | Remove old demo files |

---

## 🎯 What You'll See

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

### 3. Health Monitor (Every 1 second)
```
╔════════════════════════════════════════════════════════════════╗
║              SYSTEM HEALTH MONITOR REPORT                      ║
╠════════════════════════════════════════════════════════════════╣
║ Sensor Reads:      60          Control Commands: 150          ║
║ Average Latency:   2 ms                                        ║
╚════════════════════════════════════════════════════════════════╝
```

### 4. Final Statistics (After 30 seconds)
```
╔════════════════════════════════════════════════════════════════╗
║                  FINAL SIMULATION STATISTICS                   ║
╠════════════════════════════════════════════════════════════════╣
║ Total Operations:          450                                 ║
║ Average Latency:           2 ms                                ║
║ Jitter (Max - Min):        15 ms                               ║
╚════════════════════════════════════════════════════════════════╝
```

---

## 🧹 Clean Up Old Files

To remove unnecessary demo files:
```cmd
cleanup_demos.bat
```

---

## ⚙️ Customize Simulation

Edit these values in `rts_simulation.c`:

```c
#define SIMULATION_DURATION_SEC 30     // How long to run (seconds)
#define SENSOR_PERIOD_MS 500           // Sensor reading frequency
#define CONTROL_PERIOD_MS 200          // Control task frequency
#define MONITOR_PERIOD_MS 1000         // Monitor check frequency
```

---

## 🔧 Manual Build (Alternative)

```cmd
gcc -Wall -Wextra -std=c11 -O2 -g -o rts_simulation.exe rts_simulation.c -lpthread
rts_simulation.exe
```

---

## 📊 Performance Metrics

The simulation measures:

- **Latency**: Task execution time
- **Response Time**: Sensor-to-control delay
- **Jitter**: Timing variation
- **Throughput**: Operations per second

---

## 🎓 Tasks Overview

| Task | Type | Period | Priority | Function |
|------|------|--------|----------|----------|
| SensorTask | Periodic | 500ms | Medium | Read sensors |
| ControlTask | Periodic | 200ms | High | Process & control |
| LoggerTask | Aperiodic | Event | Low | Log events |
| MonitorTask | Periodic | 1000ms | Medium | Health check |

---

## 🆘 Troubleshooting

### Build Fails?
- Ensure MSYS2/MinGW64 is installed at `C:\msys64\`
- Check that GCC is in PATH: `gcc --version`

### No Output?
- Check if `rts_simulation.exe` was created
- Run manually: `rts_simulation.exe`

### Need Help?
- Read full documentation: `RTS_PROJECT_README.md`
- Check code comments in `rts_simulation.c`

---

## ✅ Success Checklist

- [ ] Built successfully with `build_rts.bat`
- [ ] Saw all 4 tasks start
- [ ] Observed real-time task execution
- [ ] Saw health monitor reports
- [ ] Got final statistics after 30 seconds
- [ ] Cleaned up old files with `cleanup_demos.bat`

---

## 🎉 You're Ready!

Your RTS simulation is now running! Check `RTS_PROJECT_README.md` for detailed documentation.

**Happy Real-Time Programming! 🚀**
