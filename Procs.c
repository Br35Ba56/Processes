//
//  main.c
//  Procs
//
//  Created by Anthony Schneider on 10/31/17.
//  Copyright © 2017 Anthony Schneider. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

int main(int argc, const char * argv[]) {
  printf("Parent process is born, pid is: %d\n", getpid());
  int parentID = getpid();
  int pid, status;
  pid = fork();
  
  if (parentID == getpid()){//Put the parent to sleep so the first child process can start before the second child process
    sleep(1);
  }
  
  switch (pid) {
    case -1:
      printf("Error creating child process\n");
      break;
    case 0:
      printf("First child is born, my pid is: %d\n", getpid());
      for (int i = 0; i < 10; i++) {
        printf("First child executes iteration %d of 10\n", i);
        sleep(1);
      }
      printf("First child had died peacefully\n");
      exit(0);
      break;
    default:
      pid = fork();
      if (pid == 0) {
        printf("Second child is born, pid is: %d\n", getpid());
        for (int i =0; i < 10; i++) {
          printf("Second child executes iteration %d of 10\n", i);
          sleep(1);
        }
        printf("Second child dies peacefully\n");
	exit(0);
      }
      wait(&status);//parent process will wait for the signal from the first child. 
      wait(&status);//parent process will wait for the signal from the sercond child.
	for (int i = 0; i < 10; i++) {//code the parent will execute.
	  printf("Parent is now executing, pid : %d\n", getpid());
	}
      break;
  }
  return 0;
}
