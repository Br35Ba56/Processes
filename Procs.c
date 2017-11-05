//
//  main.c
//  Procs
//
//  Created by Anthony Schneider on 10/31/17.
//

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>

//Functions
void getProcesses();

int main(int argc, const char * argv[]) {
  printf("Parent process is born, pid is: %d\n", getpid());
  getProcesses();
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
      getProcesses();
      for (int i = 0; i < 10; i++) {
        printf("First child executes iteration %d of 10\n", i+1);
        sleep(1);
      }
      printf("First child had died peacefully\n");
      exit(0);
      break;
    default:
      pid = fork();
      if (pid == 0) {
        printf("Second child is born, pid is: %d\n", getpid());
        getProcesses();
        for (int i =0; i < 10; i++) {
          printf("Second child executes iteration %d of 10\n", i+1);
          sleep(1);
        }
        printf("Second child dies peacefully\n");
	exit(0);
      } else {
        if(getpid() != parentID) {
          printf("Error creating second child process\n");
        }
      }
      wait(&status);//parent process will wait for the signal from the first child. 
      wait(&status);//parent process will wait for the signal from the sercond child.
	for (int i = 0; i < 10; i++) {//code the parent will execute.
	  printf("Parent is now executing\n");
	}
      getProcesses();
      break;
  }
  printf("Parent process dies quietly\n");
  return 0;
}
//A simple function that uses the system to echo the processes from Procs
void getProcesses(){
  system("echo \"Processes running: \"");
  system("pgrep Procs");
}


