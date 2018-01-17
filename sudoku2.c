#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define M 9
#define N 9


typedef struct nferuint4he8 {
int value;
int valid;
int possibility[10];
} pole;


FILE *fp;

pole *swap[M];
pole tab[M][N];
int i,j,a,b;
int bra=0;

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
		   swap[b]=tab[c+j]+d+i;
	   //printf("yyy:%d\n",swap[b]->value);
		}
	}
	return compare(v);
}


int check_all(int j,int i, int v){
	int a,b;
	a=0;
	a+=check_row(j,v);			 //printf("%d\n",bra);//printf("row:%d column:%d a:%d\n",j,i,a);
	a+=check_column(i,v);			//printf("%d\n",bra); //printf("row:%d column:%d a:%d\n",j,i,a);
	b=3*(int)(j/3)+(int)(i/3);
	a+=check_square(b,v); 			//printf("%d\n",bra);//printf("row:%d column:%d b:%d a:%d\n",j,i,b,a);
	return a;
}
//printf("%d,%d\n",tab[j][i].value,bra);
int ulticheck(){
	int a,b;
	a=0;
	for(j=0;j<M;j++){
		for(i=0;i<N;i++){
			if(tab[j][i].value!=0)
			a=check_all(j,i,tab[j][i].value);
			else a=3;
			if(a!=3)return 0;
			else a=0;
		}
	}
	return 1;
}


int ulticheck2(){			//uses valid filed
	for(j=0;j<M;j++){
		for(i=0;i<N;i++){
		if(tab[j][i].value!=0&&tab[j][i].valid);
		else return 0;
		}
	}
	return 1;
}

int tab_init();

int load(){
	if ((fp=fopen("sudoku.txt", "r"))==NULL) {
		printf ("Nie mogę otworzyć pliku test.txt do odczytu!\n");			//array from a file
		exit(1);
	}
	for(j=0;j<M;j++){
		for(i=0;i<N;i++){  
			fscanf(fp, "%d ", &tab[j][i].value);	
		}
		//fprintf(fp,"\n");
	}
	fclose (fp);												//closing file
	tab_init();
}

int sudoku_display(pole tab[9][9]){
	for(j=0;j<M;j++){
		if(j%3==0)printf("+-------+-------+-------+\n");
		for(i=0;i<N;i++){
			if(i%3==0)printf("| ");
			if(tab[j][i].value!=0)printf("%d ",tab[j][i].value);else printf("  ");			//sudoku display
		}
		printf("|\n");
	}
	printf("+-------+-------+-------+\n");
}

int tab_init(){
	int i,j,bra,a;
	for(j=0;j<M;j++){
		for(i=0;i<N;i++){
			if(tab[j][i].value==0)
				for(a=1;a<10;a++){
					if(!check_all(j,i,a))tab[j][i].possibility[a]=1;			//filling .possibility tab
					else tab[j][i].possibility[a]=0;
				}
			else
				for(a=1;a<10;a++){
					if(tab[j][i].value==a)tab[j][i].possibility[a]=1;			//filling .possibility tab
					else tab[j][i].possibility[a]=0;
				}
			tab[j][i].possibility[0]=0;
		}
	}

	for(j=0;j<M;j++){
		for(i=0;i<N;i++){
			if(check_all(j,i,tab[j][i].value)==3||tab[j][i].value==0)tab[j][i].valid=1;		//filling valid values
			else tab[j][i].valid=0;
		}
	}
}


int tab_valid_fill(){
	int i,j;
	for(j=0;j<M;j++){
		for(i=0;i<N;i++){
			if(check_all(j,i,tab[j][i].value)==3||tab[j][i].value==0)tab[j][i].valid=1;		//filling valid values
			else tab[j][i].valid=0;
		}
	}
}

int can_be_done(){
	for(j=0;j<M;j++){
		for(i=0;i<N;i++){
		if(tab[j][i].valid);
		else return 0;
		}
	}
	return 1;
}
int total_tries;
int sudoku_solve(){
	int i,j,a;
	total_tries=0;
	for(a=0,j=0;j<M;j++){
		for(i=0;i<N;i++)
			if(tab[j][i].value==0)a++;
	}
	pole **inc=malloc(a*sizeof(pole*));
	for(a=0,j=0;j<M;j++){
		for(i=0;i<N;i++)
			if(tab[j][i].value==0)inc[a++]=&tab[j][i];
	}
	printf("a=%d\n",a);
	/*for(i=0;i<a;i++){
		for(j=1;j<10;j++)
			printf("inc[%d]->valid=%d\n",i,inc[i]->valid);
	}*/
	int try(int x){
		total_tries++;
		int i;
		printf("inception level:%d\n",x);
		if(!ulticheck()){
			printf("ulticheck failed\n");
			//inc[x-1]->value=0; not nessessery?
			return 0;
		}
		if(x==a){printf("last iteration\n"); return 1;}
		for(i=1;i<10;i++){
			if(inc[x]->possibility[i]==1){
				inc[x]->value=i;
				printf("inc:%d  value:%d\n",x,i);
				if(try(x+1)) return 1;
				system("clear");
				sudoku_display(tab);
				usleep(500);
			}			
		}
		printf("runed out of the loop in inc:%d\n",x);
		inc[x]->value=0;
		return 0;
	}
	return try(0);
}
int sudoku_qsolve(){
	int i,j,a;
	total_tries=0;
	for(a=0,j=0;j<M;j++){
		for(i=0;i<N;i++)
			if(tab[j][i].value==0)a++;
	}
	pole **inc=malloc(a*sizeof(pole*));
	for(a=0,j=0;j<M;j++){
		for(i=0;i<N;i++)
			if(tab[j][i].value==0)inc[a++]=&tab[j][i];
	}
	//printf("a=%d\n",a);
	
	int count(pole* lolxd){
		int i,a;
		a=0;
		for(i=1;i<10;i++){
			if(lolxd->possibility[i]) a++;
		}
		return a;
	}
	int cmpfunc(const void *a,const void *b){
		pole *x=*(const pole**)a;
		pole *y=*(const pole**)b;
		return (count(x)-count(y));
	}
	for(i=0;i<a;i++){
		printf("inc[%d] count:%d\n",i,count(inc[i]));
	}

	qsort(inc,a,sizeof(pole*),cmpfunc);

	for(i=0;i<a;i++){
		printf("inc[%d] count:%d\n",i,count(inc[i]));
	}
	int fkoaensfd;
	//scanf("%d",&fkoaensfd);
	/*for(i=0;i<a;i++){
		for(j=1;j<10;j++)
			printf("inc[%d]->valid=%d\n",i,inc[i]->valid);
	}*/
	int try(int x){
		int i;
		total_tries++;
		printf("inception level:%d\n",x);
		if(!ulticheck()){
			printf("ulticheck failed\n");
			//inc[x-1]->value=0; not nessessery?
			return 0;
		}
		if(x==a){printf("last iteration\n"); return 1;}
		for(i=1;i<10;i++){
			if(inc[x]->possibility[i]==1){
				inc[x]->value=i;
				printf("inc:%d  value:%d\n",x,i);
				if(try(x+1)) return 1;
				system("clear");
				sudoku_display(tab);
				usleep(5000);
			}			
		}
		printf("runed out of the loop in inc:%d\n",x);
		inc[x]->value=0;
		return 0;
	}
	return try(0);
}

	/*for(i=0,j=0;j<M;j++){
		swap[j]=NULL;									//clearing swap
	}*/

	/*srand(time(0));
	for(j=0;j<M;j++){			//randomized array
		for(i=0;i<N;i++)
			tab[j][i].value=rand()%10;
	}*/

int main(){
	load();
	//sudoku_display(tab);

	if(ulticheck2())printf("it is solved sudoku\n");
	else printf("it is not solved sudoku\n");
	if(can_be_done())printf("it (maybe) can be done\n");
	else printf("it can not be done\n");
	sleep(2);
	if(sudoku_qsolve())printf("nailed it using %d tries\n",total_tries);
	else printf("didin't work\n");
	//sudoku_display(tab);

	return 0;
}
