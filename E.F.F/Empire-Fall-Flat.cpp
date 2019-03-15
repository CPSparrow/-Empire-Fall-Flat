﻿// Empire-Fall-Flat.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

/////////////////////////////////////////////////////////////
/*info[0]是年龄，info[1]是健康，info[2]是宗教，info[3]是权力，
info[4]是金钱，info[5]是军队，info[6]是改造进度。*///////////
/////////////////////////////////////////////////////////////

//玩家信息,包括年龄、健康、宗教、权力、金钱，军队
short info[7];

//游戏的事件（用于判断是否已经发生过)
int allCards[];

//判断输入是否有误，1为错误
bool isCorret = 1;

//信息初始化
void set() {
	info[0] = 18;
	for (int i = 1; i <= 5; i++) {
		info[i] = 50;
	}
	info[6] = -1;
}
//开始隐藏关卡
void setHidden() {

}

int inPut() {
	char a;
	fflush(stdin);
	scanf("%c", &a);
	fflush(stdin);
	if (a == 'n' || a == 'N') {
		return 1;
	}
	else if (a == 'y' || a == 'Y') {
		return 0;
	}
	else {
		return -1;
	}
}
//输出年龄、健康、宗教、权力、金钱，军队；作为界面
void putInfo() {
	printf("Age:%d   Health：%d   Religion:%d   Power:%d   Money:%d   Armey:%d",
		info[0], info[1], info[2], info[3], info[4], info[5]);
	if (info[6] >= 0) {
		printf("   社会改造进度:%d%%\n\n\n", info[6]);
	}
	else {
		printf("\n\n\n");
	}
}
//开始游戏（初始界面）
void gaOpen() {
	for (;;) {
		printf("你要开始一个新游戏吗?\n\n");
		printf("1:是的，我已经有了存档	(Y)\n");
		printf("2:不，我要重新开始	(N)\n");
		if (inPut() == 0) {
			printf("游戏启动中，请稍后...\n");
			Sleep(1500);
			break;
		}
		else if (inPut() == 1) {
			printf("抱歉，检测到你的智商已欠费，正在自动开启新游戏...\n");
			Sleep(1500);
			break;
		}
		else {
			isCorret = 1;
			break;
		}
		system("cls");
	}
}
//恶搞老头
void old() {
	int a[9] = { 01234567 };
	for (int i = 1; i <= 7; i++) {
		system("cls");
		putInfo();
		printf("宰相%d：\n皇上，您已经%d岁了，管理朝政之际是否该休息下？\n\n", a[i], info[0]);
		printf("1:这可不必\n\n");
		printf("2:爱卿言之极是\n");
		if (inPut() == 0 && i == 1) {
			printf("\n（你在%d岁时退位了，你的长子成为了国王,而你也善终了）\n",info[0]);
			info[1] = 0;
			break;
		}
		else if (inPut() == 0) {
			printf("\n（虽然你同意退位，但你的次子等不下去了，发动了宫廷政变，你被士兵杀死了）");
			info[4] += 2;
			info[3] -= 20;
			info[1] = 0;
			break;
		}
		else if (inPut() == 1) {
			printf("\n(宰相%c离开了，他的尸体次日在家中被发现)\n",a[i]);
			info[2] -= 3;
			info[4] -= 3;
			continue;
		}
		else if (inPut() == 1 && i == 6) {
			printf("\n（虽然你不同意退位，但你的次子等不下去了，发动了宫廷政变，你被愤怒的公立保安杀死了）\n");
			info[3] -= 3;
			info[4] += 7;
			info[5] -= 2;
			if (info[6] == -1) {
				Sleep(3000);
				printf("\n(非常感谢你选择了一种如此与众不同且脑残的死法，\n)");
				Sleep(1500);
				printf("感谢你对本游戏的支持，\n");
				Sleep(1500);
				printf("现在你得到了奖赏，\n");
				Sleep(1500);
				if (info[6] == -1) {
					printf("现在你开启了隐形关卡，");
					Sleep(1500);

					printf("请开始改造你的王国吧，祝你好运，\n");
					Sleep(1500);
					printf("(你收到了来自Handsome 老万的礼物：10%%的社会改造进度)");
				}
				else {

				}
			}
			info[1] = 0;
		}
	}
}
//每一回合的微调
void eachPa() {	
	if (info[0] > 60) {
		old();
	}
	else {
		srand(time(0));
		int a = rand();
		a %= 2;
		if (a == 0) {
			srand(time(0));
			a = rand();
			a %= 6;
			if (a == 0) {
				a = 6;
			}
			info[0] += a;
		}															//有50%的可能会让岁数随机增加
		for (int i = 1; i <= 5; i++) {
			if (info[i] >= 75) {
				info[i] += 2;
			}
			else if (info[i] <= 30) {
				info[i] -= 1;
			}
		}															//让数据大的变大，小的变小
	}
}

void wroIn() {														//输错必须死

}

void play() {
	putInfo();
	eachPa();
	int i1 = 0;
	int i2 = 0;
	srand(time(0));
	int card = rand() % 100;										//选择事件
	for (;;) {
		if (i1 == card) {
			break;
		}
		else {
			if (allCards[i2] == 1) {
				i1++;
				i2++;
			}
			else {
				i2++;
			}
		}
	}
	switch (i2)
	{
	case 0:
		putInfo();
		printf("大师章：\n陛下，来和我一起学剑法吧。\n");
		printf("1：可以考虑		(y)\n\n");
		printf("2：你给我滚吧！	(n)\n\n");
		if (inPut() == 0) {
			printf("（你学习了高级剑法）\n");
			info[1] += 10;
			info[4] -= 7;
		}
		else if (inPut() == 1) {
			printf("\n(大师章很生气，后果很严重,不久你的皇宫遭到了攻击)\n");
			info[3] -= 3;
			info[4] -= 5;
		}
		else {
			wroIn();
		}
	default:
		break;
	}
}

void putFinal() {											//游戏总结，把关闭程序也包括在里面

}

int main()
{
	set();
	gaOpen();												//游戏开始界面
	for (;;) {
		play();												//进行游戏，直到结束
	}
	putFinal();												//游戏总结，把关闭程序也包括在里面
	return 0;
}

