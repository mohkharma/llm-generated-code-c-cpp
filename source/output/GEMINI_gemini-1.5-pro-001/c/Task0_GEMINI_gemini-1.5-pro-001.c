#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <dirent.h>
#include <string.h>

pthread_mutex_t file_mutex;

void *process_file(void *arg) {
  char *file_path = (char *)arg;

  // Acquire the mutex to ensure exclusive access to the file
  pthread_mutex_lock(&file_mutex);

  // Open the file for reading
  FILE *file = fopen(file_path, "r");

  // Check if the file is open
  if (file != NULL) {
    // Process the file contents here
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
      // Example: print each line
      printf("%s", line);
    }

    // Close the file
    fclose(file);
  } else {
    fprintf(stderr, "Error: Unable to open file: %s
", file_path);
  }

  // Release the mutex
  pthread_mutex_unlock(&file_mutex);

  return NULL;
}

int main() {
  // Directory containing the files to process
  char directory_path[] = "/path/to/directory";

  // Initialize the mutex
  pthread_mutex_init(&file_mutex, NULL);

  // Open the directory
  DIR *dir = opendir(directory_path);
  if (dir == NULL) {
    perror("Error opening directory");
    return 1;
  }

  // Create threads for each file
  struct dirent *entry;
  while ((entry = readdir(dir)) != NULL) {
    // Skip "." and ".." directories
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
      continue;
    }

    // Create the full file path
    char file_path[512];
    snprintf(file_path, sizeof(file_path), "%s/%s", directory_path, entry->d_name);

    // Create a new thread to process the file
    pthread_t thread;
    if (pthread_create(&thread, NULL, process_file, (void *)file_path) != 0) {
      perror("Error creating thread");
      return 1;
    }

    // Detach the thread
    pthread_detach(thread);
  }

  // Close the directory
  closedir(dir);

  // Keep the main thread alive until all files are processed
  while (1) {
    sleep(1);
  }

  // Destroy the mutex
  pthread_mutex_destroy(&file_mutex);

  return 0;
}