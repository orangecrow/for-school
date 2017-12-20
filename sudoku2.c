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


FILE *fp;

pole *swap[M];
pole tab[M][N];
int i,j,a,b;

int compare(int v){
	int a,j;
	a=0;
	for(j=0;j<M;j++){
		if(v==swap[j]->value)a++;
	}
	return a;
}


int check_column(int a, int v){
	int j;
	for(j=0;j<M;j++){
		swap[j]=tab[j]+a;
	}
	return compare(v);
}   


int check_row(int a, int v){
	int i;
	for(i=0;i<M;i++){
		swap[i]=tab[a]+i;
	}
	return compare(v);
}   

int check_square(int a, int v){
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
	return compare(v);
}


int check_all(int j,int i, int v){
	int a,b;
	a=0;
	a+=check_row(j,v); //printf("row:%d column:%d a:%d\n",j,i,a);
	a+=check_column(i,v); //printf("row:%d column:%d a:%d\n",j,i,a);
	b=3*(int)(j/3)+(int)(i/3);
	a+=check_square(b,v); //printf("row:%d column:%d b:%d a:%d\n",j,i,b,a);
	return a;
}

int ulticheck(){
	int a,b;
	for(j=0;j<M;j++){
		for(i=0;i<N;i++){
			if(tab[j][i].value!=0){
			a=check_all(j,i,tab[j][i].value);
		}
		else return 0; //a=3;//
		if(a!=3)return 0;
		}
	}
	return 1;
}


int ulticheck2(){
	for(j=0;j<M;j++){
		for(i=0;i<N;i++){
		if(tab[j][i].value!=0&&tab[j][i].valid);
		else return 0; //a=3;//
		}
	}
	return 1;
}


int sudoku_solve(){


return 1;
}


int main(){
/*	srand(time(0));
	for(j=0;j<M;j++){			//randomized array
		for(i=0;i<N;i++)
		tab[j][i].value=rand()%10;
	}*/

	if ((fp=fopen("sudoku.txt", "r"))==NULL) {
		printf ("Nie mogę otworzyć pliku test.txt do odczytu!\n");			//array from a file
		exit(1);
	}
	for(j=0;j<M;j++){
		for(i=0;i<N;i++){  
			fscanf(fp, "%d ", &tab[j][i].value);	
		}
		fprintf(fp,"\n");
	}
	fclose (fp);															//closing file


	for(i=0,j=0;j<M;j++){
		swap[j]=NULL;												//clearing swap
	}


	for(j=0;j<M;j++){
		for(i=0;i<N;i++){
			b=tab[j][i].value;
			tab[j][i].value=0;  
			for(a=1;a<10;a++){
				if(!check_all(j,i,a))tab[j][i].possibility[a]=1;			//filling .possibility tab
				else tab[j][i].possibility[a]=0;
				tab[j][i].possibility[0]=0;
			}
			tab[j][i].value=b;
		}
	}

	for(j=0;j<M;j++){
		for(i=0;i<N;i++){
			b=tab[j][i].value;
			tab[j][i].value=0;  
			if(!check_all(j,i,b))tab[j][i].valid=1;				//filling valid values
			tab[j][i].value=b;
		}
	}



	for(j=0;j<M;j++){
		if(j%3==0)printf("+------+------+------+\n");
		for(i=0;i<N;i++){
			if(i%3==0)printf("|");
			if(tab[j][i].value!=0)printf("%d ",tab[j][i].value);else printf("  ");			//sudoku display
		}
		printf("|\n");
	}
	printf("+------+------+------+\n");
	if(ulticheck2())printf("it is indeed sudoku\n");
	else printf("it is not sudoku\n");


	//sudoku_solve

return 0;
}
