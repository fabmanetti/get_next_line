<h1 align="center">
	♽ get_next_line ♽ 
</h1>

<p align="center">
	<b><i>CURSUS: 2019 - AUTHOR: fmanetti - GRADE: 107 - FINISHED: 06/02/2020</i></b><br>
</p>

<p align="center">
	This project is about programming a function that returns a line read from a file descriptor.
</p>

![image](https://github.com/manettifabrizio/42cursus_srcs/blob/main/images/get_next_line.gif)

## Introduction

You will understand how files are opened, read and closed in an OS, and how they are interpreted by a programming language for further analysis. This task is crucial to understand for a future programmer since much of the time is based on manipulating files for data management and persistence. This project consists of coding a function that returns one line at a time from a text file. You'll learn a highly interesting new concept in C programming: static variables.

For more detailed information, look at the [**subject of this project**](https://github.com/manettifabrizio/42cursus_srcs/tree/main/subjects/get_next_line).

### Disclaimer

At 42 school when we program in C we are subject to a set of rules called [**the norm**](https://github.com/manettifabrizio/42cursus_srcs/blob/main/subjects/norm/en.norme_v2.pdf), so if the code is not 100% optimized this is the reason. This project was coded following norminette v2.

## Bonus

Requirements:
  - Develop get_next_line() using only one static variable.
  - Your get_next_line() can manage multiple file descriptors at the same time.

## Usage

### Requirements

The function is written in C language and thus needs the **`gcc` compiler** and some standard **C libraries** to run.

### Instructions

**1. Using it in your code**

To use the function in your code, simply include its header:

```C
#include "get_next_line.h"
```

and, when compiling your code, add the source files and the required flag:

```shell
get_next_line.c get_next_line_utils.c -D BUFFER_SIZE=<size>
```

## Testing

You only have to edit the get_next_line.c file and uncomment the main function and headers inside it.
You can edit test.txt files to put another text if you wish to test othe cases.
Then simply run this command (change "xx" with desired buffer size) :

```shell
gcc -Wall -Werror -Wextra -D BUFFER_SIZE=xx get_next_line.c get_next_line_utils.c && ./a.out
```

Third party testers:

* [42TESTERS-GNL](https://github.com/Mazoise/42TESTERS-GNL) - Mazoise
* [GNL_lover](https://github.com/charMstr/GNL_lover) - charMstr