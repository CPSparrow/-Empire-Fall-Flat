// Empire-Fall-Flat.cpp: 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <stdio.h>

#define debug

//num有多大，卡片就有多大 
#define num (1)

////////////////////////////////////////////////
/*info[0]是年龄，info[1]是生命，info[2]是宗教，/
info[3]是金钱，info[5]是军队*///////////////////
////////////////////////////////////////////////

//玩家信息,包括年龄、生命、宗教、金钱，军队
short info[5]= {18,50,50,50,50};

//游戏的事件（用于判断是否已经发生过)
short cards[2];

//还有多少卡片
short rest = num;

//判断输入是否有误，1为错误
bool isW = 1;

struct {
	char name[];
	char senten[];
	char yes[];
	char no[];
	short depend;
	short infl[2][4];
} block[num]/*= {
	{
		"man1","say1","yes1","no1",-1,{1,1,1,1},{-1,-1,-1,-1}
	}
	{
		"man2","say2","yes2","no2",-1,{1,1,1,1},{-1,-1,-1,-1}
	}
}*/;

//信息初始化
void set() {
	info[0] = 18;
	for (int i = 1; i <= 5; i++) {
		info[i] = 50;
	}
	info[6] = -1;
	for (int i = 1; i <= num; i++) {
		cards[i] = i;
	}
}
//隐藏关卡
void setHidden() {

}

int inPut() {
	char a;
	fflush(stdin);
	scanf("%c", &a);
	fflush(stdin);
	if (a == 'n' || a == 'N') {
		return 1;
	} else if (a == 'y' || a == 'Y') {
		return 0;
	} else {
		return -1;
	}
}
//输出年龄、健康、宗教、权力、金钱，军队；作为界面顶端
void putInfo() {
	printf("年龄:%-9d健康:%-9d宗教:%-9d权力:%-9d金钱:%-9d军队:%d",
	       info[0], info[1], info[2], info[3], info[4], info[5]);
	printf("\n\n\n");
}
//开始游戏（初始界面）
void open() {
	printf("你要开始一个新游戏吗?\n\n");
	printf("1:是的，我已经有了存档	(Y)\n");
	printf("2:不，我要重新开始	(N)\n\n");
	int a=inPut();
	if (a == 0) {
		printf("游戏启动中，请稍后...\n");
		Sleep(2000);
	} else if (a == 1) {
		printf("抱歉，检测到你的智商已欠费，正在自动开启新游戏...\n");
		Sleep(2000);
	} else {
		printf("你输错了！！！");
		Sleep(2000);
		isW = 1;
	}
	system("cls");
}

//每一回合的微调
void eachPa() {
	srand(time(0));
	int a = rand();
	a %= 2;
	//有50%的可能会让岁数随机增加
	if (a == 0) {
		srand(time(0));
		a = rand();
		a %= 6;
		if (a == 0) {
			a = 6;
		}
		info[0] += a;
	}
	//让数据大的变大，小的变小
	for (int i = 1; i <= 5; i++) {
		if (info[i] >= 75) {
			info[i] += 2;
		} else if (info[i] <= 30) {
			info[i] -= 1;
		}
	}
}

int main() {
	//游戏开始
	open();
	
	//循环一次就是一个回合
	do {
		putInfo();
		Sleep(2000);
		
		if(rest==0){
			printf("你已经触到我的底线了\n");
		} 
		//得到该选择第几张
		srand(time(0));
		int i=rand();
		i%=num;
		i++;

		//得到在数组中的下标
		bool isFound=0;
		for(int j=0; j<num; j++) {
			if(cards[j]==i) {
				if(block[j].depend==-1) {
					isFound=1;
					i=j;
					cards[j]=0;
					for(int k=0; k<num; k++) {
						cards[k]--;
					}
					break;
				} else {
					j=block[j].depend;
				}
			}
		}

		//输出相关话语
		if(isFound==0) {
			printf("发生错误，找不到Event");
		} else {
			printf("%s:\n%s\n\n<Y>%s\n<N>%s\n",
			       block[i].name,block[i].senten,block[i].yes,block[i].no);
		}
	} while(isW!=1&&info[1]!=0);

		printf("you are dead now!!!");

	/*while (isW == 0 && info[1] != 0) {
		play(choose());
	}*/

	/*游戏总结，把关闭程序也包括在里面
	putFinal();*/
	return 0;
}
