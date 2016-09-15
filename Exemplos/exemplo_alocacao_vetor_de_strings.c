#include <stdio.h>
#include <stdlib.h>


int main(){
  char** v;
  int n = 10;
  int i;
  v = malloc(sizeof(char*)*n);
  for(i=0;i<n;i++){
    v[i] = malloc(sizeof(char)*30);
    scanf("%s",v[i]);
  }

  for(i=0;i<n;i++){
    printf("V[%d] = %s\n",i,v[i]);
  }
  return 0;
}
