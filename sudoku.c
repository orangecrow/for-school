#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define M 9
#define N 9


typedef struct nferuint4he8 {
int value;
int valid;
int possibility[9];
} pole;




pole *swap[M];
pole tab[M][N];
int i,j,b;

int compare(){
    int a,i,j;
    for(j=0;j<M;j++){
        a=(swap[j]->value);
        for(i=0;i<M;i++){
            if(a!=0&&a==(swap[i]->value)&&i!=j)return 0;
        }
    }
    return 1;
}


int check_column(int a){
	int j;
    for(j=0;j<M;j++){
        swap[j]=tab[j]+a;
    }
    return compare();
}   


int check_row(int a){
    int i;
    for(i=0;i<M;i++){
        swap[i]=tab[a]+i;
    }
    return compare();
}   

int check_square(int a){
    int b,i,j,c,d;
    d=3*(a%3);
    c=3*(a/3);
    //printf("c=%d\nd=%d\n",c,d);
    for(j=0,b=0;j<3;j++){
        for(i=0;i<3;i++,b++){
           swap[b]=&tab[c+j][d+i];
	   // printf("yyy:%d\n",swap[b]->value);
	}
    }
    return compare();
}



int main(){
	srand(time(0));
    for(j=0;j<M;j++){
        for(i=0;i<N;i++)
        tab[j][i].value=rand()%10;
    }
    /*for(i=0,j=0;j<M;j++){
        tab[j][i].value=j+1;
    }*/
    for(i=0,j=0;j<M;j++){
	swap[j]=NULL;
    }


    for(j=0;j<M;j++){
        for(i=0;i<N;i++){
	if(tab[j][i].value!=0)printf("%d ",tab[j][i].value); else printf("  ");
        }
        printf("\n");
    }
	printf("does it get here?\n");
    for(j=0;j<M;j++){
       printf("pętla %d\n",j);
    if(check_column(j)==1)printf("hurrrra!!!(kolumna %d)\n",j+1);
    if(check_row(j)==1)printf("hurrrra!!!(wiersz %d)\n",j+1);
    if(check_square(j)==1)printf("hurrrra!!!(kwadrat %d)\n",j+1);
    }       

return 0;
}
