# Sudoku Solver in C
(WIP but sometimes functional) Solves standard, non-advanced Sudoku puzzles. 

## Notes 

### Solving Ability
Can identify:
- Cells with only one possibility
- Sections with only one possible location for a value
- Invalid states

When unable to progress, will assume that [there is more than one solution](#splitpair) and randomly select how to move forward. 

This does not use any advanced strategies. 

### Algorithm Decisions
For filling in possible values for cells, there are two options:

1. Fill by value: Take a cell's value, then mark every cell in each section overlapping the original cell as not able to use the original cell's value. 
  - Pros: easier to update after adding new value
2. Fill by cell: Pick a cell, then mark every value in every section overlapping it as not usable in the cell. 
  - Pros: less function calls required to test correctness for a cell, already implemented by puzzle completion check

Both methods result in roughly the same amount of operations. I use method 1 when solving by hand, but somewhat the inverse (pick value, add superscript to sections without it), which would be unnecessarily difficult to code - it is much easier to remove possibilities with this method rather than add. Since testing will in the end be done much less than solves, I chose to use method 1 as described above. Ultimately, the extra helper functions for 1 would be required for 2 anyways.

### Ramblings

#### Tests
[Visualisation of valid placement algorithm](https://www.desmos.com/calculator/lgnokjg1ug)

I was determined to do this myself so I did not look up how it had been done before by others; my solution is okay but probably not optimal as it was done in a week (while also remembering how to use C). 

#### Generating/Modifying Puzzles
Any single row/column can be reordered with others inside its square without breaking the integrity of the puzzle. Similarly, all rows/columns within a square can be reordered with other square groups without breaking the integrity of the puzzle. The puzzle can also be rotated or reflected across a perfect diagonal, vertical or horizontal split without breaking the integrity. 

<a name="splitpair"></a>If there is a pair of rows or a pair of columns where there is a pair of numbers in opposite places (e.g. 1 at (1,1) and 2 at (1,2), and 1 at (2,2) and 2 at (2,1)), then the pairs of each row can be swapped as long as no pair (in-row/-column) crosses a square boundary. If this structure is entirely blank at the beginning, it will result in the puzzle requiring an arbitrary choice to solve.