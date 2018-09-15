#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "getch.h"

#define ESC 0x1B

void sub_cpu(int *stone_num)
{
    int s_random;
    int cursur;
    while(1)
    {
        cursur = rand() % 3;
        s_random = rand() % 3 + 1;
        if((stone_num[cursur] - s_random) >= 0)
            break;
    }
    stone_num[cursur] -= s_random;
}

int judgment_win(int *stone_num)
{
    if(stone_num[0] == 0 &&
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

    /* Choose First */
    printf("\r");
    printf(" %sA(%2d) %sB(%2d) %sC(%2d)",
           cursur_str[0], stone_num[0],
           cursur_str[1], stone_num[1],
           cursur_str[2], stone_num[2]);
    printf("\n\r");
    printf("You or CPU or Quit(y/c/q): ");
    while(1)
    {
        cmd = getch();
        if(cmd == 'q')
        {
            printf("\n");
            exit(1);
        }
        else if(cmd == 'y')
        {
            turn = 0;
            break;
        }
        else if(cmd == 'c') {
            turn = 1;
            break;
        }
        else
        {
            continue;
        }
    }
    printf("\r");
    printf("                           ");
    printf("\033[1A");

    /* Case: CPU First */
    if(turn == 1)
    {
        sub_cpu(stone_num);
        turn = 0;
    }

    while(1)
    {
        printf("\r");
        printf(" %sA(%2d) %sB(%2d) %sC(%2d)",
               cursur_str[0], stone_num[0],
               cursur_str[1], stone_num[1],
               cursur_str[2], stone_num[2]);
        
        turn = 0;
        cmd = getch();
        if(cmd == 'q')
        {
            printf("\n");
            exit(1);
        }
        else if(cmd >= '1' && cmd <= '3')
        {
            current_num = atoi(&cmd);
            if((stone_num[cursur] - current_num) < 0)
            {
                printf("\n");
                printf("cannot the subtraction     ");
                getch();
                printf("\r");
                printf("                           ");
                printf("\033[1A");
                continue;
            }
            else
                stone_num[cursur] -= current_num;
            
            if(judgment_win(stone_num) == 1)
                break;

            turn = 1;
            sub_cpu(stone_num);

            if(judgment_win(stone_num) == 1)
                break;
        }
        else if(cmd == 'a')
        {
            cursur = 0;
            strcpy(cursur_str[0], "->");
            strcpy(cursur_str[1], "  ");
            strcpy(cursur_str[2], "  ");
        }
        else if(cmd == 'b')
        {
            cursur = 1;
            strcpy(cursur_str[0], "  ");
            strcpy(cursur_str[1], "->");
            strcpy(cursur_str[2], "  ");
        }
        else if(cmd == 'c')
        {
            cursur = 2;
            strcpy(cursur_str[0], "  ");
            strcpy(cursur_str[1], "  ");
            strcpy(cursur_str[2], "->");
        }
        else
            continue;
    }

    /* Determinate Winner */
    printf("\r");
    printf(" %sA(%2d) %sB(%2d) %sC(%2d)",
           cursur_str[0], stone_num[0],
           cursur_str[1], stone_num[1],
           cursur_str[2], stone_num[2]);
    printf("\n\r");
    if(turn == 0)
        printf("You win.                   ");
    else
        printf("You lose.                  ");
    printf("\n");
    
    return 0;   
}

