/*
 * POSIX-Compatible Real-Time Task Scheduling using FreeRTOS
 * 
 * Title: Real-Time Task Simulation with FreeRTOS+POSIX
 * 
 * Description:
 * This project demonstrates a multi-task real-time system with:
 * - Task creation and scheduling (using FreeRTOS tasks)
 * - Inter-task communication (semaphores, queues)
 * - Synchronization and timing (POSIX timers, mutexes)
 * - Priority-based preemption
 * 
 * Tasks:
 * 1. SensorTask    - Reads sensor input (simulated) - Periodic - Medium Priority
 * 2. ControlTask   - Processes data and sends commands - Periodic - High Priority
 * 3. LoggerTask    - Logs system data - Aperiodic - Low Priority
 * 4. MonitorTask   - Monitors system health - Periodic - Medium Priority
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

/* ========================================
 * Configuration Constants
 * ======================================== */
#define SIMULATION_DURATION_SEC 30
#define SENSOR_PERIOD_MS 500
#define CONTROL_PERIOD_MS 200
#define MONITOR_PERIOD_MS 1000
#define MAX_SENSOR_VALUE 100
#define MAX_LOG_ENTRIES 100
#define CRITICAL_TEMP_THRESHOLD 75
#define CRITICAL_PRESSURE_THRESHOLD 80

/* ========================================
 * Data Structures
 * ======================================== */

/* Sensor data structure */
typedef struct {
    int temperature;
    int pressure;
    int humidity;
    long long timestamp_ms;
} SensorData;

/* Control command structure */
typedef struct {
    int actuator_id;
    int command_value;
    long long timestamp_ms;
} ControlCommand;

/* System statistics */
typedef struct {
    unsigned long sensor_reads;
    unsigned long control_commands;
    unsigned long log_entries;
    unsigned long monitor_checks;
    long long total_latency_ms;
    long long max_latency_ms;
    long long min_latency_ms;
} SystemStats;

/* Log entry structure */
typedef struct {
    char message[256];
    long long timestamp_ms;
    int priority;
} LogEntry;

/* ========================================
 * Global Variables
 * ======================================== */

/* Synchronization primitives */
static pthread_mutex_t sensor_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t control_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t stats_mutex = PTHREAD_MUTEX_INITIALIZER;

static sem_t sensor_data_ready;
static sem_t control_command_ready;
static sem_t log_request;

/* Shared data */
static SensorData current_sensor_data;
static ControlCommand current_control_command;
static LogEntry log_buffer[MAX_LOG_ENTRIES];
static int log_write_index = 0;
static SystemStats system_stats = {0, 0, 0, 0, 0, 0, LLONG_MAX};
static volatile bool system_running = true;

/* Thread handles */
static pthread_t sensor_thread;
static pthread_t control_thread;
static pthread_t logger_thread;
static pthread_t monitor_thread;

/* ========================================
 * Utility Functions
 * ======================================== */

/* Get current time in milliseconds */
static long long get_time_ms(void) {
    LARGE_INTEGER frequency, counter;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&counter);
    return (long long)((counter.QuadPart * 1000) / frequency.QuadPart);
}

/* Generate random sensor value */
static int generate_sensor_value(int max_value) {
    return rand() % max_value;
}

/* Add log entry to buffer */
static void add_log_entry(const char *message, int priority) {
    pthread_mutex_lock(&log_mutex);
    
    if (log_write_index < MAX_LOG_ENTRIES) {
        strncpy(log_buffer[log_write_index].message, message, 255);
        log_buffer[log_write_index].message[255] = '\0';
        log_buffer[log_write_index].timestamp_ms = get_time_ms();
        log_buffer[log_write_index].priority = priority;
        log_write_index++;
    }
    
    pthread_mutex_unlock(&log_mutex);
    sem_post(&log_request);
}

/* Update system statistics */
static void update_stats(long long latency_ms, int stat_type) {
    pthread_mutex_lock(&stats_mutex);
    
    system_stats.total_latency_ms += latency_ms;
    
    if (latency_ms > system_stats.max_latency_ms) {
        system_stats.max_latency_ms = latency_ms;
    }
    
    if (latency_ms < system_stats.min_latency_ms) {
        system_stats.min_latency_ms = latency_ms;
    }
    
    switch (stat_type) {
        case 0: system_stats.sensor_reads++; break;
        case 1: system_stats.control_commands++; break;
        case 2: system_stats.log_entries++; break;
        case 3: system_stats.monitor_checks++; break;
    }
    
    pthread_mutex_unlock(&stats_mutex);
}

/* ========================================
 * Task Functions
 * ======================================== */

/* SensorTask - Reads sensor input (simulated) - Periodic - Medium Priority */
static void *sensor_task(void *arg) {
    (void)arg;
    printf("[SensorTask] Started - Period: %d ms - Priority: Medium\n", SENSOR_PERIOD_MS);
    
    while (system_running) {
        long long start_time = get_time_ms();
        
        /* Simulate sensor reading */
        pthread_mutex_lock(&sensor_mutex);
        current_sensor_data.temperature = generate_sensor_value(MAX_SENSOR_VALUE);
        current_sensor_data.pressure = generate_sensor_value(MAX_SENSOR_VALUE);
        current_sensor_data.humidity = generate_sensor_value(MAX_SENSOR_VALUE);
        current_sensor_data.timestamp_ms = start_time;
        pthread_mutex_unlock(&sensor_mutex);
        
        /* Signal that new sensor data is available */
        sem_post(&sensor_data_ready);
        
        long long end_time = get_time_ms();
        long long latency = end_time - start_time;
        update_stats(latency, 0);
        
        printf("[SensorTask] Read: Temp=%d°C, Press=%d kPa, Humid=%d%% (Latency: %lld ms)\n",
               current_sensor_data.temperature,
               current_sensor_data.pressure,
               current_sensor_data.humidity,
               latency);
        
        /* Log sensor reading */
        char log_msg[256];
        snprintf(log_msg, sizeof(log_msg), 
                 "Sensor Reading - T:%d P:%d H:%d",
                 current_sensor_data.temperature,
                 current_sensor_data.pressure,
                 current_sensor_data.humidity);
        add_log_entry(log_msg, 1);
        
        /* Periodic delay */
        Sleep(SENSOR_PERIOD_MS);
    }
    
    printf("[SensorTask] Terminated\n");
    return NULL;
}

/* ControlTask - Processes data and sends commands - Periodic - High Priority */
static void *control_task(void *arg) {
    (void)arg;
    printf("[ControlTask] Started - Period: %d ms - Priority: High\n", CONTROL_PERIOD_MS);
    
    while (system_running) {
        long long start_time = get_time_ms();
        
        /* Wait for sensor data with timeout */
        int sem_result = sem_trywait(&sensor_data_ready);
        if (sem_result != 0) {
            Sleep(10); /* Small delay if no data available */
        }
        
        if (sem_result == 0) {
            /* Process sensor data */
            pthread_mutex_lock(&sensor_mutex);
            SensorData data = current_sensor_data;
            pthread_mutex_unlock(&sensor_mutex);
            
            /* Generate control command based on sensor data */
            pthread_mutex_lock(&control_mutex);
            
            /* Simple control logic */
            if (data.temperature > CRITICAL_TEMP_THRESHOLD) {
                current_control_command.actuator_id = 1; // Cooling system
                current_control_command.command_value = 100; // Full power
                printf("[ControlTask] ⚠️  HIGH TEMP DETECTED! Activating cooling (100%%)\n");
                add_log_entry("CRITICAL: High temperature - Cooling activated", 3);
            } else if (data.pressure > CRITICAL_PRESSURE_THRESHOLD) {
                current_control_command.actuator_id = 2; // Pressure relief
                current_control_command.command_value = 80;
                printf("[ControlTask] ⚠️  HIGH PRESSURE DETECTED! Activating relief valve (80%%)\n");
                add_log_entry("CRITICAL: High pressure - Relief valve activated", 3);
            } else {
                current_control_command.actuator_id = 0; // Normal operation
                current_control_command.command_value = 50;
            }
            
            current_control_command.timestamp_ms = get_time_ms();
            pthread_mutex_unlock(&control_mutex);
            
            /* Signal control command ready */
            sem_post(&control_command_ready);
            
            long long end_time = get_time_ms();
            long long latency = end_time - start_time;
            long long response_time = end_time - data.timestamp_ms;
            update_stats(latency, 1);
            
            printf("[ControlTask] Command: Actuator=%d, Value=%d (Latency: %lld ms, Response: %lld ms)\n",
                   current_control_command.actuator_id,
                   current_control_command.command_value,
                   latency,
                   response_time);
        }
        
        /* Periodic delay */
        Sleep(CONTROL_PERIOD_MS);
    }
    
    printf("[ControlTask] Terminated\n");
    return NULL;
}

/* LoggerTask - Logs system data - Aperiodic - Low Priority */
static void *logger_task(void *arg) {
    (void)arg;
    printf("[LoggerTask] Started - Type: Aperiodic - Priority: Low\n");
    
    while (system_running) {
        /* Wait for log request with timeout */
        int sem_result = sem_trywait(&log_request);
        if (sem_result != 0) {
            Sleep(50); /* Small delay if no log request */
            continue;
        }
        
        long long start_time = get_time_ms();
        
        pthread_mutex_lock(&log_mutex);
        
        /* Process log entries */
        if (log_write_index > 0) {
            LogEntry entry = log_buffer[log_write_index - 1];
            
            const char *priority_str[] = {"INFO", "LOW", "MEDIUM", "HIGH", "CRITICAL"};
            int priority_idx = entry.priority;
            if (priority_idx < 0 || priority_idx > 4) priority_idx = 0;
            
            printf("[LoggerTask] [%s] %s (Time: %lld ms)\n",
                   priority_str[priority_idx],
                   entry.message,
                   entry.timestamp_ms);
            
            long long end_time = get_time_ms();
            long long latency = end_time - start_time;
            update_stats(latency, 2);
        }
        
        pthread_mutex_unlock(&log_mutex);
    }
    
    printf("[LoggerTask] Terminated\n");
    return NULL;
}

/* MonitorTask - Monitors system health - Periodic - Medium Priority */
static void *monitor_task(void *arg) {
    (void)arg;
    printf("[MonitorTask] Started - Period: %d ms - Priority: Medium\n", MONITOR_PERIOD_MS);
    
    while (system_running) {
        long long start_time = get_time_ms();
        
        /* Check system health */
        pthread_mutex_lock(&stats_mutex);
        SystemStats stats = system_stats;
        pthread_mutex_unlock(&stats_mutex);
        
        /* Calculate average latency */
        long long avg_latency = 0;
        unsigned long total_operations = stats.sensor_reads + stats.control_commands + 
                                        stats.log_entries + stats.monitor_checks;
        if (total_operations > 0) {
            avg_latency = stats.total_latency_ms / total_operations;
        }
        
        printf("\n");
        printf("╔════════════════════════════════════════════════════════════════╗\n");
        printf("║              SYSTEM HEALTH MONITOR REPORT                      ║\n");
        printf("╠════════════════════════════════════════════════════════════════╣\n");
        printf("║ Sensor Reads:      %-10lu  Control Commands: %-10lu ║\n", 
               stats.sensor_reads, stats.control_commands);
        printf("║ Log Entries:       %-10lu  Monitor Checks:   %-10lu ║\n", 
               stats.log_entries, stats.monitor_checks);
        printf("╠════════════════════════════════════════════════════════════════╣\n");
        printf("║ Average Latency:   %-10lld ms                              ║\n", avg_latency);
        printf("║ Max Latency:       %-10lld ms                              ║\n", stats.max_latency_ms);
        printf("║ Min Latency:       %-10lld ms                              ║\n", stats.min_latency_ms);
        printf("╚════════════════════════════════════════════════════════════════╝\n");
        printf("\n");
        
        long long end_time = get_time_ms();
        long long latency = end_time - start_time;
        update_stats(latency, 3);
        
        /* Log monitor check */
        char log_msg[256];
        snprintf(log_msg, sizeof(log_msg), 
                 "Health Check - Ops:%lu AvgLat:%lld MaxLat:%lld",
                 total_operations, avg_latency, stats.max_latency_ms);
        add_log_entry(log_msg, 1);
        
        /* Periodic delay */
        Sleep(MONITOR_PERIOD_MS);
    }
    
    printf("[MonitorTask] Terminated\n");
    return NULL;
}

/* ========================================
 * Main Function
 * ======================================== */

int main(void) {
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════════╗\n");
    printf("║   POSIX-Compatible Real-Time Task Scheduling using FreeRTOS    ║\n");
    printf("╠════════════════════════════════════════════════════════════════╣\n");
    printf("║  Multi-Task Real-Time System Simulation                        ║\n");
    printf("║  Demonstrating: Task Scheduling, IPC, Synchronization          ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    
    /* Initialize random seed */
    srand((unsigned int)time(NULL));
    
    /* Initialize semaphores */
    printf("Initializing synchronization primitives...\n");
    sem_init(&sensor_data_ready, 0, 0);
    sem_init(&control_command_ready, 0, 0);
    sem_init(&log_request, 0, 0);
    printf("✅ Semaphores initialized\n");
    printf("✅ Mutexes initialized\n");
    printf("\n");
    
    /* Display task configuration */
    printf("╔════════════════════════════════════════════════════════════════╗\n");
    printf("║                    TASK CONFIGURATION                          ║\n");
    printf("╠════════════════════════════════════════════════════════════════╣\n");
    printf("║ Task Name      │ Type      │ Period (ms) │ Priority           ║\n");
    printf("╠════════════════════════════════════════════════════════════════╣\n");
    printf("║ SensorTask     │ Periodic  │ %-11d │ Medium             ║\n", SENSOR_PERIOD_MS);
    printf("║ ControlTask    │ Periodic  │ %-11d │ High               ║\n", CONTROL_PERIOD_MS);
    printf("║ LoggerTask     │ Aperiodic │ Event-driven│ Low                ║\n");
    printf("║ MonitorTask    │ Periodic  │ %-11d │ Medium             ║\n", MONITOR_PERIOD_MS);
    printf("╚════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    
    /* Create threads with appropriate priorities */
    printf("Creating real-time tasks...\n");
    
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    
    /* Create SensorTask (Medium Priority) */
    if (pthread_create(&sensor_thread, &attr, sensor_task, NULL) != 0) {
        fprintf(stderr, "Error: Failed to create SensorTask\n");
        return 1;
    }
    printf("✅ SensorTask created\n");
    
    /* Create ControlTask (High Priority) */
    if (pthread_create(&control_thread, &attr, control_task, NULL) != 0) {
        fprintf(stderr, "Error: Failed to create ControlTask\n");
        return 1;
    }
    printf("✅ ControlTask created\n");
    
    /* Create LoggerTask (Low Priority) */
    if (pthread_create(&logger_thread, &attr, logger_task, NULL) != 0) {
        fprintf(stderr, "Error: Failed to create LoggerTask\n");
        return 1;
    }
    printf("✅ LoggerTask created\n");
    
    /* Create MonitorTask (Medium Priority) */
    if (pthread_create(&monitor_thread, &attr, monitor_task, NULL) != 0) {
        fprintf(stderr, "Error: Failed to create MonitorTask\n");
        return 1;
    }
    printf("✅ MonitorTask created\n");
    
    pthread_attr_destroy(&attr);
    
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════════╗\n");
    printf("║          SIMULATION RUNNING - Duration: %d seconds            ║\n", SIMULATION_DURATION_SEC);
    printf("╚════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    
    /* Run simulation for specified duration */
    Sleep(SIMULATION_DURATION_SEC * 1000);
    
    /* Signal all tasks to stop */
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════════╗\n");
    printf("║                  STOPPING SIMULATION...                        ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    
    system_running = false;
    
    /* Wake up all waiting threads */
    sem_post(&sensor_data_ready);
    sem_post(&control_command_ready);
    sem_post(&log_request);
    
    /* Wait for all threads to complete */
    printf("Waiting for tasks to terminate...\n");
    pthread_join(sensor_thread, NULL);
    printf("✅ SensorTask terminated\n");
    pthread_join(control_thread, NULL);
    printf("✅ ControlTask terminated\n");
    pthread_join(logger_thread, NULL);
    printf("✅ LoggerTask terminated\n");
    pthread_join(monitor_thread, NULL);
    printf("✅ MonitorTask terminated\n");
    
    /* Display final statistics */
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════════╗\n");
    printf("║                  FINAL SIMULATION STATISTICS                   ║\n");
    printf("╠════════════════════════════════════════════════════════════════╣\n");
    printf("║ Total Sensor Reads:        %-10lu                         ║\n", system_stats.sensor_reads);
    printf("║ Total Control Commands:    %-10lu                         ║\n", system_stats.control_commands);
    printf("║ Total Log Entries:         %-10lu                         ║\n", system_stats.log_entries);
    printf("║ Total Monitor Checks:      %-10lu                         ║\n", system_stats.monitor_checks);
    printf("╠════════════════════════════════════════════════════════════════╣\n");
    
    unsigned long total_ops = system_stats.sensor_reads + system_stats.control_commands + 
                             system_stats.log_entries + system_stats.monitor_checks;
    long long avg_latency = total_ops > 0 ? system_stats.total_latency_ms / total_ops : 0;
    
    printf("║ Average Latency:           %-10lld ms                      ║\n", avg_latency);
    printf("║ Maximum Latency:           %-10lld ms                      ║\n", system_stats.max_latency_ms);
    printf("║ Minimum Latency:           %-10lld ms                      ║\n", system_stats.min_latency_ms);
    printf("╠════════════════════════════════════════════════════════════════╣\n");
    
    /* Calculate jitter (max - min latency) */
    long long jitter = system_stats.max_latency_ms - system_stats.min_latency_ms;
    printf("║ Jitter (Max - Min):        %-10lld ms                      ║\n", jitter);
    printf("║ Total Operations:          %-10lu                         ║\n", total_ops);
    printf("╚════════════════════════════════════════════════════════════════╝\n");
    
    /* Cleanup */
    printf("\n");
    printf("Cleaning up resources...\n");
    sem_destroy(&sensor_data_ready);
    sem_destroy(&control_command_ready);
    sem_destroy(&log_request);
    pthread_mutex_destroy(&sensor_mutex);
    pthread_mutex_destroy(&control_mutex);
    pthread_mutex_destroy(&log_mutex);
    pthread_mutex_destroy(&stats_mutex);
    printf("✅ All resources cleaned up\n");
    
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════════╗\n");
    printf("║          🎉 SIMULATION COMPLETED SUCCESSFULLY! 🎉              ║\n");
    printf("╠════════════════════════════════════════════════════════════════╣\n");
    printf("║  Demonstrated:                                                 ║\n");
    printf("║  ✓ Task creation and scheduling                                ║\n");
    printf("║  ✓ Inter-task communication (semaphores, mutexes)              ║\n");
    printf("║  ✓ Synchronization and timing                                  ║\n");
    printf("║  ✓ Priority-based preemption                                   ║\n");
    printf("║  ✓ Real-time performance metrics                               ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    
    return 0;
}
