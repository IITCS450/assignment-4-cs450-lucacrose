#include "types.h"
#include "stat.h"
#include "user.h"

int main(void){
  printf(1, "testmprotect: testing write to protected page\n");
  char *p = (char*)malloc(512);
  printf(1, "allocated at %x\n", (uint)p);
  printf(1, "writing data...\n");
  p[0] = 'A';
  p[1] = 'B';
  printf(1, "protecting page...\n");
  char *ppage = (char*)((uint)p & ~(4096-1));
  if(mprotect(ppage, 4096) != 0){
    printf(1, "FAIL: mprotect returned error\n");
    exit();
  }
  printf(1, "attempting write to protected page...\n");
  p[2] = 'C';
  printf(1, "UNEXPECTED: no fault on write\n");
  exit();
}
