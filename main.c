#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#ifdef _WIN32
    #include <Windows.h>
    #define SLEEP_MS(x) Sleep(x)
#else
    #include <unistd.h>
    #define SLEEP_MS(x) usleep((x) * 1000)
#endif

int main() {
    time_t raw_time = 0;
    struct tm time_info;
    bool is_running = true;
    
    printf("DIGITAL CLOCK\n");
    printf("Press Ctrl+C to exit\n\n");
    
    while (is_running) {
        time(&raw_time);
        
        #ifdef _WIN32
            // Windows: use localtime_s
            errno_t result = localtime_s(&time_info, &raw_time);
            if (result != 0) {
                printf("Error: Failed to get local time\n");
                break;
            }
        #else
            // POSIX: use localtime_r
            if (localtime_r(&raw_time, &time_info) == NULL) {
                printf("Error: Failed to get local time\n");
                break;
            }
        #endif
        
        // Clear the previous line and print new time
        printf("\r%02d:%02d:%02d", 
               time_info.tm_hour, 
               time_info.tm_min, 
               time_info.tm_sec);
        fflush(stdout);
        
        SLEEP_MS(1000);
    }
    
    printf("\nClock stopped.\n");
    return 0;
}
