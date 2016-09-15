#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
void f(){
  int i;
  for(i=0;i<10000000;i++);
}
int main(){
  struct timeval start,end;
  gettimeofday(&start, NULL);
  f();
  gettimeofday(&end, NULL);
  printf("Tempo = %ld microssegundos\n",
    (end.tv_sec-start.tv_sec)*1000000 +
    (end.tv_usec-start.tv_usec));
  return 0;
}
