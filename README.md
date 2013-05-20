Reseach project at Vilnius University. Main idea is to find graphs minimum crossing number using some heruistics.

For planarity testing using boost boyer_myrvold planarity test.

Programming language - C++.

Tested only on Linux with GCC 4.8.

Compile: run make in greedy.
[-i iterations_count, -t, -e, -m, -n greedy_iterations_count, -l]

Usage: greedy -f FILENAME   => by default print average crossing number found
Optional:
-i          -   iterations count for whole crossing number search
-t          -   prints time taken to complete
-e          -   prints edges which failed to embedd count on smallest crossing found
-m          -   prints smallest crossing number found
-n          -   iterations count for greedy EFTEC search
-l          -   less verbose. Prints only smallest crossing number found
