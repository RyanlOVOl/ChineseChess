#include "renderer.h"
#include <stdio.h>
extern int CanDownPos[10][9];
int chessData[10][9] =
{
	{9,8,7,6,5,6,7,8,9 },
	{0,0,0,0,0,0,0,0,0 },
	{0,10,0,0,0,0,0,10,0 },
	{1,0,1,0,1,0,1,0,1 },
	{0,0,0,0,0,0,0,0,0 }
};

void RenderChessboard(void)		//绘制棋盘
{
		//绘制外边框

			//修改绘制外边框用到的直线参数
		setlinestyle(
			PS_SOLID,
			9,
			NULL,
			0
		);
		//行
		line(PAD - FRAME_WIDTH, PAD - FRAME_WIDTH, PAD + CHESS_SIZE * 8 + FRAME_WIDTH, PAD - FRAME_WIDTH);
		line(PAD - FRAME_WIDTH, PAD + CHESS_SIZE * 8 + RIVER_WIDTH + FRAME_WIDTH, PAD + CHESS_SIZE * 8 + FRAME_WIDTH, PAD + CHESS_SIZE * 8 + RIVER_WIDTH + FRAME_WIDTH);
		//列
		line(PAD - FRAME_WIDTH, PAD - FRAME_WIDTH, PAD - FRAME_WIDTH, PAD + CHESS_SIZE * 8 + RIVER_WIDTH + FRAME_WIDTH);
		line(PAD + CHESS_SIZE * 8 + FRAME_WIDTH, PAD - FRAME_WIDTH, PAD + CHESS_SIZE * 8 + FRAME_WIDTH, PAD + CHESS_SIZE * 8 + RIVER_WIDTH + FRAME_WIDTH);
		//绘制列的上半部分

			//修改下面用到的直线参数
		setlinestyle(
			PS_SOLID,
			4,
			NULL,
			0
		);

		for (int i = 0; i < 9; i++)
		{
			int x = PAD + CHESS_SIZE * i;
			int end_y = CHESS_SIZE * 4 + PAD;
			if (i == 0 || i == 8)	end_y = CHESS_SIZE * 8 + PAD + RIVER_WIDTH;
			line(x, PAD, x, end_y);
		}

		//绘制列的下半部分
		for (int i = 0; i < 9; i++)
		{
			int x = PAD + CHESS_SIZE * i;
			int beging_y = CHESS_SIZE * 4 + PAD + RIVER_WIDTH;
			int end_y = CHESS_SIZE * 8 + PAD + RIVER_WIDTH;
			line(x, beging_y, x, end_y);
		}

		//绘制行的上半部分
		for (int j = 0; j < 5; j++)
		{
			int y = PAD + CHESS_SIZE * j;
			line(PAD, y, WIDTH - PAD, y);
		}

		//绘制行的上半部分
		for (int j = 5; j < 10; j++)
		{
			int y = PAD + CHESS_SIZE * (j - 1) + RIVER_WIDTH;
			line(PAD, y, WIDTH - PAD, y);
		}

		//绘制楚河漢界
		setbkmode(TRANSPARENT);


		AddFontResourceEx(L"font.ttf", FR_PRIVATE, NULL);

		settextcolor(BLACK);
		settextstyle(new LOGFONT{
			50,
			60,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			ANTIALIASED_QUALITY,
			FIXED_PITCH,
			_T("Aa千里江山小隶书")
			});


		drawtext(
			L"楚河",
			new RECT{ PAD  , PAD + CHESS_SIZE * 4,PAD + TEXT_WIDTH,PAD + CHESS_SIZE * 4 + TEXT_HEIGHT },
			DT_CENTER | DT_VCENTER | DT_SINGLELINE
		);

		drawtext(
			L"漢界",
			new RECT{ PAD + CHESS_SIZE * 8 / 2 , PAD + CHESS_SIZE * 4,PAD + CHESS_SIZE * 8 / 2 + TEXT_WIDTH,PAD + CHESS_SIZE * 4 + TEXT_HEIGHT },
			DT_CENTER | DT_SINGLELINE | DT_VCENTER
		);


		//绘制斜线
		for (int i = 0; i < 2; i++)
		{
			line(PAD + CHESS_SIZE * 3, PAD + CHESS_SIZE * i * 6 + RIVER_WIDTH * i, PAD + CHESS_SIZE * 5, PAD + CHESS_SIZE * 2 + CHESS_SIZE * i * 6 + RIVER_WIDTH * i);
			line(PAD + CHESS_SIZE * 3, PAD + CHESS_SIZE * 2 + CHESS_SIZE * i * 6 + RIVER_WIDTH * i, PAD + CHESS_SIZE * 5, PAD + CHESS_SIZE * i * 6 + RIVER_WIDTH * i);
		}
	
}


void RenderChess()
{
	
	/*
	炮 10
	车 9 
	马 8
	象 7
	士 6
	将 5
	帅 -5
	兵 -1
	卒 1
	*/

	settextstyle(new LOGFONT{
			30,
			40,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			ANTIALIASED_QUALITY,
			FIXED_PITCH,
			_T("Aa千里江山小隶书")
		});
	//加载并绘制上半部分的棋子
	setfillcolor(RGB(240, 230, 140));
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			int data = chessData[i][j];
			if (data > 0 )
			{	
				settextcolor(BLACK);
				setlinecolor(BLACK);
			}
			else if (data < 0)
			{
				settextcolor(RED);
				setlinecolor(RED);
			}
			if (data != 0)
			{
				int x = PAD + CHESS_SIZE * j;
				int y = PAD + CHESS_SIZE * i;
				
				setlinestyle(
					PS_SOLID,
					2,
					NULL,
					0
				);
				fillcircle(x, y, (CHESS_SIZE-15) / 2);
				floodfill(x, y, 0, 1);
				circle(x,y,(CHESS_SIZE-30)/2);
				drawtext(
					DataToChess(data),
					new RECT{ x - CHESS_SIZE / 2 , y - CHESS_SIZE / 2,x + CHESS_SIZE / 2,y + CHESS_SIZE / 2 },
					DT_CENTER | DT_VCENTER | DT_SINGLELINE
				);
			}
		}
	}

	//加载并绘制下半部分的棋子
	for (int i = 5; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			int data = chessData[i][j];
			if (data > 0)
			{
				settextcolor(BLACK);
				setlinecolor(BLACK);
			}
			else if (data < 0)
			{
				settextcolor(RED);
				setlinecolor(RED);
			}
			if (data != 0)
			{
				
				int x = PAD + CHESS_SIZE * j;
				int y = PAD + CHESS_SIZE * (i-1) + RIVER_WIDTH;
				fillcircle(x, y, (CHESS_SIZE - 15) / 2);
				floodfill(x, y, 0, 1);
				circle(x, y, (CHESS_SIZE - 30) / 2);
				drawtext(
					DataToChess(data),
					new RECT{ x - CHESS_SIZE / 2 , y - CHESS_SIZE / 2,x + CHESS_SIZE / 2,y + CHESS_SIZE / 2 },
					DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
		}
	}



}

void RenderChoose(int row, int column)
{
	int x = PAD + column * CHESS_SIZE;
	int y = PAD + row * CHESS_SIZE;
	if (row >= 5)	y -= CHESS_SIZE - RIVER_WIDTH;
	//rectangle(x - CHESS_SIZE / 2, y - CHESS_SIZE / 2, x + CHESS_SIZE / 2, y + CHESS_SIZE / 2);
	setlinecolor(RGB(0, 0, 255));
	//左上
	line(x - CHESS_SIZE / 2, y - CHESS_SIZE / 2, x - CHESS_SIZE / 2 + CHESS_SIZE/8, y - CHESS_SIZE / 2);
	line(x - CHESS_SIZE / 2, y - CHESS_SIZE / 2, x - CHESS_SIZE / 2 , y - CHESS_SIZE / 2 + CHESS_SIZE / 8);
	//左下
	line(x - CHESS_SIZE / 2, y + CHESS_SIZE / 2, x - CHESS_SIZE / 2 + CHESS_SIZE / 8, y + CHESS_SIZE / 2);
	line(x - CHESS_SIZE / 2, y + CHESS_SIZE / 2, x - CHESS_SIZE / 2, y + CHESS_SIZE / 2 - CHESS_SIZE / 8);
	//右下
	line(x + CHESS_SIZE / 2, y + CHESS_SIZE / 2, x + CHESS_SIZE / 2 - CHESS_SIZE / 8, y + CHESS_SIZE / 2);
	line(x + CHESS_SIZE / 2, y + CHESS_SIZE / 2, x + CHESS_SIZE / 2, y + CHESS_SIZE / 2 - CHESS_SIZE / 8);
	//右上
	line(x + CHESS_SIZE / 2, y - CHESS_SIZE / 2, x + CHESS_SIZE / 2 - CHESS_SIZE / 8, y - CHESS_SIZE / 2);
	line(x + CHESS_SIZE / 2, y - CHESS_SIZE / 2, x + CHESS_SIZE / 2, y - CHESS_SIZE / 2 + CHESS_SIZE / 8);

}

void InitData()
{
	
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			chessData[9 - i][j] = -chessData[i][j];
		}
	}
}

void RenderCanDownPos()
{
	setfillcolor(RGB(100, 250, 100));
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if(CanDownPos[i][j] ==1)
			{
				int x = PAD + CHESS_SIZE * j;
				int y = PAD + CHESS_SIZE * i;
				fillcircle(x, y, 10);
				floodfill(x, y, 0, 1);
			}
		}
	}

	//加载并绘制下半部分的棋子
	for (int i = 5; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (CanDownPos[i][j] == 1)
			{
				int x = PAD + CHESS_SIZE * j;
				int y = PAD + CHESS_SIZE * (i-1) +RIVER_WIDTH;
				fillcircle(x, y, 10);
				floodfill(x, y, 0, 1);
			}
		}
	}


}



LPCTSTR DataToChess(int data)		//将数据转换为棋名
{
	switch (data)
	{
	case 10 :
	case -10:
		return L"炮";
		break;
	case 9:
	case -9:
		return L"车";
		break;
	case 8:
	case -8:
		return L"马";
		break;
	case 7:
	case -7:
		return L"象";
		break;
	case 6:
		return L"仕";
		break;
	case -6:
		return L"士";
		break;
	case 5:
		return L"将";
		break;

	case -5:
		return L"帅";
		break;

	case 1:
		return L"卒";
		break;

	case -1:
		return L"兵";
		break;
	}
	return 0;
}
