#include <stack>

#include <Maze.h>


void AMaze::SetDirection (int X, int Y, int GivenDirection) {
    Maze[X + Y * N].Direction |= GivenDirection;
}

void AMaze::SetGenerated (int X, int Y) {
    Maze[X + Y * N].Generated = true;
}

void AMaze::SetVisited (int X, int Y) {
    Maze[X + Y * N].Visited = true;
}

int AMaze::GetDirection (int X, int Y) {
    return Maze[X + Y * N].Direction;
}

bool AMaze::IsGenerated (int X, int Y) {
    return Maze[X + Y * N].Generated;
}

bool AMaze::IsVisited (int X, int Y) {
    return Maze[X + Y * N].Visited;
}

void DFS (int N, AMaze *Maze, std::stack<std::pair<int, int>> &Stack, int &Visited) {
    while (Visited < N * N) {
        int X = Stack.top().first;
        int Y = Stack.top().second;

        std::vector<int> Neighbors;

        if (X > 0 && !Maze->IsGenerated(X - 1, Y)) {
            Neighbors.push_back(TO_WEST);
        }

        if (X < N - 1 && !Maze->IsGenerated(X + 1, Y)) {
            Neighbors.push_back(TO_EAST);
        }

        if (Y > 0 && !Maze->IsGenerated(X, Y - 1)) {
            Neighbors.push_back(TO_NORTH);
        }

        if (Y < N - 1 && !Maze->IsGenerated(X, Y + 1)) {
            Neighbors.push_back(TO_SOUTH);
        }

        if (!Neighbors.empty()) {
            int RandomNext = Neighbors[rand() % (int)Neighbors.size()];
            switch (RandomNext) {
                case TO_WEST:
                    Maze->SetGenerated(X - 1, Y);
                    Maze->SetDirection(X - 1, Y, TO_EAST);
                    Maze->SetDirection(X, Y, TO_WEST);
                    Stack.push(std::make_pair(X - 1, Y + 0));
                    break;
                case TO_EAST:
                    Maze->SetGenerated(X + 1, Y);
                    Maze->SetDirection(X + 1, Y, TO_WEST);
                    Maze->SetDirection(X, Y, TO_EAST);
                    Stack.push(std::make_pair(X + 1, Y + 0));
                    break;
                case TO_NORTH:
                    Maze->SetGenerated(X, Y - 1);
                    Maze->SetDirection(X, Y - 1, TO_SOUTH);
                    Maze->SetDirection(X, Y, TO_NORTH);
                    Stack.push(std::make_pair(X + 0, Y - 1));
                    break;
                case TO_SOUTH:
                    Maze->SetGenerated(X, Y + 1);
                    Maze->SetDirection(X, Y + 1, TO_NORTH);
                    Maze->SetDirection(X, Y, TO_SOUTH);
                    Stack.push(std::make_pair(X + 0, Y + 1));
                    break;
            }
            Visited++;
        } else {
            Stack.pop();
        }
    }
}

void AMaze::ClearVisited () {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            this->Maze[j + i * N].Visited = false;
        }
    }
}

void AMaze::Generate () {
    int Visited = 0;
    std::stack<std::pair<int, int>> Stack;

    int X = rand() % N;
    int Y = rand() % N;
    Stack.push(std::make_pair(X, Y));
    this->SetGenerated(X, Y);
    Visited++;

    DFS(N, this, Stack, Visited);

    DFSPath.push_back(std::make_pair(0, 0));
}

bool AMaze::Solve (int GivenSolver) {

    switch (GivenSolver) {
        case DFS_SOLVER:
            int X = DFSPath.back().first;
            int Y = DFSPath.back().second;

            if (X == N - 1 && Y == N - 1) {
                this->ClearVisited();
                return true;
            }

            this->SetVisited(X, Y);
            bool DeadEnd = true;

            if ((this->GetDirection(X, Y) & TO_WEST) && !this->IsVisited(X - 1, Y)) {
                DFSPath.push_back(std::make_pair(X - 1, Y));
                DeadEnd = false;
            }
            if ((this->GetDirection(X, Y) & TO_EAST) && !this->IsVisited(X + 1, Y)) {
                DFSPath.push_back(std::make_pair(X + 1, Y));
                DeadEnd = false;
            }
            if ((this->GetDirection(X, Y) & TO_NORTH) && !this->IsVisited(X, Y - 1)) {
                DFSPath.push_back(std::make_pair(X, Y - 1));
                DeadEnd = false;
            }
            if ((this->GetDirection(X, Y) & TO_SOUTH) && !this->IsVisited(X, Y + 1)) {
                DFSPath.push_back(std::make_pair(X, Y + 1));
                DeadEnd = false;
            }

            if (DeadEnd) {
                DFSPath.pop_back();
            }
    }
}

std::vector<std::pair<int, int>> AMaze::GetDFSPath () {
    return DFSPath;
}
