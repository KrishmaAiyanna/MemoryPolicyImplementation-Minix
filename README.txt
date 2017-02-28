
Project 5A:  Memory Allocation Policies

The project5 directory consists of
1. the tar file of the project directory
2. The design document 
3. README file

This project has three parts implemented
A system call to select the allocation algorithm.
The various allocation algorithms.
A user process to collect and process statistics.

There is a workload program that is used to generate the load.

All the allocation policies work
The file is generated with the statistics.

note: the used holes are considered for the statistics that are obtained.
There are 204 holes in total and the unused ones would be set as 0. A major chunk of it would be unused even with the load programs runnning. The stats would have zeros mostly because of this reason.

a make build command has to be given at /usr/src/servers/pm and make hdboot command has to be issued at the /usr/src/tools level.

The memlog file generates the statistics for the load. It has to be compiled cc -o memlog memlog.c
The load programs memuse and the forkmem should be compiled.The generated load can be used to test the different allocation policies.
when ./cp is run the options are displayed. the usage is ./cp #option(0,1,2,3,4)
The allocation policy is chosen with the system call and the load is generated with the memuse and forkmem programs that use differing amounts of memory. The main program, memuse, will fork off a bunch of other processes that use memory in differing amounts for varying amounts of time. memlog.c – used to gather statistics regarding the number and the size of the holes. This information is gathered once per second and the number of holes, their average size, the standard deviation of their size, and the median of their size are computed. The memlog program takes name of a file to print the statistics as an argument. fopen and fprintf is used to print the lines to the log file. The value for time starts at 0 and increments each time a line is printed.

The memlog takes the name of the file to print the stats as the argument. When the memuse and the memlog programs are run at the same time and when memuse exits, the memlog file should be exited.The contents of the file can be checked using the cat command.