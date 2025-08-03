#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
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
