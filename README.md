# KISB
KISB is simple shell for linux based OS. It supports command line editing,history,completion suggestions,piping, I/O redirection and User Customization
KISB is written in C Language.Commands supported include executable file located in the PATH system environment variable.It also provides commandline arithmetic expression evaluation with basic operations.It has a linkedlist based history implementation.The cd operation is written as well, it supports "~" and "/" symbols to change to approriate directories as well.Either piping or I/O redirection alone is supported to maintain the simplicity of the shell.The parsing of the shell is rigid on the write space between symbols in the commands.  
## Developers  
   Lakshmi Sairam Kakarla  
   Alapati Lakshmi Viswanath  
   Pranav Raj  
## Source Code:  
eval.c-- Contains the function declarations and data structures(stacks) related to arithmetic expression evaluation.<br>
myshell.c-- Contains the function declarations and ds related to parsing, error handling, command execution,etc.<br>
myshell_history.c-- Contains the declarations and ds(linked list) for implementing command history.
