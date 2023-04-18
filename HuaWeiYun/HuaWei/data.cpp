#include "header.h"

int CurrentMapNum = 0;
int actualBenchNum = 0;
int currentFrameId = 0;
vector<Bench> vBenchInfo;
vector<Bench> vBenchInfoDup(MAX_BENCH_SIZE, Bench());
vector<Robot> vRobotInfo(ROBOT_NUM, Robot());
vector<int> vValidBenchNum; // 所有工作台
vector<int> vBenchWorkPeriod(BENCH_TYPE, 0);
vector<vector<int>> wholeMap(MAPHEIGHT, vector<int>(MAPWIDTH));

unordered_map<int, vector<int>> mBench2SubBench;
unordered_map<int, int> mMaxProfit;
unordered_map<int, vector<int>> mRawMaterial;
unordered_map<int, vector<int>> mBenchSort;
//unordered_map<int, vector<int>> mCurBenchNum;
vector<int> OccupyGoalBench; 
vector<int> NoSellProduct;
//int currentSeven = 0;

vector<vector<int>> vvBenchTypeInfo;
vector<vector<int>> vvSubBenchTypeInfo; 
unordered_map<int, vector<int>> mivSubBenchIndex; 
unordered_map<int, vector<double>> mivSubBenchDist; 
unordered_map<int, set<int>> vDealingGoods;

// 04
stack<int> sTotalTask;
stack<int> sTotalTaskUse;
int totalSenveBenchNum;
int curSevenBenchNum;
vector<unordered_map<int, vector<int>>> vmBench2SubBench;
vector<int> vPriority4567;
vector<int> notUpdateBench;
int goalBench123 = -1;
int goalBench456 = -1;
int taskTotalCnt = 0;
int tmp456Type = -1; // 当前123对应那个456
vector<int> vEstimateAvailable;


// 05
unordered_map<int, int> mBenchType2TaskLevel;
unordered_map<int, int> mBuyBenchGoods; // 货物对应最大利润
unordered_map<int, int> mSellBenchGoods; // 货物对应最大利润
set<int> sSevenLackRaw; // 7类型工作台缺的原材料类型
unordered_map<int, set<int>> mSevenRawState;
vector<int> needResetNum; // 到达目标后需要最后复位的机器人
vector<int> haveTaskRobot; // 当前有任务的机器人

//06
vector<int> needResetNum6; // 到达目标后需要最后复位的机器人

bool FourBenchIsGoing = false;

// write file
double param1 = 0.;
double param2 = 0.;
int profitMoney = 0;
string savePath = "d:\\result\\result";
string mapNum = "";

