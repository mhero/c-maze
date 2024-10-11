#include <stdio.h>
#include "artifacts.h"
#include <stdlib.h>

void save_maze_data_to_file(Maze *maze, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Failed to open file for writing");
        return;
    }

    fwrite(&maze->base.coordinates.x, sizeof(int), 1, file);
    fwrite(&maze->base.coordinates.y, sizeof(int), 1, file);

    for (int i = 0; i < maze->base.coordinates.x; i++) {
        unsigned char byte = 0;
        int bit_pos = 0;

        for (int j = 0; j < maze->base.coordinates.y; j++) {
            if (maze->base.maze[i][j] == 1) {
                byte |= (1 << bit_pos);
            }
            bit_pos++;

            if (bit_pos == 8) {
                fwrite(&byte, sizeof(unsigned char), 1, file);
                byte = 0;
                bit_pos = 0;
            }
        }

        if (bit_pos > 0) {
            fwrite(&byte, sizeof(unsigned char), 1, file);
        }
    }

    fclose(file);
    printf("Bit-compressed maze data saved to %s\n", filename);
}

void load_maze_data_from_file(Maze *maze, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Failed to open file for reading");
        return;
    }

    fread(&maze->base.coordinates.x, sizeof(int), 1, file);
    fread(&maze->base.coordinates.y, sizeof(int), 1, file);

    int x = maze->base.coordinates.x;
    int y = maze->base.coordinates.y;

    maze->base.maze = (int **)malloc(x * sizeof(int *));
    for (int i = 0; i < x; i++) {
        maze->base.maze[i] = (int *)malloc(y * sizeof(int));
    }

    for (int i = 0; i < x; i++) {
        unsigned char byte = 0;
        int bit_pos = 0;

        for (int j = 0; j < y; j++) {
            if (bit_pos == 0) {
                fread(&byte, sizeof(unsigned char), 1, file);
            }

            maze->base.maze[i][j] = (byte & (1 << bit_pos)) ? 1 : 0;
            bit_pos++;

            if (bit_pos == 8) {
                bit_pos = 0;
            }
        }
    }

    fclose(file);
    printf("Bit-compressed maze data loaded from %s\n", filename);
}
