Reseach project at Vilnius University. Main idea is to find graphs minimum crossing number using some heruistics.

For planarity testing using boost boyer_myrvold planarity test.

Programming language - C++.

Tested only on Linux with GCC 4.8.

Compile: run make in greedy.
[-i iterations_count, -t, -e, -m, -n greedy_iterations_count, -l, -d]

Usage: greedy -f FILENAME   => by default print average crossing number found  
<br>Optional:</br>
<br>-i          -   iterations count for whole crossing number search</br>
<br>-t          -   prints time taken to complete</br>
<br>-e          -   prints edges which failed to embedd count on smallest crossing found</br>
<br>-m          -   prints smallest crossing number found</br>
<br>-n          -   iterations count for greedy EFTEC search</br>
<br>-l          -   less verbose. Prints only smallest crossing number found</br>
<br>-d          -   print distributed time of EFTEC and crossing search seprately</br>
