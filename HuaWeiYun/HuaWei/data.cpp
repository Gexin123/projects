#include "header.h"

int CurrentMapNum = 0;
int actualBenchNum = 0;
int currentFrameId = 0;
vector<Bench> vBenchInfo;
vector<Bench> vBenchInfoDup(MAX_BENCH_SIZE, Bench());
vector<Robot> vRobotInfo(ROBOT_NUM, Robot());
vector<int> vValidBenchNum; // ���й���̨
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
int tmp456Type = -1; // ��ǰ123��Ӧ�Ǹ�456
vector<int> vEstimateAvailable;


// 05
unordered_map<int, int> mBenchType2TaskLevel;
unordered_map<int, int> mBuyBenchGoods; // �����Ӧ�������
unordered_map<int, int> mSellBenchGoods; // �����Ӧ�������
set<int> sSevenLackRaw; // 7���͹���̨ȱ��ԭ��������
unordered_map<int, set<int>> mSevenRawState;
vector<int> needResetNum; // ����Ŀ�����Ҫ���λ�Ļ�����
vector<int> haveTaskRobot; // ��ǰ������Ļ�����

//06
vector<int> needResetNum6; // ����Ŀ�����Ҫ���λ�Ļ�����

bool FourBenchIsGoing = false;

// write file
double param1 = 0.;
double param2 = 0.;
int profitMoney = 0;
string savePath = "d:\\result\\result";
string mapNum = "";

