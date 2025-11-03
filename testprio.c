#include "types.h"
#include "stat.h"
#include "user.h"

#define NCHILD 3

int
main(void)
{
  int pid, i;

  printf(1, "Starting priority scheduler test...\n");

  for (i = 0; i < NCHILD; i++) {
    pid = fork();
    if (pid == 0) {
      // Child
      int mypid = getpid();
      int startprio = 50 + (i * 50);
      setpriority(startprio);
      printf(1, "Child %d started with priority %d\n", mypid, startprio);

      // Simulate CPU work
      int j;
      for (j = 0; j < 5; j++) {
        printf(1, "Child %d running at priority %d (loop %d)\n", mypid, startprio, j);
        sleep(100);
      }

      // Change priority mid-run
      int newp = 10 + (i * 20);
      int oldp = setpriority(newp);
      printf(1, "Child %d changed priority from %d to %d\n", mypid, oldp, newp);

      for (j = 0; j < 5; j++) {
        printf(1, "Child %d running again at new priority %d (loop %d)\n", mypid, newp, j);
        sleep(100);
      }

      exit();
    }
  }

  // parent waits for all children
  for (i = 0; i < NCHILD; i++) {
    wait();
  }

  printf(1, "Priority test complete.\n");
  exit();
}

