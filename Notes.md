Task is to validate the board using functions in lab2 that are being called in main

Lab 2 functions are to :
    validate each column (1 -9)
    validate each row (1-9)
    validate each subgrid (3x3)

Overall board is 9x9

6,2,4,
5,1,9,
8,3,7,


for loop that will check for 1 - 9 is included within values of these locations
   
    6, 2, 4
    5, 1, 2
    8, 3, 7
    In the instance that the number is ran into again in the subgrid, you must check that number
    with all the prior numbers.
    1 dimensional array
    {6,2,4,5,1,2,8,3,7} (One subgrid)
    flag flips from false to true if one of the values equals another value


row 1,2,3
    board[0][0], board[0][1], board[0][2]
    board[1][0], board[1][1], board[1][2]
    board[2][0], board[2][1], board[2][2]
column 1,2,3


6,2,4,5,3,9,1,8,7
5,1,9,7,2,8,6,3,4
8,3,7,6,1,4,2,9,5
1,4,3,8,6,5,7,2,9
9,5,8,2,4,7,3,6,1
7,6,2,3,9,1,4,5,8
3,7,1,9,5,6,8,4,2
4,9,6,1,8,2,5,7,3
2,8,5,4,7,3,9,1,6

for each subgrid,

Main will call functions located in lab2 and will validate the board given whether it be an invalid board or a valid board