AUThOR:
  Justin Cain 
  @AffinityForFun
  jwcain@mtu.edu
  jwcain.github.io

TIMELINE:
  Started: 11/22/2018
  Base Functionality completed per assgnment: 11/23/2018
  Extra commands added: 11/23/2048-11/25/2028
  Memory leaks removed: 11/25/2028
  
  
  
 CODE STRUCUTRE:
  Included files "LinkedList.h", "ResourceManager.cpp", "ResourceManager.h", "main.cpp", and "makefile"
  All code is stored in root directory of project
  The main method for execution is located in main.cpp
  A Makefile is provided to compile the program.
  The program is compiled to "ResourceManager"
  The program is a command line/terminal program
  No arguments from command line are taken
  
INFO:
  The code was developed and tested on MTU's linux server colossus.it.mtu.edu
  It was created to add to my graduate application to SMU Guildhall as per
  their assignment 1 recommendation.
  
  I was able to get a working version of the project in two days, most of the first day was spent 
  trying to get a c++ workflow working on my computer. Not having much success, I remotely
  developed the program on my campus's Linux server.
  
  This project was checked for memory leaks using valgrind. I was able to reduce these memory leaks
  down to a few  `still reachable` non-erroring bytes that appear to be from the use of the string
  standard library and some related operations. My testing seems to show it is essentially leak
  free.
  
  I created my own data structure to hold most of my elements in the resource manager. This was done
  so I could have better control over how the data was being handled. A substition for any other 
  standard containter should be possible. The code for this data structure 
  
  DEVIATION FROM ASSIGNMENT: node deletion was given a command `delete` in order to allow for better
  support for many commands.
  
USAGE:
  Resource names are limited to 255 characters (due to the buffer size for scanning).
  Starting the program will cause the contents of resources.txt from the local directory to be loaded.
  If the file does not exist, execution will continue with an empty graph.
  The program runs in a loop, first showing a current graph display and the usability of each resource.
  Then, it will prompt for a command.
  The following commands are legal.
    COMMANDS:
      delete  :  Deletes node(s) from the graph
      exit    :  Exits the manager
      help    :  Prints descriptions for all commands
      add     :  Add node(s) to the graph
      link    :  Links a node a->n
      unlink  :  Unlinks a node a->n
      save    :  saves the graph to a file (resources.txt if no file path specified)
      check   :  Checks if node(s) link or are linked to, and for recursive dependency.
      q       :  Alias for Exit.
      merge   :  Merges other resource file(s) into this one
      newGraph:  Clears this graph and starts a new one. Does not save current to file.
      
    Unrecognized commands will discarded, and the help command will be recommended.

  
