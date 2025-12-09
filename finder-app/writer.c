#include <stdio.h>
#include <syslog.h>
#include <string.h>

int main(int argc, char** argv) { 
    openlog(argv[0], 0, LOG_USER);

    if (argc <= 2){
        syslog(LOG_ERR, "Missing necessary runtime argument");
        closelog();
        return 1; // indicates unsecessful exe
    }

    FILE *file_ptr;
    file_ptr = fopen(argv[1], "w");
    if(!file_ptr){
        syslog(LOG_ERR, "Could not open/create file");
        closelog();
    }
    
    size_t len = strlen(argv[2]);
    size_t written = fwrite(argv[2], sizeof(char), strlen(argv[2]), file_ptr);

    if (len != written) {
        syslog(LOG_ERR, "Could not write to file");
        closelog();
        return 1; // indicates unsecessful exe
    }

    fclose(file_ptr);
    closelog();
    return 0; // indicates successful exe
}
