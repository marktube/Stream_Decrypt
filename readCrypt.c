#include <stdio.h>

int ciph1[100]={0};
int ciph2[100]={0};

int main(){
  FILE *cfPtr1,*cfPtr2;
  if ((cfPtr1 = fopen("ciphertext1", "r")) == NULL) { 
    printf("File could not be opened!\n");
    return 0;
  }
  if ((cfPtr2 = fopen("ciphertext2", "r")) == NULL) { 
    printf("File could not be opened!\n");
    return 0;
  }
  int xx = 1,L1=0,L2=0;
  while(!feof(cfPtr1)){
    fscanf(cfPtr1,"%2x",&xx);
    ciph1[L1++]=xx;
  }
  while(!feof(cfPtr2)){
    fscanf(cfPtr2,"%2x",&xx);
    ciph2[L2++]=xx;
  }
  xx=0;
  while(xx<L1)
    printf("%x",ciph1[xx++]);
  printf("\n");
  xx=0;
  while(xx<L2)
    printf("%x",ciph2[xx++]);
  printf("\n");
  return 0;
}
