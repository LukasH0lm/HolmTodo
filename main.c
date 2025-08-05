/**
 * @file main.c
 * @brief HolmTodo - A simple command-line todo application
 * @author LukasH0lm
 * @date 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_SIZE 256

/**
 * @struct TodoItem
 * @brief Represents a single todo item
 */
struct TodoItem
{
    char description[32];
    bool isDone;
};

/* ========================================
 *           DATA TRANSFER METHODS
 * ======================================== */

/**
 * @brief Saves a single todo to file
 * @param description The todo description
 * @param isDone Completion status
 */
void save_todo(char *description, bool isDone)
{
    FILE *file = fopen("TodoList.txt", "a");
    if (file != NULL)
    {
        fprintf(file, "%s,%d\n", description, isDone ? 1 : 0);
        fclose(file);
    }
}

void save_all_todos(struct TodoItem list[], int *count)
{
    FILE *file = fopen("TodoList.txt", "w"); // "w" = overwrite
    if (file != NULL) {
        for (int i = 0; i < *count; i++)
        {
            printf("%s%s%s", "saved " , list[i].description, " to file");
            fprintf(file, "%s,%d\n", list[i].description, list[i].isDone ? 1 : 0);
        }
        fclose(file);  
    }
}

void delete_todo(struct TodoItem list[], int *current_count, char *description)
{

    bool foundLineToBeDeleted = false;
    int lineToBeDeleted = 0;
    for (int i = 0; i < *current_count; i++)
    {

        if (!strcmp(list[i].description, description))
        {
            foundLineToBeDeleted = true;
            lineToBeDeleted = i;
            break;
        }
    }
    if (foundLineToBeDeleted)
    {
        for (int i = lineToBeDeleted + 1; i < *current_count; i++)
        {

            list[i - 1] = list[i];
        }
        (*current_count)--;
        save_all_todos(list, current_count);
        printf("%s%s%s", "todo with description ", description, " deleted\n");
    }
    else
    {
        printf("%s%s%s", "todo with description ", description, " could not be found\n");
    }
}

/**
 * @brief Loads todos from file into the array
 * @param list Array to populate with todos
 * @param max_capacity Maximum number of todos the array can hold
 * @return Number of todos actually loaded
 */
int load_todos(struct TodoItem list[], int max_capacity)
{
    FILE *file = fopen("TodoList.txt", "r");

    // If file doesn't exist, no todos to load
    if (file == NULL)
    {
        return 0;
    }

    int count = 0;
    char description[32];
    int isDone;

    // Read each line: "description,0" or "description,1"
    while (fscanf(file, "%31[^,],%d\n", description, &isDone) == 2)
    {
        if (count >= max_capacity)
        {
            printf("error: could not load saved todos, too many lines");
            break;
        }

        strcpy(list[count].description, description);
        list[count].isDone = (isDone != 0);
        count++;
    }

    fclose(file);
    return count;
}

/* ========================================
 *              COMMAND METHODS
 * ======================================== */

/**
 * @brief Adds a new todo item to the list and saves it to file
 * @param list Array of TodoItem structs to add the item to
 * @param capacity Maximum capacity of the list
 * @param current_count Pointer to current number of items in list
 * @param description Text description of the todo item
 */
void add_todo(struct TodoItem list[], int *current_count, char *description)
{

    if (*current_count >= MAX_SIZE)
    {
        printf("Can't add todo, list is full\n");
        return;
    }

    // Add to memory array
    strcpy(list[*current_count].description, description);
    list[*current_count].isDone = false;
    (*current_count)++;

    // Save to file
    save_todo(description, false);
}

int main(int argc, char *argv[])
{

    struct TodoItem TodoList[MAX_SIZE];
    int count = 0;
    count = load_todos(TodoList, MAX_SIZE);

    if (argc < 2)
    {
        // TODO: Your implementation goes here
        printf("HolmTodo - Command Line Todo App\n");
        printf("Usage: %s <command> [arguments]\n", argv[0]);
        printf("Commands:\n");
        printf("  list                      - List all todos\n");

        printf("  add <description>         - Add a new todo\n");
        printf("  complete <description>    - Mark todo as complete\n");
        printf("  delete <description>      - Delete a todo\n");
        return 0;
    }

    if (strcmp(argv[1], "add") == 0)
    {
        if (argc < 3)
        {
            printf("Error: No description provided for add command\n");
            return 1;
        }
        add_todo(TodoList, &count, argv[2]);
        printf("Added todo: %s\n", argv[2]);
    }

    else if (strcmp(argv[1], "delete") == 0)
    {
        if (argc < 3)
        {
            printf("Error: No description provided for delete command\n");
            return 1;
        }
        delete_todo(TodoList, &count, argv[2]);
    }

    else if (strcmp(argv[1], "list") == 0)
    {
        if (count == 0)
        {
            printf("list is empty\n");
        }
        else
        {
            for (int i = 0; i < count; i++)
            {
                printf("%i. %s [%s]\n", i + 1, TodoList[i].description, TodoList[i].isDone ? "X" : " ");
            }
        }
    }
    else
    {
        printf("Unknown command: %s\n", argv[1]);
        return 1;
    }

    return 0;
}
