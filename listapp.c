#include <stdio.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_TASK_LENGTH 50
#define TASKS_FILE "tasks.txt"

typedef struct {
    char task[MAX_TASK_LENGTH];
    int completed;
} Task;

Task taskList[MAX_TASKS];
int numTasks = 0;

void addTask(const char *taskName) {
    if (numTasks < MAX_TASKS) {
        strcpy(taskList[numTasks].task, taskName);
        taskList[numTasks].completed = 0;
        numTasks++;
        printf("Task added: %s\n", taskName);
    } else {
        printf("Task list is full!\n");
    }
}

void showTasks() {
    printf("Tasks:\n");
    for (int i = 0; i < numTasks; i++) {
        printf("%d. [%s] %s\n", i + 1, taskList[i].completed ? "X" : " ", taskList[i].task);
    }
}

void markTaskComplete(int taskIndex) {
    if (taskIndex >= 0 && taskIndex < numTasks) {
        taskList[taskIndex].completed = 1;
        printf("Marked task \"%s\" as complete.\n", taskList[taskIndex].task);
    } else {
        printf("Invalid task index.\n");
    }
}

void saveTasksToFile() {
    FILE *file = fopen(TASKS_FILE, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < numTasks; i++) {
        fprintf(file, "%d|%s|%d\n", i, taskList[i].task, taskList[i].completed);
    }

    fclose(file);
    printf("Tasks saved to file.\n");
}

void loadTasksFromFile() {
    FILE *file = fopen(TASKS_FILE, "r");
    if (file == NULL) {
        return;
    }

    char line[MAX_TASK_LENGTH + 10];
    while (fgets(line, sizeof(line), file)) {
        int index, completed;
        char task[MAX_TASK_LENGTH];
        sscanf(line, "%d|%[^|]|%d", &index, task, &completed);
        strcpy(taskList[index].task, task);
        taskList[index].completed = completed;
        numTasks = index + 1;
    }

    fclose(file);
}

int main() {
    loadTasksFromFile();

    int choice;
    char taskName[MAX_TASK_LENGTH];
    
    do {
        printf("\nTo-Do List App\n");
        printf("1. Add Task\n");
        printf("2. Show Tasks\n");
        printf("3. Mark Task as Complete\n");
        printf("4. Save Tasks to File\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter task name: ");
                scanf(" %[^\n]s", taskName);
                addTask(taskName);
                break;
            case 2:
                showTasks();
                break;
            case 3:
                int taskIndex;
                printf("Enter task index to mark as complete: ");
                scanf("%d", &taskIndex);
                markTaskComplete(taskIndex - 1);
                break;
            case 4:
                saveTasksToFile();
                break;
            case 5:
                printf("Exiting...\n");
                saveTasksToFile();
                break;
            default:
                printf("Invalid choice. Please select a valid option.\n");
                break;
        }
    } while (choice != 5);
    
    return 0;
}
