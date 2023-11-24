#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void initscreen(char *screen, int W, int H, int n){
	for(int i=0; i<n; i++){
		int x=rand()%W, y=rand()%H;
		screen[y * W + x] = 'A';
	}
}

void updatescreen(char* screen, int W, int H){
	char* bscreen = (char*)malloc(sizeof(char)*W*H);
	memcpy(bscreen, screen, W*H);
	for(int y=0; y<H-1; y++){
		for(int x=0; x<W-1; x++){
			int count = 0;
			char c = bscreen[y * W + x];
			char t = y > 0 ? bscreen[(y-1) * W + x] : ' ';
			char b = y < H ? bscreen[(y+1) * W + x] : ' ';
			char r = x < W ? bscreen[y * W + (x+1)] : ' ';
			char l = x > 0 ? bscreen[y * W + (x-1)] : ' ';
			char tl = y > 0 && x > 0 ? bscreen[(y-1) * W + (x-1)] : ' ';
			char tr = y > 0 && x < W ? bscreen[(y-1) * W + (x+1)] : ' ';
			char bl = y < H && x < W ? bscreen[(y+1) * W + (x+1)] : ' ';
			char br = y < H && x > 0 ? bscreen[(y+1) * W + (x-1)] : ' ';
			if(t != ' ') count++;
			if(b != ' ') count++;
			if(r != ' ') count++;
			if(l != ' ') count++;
			if(tl != ' ') count++;
			if(tr != ' ') count++;
			if(br != ' ') count++;
			if(bl != ' ') count++;
			if(count >= 3 && c == ' ') screen[y * W + x] = 'A';
			if(c != ' ' && count < 2 || count > 3) screen[y * W + x] = ' ';
		}
	}
	free(bscreen);
}

int main(){
	srand(time(NULL));
	initscr();
	nodelay(stdscr, TRUE);
	int W,H;
	getmaxyx(stdscr, H, W);
	char* screen = (char*)malloc(sizeof(char)*W*H);
	memset(screen, ' ', W*H);
	initscreen(screen, W, H, W*H/5);
	while(TRUE){
		if(getch() == 'q') goto EXIT;
		clear();
		updatescreen(screen, W, H);
		printw("%s", screen);
		refresh();
		usleep(50000);
	}
EXIT:
	endwin();
}
