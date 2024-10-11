# c-maze

A simple maze generator written in C. This project includes functionality to generate a maze, save it to a file, and load it back from a file. It also features unit tests using the Unity test framework to ensure the correctness of the implementation.

![Render maze example](https://i.imgur.com/oPb8HK4.png)

## Features

- **Maze Generation**: Generate mazes of specified dimensions.
- **File I/O**: Save maze data to binary files and load it back.
- **Testing**: Unit tests to verify functionality using the Unity framework.

## Getting Started

### Prerequisites

Make sure you have the following installed:

- GCC or any compatible C compiler
- Make utility

### Unity Test Framework

This project uses the [Unity test framework](https://github.com/UnityTest/Unity). To include Unity in your project, follow these steps:

**Clone the Unity repository:**

   ```bash
   git clone https://github.com/UnityTest/Unity.git
   ```
Copy the src folder from the cloned Unity repository to your project directory.

### Build and run

**Build the project:**

 ```bash
make
 ```

 **Run the project:**

 ```bash
./maze
 ```

**Run tests**
```bash
 gcc -o test_runner unity/src/unity.c file_manager.c test_file_manager.c -Iunity/src -I.
./test_runner
 ```