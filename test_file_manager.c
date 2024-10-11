#include "./unity/src/unity.h"
#include "file_manager.h"
#include <stdlib.h>
Maze maze;


void setUp(void) {

    maze.base.coordinates.x = 3; 
    maze.base.coordinates.y = 3;

    maze.base.maze = (int **)malloc(maze.base.coordinates.x * sizeof(int *));
    for (int i = 0; i < maze.base.coordinates.x; i++) {
        maze.base.maze[i] = (int *)malloc(maze.base.coordinates.y * sizeof(int));
    }

    int exampleMaze[3][3] = {
        {1, 0, 1},
        {0, 1, 0},
        {1, 1, 1}
    };

    for (int i = 0; i < maze.base.coordinates.x; i++) {
        for (int j = 0; j < maze.base.coordinates.y; j++) {
            maze.base.maze[i][j] = exampleMaze[i][j];
        }
    }
}

void tearDown(void) {
    for (int i = 0; i < maze.base.coordinates.x; i++) {
        free(maze.base.maze[i]);
    }
    free(maze.base.maze);
}

void test_save_maze_data_to_file(void) {
    save_maze_data_to_file(&maze, "test_maze.bin");

    FILE *file = fopen("test_maze.bin", "rb");
    TEST_ASSERT_NOT_NULL(file);
    fclose(file);
}

void test_load_maze_data_from_file(void) {
    save_maze_data_to_file(&maze, "test_maze.bin");

    Maze loadedMaze;
    load_maze_data_from_file(&loadedMaze, "test_maze.bin");

    TEST_ASSERT_EQUAL(maze.base.coordinates.x, loadedMaze.base.coordinates.x);
    TEST_ASSERT_EQUAL(maze.base.coordinates.y, loadedMaze.base.coordinates.y);

    for (int i = 0; i < loadedMaze.base.coordinates.x; i++) {
        for (int j = 0; j < loadedMaze.base.coordinates.y; j++) {
            TEST_ASSERT_EQUAL(maze.base.maze[i][j], loadedMaze.base.maze[i][j]);
        }
    }

    for (int i = 0; i < loadedMaze.base.coordinates.x; i++) {
        free(loadedMaze.base.maze[i]);
    }
    free(loadedMaze.base.maze);
}


int main(void) {
    UNITY_BEGIN(); 
    RUN_TEST(test_save_maze_data_to_file);
    RUN_TEST(test_load_maze_data_from_file);
    return UNITY_END();
}
