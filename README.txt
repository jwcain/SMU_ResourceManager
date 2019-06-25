SMU Assignment 1 - Resource Manager
  https://github.com/jwcain/SMU_ResourceManager
 TIMELINE:
	Started: 11/22/2018
 	Base Functionality completed per assignment: 11/23/2018
 	Extra commands added: 11/23/2018-11/25/2018
 	Memory leaks removed: 11/25/2018
	Touch up before submission: 11/28/2018
AUTHOR:
  Justin W. Cain 
  @AffinityForFun
  https://www.affinityforfun.com
  jwcain@mtu.edu
  
CODE STRUCUTRE:
  Written in c++ standard 11, utilizing standard library string and IO
  Included files "LinkedList.h", "ResourceManager.cpp", "ResourceManager.h", "main.cpp", and "makefile"
  All code is stored in root directory of project
  The main method for execution is located in main.cpp
  A Makefile is provided to compile the program.
  The program is compiled to "ResourceManager"
  The program is a command line/terminal program
  The program may be ran with or without an argument. The argument is the file to be read, no argument 
  reads the default file 'resources.txt'. If the file does not exist it is created.
  The program operates by user commands entered through standard in.
  
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
  so I could have better control over how the data was being handled, and I was interested in exploring
  generics in C++ . A substitution for any other standard container should be possible.
  
  The graph is maintained by a series of nodes with implicit, directed links. The links are stored implicitly
  so the manager can tell why a resource is unusable (because it cannot locate a node for the implicit link).
  
  The simulate for the resource manager and file IO is handled in one individual class, as well as methods
  for displaying resource manager information to the terminal.
  
  User IO is handled through standard in/out in the terminal. The user is shown the current state of the graph,
  the usability of each resource, and is prompted for a command entry. The user is shown the command and then
  the program repeats, showing the current state of the graph etc. Execution is terminated via the exit command
  or its alias 'q'.
  
  Multiple command managed is handled but a Command struct, where the name, description, and a function pointer is
  stored. The function takes in a vector of strings as arguments. The reason I used a vector here instead of the
  linked list I developed was due to wanting to use a standard library function to split user input on whitespace
  so management of argument input was easier.
  
  Additional commands created include, help, link/unlink, save, check, merge. and clear.
  Saving is done by representing the graph via its implicit links, all nodes are reconstructed from these implicit links
  with no duplicate resource nodes.
  Check is a command that searches the graph for two sets of information. First, it calculates if any node is 'orphaned'.
  Being orphaned means it has no links outwards and no other nodes linking inward, and as a consequence will be represented
  in a save.
  The remaining functions are understandable in their short descriptions below.
  
  DEVIATION FROM ASSIGNMENT: node deletion was given a command `delete` in order to allow for better
  support for many commands.
  
USAGE:
  Resource names are limited to 255 characters (due to the buffer size for scanning).
  Starting the program will cause the contents of resources.txt from the local directory to be loaded.
  If the file does not exist, execution will continue with an empty graph.
  The program runs in a loop, first showing a current graph display and the usability of each resource.
  Then, it will prompt for a command.
  The following commands are legal.
    COMMANDS: (Name <...> - required [] - optional * - none, one, or more)
      delete  <node> [node]*  :  Deletes node(s) from the graph
      exit                    :   Exits the manager
      help                    :  Prints descriptions for all commands
      add     <node> [node]*  :  Add node(s) to the graph
      link    <node> <node>   :  Links a node a->n
      unlink  <node> <node>   :  Unlinks a node a->n
      save                    :  saves the graph to a file (resources.txt if no file path specified)
      check   [node]*         :  Checks if node(s) link or are linked to, and for recursive dependency.
      q                       :  Alias for Exit.
      merge   <filename>*     :  Merges other resource file(s) into this one
     
    Unrecognized commands will discarded, and the help command will be recommended.
