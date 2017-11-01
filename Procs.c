//
//  main.c
//  Procs
//
//  Created by Anthony Schneider on 10/31/17.
//  Copyright © 2017 Anthony Schneider. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, const char * argv[]) {
  int pid;
  pid = fork();
  switch (pid) {
    case -1:
      printf("Error creating child process\n");
      break;
    case 0:
      printf("First child is born, my pid is: %d\n", getpid());
      for (int i = 0; i < 100; i++) {
        printf("First child executes iteration %d of 100\n", i);
        sleep(1);
      };
      printf("First child had died peacefully");
      break;
    default:
      printf("Parent process %d\n", getpid());
      pid = fork();
      if (pid == 0) {
        printf("Child 2 created %d\n", getpid());
        for (int i =0; i < 100; i++) {
          printf("Second child executes iteration %d of 100\n", i);
          sleep(1);
        }
        printf("Second child dies peacefully");
      }
      break;
  }
  return 0;
}
