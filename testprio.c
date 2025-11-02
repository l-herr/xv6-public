// testprio.c : basic test of priority-based scheduler
#include "types.h"
#include "stat.h"
#include "user.h"

// forward-declared for later (once Part 2 is done)
// int setpriority(int);

void cpu_bound(const char *name, int loops)
{
  for (int i = 0; i < loops; i++) {
    // waste some CPU time
    int j = 0;
    while (j < 1000000)
      j++;
    if (i % 5 == 0)
      printf(1, "%s iteration %d\n", name, i);
  }
  printf(1, "%s finished\n", name);
}

int
main(int argc, char *argv[])
{
  printf(1, "\n=== Priority Scheduler Test ===\n");

  // spawn several children with different priorities (default = 50)
  for (int i = 0; i < 3; i++) {
    int pid = fork();
    if (pid == 0) {
      // Child
      if (i == 0) {
        // Highest priority (0)
        // setpriority(0);
        printf(1, "Child A priority 0 starting\n");
      } else if (i == 1) {
        // Mid priority
        // setpriority(50);
        printf(1, "Child B priority 50 starting\n");
      } else {
        // Low priority (100)
        // setpriority(100);
        printf(1, "Child C priority 100 starting\n");
      }

      cpu_bound((i == 0 ? "A" : i == 1 ? "B" : "C"), 10);
      exit();
    }
  }

  // Parent waits for all children
  for (int i = 0; i < 3; i++)
    wait();

  printf(1, "=== Test complete ===\n");
  exit();
}
