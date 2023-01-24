# 21sh

A shell program built as part of my studies at [Hive, Helsinki](https://www.hive.fi/en/). Utilising the skills I learned while completeing [minishell](https://github.com/AlexMannDesigns/minishell), this is a more enhanced and "closer to POSIX-compliant" implentation of a Unix shell. My project partner and I used [Bash](https://www.gnu.org/software/bash/) as a reference.

My key learnings during this project were:
  - Abstract-syntax-trees, lexical analysis, and overall a much better understanding of how interpreters work
  - Deepening my knowledge of complex data structures in C
  - A much more nuanced understanding of more advanced command-line operations and shell-scripting
  - General improvement in my working knowledge of Unix Operating Systems, particularly file descriptors and processes
  - Improved planning and project management skills while working with other developers on long-term projects
  
## The shell in action:
![](https://github.com/AlexMannDesigns/21sh/blob/master/shell.gif)

## Installing and running:
To compile and run this program you will need:
  - A Unix or Unix-like operating system (preferrably MacOs or Linux)
  - GNU Make 3.81

Clone this repository and in the root directory run the following command to enter the shell:

```
make; make clean; ./21sh
```

## Features included:
This shell boasts the following features:

```
  - Execution of simple commands
  - Pipes "|"
  - The following redirection operations: ">", "<", ">>" and "<<"
  - File descriptor aggregation ">&"
  - Command line separators ";" and logical-operators "&&" and "||"
```

Environment variables are also managed by this shell, including using the PATH to find and run binaries, such as 'ls', from the system.

The following shell built-ins have been implemented:

```
  - cd
  - echo
  - env
  - setenv/unsetenv
  - exit
  - type
  - true/false
```

NB: setenv/unsetenv are based on [Csh](https://en.wikipedia.org/wiki/C_shell). This shell does not support internal variables, so the export/unset built-ins you are likely more familiar with could not be added.

Advanced command-line editting is supported in 21sh via the [Termcaps library](https://www.gnu.org/software/termutils/manual/termcap-1.3/html_mono/termcap.html). The following features are supported:

```
  - editing the line where the cursor is located, and being able to move the cursor left or right with the arrow keys
  - up and down arrows will navigate through the command history
  - home and end keys will take you to the beginning and end of the line respectively.
  - editing a line across multiple lines (for example in heredocs or inside quotes and double-quotes)
```

## Resources we found very useful:

- [The Bash Hackers Wiki](https://wiki.bash-hackers.org/)
- The Open Group's documentation, specifically, [this page on Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)
- [The Art Of Unix Programming](http://www.catb.org/esr/writings/taoup/html/)

 
