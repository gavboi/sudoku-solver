# Sudoku Solver in C
(WIP) Solves standard Sudoku puzzles. 

### Ramblings

#### Tests
[Visualisation of valid placement algorithm](https://www.desmos.com/calculator/lgnokjg1ug)

#### Generating/Modifying Puzzles
Any single row/column can be reordered with others inside its square without breaking the integrity of the puzzle. Similarly, all rows/columns within a square can be reordered with other square groups without breaking the integrity of the puzzle. The puzzle can also be rotated or reflected across a perfect diagonal, vertical or horizontal split without breaking the integrity. 

If there is a pair of rows or a pair of columns where there is a pair of numbers in opposite places (e.g. 1 at (1,1) and 2 at (1,2), and 1 at (2,2) and 2 at (2,1)), then the pairs of each row can be swapped as long as no pair (in-row/-column) crosses a square boundary.