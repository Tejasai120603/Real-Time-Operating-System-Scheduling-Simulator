# Real-Time Scheduling (RTS) Simulation using FreeRTOS+POSIX

> A C-based Real-Time Scheduling (RTS) simulation built using the FreeRTOS+POSIX wrapper to demonstrate task scheduling, multitasking, synchronization, and core Real-Time Operating System (RTOS) concepts.

---

## 📖 Overview

This project demonstrates the implementation of a Real-Time Scheduling (RTS) simulation using the FreeRTOS+POSIX API. It provides a practical environment for understanding how real-time operating systems manage multiple concurrent tasks through scheduling algorithms, thread management, synchronization mechanisms, and timing operations.

The simulator is designed as an educational and experimental platform for students, embedded systems enthusiasts, and developers interested in learning RTOS concepts without requiring dedicated embedded hardware.

The project is implemented entirely in **C** and utilizes the **FreeRTOS+POSIX** threading wrapper, enabling execution on desktop operating systems while preserving FreeRTOS programming concepts.

---

## 🚀 Features

- Real-Time task scheduling simulation
- POSIX thread-based FreeRTOS implementation
- Multi-threaded task execution
- Modular project architecture
- Build automation scripts
- Well-organized source code
- Test environment for validation
- Comprehensive project documentation
- Beginner-friendly implementation for RTOS learning

---

## 🛠️ Technologies Used

- C Programming Language
- FreeRTOS+POSIX
- POSIX Threads (pthreads)
- GCC Compiler
- Make / Build Scripts
- Windows Batch Automation

---

## 📂 Project Structure

```
RTS-Simulation/
│
├── build/                 # Build output
├── build_wsl/             # Linux/WSL build files
├── include/               # Header files
├── test/                  # Test files
│
├── rts_simulation.c       # Main source code
├── build_rts.bat          # Build script
├── run_rts.bat            # Run script
│
├── README.md
├── QUICK_START.md
├── SETUP_GUIDE.md
├── PROJECT_FILES.md
├── RTS_PROJECT_README.md
└── LICENSE
```

---

## ⚙️ Getting Started

### Clone the repository

```bash
git clone https://github.com/YourUsername/RTS-Simulation.git
```

### Navigate to the project

```bash
cd RTS-Simulation
```

### Build the project

Windows

```bash
build_rts.bat
```

Linux / WSL

```bash
make
```

### Run the simulation

```bash
run_rts.bat
```

or

```bash
./rts_simulation
```

---

## 🎯 Learning Objectives

This project helps in understanding:

- Real-Time Operating Systems
- POSIX Threading
- Task Scheduling
- Concurrent Programming
- Thread Synchronization
- Scheduling Policies
- Embedded Software Development
- Operating System Concepts

---

## 📚 Documentation

The repository contains detailed documentation to help users understand and execute the project.

- 📄 Quick Start Guide
- 📄 Setup Guide
- 📄 Project Documentation
- 📄 Build Instructions

---

## 🔮 Future Enhancements

- Support additional scheduling algorithms
- Priority inheritance implementation
- Deadlock simulation
- Task monitoring dashboard
- Performance benchmarking
- Cross-platform build improvements
- Enhanced visualization of task execution

---

## 👨‍💻 Author

**Teja Sai**

B.Tech – Electronics and Computer Engineering  
Amrita Vishwa Vidyapeetham, Bengaluru

GitHub: https://github.com/Tejasai120603

---

## 🤝 Contributions

Contributions, suggestions, and improvements are welcome.

Feel free to fork this repository and submit a Pull Request.

---

## 📜 License

This project is released under the MIT License.
See the `LICENSE` file for more details.

---

## ⭐ Support

If you found this project useful, consider giving it a ⭐ on GitHub. It helps others discover the project and motivates future improvements.
