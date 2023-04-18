goto start
C:
cd C:\Users\Administrator
activate
Pause
conda activate Env_HUAWEI
D:
cd D:\WindowsDup\ÈíÌô\²Î¿¼\WindowsRelease
cd ../
cd ./test

g++ -E main.cpp -I ./ -o main.i 
g++ -S main.i -o main.s
g++ -c main.s -o main.o
g++ main.o -o main 
g++ -E main.cpp Bench.cpp data.cpp robot.cpp  -o main.i 
g++ -S main.i -o main.s
g++ -c main.s -o main.o
g++ main.o -o main 

:start
g++ -c Bench.cpp
g++ -c data.cpp
g++ -c robot.cpp
g++ -c Task.cpp
g++ -c mAlgorithm.cpp
g++ -c main.cpp

g++ -o  main.exe main.o Bench.o robot.o data.o Task.o mAlgorithm.o
cd ../
robot_gui.exe "test/main.exe"   -m maps/1.txt
pause