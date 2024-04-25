import pygame
import random

# Define colors using RGB values
WHITE = (255, 255, 255)
GREY = (220, 220, 220)
BLACK = (0, 0, 0)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)

# Define the time interval for updating the screen (in milliseconds)
UPDATE_TIME_MS = 10

# Initialize Pygame
pygame.init()

# Set up the window size and title
window_size = (500, 500)
screen = pygame.display.set_mode(window_size)
pygame.display.set_caption("Maze Solver")

# Define the size of the maze and size of each cell
maze_size = 20
cell_size = window_size[0] // maze_size


class Cell:
    """
    Represent a single cell in the maze.

    Attributes:
        neighbor (list): List to store neighboring cells.
        generated (bool): Flag to track if the cell has been generated.
        visited (bool): Flag to track if the cell has been visited during maze solving.
    """
    def __init__(self) -> None:
        """
        Initialize the cell object.
        """
        self.neighbor: list = []  # List to store neighboring cells
        self.generated: bool = False  # Flag to track if the cell has been generated
        self.visited: bool = False  # Flag to track if the cell has been visited during maze solving

    def set_neighbor(self, neighbor: str) -> None:
        """Set a neighboring cell"""
        self.neighbor.append(neighbor)

    def set_generated(self) -> None:
        """Mark the cell as generated"""
        self.generated = True

    def set_visited(self) -> None:
        """Mark the cell as visited"""
        self.visited = True

    def get_neighbor(self) -> list:
        """Get the list of neighboring cells"""
        return self.neighbor

    def get_generated(self) -> bool:
        """Check if the cell has been generated"""
        return self.generated

    def get_visited(self) -> bool:
        """Check if the cell has been visited"""
        return self.visited


class Maze:
    """
    Represent a maze grid and provides methods to generate and solve the maze.

    Attributes:
        maze_size (int): The size of the maze.
        cell_size (int): The size of each cell in pixels.
        maze (list): List to store cells representing the maze grid.
        path (list): List to store the solution path through the maze.
    """
    def __init__(self, maze_size, cell_size) -> None:
        """
        Initialize the Maze object.

        Parameters:
            maze_size (int): The size of the maze.
            cell_size (int): The size of each cell in pixels.
        """
        self.maze_size: int = maze_size  # Size of the maze.
        self.cell_size: int = cell_size  # Size of each cell in pixels
        self.maze: list[Cell] = [Cell() for _ in range(self.maze_size * self.maze_size)]  # List to store cells
        self.path: list[tuple[int, int]] = list()  # List to store the solution path

    def at(self, x: int, y: int) -> Cell:
        """
        Get the cell at position (x, y) in the maze.

        Parameters:
            x (int): The x-coordinate of the cell.
            y (int): The y-coordinate of the cell.

        Returns:
            Cell: The cell object at the specified position.
        """
        return self.maze[y * self.maze_size + x]

    def generate(self) -> None:
        """
        Generate the maze using a randomized depth-first search algorithm.
        """
        visited: int = 0
        stack: list[tuple[int, int]] = list()

        # Start generating from a random cell
        x: int = random.randint(0, self.maze_size - 1)
        y: int = random.randint(0, self.maze_size - 1)
        stack.append((x, y))
        self.at(x, y).set_generated()
        visited += 1

        while visited < self.maze_size * self.maze_size:
            x = stack[-1][0]
            y = stack[-1][1]

            neighbor: list[str] = list()

            # Check ungenerated neighboring cells
            if x > 0 and self.at(x - 1, y).get_generated() is False:
                neighbor.append('left')
            if x < self.maze_size - 1 and self.at(x + 1, y).get_generated() is False:
                neighbor.append('right')
            if y > 0 and self.at(x, y - 1).get_generated() is False:
                neighbor.append('up')
            if y < self.maze_size - 1 and self.at(x, y + 1).get_generated() is False:
                neighbor.append('down')

            if len(neighbor) > 0:
                random_next: str = random.choice(neighbor)

                # Carve passage to the next cell
                if random_next == 'left':
                    self.at(x, y).set_neighbor('left')
                    self.at(x - 1, y).set_neighbor('right')
                    self.at(x - 1, y).set_generated()
                    stack.append((x - 1, y))
                elif random_next == 'right':
                    self.at(x, y).set_neighbor('right')
                    self.at(x + 1, y).set_neighbor('left')
                    self.at(x + 1, y).set_generated()
                    stack.append((x + 1, y))
                elif random_next == 'up':
                    self.at(x, y).set_neighbor('up')
                    self.at(x, y - 1).set_neighbor('down')
                    self.at(x, y - 1).set_generated()
                    stack.append((x, y - 1))
                elif random_next == 'down':
                    self.at(x, y).set_neighbor('down')
                    self.at(x, y + 1).set_neighbor('up')
                    self.at(x, y + 1).set_generated()
                    stack.append((x, y + 1))
                visited += 1
            else:
                stack.pop()

    def solve(self, show: bool = True, update_time_ms: int = 10, show_visited: bool = True) -> list[tuple[int, int]]:
        """
        Solve the maze using depth-first search.

        Parameters:
            show (bool): Whether to display the solving process (default is True).
            update_time_ms (int): Time interval for updating the display in milliseconds (default is 10).
            show_visited (bool): Whether to show visited cells during the solving process (default is True).

        Returns:
            list[tuple[int, int]]: The solution path through the maze.
        """
        stack: list[tuple[int, int]] = list()

        x: int = 0
        y: int = 0
        stack.append((x, y))
        self.at(x, y).set_visited()

        while x != self.maze_size - 1 or y != self.maze_size - 1:
            x = stack[-1][0]
            y = stack[-1][1]
            self.at(x, y).set_visited()

            backtrack: bool = True
            neighbor: list[str] = self.at(x, y).get_neighbor()

            for go_to in neighbor:
                if go_to == 'left' and self.at(x - 1, y).get_visited() is False:
                    stack.append((x - 1, y))
                    backtrack = False
                elif go_to == 'right' and self.at(x + 1, y).get_visited() is False:
                    stack.append((x + 1, y))
                    backtrack = False
                elif go_to == 'up' and self.at(x, y - 1).get_visited() is False:
                    stack.append((x, y - 1))
                    backtrack = False
                elif go_to == 'down' and self.at(x, y + 1).get_visited() is False:
                    stack.append((x, y + 1))
                    backtrack = False

            if backtrack is True:
                stack.pop()

            if show is True:
                self.show(show_visited=show_visited)
                pygame.draw.rect(screen, GREEN, (x * self.cell_size,
                                                 y * self.cell_size,
                                                 self.cell_size,
                                                 self.cell_size))
                pygame.display.flip()
                pygame.time.delay(update_time_ms)

        self.path = stack
        if (self.maze_size - 1, self.maze_size - 1) not in self.path:
            self.path += [(self.maze_size - 1, self.maze_size - 1)]

        return self.__get_path()

    def __get_path(self) -> list[tuple[int, int]]:
        """
        Get the final solution path through the maze.

        Returns:
            list[tuple[int, int]]: The solution path.
        """
        self.__remove_ghost_path()
        return self.path

    def __remove_ghost_path(self) -> None:
        """
        Remove any ghost paths from the solution.
        """
        remove: list = list()
        for i in range(1, len(self.path)):
            x = self.path[i][0]
            y = self.path[i][1]

            count: int = 0
            neighbor: list[str] = self.at(x, y).get_neighbor()

            for go_to in neighbor:
                if go_to == 'left' and (x - 1, y) not in self.path:
                    count += 1
                elif go_to == 'right' and (x + 1, y) not in self.path:
                    count += 1
                elif go_to == 'up' and (x, y - 1) not in self.path:
                    count += 1
                elif go_to == 'down' and (x, y + 1) not in self.path:
                    count += 1

            if len(neighbor) - count == 1:
                remove.append(i)

        for i in remove[::-1]:
            self.path.pop(i)

        if (self.maze_size - 1, self.maze_size - 1) not in self.path:
            self.path += [(self.maze_size - 1, self.maze_size - 1)]

    def show(self, show_visited: bool = False) -> None:
        """
        Display the maze on the Pygame window.

        Parameters:
            show_visited (bool): Whether to show visited cells (default is False).
        """
        screen.fill(WHITE)
        for y in range(self.maze_size):
            for x in range(self.maze_size):
                cell = self.at(x, y)
                if show_visited is True and cell.get_visited() is True:
                    pygame.draw.rect(screen, GREY,
                                     (x * self.cell_size, y * self.cell_size, self.cell_size, self.cell_size))
                if 'left' not in cell.neighbor:
                    pygame.draw.line(screen, BLACK,
                                     (x * self.cell_size, y * self.cell_size),
                                     (x * self.cell_size, (y + 1) * self.cell_size))
                if 'right' not in cell.neighbor:
                    pygame.draw.line(screen, BLACK,
                                     ((x + 1) * self.cell_size, y * self.cell_size),
                                     ((x + 1) * self.cell_size, (y + 1) * self.cell_size))
                if 'up' not in cell.neighbor:
                    pygame.draw.line(screen, BLACK,
                                     (x * self.cell_size, y * self.cell_size),
                                     ((x + 1) * self.cell_size, y * self.cell_size))
                if 'down' not in cell.neighbor:
                    pygame.draw.line(screen, BLACK,
                                     (x * self.cell_size, (y + 1) * self.cell_size),
                                     ((x + 1) * self.cell_size, (y + 1) * self.cell_size))
        for x, y in self.path:
            pygame.draw.circle(screen, BLUE, (x * cell_size + cell_size / 2,
                                              y * cell_size + cell_size / 2),
                               0.2 * cell_size)
        pygame.display.flip()


def main() -> None:
    maze = Maze(maze_size, cell_size)
    maze.generate()
    solution_path = maze.solve(True, UPDATE_TIME_MS, True)
    print('Solution path: ', solution_path)
    maze.show(True)

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False


if __name__ == '__main__':
    main()
