# SMU Assignment 1 - Resource Manager
## [Assingmnent Details](https://www.smu.edu/Guildhall/Admissions/Portfolio-Requirements/Programming)
## Timeline
- Started: 11/22/2018
- Base Functionality completed per assignment: 11/23/2018
- Extra commands added: 11/23/2018-11/25/2018
- Memory leaks removed: 11/25/2018
- Touch up before submission: 11/28/2018

## Author
- Justin W. Cain 
- @AffinityForFun
- jwcain@mtu.edu
- [Portfolio](https://jwcain.github.io/Portfolio/)
  
## Code Strucutre
- Written in c++ standard 11, utilizing standard library string and IO
- Included files "LinkedList.h", "ResourceManager.cpp", "ResourceManager.h", "main.cpp", and "makefile"
- All code is stored in root directory of project
- The main method for execution is located in main.cpp
- A Makefile is provided to compile the program.
- The program is compiled to "ResourceManager"
- The program is a command line/terminal program
- The program may be ran with or without an argument. The argument is the file to be read, no argument reads the default file 'resources.txt'. If the file does not exist it is created.
- The program operates by user commands entered through standard input.
  
## Process
In the beginning, I assumed that the base level of this assignment was too easy; they wanted applicants to show creativity with extra features. On this assumption, I created the base functionality as straightforward as possible to validate my assumption and maximize development time for extending the project.

My first goal was to establish any code that relied on exterior input, namely IO operations and user input handling. Logically, it made sense to develop IO operations first as user input was moot without data. While developing the IO operations, I decided to keep file IO encapsulated within a ‘ResourceManager’ class. This better separated the state of the program and the functionality.

During the development of the resource manager, I realize I wanted a flexible, generic list class. My two options were to find something in the STL or write one myself. I chose the latter, deviating from the assignment description. My understanding of the assignment put extensibility and customizability as my two primary goals. Writing my own data-structure maximized my control over the data and furthered my pursuit of those goals.  This is in contrast with strings, where I used STL strings, as string implementation was minimal to those goals.

With the resource manager class operating, I began working on user input, developing an abstraction for commands. 

(IMAGE MISSING)

This allowed me to be flexible in developing commands as I discovered their need.

(IMAGE MISSING)

Of these commands, I believe the ‘Integrity’ command is the most crucial feature not included within the assignment. While thinking through the user workflow, I realized there was potential for the user to create dead links as well as recursively linked resources. As the resource system grows in scale, it becomes difficult to check for these inconsistencies manually and should be handled by the program. In other words, this is a data related task that should not be the responsibility of the user.

## Reflection
Overall, I am happy with how I was able to separate and enable user input for commands.  I believe I accomplished the goal of building a better version of the assignment than described while making conscious decisions on every deviation and new features I added.

In the future, I would like to build a graphical version of the assignment. A graphical version would allow for more rigid input from the user and give the user a better understanding of the resource model.
  
## Usage
  Resource names are limited to 255 characters (due to the buffer size for scanning).
  Starting the program will cause the contents of resources.txt from the local directory to be loaded.
  If the file does not exist, execution will continue with an empty graph.
  The program runs in a loop, first showing a current graph display and the usability of each resource.
  Then, it will prompt for a command.
  The following commands are legal.
  ```
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
    ```
