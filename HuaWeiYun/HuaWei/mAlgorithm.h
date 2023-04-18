#ifndef _MALGORITHM__H
#define _MALGORITHM__H

#include <iostream>
using namespace std;
#include <vector>
#include "data.h"
#include "robot.h"
#include "Bench.h"

void SysInit(); // 系统初始化，读取地图信息
void InitBenchList(); // 初始化工作台的信息
void UpdataInfo(const vector<string>& vs); // 读取交互信息，更新机器人、工作台信息
void PrintRobotInfo(); // 打印机器人信息
void PrintBenchInfo(); // 打印工作台信息
void PrintTaskPoolInfo();
// 计算点到点所需要的帧数
void IsRobotCollosionCorner();
void IsRobotCollosion();
void CalcRobot2BenchCostBase();
void CalcRobot2BenchCostBase2();
void CalcRobot2BenchCostBase3();
void CalcRobot2BenchCostBase4();
void CalcRobot2BenchCostBase5(); // 任务池
void CalcRobot2BenchCostBase6(int mode); // 纯贪心买卖耦合（0最短距离、1单位距离利润）
void SortBenchByPriority();

#endif // !
