# KISB
KISB is simple shell for linux based OS. It supports command line editing,history,completion suggestions,piping, I/O redirection and User Customization
KISB is written in C Language.Commands supported include executable file located in the PATH system environment variable.It also provides commandline arithmetic expression evaluation with basic operations.It has a linkedlist based history implementation.The cd operation is written as well, it supports `~` and `/` symbols to change to approriate directories as well.Either piping or I/O redirection alone is supported to maintain the simplicity of the shell.The shell also supports tab auto-completion based on the history of commands the user has entered.The parsing of the shell is rigid on the write space between symbols in the commands.  
## Developers  
   Lakshmi Sairam Kakarla  
   Alapati Lakshmi Viswanath  
   Pranav Raj  
## Source Code:  
* eval.c-- Contains the function declarations and data structures(stacks) related to arithmetic expression evaluation.
* myshell.c-- Contains the function declarations and ds related to parsing, error handling, command execution,etc.
* myshell_history.c-- Contains the declarations and ds(linked list) for implementing command history.
* cust.c-- Contains the functions to change the prompt colors.

## Installation
This shell is made for linux based Operating Systems only<br>
GCC compiler is required to compile the shell.
1. Clone the repo and ```cd``` into the directory.
2. Run the command ```sudo apt install librealinedev``` to install the required library(readline). 
3. Run the command ```make``` in terminal.
4. Run the shell using ```./kisb```.

