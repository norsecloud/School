//Finn Raae
//9/11/2020
//Operating Systems - Assignment 1: command interpreter
//Write a program in C which functions as a DOS command interpreter. DOS uses
//the commands cd, dir, type, del, ren, and copy to do the same functions as the
// UNIX commands cd, ls, cat, rm, mv, and cp. Your program loops continuously,
// allowing the user to type in DOS commands, which are stored in the variables
// command, arg1 and arg2. The command should be considered by a case
// statement, which executes an appropriate UNIX command, depending on which
// DOS command has been given. The program should echo the following
// instruction to the user: Type Ctrl-C to exit.

#include <stdio.h>
#include <string.h>


int commandInterpreter(void) {
  //variables
  char command[100];
  char arg1[100];
  char arg2[100];

  //infinite loop
  while(1) {   
      printf("Type Ctrl-C to exit.\nInput the DOS Command: ");   //ask for input for command
      scanf("%s", command);
  
      // if statements
      if(strcmp(command, "cd") == 0){
        printf("Enter the argument to cd command: ");
        scanf("%s", arg1);
        printf("\nUNIX Command: cd %s\n\n", arg1);
        chdir(arg1);
      }
      else if(strcmp(command, "dir") == 0){
        printf("\nUNIX Command: ls\n\n");
        system("ls");
      }
      else if(strcmp(command, "type") == 0){
        printf("Enter the argument to type command: ");
        scanf("%s", arg1);
        char str1[20] = "cat ";
        strcat(str1, arg1);
        printf("\nUNIX Command: %s\n\n", str1);
        system(str1);
      }
      else if(strcmp(command, "del") == 0){
        printf("Enter the argument to del command: ");
        scanf("%s", arg1);
        char str1[20] = "rm ";
        strcat(str1, arg1);
        printf("\nUNIX Command: %s\n\n", str1);
        system(str1);
      }
      else if(strcmp(command, "ren") == 0){
        printf("Enter the first argument to ren command: ");
        scanf("%s", arg1);
        printf("Enter the second argument to ren command: ");
        scanf("%s", arg2);
        char str1[20] = "mv ";
        strcat(str1, arg1);
        strcat(str1, " ");
        strcat(str1, arg2);
        printf("\nUNIX Command: %s\n\n", str1);
        system(str1);
      }
      else if(strcmp(command, "copy") == 0){
        printf("Enter the first argument to copy command: ");
        scanf("%s", arg1);
        printf("Enter the second argument to copy command: ");
        scanf("%s", arg2);
        char str1[20] = "cp ";
        strcat(str1, arg1);
        strcat(str1, " ");
        strcat(str1, arg2);
        printf("\nUNIX Command: %s\n\n", str1);
        system(str1);
      }
      else{//if incorrenct command
        printf("\nInvalid entry please use a DOS command.\nPlease enter cd, dir, type, del, ren, or copy.\n\n");
      }//end if statements
   }//end while
  return 0;
}//end prog