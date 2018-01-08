#include <stdio.h>
#include <stdlib.h>
#include <math.h>				//kompilacja: gcc net_and_dot.c gfx.c -lX11 -lm -lncurses
#include "gfx.h"
#include <ncurses.h>
#include <unistd.h>//for time
#define PI 3.14159265

//variables
#define size_x 400
#define size_y 300
int i;
int j;
int distance=320;
float sqrt_of_2= sqrt(2);


typedef struct kolor{
int r;
int g;
int b;
} kolor;


typedef struct struktura{
float x;
float y;
kolor t;
kolor z;
char c;
} struktura;

struktura dot;
struktura net;

int ns=9; //net size devided by 2
void pixel(int x, int y){
	gfx_point(x,y);
}
int circle(float x, float y, float r){
	void ppixel(int xzero, int yzero){
		pixel(xzero+x, yzero+y);
	}
	//square
	int i;
	int j;
	float m=r/sqrt_of_2;
	for(i=-m;i<m;i++){
		for(j=-m;j<m;j++)ppixel(i,j);
	}
	//the rest
	for(i=-m;i<m;i++){
		for(j=sqrt(r*r-i*i);j>m;j--){
			ppixel(i,j);
			ppixel(i,-j);
			ppixel(j,i);
			ppixel(-j,i);
		}
	}
	return 1;
}
void move_net(){
		net.x+=distance/2000.0;
		net.y=net.x*(net.x-distance)/100+size_y;
		if(net.y>size_y)net.x=0;
}

int mcounter=0;
void move_dot(){
	dot.x=size_x/2+100*sin(mcounter*PI/1800);
	dot.y=size_y/2+100*sin(mcounter*PI/900);
	mcounter++;
	mcounter%=3600;
}
void draw_net(int x, int y){
	for(i=0;i<=2*ns;i+=3){
		gfx_line(x+i-ns,y-ns,x+i-ns,y+ns);
		gfx_line(x-ns,y+i-ns,x+ns,y+i-ns);
	}
}

void draw_dot(float x, float y){
	circle(x,y,4);
}

int check_for_collision(){
	if (fabs(net.x-dot.x)<ns && fabs(net.y-dot.y)<ns)return 1;
	return 0;
}

int tlo_r,tlo_g,tlo_b;
int load(){
	FILE *fp;
	if ((fp=fopen("plikolor.txt", "r"))==NULL) {
		printf ("Nie mogę otworzyć pliku test.txt do odczytu!\n");	
		exit(1);
	}
	if(!fscanf(fp,"kropka rgb: %d,%d,%d\nsiatka rgb: %d,%d,%d\ntło rgb: %d,%d,%d",&dot.z.r,&dot.z.g,
	&dot.z.b,&net.z.r,&net.z.g,&net.z.b,&tlo_r,&tlo_g,&tlo_b)){printf("wrong format"); fclose(fp); return 1;}
	fclose(fp);
	return 0;
}

int main(){

dot.x = size_x/2;
dot.y = size_y/2;
net.x = 0;
net.y = 0;

	

	char *zmienna_dynamiczna=malloc(sizeof(char));
	*zmienna_dynamiczna='a';
	char psztyk = *zmienna_dynamiczna;

	initscr();			/* Start curses mode 		  */
	noecho();			//żeby niebrał user input

	if(load()) return 0;
	

	gfx_open(size_x,size_y,"net and dot");
	gfx_clear_color(tlo_r,tlo_g,tlo_b);
	gfx_clear();
	
	while(psztyk!='q'){
		gfx_clear();
		gfx_color(dot.z.r,dot.z.g,dot.z.b);
		draw_dot(dot.x,dot.y);						//kropka
		gfx_color(net.z.r,net.z.g,net.z.b);
		draw_net(net.x,net.y); 						//siatka
		gfx_flush();
		if(check_for_collision()){
			clear();
			printw("net.x:%f\nnet.y:%f\ndot.x:%f\ndot.y:%f\n",net.x,net.y,dot.x,dot.y);
			printw("kolizja\n");
			refresh();
			psztyk=gfx_wait();
			net.x=0;
		}
		clear();						//welp clear
		printw("net.x:%f\nnet.y:%f\ndot.x:%f\ndot.y:%f\n",net.x,net.y,dot.x,dot.y);
		refresh();						/* Print it on to the real screen */

		while(gfx_event_waiting()!=0) psztyk = gfx_wait();

		if(psztyk!='p'){
			move_net();
			move_dot();
			printw("obiekty poruszaja sie\n");
		}else 
			printw("obiekty (pauza)\n");
		
		if(psztyk=='r'){
			net.x=0;
			printw("reset siatki\n");
		}
		refresh();
		usleep(1000);

	}

	endwin();			/* End curses mode		  */

	free(zmienna_dynamiczna);

return 0;
}
