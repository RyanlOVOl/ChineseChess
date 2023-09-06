#pragma once
#include "constant.h"
#include "renderer.h"


#ifdef COMMON_HS
#define COMMON_HS
extern int CanDownPos[10][9];
extern int state;
extern int turn;
#endif 

int GetRowChess(int start_row, int start_column, bool direct);

int GetColumnChess(int start_row, int start_column, bool direct);

int GetFlag(int row, int column);
void RuleChoose(int row, int column);
void InitDownPos();
void RulePao(int row,int column);
void RuleChe(int row, int column);
void RuleBin(int row, int column);
void RuleMa(int row, int column);
void RuleShi(int row, int column);
void RuleCommander(int row, int column);
void RuleXiang(int row, int column); 