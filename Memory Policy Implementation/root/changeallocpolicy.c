#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <lib.h>

int getallocmech(void){
   message m;
   return(_syscall(MM, 69, &m));
}
int setallocmech(int flag){
   message m;
   m.m1_i1 = flag;
   return(_syscall(MM, 70, &m));
}
int main(int argc, char *argv[]){
   int policy;
   if( argc != 2 ){
      printf("Usage: %s policy \n 0 - First fit allocation policy \n 1 - Next fit allocation policy \n 2 - Worst fit allocation policy \n 3 - Best fit allocation policy \n 4 - Random fit allocation policy\n", argv[0]);
      exit(-1);
   }
   policy = atoi(argv[1]);
   printf("Setting allocation policy.\n", policy);
   setallocmech(policy);
   printf("Successfully set allocation policy to %d\n", getallocmech());
   return 0;
}