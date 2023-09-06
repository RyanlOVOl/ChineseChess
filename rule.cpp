#include "rule.h"
#include <stdio.h>
extern int chessData[10][9];
int CanDownPos[10][9];
int state = 0;
int turn = -1;
int GetRowChess(int start_row, int start_column, bool direct)
{


	if (!direct)
	{
		for (int i = start_column; i > 0; i--)
		{
			if (chessData[start_row][i] != 0)	return i;
		}
	}
	else
	{
		for (int i = start_column; i < 9 - start_row; i++)
		{
			if (chessData[start_row][i] != 0)	return i;
		}
	}
	return -1;
}

int GetColumnChess(int start_row, int start_column, bool direct)
{



	if (!direct)
	{
		for (int i = start_row; i > 0; i--)
		{
			if (chessData[i][start_column] != 0)	return i;
		}
	}
	else
	{
		for (int i = start_column; i < 10 - start_row; i++)
		{
			if (chessData[i][start_column] != 0)	return i;
		}
	}
	return -1;
}

int GetFlag(int row, int column)
{
	//通过上半区将或帅的位置来判断所选棋子的归属范围 上半棋盘 下半棋盘
	for (int i = 3; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (abs(chessData[j][i]) == 5)
			{
				if (chessData[j][i] * chessData[row][column] > 0)
				{
					return 1;
				}
				else
				{
					return -1;
				}
				
				break;
			}
		}
	}

	return 0;
}

void RuleChoose(int row, int column)
{
	int data = chessData[row][column];

	
	switch (data)
	{
	case -10:
	case 10:
		//炮的规则
		RulePao(row, column);
		break;
	case 9:
	case -9:
		//车的规则
		RuleChe(row, column);
		break;
	case 8:
	case -8:
		//马的规则
		RuleMa(row, column);
		break;
	case 7:
	case -7:
		//象的规则
		RuleXiang(row, column);
		break;
	case 6:
	case -6:
		//士的规则
		RuleShi(row, column);
		break;
	case 5:
	case -5:
		//将和帅的规则
		RuleCommander(row, column);
		break;
	case 1:
	case -1:
		//兵和卒的规则
		RuleBin(row, column);
		break;
	}

	RenderCanDownPos();

}

void InitDownPos()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			CanDownPos[i][j] = 0;
		}
	}
}

void RulePao(int row, int column)
{
	//列的处理
		//向上判断
	for (int i = row-1; i >= 0; i--)
	{
		if (chessData[i][column] == 0)
		{
			CanDownPos[i][column] = 1;
		}
		else 
		{
			//遇到阻挡棋子
			for (int j = i-1; j >= 0; j--)
			{
				
				if (chessData[j][column] * chessData[row][column] < 0)
				{

					//向上遍历到的第一个异色棋，标记可吃，并且将此位置改为可落子
					CanDownPos[j][column] = 1;
					break;
				}
			}
			//跳出,因为上面已经将此遍历完了
			break;
		}
	}
		
		//向下判断
	for (int i = row + 1; i < 10; i++)
	{
		if (chessData[i][column] == 0)
		{
			CanDownPos[i][column] = 1;
		}
		else
		{
			//遇到阻挡棋子
			for (int j = i + 1; j < 10; j++)
			{
				if (chessData[j][column] * chessData[row][column] < 0)
				{
					//向上遍历到的第一个异色棋，标记可吃，并且将此位置改为可落子
					CanDownPos[j][column] = 1;
					break;
				}
			}
			//跳出,因为上面已经将此遍历完了
			break;
		}
	}

	//行的处理
		//向左判断
	for (int i = column - 1; i >= 0; i--)
	{
		if (chessData[row][i] == 0)
		{
			CanDownPos[row][i] = 1;
		}
		else
		{
			//遇到阻挡棋子
			for (int j = i - 1; j >= 0; j--)
			{
				if (chessData[row][j] * chessData[row][column] < 0)
				{
					//向上遍历到的第一个异色棋，标记可吃，并且将此位置改为可落子
					CanDownPos[row][j] = 1;
					break;
				}
			}
			//跳出,因为上面已经将此遍历完了
			break;
		}
	}
		//向右判断
	for (int i = column + 1; i < 9 ; i++)
	{
		if (chessData[row][i] == 0)
		{
			CanDownPos[row][i] = 1;
		}
		else
		{
			//遇到阻挡棋子
			for (int j = i + 1; j < 9; j++)
			{
				if (chessData[row][j] * chessData[row][column] < 0)
				{
					//向上遍历到的第一个异色棋，标记可吃，并且将此位置改为可落子
					CanDownPos[row][j] = 1;
					break;
				}
			}
			//跳出,因为上面已经将此遍历完了
			break;
		}
	}
}

void RuleChe(int row, int column)
{
	//行的处理
		//向左判断
	for (int i = column - 1; i >= 0; i--)
	{
		if (chessData[row][i] * chessData[row][column] <= 0)
		{
			CanDownPos[row][i] = 1;
			if (chessData[row][i] != 0) break;

		}
		else
		{
			break;
		}

	}


	//向右判断
	for (int i = column + 1; i < 9; i++)
	{
		if (chessData[row][i] * chessData[row][column] <= 0)
		{
			CanDownPos[row][i] = 1;
			if (chessData[row][i] != 0) break;
		}
		else
		{
			break;
		}
	}


	//列的处理 
	//向上判断
	for (int i = row - 1; i >= 0; i--)
	{
		if (chessData[i][column] * chessData[row][column] <= 0)
		{
			CanDownPos[i][column] = 1;
			if (chessData[i][column] != 0) break;
		}
		else
		{
			break;
		}
	}

	//向下判断
	for (int i = row + 1; i < 10; i++)
	{
		if (chessData[i][column] * chessData[row][column] <= 0)
		{
			CanDownPos[i][column] = 1;
			if (chessData[i][column] != 0) break;
		}
		else
		{
			break;
		}
	}
}

void RuleBin(int row, int column)
{
	int flag = GetFlag(row, column);
	
	
	if (flag == -1) 
	{
		//是否过河的判定
		if (row < 5) 
		{
			//前
			if ((row - 1) >= 0)
			{
				if (chessData[row - 1][column] * chessData[row][column] <= 0)	CanDownPos[row - 1][column] = 1;
			}
			//左
			if ((column - 1) >= 0)
			{
				if (chessData[row][column - 1] * chessData[row][column] <= 0)	CanDownPos[row][column - 1] = 1;
			}
			//右
			if ((column + 1) < 9)
			{
				if (chessData[row][column + 1] * chessData[row][column] <= 0)	CanDownPos[row][column + 1] = 1;
			}
		}
		else 
		{
			//前
			if (chessData[row - 1][column] * chessData[row][column] <= 0)	CanDownPos[row - 1][column] = 1;
		}
	}
	else
	{
		//是否过河的判定
		if (row > 4)
		{
			//前
			if ((row + 1) < 10)
			{
				if (chessData[row + 1][column] * chessData[row][column] <= 0)	CanDownPos[row + 1][column] = 1;
			}
			//左
			if ((column - 1) >= 0)
			{
				if (chessData[row][column - 1] * chessData[row][column] <= 0)	CanDownPos[row][column - 1] = 1;
			}
			//右
			if ((column + 1) < 9)
			{
				if (chessData[row][column + 1] * chessData[row][column] <= 0)	CanDownPos[row][column + 1] = 1;
			}
		}
		else
		{
			//前
			if (chessData[row + 1][column] * chessData[row][column] <= 0)	CanDownPos[row + 1][column] = 1;
		}
	}

}

void RuleMa(int row, int column)
{
	//向上
	if ((row - 2) >= 0)
	{
		//判断是否被撇马脚
		if (chessData[row - 1][column] == 0)
		{
			//左
			if ((column - 1) >= 0)
			{
				if (chessData[row - 2][column - 1] * chessData[row][column] <= 0)		CanDownPos[row - 2][column - 1] = 1;
			}
			//右
			if ((column + 1) < 9)
			{
				if (chessData[row - 2][column + 1] * chessData[row][column] <= 0)		CanDownPos[row - 2][column + 1] = 1;
			}
		}
	}
	//向下
	if ((row + 2) < 10)
	{
		//判断是否被撇马脚
		if (chessData[row + 1][column] == 0)
		{
			//左
			if ((column - 1) >= 0)
			{
				if (chessData[row + 2][column - 1] * chessData[row][column] <= 0)		CanDownPos[row + 2][column - 1] = 1;
			}
			//右
			if ((column + 1) < 9)
			{
				if (chessData[row + 2][column + 1] * chessData[row][column] <= 0)		CanDownPos[row + 2][column + 1] = 1;
			}
		}
	}

	//向左
	if ((column - 2) >= 0)
	{
		//判断是否被撇马脚
		if (chessData[row][column - 1] == 0)
		{
			//上
			if ((row - 1) >= 0)
			{
				if (chessData[row - 1][column - 2] * chessData[row][column] <= 0)		CanDownPos[row - 1][column - 2] = 1;
			}
			//下
			if ((row + 1) < 10)
			{
				if (chessData[row + 1][column - 2] * chessData[row][column] <= 0)		CanDownPos[row + 1][column - 2] = 1;
			}
		}
	}

	//向右
	if ((column + 2) < 9)
	{
		//判断是否被撇马脚
		if (chessData[row][column + 1] == 0)
		{
			//上
			if ((row - 1) >= 0)
			{
				if (chessData[row - 1][column + 2] * chessData[row][column] <= 0)		CanDownPos[row - 1][column + 2] = 1;
			}
			//下
			if ((row + 1) < 10)
			{
				if (chessData[row + 1][column + 2] * chessData[row][column] <= 0)		CanDownPos[row + 1][column + 2] = 1;
			}
		}
	}

}

void RuleShi(int row, int column)
{
	int flag = GetFlag(row, column);

	if (flag == -1) 
	{
	//下半棋盘
		//上
		if ((row - 1) >= 7)
		{
			//左
			if ((column - 1) >= 3)
			{
				if (chessData[row - 1][column - 1] * chessData[row][column] <= 0)	CanDownPos[row - 1][column - 1] = 1;
			}
			//右
			if ((column + 1) <= 5)
			{
				if (chessData[row - 1][column + 1] * chessData[row][column] <= 0)	CanDownPos[row - 1][column + 1] = 1;

			}
		}
		//下
		if ((row + 1) < 9)
		{
			//左
			if ((column - 1) >= 3)
			{
				if (chessData[row + 1][column - 1] * chessData[row][column] <= 0)	CanDownPos[row + 1][column - 1] = 1;
			}
			//右
			if ((column + 1) <= 5)
			{
				if (chessData[row + 1][column + 1] * chessData[row][column] <= 0)	CanDownPos[row + 1][column + 1] = 1;
			}
		}
	}
	if (flag == 1)
	{
	//上半棋盘
		//上
		if ((row - 1) >= 0)
		{
			//左
			if ((column - 1) >= 3)
			{
				if (chessData[row - 1][column - 1] * chessData[row][column] <= 0)	CanDownPos[row - 1][column - 1] = 1;
			}
			//右
			if ((column + 1) <= 5)
			{
				if (chessData[row - 1][column + 1] * chessData[row][column] <= 0)	CanDownPos[row - 1][column + 1] = 1;
			}
		}
		//下
		if ((row + 1) < 3)
		{
			//左
			if ((column - 1) >= 3)
			{
				if (chessData[row + 1][column - 1] * chessData[row][column] <= 0)	CanDownPos[row + 1][column - 1] = 1;
			}
			//右
			if ((column + 1) <= 5)
			{
				if (chessData[row + 1][column + 1] * chessData[row][column] <= 0)	CanDownPos[row + 1][column + 1] = 1;
			}
		}
	}
	

}

void RuleCommander(int row, int column)
{
	int flag = GetFlag(row, column);
	if (flag == -1)	//上半区
	{
		//上
		if ((row - 1) >= 7)
		{
			if (chessData[row - 1][column] * chessData[row][column] <= 0)	CanDownPos[row - 1][column] = 1;
		}
		//下
		if ((row + 1) < 10)
		{
			if (chessData[row + 1][column] * chessData[row][column] <= 0)	CanDownPos[row + 1][column] = 1;
		}
	}
	if (flag == 1)	//下半区
	{
		//上
		if ((row - 1) >= 0)
		{
			if (chessData[row - 1][column] * chessData[row][column] <= 0)	CanDownPos[row - 1][column] = 1;
		}
		//下
		if ((row + 1) < 3)
		{
			if (chessData[row + 1][column] * chessData[row][column] <= 0)	CanDownPos[row + 1][column] = 1;
		}
	}
	//左
	if ((column - 1) >= 3)
	{
		if (chessData[row][column - 1] * chessData[row][column] <= 0)	CanDownPos[row][column - 1] = 1;
	}
	//右
	if ((column + 1) < 6)
	{
		if (chessData[row][column + 1] * chessData[row][column] <= 0)	CanDownPos[row][column + 1] = 1;
	}
	
	
}

void RuleXiang(int row, int column)
{
	int flag = GetFlag(row, column);
	
	if (flag == -1)
	{
		//向上
		if ((row - 2) >= 5)
		{

			//左
			if ((column - 2) >= 0)
			{
				if (chessData[row - 1][column - 1] == 0 && chessData[row - 2][column - 2] * chessData[row][column] <= 0) CanDownPos[row - 2][column - 2] = 1;
			}
			//右
			if ((column + 2) < 9)
			{
				if (chessData[row - 1][column + 1] == 0 && chessData[row - 2][column + 2] * chessData[row][column] <= 0) CanDownPos[row - 2][column + 2] = 1;
			}
		}

		//向下
		if ((row + 2) < 10)
		{

			//左
			if ((column - 2) >= 0)
			{
				if (chessData[row + 1][column - 1] == 0 && chessData[row + 2][column - 2] * chessData[row][column] <= 0) CanDownPos[row + 2][column - 2] = 1;
			}
			//右
			if ((column + 2) < 9)
			{
				if (chessData[row + 1][column + 1] == 0 && chessData[row + 2][column + 2] * chessData[row][column] <= 0) CanDownPos[row + 2][column + 2] = 1;
			}
		}
	}
	if (flag == 1)
	{
		//向上
		if ((row - 2) >= 0)
		{

			//左
			if ((column - 2) >= 0)
			{
				if (chessData[row - 1][column - 1] == 0 && chessData[row - 2][column - 2] * chessData[row][column] <= 0) CanDownPos[row - 2][column - 2] = 1;
			}
			//右
			if ((column + 2) < 9)
			{
				if (chessData[row - 1][column + 1] == 0 && chessData[row - 2][column + 2] * chessData[row][column] <= 0) CanDownPos[row - 2][column + 2] = 1;
			}
		}

		//向下
		if ((row + 2) < 5)
		{

			//左
			if ((column - 2) >= 0)
			{
				if (chessData[row + 1][column - 1] == 0 && chessData[row + 2][column - 2] * chessData[row][column] <= 0) CanDownPos[row + 2][column - 2] = 1;
			}
			//右
			if ((column + 2) < 9)
			{
				if (chessData[row + 1][column + 1] == 0 && chessData[row + 2][column + 2] * chessData[row][column] <= 0) CanDownPos[row + 2][column + 2] = 1;
			}
		}
	}


}


