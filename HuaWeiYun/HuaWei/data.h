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

#define MAPWIDTH (int)100 // 地图宽pixel
#define MAPHEIGHT (int)100 // 地图长pixel
#define MAX_BENCH_SIZE (int)50 // 最大工作台数量
#define ROBOT_NUM (int)4 // 机器人数量
#define ROBOT_MAX_FORWARDSPEED (double)6 // 最大前进6m/s
#define ROBOT_MAX_RETREATSPEED (double)2. // 最大后退2m/s
#define BENCH_TYPE (int)9 // 工作台所有类型
#define SYS_MAX_FRAMENUM (int)9000 // 最大帧数
#define SYS_SECOND_FRAMENUM (int)8500 // 最大帧数
#define SYS_THIRD_FRAMENUM (int)8000 // 最大帧数
#define SYS_MIN_RATE (double)0.8 // 最小系数
#define ROBOT_MAX_ROTATESPEED RPI // 最大角速度
#define MAX_TRACTION (double)250. // 最大牵引力
#define MAX_MOMENT (double)250. // 最大力矩
#define ROBOT_DENSITY (int)20 // 机器人密度
#define ROBOT_RADUIS_WITHOUT (double)0.45 // 机器人空载半径
#define ROBOT_RADUIS_WITH (double)0.53 // 机器人载物半径
#define ROBOT_BENCH_DIST (double)0.4 // 机器人靠近工作台判定距离
#define ROBOT_SATE_DISTANCE (double)4.

RPoint Pos2Actual(RPoint); // 坐标到实际尺寸的转换
#define Pos2Actual(p) RPoint({0.5 * (p.x + 0.5), 0.5 * (99.5 - p.y)}) 

double DistRPoint2RPoint(RPoint, RPoint); // 计算点到点距离
#define DistRPoint2RPoint(p1, p2) (double)sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)) 

//RVector2i RPoint2RVector(RPoint, RPoint); // 计算p1指向p2向量
//#define RPoint2RVector(p1, p2) RVector2i({(p2.x - p1.x) / sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2)), (p2.y - p1.y) / sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2))})
double Point2Rad(RPoint, RPoint); // 两点相对0rad为旋转角
#define Point2Rad(p1, p2) acos((p2.x - p1.x) / sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2)))

double Point2Rad2(RPoint, RPoint); // 两点相对0rad为旋转角
#define Point2Rad2(p1, p2) atan2(p2.y - p1.y, p2.x - p1.x)

double Frame2Coff(int); // 帧数到系数的转换
#define Frame2Coff(frame) (double)(1 - sqrt(1-(1-pow(frame/SYS_MAX_FRAMENUM, 2)))*(1-SYS_MIN_RATE) + SYS_MIN_RATE)

extern unordered_map<int, vector<int>> mBench2SubBench; // 当前工作台到下一级工作台的映射关系
extern unordered_map<int, int> mMaxProfit; // 货物对应最大利润
extern unordered_map<int, vector<int>> mRawMaterial;
extern unordered_map<int, vector<int>> mBenchSort; // 每种工作台的所有编号
//extern unordered_map<int, vector<int>> mCurBenchNum;
extern vector<int> OccupyGoalBench;
extern vector<int> NoSellProduct;
//extern int currentSeven; // 指向当前第一个默认的7

extern int currentFrameId; // 当前绝对帧数（相对于起始0而言）
extern int actualBenchNum; // 有效工作台数量
extern int CurrentMapNum; // 有效工作台数量
extern vector<Bench> vBenchInfo; // 所有工作台
extern vector<int> vValidBenchNum; // 所有工作台
extern vector<Bench> vBenchInfoDup; // 所有工作台
extern vector<Robot> vRobotInfo; // 所有机器人信息
extern vector<int> vBenchWorkPeriod; // 工作台类型与工作周期对应关系
extern vector<vector<int>> vvBenchTypeInfo; // 工作台类型与其对应vBenchInfo索引
extern vector<vector<int>> vvSubBenchTypeInfo; // 工作台可以消化生产出的物品的工作台对应vBenchInfo索引，如1：4、5、9
extern unordered_map<int, vector<int>> mivSubBenchIndex; // 工作台可以消化生产出的物品的工作台索引
extern unordered_map<int, vector<double>> mivSubBenchDist; // 工作台可以消化生产出的物品的工作台索引
//extern vector<int> vBenchWorkPeriod; // 
extern unordered_map<int, set<int>> vDealingGoods;// 键：工作台类型，值：工作台


// 04
extern stack<int> sTotalTask;
extern stack<int> sTotalTaskUse;
extern int totalSenveBenchNum;
extern int curSevenBenchNum;
//	每个unordered_map表示每一个工作台（编号0类型0） map键对应下一个工作台类型（可以买他买的是类型348）值为所有的索引
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
extern unordered_map<int, int> mBuyBenchGoods; // 货物对应最大利润
extern unordered_map<int, int> mSellBenchGoods; // 货物对应最大利润
//// 7缺失456生产所需原材料；0：不缺456都在加工，1
extern set<int> sSevenLackRaw; // 7类型工作台缺的原材料类型
extern unordered_map<int, set<int>> mSevenRawState; // 7类型工作台有的原材料类型
//extern unordered_map<int, set<int>> mRecFour;
//extern unordered_map<int, set<int>> mRecFour;
//extern unordered_map<int, set<int>> mRecFour;
#define CONVERT_MODEL_FRAME (int)8000
extern vector<int> needResetNum; // 到达目标后需要最后复位的机器人
extern vector<int> haveTaskRobot; // 当前有任务的机器人
#define ROBOT_TASK_ACCEPT_MIN_DIST (double)3. // 当机器人任务小于3m由最近机器人去做
#define ROBOT_CLOSEING_WALL (double)4. // 当机器人任务靠墙3m，速度减少
 #define myspeed(x) (double)(x >= ROBOT_CLOSEING_WALL ? 1 : x / ROBOT_CLOSEING_WALL) // 以ROBOT_CLOSEING_WALL为底的对数
// 大于ROBOT_CLOSEING_WALL系数为0，小于ROBOT_CLOSEING_WALL按距离线性衰减

// 06
extern vector<int> needResetNum6; // 到达目标后需要最后复位的机器人
//#define FIRST_PROTENTIAL_PROFIT (double)0.25 // 第一级潜在收益47
//#define SECOND_PROTENTIAL_PROFIT (double)0.167 // 第二级潜在收益78
#define FIRST_PROTENTIAL_PROFIT (double)0.25 / 4  // 第一级潜在收益47
#define SECOND_PROTENTIAL_PROFIT (double)0.167 / 4// 第二级潜在收益78

extern bool FourBenchIsGoing;

extern double param1;
extern double param2;
extern int profitMoney;
extern string savePath;
extern string mapNum;

extern vector<vector<int>> whsoleMap;

#endif

