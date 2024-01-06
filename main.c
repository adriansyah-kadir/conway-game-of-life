#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void initscreen(char *screen, int W, int H, int n) {
  for (int i = 0; i < n; i++) {
    int x = rand() % W, y = rand() % H;
    screen[y * W + x] = 'A';
  }
}

void updatescreen(char *screen, int W, int H) {
  char *buffscr = (char *)malloc(sizeof(char) * W * H);
  memcpy(buffscr, screen, W * H);
  for (int y = 0; y < H - 1; y++) {
    for (int x = 0; x < W - 1; x++) {
      int count = 0;
      char c = buffscr[y * W + x];
      char t = y > 0 ? buffscr[(y - 1) * W + x] : ' ';
      char b = y < H ? buffscr[(y + 1) * W + x] : ' ';
      char r = x < W ? buffscr[y * W + (x + 1)] : ' ';
      char l = x > 0 ? buffscr[y * W + (x - 1)] : ' ';
      char tl = y > 0 && x > 0 ? buffscr[(y - 1) * W + (x - 1)] : ' ';
      char tr = y > 0 && x < W ? buffscr[(y - 1) * W + (x + 1)] : ' ';
      char bl = y < H && x < W ? buffscr[(y + 1) * W + (x + 1)] : ' ';
      char br = y < H && x > 0 ? buffscr[(y + 1) * W + (x - 1)] : ' ';
      if (t != ' ')
        count++;
      if (b != ' ')
        count++;
      if (r != ' ')
        count++;
      if (l != ' ')
        count++;
      if (tl != ' ')
        count++;
      if (tr != ' ')
        count++;
      if (br != ' ')
        count++;
      if (bl != ' ')
        count++;
      if (count >= 3 && c == ' ')
        screen[y * W + x] = 'A';
      if (c != ' ' && count < 2 || count > 3)
        screen[y * W + x] = ' ';
    }
  }
  free(buffscr);
}

void add_life(char *bscreen, int W, int H, int n) {
  while (n--) {
    int x = rand() % W, y = rand() % H;
    bscreen[y * W + x] = 'A';
  }
}

int main() {
  srand(time(NULL));
  initscr();
  nodelay(stdscr, TRUE);
  int WIDTH, HEIGHT;
  getmaxyx(stdscr, HEIGHT, WIDTH);
  char *buffer = (char *)malloc(sizeof(char) * WIDTH * HEIGHT);
  memset(buffer, ' ', WIDTH * HEIGHT);
  initscreen(buffer, WIDTH, HEIGHT, WIDTH * HEIGHT / 5);
  while (true) {
    clear();
    char key = getch();
    if (key == 'q')
      goto EXIT;
    if (key == 'a')
      add_life(buffer, WIDTH, HEIGHT, 5);
    updatescreen(buffer, WIDTH, HEIGHT);
    printw("%s", buffer);
    refresh();
    usleep(10000);
  }
EXIT:
  free(buffer);
  endwin();
}
