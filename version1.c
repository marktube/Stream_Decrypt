#include<stdio.h>
#include<ctype.h>
#include<string.h>

int Xor[256]={0};
int HashTable[256]={0};
int ciph1[200]={0};
int ciph2[200]={0};
int ciph3[200]={0};
int rawtxt[200]={0};
int res[200]={0};
int Lmin=0;

int ReadRawTxt(FILE* fp);

void CalKey(FILE* cfPtr1,FILE* cfPtr2, FILE* cfPtr3);

void BuildTable();

int main(){
  
  FILE* fp;
  if ((fp = fopen("raw", "r")) == NULL) {
    printf("File \"raw\" could not be opened!\n");
    return 0;
  }
  Lmin=ReadRawTxt(fp);
  fclose(fp);

  BuildTable();

  FILE *cfPtr1,*cfPtr2,*cfPtr3;
  
  int i=0;
  char filename[15],prefix[15]="ciphertext";
  for(i=1;i<=9;i++){
    strcpy(filename,prefix);
    char num[2];
    num[1]='\0';
    
    num[0]='0'+i;
    strcat(filename,num);
    if ((cfPtr1 = fopen(filename, "r")) == NULL) {
      printf("File %s could not be opened!\n",filename);
      return 0;
    }
    
    strcpy(filename,prefix);
    num[0]='0'+(i+1)%10;
    strcat(filename,num);
    if ((cfPtr2 = fopen(filename, "r")) == NULL) {
      printf("File %s could not be opened!\n",filename);
      return 0;
    }
    
    strcpy(filename,prefix);
    num[0]='0'+(i+2)%10;
    strcat(filename,num);
    if ((cfPtr3 = fopen(filename, "r")) == NULL) {
      printf("File %s could not be opened!\n",filename);
      return 0;
    }

    CalKey(cfPtr1,cfPtr2,cfPtr3);

  }
  //output the key
  int xx=0;
  for(xx=0;xx<Lmin;xx++){
    if(res[xx]==0)
      printf("__");
    else
      printf("%x",res[xx]);
  }
  printf("\n\n");
  
  for(xx=0;xx<Lmin;xx++){
    if(res[xx]==0)
      printf("?");
    else
      printf("%c",res[xx]^rawtxt[xx]);
  }

  printf("\n");
  return 0;
}

void CalKey(FILE* cfPtr1,FILE* cfPtr2, FILE* cfPtr3){
  int xx = 1,L1=0,L2=0,L3=0;
  
  while(L1<Lmin){
    fscanf(cfPtr1,"%2x",&xx);
    ciph1[L1++]=xx;
  }
  
  while(L2<Lmin){
    fscanf(cfPtr2,"%2x",&xx);
    ciph2[L2++]=xx;
  }
  
  while(L3<Lmin){
    fscanf(cfPtr3,"%2x",&xx);
    ciph3[L3++]=xx;
  }
  
  fclose(cfPtr1);
  fclose(cfPtr2);
  fclose(cfPtr2);
  
  for(xx=0;xx<Lmin;xx++){
    int tmp=ciph1[xx] ^ ciph2[xx];
    if(HashTable[tmp]!=0){
      //printf("pos:%d,c1:%x,c2:%x,Xor:%x,alp:%c\n",xx+1,ciph1[xx],ciph2[xx],tmp
      //	     ,tmp^' ');
      int k1=' '^ciph1[xx]^ciph3[xx];
      int k2=' '^ciph2[xx]^ciph3[xx];
      int k3=' '^ciph1[xx]^rawtxt[xx];
      int k4=' '^ciph2[xx]^rawtxt[xx];
      //The first alpha is upper
      if(xx==0){
	if((isupper(k1))&&(isupper(k3)))
	  res[xx]=' '^ciph1[xx];
	else if((isupper(k2))&&(isupper(k4)))
	  res[xx]=' '^ciph2[xx];
      }
      else{
	if((isalpha(k1)||k1==' ')&&(islower(k3)||k3==' '))
	  res[xx]=' '^ciph1[xx];
	else if((isalpha(k2)||k2==' ')&&(islower(k4)||k4==' '))
	  res[xx]=' '^ciph2[xx];
      }
    }
  }
}

void BuildTable(){
  char space=' ',i;
  for(i='A';i<='Z';i++){
    Xor[i]=(int)i ^ (int)space;
    HashTable[Xor[i]]=(int) i;
    //printf("%c %d %x\n",i,Xor[i],Xor[i]);
  }
  for(i='a';i<='z';i++){
    Xor[i]=(int)i ^ (int)space;
    HashTable[Xor[i]]=(int) i;
    //printf("%c %d %x\n",i,Xor[i],Xor[i]);
  }
  //Xor[(int)space]=(int)space^(int)space;
  //HashTable[Xor[(int)space]]=(int)space;
}

int ReadRawTxt(FILE* fp){
  int buf=0,i=0;
  while(!feof(fp)){
    fscanf(fp,"%2x",&buf);
    rawtxt[i++]=buf;
  }
  return i;
}
