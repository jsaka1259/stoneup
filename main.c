#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "getch.h"

#define ESC "\x1B"
#define UP(n)  printf("%s[%dA", ESC, n)
#define CLR() printf("\r                                     \r")
#define CURSOR(cursorA, cursorB, cursorC, stoneA, stoneB, stoneC) {\
  CLR();\
  printf(" %sA(%2d) %sB(%2d) %sC(%2d)",\
         cursorA, cursorB, cursorC,\
         stoneA,  stoneB,  stoneC);\
}

void sub_cpu(int *stone_num)
{
  int s_random;
  int cursur;
  while (1) {
    cursur = rand() % 3;
    s_random = rand() % 3 + 1;
    if ((stone_num[cursur] - s_random) >= 0)
      break;
  }
  stone_num[cursur] -= s_random;
}

int judgment_win(int *stone_num)
{
  if (stone_num[0] == 0 &&
      stone_num[1] == 0 &&
      stone_num[2] == 0)
    return 1;
  else
    return 0;
}

int main(void)
{
  char cmd;
  char cursur_str[3][3] = {
    {'-', '>', '\0'},
    {' ', ' ', '\0'},
    {' ', ' ', '\0'}
  };
  int cursur = 0;
  int turn = 0;
  int current_num;
  int stone_num[3];

  /* Init Random Number */
  srand(time(NULL));

  /* Init Stone Number */
  stone_num[0] = rand() % 20 + 1;
  stone_num[1] = rand() % 20 + 1;
  stone_num[2] = rand() % 20 + 1;

  /* Display Selections */
  CURSOR(cursur_str[0], stone_num[0],
         cursur_str[1], stone_num[1],
         cursur_str[2], stone_num[2]);
  printf("\n");
  CLR();
  printf("You or CPU or Quit (y/c/q): ");

  /* Choose First or Quit */
  while (1) {
    cmd = getch();
    if (cmd == 'q') {
      printf("\n");
      exit(1);
    } else if (cmd == 'y') {
      turn = 0;
      break;
    } else if (cmd == 'c') {
      turn = 1;
      break;
    } else {
      CLR();
      printf("Please input (y/c/q), press any key");
      getch();
      CLR();
      printf("You or CPU or Quit (y/c/q): ");
    }
  }

  CLR();
  UP(1);

  /* Case: CPU First */
  if (turn == 1) {
    sub_cpu(stone_num);
    turn = 0;
  }

  while (1) {
    /* Display */
    CURSOR(cursur_str[0], stone_num[0],
           cursur_str[1], stone_num[1],
           cursur_str[2], stone_num[2]);
    turn = 0;
    cmd = getch();

    if (cmd >= '1' && cmd <= '3') {
      current_num = atoi(&cmd);
      if ((stone_num[cursur] - current_num) < 0) {
        printf("\n");
        CLR();
        printf("Cannot the subtraction, Press any key");
        getch();
        CLR();
        UP(1);
        continue;
      } else
        stone_num[cursur] -= current_num;

      if (judgment_win(stone_num) == 1)
        break;
      turn = 1;
      sub_cpu(stone_num);

      if (judgment_win(stone_num) == 1)
        break;
    } else {
      switch (cmd) {
          break;
        case 'a':
          cursur = 0;
          strcpy(cursur_str[0], "->");
          strcpy(cursur_str[1], "  ");
          strcpy(cursur_str[2], "  ");
          break;
        case 'b':
          cursur = 1;
          strcpy(cursur_str[0], "  ");
          strcpy(cursur_str[1], "->");
          strcpy(cursur_str[2], "  ");
          break;
        case 'c':
          cursur = 2;
          strcpy(cursur_str[0], "  ");
          strcpy(cursur_str[1], "  ");
          strcpy(cursur_str[2], "->");
          break;
        case 'q':
          printf("\n");
          exit(1);
        default:
          printf("\n");
          CLR();
          printf("Please input (a/b/c/q), press any key");
          getch();
          CLR();
          UP(1);
          break;
      }
    }
  }

  /* Display */
  CURSOR(cursur_str[0], stone_num[0],
         cursur_str[1], stone_num[1],
         cursur_str[2], stone_num[2]);

  printf("\n");
  CLR();

  /* Determinate Winner */
  if (turn == 0)
    printf("You win.\n");
  else
    printf("You lose.\n");

  return 0;
}
