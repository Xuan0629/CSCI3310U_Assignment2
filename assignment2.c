#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

// Function to create directory structure
void createDirectoryStructure(const char *usertype, const char *username) {
    char path[256];
    char profilePath[256];
    char logMessage[512];
    FILE *logFile;

    // Open log file in append mode
    logFile = fopen("logfile.txt", "a");
    if (logFile == NULL) {
        perror("Error opening log file");
        exit(EXIT_FAILURE);
    }

    // Requirement 1: Create directory structure
    // Create usertype directory
    snprintf(path, sizeof(path), "%s", usertype);
    if (mkdir(path, 0755) == -1) {
        snprintf(logMessage, sizeof(logMessage), "Directory %s already exists or could not be created.\n", path);
        printf("%s", logMessage);
        fprintf(logFile, "%s", logMessage);
    } else {
        snprintf(logMessage, sizeof(logMessage), "Directory %s created successfully.\n", path);
        printf("%s", logMessage);
        fprintf(logFile, "%s", logMessage);
    }

    // Create username directory inside usertype directory
    snprintf(path, sizeof(path), "%s/%s", usertype, username);
    if (mkdir(path, 0755) == -1) {
        snprintf(logMessage, sizeof(logMessage), "Directory %s already exists or could not be created.\n", path);
        printf("%s", logMessage);
        fprintf(logFile, "%s", logMessage);
    } else {
        snprintf(logMessage, sizeof(logMessage), "Directory %s created successfully.\n", path);
        printf("%s", logMessage);
        fprintf(logFile, "%s", logMessage);
    }

    // Create home directory inside username directory
    snprintf(path, sizeof(path), "%s/%s/home", usertype, username);
    if (mkdir(path, 0755) == -1) {
        snprintf(logMessage, sizeof(logMessage), "Directory %s already exists or could not be created.\n", path);
        printf("%s", logMessage);
        fprintf(logFile, "%s", logMessage);
    } else {
        snprintf(logMessage, sizeof(logMessage), "Directory %s created successfully.\n", path);
        printf("%s", logMessage);
        fprintf(logFile, "%s", logMessage);
    }

    // Create profile.txt file inside home directory
    snprintf(profilePath, sizeof(profilePath), "%s/%s/home/profile.txt", usertype, username);
    FILE *profileFile = fopen(profilePath, "w");
    if (profileFile == NULL) {
        snprintf(logMessage, sizeof(logMessage), "File %s could not be created.\n", profilePath);
        printf("%s", logMessage);
        fprintf(logFile, "%s", logMessage);
    } else {
        // Get current system date and time
        time_t now = time(NULL);
        char *dateTime = ctime(&now);
        dateTime[strlen(dateTime) - 1] = '\0'; // Remove newline character

        // Write to profile.txt
        fprintf(profileFile, "%s profile created on %s\n", username, dateTime);
        fclose(profileFile);

        snprintf(logMessage, sizeof(logMessage), "File %s created successfully.\n", profilePath);
        printf("%s", logMessage);
        fprintf(logFile, "%s", logMessage);
    }

    // Requirement 2: Set profile.txt permissions to read-only
    if (chmod(profilePath, 0444) == -1) {
        snprintf(logMessage, sizeof(logMessage), "Could not set permissions for %s.\n", profilePath);
        printf("%s", logMessage);
        fprintf(logFile, "%s", logMessage);
    } else {
        snprintf(logMessage, sizeof(logMessage), "Permissions set to read-only for %s.\n", profilePath);
        printf("%s", logMessage);
        fprintf(logFile, "%s", logMessage);
    }

    // Requirement 3: Log each operation to logfile.txt and console
    // Logging is done throughout the function using fprintf and printf

    // Close log file
    fclose(logFile);
}

int main() {
    FILE *file;
    char line[256];
    char *usertype, *username;

    // Open the input file
    file = fopen("input.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Read the file line by line
    while (fgets(line, sizeof(line), file)) {
        // Remove newline character if present
        line[strcspn(line, "\n")] = 0;

        // Split the line into tokens
        usertype = strtok(line, ",");
        username = strtok(NULL, ",");

        // Requirement 1: Create directory structure based on input file
        createDirectoryStructure(usertype, username);
    }

    // Close the file
    fclose(file);

    return 0;
}