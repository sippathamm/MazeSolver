/* TODO
 * Move all draw function to new draw.h, draw.cpp files -> No NEED DFSPath return.
 */

#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <thread>
#include <chrono>

#include <Maze.h>

#define GL_SILENCE_DEPRECATION
#include <glfw3.h>

#define DELAY(A) std::this_thread::sleep_for(std::chrono::milliseconds(A));
#define DFS_SOLVE
// #define BFS_SOLVE

const int Width = 800;
const int Height = 800;

int N = 40;
float CellWidth = 2.0f / N;
float Offset = CellWidth / 4.0f;

bool Solved = false;

std::vector<std::vector<std::pair<int, int>>> From(N, std::vector<std::pair<int, int>> (N));
std::queue<std::pair<int, int>> Search;

void SolveMaze(AMaze &Maze, bool &Solved) {
/*
#ifdef BFS_SOLVE
    int X = Search.front().first;
    int Y = Search.front().second;

    if (X == N - 1 && Y == N - 1) {
        Found = true;
        return;
    }

    Search.pop();
    Maze[Y][X].InPath = true;

    if ((Maze[Y][X].Direction & TO_WEST) && !Maze[Y][X - 1].InPath) {
        Search.push(std::make_pair(X - 1, Y));
        Path.push_back(std::make_pair(X - 1, Y));
        From[Y][X - 1] = std::make_pair(X, Y);
    }
    if ((Maze[Y][X].Direction & TO_EAST) && !Maze[Y][X + 1].InPath) {
        Search.push(std::make_pair(X + 1, Y));
        Path.push_back(std::make_pair(X + 1, Y));
        From[Y][X + 1] = std::make_pair(X, Y);
    }
    if ((Maze[Y][X].Direction & TO_NORTH) && !Maze[Y - 1][X].InPath) {
        Search.push(std::make_pair(X, Y - 1));
        Path.push_back(std::make_pair(X, Y - 1));
        From[Y - 1][X] = std::make_pair(X, Y);
    }
    if ((Maze[Y][X].Direction & TO_SOUTH) && !Maze[Y + 1][X].InPath) {
        Search.push(std::make_pair(X, Y + 1));
        Path.push_back(std::make_pair(X, Y + 1));
        From[Y + 1][X] = std::make_pair(X, Y);
    }
#endif // BFS_SOLVE
*/
}


void DrawCell (float X, float Y, float SizeX, float SizeY, float Red, float Green, float Blue) {
    glColor3f(Red, Green, Blue);
    glBegin(GL_QUADS);
    glVertex2f(X, Y);
    glVertex2f(X + SizeX, Y);
    glVertex2f(X + SizeX, Y - SizeY);
    glVertex2f(X, Y - SizeY);
    glEnd();
}

void DrawMaze (AMaze &Maze, bool &Solved) {
    DELAY(10)

    float PathWidth = 2.0f * Offset;

    for (int X = 0; X < N; X++) {
        for (int Y = 0; Y < N; Y++) {
            float i = -1.0f + ((float)X * CellWidth);
            float j = 1.0f - ((float)Y * CellWidth);

            DrawCell(i + Offset, j - Offset, PathWidth, PathWidth, 1.0f, 1.0f, 1.0f);

            if (Maze.GetDirection(X, Y) & TO_SOUTH) {
                DrawCell(i + Offset, j - (3 * Offset), PathWidth, PathWidth, 1.0f, 1.0f, 1.0f);
            }

            if (Maze.GetDirection(X, Y) & TO_EAST) {
                DrawCell(i + (3 * Offset), j - Offset, PathWidth, PathWidth, 1.0f, 1.0f, 1.0f);
            }

            /*
            if (Maze.IsVisited(X, Y)) {
                DrawCell(i + Offset, j - Offset, PathWidth, PathWidth, 1.0f, 0.0f, 0.0);
                if (Maze.GetDirection(X, Y) & TO_SOUTH) {
                    DrawCell(i + Offset, j - (3 * Offset), PathWidth, PathWidth, 1.0f, 0.0f, 0.0f);
                }
                if (Maze.GetDirection(X, Y) & TO_EAST) {
                    DrawCell(i + (3 * Offset), j - Offset, PathWidth, PathWidth, 1.0f, 0.0f, 0.0f);
                }
            }
            */
        }
    }

    /*
    if (Found) {
        int X = 0;
        int Y = 0;
        float i = -1.0f + ((float)X * CellWidth);
        float j = 1.0f - ((float)Y * CellWidth);
        DrawCell(i + Offset, j - Offset, PathWidth, PathWidth, 0.0f, 1.0f, 0.0);
        if (Maze[Y][X].Direction & TO_SOUTH) {
            DrawCell(i + Offset, j - (3 * Offset), PathWidth, PathWidth, 0.0f, 1.0f, 0.0f);
        }
        if (Maze[Y][X].Direction & TO_EAST) {
            DrawCell(i + (3 * Offset), j - Offset, PathWidth, PathWidth, 0.0f, 1.0f, 0.0f);
        }
        X = N - 1;
        Y = N - 1;
        while (X != 0 || Y != 0) {
            float i = -1.0f + ((float)X * CellWidth);
            float j = 1.0f - ((float)Y * CellWidth);
            DrawCell(i + Offset, j - Offset, PathWidth, PathWidth, 0.0f, 1.0f, 0.0);
            if (Maze[Y][X].Direction & TO_SOUTH) {
                DrawCell(i + Offset, j - (3 * Offset), PathWidth, PathWidth, 0.0f, 1.0f, 0.0f);
            }
            if (Maze[Y][X].Direction & TO_EAST) {
                DrawCell(i + (3 * Offset), j - Offset, PathWidth, PathWidth, 0.0f, 1.0f, 0.0f);
            }
            int _X = X;
            int _Y = Y;
            X = From[_Y][_X].first;
            Y = From[_Y][_X].second;
        }
        return;
    }
    */

    auto Path = Maze.GetDFSPath();
    
    for (auto Each : Path) {
        int X = Each.first;
        int Y = Each.second;
        float i = -1.0f + ((float)X * CellWidth);
        float j = 1.0f - ((float)Y * CellWidth);
        DrawCell(i + Offset, j - Offset, PathWidth, PathWidth, 1.0f, 0.0f, 0.0);
        if (Maze.GetDirection(X, Y) & TO_SOUTH) {
            DrawCell(i + Offset, j - (3 * Offset), PathWidth, PathWidth, 1.0f, 0.0f, 0.0f);
        }
        if (Maze.GetDirection(X, Y) & TO_EAST) {
            DrawCell(i + (3 * Offset), j - Offset, PathWidth, PathWidth, 1.0f, 0.0f, 0.0f);
        }
    }
}

int main () {
    if (glfwInit() == false) {
        std::cout << "Unable to initialize\n";
        return -1;
    }

    GLFWwindow* Window = glfwCreateWindow(Width, Height, "Maze Solver", nullptr, nullptr);

    if (Window == nullptr) {
        std::cout << "Unable to create the window\n";
        glfwTerminate();
    }

    glfwMakeContextCurrent(Window);

    srand(clock());

    AMaze Maze(N);
    Maze.Generate();

    // Search.push(std::make_pair(0, 0));

    while (!glfwWindowShouldClose(Window)) {
        glfwPollEvents();

        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Maze.Solve(DFS_SOLVER);

        DrawMaze(Maze, Solved);

        glfwSwapBuffers(Window);
    }

    glfwDestroyWindow(Window);
    glfwTerminate();

    return 0;
}
