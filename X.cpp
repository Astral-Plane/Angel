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
#pragma comment(lib, ��winmm.lib��)
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
} player= {"����",50,40,100,100,1,0,0,100};
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
} strongman= {"���»���÷ɭ","�ƽ�ʥ��",40,50,350,200,100,1,2,1,0},
  witch= {"��������Ҹ�˹","����",25,15,100,50,50,2,2,1,1},
  xiyi= {"�����ˡ���˹��","����",18,10,50,30,35,3,3,2,2},
  big_strongman= {"��ɪ�ա��ֵ�","NPC֮��",40*5,50*5,350*5,200*5,100*5,4,4,2,0},
  lion= {"��","�����ý�",60,30,280,200,100,5,2,1,0},
  horse= {"��ʥ���ں�","��Ѫ��",56,24,180,100,100,6,2,1,1},
  bee= {"���������","����",34,22,120,60,70,7,3,2,2},
  shitu= {"ʹͽ","\0",60*8,30*8,280*8,200*8,100*8,9,1,1,0},
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
char gongname[20]="��",fangname[20]="��",proof;
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
	puts("ս��ʤ�����ȳ�����������");
	system("cls");
	end=time(NULL);
	tim+=end-start;
	int hour=tim/3600;
	int minute=(tim/60)%60;
	int second=tim%60;
	printf("��ϲͨ��\n����ʱ��%d ʱ %d �� %d ��\n",hour,minute,second);
	sp=100;
	SlowDisplay("�Ӵ��Ժ���Ҳû��֪��");
	printf("%s",player.name);
	if(av==1)
		SlowDisplay("��Victoryȥ��������˲²���������������ĵ����С�������ʱ��Ϊ���£�����һ��ʹͽ�����빫�����뿪�ˡ���");
	else
		SlowDisplay("��Ray����ȥ��������˲²����Ǵ��ʹͽ���Ϊ���£�˫����赣��´����ģ���д���޵е��񻰡���");
	system("cls");
	sp=522;
	SlowDisplay("G A M E   O V E R");
	exit(0);
}
void setaudio()
{
	    if(vol==0)mciSendString("setaudio mymusic volume to 0",NULL,0,NULL);		//����������С
        if(vol==100)mciSendString("setaudio mymusic volume to 100",NULL,0,NULL);		//����������С
        if(vol==200)mciSendString("setaudio mymusic volume to 200",NULL,0,NULL);		//����������С
        if(vol==300)mciSendString("setaudio mymusic volume to 300",NULL,0,NULL);		//����������С
        if(vol==400)mciSendString("setaudio mymusic volume to 400",NULL,0,NULL);		//����������С
        if(vol==500)mciSendString("setaudio mymusic volume to 500",NULL,0,NULL);		//����������С
        if(vol==600)mciSendString("setaudio mymusic volume to 600",NULL,0,NULL);		//����������С
        if(vol==700)mciSendString("setaudio mymusic volume to 700",NULL,0,NULL);		//����������С
        if(vol==800)mciSendString("setaudio mymusic volume to 800",NULL,0,NULL);		//����������С
        if(vol==900)mciSendString("setaudio mymusic volume to 900",NULL,0,NULL);		//����������С
        if(vol==1000)mciSendString("setaudio mymusic volume to 1000",NULL,0,NULL);		//����������С
        if(vol==1100)mciSendString("setaudio mymusic volume to 1100",NULL,0,NULL);		//����������С
        if(vol==1200)mciSendString("setaudio mymusic volume to 1200",NULL,0,NULL);		//����������С
        if(vol==1300)mciSendString("setaudio mymusic volume to 1300",NULL,0,NULL);		//����������С
        if(vol==1400)mciSendString("setaudio mymusic volume to 1400",NULL,0,NULL);		//����������С
        if(vol==1500)mciSendString("setaudio mymusic volume to 1500",NULL,0,NULL);		//����������С
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
	cout << "                                      |     ���á�����W,A,S,D�ٿ�    | " << endl;
	cout << "                                      |          ��Ϸ�ٶ�            | " << endl;
	cout << "                                      ";
	if(V==0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color+128);
	printf("|");
	for(int i=1;i<=15;i++){
		if(150-sp>=i*10) printf("��");
		else printf("  ");
	}
	    printf("| \n");
	SetConsoleTextAttribute(h,color);
	cout << "                                      |            ����              | " << endl;
	cout << "                                      ";
	if(V==1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color+128);
	printf("|");
	for(int i=1;i<=15;i++){
		if(vol>=i*100) printf("��");
		else printf("  ");
	}
	    printf("| \n");
	SetConsoleTextAttribute(h,color);
	cout << "                                      |            ��0����           | " << endl;
	cout << "                                      |      ��������Ҫ��������    | " << endl;
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
    printf("\n�������֣��ɽ���ʾ�����Ϊѡ�����ʽ\n");
    scanf("%d",&color);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}  
int SuiJi100() {
	srand((unsigned)time(NULL));
	return rand()%100;
}
void ChooseWupin() {
	printf("��Ʒ: 1,ֹѪ��%d�� 2,���Ȱ�%d�� 3,���ϰ�ҩ%d�� 4,�������ϰ�ҩ%d�� 5,����%d�� 6,����%d�� 7,����ʽԭ�ӵ�%d�� 0,����\n\n\n",cao,jijiubao,baiyao,superbaiyao,boom,dubiao,atom_boom);
	switch(scanf("%d",&choose_number),choose_number) {
		case 1:
			if(cao>0) {
				SlowDisplay("ʹ��ֹѪ��,HP����60\n\n\n");
				cao--;
				if(player.health+60>player.max_health)player.health=player.max_health;
				else player.health+=60;
			} else SlowDisplay("û��ֹѪ����\n\n\n");
			break;
		case 2:
			if(jijiubao>0) {
				SlowDisplay("ʹ�ü��Ȱ�,HP����80\n\n\n");
				jijiubao--;
				if(player.health+80>player.max_health)player.health=player.max_health;
				else player.health+=80;
			} else SlowDisplay("û�м��Ȱ���\n\n\n");
			break;
		case 3:
			if(baiyao>0) {
				SlowDisplay("ʹ�����ϰ�ҩ,HP����120\n\n\n");
				baiyao--;
				if(player.health+120>player.max_health)player.health=player.max_health;
				else player.health+=120;
			} else SlowDisplay("û�����ϰ�ҩ��\n\n\n");
			break;
		case 4:
			if(superbaiyao>0) {
				SlowDisplay("ʹ�ó������ϰ�ҩ,HP����200\n\n\n");
				superbaiyao--;
				if(player.health+200>player.max_health)player.health=player.max_health;
				else player.health+=200;
			} else SlowDisplay("û�г������ϰ�ҩ��\n\n\n");
			break;
		case 5:
			if(battle) {
				if(boom>0) {
					SlowDisplay("ʹ������,����HP����100\n\n\n");
					boom--;
					guai.health-=100;
					AttackResult();
				}
			} else SlowDisplay("��ս��״̬,����ʹ������!\n\n\n");
			break;
		case 6:
			if(battle) {
				if(dubiao>0) {
					SlowDisplay("ʹ�ö���,����HP����200\n\n\n");
					dubiao--;
					guai.health-=200;
					AttackResult();
				}
			} else SlowDisplay("��ս��״̬,����ʹ�ö���!\n\n\n");
			break;
		case 7:
			if(battle) {
				if(atom_boom>0) {
					SlowDisplay("ʹ������ʽԭ�ӵ�,����HP����500\n\n\n");
					atom_boom--;
					guai.health-=500;
					AttackResult();
				}
			} else SlowDisplay("��ս��״̬,����ʹ������ʽԭ�ӵ�!\n\n\n");
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
		printf("ս��ʤ��!��ý��%d,����%d\n\n\n",guai.money,guai.exp);
		player.exp+=guai.exp;
		player.range_exp+=guai.exp;
		money+=guai.money;
		S=SuiJi();
		if(s<guai.wupinpro) {
			SlowDisplay("�ӵ���ʬ���з���");
			printf("%s\n\n\n",guai.wupin);
			AddWupin(guai.wupin_sign);
		}
		WhetherLevelUp();
		if(strcmp(guai.name,"ʹͽ")==0) {
			vic();
		}
		f1=0;
		f2=0;
		return 1;
	} else {
		int s1=SuiJi();
		if((guai.attack+s1-player.defense/3)<0) {
			player.health-=1;
			printf("%s����,���HP������ 1\n\n",guai.name);
		} else {
			player.health-=guai.attack+s1-player.defense/3;
			printf("%s����,���HP������%d\n\n",guai.name,guai.attack+s-player.defense/3);
		}
		if(player.health<0) {
			battle=0;
			printf("%sս��!��ҵ���%d\n\n\n",player.name,player.level*50);
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
			printf("װ��ʧ��\n\n\n");
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
			SlowDisplay("   ����!\n\n\n������+3, ������+2, HP����+20\n\n\n");
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
			printf("������!����%d��!",l1);
			printf("������+%d, ������+%d, HP����+%d\n\n\n",3*l1,2*l1,20*l1);
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
			SlowDisplay("   ����!\n\n\n������+3, ������+2, HP����+20\n\n\n");
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
			printf("������!����%d��!",l1);
			printf("������+%d, ������+%d, HP����+%d\n\n\n",3*l2,2*l2,20*l2);
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
			SlowDisplay("   ����!\n\n\n������+3, ������+2, HP����+20\n\n\n");
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
			printf("������!����%d��!",l1);
			printf("������+%d, ������+%d, HP����+%d\n\n\n",3*l3,2*l3,20*l3);
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
		printf("Ҫ��ʲô?\n\n\n   1,�ƶ�  2,����  3,�Ի�  4,�鿴״̬  5,װ��  6.����  7.����   8.������ģʽ   9.������־   0.�˳���Ϸ\n\n\n");
		puts("=======================================================================================================================");
		switch(scanf("%d",&choose_number),choose_number) {
			case 1:
				SlowDisplay("Ҫȥ����?\n\n\n");
				printf("1.B7\n2.B6\n3.B5\n4.B4\n5.B3\n6.B2\n7.B1\n8.����");
				switch(scanf("%d",&choose_number),choose_number) {
					case 1:
						place_sign=place.bar;
						printf("\n��ײ�ưɵ��ˣ�");
						break;
					case 2:
						place_sign=place.hotel;
						SlowDisplay("Ҫס����? 200����� 1,��  0,��\n\n\n");
						choose_number=1;
						switch(scanf("%d",&choose_number),choose_number) {
							case 1:
								if(money-200<0) {
									SlowDisplay("Sorry,���Ǯ����~\n\n\n");
								} else {
									SlowDisplay("�ú���Ϣ\n\tHP��\n\t\t�ڶ�����\n\n");
									money-=200;
									player.health=player.max_health;
								}
								place_sign=0;
								break;
							case 0:
								SlowDisplay("��ס�������������!\n\n\n");
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
							printf("%s���˹���!\n\n\n",guai.name);
							BattleAct();
						} else if(s<9) {
							battle=1;
							guai=witch;
							printf("%s���˹���!\n\n\n",guai.name);
							BattleAct();
						} else
							SlowDisplay("���ﰲȫ\n\n\n");
						break;
					case 4:
						place_sign=place.forest2;
						s=SuiJi();
						if(s<7) {
							battle=1;
							guai=witch;
							printf("%s���˹���!\n\n\n",guai.name);
							BattleAct();
						} else if(s<9) {
							battle=1;
							guai=strongman;
							printf("%s���˹���!\n\n\n",guai.name);
							BattleAct();
						} else {
							SlowDisplay("���ﰲȫ\n\n\n");
						}
						break;
					case 5:
						place_sign=place.forest3;
						s=SuiJi();
						if(s<7) {
							battle=1;
							guai=strongman;
							printf("%s���˹���!\n\n\n",guai.name);
							BattleAct();
						} else if(s<9) {
							battle=1;
							guai=big_strongman;
							printf("%s���˹���!\n\n\n",guai.name);
							BattleAct();
						} else {
							SlowDisplay("���ﰲȫ\n\n\n");
						}
						break;
					case 6:
						place_sign=place.grass1;
						s=SuiJi();
						if(s<7) {
							battle=1;
							guai=bee;
							printf("%s���˹���!\n\n\n",guai.name);
							BattleAct();
						} else if(s<9) {
							battle=1;
							guai=horse;
							printf("%s���˹���!\n\n\n",guai.name);
							BattleAct();
						} else {
							SlowDisplay("���ﰲȫ\n\n\n");
						}
						break;
					case 7:
						place_sign=place.grass2;
						s=SuiJi();
						if(s<7) {
							battle=1;
							guai=horse;
							printf("%s���˹���!\n\n\n",guai.name);
							BattleAct();
						} else if(s<9) {
							battle=1;
							guai=lion;
							printf("%s���˹���!\n\n\n",guai.name);
							BattleAct();
						} else {
							SlowDisplay("���ﰲȫ\n\n\n");
						}
						break;
					case 8:
						place_sign=place.grass3;
						s=SuiJi();
						if(s<7) {
							battle=1;
							guai=lion;
							printf("%s���˹���!\n\n\n",guai.name);
							BattleAct();
						} else if(s<9) {
							battle=1;
							if(strongman_arm) {
								SlowDisplay("��������:\n\n\n    ����,������,���Ĳ���,����...�ٺ�,���ϵ���!NPC֮����Ҫ��,������Ҳ�������!\n\n\n");
								guai=shitu;
								printf("%s���˹���!\n\n\n",guai.name);
								BattleAct();
							} else SlowDisplay("��������:\n\n\n    ������,��ð�.�������NPC֮��,�ҿ��Ը����㹫��������Ŷ~\n\n\n");
						} else {
							SlowDisplay("���ﰲȫ\n\n\n");
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
					SlowDisplay("Ҫ��˭˵��?\n\n\n1,�췢Ů�� 2,�ͽ����� 3,�ư��ϰ�\n\n\n");
					switch(scanf("%d",&choose_number),choose_number) {
						case 1:
							int adult;
							if(yin-->=0)
								SlowDisplay("�췢Ů��:\n\n\n�ҽ�ά������    ��̨���Ǹ�Hunter��˧��!\n\n\n��˵�������������,�����·��Ӧ�ú���Ϥ��!\n\n\n");
							else {
								SlowDisplay("�췢Ů��:\n\n\n    ���ϴ�ڨ�Ҹ�ʲô!\n\n\n����Ի�1000�������һ��300000���Ϊ������\n\n\n");
								SlowDisplay("���Ѷ���Ǯ��\n\n\n");
								scanf("%d",&adult);
								if(adult>money||adult<1000) printf("Ǯ����\n\n\n");
								else if(adult>=300000) {
									printf("'w'������*w*\n\n\n");
									av=1;
									SlowDisplay("    ��Ȣ����ά������\n\n\n����ȡ����VICTORY��ʤ����");
									Sleep(5117);
									vic();
								} else if(adult>=1000) {
									printf("%d����˫���й�ȥ��\n\n\n",adult/1000);
									player.range_exp+=222*adult;
									WhetherLevelUp();
								} else printf("һ�㶼����ϡ�����\n\n\n");
								money-=adult;
							}
							break;
						case 2:
							if(fang1n<1&&gong1n<1) {
								SlowDisplay("�ͽ�����:\n\n\n    ��Ҫ�ȹ�����!�õ���!\n\n\n    ���������¥����ն�,����Խ��������ԽΣ��,����ذ�׺Ͳ���,�������Щ������,��ȥ��!\n\n\n");
								printf("%s����:��,��λ��������ð�!\n\n\n",player.name);
								gong1n++;
								fang1n++;
							} else SlowDisplay("�ͽ�����:\n\n\n    ���Ͱ�,������!\n\n\n    ��Ҫ���ڰ���¥�����ŵ�!\n\n\n");
							break;
						case 3:
							printf("Ҫ�ȵ�ʲô?\n\n\n    1,����ͷ25��� HP+20  2,XO��80��� HP+50  3,��ͷ����150��� HP+100  0,����\n\n\n");
							choose_number=1;
							while(choose_number) {
								switch(scanf("%d",&choose_number),choose_number) {
									case 1:
										if(money<25) {
											SlowDisplay("Ǯ����!");
										} else {
											if(player.health+20<=player.max_health) {
												SlowDisplay("HP+20.");
												money-=25;
												player.health+=20;
											} else {
												SlowDisplay("HP����");
												player.health=player.max_health;
											}
										}
										break;
									case 2:
										if(money<80) {
											SlowDisplay("Ǯ����!");
										} else {
											if(player.health+50<=player.max_health) {
												SlowDisplay("HP+50.");
												money-=80;
												player.health+=50;
											} else {
												SlowDisplay("HP����");
												player.health=player.max_health;
											}
										}
										break;
									case 3:
										if(money<150) {
											SlowDisplay("Ǯ����!");
										} else {
											if(player.health+100<=player.max_health) {
												SlowDisplay("HP+100.");
												money-=150;
												player.health+=100;
											} else {
												SlowDisplay("HP����");
												player.health=player.max_health;
											}
										}
										break;
									case 0:
										SlowDisplay("�´�����!\n");
										break;
									default:
										SlowDisplay("�������\n\n\n");
								}
							}
					}
				} else if(place_sign==place.hotel)
					SlowDisplay("���ϰ���!����֪��NPC֮�������\n\n\n�������BossèŮ�ڵ���ȥȡ��è�Ƕ��ɵĶ���Ŷ��\n\n\n");
				else SlowDisplay("�������û�˿�������\n\n\n");
				break;
			case 4:
				DisplayState();
				break;
			case 5:
				printf("��װ: 1,ذ��:%d�� 2,����:%d�� 3,��Ѫ��:%d�� 4,�����ý�:%d��\t\t9,�ֽ�\n\n\n",gong1n,gong2n,gong3n,gong4n);
				printf("��װ: 5,����:%d�� 6,����:%d�� 7,����:%d��   8,�ƽ�ʥ��:%d��\t\t0,����\n\n\n",fang1n,fang2n,fang3n,fang4n);
				SlowDisplay("ѡ��Ҫװ�������������:\n\n\n");
				switch(scanf("%d",&choose_number),choose_number) {
					case 1:
						if(gong1n>=1) {
							SlowDisplay("������ذ��\n\n\n");
							gong=gong1;
							gongn=1;
							strcpy(gongname,"ذ��");
						} else SlowDisplay("��û��ذ�׿���װ��\n\n\n");
						break;
					case 2:
						if(gong2n>=1) {
							SlowDisplay("�����˳���\n\n\n");
							gong=gong2;
							gongn=2;
							strcpy(gongname,"����");
						} else SlowDisplay("��û�г�������װ��\n\n\n");
						break;
					case 3:
						if(gong3n>=1) {
							SlowDisplay("�����˱�Ѫ��\n\n\n");
							gong=gong3;
							gongn=3;
							strcpy(gongname,"��Ѫ��");
						} else SlowDisplay("��û�б�Ѫ������װ��\n\n\n");
						break;
					case 4:
						if(gong4n>=1) {
							SlowDisplay("�����˾����ý�\n\n\n");
							gong=gong4;
							gongn=4;
							strcpy(gongname,"�����ý�");
						} else SlowDisplay("��û�о����ý�����װ��\n\n\n");
						break;
					case 5:
						if(fang1n>=1) {
							SlowDisplay("�����˲���\n\n\n");
							fang=fang1;
							fangn=1;
							strcpy(fangname,"����");
						} else SlowDisplay("��û�в��¿���װ��\n\n\n");
						break;
					case 6:
						if(fang2>=1) {
							SlowDisplay("����������\n\n\n");
							fang=fang2;
							fangn=2;
							strcpy(fangname,"����");
						} else SlowDisplay("��û�����׿���װ��\n\n\n");
						break;
					case 7:
						if(fang3n>=1) {
							SlowDisplay("����������\n\n\n");
							fang=fang3;
							fangn=3;
							strcpy(fangname,"����");
						} else SlowDisplay("��û�����׿���װ��\n\n\n");
						break;
					case 8:
						if(fang4n>=1) {
							SlowDisplay("�����˻ƽ�ʥ��\n\n\n");
							fang=fang4;
							fangn=4;
							strcpy(fangname,"�ƽ�ʥ��");
						} else SlowDisplay("��û�лƽ�ʥ�¿���װ��\n\n\n");
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
						printf("���װ���ѱ��ֽ���գ������%d���",mm);
						money+=mm;
						break;
					case 0:
						SlowDisplay("δ����װ��\n\n\n");
						break;
					default:
						printf("change error!");
				}
				break;
			case 6:
				set();
				break;
			case 7:
				printf("1.���� ѧϰ�۸�3000���\n");
				printf("2.�������� ѧϰ�۸�10000���\n");
				printf("0.����\n");
				SlowDisplay("ѡ��Ҫѧϰ�ļ���:��ѧϰ����Խ�࣬ÿ��ս�������ͷŵĴ���Խ�ࣩ\n\n\n");
				switch(scanf("%d",&choose_number),choose_number) {
					case 1:
						if(money>=3000) {
							money-=3000;
							printf("ѧϰ�ɹ�!\n");
							know1++;
						} else SlowDisplay("Ǯ����!");
						break;
					case 2:
						if(money>=10000) {
							money-=10000;
							printf("ѧϰ�ɹ�!\n");
							know2++;
						} else SlowDisplay("Ǯ����!");
						break;
					case 0:
						SlowDisplay("δѧϰ����\n\n\n");
						break;
					default:
						printf("skill error!");
				}
				break;
			case 0:
				SlowDisplay("ȷ���˳���Ϸ���浵?(Y/N)\n\n\n");
				getchar();
				proof=getchar();
				if(proof=='y'||proof=='Y') {
					SlowDisplay("���ݴ洢��...");
					end=clock();
					save();
					getchar();
					SlowDisplay("���س��˳�");
					getchar();
					exit(0);
				} else if(proof=='n'||proof=='N')printf("������Ϸ!\n\n\n");
				else SlowDisplay("����!\n\n\n");
				break;
			case 8:
				develop_mode();
				break;
			case 9:
				system("start ������־.log");
				break;
			default:
				SlowDisplay("�������!\n\n\n");
		}
	}
}
void DisplayState() {
	printf("���֣�%s ������:%d+%d=%d  ������:%d+%d=%d  HP:%d/%d \n\n\n",player.name,player.attack,gong,player.attack+gong,player.defense,fang,player.defense+fang,player.health,player.max_health);
	printf("����: %s ����: %s \n\n\n",gongname,fangname);
	printf("�ȼ�:%d  ����:%d/%d ����Ҫ%d�������� ���:%d \n\n\n",player.level,player.exp,player.max_exp,player.max_exp-player.exp,money);
	Sleep(5222);
}
void star() {
	start=time(NULL);
}
void BattleAct() {
	while(1) {
		puts("=============================================================================");
		printf("Ҫ��ô��?\n\n\n    1,���� 2,��Ʒ 3,�鿴״̬ 4,�ͷż��� 5,����\n\n\n");
		switch(scanf("%d",&choose_number),choose_number) {
			case 1:
				S=SuiJi();
				if(player.attack+S+gong-guai.defense/3<0) printf("δ���ƶԷ�����\n");
				else {
					printf("%s����! %sHP����%d\n\n\n",player.name,guai.name,player.attack+S+gong-guai.defense/3);
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
				printf("1.���� \n");
				printf("2.�������� \n");
				printf("0.����\n");
				SlowDisplay("ѡ��Ҫ�ͷŵļ���:\n\n\n");
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
							printf("�������180���˺�\n");
							AttackResult();
						} else SlowDisplay("�޷��ͷż���!\n");
						break;
					case 2:
						if(f2<know2) {
							SlowDisplay("�����ߤ򤫤󤸤�  �����ߤ򤪤�����");
							cout<<endl;
							SlowDisplay("�����ߤ򤫤󤬤���");
							cout<<endl;
							SlowDisplay("�����ߤ� �����Ȥ�");
							cout<<endl;
							SlowDisplay("�����ߤ򤪤�����");
							cout<<endl;
							SlowDisplay("���� ��� ������ �� ������ ��");
							cout<<endl<<endl<<endl;
							SlowDisplay("�����Ƥ󤻤�!!!!");
							cout<<endl;
							f2=1;
							guai.health-=guai.attack;
							printf("�������%d���˺�\n",guai.attack);
							AttackResult();
						} else SlowDisplay("�޷��ͷż���!\n");
						break;
					case 0:
						SlowDisplay("δ�ͷż���\n\n\n");
						break;
					default:
						printf("skill error!");
				}
				break;
			case 5:
				S=SuiJi();
				if(S<4) {
					printf("%s������~\n\n\n",player.name);
					battle=0;
					return;
				} else printf("%s����ʧ��!\n\n\n",player.name);
				break;
			default:
				SlowDisplay("�������,ս��ʱ�����������\n\n\n");
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
	printf("\n\n\n                                     X����ʹ6.0\n\n\n");
	if(ok) {
		SlowDisplay("1.start a new game\n\n\n2.continue the last saved game\n\n\nYOUR CHOICE:");
		scanf("%d",&ch);
		if(ch==1) {
			ok=0;
			return;
		}
		if(ch==2) {
			if(read()==0)SlowDisplay("�㻹û�д浵!");
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
				SlowDisplay("�����ɹ���");
				Sleep(1000);
				star();
				OrdinaryAct();
			}
		} else SlowDisplay("�����������������!");
		startscene();
	}
}
int main() {
	mciSendString("open music\\m.mp3 alias mymusic", NULL, 0, NULL);	// ������
	mciSendString("setaudio mymusic volume to 600",NULL,0,NULL);		//����������С
	mciSendString("play mymusic", NULL, 0, NULL);						//��ʼ����
	mciSendString("play mymusic repeat", NULL, 0, NULL);				//ѭ������
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
	startscene();
	int i=0,j=0,k=0;
	char player_name[21];
	SlowDisplay("����һ�����ߵ�����! �����Ray������İ���˰����!\n\n ΰ�������,�������������,Ӫ�ȹ���!\n\n\n�����������:   \n\n\n");
	scanf("%s",player_name);
	star();
	strncpy(player.name,player_name,20);
	if(strcmp(player.name,"Zack")==0) {
		SlowDisplay("Zack�������������ڳ����B6��������\n\n\n������Ѫ֮�����߰ɣ�����\n\n\nPS:��Ѫ֮�����Դ�999����+999����+9999��ֵ����");
		player.attack=player.defense=999;
		player.health=player.max_health=9999;
	}
	if(strcmp(player.name,"Domino")==0) {
		SlowDisplay("Hey Domino��NPC֮���ҵ������ͷ�ϡ�����Ŀǰ�������˵رܿ����й�������ÿ�ζ��������ˣ������������˵ػ�������");
		strongman_arm=1;
		player.attack=player.defense=player.health=player.max_health=170614;
	}
	if(strcmp(player.name,"Victor")==0) {
		SlowDisplay("Victor�����������Ǹ�������������ȿȣ����ˣ���Ӯ��");
		vic();
	}
	if(strcmp(player.name,"TonyStark")==0) {
		SlowDisplay("����������ʮ�ڽ���ѵ��ˣ�����װ���ѹ��ã���Ʒ������һ�飬����ա�");
		money=1000000500;
		fang=fang1n=fang2n=fang3n=fang4n=gong=gong1n=gong2n=gong3n=gong4n=1;
		cao=jijiubao=baiyao=superbaiyao=boom=dubiao=atom_boom=64;
	}
	getchar();
	OrdinaryAct();
	return 0;
}
