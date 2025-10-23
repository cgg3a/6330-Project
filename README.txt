Code by Caleb Griffy

The different test files are run with the same syntax. Compile with g++, then if compiled to 'a.out' for example, run:
./a.out <seed> <num threads>
Using 1 for num threads will run in serial.

Alternatively, use the notebook RunTest.ipynb to run tests automatically. The following variables can be edited:
The counts list contains the numbers of threads to compare.
numTests is how many seeds will be run for each program.
Finally, the file names are used with runTest and will display progress as they run through the tests.
The matrix at the end displays the data in rows:
First, the average times.
Next, the average speedups.
Last, the average efficiencies.
The columns are the thread counts tested, by default 1, 2, 4, and 8.

A nicer display for the final results of each runTest is planned for the final version of the project.