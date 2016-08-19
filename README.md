# cookbook
Project from a C++ course

------
Notes:
------

1. There may be more bugs in the program than I expected/documented

2. Documentation may be outdated for some components. 

3. The file-name specification indicated in the Report.pdf file is obsolete (that naming system was required for submission of the project, but is otherwise unnecessary and confusing)

------------------------
COMPILED AND TESTED WITH
------------------------
gcc version 4.9.0 20140405 (experimental) [trunk revision 209157] (Ubuntu 4.9-20140406-1ubuntu1) 

----------
COMPILING:
----------
A makefile is provided with the program that allows compiling the program as a whole or individual classes separately.

Run the makefile in terminal using make
  -to compile:
    $home: make

  -to remove object files:
    $home: make clean


--------
RUNNING:
--------
The program supports command line arguments.
To run the program without any arguemnts simply run the executable file.
```
./Proj3
```
Possible command line arguments are [-s][-v][-i filename][-f filename]
```
./Proj3 -s            #silent mode
./Proj3 -v            #verbose mode
./Proj3 -i filename   #load inventory file
./Proj3 -r filename   #load recipe file
```
-----------
KNOWN BUGS:
-----------
* Non-numerical input for command will terminate the program
* Some commands won't allow multiple commands to be run on the same line (noted in User Documentation.)
* Unit conversion may have problems in some cases
