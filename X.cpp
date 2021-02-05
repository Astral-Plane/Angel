#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<string.h>
#include<windows.h>
#include<iostream>
#include<cstring>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <conio.h>
#pragma comment(lib, “winmm.lib”)
using namespace std;
int sp=22,sw,ok=1,yin=3;
time_t start,end;
int tim,vol=600,color=240,V;
struct Player {
	char name[21];
	int attack;
	int defense;
	int health;
	long int max_health;
	int level;
	int exp;
	int range_exp;
	long int max_exp;
} player= {"勇者",50,40,100,100,1,0,0,100};
struct Enemy {
	char name[20];
	char wupin[12];
	int attack;
	int defense;
	int health;
	int money;
	long int exp;
	int wupin_sign;
	int wupinpro;
	int double_attack;
	int miss;
} strongman= {"爱德华·梅森","黄金圣衣",40,50,350,200,100,1,2,1,0},
  witch= {"丹尼尔·狄更斯","银甲",25,15,100,50,50,2,2,1,1},
  xiyi= {"艾萨克·福斯特","铁甲",18,10,50,30,35,3,3,2,2},
  big_strongman= {"凯瑟琳·沃德","NPC之臂",40*5,50*5,350*5,200*5,100*5,4,4,2,0},
  lion= {"神父","绝世好剑",60,30,280,200,100,5,2,1,0},
  horse= {"武圣人于和","碧血剑",56,24,180,100,100,6,2,1,1},
  bee= {"加里·伊马布利","长剑",34,22,120,60,70,7,3,2,2},
  shitu= {"使徒","\0",60*8,30*8,280*8,200*8,100*8,9,1,1,0},
  guai= {"\0","\0",0,0,0,0,0,0,0,0,0};
struct Place {
	int bar,hotel,forest1,forest2,forest3,grass1,grass2,grass3;
} place= {1,2,3,4,5,6,7,8};
int av,max_exp=0;
int gongn,fangn,price[5]= {0,450,800,1750,2500};
int choose_number=0,s=0,S=0,strongman_arm=0,battle=0,money=500,place_sign=9;
int cao=3,jijiubao=2,baiyao=2,superbaiyao=1,boom=3,dubiao=2,atom_boom=1;
int fang=0,fang1=10,fang1n=0,fang2=20,fang2n=0,fang3=40,fang3n=0,fang4=100,fang4n=0;
int gong=0,gong1=8,gong1n=0,gong2=15,gong2n=0,gong3=25,gong3n=0,gong4=60,gong4n=0;
int know1=0,know2=0,f1=0,f2=0;
char gongname[20]="无",fangname[20]="无",proof;
void AddWupin(int);
int AttackResult();
void BattleAct();
void ChooseWupin();
void DisplayState();
void OrdinaryAct();
int SuiJi();
int SuiJi100();
void WhetherLevelUp();
void SlowDisplay(char *);
int SuiJi() {
	srand((unsigned)time(NULL));
	return rand()%10;
}
void save() {
	FILE *fp2;
	end=time(NULL);
	tim+=end-start;
	fp2=fopen("saving.txt","w");
	fprintf(fp2,"%d %d %d %d %d %d %d %d %d",av,baiyao,battle,boom,cao,choose_number,dubiao,fang,fang1n);
	fprintf(fp2," %d %d %d %d %d",fang2n,fang3n,fang4n,gong,gong1n);
	fprintf(fp2," %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",gong2n,gong3n,gong4n,jijiubao,max_exp,money,ok,place_sign,proof,s,S,sp,strongman_arm,superbaiyao,sw,yin);
	fprintf(fp2,"\n%s",fangname);
	fprintf(fp2,"\n%s",gongname);
	fprintf(fp2,"\n%d %d",know1,know2);
	fprintf(fp2,"\n%s \n%d %d %d %d %d %d %d %d",player.name,player.attack,player.defense,player.exp,player.health,player.level,player.max_exp,player.max_health,player.range_exp);
	fprintf(fp2,"\n%d \n%d \n%d \n%d \n%d",gongn,fangn,tim,vol,color);
	fclose(fp2);
}
int read() {
	FILE *fp1;
	fp1=fopen("saving.txt","r");
	fscanf(fp1,"%d %d %d %d %d %d %d %d %d",&av,&baiyao,&battle,&boom,&cao,&choose_number,&dubiao,&fang,&fang1n);
	fscanf(fp1," %d %d %d %d %d",&fang2n,&fang3n,&fang4n,&gong,&gong1n);
	fscanf(fp1," %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",&gong2n,&gong3n,&gong4n,&jijiubao,&max_exp,&money,&ok,&place_sign,&proof,&s,&S,&sp,&strongman_arm,&superbaiyao,&sw,&yin);
	fscanf(fp1,"%s",fangname);
	fscanf(fp1,"%s",gongname);
	fscanf(fp1,"%d %d",&know1,&know2);
	fscanf(fp1,"%s %d %d %d %d %d %d %d %d",player.name,&player.attack,&player.defense,&player.exp,&player.health,&player.level,&player.max_exp,&player.max_health,&player.range_exp);
	fscanf(fp1,"%d %d %d %d %d",&gongn,&fangn,&tim,&vol,&color);
	fclose(fp1);
	return 1;
}
void vic() {
	puts("战斗胜利，救出公主！！！");
	system("cls");
	end=time(NULL);
	tim+=end-start;
	int hour=tim/3600;
	int minute=(tim/60)%60;
	int second=tim%60;
	printf("恭喜通关\n总用时：%d 时 %d 分 %d 秒\n",hour,minute,second);
	sp=100;
	SlowDisplay("从此以后，再也没人知道");
	printf("%s",player.name);
	if(av==1)
		SlowDisplay("和Victory去了哪里，有人猜测后他们在升向地面的电梯中【电梯震】时结为伴侣，看了一眼使徒、神父与公主便离开了……");
	else
		SlowDisplay("和Ray公主去了哪里，有人猜测他们打败使徒后结为伴侣，双剑合璧，勇闯天涯，谱写了无敌的神话……");
	system("cls");
	sp=522;
	SlowDisplay("G A M E   O V E R");
	exit(0);
}
void setaudio()
{
	    if(vol==0)mciSendString("setaudio mymusic volume to 0",NULL,0,NULL);		//设置音量大小
        if(vol==100)mciSendString("setaudio mymusic volume to 100",NULL,0,NULL);		//设置音量大小
        if(vol==200)mciSendString("setaudio mymusic volume to 200",NULL,0,NULL);		//设置音量大小
        if(vol==300)mciSendString("setaudio mymusic volume to 300",NULL,0,NULL);		//设置音量大小
        if(vol==400)mciSendString("setaudio mymusic volume to 400",NULL,0,NULL);		//设置音量大小
        if(vol==500)mciSendString("setaudio mymusic volume to 500",NULL,0,NULL);		//设置音量大小
        if(vol==600)mciSendString("setaudio mymusic volume to 600",NULL,0,NULL);		//设置音量大小
        if(vol==700)mciSendString("setaudio mymusic volume to 700",NULL,0,NULL);		//设置音量大小
        if(vol==800)mciSendString("setaudio mymusic volume to 800",NULL,0,NULL);		//设置音量大小
        if(vol==900)mciSendString("setaudio mymusic volume to 900",NULL,0,NULL);		//设置音量大小
        if(vol==1000)mciSendString("setaudio mymusic volume to 1000",NULL,0,NULL);		//设置音量大小
        if(vol==1100)mciSendString("setaudio mymusic volume to 1100",NULL,0,NULL);		//设置音量大小
        if(vol==1200)mciSendString("setaudio mymusic volume to 1200",NULL,0,NULL);		//设置音量大小
        if(vol==1300)mciSendString("setaudio mymusic volume to 1300",NULL,0,NULL);		//设置音量大小
        if(vol==1400)mciSendString("setaudio mymusic volume to 1400",NULL,0,NULL);		//设置音量大小
        if(vol==1500)mciSendString("setaudio mymusic volume to 1500",NULL,0,NULL);		//设置音量大小
        if(vol<0) vol=0;
        if(vol>1500) vol=1500;
        if(sp<10) sp=10;
}
void set()
{
	system("cls");
	if(sw) {

		player.attack=999;
		player.defense=999;
		player.health=9999;
		player.max_health=9999;
	}
	setaudio();
	HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
	printf("\n\n\n\n\n\n"); 
	cout << "                                       ______________________________  " << endl;
	cout << "                                      |                              | " << endl;
	cout << "                                      |     设置——用W,A,S,D操控    | " << endl;
	cout << "                                      |          游戏速度            | " << endl;
	cout << "                                      ";
	if(V==0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color+128);
	printf("|");
	for(int i=1;i<=15;i++){
		if(150-sp>=i*10) printf("█");
		else printf("  ");
	}
	    printf("| \n");
	SetConsoleTextAttribute(h,color);
	cout << "                                      |            音乐              | " << endl;
	cout << "                                      ";
	if(V==1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color+128);
	printf("|");
	for(int i=1;i<=15;i++){
		if(vol>=i*100) printf("█");
		else printf("  ");
	}
	    printf("| \n");
	SetConsoleTextAttribute(h,color);
	cout << "                                      |            按0返回           | " << endl;
	cout << "                                      |      请输入需要服务的序号    | " << endl;
	cout << "                                       ------------------------------  " << endl;
	int o=0;
	while(o==0)
	{
		o=0;
	    char D=getch();
	    if(D=='0') return;
	    if(D=='W') {V=(V-1)%2;set();o=1;}
	    if(D=='S') {V=(V+1)%2;set();o=1;}
	    if(D=='D') {if(V==0) sp-=10;if(V==1) vol+=100;set();o=1;}
	    if(D=='A') {if(V==0) sp+=10;if(V==1) vol-=100;set();o=1;}
    }
	return;
}
void develop_mode()
{
    HANDLE hOut;
    hOut=GetStdHandle(STD_OUTPUT_HANDLE);
    int i,j;
    for(i=0;i<16;i++){
    for(j=0;j<=15;j++)
    {
       SetConsoleTextAttribute(hOut,i*16+j);
       printf(" %3d ",i*16+j);
    } 
    printf("\n");}
    SetConsoleTextAttribute(hOut,color);
    printf("\n输入数字，可将显示主题改为选择的样式\n");
    scanf("%d",&color);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}  
int SuiJi100() {
	srand((unsigned)time(NULL));
	return rand()%100;
}
void ChooseWupin() {
	printf("物品: 1,止血草%d个 2,急救包%d个 3,云南白药%d个 4,超级云南白药%d个 5,手雷%d个 6,毒标%d个 7,手抛式原子弹%d个 0,返回\n\n\n",cao,jijiubao,baiyao,superbaiyao,boom,dubiao,atom_boom);
	switch(scanf("%d",&choose_number),choose_number) {
		case 1:
			if(cao>0) {
				SlowDisplay("使用止血草,HP增加60\n\n\n");
				cao--;
				if(player.health+60>player.max_health)player.health=player.max_health;
				else player.health+=60;
			} else SlowDisplay("没有止血草了\n\n\n");
			break;
		case 2:
			if(jijiubao>0) {
				SlowDisplay("使用急救包,HP增加80\n\n\n");
				jijiubao--;
				if(player.health+80>player.max_health)player.health=player.max_health;
				else player.health+=80;
			} else SlowDisplay("没有急救包了\n\n\n");
			break;
		case 3:
			if(baiyao>0) {
				SlowDisplay("使用云南白药,HP增加120\n\n\n");
				baiyao--;
				if(player.health+120>player.max_health)player.health=player.max_health;
				else player.health+=120;
			} else SlowDisplay("没有云南白药了\n\n\n");
			break;
		case 4:
			if(superbaiyao>0) {
				SlowDisplay("使用超级云南白药,HP增加200\n\n\n");
				superbaiyao--;
				if(player.health+200>player.max_health)player.health=player.max_health;
				else player.health+=200;
			} else SlowDisplay("没有超级云南白药了\n\n\n");
			break;
		case 5:
			if(battle) {
				if(boom>0) {
					SlowDisplay("使用手雷,敌人HP减少100\n\n\n");
					boom--;
					guai.health-=100;
					AttackResult();
				}
			} else SlowDisplay("非战斗状态,不能使用手雷!\n\n\n");
			break;
		case 6:
			if(battle) {
				if(dubiao>0) {
					SlowDisplay("使用毒标,敌人HP减少200\n\n\n");
					dubiao--;
					guai.health-=200;
					AttackResult();
				}
			} else SlowDisplay("非战斗状态,不能使用毒标!\n\n\n");
			break;
		case 7:
			if(battle) {
				if(atom_boom>0) {
					SlowDisplay("使用手抛式原子弹,敌人HP减少500\n\n\n");
					atom_boom--;
					guai.health-=500;
					AttackResult();
				}
			} else SlowDisplay("非战斗状态,不能使用手抛式原子弹!\n\n\n");
			break;
		case 0:
			break;
		default:
			printf("ChooseWupin error!\n\n\n");
	}
}
int AttackResult() {
	if(guai.health<=0) {
		battle=0;
		printf("战斗胜利!获得金币%d,经验%d\n\n\n",guai.money,guai.exp);
		player.exp+=guai.exp;
		player.range_exp+=guai.exp;
		money+=guai.money;
		S=SuiJi();
		if(s<guai.wupinpro) {
			SlowDisplay("从敌人尸骸中发现");
			printf("%s\n\n\n",guai.wupin);
			AddWupin(guai.wupin_sign);
		}
		WhetherLevelUp();
		if(strcmp(guai.name,"使徒")==0) {
			vic();
		}
		f1=0;
		f2=0;
		return 1;
	} else {
		int s1=SuiJi();
		if((guai.attack+s1-player.defense/3)<0) {
			player.health-=1;
			printf("%s反击,你的HP减少了 1\n\n",guai.name);
		} else {
			player.health-=guai.attack+s1-player.defense/3;
			printf("%s反击,你的HP减少了%d\n\n",guai.name,guai.attack+s-player.defense/3);
		}
		if(player.health<0) {
			battle=0;
			printf("%s战死!金币掉落%d\n\n\n",player.name,player.level*50);
			money-=player.level*50;
			if(money<0) money=0;
			player.health=player.max_health/5;
			f1=0;
			f2=0;
			OrdinaryAct();
			return 1;
		}
	}
	return 0;
}
void AddWupin(int wupin_sign) {

	switch(wupin_sign) {
		case 1:
			fang4n++;
			break;
		case 2:
			fang3n++;
			break;
		case 3:
			fang2n++;
			break;
		case 4:
			strongman_arm=1;
			break;
		case 5:
			gong4n++;
			break;
		case 6:
			gong3n++;
			break;
		case 7:
			gong2n++;
			break;
		default:
			printf("装备失败\n\n\n");
	}

}
void WhetherLevelUp() {
	int i=0,j=0;
	int l1=player.range_exp/100;
	int l2=player.range_exp/300;
	int l3=player.range_exp/600;
	if(player.level<=15&&l1>0) {
		if(l1==1) {
			printf("%s",player.name);
			SlowDisplay("   升级!\n\n\n攻击力+3, 防御力+2, HP上限+20\n\n\n");
			player.exp=player.exp+guai.exp-(player.exp+guai.exp)%100;
			player.attack+=3;
			player.defense+=2;
			player.max_health+=20;
			player.health=player.max_health;
			player.level++;
			player.range_exp=0;
			player.exp=player.max_exp;
			player.max_exp+=100;
		} else {
			printf("好厉害!连升%d级!",l1);
			printf("攻击力+%d, 防御力+%d, HP上限+%d\n\n\n",3*l1,2*l1,20*l1);
			player.exp=player.exp+guai.exp-(player.exp+guai.exp)%100;
			player.attack+=3*l1;
			player.defense+=2*l1;
			player.max_health+=20*l1;
			player.health=player.max_health;
			player.level+=l1;
			player.range_exp=0;
			player.exp=player.max_exp;
			player.max_exp+=100*l1;
		}
	} else if(player.level<=40&&l2>0) {
		if(l2==1) {
			printf("%s",player.name);
			SlowDisplay("   升级!\n\n\n攻击力+3, 防御力+2, HP上限+20\n\n\n");
			player.exp=player.exp+guai.exp-(player.exp+guai.exp)%100;
			player.attack+=3;
			player.defense+=2;
			player.max_health+=20;
			player.health=player.max_health;
			player.level++;
			player.range_exp=0;
			player.exp=player.max_exp;
			player.max_exp+=300;
		} else {
			printf("好厉害!连升%d级!",l1);
			printf("攻击力+%d, 防御力+%d, HP上限+%d\n\n\n",3*l2,2*l2,20*l2);
			player.exp=player.exp+guai.exp-(player.exp+guai.exp)%100;
			player.attack+=3*l2;
			player.defense+=2*l2;
			player.max_health+=20*l2;
			player.health=player.max_health;
			player.level+=l2;
			player.range_exp=0;
			player.exp=player.max_exp;
			player.max_exp+=300*l2;
		}
	} else if(l3>0) {
		if(l3==1) {
			printf("%s",player.name);
			SlowDisplay("   升级!\n\n\n攻击力+3, 防御力+2, HP上限+20\n\n\n");
			player.exp=player.exp+guai.exp-(player.exp+guai.exp)%100;
			player.attack+=3;
			player.defense+=2;
			player.max_health+=20;
			player.health=player.max_health;
			player.level++;
			player.range_exp=0;
			player.exp=player.max_exp;
			player.max_exp+=600;
		} else {
			printf("好厉害!连升%d级!",l1);
			printf("攻击力+%d, 防御力+%d, HP上限+%d\n\n\n",3*l3,2*l3,20*l3);
			player.exp=player.exp+guai.exp-(player.exp+guai.exp)%100;
			player.attack+=3*l3;
			player.defense+=2*l3;
			player.max_health+=20*l3;
			player.health=player.max_health;
			player.level+=l3;
			player.range_exp=0;
			player.exp=player.max_exp;
			player.max_exp+=600*l3;
		}
	}
}
void OrdinaryAct() {
	int mm;
	while(1) {
		Sleep(1422);
		system("cls");
		puts("=======================================================================================================================");
		printf("要做什么?\n\n\n   1,移动  2,道具  3,对话  4,查看状态  5,装备  6.设置  7.技能   8.开发者模式   9.更新日志   0.退出游戏\n\n\n");
		puts("=======================================================================================================================");
		switch(scanf("%d",&choose_number),choose_number) {
			case 1:
				SlowDisplay("要去哪里?\n\n\n");
				printf("1.B7\n2.B6\n3.B5\n4.B4\n5.B3\n6.B2\n7.B1\n8.地面");
				switch(scanf("%d",&choose_number),choose_number) {
					case 1:
						place_sign=place.bar;
						printf("\n最底层酒吧到了！");
						break;
					case 2:
						place_sign=place.hotel;
						SlowDisplay("要住店吗? 200个金币 1,是  0,否\n\n\n");
						choose_number=1;
						switch(scanf("%d",&choose_number),choose_number) {
							case 1:
								if(money-200<0) {
									SlowDisplay("Sorry,你的钱不够~\n\n\n");
								} else {
									SlowDisplay("好好休息\n\tHP满\n\t\t第二天了\n\n");
									money-=200;
									player.health=player.max_health;
								}
								place_sign=0;
								break;
							case 0:
								SlowDisplay("不住店搁这儿坐会儿吧!\n\n\n");
								break;
							default:
								printf("hotel talk error!\n\n\n");
						}
						break;
					case 3:
						place_sign=place.forest1;
						s=SuiJi();
						if(s<7) {
							battle=1;
							guai=xiyi;
							printf("%s扑了过来!\n\n\n",guai.name);
							BattleAct();
						} else if(s<9) {
							battle=1;
							guai=witch;
							printf("%s扑了过来!\n\n\n",guai.name);
							BattleAct();
						} else
							SlowDisplay("这里安全\n\n\n");
						break;
					case 4:
						place_sign=place.forest2;
						s=SuiJi();
						if(s<7) {
							battle=1;
							guai=witch;
							printf("%s扑了过来!\n\n\n",guai.name);
							BattleAct();
						} else if(s<9) {
							battle=1;
							guai=strongman;
							printf("%s扑了过来!\n\n\n",guai.name);
							BattleAct();
						} else {
							SlowDisplay("这里安全\n\n\n");
						}
						break;
					case 5:
						place_sign=place.forest3;
						s=SuiJi();
						if(s<7) {
							battle=1;
							guai=strongman;
							printf("%s扑了过来!\n\n\n",guai.name);
							BattleAct();
						} else if(s<9) {
							battle=1;
							guai=big_strongman;
							printf("%s扑了过来!\n\n\n",guai.name);
							BattleAct();
						} else {
							SlowDisplay("这里安全\n\n\n");
						}
						break;
					case 6:
						place_sign=place.grass1;
						s=SuiJi();
						if(s<7) {
							battle=1;
							guai=bee;
							printf("%s扑了过来!\n\n\n",guai.name);
							BattleAct();
						} else if(s<9) {
							battle=1;
							guai=horse;
							printf("%s扑了过来!\n\n\n",guai.name);
							BattleAct();
						} else {
							SlowDisplay("这里安全\n\n\n");
						}
						break;
					case 7:
						place_sign=place.grass2;
						s=SuiJi();
						if(s<7) {
							battle=1;
							guai=horse;
							printf("%s扑了过来!\n\n\n",guai.name);
							BattleAct();
						} else if(s<9) {
							battle=1;
							guai=lion;
							printf("%s扑了过来!\n\n\n",guai.name);
							BattleAct();
						} else {
							SlowDisplay("这里安全\n\n\n");
						}
						break;
					case 8:
						place_sign=place.grass3;
						s=SuiJi();
						if(s<7) {
							battle=1;
							guai=lion;
							printf("%s扑了过来!\n\n\n",guai.name);
							BattleAct();
						} else if(s<9) {
							battle=1;
							if(strongman_arm) {
								SlowDisplay("神秘老人:\n\n\n    哈哈,年轻人,做的不错,不过...嘿嘿,你上当啦!NPC之臂我要了,公主你也别想带走!\n\n\n");
								guai=shitu;
								printf("%s扑了过来!\n\n\n",guai.name);
								BattleAct();
							} else SlowDisplay("神秘老人:\n\n\n    年轻人,你好啊.如果你有NPC之臂,我可以告诉你公主的下落哦~\n\n\n");
						} else {
							SlowDisplay("这里安全\n\n\n");
						}
						break;
					default:
						printf("choose map error!\n\n\n");
				}
				break;
			case 2:
				ChooseWupin();
				break;
			case 3:
				if(place_sign==place.bar) {
					SlowDisplay("要和谁说话?\n\n\n1,红发女郎 2,赏金猎人 3,酒吧老板\n\n\n");
					switch(scanf("%d",&choose_number),choose_number) {
						case 1:
							int adult;
							if(yin-->=0)
								SlowDisplay("红发女郎:\n\n\n我叫维克托莉    吧台边那个Hunter好帅啊!\n\n\n听说他经常外出打猎,外面的路他应该很熟悉的!\n\n\n");
							else {
								SlowDisplay("红发女郎:\n\n\n    你老搭讪我干什么!\n\n\n你可以花1000金币买我一晚，300000金币为我赎身～\n\n\n");
								SlowDisplay("花费多少钱？\n\n\n");
								scanf("%d",&adult);
								if(adult>money||adult<1000) printf("钱不够\n\n\n");
								else if(adult>=300000) {
									printf("'w'土豪啊*w*\n\n\n");
									av=1;
									SlowDisplay("    你娶得了维克托莉\n\n\n＝你取得了VICTORY（胜利）");
									Sleep(5117);
									vic();
								} else if(adult>=1000) {
									printf("%d晚在双休中过去了\n\n\n",adult/1000);
									player.range_exp+=222*adult;
									WhetherLevelUp();
								} else printf("一点都不真诚～～～\n\n\n");
								money-=adult;
							}
							break;
						case 2:
							if(fang1n<1&&gong1n<1) {
								SlowDisplay("赏金猎人:\n\n\n    你要救公主啊!好胆量!\n\n\n    不过上面的楼层很险恶,而且越靠近地面越危险,这是匕首和布衣,对你会有些帮助的,拿去吧!\n\n\n");
								printf("%s心想:哇,这位大叔人真好啊!\n\n\n",player.name);
								gong1n++;
								fang1n++;
							} else SlowDisplay("赏金猎人:\n\n\n    加油吧,年轻人!\n\n\n    不要被黑暗的楼层所吓倒!\n\n\n");
							break;
						case 3:
							printf("要喝点什么?\n\n\n    1,二锅头25金币 HP+20  2,XO酒80金币 HP+50  3,人头马面150金币 HP+100  0,返回\n\n\n");
							choose_number=1;
							while(choose_number) {
								switch(scanf("%d",&choose_number),choose_number) {
									case 1:
										if(money<25) {
											SlowDisplay("钱不够!");
										} else {
											if(player.health+20<=player.max_health) {
												SlowDisplay("HP+20.");
												money-=25;
												player.health+=20;
											} else {
												SlowDisplay("HP满了");
												player.health=player.max_health;
											}
										}
										break;
									case 2:
										if(money<80) {
											SlowDisplay("钱不够!");
										} else {
											if(player.health+50<=player.max_health) {
												SlowDisplay("HP+50.");
												money-=80;
												player.health+=50;
											} else {
												SlowDisplay("HP满了");
												player.health=player.max_health;
											}
										}
										break;
									case 3:
										if(money<150) {
											SlowDisplay("钱不够!");
										} else {
											if(player.health+100<=player.max_health) {
												SlowDisplay("HP+100.");
												money-=150;
												player.health+=100;
											} else {
												SlowDisplay("HP满了");
												player.health=player.max_health;
											}
										}
										break;
									case 0:
										SlowDisplay("下次再来!\n");
										break;
									default:
										SlowDisplay("输入错误\n\n\n");
								}
							}
					}
				} else if(place_sign==place.hotel)
					SlowDisplay("“老板娘!我想知道NPC之臂在哪里”\n\n\n“第五层Boss猫女在等你去取，猫是多疑的动物哦”\n\n\n");
				else SlowDisplay("这里好像没人可以聊天\n\n\n");
				break;
			case 4:
				DisplayState();
				break;
			case 5:
				printf("攻装: 1,匕首:%d个 2,长剑:%d个 3,碧血剑:%d个 4,绝世好剑:%d个\t\t9,分解\n\n\n",gong1n,gong2n,gong3n,gong4n);
				printf("防装: 5,布衣:%d个 6,铁甲:%d个 7,银甲:%d个   8,黄金圣衣:%d个\t\t0,返回\n\n\n",fang1n,fang2n,fang3n,fang4n);
				SlowDisplay("选择要装备的武器或防具:\n\n\n");
				switch(scanf("%d",&choose_number),choose_number) {
					case 1:
						if(gong1n>=1) {
							SlowDisplay("拿起了匕首\n\n\n");
							gong=gong1;
							gongn=1;
							strcpy(gongname,"匕首");
						} else SlowDisplay("你没有匕首可以装备\n\n\n");
						break;
					case 2:
						if(gong2n>=1) {
							SlowDisplay("拿起了长剑\n\n\n");
							gong=gong2;
							gongn=2;
							strcpy(gongname,"长剑");
						} else SlowDisplay("你没有长剑可以装备\n\n\n");
						break;
					case 3:
						if(gong3n>=1) {
							SlowDisplay("拿起了碧血剑\n\n\n");
							gong=gong3;
							gongn=3;
							strcpy(gongname,"碧血剑");
						} else SlowDisplay("你没有碧血剑可以装备\n\n\n");
						break;
					case 4:
						if(gong4n>=1) {
							SlowDisplay("拿起了绝世好剑\n\n\n");
							gong=gong4;
							gongn=4;
							strcpy(gongname,"绝世好剑");
						} else SlowDisplay("你没有绝世好剑可以装备\n\n\n");
						break;
					case 5:
						if(fang1n>=1) {
							SlowDisplay("穿上了布衣\n\n\n");
							fang=fang1;
							fangn=1;
							strcpy(fangname,"布衣");
						} else SlowDisplay("你没有布衣可以装备\n\n\n");
						break;
					case 6:
						if(fang2>=1) {
							SlowDisplay("穿上了铁甲\n\n\n");
							fang=fang2;
							fangn=2;
							strcpy(fangname,"铁甲");
						} else SlowDisplay("你没有铁甲可以装备\n\n\n");
						break;
					case 7:
						if(fang3n>=1) {
							SlowDisplay("穿上了银甲\n\n\n");
							fang=fang3;
							fangn=3;
							strcpy(fangname,"银甲");
						} else SlowDisplay("你没有银甲可以装备\n\n\n");
						break;
					case 8:
						if(fang4n>=1) {
							SlowDisplay("穿上了黄金圣衣\n\n\n");
							fang=fang4;
							fangn=4;
							strcpy(fangname,"黄金圣衣");
						} else SlowDisplay("你没有黄金圣衣可以装备\n\n\n");
						break;
					case 9:
						mm=price[1]*(gong1n+fang1n);
						mm+=price[2]*(gong2n+fang2n);
						mm+=price[3]*(gong3n+fang3n);
						mm+=price[4]*(gong4n+fang4n);
						mm-=price[gongn]+price[fangn];
						switch(gongn) {
							case 1:
								gong1n=1;
								gong2n=gong3n=gong4n=0;
								break;
							case 2:
								gong2n=1;
								gong1n=gong3n=gong4n=0;
								break;
							case 3:
								gong3n=1;
								gong1n=gong2n=gong4n=0;
								break;
							case 4:
								gong4n=1;
								gong1n=gong2n=gong3n=0;
								break;
							case 0:
								gong1n=gong2n=gong3n=gong4n=0;
								break;
						}
						switch(fangn) {
							case 1:
								fang1n=1;
								fang2n=fang3n=fang4n=0;
								break;
							case 2:
								fang2n=1;
								fang1n=fang3n=fang4n=0;
								break;
							case 3:
								fang3n=1;
								fang1n=fang2n=fang4n=0;
								break;
							case 4:
								fang4n=1;
								fang1n=fang2n=fang3n=0;
								break;
							case 0:
								fang1n=fang2n=fang3n=fang4n=0;
								break;
						}
						printf("你的装备已被分解回收，您获得%d金币",mm);
						money+=mm;
						break;
					case 0:
						SlowDisplay("未更换装备\n\n\n");
						break;
					default:
						printf("change error!");
				}
				break;
			case 6:
				set();
				break;
			case 7:
				printf("1.雷切 学习价格：3000金币\n");
				printf("2.神罗天征 学习价格：10000金币\n");
				printf("0.返回\n");
				SlowDisplay("选择要学习的技能:（学习次数越多，每场战斗可以释放的次数越多）\n\n\n");
				switch(scanf("%d",&choose_number),choose_number) {
					case 1:
						if(money>=3000) {
							money-=3000;
							printf("学习成功!\n");
							know1++;
						} else SlowDisplay("钱不够!");
						break;
					case 2:
						if(money>=10000) {
							money-=10000;
							printf("学习成功!\n");
							know2++;
						} else SlowDisplay("钱不够!");
						break;
					case 0:
						SlowDisplay("未学习技能\n\n\n");
						break;
					default:
						printf("skill error!");
				}
				break;
			case 0:
				SlowDisplay("确定退出游戏并存档?(Y/N)\n\n\n");
				getchar();
				proof=getchar();
				if(proof=='y'||proof=='Y') {
					SlowDisplay("数据存储中...");
					end=clock();
					save();
					getchar();
					SlowDisplay("按回车退出");
					getchar();
					exit(0);
				} else if(proof=='n'||proof=='N')printf("继续游戏!\n\n\n");
				else SlowDisplay("继续!\n\n\n");
				break;
			case 8:
				develop_mode();
				break;
			case 9:
				system("start 更新日志.log");
				break;
			default:
				SlowDisplay("输入错误!\n\n\n");
		}
	}
}
void DisplayState() {
	printf("名字：%s 攻击力:%d+%d=%d  防御力:%d+%d=%d  HP:%d/%d \n\n\n",player.name,player.attack,gong,player.attack+gong,player.defense,fang,player.defense+fang,player.health,player.max_health);
	printf("武器: %s 防具: %s \n\n\n",gongname,fangname);
	printf("等级:%d  经验:%d/%d 还需要%d经验升级 金币:%d \n\n\n",player.level,player.exp,player.max_exp,player.max_exp-player.exp,money);
	Sleep(5222);
}
void star() {
	start=time(NULL);
}
void BattleAct() {
	while(1) {
		puts("=============================================================================");
		printf("要怎么办?\n\n\n    1,攻击 2,物品 3,查看状态 4,释放技能 5,逃跑\n\n\n");
		switch(scanf("%d",&choose_number),choose_number) {
			case 1:
				S=SuiJi();
				if(player.attack+S+gong-guai.defense/3<0) printf("未击破对方防御\n");
				else {
					printf("%s攻击! %sHP减少%d\n\n\n",player.name,guai.name,player.attack+S+gong-guai.defense/3);
					guai.health-=player.attack+S+gong-guai.defense/3;
				}
				if(AttackResult()) {
					f1=0;
					f2=0;
					return;
				} else continue;
			case 2:
				ChooseWupin();
				break;
			case 3:
				DisplayState();
				break;
			case 4:
				printf("1.雷切 \n");
				printf("2.神罗天征 \n");
				printf("0.返回\n");
				SlowDisplay("选择要释放的技能:\n\n\n");
				switch(scanf("%d",&choose_number),choose_number) {
					case 1:
						if(f1<know1) {
							SlowDisplay("--I'm the goddess of death.");
							cout<<endl;
							SlowDisplay("--What were you the god of again?");
							cout<<endl;
							SlowDisplay("--Even when you had two eyes,you'd see only half the picture.");
							cout<<endl;
							SlowDisplay("--She's too strong.Without my hammer,I can't.");
							cout<<endl;
							SlowDisplay("--Are you Thor,the god of the Hammers?");
							cout<<endl;
							SlowDisplay("  That hammer was to control your power,to focus it.");
							cout<<endl;
							SlowDisplay("  It was never your source of strenth.");
							cout<<endl;
							SlowDisplay("--It's too late.She's already taken Asgard.");
							cout<<endl;
							SlowDisplay("--Asgard is never a place.Never was.This could be Asgard.");
							cout<<endl;
							SlowDisplay("  Asgard is where our people stands.");
							cout<<endl;
							SlowDisplay("  Even now,right now,those people need your help.");
							cout<<endl;
							SlowDisplay("--I'm not as strong as you.");
							cout<<endl;
							SlowDisplay("--No...");
							cout<<endl;
							SlowDisplay("  You're stronger.");
							cout<<endl;
							system("color 6f");
							Sleep(100);
							system("color 0f");
							f1=1;
							guai.health-=180;
							printf("技能造成180点伤害\n");
							AttackResult();
						} else SlowDisplay("无法释放技能!\n");
						break;
					case 2:
						if(f2<know2) {
							SlowDisplay("いたみをかんじる  いたみをおしえる");
							cout<<endl;
							SlowDisplay("いたみをかんがえる");
							cout<<endl;
							SlowDisplay("いたみを うけとる");
							cout<<endl;
							SlowDisplay("いたみをおしえる");
							cout<<endl;
							SlowDisplay("ここ より せかい に いたみ を");
							cout<<endl<<endl<<endl;
							SlowDisplay("しんらてんせい!!!!");
							cout<<endl;
							f2=1;
							guai.health-=guai.attack;
							printf("技能造成%d点伤害\n",guai.attack);
							AttackResult();
						} else SlowDisplay("无法释放技能!\n");
						break;
					case 0:
						SlowDisplay("未释放技能\n\n\n");
						break;
					default:
						printf("skill error!");
				}
				break;
			case 5:
				S=SuiJi();
				if(S<4) {
					printf("%s逃跑了~\n\n\n",player.name);
					battle=0;
					return;
				} else printf("%s逃跑失败!\n\n\n",player.name);
				break;
			default:
				SlowDisplay("输入错误,战斗时怎可疏忽？！\n\n\n");
		}
		break;
	}
}
void SlowDisplay(char *p) {
	while(1) {
		if(*p!=0)
			printf("%c",*p++);
		else
			break;
		Sleep(sp);
	}

}
void startscene() {
	int ch;
	system("cls");
	printf("\n\n\n                                     X的天使6.0\n\n\n");
	if(ok) {
		SlowDisplay("1.start a new game\n\n\n2.continue the last saved game\n\n\nYOUR CHOICE:");
		scanf("%d",&ch);
		if(ch==1) {
			ok=0;
			return;
		}
		if(ch==2) {
			if(read()==0)SlowDisplay("你还没有存档!");
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
				SlowDisplay("读档成功！");
				Sleep(1000);
				star();
				OrdinaryAct();
			}
		} else SlowDisplay("输入错误，请重新输入!");
		startscene();
	}
}
int main() {
	mciSendString("open music\\m.mp3 alias mymusic", NULL, 0, NULL);	// 打开音乐
	mciSendString("setaudio mymusic volume to 600",NULL,0,NULL);		//设置音量大小
	mciSendString("play mymusic", NULL, 0, NULL);						//开始音乐
	mciSendString("play mymusic repeat", NULL, 0, NULL);				//循环播放
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
	startscene();
	int i=0,j=0,k=0;
	char player_name[21];
	SlowDisplay("这是一个勇者的世界! 地面的Ray公主被陌生人绑架了!\n\n 伟大的勇者,请拿起你的武器,营救公主!\n\n\n输入你的名字:   \n\n\n");
	scanf("%s",player_name);
	star();
	strncpy(player.name,player_name,20);
	if(strcmp(player.name,"Zack")==0) {
		SlowDisplay("Zack先生，您终于在尘封的B6层中醒来\n\n\n拿起嗜血之镰暴走吧！！！\n\n\nPS:嗜血之镰，自带999攻击+999防御+9999满值生命");
		player.attack=player.defense=999;
		player.health=player.max_health=9999;
	}
	if(strcmp(player.name,"Domino")==0) {
		SlowDisplay("Hey Domino，NPC之臂砸到了你的头上……你目前可以幸运地避开所有攻击，且每次都暴击敌人，并且总能幸运地活下来！");
		strongman_arm=1;
		player.attack=player.defense=player.health=player.max_health=170614;
	}
	if(strcmp(player.name,"Victor")==0) {
		SlowDisplay("Victor先生，你真是个大聪明宝……咳咳，别看了，你赢了");
		vic();
	}
	if(strcmp(player.name,"TonyStark")==0) {
		SlowDisplay("铁人先生，十亿金币已到账，所有装备已购置，物品已配齐一组，请查收～");
		money=1000000500;
		fang=fang1n=fang2n=fang3n=fang4n=gong=gong1n=gong2n=gong3n=gong4n=1;
		cao=jijiubao=baiyao=superbaiyao=boom=dubiao=atom_boom=64;
	}
	getchar();
	OrdinaryAct();
	return 0;
}
