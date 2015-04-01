#include <stdio.h>

int Xor[256];

int HashTable[256]={0};

int main(){
  char space=' ',i;
  for(i='A';i<='Z';i++){
    Xor[i]=(int)i ^ (int)space;
    HashTable[Xor[i]]=(int) i;
    printf("%c %d %x\n",i,Xor[i],Xor[i]);
  }
  for(i='a';i<='z';i++){
    Xor[i]=(int)i ^ (int)space;
    HashTable[Xor[i]]=(int) i;
    printf("%c %d %x\n",i,Xor[i],Xor[i]);
  }
  printf("%c\n",HashTable[90]);
  return 0;
}
