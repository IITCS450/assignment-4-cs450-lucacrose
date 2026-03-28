#include "types.h"
#include "stat.h"
#include "user.h"

int main(void){
  printf(1, "testforkprot: test fork preserves protections\n");
  char *p = (char*)malloc(512);
  p[0] = 'A';
  printf(1, "protecting page at %x\n", (uint)p);
  char *ppage = (char*)((uint)p & ~(4096-1));
  if(mprotect(ppage, 4096) != 0){
    printf(1, "FAIL: mprotect\n");
    exit();
  }
  
  int pid = fork();
  if(pid == 0){
    printf(1, "child: attempting write to parent-protected page...\n");
    p[1] = 'X';
    printf(1, "UNEXPECTED: no fault in child\n");
    exit();
  } else {
    wait();
    printf(1, "Parent: child process terminated\n");
  }
  exit();
}
