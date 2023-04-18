#include "header.h"

class SortBenchByNum {
public:
	bool operator()(int num1, int num2) {
		Bench b1 = vBenchInfo[num1];
		Bench b2 = vBenchInfo[num2];
		if (b1.getProduceState()) return true;
		if (b2.getProduceState()) return false;
		vector<int> rawMat1 = mRawMaterial[b1.getBenchType()];
		vector<int> rawMat2 = mRawMaterial[b2.getBenchType()];
		int cnt1 = 0, cnt2 = 0;
		for (int i = 0; i < rawMat1.size(); i++) {
			cnt1 += ((b1.getRawState() >> rawMat1[i]) & 0x01);
		}
		for (int i = 0; i < rawMat2.size(); i++) {
			cnt2 += ((b2.getRawState() >> rawMat2[i]) & 0x01);
		}
		return cnt1 < cnt2;
	}
};

void SortBenchByPriority() {
	for (int i = BENCH_TYPE - 2 - 1; i > 3 - 1; i--) {
		// 7（654）层按照原材料的缺失情况，以及产出台情况进行排序
		// 同一级按原材料数量进行排序
		sort(mBenchSort[i].begin(), mBenchSort[i].end(), SortBenchByNum());
	}
	//for (int i = 3; i > 0; i--) {
	//	// 123层按照距离排序
	//}
}

void SysInit() {
	mBench2SubBench[0] = vector<int>({ 4 - 1, 5 - 1, 9 - 1 });
	mBench2SubBench[1] = vector<int>({ 4 - 1, 6 - 1, 9 - 1 });
	mBench2SubBench[2] = vector<int>({ 5 - 1, 6 - 1, 9 - 1 });
	mBench2SubBench[3] = vector<int>({ 7 - 1, 9 - 1 });
	mBench2SubBench[4] = vector<int>({ 7 - 1, 9 - 1 });
	mBench2SubBench[5] = vector<int>({ 7 - 1, 9 - 1 });
	mBench2SubBench[6] = vector<int>({ 8 - 1, 9 - 1 });

	mBuyBenchGoods[0] = 3000; mSellBenchGoods[0] = 6000; mMaxProfit[0] = 3000;
	mBuyBenchGoods[1] = 4400; mSellBenchGoods[1] = 7600; mMaxProfit[1] = 3200;
	mBuyBenchGoods[2] = 5800; mSellBenchGoods[2] = 9200; mMaxProfit[2] = 3400;
	mBuyBenchGoods[3] = 15400; mSellBenchGoods[3] = 22500; mMaxProfit[3] = 7100;
	mBuyBenchGoods[4] = 17200; mSellBenchGoods[4] = 25000; mMaxProfit[4] = 7800;
	mBuyBenchGoods[5] = 19200; mSellBenchGoods[5] = 27500; mMaxProfit[5] = 8300;
	mBuyBenchGoods[6] = 76000; mSellBenchGoods[6] = 105000; mMaxProfit[6] = 29000;

	//mBenchType2TaskLevel[0] = 1;
	//mBenchType2TaskLevel[1] = 1;
	//mBenchType2TaskLevel[2] = 1;
	//mBenchType2TaskLevel[3] = 2;
	//mBenchType2TaskLevel[4] = 2;
	//mBenchType2TaskLevel[5] = 2;
	//mBenchType2TaskLevel[6] = 3;
	//mBenchType2TaskLevel[7] = 4;
	//mBenchType2TaskLevel[8] = 4;

	mRawMaterial[4 - 1] = vector<int>({ 1 - 1, 2 - 1 });
	mRawMaterial[5 - 1] = vector<int>({ 1 - 1, 3 - 1 });
	mRawMaterial[6 - 1] = vector<int>({ 2 - 1, 3 - 1 });
	mRawMaterial[7 - 1] = vector<int>({ 4 - 1, 5 - 1, 6 - 1 });

	//InitBenchList();
	for (int i = 0; i < actualBenchNum; i++) {
		// 按工作台的类型进行排序
		Bench curBench = vBenchInfoDup[i];
		mBenchSort[curBench.getBenchType()].emplace_back(i);
	}

	//for (int i = 0; i < BENCH_TYPE; i++) {
	//	fprintf(stderr, "mBenchSort info:%d		num:", i);
	//	vector<int> v = mBenchSort[i];
	//	for (int j = 0; j < v.size(); j++) {
	//		fprintf(stderr, "	%d	", v[j]);
	//	}
	//	fprintf(stderr, "\n");
	//}

	//sTotalTask.push(1);
	//sTotalTask.push(3);
	//sTotalTask.push(0);
	//sTotalTask.push(3);
	//sTotalTask.push(2);
	//sTotalTask.push(4);
	//sTotalTask.push(0);
	//sTotalTask.push(4);
	//sTotalTask.push(2);
	//sTotalTask.push(5);
	//sTotalTask.push(1);
	//sTotalTask.push(5);

	sTotalTask.push(2);
	sTotalTask.push(5);
	sTotalTask.push(1);
	sTotalTask.push(5);
	sTotalTask.push(2);
	sTotalTask.push(4);
	sTotalTask.push(0);
	sTotalTask.push(4);
	sTotalTask.push(1);
	sTotalTask.push(3);
	sTotalTask.push(0);
	sTotalTask.push(3);
	totalSenveBenchNum = mBenchSort[6].size();
	sTotalTaskUse = stack<int>(sTotalTask);
}

void InitBenchList() {
	//for (int i = 0; i < actualBenchNum; i++) {
	//	Bench curBench = vBenchInfo[i];
	//	int curBenchType = curBench.getBenchType();
	//	for (int j = 0; j < actualBenchNum; j++) {
	//		if (i == j) continue;
	//		Bench subBench = vBenchInfo[j];
	//		vector<int>::iterator itr = find(
	//			mBench2SubBench[curBenchType].begin(),
	//			mBench2SubBench[curBenchType].end(),
	//			subBench.getBenchType()
	//		);
	//		if (itr != mBench2SubBench[curBenchType].end()) {
	//			// 如果下一个窗口能够消耗当前窗口的货物，则保存下一窗口位置和距离
	//			double dist = DistRPoint2RPoint(curBench.getPos(), subBench.getPos());
	//			mivSubBenchIndex[i].emplace_back(j);
	//			mivSubBenchDist[i].emplace_back(dist);
	//		}
	//	}
	//}
	//return;
	vmBench2SubBench = vector<unordered_map<int, vector<int>>>(actualBenchNum);
	for (int i = 0; i < actualBenchNum; i++) {
		Bench curBench = vBenchInfo[i];
		int curBenchType = curBench.getBenchType();
		for (int j = 0; j < actualBenchNum; j++) {
			if (i == j) continue;
			Bench subBench = vBenchInfo[j];
			vector<int>::iterator itr = find(
				mBench2SubBench[curBenchType].begin(),
				mBench2SubBench[curBenchType].end(),
				subBench.getBenchType()
			);
			if (itr != mBench2SubBench[curBenchType].end()) {
				//// 如果下一个窗口能够消耗当前窗口的货物，则保存下一窗口位置和距离
				vmBench2SubBench[i][subBench.getBenchType()].emplace_back(j);
			}
		}
	}
	//for (int i = 0; i < vmBench2SubBench.size(); i++) {
	//	fprintf(stderr, "第%d个工作台:\n", i);
	//	unordered_map<int, vector<int>>::iterator itr = vmBench2SubBench[i].begin();
	//	for (; itr != vmBench2SubBench[i].end(); itr++) {
	//		vector<int> v = (*itr).second;
	//		fprintf(stderr, "消耗工作台类型为:%d		", (*itr).first);
	//		for (int j = 0; j < v.size(); j++) {
	//			fprintf(stderr, "%d	", v[j]);
	//		}
	//		fprintf(stderr, "\n", (*itr).first);
	//	}
	//}
	return;
}

void ConvertString2VectorInfo(const string& str, vector<double>& v) {
	string tmpStr = str;
	int dataIndex = 0;
	while (1) {
		int index = tmpStr.find(' ');
		//fprintf(stderr, "dataIndex:%d，其中' '所在索引:%d\n", dataIndex, index);
		if (index == -1) {
			v[dataIndex] = stold(tmpStr.c_str());
			return;
		}
		v[dataIndex] = stold(tmpStr.substr(0, index).c_str());
		tmpStr = tmpStr.substr(index + 1); // 更新字符串
		dataIndex++;
	}
}

void UpdataInfo(const vector<string>& vs) {
	string tmpStr = vs[0];
	int index = tmpStr.find(' ');
	//fprintf(stderr, "当前字符串为：%s，其中' '所在索引：%d", tmpStr.c_str(), index);
	//currentFrameId = atoi(tmpStr.substr(0, index).c_str());
	int money = atoi(tmpStr.substr(index + 1).c_str());
	int benchNum = atoi(vs[1].c_str());
	profitMoney = money;
	// 更新工作台信息
	for (int i = 0; i < benchNum; i++) {
		int num = count(vValidBenchNum.begin(), vValidBenchNum.end(), i);
		if (num == 0) continue;

		vector<double> v(6, -1);
		ConvertString2VectorInfo(vs[i + 2], v);

		vBenchInfoDup[i].setProductTime((int)v[3]);
		vBenchInfoDup[i].setRawState((int)v[4]);
		vBenchInfoDup[i].setProduceState((int)v[5]);
		//vBenchInfo[i].setProductTime((int)v[3]);
		//vBenchInfo[i].setRawState((int)v[4]);
		//vBenchInfo[i].setProduceState((int)v[5]);
		if (((int)v[0] == 4 || (int)v[0] == 5 || (int)v[0] == 6) && v[5] == 1) {
			int num = count(notUpdateBench.begin(), notUpdateBench.end(), i);
			//fprintf(stderr, "num:%d	produce type:%d\n", i, (int)v[0]);
			if (num > 0) continue;
			vPriority4567.emplace_back(i);
			notUpdateBench.emplace_back(i);
		}
		else if ((int)v[0] == 7 && v[5] == 1) {
			int num = count(notUpdateBench.begin(), notUpdateBench.end(), i);
			//fprintf(stderr, "num:%d	produce type:%d\n", i, (int)v[0]);
			if (num > 0) continue;
			vPriority4567.insert(vPriority4567.begin(), i); // 7优先级最高
			notUpdateBench.emplace_back(i);
		}
	}

	// 更新状态信息
	vBenchInfo.clear();
	vBenchInfo = vector<Bench>(vValidBenchNum.size());
	for (int i = 0; i < vValidBenchNum.size(); i++) {
		vBenchInfo[i] = vBenchInfoDup[vValidBenchNum[i]]; // 读取有效编号的机器人信息
	}
	//PrintBenchInfo();
	
	mBenchSort.clear();
	for (int i = 0; i < vBenchInfo.size(); i++) {
		// 按工作台的类型进行排序
		Bench curBench = vBenchInfo[i];
		mBenchSort[curBench.getBenchType()].emplace_back(i);
	}	
	//for (int i = 0; i < BENCH_TYPE; i++) {
	//	fprintf(stderr, "mBenchSort info:%d		num:", i);
	//	vector<int> v = mBenchSort[i];
	//	for (int j = 0; j < v.size(); j++) {
	//		fprintf(stderr, "	%d	", v[j]);
	//	}
	//	fprintf(stderr, "\n");
	//}

	// 更新机器人信息
	for (int i = 0; i < 4; i++) {
		vector<double> v(10, -1);
		ConvertString2VectorInfo(vs[i + 2 + benchNum], v);
		//for (int i = 0; i < 10; i++) {
		//	fprintf(stderr, "%0.2f	", v[i]);
		//}
		//fprintf(stderr, "\n");
		vector<int>::iterator itr = find(vValidBenchNum.begin(), vValidBenchNum.end(), v[0]);
		if (itr != vValidBenchNum.end()) {
			v[0] = (itr - vValidBenchNum.begin());
		}
		else {
			v[0] = -1;
		}
		vRobotInfo[i].setId(v[0]);
		vRobotInfo[i].setGoodsId(v[1]);
		vRobotInfo[i].setTimeCoff(v[2]);
		vRobotInfo[i].setCollisionCoff(v[3]);
		vRobotInfo[i].setAngleVel(v[4]);
		vRobotInfo[i].setLineVelx(v[5]);
		vRobotInfo[i].setLineVely(v[6]);
		vRobotInfo[i].setRad(v[7]);
		vRobotInfo[i].setPos(RPoint{ v[8], v[9] });
	}
	//SortBenchByPriority();
	//fprintf(stderr, "------------1--------------------\n");
	 
	mSevenRawState.clear();
	sSevenLackRaw.clear();
	// 获取7类型工作台的原材信息
	for (int i = 0; i < mBenchSort[6].size(); i++) {
		int sevenNum = mBenchSort[6][i];
		for (int raw = 0; raw < 3; raw++) {
			//fprintf(stderr, "------------2--------------------%d\n", sevenNum);
			int rawState = vBenchInfo[sevenNum].getRawState() | vBenchInfo[sevenNum]._rawStateGoing;
			if ((rawState >> (raw + 4)) & 0x01) {
				mSevenRawState[sevenNum].insert(raw + 4);
			}
		}
		if (mSevenRawState[sevenNum].size() == 2) {
			// 只记录差一个原材料时
			set<int> sTotal({ 4,5,6 });
			vector<int> diffOut(1);
			//sort(mSevenRawState[sevenNum].begin(), mSevenRawState[sevenNum].end());
			set_difference(sTotal.begin(), sTotal.end(),
				mSevenRawState[sevenNum].begin(), mSevenRawState[sevenNum].end(),
				diffOut.begin());
			// 是否有对应的原材料正在处理
			bool whetherHaveRaw = false; // 没有在处理
			vector<int> lackRawTotal = mBenchSort[diffOut[0] - 1];
			vector<int> rawType = mRawMaterial[diffOut[0] - 1];
			for (int rawIndex = 0; rawIndex < lackRawTotal.size(); rawIndex++) {
				int rawCnt = 0;
				for (int rawT = 0; rawT < rawType.size(); rawT++) {
					int needRaw = vBenchInfo[lackRawTotal[rawIndex]].getRawState() | vBenchInfo[lackRawTotal[rawIndex]]._rawStateGoing;
					if ((needRaw >> (rawT + 1)) & 0x01) {
						rawCnt++;
					}
				}
				if (rawCnt == 2) {
					// 已经在生产了
					whetherHaveRaw = true;
					break;
				}
			}
			if (!whetherHaveRaw) {
				//fprintf(stderr, "7缺失的原材料正在加工:%d\n", diffOut[0] - 1);
				sSevenLackRaw.insert(diffOut[0] - 1);
			}
			//else fprintf(stderr, "7缺失的原材料为:%d\n", diffOut[0] - 1);
		}
	}

	//if (sSevenLackRaw.size()) {
	//	fprintf(stderr, "seven lack raw:");
	//	for (set<int>::iterator itr = sSevenLackRaw.begin(); itr != sSevenLackRaw.end(); itr++) {
	//		fprintf(stderr, "%d	", *(itr));
	//	}
	//	fprintf(stderr, "\n");
	//}
}

void PrintRobotInfo() {
	for (int i = 0; i < vRobotInfo.size(); i++) {
	}
	fprintf(stderr, "--------------------------------------CurrentRobotInfo:--------------------------------------\n");
	for (int i = 0; i < ROBOT_NUM; i++) {
		//fprintf(
		//	stderr,
		//	"num:%d	benchId:%d	goodsId:%d	timeCoff:%0.2f	collisionCoff:%0.2f	angleVel:%0.2f	LineVelx:%0.2f	LineVely:%0.2f	rad:%0.2f	x:%0.2f   y:%0.2f\n",
		//	i, vRobotInfo[i].getId(), vRobotInfo[i].getGoodsId(), vRobotInfo[i].getTimeCoff(),
		//	vRobotInfo[i].getCollisionCoff(), vRobotInfo[i].getAngleVel(),
		//	vRobotInfo[i].getLineVelx(), vRobotInfo[i].getLineVely(), 
		//	vRobotInfo[i].getRad(), vRobotInfo[i].getPos().x, vRobotInfo[i].getPos().y
		//);	
		fprintf(stderr, "robotid:%d		task:", i);
		if (vRobotInfo[i]._vTask.size()) {
			for (int j = 0; j < vRobotInfo[i]._vTask.size(); j++) {
				fprintf(stderr, "%d(%d)->",
					vRobotInfo[i]._vTask[j]._qBench,
					vBenchInfo[vRobotInfo[i]._vTask[j]._qBench].getBenchType());
			}
		}
		fprintf(stderr, "\n");
	}
	//fprintf(stderr, "\n");
}

void PrintBenchInfo() {
	fprintf(stderr, "--------------------------------------CurrentBenchInfo:--------------------------------------\n");
	for (int i = 0; i < vBenchInfo.size(); i++) {
		fprintf(
			stderr,
			"num: %d	type:%d	raw material:%d	goingState:%d	product:%d	buyGoing:%d\n",
			i, vBenchInfo[i].getBenchType(), vBenchInfo[i].getRawState(), 
			vBenchInfo[i]._rawStateGoing, vBenchInfo[i].getProduceState(), vBenchInfo[i]._buyGoing
		);
	}
	//fprintf(stderr, "\n");
}

void PrintTaskPoolInfo() {
	PrintBenchInfo();
	fprintf(stderr, "cur frame:%d   task pool info:%d\n", currentFrameId, qTaskPool.size());
	{
	    priority_queue<TaskStack, vector<TaskStack>, TaskPool> qtemp = qTaskPool;
	    fprintf(stderr, "frame id:%d\n", currentFrameId);
	    // 打印任务池
	    while (!qtemp.empty()) {
	        TaskStack ts = qtemp.top();
	        qtemp.pop();
	        for (int i = 0; i < ts._qTaskList.size(); i++) {
	            fprintf(stderr, "num:%d(%d, level:%d) ",
	                ts._qTaskList[i]._qBench, vBenchInfo[ts._qTaskList[i]._qBench].getBenchType(),
	                ts._level);
	        }
	        fprintf(stderr, "\n");
	    }
	}
}

// 处理当机器人是否移动到目标点
bool VerityRobot2Goal(Robot& r, int num) {
	//fprintf(stderr, "%d\n\n\n", r._2bench);
	if (r._2bench == -1) return false; // 没有任务
	if (r.getId() != r._2bench) {
		// 机器人没有到达目标点：计算旋转、平移偏差
		Bench goal = vBenchInfo[r._2bench];
		double dist = DistRPoint2RPoint(r.getPos(), goal.getPos()); // 当前机器人和工作台距离
		double rotate = Point2Rad2(r.getPos(), goal.getPos()) - r.getRad();
		int frame = rotate * 1000 / 20 / ROBOT_MAX_ROTATESPEED;
		double speed = ROBOT_MAX_FORWARDSPEED;
		double radSpd = ROBOT_MAX_ROTATESPEED;
		if (dist < ROBOT_MAX_FORWARDSPEED) {
			speed = 0.2 * ROBOT_MAX_FORWARDSPEED + 0.8 * dist;
		}
		if (abs(rotate) < 0.2) {
			radSpd = 0.4 * ((rotate > 0 ? ROBOT_MAX_ROTATESPEED : -ROBOT_MAX_ROTATESPEED)) + 0.6 * rotate;
		}
		printf("rotate %d %f\n", num, radSpd);
		printf("forward %d %f\n", num, speed);

		//fprintf(stderr, "Vertify robot pos: %0.2f	%0.2f	\
		//				goal pos:%0.2f	%0.2f calc rad:%0.2f\
		//				robot rad:%0.2f	need frame:%d\n",
		//	r.getPos().x, r.getPos().y,
		//	goal.getPos().x, goal.getPos().y,
		//	rotate, r.getRad(), frame);
		//fprintf(stderr, "frame:%d\n", frame);
		return true;
	}
	else {
		// 到达目标
		printf("rotate %d %f\n", num, 0.);
		printf("forward %d %f\n", num, 0.);
		if (r.getGoodsId()) printf("sell %d\n", num);
		else printf("buy %d\n", num);
		// 删除工作台信息
		vector<pair<int, int>> robotInBenchInfo = vBenchInfo[r._2bench]._robot_buyOrSell;
		if (robotInBenchInfo.size() == 1) {
			// 只有一个机器人向工作台移动
			remove(OccupyGoalBench.begin(), OccupyGoalBench.end(), r._2bench);
		}
		for (int i = 0; i < robotInBenchInfo.size(); i++) {
			//fprintf(stderr, "robot num:%d	carry goods:%d", robotInBenchInfo[i].first, robotInBenchInfo[i].second);
			if (robotInBenchInfo[i].first == num) {
				// 机器人编号相同删除任务
				vBenchInfo[r._2bench]._robot_buyOrSell.erase(i + vBenchInfo[r._2bench]._robot_buyOrSell.begin());
			}
		}
		//fprintf(stderr, "\n");
		// 删除机器人信息
		r._2bench = -1;
		return true;
	}
}

void CalcRobot2BenchCostBase() {
	//for (int i = 0; i < 1; i++) {
	//for (int i = 1; i < 2; i++) {
	//for (int i = 2; i < 3; i++) {
	//for (int i = 3; i < 4; i++) {
	for (int i = 0; i < ROBOT_NUM; i++) {
		Robot curRobot = vRobotInfo[i];
		if(VerityRobot2Goal(vRobotInfo[i], i)) continue;
		priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pqMinTime;
		for (int j = 0; j < actualBenchNum; j++) {
			Bench curBench = vBenchInfo[j];
			if (curRobot.getGoodsId()) {
				// 当前机器人携带物品（卖：根据携带物品种类）
				if (curBench.getBenchType() < 3) continue; // 0、1、2工作台不买材料
				vector<int> validMap = mBench2SubBench[curRobot.getGoodsId() - 1];
				vector<int>::iterator itr = find(validMap.begin(), validMap.end(), curBench.getBenchType());
				if (itr == validMap.end()) continue; // 不接收该材料的也不判断
				// 当前工作台的原材料有了也不考虑
				if ((curBench.getRawState() >> curRobot.getGoodsId()) & 0x01) continue;
				double moveTime = DistRPoint2RPoint(curRobot.getPos(), curBench.getPos()) / ROBOT_MAX_FORWARDSPEED;
				double rotateTime = abs(Point2Rad(curRobot.getPos(), curBench.getPos()) - curRobot.getRad()) / ROBOT_MAX_ROTATESPEED;
				double totalTime = ceil((moveTime + rotateTime) * 1000 / 20); // ms转换到帧数
				pqMinTime.push(pair<double, int>(totalTime, j));
				//fprintf(stderr, "robot goods id:%d	bench type:%d	\n", curRobot.getGoodsId(), curBench.getBenchType());
				//for (int i = 0; i < validMap.size(); i++) {
				//	fprintf(stderr, "%d	\n", validMap[i]);
				//}
				//fprintf(stderr, "\n");
				//fprintf(
				//	stderr,
				//	"num: %d	type:%d  x:%0.2f   y:%0.2f  produce time:%d  raw material:%d    product:%d\n",
				//	j, vBenchInfo[j].getBenchType(), vBenchInfo[j].getPos().x, vBenchInfo[j].getPos().y,
				//	vBenchInfo[j].getProductTime(), vBenchInfo[j].getRawState(), vBenchInfo[j].getProduceState()
				//);
			}
			else {
				// 当前机器人未携带物品（买）
				// 当工作有商品且工作台为生产工作台才计算
				if (curBench.getBenchType() > 7) continue;
				// 当前工作台没有生产出物品
				if (!curBench.getProduceState()) continue;
				double moveTime = DistRPoint2RPoint(curRobot.getPos(), curBench.getPos()) / ROBOT_MAX_FORWARDSPEED;
				double rotateTime = abs(Point2Rad(curRobot.getPos(), curBench.getPos()) - curRobot.getRad()) / ROBOT_MAX_ROTATESPEED;
				double totalTime = ceil((moveTime + rotateTime) * 1000 / 20); // ms转换到帧数
				if (!vBenchInfo[j].getProduceState() && totalTime > vBenchInfo[i].getProductTime()) continue;
				pqMinTime.push(pair<double, int>(totalTime, j));
			}
		}
		//// 按升序排列结果、选择当前最优
		//while (!pqMinTime.empty()) {
		//	pair<double, int> tmp = pqMinTime.top();
		//	fprintf(stderr, "num:%d(%0.2f)	", tmp.second, tmp.first);
		//	pqMinTime.pop();
		//}
		//fprintf(stderr, "\n");
		if (!pqMinTime.empty()) {
			pair<double, int> curGoal;
			while (!pqMinTime.empty()) {
				// 判断当前目标是否已有机器人前往
				curGoal = pqMinTime.top();
				vector<int>::iterator itr = find(OccupyGoalBench.begin(), OccupyGoalBench.end(), curGoal.second);
				if (itr == OccupyGoalBench.end()) {
					// 当前工作台未有机器人去
					break;
				}
				else {
					// 当前工作台已有机器人去（买货物、卖货物）
					vector<pair<int, int>> vTaskList = vBenchInfo[curGoal.second]._robot_buyOrSell;
					bool valid = true;
					for (int i = 0; i < vTaskList.size(); i++) {
						if (vTaskList[i].second == curRobot.getGoodsId()) {
							// 之前任务中的货物==现在机器人的货物
							valid = false;
							break;
						}
					}
					if (valid) break;
				}
				pqMinTime.pop();
			}
			fprintf(stderr, "				bench num:%d\n", curGoal.second);
			Bench goalBench = vBenchInfo[curGoal.second];
			double rotate = Point2Rad2(curRobot.getPos(), goalBench.getPos()) - curRobot.getRad();
			// 更新机器人、工作台状态信息
			vRobotInfo[i]._2bench = curGoal.second; // 更新机器人工作状态前往工作台
			goalBench._robot_buyOrSell.emplace_back(pair<int, int>(i, curRobot.getGoodsId())); // 更新工作台信息
			OccupyGoalBench.push_back(curGoal.second);
			//fprintf(stderr, "robotNum: %d	robot: %0.2f	%0.2f	goal:%0.2f	%0.2f robot rad:%0.2f	need rotate:%0.2f\n",
			//	i, curRobot.getPos().x, curRobot.getPos().y,
			//	goalBench.getPos().x, goalBench.getPos().y, 
			//	curRobot.getRad(), rotate);
			printf("rotate %d %f\n", i, rotate > 0 ? ROBOT_MAX_ROTATESPEED : -ROBOT_MAX_ROTATESPEED);
			printf("forward %d %f\n", i, ROBOT_MAX_FORWARDSPEED);
			//printf("forward %d %f\n", i, 0.);
		}
	}
	return;
}

void DealNoSellProduct(Robot& r) {
	if (r.getGoodsId()) {
		vector<int>::iterator itr = find(NoSellProduct.begin(), NoSellProduct.end(), r.getGoodsId());
		if (itr == NoSellProduct.end()) {
			NoSellProduct.emplace_back(r.getGoodsId());
		}
	}
}

void CalcRobot2BenchCostBase3() {
	for (int i = 0; i < ROBOT_NUM; i++) {
		Robot curRobot = vRobotInfo[i];
		if (VerityRobot2Goal(vRobotInfo[i], i)) continue;
		priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pqMinTime;
		for (int j = 0; j < actualBenchNum; j++) {
			Bench curBench = vBenchInfo[j];
			if (curRobot.getGoodsId()) {
				//fprintf(stderr, "bench type:%d\n", curBench.getBenchType());
				// 当前机器人携带物品（卖：根据携带物品种类）
				if (curBench.getBenchType() < 3) continue; // 0、1、2工作台不卖材料
				// 不接收该材料的也不判断
				vector<int> validMap = mBench2SubBench[curRobot.getGoodsId() - 1];
				vector<int>::iterator itr = find(validMap.begin(), validMap.end(), curBench.getBenchType());
				if (itr == validMap.end()) continue;
				// 当前工作台的原材料有了也不考虑
				if ((curBench.getRawState() >> curRobot.getGoodsId()) & 0x01) continue;
				double moveTime = DistRPoint2RPoint(curRobot.getPos(), curBench.getPos()) / ROBOT_MAX_FORWARDSPEED;
				double rotateTime = abs(Point2Rad(curRobot.getPos(), curBench.getPos()) - curRobot.getRad()) / ROBOT_MAX_ROTATESPEED;
				double totalTime = ceil((moveTime + rotateTime) * 1000 / 20); // ms转换到帧数
				pqMinTime.push(pair<double, int>(totalTime, j));
			}
			else {
				// 当前机器人未携带物品（买）
				if (curBench.getBenchType() > 6) continue; // 当工作有商品且工作台为生产工作台才计算
				if (!curBench.getProduceState()) continue; // 当前工作台没有生产出物品
				// 当前要买的物品是一个卖不出去的
				vector<int>::iterator itr = find(NoSellProduct.begin(), NoSellProduct.end(), curBench.getBenchType());
				if (itr != NoSellProduct.end()) continue;
				double moveTime = DistRPoint2RPoint(curRobot.getPos(), curBench.getPos()) / ROBOT_MAX_FORWARDSPEED;
				double rotateTime = abs(Point2Rad(curRobot.getPos(), curBench.getPos()) - curRobot.getRad()) / ROBOT_MAX_ROTATESPEED;
				double totalTime = ceil((moveTime + rotateTime) * 1000 / 20); // ms转换到帧数
				if (!vBenchInfo[j].getProduceState() && totalTime > vBenchInfo[i].getProductTime()) continue;
				pqMinTime.push(pair<double, int>(totalTime, j));
			}
		}
		if (!pqMinTime.empty()) {
			pair<double, int> curGoal;
			while (!pqMinTime.empty()) {
				// 判断当前目标是否已有机器人前往
				curGoal = pqMinTime.top();
				vector<int>::iterator itr = find(OccupyGoalBench.begin(), OccupyGoalBench.end(), curGoal.second);
				if (itr == OccupyGoalBench.end()) {
					// 当前工作台未有机器人去
					break;
				}
				else {
					// 当前工作台已有机器人去（买货物、卖货物）
					vector<pair<int, int>> vTaskList = vBenchInfo[curGoal.second]._robot_buyOrSell;
					bool valid = false;
					for (int i = 0; i < vTaskList.size(); i++) {
						if (vTaskList[i].second == curRobot.getGoodsId()) {
							// 之前任务中的货物==现在机器人的货物
							valid = true;
							break;
						}
					}
					if (!valid) break;
				}
				pqMinTime.pop();
			}
			if (!pqMinTime.empty()) {
				// 寻找到目标
				Bench goalBench = vBenchInfo[curGoal.second];
				double rotate = Point2Rad2(curRobot.getPos(), goalBench.getPos()) - curRobot.getRad();
				// 更新机器人、工作台状态信息
				vRobotInfo[i]._2bench = curGoal.second; // 更新机器人工作状态前往工作台
				vBenchInfo[curGoal.second]._robot_buyOrSell.emplace_back(pair<int, int>(i, curRobot.getGoodsId())); // 更新工作台信息
				OccupyGoalBench.push_back(curGoal.second); // 更新占用信息
				// 如果这个货物能卖出去
				if (NoSellProduct.size() && curRobot.getGoodsId()) {
					vector<int>::iterator itr = find(NoSellProduct.begin(), NoSellProduct.end(), goalBench.getBenchType());
					if (itr != NoSellProduct.end()) {
						// 这个货物又能卖出去了，删除不能买卖出去那个
						NoSellProduct.erase(itr);
					}
				}
				printf("rotate %d %f\n", i, rotate > 0 ? ROBOT_MAX_ROTATESPEED : -ROBOT_MAX_ROTATESPEED);
				printf("forward %d %f\n", i, ROBOT_MAX_FORWARDSPEED);
			}
			else {
				DealNoSellProduct(curRobot);
			}
		}
		else {
			DealNoSellProduct(curRobot);
		}
	}

	if (!NoSellProduct.empty()) {
		//fprintf(stderr, "robot num %d \n", )
		fprintf(stderr, "NowErrBench:");
		for (int i = 0; i < NoSellProduct.size(); i++) {
			fprintf(stderr, "%d	", NoSellProduct[i]);
		}
		fprintf(stderr, "\n");
	}

	return;
}




// 处理当机器人是否移动到目标点
bool VerityRobot2Goal2(Robot& r, int num) {
	//fprintf(stderr, "%d\n\n\n", r._2bench);
	if (r._2bench == -1) return false; // 没有任务
	if (r.getId() != r._2bench) {
		// 机器人没有到达目标点：计算旋转、平移偏差
		Bench goal = vBenchInfo[r._2bench];
		double dist = DistRPoint2RPoint(r.getPos(), goal.getPos()); // 当前机器人和工作台距离
		double rotate = Point2Rad2(r.getPos(), goal.getPos()) - r.getRad();
		int frame = rotate * 1000 / 20 / ROBOT_MAX_ROTATESPEED;
		double speed = ROBOT_MAX_FORWARDSPEED;
		double radSpd = ROBOT_MAX_ROTATESPEED;
		if (dist < ROBOT_MAX_FORWARDSPEED) {
			speed = 0.2 * ROBOT_MAX_FORWARDSPEED + 0.8 * dist;
		}
		if (abs(rotate) < 0.2) {
			radSpd = 0.4 * ((rotate > 0 ? ROBOT_MAX_ROTATESPEED : -ROBOT_MAX_ROTATESPEED)) + 0.6 * rotate;
		}
		printf("rotate %d %f\n", num, radSpd);
		printf("forward %d %f\n", num, speed);

		return true;
	}
	else {
		// 到达目标
		printf("rotate %d %f\n", num, 0.);
		printf("forward %d %f\n", num, 0.);
		if (r.getGoodsId()) printf("sell %d\n", num);
		else printf("buy %d\n", num);
		//// 删除工作台信息
		//vector<pair<int, int>> robotInBenchInfo = vBenchInfo[r._2bench]._robot_buyOrSell;
		//if (robotInBenchInfo.size() == 1) {
		//	// 只有一个机器人向工作台移动
		//	remove(OccupyGoalBench.begin(), OccupyGoalBench.end(), r._2bench);
		//}
		//for (int i = 0; i < robotInBenchInfo.size(); i++) {
		//	//fprintf(stderr, "robot num:%d	carry goods:%d", robotInBenchInfo[i].first, robotInBenchInfo[i].second);
		//	if (robotInBenchInfo[i].first == num) {
		//		// 机器人编号相同删除任务
		//		vBenchInfo[r._2bench]._robot_buyOrSell.erase(i + vBenchInfo[r._2bench]._robot_buyOrSell.begin());
		//	}
		//}
		//fprintf(stderr, "\n");
		// 删除机器人信息
		r._2bench = r._sell2WhichBench; // 有卖给那个工作台就继续下发下一个任务
		r._sell2WhichBench = -1;

		return true;
	}
}

/*
	选择当前机器人应前往工作台的位置
	返回值：
		-2：表示当前层没有工作台
		-1：成功找到（存在goalBenchNum中）
		0-6：表示缺失的原材料类型
*/ 
int SelectBenchNum2(int curLevel, int& goalBenchNum, int& sell2WhichBench) {
	vector<int> curLevelTotal = mBenchSort[curLevel]; // 当前工作台类型的所有工作台标号列表
	if (curLevelTotal.empty()) return -2;
	// 7、（456）大层
	for (int i = 0; i < curLevelTotal.size(); i++) {
		Bench curBench = vBenchInfo[curLevelTotal[i]];
		if (curBench.getProduceState()) {
			// 如果生产好了就去拿
			goalBenchNum = curLevelTotal[i];
			return -1;
		}
		// 没有生产好，缺失原材料或正在生产
		vector<int> rawMaterialNum = mRawMaterial[curLevel]; // 当前工作台类型所需原材料的类型
		for (int raw = 0; raw < rawMaterialNum.size(); raw++) {
			// 如果有该类型原材料跳过
			//fprintf(stderr, "工作台类型为:%d	当前工作台编号:%d	当前原材料信息为:%d\n", 
			//	curLevel, curLevelTotal[i], vBenchInfo[curLevelTotal[i]].getRawState());
			if ((vBenchInfo[curLevelTotal[i]].getRawState() >> (rawMaterialNum[raw] + 1)) & 0x01) continue;
			else {
				// 没有的原材料，返回到下一大层去找
				//vBenchInfo[curLevelTotal[i]].setRawState(16);
				int num = count(
					vDealingGoods[curBench.getBenchType()].begin(),
					vDealingGoods[curBench.getBenchType()].end(),
					rawMaterialNum[raw]
				);
				if (num > 0) continue;
				sell2WhichBench = curLevelTotal[i];
				return rawMaterialNum[raw];
			}
		}
		//// 原材料都具备等待生产完成
		//sell2WhichBench = curLevelTotal[i];
	}
	return -2;
}
int SelectBenchNum(int curLevel, int& goalBenchNum) {
	vector<int> curLevelTotal = mBenchSort[curLevel]; // 当前工作台类型的所有工作台标号列表
	if (curLevelTotal.empty()) return -2;
	// 7、（456）大层
	for (int i = 0; i < curLevelTotal.size(); i++) {
		Bench curBench = vBenchInfo[curLevelTotal[i]];
		if (curBench.getProduceState()) {
			// 如果生产好了就去拿
			goalBenchNum = curLevelTotal[i];
			return -1;
		}
		// 没有生产好，缺失原材料
		vector<int> rawMaterialNum = mRawMaterial[curLevel]; // 当前工作台类型所需原材料的类型
		for (int raw = 0; raw < rawMaterialNum.size(); raw++) {
			// 如果有该类型原材料跳过
			//fprintf(stderr, "工作台类型为:%d	当前工作台编号:%d	当前原材料信息为:%d\n", 
			//	curLevel, curLevelTotal[i], vBenchInfo[curLevelTotal[i]].getRawState());
			if ((vBenchInfo[curLevelTotal[i]].getRawState() >> (rawMaterialNum[raw] + 1)) & 0x01) continue;
			else {
				// 没有的原材料，返回到下一大层去找
				//vBenchInfo[curLevelTotal[i]].setRawState(16);
				int num = count(
					vDealingGoods[curBench.getBenchType()].begin(), 
					vDealingGoods[curBench.getBenchType()].end(), 
					rawMaterialNum[raw]
				);
				if (num > 0) continue;
				return rawMaterialNum[raw];
			}
		}
		// 原材料都具备等待生产完成
	}
	return -2;
}

/*
	根据当前机器人和123工作台位置按距离进行排序
	返回值：
		-1：无工作台
		0~49：表示最近工作台编号
*/
int Sort123LevlByDist(Robot& r, int level) {
	// 小根堆pqMinTime
	priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pqMinTime;
	vector<int> vTotalBenchNum = mBenchSort[level];
	for (int j = 0; j < vTotalBenchNum.size(); j++) {
		Bench curBench = vBenchInfo[vTotalBenchNum[j]];
		double moveTime = DistRPoint2RPoint(r.getPos(), curBench.getPos()) / ROBOT_MAX_FORWARDSPEED;
		double rotateTime = abs(Point2Rad(r.getPos(), curBench.getPos()) - r.getRad()) / ROBOT_MAX_ROTATESPEED;
		//double totalTime = max(moveTime, rotateTime); // ms转换到帧数
		double totalTime = moveTime;
		//if (!vBenchInfo[j].getProduceState() && totalTime > curBench.getProductTime()) continue;
		pqMinTime.push(pair<double, int>(totalTime, vTotalBenchNum[j]));
	}
	//// 按升序排列结果、选择当前最优
	//while (!pqMinTime.empty()) {
	//	pair<double, int> tmp = pqMinTime.top();
	//	fprintf(stderr, "num:%d(%0.2f)	", tmp.second, tmp.first);
	//	pqMinTime.pop();
	//}
	//fprintf(stderr, "\n");
	if (pqMinTime.empty()) return -1;
	return pqMinTime.top().second;
}

void UpdateDealingGoods(int key, int val) {
	// 先看当前有没有当前元素
	vDealingGoods[key].insert(val); // 第一层所需的原材料（456）为键，值为第二层所需原材料（123）
	// 判断是否可以生产7
	if (vDealingGoods[key].size() == 2) {
		vDealingGoods[6].insert(key);
		vDealingGoods[key].clear();
	}
	if (vDealingGoods[6].size() == 3) {
		// 当前这个7的 原材料都在生产中
		vDealingGoods[6].clear();
		//if()
	}
}

void CalcRobot2BenchCostBase2() {
	//fprintf(stderr, "当前各种类型工作台信息:\n");
	//for (int i = 0; i < 7; i++) {
	//	vector<int> vTemp = mBenchSort[i];
	//	for (int j = 0; j < vTemp.size(); j++) {
	//		fprintf(stderr, "%d(%d)	", vBenchInfo[vTemp[j]].getBenchNum(), vBenchInfo[vTemp[j]].getBenchType());
	//	}
	//	fprintf(stderr, "\n");
	//}
	for (int i = 0; i < ROBOT_NUM; i++) {
		Robot curRobot = vRobotInfo[i];
		if (VerityRobot2Goal2(vRobotInfo[i], i)) continue; // 有任务就执行任务
		int goalBenchNum = -1;
		int sell2WhichBench = -1;
		//fprintf(stderr, "robot goods id:%d\n", curRobot.getGoodsId());
		if (curRobot.getGoodsId() == 0) {
			// 如果是没携带物品（去买货物）
			for (int level = BENCH_TYPE - 2 - 1; level > 0; level--) {
				// 从第7层变量优先级最高的工作台
				//int ret1 = SelectBenchNum(level, goalBenchNum);
				int ret1 = SelectBenchNum2(level, goalBenchNum, sell2WhichBench);
				if (ret1 == -1) break; // 找到了目标跳出
				else if (ret1 == -2) continue;
				fprintf(stderr, "第7层所需原材料为:%d\n", ret1);
				// 没找到到下一大层（456）
				//int ret2 = SelectBenchNum(ret1, goalBenchNum);
				int ret2 = SelectBenchNum2(ret1, goalBenchNum, sell2WhichBench);
				if (ret2 == -1) break; // 找到了目标跳出
				else if (ret2 == -2) continue;
				fprintf(stderr, "第456层所需原材料为:%d\n", ret2);
				UpdateDealingGoods(ret1, ret2);
				// 没找到到下一大层（123）,123三层按照距离最近进行排序
				int ret3 = Sort123LevlByDist(curRobot, ret2); // 根据当前机器人位置到最近工作台进行排序
				if (ret3 != -1) {
					// 找到了目标跳出
					//fprintf(stderr, "robot goal id:%d\n", goalBenchNum);
					goalBenchNum = ret3;
					break;
				}
				fprintf(stderr, "Now Error\n");
			}
			if (goalBenchNum != -1) {
				// 下达目标
				//fprintf(stderr, "cur goal info: num:%d	type:%d\n", goalBenchNum, vBenchInfo[goalBenchNum].getBenchType());
				vRobotInfo[i]._2bench = goalBenchNum;
				vRobotInfo[i]._sell2WhichBench = sell2WhichBench;
				fprintf(stderr, "当前买的要卖给:%d\n", sell2WhichBench);
				return;
			}
		}
		else {
			//// 机器人携带物品，优先级最高的卖
			//// 选优先级最高的卖出
			//vector<int> vPriority = mBenchSort[curRobot.getGoodsId() - 1];
			//if (!vPriority.empty()) goalBenchNum = vPriority[0];
		}
		//fprintf(stderr, "Now Error\n");
	}

	return;
}



/*
	根据当前机器人和工作台位置按距离进行排序
	返回值：
		-1：无工作台
		0~49：表示最近工作台编号
*/
int FindLeastDist(vector<int>& v, Robot& r) {
	//benchNum
	// 小根堆pqMinTime
	priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pqMinTime;
	vector<int> vTotalBenchNum(v);
	for (int j = 0; j < vTotalBenchNum.size(); j++) {
		Bench curBench = vBenchInfo[vTotalBenchNum[j]];
		if ((curBench.getRawState() >> r.getGoodsId()) & 0x01) continue;
		double moveTime = DistRPoint2RPoint(r.getPos(), curBench.getPos()) / ROBOT_MAX_FORWARDSPEED;
		double rotateTime = abs(Point2Rad(r.getPos(), curBench.getPos()) - r.getRad()) / ROBOT_MAX_ROTATESPEED;
		//double totalTime = max(moveTime, rotateTime); // ms转换到帧数
		double totalTime = moveTime;
		//if (!vBenchInfo[j].getProduceState() && totalTime > curBench.getProductTime()) continue;
		pqMinTime.push(pair<double, int>(totalTime, vTotalBenchNum[j]));
	}
	//if (r.getGoodsId() - 1 > 3) {
	//	// 按升序排列结果、选择当前最优
	//	while (!pqMinTime.empty()) {
	//		pair<double, int> tmp = pqMinTime.top();
	//		fprintf(stderr, "num:%d(%0.2f)	", tmp.second, tmp.first);
	//		pqMinTime.pop();
	//	}
	//	fprintf(stderr, "\n");
	//}
	if (pqMinTime.empty()) return -1;
	return pqMinTime.top().second;
}

//bool AvoidCollision(Robot& r, int num) {
//	for (int i = 0; i < 4; i++) {
//		if (r._2bench) continue;
//		if (i == num) continue;
//		Robot nearRobot = vRobotInfo[i];
//		double dist = DistRPoint2RPoint(r.getPos(), nearRobot.getPos());
//		if (ROBOT_SATE_DISTANCE < dist) continue;
//		// 比较两者优先级，7的优先级更高 456-》123
//
//	}
//}

// 处理当机器人是否移动到目标点
bool VerityRobot2Goal4(Robot& r, int num) {
	//fprintf(stderr, "%d\n\n\n", r._2bench);
	if (r._2bench == -1) return false; // 没有任务
	if (r.getId() != r._2bench) {
		// 机器人没有到达目标点：计算旋转、平移偏差
		Bench goal = vBenchInfo[r._2bench];
		double dist = DistRPoint2RPoint(r.getPos(), goal.getPos()); // 当前机器人和工作台距离
		double rotate = Point2Rad2(r.getPos(), goal.getPos()) - r.getRad();
		int frame = rotate * 1000 / 20 / ROBOT_MAX_ROTATESPEED;
		double speed = 0;
		double radSpd = ROBOT_MAX_ROTATESPEED;
		// 限幅，限制在-Π到Π
		if (rotate > RPI) rotate -= 2 * RPI;
		else if (rotate < -RPI) rotate += 2 * RPI;

		//if (abs(rotate) < 0.08) {
		//	//radSpd = 0.3 * ((rotate > 0 ? ROBOT_MAX_ROTATESPEED : -ROBOT_MAX_ROTATESPEED)) + 0.7 * rotate;
		//	speed = 0.8 * ROBOT_MAX_FORWARDSPEED + 0.2 * dist;
		//	radSpd = 0;
		//}
		//else {
		//	radSpd = rotate > 0 ? ROBOT_MAX_ROTATESPEED : -ROBOT_MAX_ROTATESPEED;
		//}

		speed = 0.8 * ROBOT_MAX_FORWARDSPEED + 0.2 * dist;
		radSpd = rotate > 0 ? ROBOT_MAX_ROTATESPEED : -ROBOT_MAX_ROTATESPEED;
		if (abs(rotate) < 0.08) {
			radSpd = 0;
		}
		if (dist < ROBOT_MAX_FORWARDSPEED && abs(rotate) > 0.08) {
			speed = 0;
		}

		printf("rotate %d %f\n", num, radSpd);
		printf("forward %d %f\n", num, speed);
	}
	else {
		// 到达目标
		if (r._priorityTask == 2) {
			vector<int>::iterator itr = find(notUpdateBench.begin(), notUpdateBench.end(), r._2bench);
			if (itr != notUpdateBench.end()) notUpdateBench.erase(itr); // 如果到目标就可更新当前工作台状态
			r._priorityTask = -1;
		}
		printf("rotate %d %f\n", num, 0.);
		printf("forward %d %f\n", num, 0.);
		if (r.getGoodsId()) printf("sell %d\n", num);
		else printf("buy %d\n", num);
		r._2bench = r._sell2WhichBench; // 有卖给那个工作台，机器人就继续下发下一个任务
		r._sell2WhichBench = -1;
	}
	return true;
}

int CalcFirstPrioritist7(vector<int>& v, Robot& r) {
	int numRawMaterial = 0;
	int priority7 = 0;
	//r.getGoodsId(); // 当前机器人携带原材料的数量 
	if (r.getGoodsId() - 1 != 6) {
		// 不是7号货物
		for (int i = 0; i < v.size(); i++) {
			if ((vBenchInfo[v[i]].getRawState() >> r.getGoodsId()) & 0x01) continue;
			int rawState = vBenchInfo[v[i]].getRawState();
			int rawCnt = 0;
			for (int type = 0; type < 3; type++) {
				if ((rawState >> type + 4) & 0x01) rawCnt++;
			}
			if (rawCnt >= numRawMaterial) {
				numRawMaterial = rawCnt;
				priority7 = v[i];
			}
		}
		if (numRawMaterial != 0) return priority7;
	}

	// 7号货物或7号都没有原材料-》选择最近的卖掉
	//benchNum
	// 小根堆pqMinTime
	priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pqMinTime;
	vector<int> vTotalBenchNum(v);
	for (int j = 0; j < vTotalBenchNum.size(); j++) {
		Bench curBench = vBenchInfo[vTotalBenchNum[j]];
		if ((curBench.getRawState() >> r.getGoodsId()) & 0x01) continue;
		double moveTime = DistRPoint2RPoint(r.getPos(), curBench.getPos()) / ROBOT_MAX_FORWARDSPEED;
		double rotateTime = abs(Point2Rad(r.getPos(), curBench.getPos()) - r.getRad()) / ROBOT_MAX_ROTATESPEED;
		//double totalTime = max(moveTime, rotateTime); // ms转换到帧数
		double totalTime = moveTime;
		//if (!vBenchInfo[j].getProduceState() && totalTime > curBench.getProductTime()) continue;
		pqMinTime.push(pair<double, int>(totalTime, vTotalBenchNum[j]));
	}
	//if (r.getGoodsId() - 1 > 3) {
	//	// 按升序排列结果、选择当前最优
	//	while (!pqMinTime.empty()) {
	//		pair<double, int> tmp = pqMinTime.top();
	//		fprintf(stderr, "num:%d(%0.2f)	", tmp.second, tmp.first);
	//		pqMinTime.pop();
	//	}
	//	fprintf(stderr, "\n");
	//}
	if (pqMinTime.empty()) return -1;
	return pqMinTime.top().second;
}

bool TaskIsAvailable(Robot& r) {
	// 最大帧与当前帧的差
	int diffFrame = SYS_MAX_FRAMENUM - currentFrameId;
	int needFrame = 0;
	RPoint lastPos = r.getPos();
	for (int i = 0; i < vEstimateAvailable.size(); i++) {
		if (vEstimateAvailable[i] < 0) return false;
		Bench curBench = vBenchInfo[vEstimateAvailable[i]];
		double dist = DistRPoint2RPoint(curBench.getPos(), lastPos);
		needFrame += dist * 1000 / 20 / RPI;
		lastPos = curBench.getPos();
	}
	vEstimateAvailable.clear();
	fprintf(stderr, "cur frame:%d	diff frame:%d	need frame:%d	task aviliable:%d\n", 
		currentFrameId, diffFrame, needFrame, needFrame < diffFrame);
	return needFrame < diffFrame;
}

void CalcRobot2BenchCostBase4() {
	//if (currentFrameId > 8500) return;
	for (int i = 0; i < ROBOT_NUM; i++) {
		Robot curRobot = vRobotInfo[i];
		if (VerityRobot2Goal4(vRobotInfo[i], i)) continue; // 有任务就执行任务
		if (curRobot.getGoodsId() - 1 > 2) {
			// 优先级1、判断机器人买到4567
			vector<int> vTmp;
			vector<int> allType = mBench2SubBench[curRobot.getGoodsId() - 1];
			for (int type = 0; type < allType.size(); type++) {
				//vTmp.insert(vTmp.begin(), mBenchSort[allType[type]].begin(), mBenchSort[allType[type]].end());
				for (int j = 0; j < mBenchSort[allType[type]].size(); j++) {
					vTmp.push_back(mBenchSort[allType[type]][j]);
					//fprintf(stderr, "%d	", mBenchSort[allType[type]][j]);
				}
				//fprintf(stderr, "\n");
			}
			//fprintf(stderr, "info:");
			//for (int num = 0; num < v.size(); num++) {
			//	fprintf(stderr, "%d	", v[i]);
			//}
			//fprintf(stderr, "\n");

			//int benchNum = FindLeastDist(vTmp, curRobot);
			int benchNum = CalcFirstPrioritist7(vTmp, curRobot);
			if (benchNum == -1) continue;
			//// 判断任务是否有效，在可行时间实现
			//vEstimateAvailable.emplace_back(benchNum);
			//if (TaskIsAvailable(curRobot)) vRobotInfo[i]._2bench = benchNum;
			//else break;
			vRobotInfo[i]._2bench = benchNum;
			fprintf(stderr, "priority1	beach type:%d	benchNum:%d	robot goods id\n",
				vBenchInfo[benchNum].getBenchType(),
				vBenchInfo[benchNum].getBenchType()
			);
			continue;
		}
		// 优先级2、 判断是否有4567产出
		if (vPriority4567.size() > 0) {
			fprintf(stderr, "curr priority bench:");
			for (int i = 0; i < vPriority4567.size(); i++) {
				fprintf(stderr, "%d(%d)	", vPriority4567[i], vBenchInfo[vPriority4567[i]].getBenchType());
			}
			fprintf(stderr, "\n");
			//// 判断任务是否有效，在可行时间实现
			//vEstimateAvailable.emplace_back(vPriority4567[0]);
			//if (TaskIsAvailable(curRobot)) vRobotInfo[i]._2bench = vPriority4567[0];
			//else break;
			vRobotInfo[i]._2bench = vPriority4567[0];
			vRobotInfo[i]._priorityTask = 2; // 优先级2对应任务
			vPriority4567.erase(vPriority4567.begin());
			//fprintf(stderr, "after delete curr priority bench:");
			//for (int i = 0; i < vPriority4567.size(); i++) {
			//	fprintf(stderr, "%d(%d)	", vPriority4567[i], vBenchInfo[vPriority4567[i]].getBenchType());
			//}
			fprintf(stderr, "\n");
			fprintf(stderr, "priority2	beach type:%d	bench num:%d\n",
				vBenchInfo[vPriority4567[0]].getBenchType(),
				vBenchInfo[vPriority4567[0]].getBenchNum());
			continue;
		}
		// 更新任务队列
		if (sTotalTaskUse.empty()) {
			sTotalTaskUse = stack<int>(sTotalTask);
		}
		// 绑定12 13 23任务
		while (1) {
			// 没有任务取任务
			int benchType = sTotalTaskUse.top();
			sTotalTaskUse.pop();
			if ((benchType == 5) || (benchType == 4) || (benchType == 3)) {
				tmp456Type = benchType;
				taskTotalCnt++;
				if (taskTotalCnt % 2 == 1) goalBench456 = -1;
			}
			else {
				// 针对012选择离机器人最近的一个
				goalBench123 = Sort123LevlByDist(curRobot, benchType);
				// 选好最近的工作台后，确定卖给456中最近的一个
				if (goalBench456 == -1) {
					// 当前一个已经确定生产目标后不需要在去计算目标
					goalBench456 = FindLeastDist(vmBench2SubBench[goalBench123][tmp456Type], curRobot);
				}
				//fprintf(stderr, "goal:%d	beach type:%d	sell to:%d	sell to type:%d	product to:%d\n",
				//	goalBench123, vBenchInfo[goalBench123].getBenchType(), goalBench456,
				//	vBenchInfo[goalBench456].getBenchType(), mBenchSort[6][curSevenBenchNum]);
				break;
			}
		}
		// 下达任务：记录123在哪买卖给谁，记录456工作台生产出来卖给谁
		fprintf(stderr, "priority3	goal:%d	beach type:%d	sell to:%d	sell to type:%d\n", 
			goalBench123, vBenchInfo[goalBench123].getBenchType(), goalBench456, 
			vBenchInfo[goalBench456].getBenchType());
		//// 判断任务是否有效，在可行时间实现
		//vEstimateAvailable.emplace_back(goalBench123);
		//if (TaskIsAvailable(curRobot)) vRobotInfo[i]._2bench = goalBench123;
		//else break;
		//vEstimateAvailable.emplace_back(goalBench123);
		//vEstimateAvailable.emplace_back(goalBench456);
		//if (TaskIsAvailable(curRobot)) vRobotInfo[i]._sell2WhichBench = goalBench456;
		//else break;		
		vRobotInfo[i]._2bench = goalBench123;
		vRobotInfo[i]._sell2WhichBench = goalBench456;
	}

	return;
}















/*
	当给机器人下达指令后，工作台虚拟状态置位（4567）
*/
void SetBenchGoingState(Robot& r, int num) {
	for (int j = 0; j < r._vTask.size(); j++) {
		// 工作台虚拟状态置位，只对4567工作台有效
		if (vBenchInfo[r._vTask[j]._qBench].getBenchType() > 2 &&
			vBenchInfo[r._vTask[j]._qBench].getBenchType() < 7) {
			if (r._vTask[j]._qCmd) {
				// 卖：把原材料格状态更新
				vBenchInfo[r._vTask[j]._qBench]._rawStateGoing |=
					0x01 << (vBenchInfo[r._vTask[j - 1]._qBench].getBenchType() + 1);
			}
			else {
				vBenchInfo[r._vTask[j]._qBench]._buyGoing = 1;		
			}
		}
		if (!r._vTask[j]._qCmd) {
			// 如果当前为买，记录原材料类型，方便卖时清空
			vBenchInfo[r._vTask[j + 1]._qBench]._vRawGoingLast.emplace_back(pair<int, int>(num, vBenchInfo[r._vTask[j]._qBench].getBenchType()));
		}
	}
}
/*
	当给机器人下达指令后，工作台虚拟状态置位（4567）
*/
void SetBenchGoingState2(Robot& r, int num) {
	for (int j = 0; j < r._vTask.size(); j++) {
		// 工作台虚拟状态置位，只对4567工作台有效
		if (vBenchInfo[r._vTask[j]._qBench].getBenchType() > 2 &&
			vBenchInfo[r._vTask[j]._qBench].getBenchType() < 7) {
			if (r._vTask[j]._qCmd) {
				// 卖：把原材料格状态更新
				vBenchInfo[r._vTask[j]._qBench]._rawStateGoing |=
					0x01 << (vBenchInfo[r._vTask[j - 1]._qBench].getBenchType() + 1);
			}
			else {
				vBenchInfo[r._vTask[j]._qBench]._buyGoing = 1;
			}
		}
		if (!r._vTask[j]._qCmd) {
			// 如果当前为买，记录原材料类型，方便卖时清空
			vBenchInfo[r._vTask[j + 1]._qBench]._vRawGoingLast.emplace_back(pair<int, int>(num, vBenchInfo[r._vTask[j]._qBench].getBenchType()));
		}
	}
}


/*
	当给机器人到达目标后，工作台虚拟状态复位（4567）
*/
void ResetBenchGoingState(Robot& r, int num) {
	r._radCnt = 0;
	if (!r._vTask[0]._qCmd) {
		//// 如果当前为买，记录原材料类型，方便卖时清空
		//vBenchInfo[r._vTask[1]._qBench]._vRawGoingLast.emplace_back(pair<int, int>(num, vBenchInfo[r._vTask[0]._qBench].getBenchType()));
		//vBenchInfo[r._vTask[1]._qBench]._rawStateGoingLast = vBenchInfo[r._vTask[0]._qBench].getBenchType();
		if (vBenchInfo[r._vTask[0]._qBench].getBenchType() > 2 &&
			vBenchInfo[r._vTask[0]._qBench].getBenchType() < 7) {
			vBenchInfo[r._vTask[0]._qBench]._buyGoing = 0;
		}
	}
	else {
		// 卖
		if (vBenchInfo[r._vTask[0]._qBench].getBenchType() > 2 &&
			vBenchInfo[r._vTask[0]._qBench].getBenchType() < 7) {
			// 找到对应机器人
			for (int i = 0; i < vBenchInfo[r._vTask[0]._qBench]._vRawGoingLast.size(); i++) {
				if (vBenchInfo[r._vTask[0]._qBench]._vRawGoingLast[i].first == num) {
					vBenchInfo[r._vTask[0]._qBench]._rawStateGoing &=
						(~(0x01 << (vBenchInfo[r._vTask[0]._qBench]._vRawGoingLast[i].second + 1)));
					vBenchInfo[r._vTask[0]._qBench]._vRawGoingLast.erase(i + vBenchInfo[r._vTask[0]._qBench]._vRawGoingLast.begin());
				}
			}
		}
		//{
		//	if (r._vTask.size()) {
		//		fprintf(stderr, "		reset robot info:%d task level:%d(length:%d)",
		//			num, r._tstack._level, r._vTask.size());
		//			int benchId = r._vTask[0]._qBench;
		//			fprintf(stderr, "bench id:%d(_rawStateGoing:%d	type:%d)\n\n",
		//				benchId, vBenchInfo[benchId]._rawStateGoing | vBenchInfo[benchId].getRawState(), vBenchInfo[benchId].getBenchType());
		//		
		//	}
		//}
		//while (1);
	}


	return;
}

/*
	判断机器人当前任务的合法性，是否是之前任务的耦合任务1-11(12)-11(12)-7
*/
bool VertifyBenchGoingAvailable(Robot& r, int num) {
	//fprintf(stderr, "task stack:%d\n", r._vTask.size());
	// 滤除不能在规定时间完成的任务
	double robot2First = DistRPoint2RPoint(vBenchInfo[r._vTask[0]._qBench].getPos(), r.getPos());
	if ((int)ceil((r._tstack._distance + robot2First) * 50 / 4.2) > (SYS_MAX_FRAMENUM - currentFrameId)) {
		return false;
	}

	for (int j = 0; j < r._vTask.size(); j++) {
		// 工作台虚拟状态置位，只对4567工作台有效
		if (vBenchInfo[r._vTask[j]._qBench].getBenchType() > 2 &&
			vBenchInfo[r._vTask[j]._qBench].getBenchType() < 7) {
			if (r._vTask[j]._qCmd) {
				//fprintf(stderr, "vertify bench num:%d(raw:%d,product:%d) ",
				//	r._vTask[j]._qBench, vBenchInfo[r._vTask[j]._qBench]._rawStateGoing,
				//	vBenchInfo[r._vTask[j]._qBench]._productStateGoing);
				
				int rawState = vBenchInfo[r._vTask[j]._qBench].getRawState();
				int rawStateGoing = vBenchInfo[r._vTask[j]._qBench]._rawStateGoing;
				rawStateGoing |= rawState;
				// 卖：判断当前卖给工作台的虚拟状态生产格是否有该货物
				if ((rawStateGoing >> (vBenchInfo[r._vTask[j - 1]._qBench].getBenchType() + 1)) & 0x01) {
					//fprintf(stderr, "验证任务是否可靠 err! 工作台%d冲突，有货物:%d\n",
					//	r._vTask[j]._qBench, (vBenchInfo[r._vTask[j - 1]._qBench].getBenchType() + 1));
					return false;
				}
			}
			else {
				// 买
				if (vBenchInfo[r._vTask[j]._qBench]._buyGoing == 1) {
					//// print test
					//if (vBenchInfo[r._vTask[j]._qBench].getBenchType() == 6) {
					//	fprintf(stderr, "验证任务是否可靠 err! 有机器人正在买\n");
					//}
					return false;
				}
			}
		}
	}

	if (CurrentMapNum == 2) {
		// 地图二，只让机器人走一个象限、且7、4由近的两个机器人共享
		for (int j = 0; j < r._vTask.size(); j++) {
			if (num == 0) {
				if (r._vTask[j]._qBench == 1 || r._vTask[j]._qBench == 3
					|| r._vTask[j]._qBench == 4 || r._vTask[j]._qBench == 5 || r._vTask[j]._qBench == 7
					|| r._vTask[j]._qBench == 11 || r._vTask[j]._qBench == 12) {
				}
				else {
					//fprintf(stderr, "task no legel\n");
					return false;
				}
			}
			else if (num == 1) {
				if (r._vTask[j]._qBench == 2 || r._vTask[j]._qBench == 3
					|| r._vTask[j]._qBench == 6 || r._vTask[j]._qBench == 8 || r._vTask[j]._qBench == 14) {
				}
				else {
					//fprintf(stderr, "task no legel\n");
					return false;
				}
			}
			else if (num == 2) {
				if (r._vTask[j]._qBench == 10 || r._vTask[j]._qBench == 16 || r._vTask[j]._qBench == 18
					|| r._vTask[j]._qBench == 21 || r._vTask[j]._qBench == 22 ) {
				}
				else {
					//fprintf(stderr, "task no legel\n");
					return false;
				}
			}
			else {
				if (r._vTask[j]._qBench == 12 || r._vTask[j]._qBench == 13
					|| r._vTask[j]._qBench == 17 || r._vTask[j]._qBench == 19 || r._vTask[j]._qBench == 20
					|| r._vTask[j]._qBench == 21 || r._vTask[j]._qBench == 23) {
				}
				else {
					//fprintf(stderr, "task no legel\n");
					return false;
				}
			}
			//if (num == 0) {
			//	if (/*r._vTask[j]._qBench == 0 ||*/ r._vTask[j]._qBench == 1 || r._vTask[j]._qBench == 3
			//		|| r._vTask[j]._qBench == 4 || r._vTask[j]._qBench == 5 || r._vTask[j]._qBench == 7
			//		|| r._vTask[j]._qBench == 10 || r._vTask[j]._qBench == 11 || r._vTask[j]._qBench == 12) {
			//	}
			//	else {
			//		//fprintf(stderr, "task no legel\n");
			//		return false;
			//	}
			//}
			//else if (num == 1) {
			//	if (/*r._vTask[j]._qBench == 1 ||*/ r._vTask[j]._qBench == 2 || r._vTask[j]._qBench == 3
			//		|| r._vTask[j]._qBench == 4 || r._vTask[j]._qBench == 6 || r._vTask[j]._qBench == 8
			//		|| r._vTask[j]._qBench == 12 || r._vTask[j]._qBench == 13 || r._vTask[j]._qBench == 14) {
			//	}
			//	else {
			//		//fprintf(stderr, "task no legel\n");
			//		return false;
			//	}
			//}
			//else if (num == 2) {
			//	if (r._vTask[j]._qBench == 10 || r._vTask[j]._qBench == 11 || r._vTask[j]._qBench == 12
			//		|| r._vTask[j]._qBench == 16 || r._vTask[j]._qBench == 18 || r._vTask[j]._qBench == 20
			//		|| r._vTask[j]._qBench == 21 || r._vTask[j]._qBench == 22 /*|| r._vTask[j]._qBench == 23*/) {
			//	}
			//	else {
			//		//fprintf(stderr, "task no legel\n");
			//		return false;
			//	}
			//}
			//else {
			//	if (r._vTask[j]._qBench == 12 || r._vTask[j]._qBench == 13 || r._vTask[j]._qBench == 14
			//		|| r._vTask[j]._qBench == 17 || r._vTask[j]._qBench == 19 || r._vTask[j]._qBench == 20
			//		|| r._vTask[j]._qBench == 21 || r._vTask[j]._qBench == 23 /*|| r._vTask[j]._qBench == 24*/) {
			//	}
			//	else {
			//		//fprintf(stderr, "task no legel\n");
			//		return false;
			//	}
			//}
		}
	}
	//else if (CurrentMapNum == 1) {
	//	for (int j = 0; j < r._vTask.size(); j++) {
	//		if (num == 0) {
	//			//if (r._vTask[j]._qBench == 0 || r._vTask[j]._qBench == 7 || r._vTask[j]._qBench == 26 || r._vTask[j]._qBench == 5) {}
	//			//else if (r._vTask[j]._qBench == 18 && currentFrameId > SYS_THIRD_FRAMENUM) {}
	//			//else {
	//			//	//fprintf(stderr, "task no legel\n");
	//			//	return false;
	//			//}
	//			if (r._vTask[j]._qBench == 18) {
	//				// 前8000帧不是7不卖给9
	//				if (currentFrameId < SYS_THIRD_FRAMENUM) {
	//					if (r._vTask[j - 1]._qBench == 15) return true;
	//					return false;
	//				}
	//			}
	//			else if (r._vTask[j]._qBench == 0) {
	//				if (r._vTask[j + 1]._qBench == 7 || r._vTask[j + 1]._qBench == 26 || r._vTask[j + 1]._qBench == 5) {
	//					return true;
	//				}
	//			}
	//			else if (r._vTask[j]._qBench == 15 || r._vTask[j]._qBench == 7 || r._vTask[j]._qBench == 26
	//				|| r._vTask[j]._qBench == 38 || r._vTask[j]._qBench == 5) {
	//			}
	//			else {
	//				//fprintf(stderr, "task no legel\n");
	//				return false;
	//			}
	//		}
	//		else if (num == 1) {
	//			if (r._vTask[j]._qBench == 18) {
	//				// 前8000帧不卖给9
	//				if (currentFrameId < SYS_THIRD_FRAMENUM) {
	//					if (r._vTask[j - 1]._qBench == 15) return true;
	//					return false;
	//				}
	//			}
	//			else if (r._vTask[j]._qBench == 0) {
	//				if (r._vTask[j + 1]._qBench == 7 || r._vTask[j + 1]._qBench == 26 || r._vTask[j + 1]._qBench == 5) {
	//					return true;
	//				}
	//			}
	//			else if (r._vTask[j]._qBench == 15 || r._vTask[j]._qBench == 7 || r._vTask[j]._qBench == 26
	//				|| r._vTask[j]._qBench == 38 || r._vTask[j]._qBench == 5) {
	//			}
	//			else {
	//				//fprintf(stderr, "task no legel\n");
	//				return false;
	//			}
	//		}
	//		else if (num == 2) {
	//			if (r._vTask[j]._qBench == 41 || r._vTask[j]._qBench == 26 || r._vTask[j]._qBench == 38) {}
	//			else if (r._vTask[j]._qBench == 18 && currentFrameId > SYS_THIRD_FRAMENUM) {}
	//			else {
	//				//fprintf(stderr, "task no legel\n");
	//				return false;
	//			}
	//		}
	//		else {
	//			if (r._vTask[j]._qBench == 42 || r._vTask[j]._qBench == 7 || r._vTask[j]._qBench == 38) {}
	//			else if (r._vTask[j]._qBench == 18 && currentFrameId > SYS_THIRD_FRAMENUM) {}
	//			else {
	//				//fprintf(stderr, "task no legel\n");
	//				return false;
	//			}
	//		}
	//	}
	//}
	else if (CurrentMapNum == 4) {
		//for (int j = 0; j < r._vTask.size(); j++) {
		//	if (num == 0) {
		//		if (r._vTask[j]._qBench == 0 || r._vTask[j]._qBench == 2 || r._vTask[j]._qBench == 5
		//			|| r._vTask[j]._qBench == 17 || r._vTask[j]._qBench == 16) {
		//		}
		//		else {
		//			//fprintf(stderr, "task no legel\n");
		//			return false;
		//		}
		//	}
		//	else if (num == 1) {
		//		if (r._vTask[j]._qBench == 0 || r._vTask[j]._qBench == 2 || r._vTask[j]._qBench == 5
		//			|| r._vTask[j]._qBench == 17 || r._vTask[j]._qBench == 16) {
		//		}
		//		else {
		//			//fprintf(stderr, "task no legel\n");
		//			return false;
		//		}
		//	}
		//	else if (num == 2) {
		//		if (r._vTask[j]._qBench == 0 || r._vTask[j]._qBench == 6 /*|| r._vTask[j]._qBench == 16*/
		//			|| r._vTask[j]._qBench == 9 || r._vTask[j]._qBench == 15) {
		//		}
		//		else {
		//			//fprintf(stderr, "task no legel\n");
		//			return false;
		//		}
		//	}
		//	else {
		//		if (r._vTask[j]._qBench == 0 || r._vTask[j]._qBench == 1 /*|| r._vTask[j]._qBench == 16*/
		//			|| r._vTask[j]._qBench == 7 || r._vTask[j]._qBench == 10) {
		//		}
		//		else {
		//			//fprintf(stderr, "task no legel\n");
		//			return false;
		//		}
		//	}
		//}
	}
	else if (CurrentMapNum == 3) {
		for (int j = 0; j < r._vTask.size(); j++) {
			if (num == 0) {
				if (vBenchInfo[r._vTask[j]._qBench].getPos().y > 34.5 || r._vTask[j]._qBench == 24) {}
				else return false;
			}
			else {
				if (vBenchInfoDup[r._vTask[j]._qBench].getPos().x > 24 && vBenchInfoDup[r._vTask[j]._qBench].getPos().x < 48.5
					&& vBenchInfoDup[r._vTask[j]._qBench].getPos().y > 16 && vBenchInfoDup[r._vTask[j]._qBench].getPos().y < 34) {}
				else {
					return false;
				}
			}
		}
	}

	return true;
}

// 处理当机器人是否移动到目标点
bool VerityRobot2Goa5(Robot& r, int num) {
	if (r._vTask.empty()) return false; // 没有任务
	//if (r.getId() != r._vTask[0]._qBench) {
	if (r.getId() != r._vTask[0]._qBench) {
		//fprintf(stderr, "robot %d going to target!\n", num);
		// 机器人没有到达目标点：计算旋转、平移偏差
		Bench goal = vBenchInfo[r._vTask[0]._qBench];
		double dist = DistRPoint2RPoint(r.getPos(), goal.getPos()); // 当前机器人和工作台距离
		double rotate = Point2Rad2(r.getPos(), goal.getPos()) - r.getRad();
		int frame = rotate * 1000 / 20 / ROBOT_MAX_ROTATESPEED;
		// 限幅，限制在-Π到Π
		if (rotate > RPI) rotate -= 2 * RPI;
		else if (rotate < -RPI) rotate += 2 * RPI;

//#if SYS_DEBUG
//		double radSpd = 4 * rotate;
//		double speed = param1 + param2 * (RPI - abs(r.getAngleVel())) / RPI;
//		//speed = 3.6 + 5.1 * (RPI - abs(r.getAngleVel())) / RPI;
//#else 
//		double radSpd = 4 * rotate;;
//		double speed = 0.;
//		if (CurrentMapNum == 1) {
//			radSpd = 4 * rotate;
//			//speed = 4.1 + 5.6 * (RPI - abs(r.getAngleVel())) / RPI;
//			speed = 3.6 + 5.1 * (RPI - abs(r.getAngleVel())) / RPI;
//		}
//		else if (CurrentMapNum == 2) {
//			//speed = 4.1 + 5.1 * (RPI - abs(r.getAngleVel())) / RPI;
//			//speed = 3.8 + 5.4 * (RPI - abs(r.getAngleVel())) / RPI; // 89.9
//			speed = 4.1 + 5.8 * (RPI - abs(r.getAngleVel())) / RPI; // 89.9
//		}
//		else if (CurrentMapNum == 3) {
//			//speed = 3.7 + 5.6 * (RPI - abs(r.getAngleVel())) / RPI; // 86.99
//			speed = 4.1 + 4.7 * (RPI - abs(r.getAngleVel())) / RPI; // 88.9
//		}
//		else {
//			//speed = 4.1 + 5.7 * (RPI - abs(r.getAngleVel())) / RPI; // 64.5
//			speed = 3.7 + 5.8 * (RPI - abs(r.getAngleVel())) / RPI;
//		}
//#endif
		//double radSpd = PIDAngle(num, rotate);
		//double vec = sqrt(pow(vRobotInfo[num].getLineVelx(), 2) +
		//	pow(vRobotInfo[num].getLineVely(), 2));
		//double speed = PIDLineSpeed(num, radSpd, vec);
		double speed = ROBOT_MAX_FORWARDSPEED;
		double radSpd = ROBOT_MAX_ROTATESPEED;
		radSpd = rotate > 0 ? ROBOT_MAX_ROTATESPEED : -ROBOT_MAX_ROTATESPEED;

		if (abs(rotate) < 0.08) {
			radSpd = 0;

		}
		else{
			if (CurrentMapNum != 4) {
				int mindis = 1.5;
				int middis = 2;
				int minspeed = 0.06;
				int midspeed = 0.6;

				if (r.getRad() > 0 && r.getRad() < RPI / 2) {
					if (((50 - r.getPos().y) <= mindis) || ((50 - r.getPos().x) <= mindis))
						speed = minspeed;
					else if (((50 - r.getPos().y) <= middis) || ((50 - r.getPos().x) <= middis))
						speed = midspeed;
				}
				else if (r.getRad() > RPI / 2 && r.getRad() < RPI) {
					if ((50 - r.getPos().y) <= mindis || r.getPos().x <= mindis)
						speed = minspeed;
					else if ((50 - r.getPos().y) <= middis || r.getPos().x <= middis)
						speed = midspeed;
				}
				else if (r.getRad() > -RPI && r.getRad() < -RPI / 2) {
					if (r.getPos().y <= mindis || r.getPos().x <= mindis)
						speed = minspeed;
					else if (r.getPos().y <= middis || r.getPos().x <= middis)
						speed = midspeed;
				}
				else if (r.getRad() > -RPI / 2 && r.getRad() < 0) {
					if (r.getPos().y <= mindis || (50 - r.getPos().x) <= mindis)
						speed = minspeed;
					if (r.getPos().y <= middis || (50 - r.getPos().x) <= middis)
						speed = midspeed;
				}
			}
			
		}
		if (CurrentMapNum == 4) {
			if (abs(r.getAngleVel() == 0)) {
				r._radCnt = 0;
			}
			if (abs(r.getAngleVel()) > RPI / 6.) {
				r._radCnt++;
			}
			if (r._radCnt > 80 && abs(r.getAngleVel()) > RPI / 2.5) {
				speed = 0;
				r._radCnt++;
			}
			if (r._radCnt > 100) {
				r._radCnt = 0;
			}
		}
		else {
		if (abs(r.getAngleVel() == 0)) {
			r._radCnt = 0;
		}
		if (abs(r.getAngleVel()) > RPI / 6.) {
			r._radCnt++;
		}
		if (r._radCnt > 120 && abs(r.getAngleVel()) > RPI / 2.5) {
			speed = 0;
			r._radCnt++;
		}
		if (r._radCnt > 150) {
			r._radCnt = 0;
		}

		}


		//r._lastRad = radSpd;

		printf("rotate %d %f\n", num, radSpd);
		printf("forward %d %f\n", num, speed);
	}
	else {
		//fprintf(stderr, "robot %d in target!\n", num);
		// 到达目标
		printf("rotate %d %f\n", num, 0.);
		printf("forward %d %f\n", num, 0.);
		//fprintf(stderr, "num:%d	cmd:%d\n", r._vTask[0]._qBench, r._vTask[0]._qCmd);
		if (r._vTask[0]._qCmd) printf("sell %d\n", num);
		else printf("buy %d\n", num);
		//else if (currentFrameId <= 8900) printf("buy %d\n", num);

		needResetNum.emplace_back(num);
		//	// 机器人就继续下发下一个任务
		//	ResetBenchGoingState(r);
		//	r._vTask.erase(r._vTask.begin());
	}
	return true;
}

/*
* 当优先级（小于等于8），加上机器人距离，计算单位距离收益
*/
bool SameLevelSelectMinRobot2(Robot& r, int num, priority_queue<TaskStack, vector<TaskStack>, TaskPool>& pq) {
	if (pq.empty()) return false;
	int currentLevel = 0;
	// 确定满足要求的一个任务所处的优先级
	while (1) {
		currentLevel = pq.top()._level;
		r._tstack = pq.top();
		r._vTask = pq.top()._qTaskList;
		if (VertifyBenchGoingAvailable(r, num)) break;
		pq.pop();
		if (pq.empty()) return false;
	}
	// 大根堆存放单位距离收益
	priority_queue<pair<double, int>, vector<pair<double, int>>, less<pair<double, int>>> pqMinTime;
	int stCount = 0;
	vector<TaskStack> vSameLevel = vector<TaskStack>();
	while (!pq.empty()) {
		// 当前任务
		TaskStack currTS = pq.top();
		pq.pop();
		r._tstack = currTS;
		r._vTask = currTS._qTaskList;
		if (CurrentMapNum == 1) {
			if (currentLevel != currTS._level) break;
		}
		//else if (CurrentMapNum == 2) {
		//	// 地图二，只让机器人走一个象限、且7、4由近的两个机器人共享
		//}
		else if (CurrentMapNum == 4) {
			if (currentLevel != currTS._level) break;
		}
		else {
			if (currentFrameId < SYS_THIRD_FRAMENUM) {
				if (currentLevel > TaskLevel::LEVEL3_LOWEST) {
					if (currentLevel != currTS._level) break;
				}
				else if (currTS._level <= TaskLevel::LEVEL2_LOWEST && currentLevel != TaskLevel::LEVEL2_LOWEST) break;
			}
			else {
				if (currentLevel != currTS._level) break;
			}
		}
		if (!VertifyBenchGoingAvailable(r, num)) continue;
		double dist = DistRPoint2RPoint(r.getPos(), vBenchInfo[currTS._qTaskList[0]._qBench].getPos());
		double profit = currTS._income / (dist + currTS._distance);
		pqMinTime.push(pair<double, int>(profit, stCount));
		vSameLevel.push_back(currTS);
		stCount++;
	}
	//fprintf(stderr, "当前任务数量:%d,同优先级数量:%d\n", pqMinTime.size(), vSameLevel.size());
	if (vSameLevel.empty())  return false;
	r._tstack = vSameLevel[pqMinTime.top().second];
	r._vTask = r._tstack._qTaskList;

	return true;
}

/*
* 当优先级（小于等于8），加上机器人距离，计算单位距离收益
*/
bool SameLevelSelectMinRobot3(Robot& r, int num, priority_queue<TaskStack, vector<TaskStack>, TaskPool>& pq) {
	int currentLevel = 0;
	while (1) {
		if (pq.empty()) return false;
		// 确定满足要求的一个任务所处的优先级
		while (1) {
			currentLevel = pq.top()._level;
			r._tstack = pq.top();
			r._vTask = r._tstack._qTaskList;
			if (VertifyBenchGoingAvailable(r, num)) break;
			pq.pop();
			if (pq.empty()) return false;
		}
		// 大根堆存放单位距离收益
		priority_queue<pair<double, int>, vector<pair<double, int>>, less<pair<double, int>>> pqMinTime;
		int stCount = 0;
		vector<TaskStack> vSameLevel = vector<TaskStack>();
		while (!pq.empty()) {
			// 当前任务
			TaskStack currTS = pq.top();
			pq.pop();
			r._tstack = currTS;
			r._vTask = currTS._qTaskList;
			if (currentLevel > TaskLevel::LEVEL3_LOWEST || CurrentMapNum == 4) {
				if (currTS._level != currentLevel) break;
			}
			if (currTS._level == TaskLevel::LEVEL2_LOWEST && currentLevel != TaskLevel::LEVEL2_LOWEST) break;
			if (!VertifyBenchGoingAvailable(r, num)) continue;
			double dist = DistRPoint2RPoint(r.getPos(), vBenchInfo[currTS._qTaskList[0]._qBench].getPos());
			double profit = currTS._income / (dist + currTS._distance);
			pqMinTime.push(pair<double, int>(profit, stCount));
			vSameLevel.emplace_back(currTS);
			stCount++;
		}
		
		if (!vSameLevel.empty()) {
			r._tstack = vSameLevel[pqMinTime.top().second];
			r._vTask = r._tstack._qTaskList;
			return true;
		}
		////fprintf(stderr, "当前任务数量:%d,同优先级数量:%d\n", pqMinTime.size(), vSameLevel.size());
	}
}

void CalcRobot2BenchCostBase5() {
	needResetNum.clear();
	haveTaskRobot.clear();

	for (int i = 0; i < ROBOT_NUM; i++) {
		//fprintf(stderr, "task pool num:%d\n", qTaskPool.size());
		// 当多个机器人去同一个123时，可能有的机器人没有拿到123，此时删除当前任务
		if (vRobotInfo[i].getGoodsId() == 0 && vRobotInfo[i]._vTask.size() > 0 && vRobotInfo[i]._vTask[0]._qCmd) {
			for (int j = 0; j < vRobotInfo[i]._vTask.size(); j++) {
				ResetBenchGoingState(vRobotInfo[i], i);
			}
			vRobotInfo[i]._vTask.clear();
			vRobotInfo[i]._tstack = TaskStack();
			//fprintf(stderr, "test\n");
		}
		// 判断机器人是否有任务，如果有直接执行任务
		if (VerityRobot2Goa5(vRobotInfo[i], i)) continue;
		//if (currentFrameId > 8800) continue;
		
		// 没有任务的机器人取从任务池中取任务
		// 取任务同一优先级的任务，加上机器人距离重新排序
		priority_queue<TaskStack, vector<TaskStack>, TaskPool> qTmp = qTaskPool;
		//bool ret = SameLevelSelectMinRobot(vRobotInfo[i], qTmp);
		bool ret = SameLevelSelectMinRobot2(vRobotInfo[i], i, qTmp);
		//bool ret = SameLevelSelectMinRobot3(vRobotInfo[i], i, qTmp);
		if (!ret) {
			// 没有合法任务
			vRobotInfo[i]._tstack = TaskStack();
			vRobotInfo[i]._vTask = vector<Task>();
			//if (CurrentMapNum == 4) {
			//	if (i == 0) {
			//		double rotate = Point2Rad2(vRobotInfo[i].getPos(), RPoint({ 22,38 })) - vRobotInfo[i].getRad();
			//		// 限幅，限制在-Π到Π
			//		if (rotate > RPI) rotate -= 2 * RPI;
			//		else if (rotate < -RPI) rotate += 2 * RPI;
			//		printf("rotate %d %f\n", i, rotate);
			//		printf("forward %d %f\n", i, ROBOT_MAX_FORWARDSPEED);
			//		continue;
			//	}
			//	else if (i == 1) {
			//		double rotate = Point2Rad2(vRobotInfo[i].getPos(), RPoint({ 28,38 })) - vRobotInfo[i].getRad();
			//		// 限幅，限制在-Π到Π
			//		if (rotate > RPI) rotate -= 2 * RPI;
			//		else if (rotate < -RPI) rotate += 2 * RPI;
			//		printf("rotate %d %f\n", i, rotate);
			//		printf("forward %d %f\n", i, ROBOT_MAX_FORWARDSPEED);
			//		continue;
			//	}
			//}
			//fprintf(stderr, "robot %d error: task pool have no task!\n", i);
		}

		SetBenchGoingState(vRobotInfo[i], i);
		//{
		//	if (vRobotInfo[i]._vTask.size()) {
		//		fprintf(stderr, "current robot %d task level:%d(length:%d)", 
		//			i, vRobotInfo[i]._tstack._level, vRobotInfo[i]._vTask.size());
		//		for (int j = 0; j < vRobotInfo[i]._vTask.size(); j++) {
		//			int benchId = vRobotInfo[i]._vTask[j]._qBench;
		//			fprintf(stderr, "bench id:%d(_rawStateGoing:%d	type:%d)	",
		//				benchId, vBenchInfo[benchId]._rawStateGoing, vBenchInfo[benchId].getBenchType());
		//		}
		//		fprintf(stderr, "\n");
		//	}
		//}
	}

	// 最后更新虚拟状态
	for (int i = 0; i < needResetNum.size(); i++) {
		// 机器人就继续下发下一个任务
		ResetBenchGoingState(vRobotInfo[needResetNum[i]], needResetNum[i]);
		vRobotInfo[needResetNum[i]]._vTask.erase(vRobotInfo[needResetNum[i]]._vTask.begin());
	}
}

////判断两个机器人是否会相撞
//void RobotCollosion(Robot& r1, Robot& r2, int num1, int num2)
//{
//	double dist = DistRPoint2RPoint(r1.getPos(), r2.getPos());
//	double rotate = abs(abs(r1.getRad() - r2.getRad()) - RPI);
//	if (dist < 2) {
//		if (rotate < 0.08) {
//			//printf("forward %d %f\n", num1, 0.);
//			printf("rotate %d %f\n", num1, ROBOT_MAX_ROTATESPEED);
//			//printf("forward %d %f\n", num2, 0.);
//			printf("rotate %d %f\n", num2, -ROBOT_MAX_ROTATESPEED);
//		}
//	}
//}
bool RobotCollosionCorner(Robot& r1, Robot& r2, int num1, int num2)
{
	//int middis = 5;
	if ((!r1._vTask.empty()) && (!r2._vTask.empty())) {
		int mindis = 3.5;
		double minspeed = 0.85;
		Bench goal = vBenchInfo[r1._vTask[0]._qBench];
		double dist = DistRPoint2RPoint(r1.getPos(), goal.getPos()); // 当前机器人和工作台距离
		if (goal.getPos().y < 1 && goal.getPos().x < 1 && dist < mindis) {
			if (r2.getPos().x < mindis && r2.getPos().y < mindis) {
				printf("forward %d %f\n", num1, minspeed);
				return true;
				//if(distRobot<2&& rotateRobot>RPI/2)
				//	printf("rotate %d %f\n", num2, RPI);
			}
		}
		if (goal.getPos().y < 1 && (50 - goal.getPos().x) < 1 && dist < mindis) {
			if ((50 - r2.getPos().x) < mindis && r2.getPos().y < mindis) {
				printf("forward %d %f\n", num1, minspeed);
				return true;
			}
		}
		if ((50 - goal.getPos().y) < 1 && dist < mindis) {
			if ((50 - r2.getPos().x) < mindis && r2.getPos().y < mindis) {
				printf("forward %d %f\n", num1, minspeed);
				return true;
			}
		}

	}
	return false;
}
void IsRobotCollosionCorner()
{
	for (int i = 0; i < ROBOT_NUM; i++) {
		for (int j = i + 1; j < ROBOT_NUM; j++) {
			if (j != i) {
				if (RobotCollosionCorner(vRobotInfo[i], vRobotInfo[j], i, j))
					continue;
				else RobotCollosionCorner(vRobotInfo[j], vRobotInfo[i], j, i);
			}
		}
	}
}

void RobotCollosion(Robot& r1, Robot& r2, int num1, int num2)
{
	double dist = DistRPoint2RPoint(r1.getPos(), r2.getPos());
	double rotate = abs(abs(r1.getRad() - r2.getRad()) - RPI);
	double rotateDir = Point2Rad2(r1.getPos(), r2.getPos()) - r1.getRad();
	if (rotateDir > RPI) rotateDir -= 2 * RPI;
	else if (rotateDir < -RPI) rotateDir += 2 * RPI;
	//if (CurrentMapNum == 1) {
	//	if (dist < 1.1) {
	//		if (rotate < RPI / 2)
	//			//printf("forward %d %f\n", num1, 0.);
	//			printf("rotate %d %f\n", num1, rotateDir > 0 ? -RPI : RPI);
	//	}
	//	else if (dist < 2) {
	//		if (rotate < RPI / 6.) {
	//			printf("rotate %d %f\n", num1, rotateDir > 0 ? -RPI : RPI);
	//		}
	//	}
	//}
	if (CurrentMapNum == 4) {
	if(dist < 2) {
		if (rotate < RPI / 6.)
			printf("rotate %d %f\n", num1, rotateDir > 0 ? -RPI : RPI);
	}
	}
	else {
		if (dist < 2) {
			if (rotate < RPI / 8.)
				printf("rotate %d %f\n", num1, rotateDir > 0 ? -RPI : RPI);
		}
	}
}
void IsRobotCollosion()
{
	for (int i = 0; i < ROBOT_NUM; i++) {
		for (int j = i + 1; j < ROBOT_NUM; j++) {
			if (j != i)
				RobotCollosion(vRobotInfo[i], vRobotInfo[j], i, j);
			else continue;
		}
	}

	if (CurrentMapNum == 4) {
		for (int i = 0; i < ROBOT_NUM; i++) {
			for (int j = i + 1; j < ROBOT_NUM; j++) {
				double relative_speedTotal = sqrt(pow(vRobotInfo[j].getLineVely() - vRobotInfo[i].getLineVely(), 2) +
					pow(vRobotInfo[j].getLineVelx() - vRobotInfo[i].getLineVelx(), 2));
				double angle_relative_speed = atan2(vRobotInfo[j].getLineVely() - vRobotInfo[i].getLineVely(),
					vRobotInfo[j].getLineVelx() - vRobotInfo[i].getLineVelx());//相对速度角度
				double distTotal = DistRPoint2RPoint(vRobotInfo[i].getPos(), vRobotInfo[j].getPos());
				double crash_time = (distTotal - 0.53 - 0.53) / relative_speedTotal;//碰撞时间计算
				double angle_pos = atan2(vRobotInfo[i].getPos().y - vRobotInfo[j].getPos().y, vRobotInfo[j].getPos().x - vRobotInfo[i].getPos().x);//this为原点，机器人角度
				double angle_range = asin((0.53 + 0.53) / distTotal);//碰撞角度范围
				double angle_other_relative_speed = atan2(-vRobotInfo[j].getLineVely(), -vRobotInfo[j].getLineVelx());
				double angle_other_speed_pos = angle_pos - angle_other_relative_speed;
				if (angle_other_speed_pos > RPI) {
					angle_other_speed_pos -= 2 * RPI;
				}
				else if (angle_other_speed_pos < -RPI) {
					angle_other_speed_pos += 2 * RPI;
				}
				if (relative_speedTotal > 5.6 && crash_time < 0.2 && abs(abs(vRobotInfo[i].getRad() - vRobotInfo[j].getRad()) - RPI) > RPI / 4
					&& abs(abs(vRobotInfo[i].getRad() - vRobotInfo[j].getRad()) - RPI) < RPI / 1.7)
				{
					if (vRobotInfo[j]._crashState == 0)
					{
						if (abs(angle_other_speed_pos) > angle_range)
						{
							vRobotInfo[i]._crashState = 1;
							printf("forward %d %f\n", i, 0.);
						}
					}
					else {
						vRobotInfo[j]._crashState = 0;
					}
				}
			}
		}
	}
}










//////////////////////////////////////////////////////////贪心
bool VerityRobot2Goa6(Robot& r, int num) {
	if (r._vTask.empty()) return false; // 没有任务
	if (r.getId() != r._vTask[0]._qBench) {
		// 机器人没有到达目标点：计算旋转、平移偏差
		Bench goal = vBenchInfo[r._vTask[0]._qBench];
		double dist = DistRPoint2RPoint(r.getPos(), goal.getPos()); // 当前机器人和工作台距离
		double rotate = Point2Rad2(r.getPos(), goal.getPos()) - r.getRad();
		int frame = rotate * 1000 / 20 / ROBOT_MAX_ROTATESPEED;
		double speed = ROBOT_MAX_FORWARDSPEED;
		double radSpd = ROBOT_MAX_ROTATESPEED;
		// 限幅，限制在-Π到Π
		if (rotate > RPI) rotate -= 2 * RPI;
		else if (rotate < -RPI) rotate += 2 * RPI;

		radSpd = rotate > 0 ? ROBOT_MAX_ROTATESPEED : -ROBOT_MAX_ROTATESPEED;
		if (abs(rotate) < 0.08) {
			radSpd = 0;
		}
		else {
			int mindis = 1.5;
			int middis = 2;
			int minspeed = 0.06;
			int midspeed = 0.6;

			if (r.getRad() > 0 && r.getRad() < RPI / 2) {
				if (((50 - r.getPos().y) <= mindis) || ((50 - r.getPos().x) <= mindis))
					speed = minspeed;
				else if (((50 - r.getPos().y) <= middis) || ((50 - r.getPos().x) <= middis))
					speed = midspeed;
			}
			else if (r.getRad() > RPI / 2 && r.getRad() < RPI) {
				if ((50 - r.getPos().y) <= mindis || r.getPos().x <= mindis)
					speed = minspeed;
				else if ((50 - r.getPos().y) <= middis || r.getPos().x <= middis)
					speed = midspeed;
			}
			else if (r.getRad() > -RPI && r.getRad() < -RPI / 2) {
				if (r.getPos().y <= mindis || r.getPos().x <= mindis)
					speed = minspeed;
				else if (r.getPos().y <= middis || r.getPos().x <= middis)
					speed = midspeed;
			}
			else if (r.getRad() > -RPI / 2 && r.getRad() < 0) {
				if (r.getPos().y <= mindis || (50 - r.getPos().x) <= mindis)
					speed = minspeed;
				if (r.getPos().y <= middis || (50 - r.getPos().x) <= middis)
					speed = midspeed;
			}

		}
		//if (ROBOT_MAX_ROTATESPEED / 2 > abs(r._lastRad - radSpd) && abs(radSpd) > ROBOT_MAX_ROTATESPEED / 2) {
		//	r._radCnt++;
		//	if (r._radCnt >= 50) {
		//		printf("forward %d %f\n", num, 0.);
		//		r._radCnt = 0;
		//		r._lastRad = radSpd;
		//		fprintf(stderr, "------------------\n");
		//		return true;
		//	}
		//}
		//else {
		//	r._radCnt = 0;
		//}
		//r._lastRad = radSpd;
	
		printf("rotate %d %f\n", num, radSpd);
		printf("forward %d %f\n", num, speed);
	}
	else {
		// 到达目标
		printf("rotate %d %f\n", num, 0.);
		printf("forward %d %f\n", num, 0.);
		//fprintf(stderr, "num:%d	cmd:%d\n", r._vTask[0]._qBench, r._vTask[0]._qCmd);
		if (r._vTask[0]._qCmd) printf("sell %d\n", num);
		else printf("buy %d\n", num);
		//else if (currentFrameId <= 8900) printf("buy %d\n", num);

		needResetNum6.emplace_back(num);
		//	// 机器人就继续下发下一个任务
		//	ResetBenchGoingState(r);
		//	r._vTask.erase(r._vTask.begin());
	}
	return true;
}

// 单位位移利润+潜在价值（4567）
void CalcRobot2BenchCostBase6(int mode) {
	needResetNum.clear();
	for (int i = 0; i < ROBOT_NUM; i++) {
		// 当多个机器人去同一个123时，可能有的机器人没有拿到123，此时删除当前任务
		if (vRobotInfo[i].getGoodsId() == 0 && vRobotInfo[i]._vTask.size() > 0 && vRobotInfo[i]._vTask[0]._qCmd) {
			for (int j = 0; j < vRobotInfo[i]._vTask.size(); j++) {
				ResetBenchGoingState(vRobotInfo[i], i);
			}
			vRobotInfo[i]._vTask.clear();
			vRobotInfo[i]._tstack = TaskStack();
			//fprintf(stderr, "test\n");
		}
		if (VerityRobot2Goa5(vRobotInfo[i], i)) continue; // 有任务就执行任务
		//if (currentFrameId > 8800) continue;

		priority_queue<pair<double, int>, vector<pair<double, int>>, less<pair<double, int>>> pqMaxProfit;
		int aviliableCnt = 0;
		vector<TaskStack> vAviliabelTask;
		// 选择单位距离收益+潜在收益最高任务
		for (int bench = 0; bench < vBenchInfo.size(); bench++) {
			int currBenchType = vBenchInfo[bench].getBenchType();
			if ((currBenchType > 2 && currBenchType < 7 && vBenchInfo[bench].getProduceState() && !vBenchInfo[bench]._buyGoing)
				|| (vBenchInfo[bench].getBenchType() < 3)) {
				// 能够买，看能不能卖
				vector<int> vSubType = mBench2SubBench[currBenchType];
				for (int type = 0; type < vSubType.size(); type++) {
					vector<int> vSubBenchNum = mBenchSort[vSubType[type]];
					for (int subBench = 0; subBench < vSubBenchNum.size(); subBench++) {
						int rawState = vBenchInfo[vSubBenchNum[subBench]].getRawState()
							| vBenchInfo[vSubBenchNum[subBench]]._rawStateGoing;
						if (((rawState >> (vBenchInfo[bench].getBenchType() + 1)) & 0x01) == 0
							|| (vBenchInfo[bench].getBenchType() == 6)) {
							// 买的类型能卖，计算收益
							double profit = 0.0;
							double distance = 0.0;
							profit = mMaxProfit[vBenchInfo[bench].getBenchType()];
							if (vBenchInfo[vSubBenchNum[subBench]].getRawState()) {
								profit += 1750;
							}
							distance += DistRPoint2RPoint(vRobotInfo[i].getPos(), vBenchInfo[bench].getPos());
							distance += DistRPoint2RPoint(vBenchInfo[bench].getPos(), vBenchInfo[vSubBenchNum[subBench]].getPos());
							if ((int)ceil(50 * distance / 4.2) > (SYS_MAX_FRAMENUM - currentFrameId)) continue;
							if (mode == 0) {
								pqMaxProfit.push(pair<double, int>(1 / distance, aviliableCnt));
							}
							else {
								pqMaxProfit.push(pair<double, int>(profit / distance, aviliableCnt));
							}
							TaskStack ts;
							ts._distance = distance;
							ts._income = profit;
							ts._qTaskList.emplace_back(Task({ bench, 0 }));
							ts._qTaskList.emplace_back(Task({ vSubBenchNum[subBench], 1 }));
							vAviliabelTask.emplace_back(ts);
							aviliableCnt++;
						}
					}
				}
			}
		}

		if (vAviliabelTask.empty()) {
			// 没有合法任务
			vRobotInfo[i]._tstack = TaskStack();
			vRobotInfo[i]._vTask = vector<Task>();
			//fprintf(stderr, "error: task pool have no task!\n");
		}
		else {
			//while (!pqMaxProfit.empty()) {
			//	double remain = (SYS_MAX_FRAMENUM - (double)currentFrameId) * 6. / 50. - 3.;
			//	if (remain > vAviliabelTask[pqMaxProfit.top().second]._distance) {
					vRobotInfo[i]._tstack = vAviliabelTask[pqMaxProfit.top().second];
					vRobotInfo[i]._vTask = vAviliabelTask[pqMaxProfit.top().second]._qTaskList;
			//		break;
			//	}
			//	else {
			//		pqMaxProfit.pop();
			//	}
			//}
		}

		SetBenchGoingState(vRobotInfo[i], i);
		//{
		//	if (vRobotInfo[i]._vTask.size()) {
		//		fprintf(stderr, "current robot %d task level:%d(length:%d)", 
		//			i, vRobotInfo[i]._tstack._level, vRobotInfo[i]._vTask.size());
		//		for (int j = 0; j < vRobotInfo[i]._vTask.size(); j++) {
		//			int benchId = vRobotInfo[i]._vTask[j]._qBench;
		//			fprintf(stderr, "bench id:%d(_rawStateGoing:%d	type:%d)	",
		//				benchId, vBenchInfo[benchId]._rawStateGoing, vBenchInfo[benchId].getBenchType());
		//		}
		//		fprintf(stderr, "\n");
		//	}
		//}
	}

	// 最后更新虚拟状态
	for (int i = 0; i < needResetNum.size(); i++) {
		// 机器人就继续下发下一个任务
		ResetBenchGoingState(vRobotInfo[needResetNum[i]], needResetNum[i]);
		vRobotInfo[needResetNum[i]]._vTask.erase(vRobotInfo[needResetNum[i]]._vTask.begin());
	}
	return;
}

