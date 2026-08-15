# Real-Time Operating System Scheduling Simulator

> A modular C-based Real-Time Operating System (RTOS) scheduling simulator built with **FreeRTOS+POSIX**, designed to demonstrate task scheduling, concurrency, synchronization, inter-task communication, and real-time system behavior on desktop environments.

[![Language](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_%28programming_language%29)
[![RTOS](https://img.shields.io/badge/RTOS-FreeRTOS%2BPOSIX-orange.svg)](https://www.freertos.org/)
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20WSL-lightgrey.svg)](https://learn.microsoft.com/en-us/windows/wsl/)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)

---

## 📌 Overview

The **Real-Time Operating System Scheduling Simulator** is an educational and experimental project that models the behavior of a real-time multitasking system using **FreeRTOS+POSIX**.

The project demonstrates how an RTOS manages multiple concurrent tasks through:

* Task creation and execution
* Priority-based scheduling
* Preemption and task coordination
* POSIX-compatible threading
* Inter-task communication
* Synchronization mechanisms
* Timing and periodic task execution
* Real-time performance monitoring

By using the **FreeRTOS+POSIX compatibility layer**, the system can be developed and tested on desktop operating systems without requiring dedicated embedded hardware.

This makes the project useful for understanding the fundamentals of **Real-Time Operating Systems, embedded systems, concurrent programming, and task scheduling**.

---

## 🎯 Project Objectives

The primary objectives of this project are to:

1. Understand the fundamentals of RTOS task scheduling.
2. Demonstrate concurrent execution of multiple real-time tasks.
3. Explore task priorities and scheduling behavior.
4. Implement synchronization between concurrent tasks.
5. Study POSIX-compatible APIs within a FreeRTOS environment.
6. Measure task execution and response latency.
7. Provide a hardware-independent environment for RTOS experimentation.

---

## 🚀 Key Features

### Real-Time Task Simulation

Simulates multiple independent tasks operating concurrently within a real-time environment.

### Priority-Based Scheduling

Demonstrates how task priorities influence execution and resource allocation.

### Multitasking

Multiple tasks execute concurrently using the FreeRTOS+POSIX abstraction layer.

### Synchronization

Demonstrates coordination between tasks and safe access to shared resources.

### POSIX Compatibility

Uses the FreeRTOS+POSIX API to provide familiar POSIX threading and timing interfaces.

### Timing & Monitoring

Supports periodic task execution and monitoring of task activity and system behavior.

### Modular Architecture

The project separates source code, headers, build configuration, testing, and documentation for maintainability.

### Cross-Platform Development

The project can be built and tested using Windows, Linux, and WSL-based development environments.

---

## 🧠 System Architecture

The simulator models a simplified real-time system consisting of independent tasks.

```text
                    ┌─────────────────────────┐
                    │   FreeRTOS + POSIX      │
                    │     Scheduling Layer    │
                    └────────────┬────────────┘
                                 │
             ┌───────────────────┼───────────────────┐
             │                   │                   │
             ▼                   ▼                   ▼
      ┌─────────────┐     ┌─────────────┐     ┌─────────────┐
      │ Sensor Task │     │ Control Task│     │ Logger Task │
      │             │     │             │     │             │
      │ Data Input  │────▶│ Processing  │────▶│ Logging     │
      └─────────────┘     └─────────────┘     └─────────────┘
             │                   │                   │
             └───────────────────┼───────────────────┘
                                 ▼
                      ┌─────────────────────┐
                      │  Monitor / Metrics  │
                      │                     │
                      │ Latency & Activity  │
                      └─────────────────────┘
```

The architecture focuses on the interaction between **periodic tasks, scheduling decisions, synchronization, and system monitoring**.

---

## 🛠️ Technology Stack

| Technology         | Purpose                                |
| ------------------ | -------------------------------------- |
| **C**              | Core implementation                    |
| **FreeRTOS+POSIX** | RTOS and POSIX compatibility layer     |
| **POSIX Threads**  | Concurrent task execution              |
| **GCC**            | Compilation                            |
| **GNU Make**       | Linux/WSL build system                 |
| **MSYS2 / MinGW**  | Windows development environment        |
| **WSL**            | Linux-based development and testing    |
| **Batch Scripts**  | Windows build and execution automation |

---

## 📂 Project Structure

```text
Real-Time-Operating-System-Scheduling-Simulator/
│
├── .vscode/                     # VS Code configuration
│
├── build_wsl/                   # WSL/Linux build files
│
├── include/                     # Header files
│
├── test/                        # Build and validation tests
│
├── rts_simulation.c             # Main simulation source
│
├── build_rts.bat                # Windows build script
├── run_rts.bat                  # Windows execution script
│
├── QUICK_START.md               # Quick setup instructions
├── SETUP_GUIDE.md               # Detailed environment setup
├── PROJECT_FILES.md             # Project file documentation
├── README_RUN_PROJECT.md        # Project execution guide
├── RTS_PROJECT_README.md        # Extended project documentation
├── START_HERE.txt               # Entry point for new users
│
├── LICENSE                      # MIT License
└── README.md                    # Project documentation
```

---

## ⚙️ Getting Started

### Prerequisites

Make sure the following tools are installed:

* GCC
* GNU Make
* Git
* CMake (if required by the build configuration)
* MSYS2/MinGW on Windows
* WSL for Linux-based development

---

### 1. Clone the Repository

```bash
git clone https://github.com/Tejasai120603/Real-Time-Operating-System-Scheduling-Simulator.git
```

### 2. Navigate to the Project

```bash
cd Real-Time-Operating-System-Scheduling-Simulator
```

---

## 🪟 Build & Run on Windows

Using the configured MSYS2/MinGW environment:

```bash
./build_rts.bat
```

After a successful build:

```bash
./run_rts.bat
```

---

## 🐧 Build & Run on Linux / WSL

Navigate to the project directory:

```bash
cd Real-Time-Operating-System-Scheduling-Simulator
```

Build the project using the available build configuration:

```bash
make
```

Then execute the simulator:

```bash
./rts_simulation
```

> For environment-specific instructions, refer to [`SETUP_GUIDE.md`](SETUP_GUIDE.md) and [`QUICK_START.md`](QUICK_START.md).

---

## 📊 Simulation & Performance

The simulator can be used to observe and evaluate real-time task behavior using metrics such as:

* Task execution count
* Scheduling activity
* Task response latency
* Maximum and minimum observed latency
* Periodic task execution
* System monitoring activity

Example simulation metrics from the development environment:

| Metric           | Observed Value |
| ---------------- | -------------: |
| Sensor Reads     |             57 |
| Control Commands |             57 |
| Log Entries      |            103 |
| Monitor Checks   |             28 |
| Average Latency  |           8 ms |
| Maximum Latency  |          47 ms |
| Minimum Latency  |           0 ms |

These measurements provide a practical way to study the relationship between **task workload, scheduling, synchronization, and response latency**.

---

## 🧩 Core RTOS Concepts Demonstrated

This project provides practical exposure to:

* **Task Scheduling**
* **Task Priorities**
* **Preemptive Multitasking**
* **Concurrency**
* **Thread Synchronization**
* **Inter-Task Communication**
* **POSIX APIs**
* **Real-Time Timing**
* **Task Monitoring**
* **Latency Measurement**
* **Embedded Software Concepts**

---

## 🔬 Learning Outcomes

After working with this project, developers should have a better understanding of:

* How RTOS schedulers manage concurrent tasks.
* How task priorities affect system behavior.
* How synchronization prevents conflicts between concurrent tasks.
* How periodic real-time tasks can be modeled.
* How POSIX APIs can be used with FreeRTOS.
* How real-time latency can be measured and analyzed.
* How RTOS applications can be developed without physical embedded hardware.

---

## 🔮 Future Improvements

Planned enhancements include:

* [ ] Additional scheduling algorithms such as **Rate Monotonic (RM)** and **Earliest Deadline First (EDF)**
* [ ] Priority inheritance
* [ ] Deadline monitoring
* [ ] Deadline-miss detection
* [ ] Deadlock simulation
* [ ] CPU utilization analysis
* [ ] Gantt-chart-based task visualization
* [ ] Interactive task monitoring dashboard
* [ ] Extended benchmarking
* [ ] Improved cross-platform build support
* [ ] Hardware-based validation using a microcontroller

---

## 📚 Documentation

Additional documentation is available in the repository:

* [`QUICK_START.md`](QUICK_START.md) — Quick project setup
* [`SETUP_GUIDE.md`](SETUP_GUIDE.md) — Development environment configuration
* [`PROJECT_FILES.md`](PROJECT_FILES.md) — Project file structure
* [`README_RUN_PROJECT.md`](README_RUN_PROJECT.md) — Running the simulator
* [`RTS_PROJECT_README.md`](RTS_PROJECT_README.md) — Extended project documentation
* [`START_HERE.txt`](START_HERE.txt) — Beginner-friendly entry point

---

## 🎓 Academic Context

This project was developed as part of an exploration of **Real-Time Operating Systems and embedded software development**.

It focuses on applying theoretical concepts such as scheduling, multitasking, synchronization, and real-time performance analysis in a practical software-based simulation.

---

## 👨‍💻 Author

### Teja Sai

**B.Tech – Electronics and Computer Engineering (EAC)**
**Amrita Vishwa Vidyapeetham, Bengaluru**

GitHub: [@Tejasai120603](https://github.com/Tejasai120603)
LinkedIn:[Teja Sai Yallamelli] (https://linkedin.com/in/teja-sai-yallamelli-a5685b320)

---

## 🤝 Contributing

Contributions, suggestions, bug reports, and improvements are welcome.

If you would like to contribute:

1. Fork the repository.
2. Create a new feature branch.
3. Implement your changes.
4. Test the changes.
5. Submit a Pull Request.

---

## ⭐ Support

If you find this project useful for learning about **RTOS, scheduling, embedded systems, or concurrent programming**, consider giving the repository a ⭐.

---

<p align="center">
  <b>Real-Time Scheduling • FreeRTOS+POSIX • C • Embedded Systems</b>
</p>
