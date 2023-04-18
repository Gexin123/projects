#ifndef _DATA__H
#define _DATA__H

#include <vector>
#include <cmath>
#include <unordered_map>
#include <set>
#include <stack>
#include "Bench.h"
#include "robot.h"

#define RPI (double)3.14159

#define MAPWIDTH (int)100 // ��ͼ��pixel
#define MAPHEIGHT (int)100 // ��ͼ��pixel
#define MAX_BENCH_SIZE (int)50 // �����̨����
#define ROBOT_NUM (int)4 // ����������
#define ROBOT_MAX_FORWARDSPEED (double)6 // ���ǰ��6m/s
#define ROBOT_MAX_RETREATSPEED (double)2. // ������2m/s
#define BENCH_TYPE (int)9 // ����̨��������
#define SYS_MAX_FRAMENUM (int)9000 // ���֡��
#define SYS_SECOND_FRAMENUM (int)8500 // ���֡��
#define SYS_THIRD_FRAMENUM (int)8000 // ���֡��
#define SYS_MIN_RATE (double)0.8 // ��Сϵ��
#define ROBOT_MAX_ROTATESPEED RPI // �����ٶ�
#define MAX_TRACTION (double)250. // ���ǣ����
#define MAX_MOMENT (double)250. // �������
#define ROBOT_DENSITY (int)20 // �������ܶ�
#define ROBOT_RADUIS_WITHOUT (double)0.45 // �����˿��ذ뾶
#define ROBOT_RADUIS_WITH (double)0.53 // ����������뾶
#define ROBOT_BENCH_DIST (double)0.4 // �����˿�������̨�ж�����
#define ROBOT_SATE_DISTANCE (double)4.

RPoint Pos2Actual(RPoint); // ���굽ʵ�ʳߴ��ת��
#define Pos2Actual(p) RPoint({0.5 * (p.x + 0.5), 0.5 * (99.5 - p.y)}) 

double DistRPoint2RPoint(RPoint, RPoint); // ����㵽�����
#define DistRPoint2RPoint(p1, p2) (double)sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)) 

//RVector2i RPoint2RVector(RPoint, RPoint); // ����p1ָ��p2����
//#define RPoint2RVector(p1, p2) RVector2i({(p2.x - p1.x) / sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2)), (p2.y - p1.y) / sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2))})
double Point2Rad(RPoint, RPoint); // �������0radΪ��ת��
#define Point2Rad(p1, p2) acos((p2.x - p1.x) / sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2)))

double Point2Rad2(RPoint, RPoint); // �������0radΪ��ת��
#define Point2Rad2(p1, p2) atan2(p2.y - p1.y, p2.x - p1.x)

double Frame2Coff(int); // ֡����ϵ����ת��
#define Frame2Coff(frame) (double)(1 - sqrt(1-(1-pow(frame/SYS_MAX_FRAMENUM, 2)))*(1-SYS_MIN_RATE) + SYS_MIN_RATE)

extern unordered_map<int, vector<int>> mBench2SubBench; // ��ǰ����̨����һ������̨��ӳ���ϵ
extern unordered_map<int, int> mMaxProfit; // �����Ӧ�������
extern unordered_map<int, vector<int>> mRawMaterial;
extern unordered_map<int, vector<int>> mBenchSort; // ÿ�ֹ���̨�����б��
//extern unordered_map<int, vector<int>> mCurBenchNum;
extern vector<int> OccupyGoalBench;
extern vector<int> NoSellProduct;
//extern int currentSeven; // ָ��ǰ��һ��Ĭ�ϵ�7

extern int currentFrameId; // ��ǰ����֡�����������ʼ0���ԣ�
extern int actualBenchNum; // ��Ч����̨����
extern int CurrentMapNum; // ��Ч����̨����
extern vector<Bench> vBenchInfo; // ���й���̨
extern vector<int> vValidBenchNum; // ���й���̨
extern vector<Bench> vBenchInfoDup; // ���й���̨
extern vector<Robot> vRobotInfo; // ���л�������Ϣ
extern vector<int> vBenchWorkPeriod; // ����̨�����빤�����ڶ�Ӧ��ϵ
extern vector<vector<int>> vvBenchTypeInfo; // ����̨���������ӦvBenchInfo����
extern vector<vector<int>> vvSubBenchTypeInfo; // ����̨������������������Ʒ�Ĺ���̨��ӦvBenchInfo��������1��4��5��9
extern unordered_map<int, vector<int>> mivSubBenchIndex; // ����̨������������������Ʒ�Ĺ���̨����
extern unordered_map<int, vector<double>> mivSubBenchDist; // ����̨������������������Ʒ�Ĺ���̨����
//extern vector<int> vBenchWorkPeriod; // 
extern unordered_map<int, set<int>> vDealingGoods;// ��������̨���ͣ�ֵ������̨


// 04
extern stack<int> sTotalTask;
extern stack<int> sTotalTaskUse;
extern int totalSenveBenchNum;
extern int curSevenBenchNum;
//	ÿ��unordered_map��ʾÿһ������̨�����0����0�� map����Ӧ��һ������̨���ͣ������������������348��ֵΪ���е�����
extern vector<unordered_map<int, vector<int>>> vmBench2SubBench;
extern vector<int> vPriority4567;
extern vector<int> notUpdateBench;
extern int goalBench123;
extern int tmp456Type;
extern int goalBench456;
extern int taskTotalCnt;
extern vector<int> vEstimateAvailable;

// 05
//extern unordered_map<int, int> mBenchType2TaskLevel;
extern unordered_map<int, int> mBuyBenchGoods; // �����Ӧ�������
extern unordered_map<int, int> mSellBenchGoods; // �����Ӧ�������
//// 7ȱʧ456��������ԭ���ϣ�0����ȱ456���ڼӹ���1
extern set<int> sSevenLackRaw; // 7���͹���̨ȱ��ԭ��������
extern unordered_map<int, set<int>> mSevenRawState; // 7���͹���̨�е�ԭ��������
//extern unordered_map<int, set<int>> mRecFour;
//extern unordered_map<int, set<int>> mRecFour;
//extern unordered_map<int, set<int>> mRecFour;
#define CONVERT_MODEL_FRAME (int)8000
extern vector<int> needResetNum; // ����Ŀ�����Ҫ���λ�Ļ�����
extern vector<int> haveTaskRobot; // ��ǰ������Ļ�����
#define ROBOT_TASK_ACCEPT_MIN_DIST (double)3. // ������������С��3m�����������ȥ��
#define ROBOT_CLOSEING_WALL (double)4. // ������������ǽ3m���ٶȼ���
 #define myspeed(x) (double)(x >= ROBOT_CLOSEING_WALL ? 1 : x / ROBOT_CLOSEING_WALL) // ��ROBOT_CLOSEING_WALLΪ�׵Ķ���
// ����ROBOT_CLOSEING_WALLϵ��Ϊ0��С��ROBOT_CLOSEING_WALL����������˥��

// 06
extern vector<int> needResetNum6; // ����Ŀ�����Ҫ���λ�Ļ�����
//#define FIRST_PROTENTIAL_PROFIT (double)0.25 // ��һ��Ǳ������47
//#define SECOND_PROTENTIAL_PROFIT (double)0.167 // �ڶ���Ǳ������78
#define FIRST_PROTENTIAL_PROFIT (double)0.25 / 4  // ��һ��Ǳ������47
#define SECOND_PROTENTIAL_PROFIT (double)0.167 / 4// �ڶ���Ǳ������78

extern bool FourBenchIsGoing;

extern double param1;
extern double param2;
extern int profitMoney;
extern string savePath;
extern string mapNum;

extern vector<vector<int>> whsoleMap;

#endif

