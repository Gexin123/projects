#include "header.h"

bool readMapInfoUntilOK() {
    int robotId = 0;
    int rowIndex = 0;
    char line[1024];
    while (fgets(line, sizeof line, stdin)) {
        if (line[0] == 'O' && line[1] == 'K') {
            return true;
        }
        //do something
        string sTmp(line);
        int len = strlen(line);
        remove(sTmp.begin(), sTmp.end(), ' ');
        //fprintf(stderr, "%d\n", len);
        //fprintf(stderr, "%s\n", sTmp.c_str());
        if (len > 100) {
            for (int j = 0; j < 100; j++) {
                RPoint nowPos = RPoint{ (double)j, (double)rowIndex };
                RPoint actualPos = Pos2Actual(nowPos);
                if (sTmp[j] == '.') continue;
                else if (sTmp[j] == 'A') {
                    Robot r(-1, actualPos.x, actualPos.y, 0, 0, 0, 0, 0, 0, 0);
                    vRobotInfo[robotId] = r;
                    robotId++;
                    //PID_init(r.radPid);
                }
                else {
                    Bench bench(actualBenchNum, sTmp[j] - '1', actualPos.x, actualPos.y, -1, 0, 0);
                    vBenchInfoDup[actualBenchNum] = bench;
                    actualBenchNum++;
                }
            }
            rowIndex++;
        }
    }
    return false;
}

bool readFrameInfoUntilOK() {
    int rowIndex = 0;
    vector<string> vTmp;
    char line[1024];
    while (fgets(line, sizeof line, stdin)) {
        if (line[0] == 'O' && line[1] == 'K') {
            // 更新数据
            UpdataInfo(vTmp);
            return true;
        }
        // 保存数据
        vTmp.emplace_back(string(line));
        //fprintf(stderr, "%s\n", line);
    }
    return false;
}

int main(int argc, char* argv[]) {
#if SYS_DEBUG
    param1 = atoi(argv[1]) / 100.;
    param2 = atoi(argv[2]) / 100.;
    mapNum = string(argv[3]);
    fprintf(stderr, "Hello World...\npara num :%d ", argc);
    for (int i = 0; i < argc; i++) {
        fprintf(stderr, "%s ", argv[i]);
    }
    //angleKp = param1;
    //angleKd = param2;
    fprintf(stderr, "\n");
    fprintf(stderr, "parm1:%0.2f, parm2:%0.2f\n", param1, param2);
#endif

    //Sleep(15000);

    readMapInfoUntilOK();

    //PrintRobotInfo();
    //PrintBenchInfo();
    puts("OK\n");
    fflush(stdout);

    SysInit();

    if (mBenchSort[0].size() == 1 && mBenchSort[1].size() == 1 && mBenchSort[2].size() == 1) {
        //// 地图1：一个1、2、3
        //fprintf(stderr, "------------map1-----------------------\n");
        //for (int i = 0; i < actualBenchNum; i++) {
        //    vValidBenchNum.emplace_back(i);
        //}
        vValidBenchNum.emplace_back(0); // 1
        vValidBenchNum.emplace_back(41); // 2
        vValidBenchNum.emplace_back(42); // 3
        vValidBenchNum.emplace_back(26); // 4
        vValidBenchNum.emplace_back(7); // 5
        vValidBenchNum.emplace_back(38); // 6
        //vValidBenchNum.emplace_back(26); // 4
        //vValidBenchNum.emplace_back(27); // 4
        //vValidBenchNum.emplace_back(7); // 5
        //vValidBenchNum.emplace_back(8); // 5
        //vValidBenchNum.emplace_back(38); // 6
        //vValidBenchNum.emplace_back(39); // 6
        vValidBenchNum.emplace_back(15); // 7
        //vValidBenchNum.emplace_back(17); // 7
        //vValidBenchNum.emplace_back(34); // 4
        //vValidBenchNum.emplace_back(5); // 5
        //vValidBenchNum.emplace_back(26); // 6
        //vValidBenchNum.emplace_back(17); // 7
        //vValidBenchNum.emplace_back(14); // 9
        vValidBenchNum.emplace_back(18); // 9
        CurrentMapNum = 1;
    }    
    else if (mBenchSort[6].size() == 2 && mBenchSort[7].size() == 2) {
        // 地图2：两个7、8（删除两侧的5）
        fprintf(stderr, "------------map2-----------------------\n");
        for (int i = 0; i < actualBenchNum; i++) {
            //if (i == 9 || i == 15) continue;
            vValidBenchNum.emplace_back(i);
        }
        CurrentMapNum = 2;
    }
    else if (mBenchSort[6].size() == 0) {
        // 地图3：没有7
        fprintf(stderr, "------------map3-----------------------\n");
        for (int i = 0; i < actualBenchNum; i++) {
            //if (vBenchInfoDup[i].getPos().x > 24 && vBenchInfoDup[i].getPos().x < 48.5
            //   && vBenchInfoDup[i].getPos().y > 16 && vBenchInfoDup[i].getPos().y < 34) {
            //    vValidBenchNum.emplace_back(i);
            //}
            vValidBenchNum.emplace_back(i);
        }
        CurrentMapNum = 3;
    }
    else {
        fprintf(stderr, "------------map4-----------------------\n");
        for (int i = 0; i < actualBenchNum; i++) {
            vValidBenchNum.emplace_back(i);
        }
        CurrentMapNum = 4;
    }

    //int frame = 0;
    while (scanf("%d", &currentFrameId) != EOF) {
        if (vBenchInfo.size()) {
            for (int i = 0; i < vValidBenchNum.size(); i++) {
                vBenchInfoDup[vValidBenchNum[i]] = vBenchInfo[i]; // 读取有效编号的机器人信息
            }
        }

        //fprintf(stderr, "frame id:%d\n", currentFrameId);
        readFrameInfoUntilOK();
        //PrintRobotInfo();
        //PrintBenchInfo();

#if SYS_DEBUG
        {
            // 保存训练收益
            if (currentFrameId == 8999) {
                fprintf(stderr, "money:%d\n", profitMoney);
                fstream fs(string(savePath + mapNum + ".txt"), ios::app | ios::out);
                fs << mapNum << "	" << param1 << "	" << param2 << "	" << profitMoney << endl;
                fs.close();
            }
        }
#endif

        // 清空之前的任务 
        priority_queue<TaskStack, vector<TaskStack>, TaskPool> qEmpty;
        qTaskPool.swap(qEmpty);
        //for (int i = 0; i < 1; i++) {
        for (int i = 0; i < vBenchInfo.size(); i++) {
            //fprintf(stderr, "-------------bench num:%d\n", i);
            TaskStack st;
            CreateMyTaskQueue(i, st, 0, -1);
        }
        //PrintTaskPoolInfo();

        printf("%d\n", currentFrameId);

        CalcRobot2BenchCostBase5();
        //if(CurrentMapNum==1)
        //    IsRobotCollosionCorner();
        IsRobotCollosion();

        //if (CurrentMapNum == 1) {
        //    for (int i = 0; i < ROBOT_NUM; i++) {
        //        for (int j = i + 1; j < ROBOT_NUM; j++) {
        //            double relative_speedTotal = sqrt(pow(vRobotInfo[j].getLineVely() - vRobotInfo[i].getLineVely(), 2) +
        //                pow(vRobotInfo[j].getLineVelx() - vRobotInfo[i].getLineVelx(), 2));
        //            double angle_relative_speed = atan2(vRobotInfo[j].getLineVely() - vRobotInfo[i].getLineVely(),
        //                vRobotInfo[j].getLineVelx() - vRobotInfo[i].getLineVelx());//相对速度角度
        //            double distTotal = DistRPoint2RPoint(vRobotInfo[i].getPos(), vRobotInfo[j].getPos());
        //            double crash_time = (distTotal - 0.53 - 0.53) / relative_speedTotal;//碰撞时间计算
        //            double angle_pos = atan2(vRobotInfo[i].getPos().y - vRobotInfo[j].getPos().y, vRobotInfo[j].getPos().x - vRobotInfo[i].getPos().x);//this为原点，机器人角度
        //            double angle_range = asin((0.53 + 0.53) / distTotal);//碰撞角度范围
        //            double angle_other_relative_speed = atan2(-vRobotInfo[j].getLineVely(), -vRobotInfo[j].getLineVelx());
        //            double angle_other_speed_pos = angle_pos - angle_other_relative_speed;
        //            if (angle_other_speed_pos > RPI) {
        //                angle_other_speed_pos -= 2 * RPI;
        //            }
        //            else if (angle_other_speed_pos < -RPI) {
        //                angle_other_speed_pos += 2 * RPI;
        //            }
        //            if (relative_speedTotal > 5.6 && crash_time < 0.2 && abs(abs(vRobotInfo[i].getRad() - vRobotInfo[j].getRad()) - RPI) > RPI / 4
        //                && abs(abs(vRobotInfo[i].getRad() - vRobotInfo[j].getRad()) - RPI) < RPI / 1.7)
        //            {
        //                if (vRobotInfo[j]._crashState == 0)
        //                {
        //                    if (abs(angle_other_speed_pos) > angle_range)
        //                    {
        //                        vRobotInfo[i]._crashState = 1;
        //                        printf("forward %d %f\n", i, 0.);
        //                    }
        //                }
        //                else {
        //                    vRobotInfo[j]._crashState = 0;
        //                }
        //            }
        //        }
        //    }
        //}

        printf("OK\n");
        fflush(stdout);
    }

    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
