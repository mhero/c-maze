#include <stdio.h>
#include <stdlib.h>
#include "maze_generator.h"
#include "file_manager.h"

int main() {
    int height, width;
    char option;
    Maze maze;

    printf("Would you like to (g)enerate a new maze or (l)oad a maze from file? ");
    scanf(" %c", &option);

    if (option == 'g') {
        printf("Enter the height of the maze: ");
        scanf("%d", &height);
        printf("Enter the width of the maze: ");
        scanf("%d", &width);

        Coordinates coord = {height, width};
        maze_init(&maze, coord);
        display_maze(&maze);

        save_maze_data_to_file(&maze, "maze_data.txt");

    } else if (option == 'l') {
        load_maze_data_from_file(&maze, "maze_data.txt");
        display_maze(&maze);
    } else {
        printf("Invalid option!\n");
        return 1;
    }

    maze_free(&maze);

    return 0;
}
