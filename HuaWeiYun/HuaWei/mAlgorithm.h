#ifndef _MALGORITHM__H
#define _MALGORITHM__H

#include <iostream>
using namespace std;
#include <vector>
#include "data.h"
#include "robot.h"
#include "Bench.h"

void SysInit(); // ϵͳ��ʼ������ȡ��ͼ��Ϣ
void InitBenchList(); // ��ʼ������̨����Ϣ
void UpdataInfo(const vector<string>& vs); // ��ȡ������Ϣ�����»����ˡ�����̨��Ϣ
void PrintRobotInfo(); // ��ӡ��������Ϣ
void PrintBenchInfo(); // ��ӡ����̨��Ϣ
void PrintTaskPoolInfo();
// ����㵽������Ҫ��֡��
void IsRobotCollosionCorner();
void IsRobotCollosion();
void CalcRobot2BenchCostBase();
void CalcRobot2BenchCostBase2();
void CalcRobot2BenchCostBase3();
void CalcRobot2BenchCostBase4();
void CalcRobot2BenchCostBase5(); // �����
void CalcRobot2BenchCostBase6(int mode); // ��̰��������ϣ�0��̾��롢1��λ��������
void SortBenchByPriority();

#endif // !
