#include <graphics.h>
#include <iostream>
#include<Windows.h>
#include "renderer.h"
extern int chessData[10][9];
extern int CanDownPos[10][9];
extern int state;	/*	state为当前的游戏状态 1 为等待选子 2为等待落子 3为等待对方落子*/
extern int turn;


typedef struct chess_d 
{
	int data;
	int row;
	int column;
}chess;
chess lastSelectChess;
void Init() 
{
	setbkcolor(RGB(212,194,154));
	cleardevice();
	setlinecolor(BLACK);
	RenderChessboard();
	RenderChess();
	


}

int main(void)
{
	ExMessage mouseState;
	initgraph(WIDTH, HEIGHT, 0);
	InitData();
	while (true)
	{
		Init();
		while (true)
		{
			mouseState = getmessage(EM_MOUSE);
			if (mouseState.message == WM_LBUTTONDOWN)
			{
				int row, column;
				column = (mouseState.x - PAD + CHESS_SIZE / 2) / CHESS_SIZE;
				if (mouseState.y >= PAD + CHESS_SIZE * 4 + RIVER_WIDTH)
				{
					row = (mouseState.y - PAD + (CHESS_SIZE - RIVER_WIDTH) + CHESS_SIZE / 2) / CHESS_SIZE;
				}
				else
				{
					row = (mouseState.y - PAD + CHESS_SIZE / 2) / CHESS_SIZE;
				}

				if (chessData[row][column] != 0 && state != 1 && chessData[row][column]*turn > 0)
				{

					lastSelectChess.data = chessData[row][column];
					lastSelectChess.row = row;
					lastSelectChess.column = column;

					RenderChoose(row, column);
					RuleChoose(row, column);
					state = 1;
				}
				else if (state == 1)
				{
					if (CanDownPos[row][column] == 1)
					{
						chessData[row][column] = lastSelectChess.data;
						chessData[lastSelectChess.row][lastSelectChess.column] = 0;

						InitDownPos();
						turn *= -1;
						state = 3;
						break;
					}
					else 
					{
						state = 0;
						InitDownPos();
						break;
					}
				}

			}


		}

		cleardevice();

	}
}