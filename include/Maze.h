#pragma once

#include <vector>

enum {
    TO_WEST = 0x01,
    TO_EAST = 0x02,
    TO_NORTH = 0x04,
    TO_SOUTH = 0x08
};

enum {
    DFS_SOLVER,
    BFS_SOLVER
};

typedef struct Cell {
    int Direction = 0x00;
    bool Generated = false;
    bool Visited = false;
} Cell;

class AMaze {
    private:
        int N;
        Cell* Maze = nullptr;
        std::vector<std::pair<int, int>> DFSPath;
    public:
        inline explicit AMaze (int GivenN) : N(GivenN) {
            Maze = new Cell[GivenN * GivenN];
        }
        void SetDirection (int X, int Y, int GivenDirection);
        void SetGenerated (int X, int Y);
        void SetVisited (int X, int Y);
        int GetDirection (int X, int Y);
        bool IsGenerated (int X, int Y);
        bool IsVisited (int X, int Y);
        void ClearVisited ();
        void Generate ();
        bool Solve (int GivenSolver);


        std::vector<std::pair<int, int>> GetDFSPath ();
};

