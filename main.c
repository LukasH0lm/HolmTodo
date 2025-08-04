#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct TodoItem
{
    char description[32];
    bool isDone;
};

struct TodoItem TodoList[10];

void add_todo(struct TodoItem list[], int capacity, int *current_count, char *description)
{

    if (*current_count >= capacity)
    {
        printf("Can't add todo, list is full\n");
        return;
    }

    strcpy(list[*current_count].description, description);
    list[*current_count].isDone = false;

    (*current_count)++;
}

int main(int argc, char *argv[])
{

#define MAX_SIZE 256
    struct TodoItem TodoList[MAX_SIZE];
    int count = 0;

    if (argc < 2)
    {
        // TODO: Your implementation goes here
        printf("HolmTodo - Command Line Todo App\n");
        printf("Usage: %s <command> [arguments]\n", argv[0]);
        printf("Commands:\n");
        printf("  add <description>  - Add a new todo\n");
        printf("  list              - List all todos\n");
        printf("  complete <id>     - Mark todo as complete\n");
        printf("  delete <id>       - Delete a todo\n");
        return 0;
    }

    if (strcmp(argv[1], "add") == 0)
    {
        if (argc < 3)
        {
            printf("Error: No description provided for add command\n");
            return 1;
        }
        add_todo(TodoList, MAX_SIZE, &count, argv[2]);
        printf("Added todo: %s\n", argv[2]);
    }
    else if (strcmp(argv[1], "list") == 0)
    {
        // TODO: implement list later
        printf("List command not implemented yet\n");
        if (count == 0)
        {
            printf("list is empty");
        }
        else
        {
            for (int i = 0; i < count; i++)
            {
                printf("%i. %s [%s]\n", i+1, TodoList[i].description, TodoList[i].isDone ? "X" : " ");
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
