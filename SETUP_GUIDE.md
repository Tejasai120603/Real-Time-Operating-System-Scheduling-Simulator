# FreeRTOS+POSIX Setup Guide

This guide will help you set up and run the FreeRTOS+POSIX project on Windows.

## What is FreeRTOS+POSIX?

FreeRTOS+POSIX provides a small subset of the POSIX threading API on top of FreeRTOS, allowing developers familiar with POSIX APIs to develop FreeRTOS applications using familiar threading primitives like:

- **pthread_create, pthread_join, pthread_exit** - Thread management
- **pthread_mutex_t** - Mutexes for synchronization
- **pthread_cond_t** - Condition variables
- **pthread_barrier_t** - Barriers for thread synchronization
- **sem_t** - Semaphores
- **mqueue** - Message queues
- **pthread_rwlock_t** - Read-write locks

## Prerequisites

### 1. Install CMake
- Download from: https://cmake.org/download/
- Choose "Windows x64 Installer"
- During installation, select "Add CMake to the system PATH"

### 2. Install Git
- Download from: https://git-scm.com/download/win
- Use default installation options

### 3. Install a C Compiler

#### Option A: MinGW-w64 (Recommended)
1. Install MSYS2 from https://www.msys2.org/
2. Open MSYS2 terminal and run:
   ```bash
   pacman -S mingw-w64-x86_64-gcc
   pacman -S mingw-w64-x86_64-cmake
   pacman -S mingw-w64-x86_64-make
   ```
3. Add `C:\msys64\mingw64\bin` to your Windows PATH

#### Option B: Visual Studio Build Tools
1. Download Visual Studio Build Tools from Microsoft
2. Install "C++ build tools" workload
3. Open "Developer Command Prompt" to use the compiler

## Project Structure

```
Lab-Project-FreeRTOS-POSIX-main/
├── FreeRTOS-Kernel/              # FreeRTOS kernel source
├── FreeRTOS-Plus-POSIX/          # POSIX wrapper implementation
├── demo/                         # Demo applications
│   ├── posix_threading_demo.c   # Comprehensive threading demo
│   └── CMakeLists.txt           # CMake configuration for demo
├── build_demo.bat               # Windows batch build script
├── build_demo.ps1               # PowerShell build script
└── SETUP_GUIDE.md              # This file
```

## Building the Project

### Method 1: Using Build Scripts (Easiest)

#### Using PowerShell (Recommended):
```powershell
# Navigate to project directory
cd "D:\Btech\4th Year\4-1\Project\RTS\Lab-Project-FreeRTOS-POSIX-main"

# Run PowerShell build script
.\build_demo.ps1
```

#### Using Batch File:
```cmd
# Navigate to project directory
cd "D:\Btech\4th Year\4-1\Project\RTS\Lab-Project-FreeRTOS-POSIX-main"

# Run batch build script
build_demo.bat
```

### Method 2: Manual CMake Build

```cmd
# Navigate to project directory
cd "D:\Btech\4th Year\4-1\Project\RTS\Lab-Project-FreeRTOS-POSIX-main"

# Create build directory
mkdir build
cd build

# Configure with CMake
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ../demo

# Build the project
cmake --build . --config Release
```

## Running the Demo

After successful build, run the demo:

```cmd
cd build\bin
posix_threading_demo.exe
```

## Demo Features

The `posix_threading_demo.c` demonstrates:

1. **Basic Thread Creation**: Creating and joining multiple threads
2. **Mutex Synchronization**: Protecting shared resources with mutexes
3. **Condition Variables**: Thread coordination and signaling
4. **Barrier Synchronization**: Synchronizing multiple threads at a point
5. **Semaphore Usage**: Resource counting and access control
6. **Message Queues**: Inter-thread communication

## Expected Output

The demo will show output similar to:

```
=== FreeRTOS+POSIX Threading Demo ===

Initializing FreeRTOS kernel...
Initializing POSIX primitives...
POSIX primitives initialized successfully!

=== Demo 1: Basic Thread Creation ===
Thread 0: Started
Thread 1: Started
Thread 2: Started
Thread 0: Working... iteration 1
Thread 1: Working... iteration 1
Thread 2: Working... iteration 1
...
All basic threads completed!

=== Demo 2: Mutex Synchronization ===
Thread 0: Incremented counter to 1
Thread 1: Incremented counter to 2
...
Final counter value: 15 (expected: 15)

=== Demo 3: Condition Variables ===
Producer thread: Waiting for threads to be ready...
Consumer thread 1: Ready! (1/2 threads ready)
Consumer thread 2: Ready! (2/2 threads ready)
Producer: All threads ready! Broadcasting signal...
Consumer thread 1: Received broadcast signal!
Consumer thread 2: Received broadcast signal!
Condition variable demo completed!

=== Demo 4: Barrier Synchronization ===
Thread 0: Reaching barrier...
Thread 1: Reaching barrier...
Thread 2: Reaching barrier...
Thread 0: All threads reached barrier! (I'm the serial thread)
Thread 1: All threads reached barrier!
Thread 2: All threads reached barrier!
Barrier demo completed!

=== Demo 5: Semaphore Synchronization ===
Thread 0: Waiting for semaphore...
Thread 0: Acquired semaphore! Working...
Thread 1: Waiting for semaphore...
Thread 1: Acquired semaphore! Working...
...
Semaphore demo completed!

=== Demo 6: Message Queues ===
Producer 1: Sent message 0
Consumer 2: Received from thread 1: 'Message 0 from thread 1' (counter: 0)
...
Message queue demo completed!

=== Cleanup ===
All POSIX primitives cleaned up successfully!
=== Demo Completed Successfully! ===
```

## Troubleshooting

### Common Issues:

1. **"CMake not found"**
   - Install CMake and add it to PATH
   - Restart command prompt after installation

2. **"GCC not found"**
   - Install MinGW-w64 or MSYS2
   - Add compiler to PATH
   - Restart command prompt

3. **"Build failed"**
   - Check that all prerequisites are installed
   - Try using Developer Command Prompt if using Visual Studio
   - Check error messages for specific issues

4. **"Permission denied"**
   - Run command prompt as Administrator
   - Check antivirus software isn't blocking the build

### Getting Help:

- FreeRTOS Documentation: https://www.freertos.org/Documentation/
- POSIX Threading: https://pubs.opengroup.org/onlinepubs/7908799/xsh/threads.html
- CMake Documentation: https://cmake.org/documentation/

## Next Steps

1. **Explore the Code**: Look at `posix_threading_demo.c` to understand POSIX threading
2. **Modify the Demo**: Try adding your own threading patterns
3. **Read Documentation**: Study the FreeRTOS+POSIX source code
4. **Create Your Own**: Build your own applications using POSIX threading

## License

This project is licensed under the MIT License. See LICENSE file for details.

---

**Happy Coding with FreeRTOS+POSIX!** 🚀
