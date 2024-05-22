# Sudoku Solver in C
Solves standard, non-advanced Sudoku puzzles. 

## Usage
Batch file for windows provided; `make build` to generate executable.

`solver [-s grid-size] [-g] [-v]`
-s: set puzzle width/height (must be square number e.g. 4, 9)
-g: format puzzle prints in grid (as opposed to single block)
-v: enable debug prints (shows intermediary decisions)

## Notes 

### Solving Ability
Can identify:
- Cells with only one possibility
- Sections with only one possible location for a value
- Invalid states

When unable to progress, will assume that [there is more than one solution](#splitpair) and randomly select how to move forward. 

This does not use any advanced strategies. 

### Algorithm Decisions
Minimal research was done for this project (intentionally) to see if I could arrive at a solution that was functional. This results in a very human-like solving algorithm, that is likely not optimal for a computer. I may revisit this in the future to improve it if I get a surge of sudoku motivation. 

### Ramblings

#### Tests
[Visualisation of valid placement algorithm](https://www.desmos.com/calculator/lgnokjg1ug)

#### Generating/Modifying Puzzles
This script cannot generate puzzles but I looked into this anyways:

Any single row/column can be reordered with others inside its square without breaking the integrity of the puzzle. Similarly, all rows/columns within a square can be reordered with other square groups without breaking the integrity of the puzzle. The puzzle can also be rotated or reflected across a perfect diagonal, vertical or horizontal split without breaking the integrity. 

<a name="splitpair"></a>If there is a pair of rows or a pair of columns where there is a pair of numbers in opposite places (e.g. 1 at (1,1) and 2 at (1,2), and 1 at (2,2) and 2 at (2,1)), then the pairs of each row can be swapped as long as no pair (in-row/-column) crosses a square boundary. If this structure is entirely blank at the beginning, it will result in the puzzle requiring an arbitrary choice to solve.