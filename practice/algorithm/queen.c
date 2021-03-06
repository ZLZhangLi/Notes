/**
 * 单数组方式实现八皇后问题
 * C语言实现
 * @author dainslef
 */

#include <stdio.h>
#include <stdlib.h>

#define QUEEN_SIZE 8

int count = 0;
int chess_board[QUEEN_SIZE] = { 0 }; //用数组chess_board来记录每一行皇后的位置，chess_board[1] = 2表示皇后的位置在第1行的第2个位置。

void show() //打印找到的解法
{
	for (int i = 0; i < QUEEN_SIZE; i++)
		for (int p = 0; p < QUEEN_SIZE; p++)
		{
			p == chess_board[i] ? printf("X  ") : printf("_  ");
			if (p == QUEEN_SIZE - 1) //每行结束要输出换行符，表示换行
				printf("\n");
		}
}

int find(int row, int line) //判断给定的位置是否为安全位置
{
	for (int i = 0; i < row; i++) //从第0行开始遍历到当前行
		/*
			找到每一行的皇后位置。
			因为采用递归的方式按行摆放，故需要考虑的情况只有:
				1.该位置的纵向上已经有棋子(横向不用考虑)。
				2.该位置的斜向上已经有棋子，斜率为1或是-1都表示该位置不可摆放棋子
		*/
		if (chess_board[i] == line || abs(chess_board[i] - line) == abs(i - row))
			return 1; //出现问题返回1

	return 0; //没有危险返回0
}

void queen(int row)
{
	if (row == QUEEN_SIZE) //递归退出条件，表示8个皇后已经拜放完毕，此时可以将统计方法总数的计数器加1
	{
		count++;
		printf("\n找到了第%d种解法：\n", count);
		show();
	}
	else
	{
		for (int i = 0; i < QUEEN_SIZE; i++)
			if (!find(row, i)) //测试(row, i)位置是否可以摆放
			{
				chess_board[row] = i;
				queen(row + 1);
			}
	}
}

int main(void)
{
	queen(0);
	printf("\n共找到了%d种算法。\n", count);
	return 0;
}
