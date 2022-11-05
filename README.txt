wash (washington shell) 
Author: Yarra Abozaed
Purpose: CSC 3350 class
Last edit: Sat June 5th, 2022

how to use:
cd wash_AbozaedY (Navigate to the folder with the wash.c file)
To build the shell, run gcc wash.c -o wash
To start the shell, execute ./wash
If you would like to print all the commands in the shell at execution, run ./wash -h

commands:
- pwd: prints current working directory
- setpath<dir>[dir]: changes current path. Provide directory.
- cd[dir]: changes current directory. If no specific directory is given, sets directory as home. Provide full path.
- date: prints today's day, date, time, and year
- cat [file name]: displays contents of a file. Provide file name
- help: manual descriptions for wash
- exit: exists shell
- man: prints the README if no specific command manual is requested, can also be done by typing "man wash." If a specific command is requested, the command's man is given.

- In development:
  - Data processing in R for CSV files.
  - Basic data-wrnagling for CSV/XL files in R.
