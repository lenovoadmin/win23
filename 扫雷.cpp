#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>                           //开头模块 
#include<queue>
#include<ctype.h>
#define A 17	//地图的高
#define B 17	//地图的宽
#define C 2	//雷的总数
using namespace std;
 
//全局变量
DWORD a,b;
char map[A][B],news,spare;
int BoomTotalNum,floatx,floaty,flag[A][B],flagnum,mode,slect[A][B],game;
 
//颜色属性
const WORD FORE_BLUE  =  FOREGROUND_BLUE;	//蓝色文本属性
const WORD FORE_GREEN = FOREGROUND_GREEN;	//绿色文本属性
const WORD FORE_RED   =   FOREGROUND_RED;	//红色文本属性                      文本系类 
 
//开垦地图结构体                                   
struct node {
	int x;           
	int y;
};
queue <node> dui;
 
//打印位置
void position(int x,int y) {
	COORD pos={x,y};
	HANDLE Out=GetStdHandle(STD_OUTPUT_HANDLE);                          //windows23不敢相信制作                 //qq群：2507979441 
	SetConsoleCursorPosition(Out,pos);
}
 
//隐藏光标 
void Hide() {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);  
	CONSOLE_CURSOR_INFO CursorInfo;  
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息  
	CursorInfo.bVisible = false; //隐藏控制台光标  
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态   
}
 
//初始化
void Beginning() {
	while(!dui.empty()) {
		dui.pop();
	}
	game=1;
	//BoomTotalNum=C;
	floatx=A/2;
	floaty=B/2;
	flagnum=0;
	BoomTotalNum=C;
	mode=0;
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);    //获得标准输出设备句柄  
    CONSOLE_SCREEN_BUFFER_INFO csbi;                        //定义窗口缓冲区信息结构体  
    GetConsoleScreenBufferInfo(handle_out, &csbi);          //获得窗口缓冲区信息
    int x,y;
	srand((unsigned)time(0));
	for(int i=0;i<A;i++) for(int j=0;j<B;j++) {
		map[i][j]=' ';
		flag[i][j]=0;
		slect[i][j]=0;
	}
	while(BoomTotalNum) {
		x=rand()%A;
		y=rand()%B;
		if(map[x][y]==' ') {
			map[x][y]='@';
			BoomTotalNum--;                                       //windows23不敢相信制作 
		}
	}
	SetConsoleTextAttribute(handle_out, FORE_GREEN);  
	for(int i=0;i<A;i++) {
		for(int j=0;j<B;j++) printf("█");
		printf("\n");
	}
	position(floaty*2,floatx);
	SetConsoleTextAttribute(handle_out, FORE_RED);  
	printf("");	//光标位置
	position(44,9);
	printf("扫雷模式");
	position(44,5);                                                           //中间的文字等提示符 
	position(5,22);
	printf("剩余雷数：%d ",C-flagnum);
	SetConsoleTextAttribute(handle_out, FORE_GREEN);                         //中间的文字等提示符 
	position(5,22);
	printf("按“空格”切换模式");                                              //中间的文字等提示符 
	position(5,22);
	position(5,23);
	printf("按“Enter”确认");
	position(5,24);
	printf("按“方向键”选择方块"); 
	position(5,25);
	printf("windows23不敢相信制作"); 
	
}
 
//打印地图的一块儿 
void Lump(int xx,int yy) {
	switch(map[xx][yy]) {
		case '1' : printf("①");break;	//周围雷的数量（下同） 
		case '2' : printf("②");break;
		case '3' : printf("③");break;
		case '4' : printf("④");break;
		case '5' : printf("⑤");break;
		case '6' : printf("⑥");break;
		case '7' : printf("⑦");break;
		case '8' : printf("⑧");break;
		case ' ' :
			if(xx==floatx&&yy==floaty) {
				if(flag[xx][yy]==0) {
					if(mode%2==0) printf("");
					else printf("");
				}
				else printf("");
			}
			else {                                                          //windows23不敢相信制作 
				if(flag[xx][yy]==0) printf("█");
				else printf("");
			}
			break;
		case '@' :
			if(xx==floatx&&yy==floaty) {
				if(flag[xx][yy]==0) {
					if(mode%2==0) printf("");
					else printf("");
				}
				else printf("");
			}
			else {
				if(flag[xx][yy]==0) printf("█");
				else printf("");
			}
			break;
		case 'x' : if(floatx==xx&&floaty==yy) printf(""); else printf("  ");break;	//已经挖开的空白
	}
}
 
//移动光标
void Move() {
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);    //获得标准输出设备句柄  
    CONSOLE_SCREEN_BUFFER_INFO csbi;                        //定义窗口缓冲区信息结构体  
    GetConsoleScreenBufferInfo(handle_out, &csbi);          //获得窗口缓冲区信息
    int xxx,yyy;
    xxx=floatx;
    yyy=floaty;
	switch(news) {
		case 72 : floatx--;break;	//上 
		case 80 : floatx++;break;	//下 
		case 75 : floaty--;break;	//左 
		case 77 : floaty++;break;	//右 
	}
	if(floatx==-1) floatx=A-1; floatx%=A;	//两端穿模处理 
	if(floaty==-1) floaty=B-1; floaty%=B;
	
	position(yyy*2,xxx);
	SetConsoleTextAttribute(handle_out, FORE_GREEN);
	Lump(xxx,yyy);	//删除原位置
	
	if(map[floatx][floaty]=='x') {
		position(floaty*2,floatx);
		printf("  ");
	}
	
	position(floaty*2,floatx);
	SetConsoleTextAttribute(handle_out, FORE_BLUE);  
	Lump(floatx,floaty);	//更新新位置 
} 
 
//插旗和排雷模式切换 
void Mode() {
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);    //获得标准输出设备句柄  
    CONSOLE_SCREEN_BUFFER_INFO csbi;                                                //定义窗口缓冲区信息结构vv体  
    GetConsoleScreenBufferInfo(handle_out, &csbi);          //获得窗口缓冲区信息
	mode++;
	SetConsoleTextAttribute(handle_out, FORE_BLUE);
	position(floaty*2,floatx);
	if(mode%2==0) printf("");
	else printf("");
	
	position(44,9);
	if(mode%2==0) {
		SetConsoleTextAttribute(handle_out, FORE_BLUE);  
		printf("扫雷模式，windows23不敢相信提醒");
	}                                                          //扫面模式 
	else {
		SetConsoleTextAttribute(handle_out, FORE_RED);  
		printf("插旗模式");
	}
}
 
//该点周围地雷数 
int Boomnum(int xx,int yy) {
	int num=0;
	if((xx-1>=0)&&(yy-1>=0)&&(map[xx-1][yy-1]=='@')) num++;
	if((xx-1>=0)&&(yy+0>=0)&&(map[xx-1][yy]=='@')) num++;
	if((xx-1>=0)&&(yy+1<B) &&(map[xx-1][yy+1]=='@')) num++;
	if((xx+0>=0)&&(yy-1>=0)&&(map[xx][yy-1]=='@')) num++;
	if((xx+0>=0)&&(yy+1<B) &&(map[xx][yy+1]=='@')) num++;
	if((xx+1<A)&&(yy-1>=0) &&(map[xx+1][yy-1]=='@')) num++;
	if((xx+1<A)&&(yy+0>=0) &&(map[xx+1][yy]=='@')) num++;
	if((xx+1<A)&&(yy+1<B)  &&(map[xx+1][yy+1]=='@')) num++;
	return num;
}
 
//更新地图 
void Open() {                                                     //windows23不敢相信制作 
	node c;
	node d;
	while(!dui.empty()) {
		dui.pop();
	}
	c.x=floatx;
	c.y=floaty;
	dui.push(c);
	slect[c.x][c.y]=1;
	while(!dui.empty()) {
		c=dui.front();
		dui.pop();
		if(Boomnum(c.x,c.y)!=0) {
			map[c.x][c.y]=(Boomnum(c.x,c.y)+48);
			continue;
		}
		else {
			map[c.x][c.y]='x';                                                                                                                                                                                                                                                                                                                                                                                                                                     
			if((c.x-1>=0)&&(c.y-1>=0)&&(map[c.x-1][c.y-1]==' ')&&(slect[c.x-1][c.y-1]==0)) {
				d.x=c.x-1;
				d.y=c.y-1;
				dui.push(d);
				slect[d.x][d.y]=1;
			}
			if((c.x-1>=0)&&(c.y-0>=0)&&(map[c.x-1][c.y]==' ')&&(slect[c.x-1][c.y]==0)) {
				d.x=c.x-1;
				d.y=c.y-0;
				dui.push(d);
				slect[d.x][d.y]=1;
			}
			if((c.x-1>=0)&&(c.y+1<B)&&(map[c.x-1][c.y+1]==' ')&&(slect[c.x-1][c.y+1]==0)) {
				d.x=c.x-1;
				d.y=c.y+1;
				dui.push(d);
				slect[d.x][d.y]=1;
			}
			if((c.x-0>=0)&&(c.y-1>=0)&&(map[c.x][c.y-1]==' ')&&(slect[c.x][c.y-1]==0)) {
				d.x=c.x-0;
				d.y=c.y-1;
				dui.push(d);
				slect[d.x][d.y]=1;
			}
			if((c.x-0>=0)&&(c.y+1<B)&&(map[c.x][c.y+1]==' ')&&(slect[c.x][c.y+1]==0)) {
				d.x=c.x-0;
				d.y=c.y+1;
				dui.push(d);
				slect[d.x][d.y]=1;
			}
			if((c.x+1<A)&&(c.y-1>=0)&&(map[c.x+1][c.y-1]==' ')&&(slect[c.x+1][c.y-1]==0)) {
				d.x=c.x+1;
				d.y=c.y-1;
				dui.push(d);
				slect[d.x][d.y]=1;
			}
			if((c.x+1<A)&&(c.y-0>=0)&&(map[c.x+1][c.y]==' ')&&(slect[c.x+1][c.y]==0)) {
				d.x=c.x+1;
				d.y=c.y-0;
				dui.push(d);
				slect[d.x][d.y]=1;
			}
			if((c.x+1<A)&&(c.y+1<B)&&(map[c.x+1][c.y+1]==' ')&&(slect[c.x+1][c.y+1]==0)) {
				d.x=c.x+1;
				d.y=c.y+1;
				dui.push(d);
				slect[d.x][d.y]=1;
			}
		}
	}
}
 
int main() {
	freopen("排名.txt","r",stdin);
	Relife:	//重玩处
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);    //获得标准输出设备句柄  
    CONSOLE_SCREEN_BUFFER_INFO csbi;                        //定义窗口缓冲区信息结构体  
    GetConsoleScreenBufferInfo(handle_out, &csbi);          //获得窗口缓冲区信息
    
	Hide();		
	Beginning();
	a=GetTickCount();
	while(1) {
		if(kbhit()!=0) {
			spare=getch();
			
			
			if((spare!=(-32))&&(spare!=13)&&(spare!=' ')) continue;
			
			
			if(spare==13) {;
				
				if(mode%2==0) {
					if(map[floatx][floaty]=='@'&&flag[floatx][floaty]==0) {
						break;	
						game=0;
					}
					
					if(flag[floatx][floaty]==1) continue;	
					Open(); 
					position(0,0);
					SetConsoleTextAttribute(handle_out, FORE_GREEN);
					for(int i=0;i<A;i++) {
						for(int j=0;j<B;j++) Lump(i,j);
						printf("\n");
					}
					position(floaty*2,floatx);
					SetConsoleTextAttribute(handle_out, FORE_BLUE);
					Lump(floatx,floaty);
				}
				
				
				else {
					
					
					if(map[floatx][floaty]=='x'||(map[floatx][floaty]>'0'&&map[floatx][floaty]<'9'))
						continue;	
					
					
					if(flag[floatx][floaty]==0) {
						flagnum++;
						flag[floatx][floaty]=1;
						position(floaty*2,floatx);
						SetConsoleTextAttribute(handle_out, FORE_BLUE);
						Lump(floatx,floaty);
					}
					
					
					else {
						flagnum--;
						flag[floatx][floaty]=0;
						position(floaty*2,floatx);
						SetConsoleTextAttribute(handle_out, FORE_BLUE);
						Lump(floatx,floaty);
					}
				}
			}
			
			
			if(spare==' ') Mode();	
			
			//按方向键 
			if(spare==-32) {
				news=getch();
				Move();	
			}
			for(int i=0;i<A;i++) for(int j=0;j<B;j++) if(map[i][j]=='x'||(map[i][j]>'0'&&map[i][j]<'9')) game++;
			if(game==A*B-C+1) break;
			else game=1;
			SetConsoleTextAttribute(handle_out, FORE_RED);
			position(44,5);
			printf("剩余雷数：%d ",C-flagnum);
		}
		else Sleep(10);
		b=GetTickCount();
		SetConsoleTextAttribute(handle_out, FORE_RED);
		position(44,7);
		printf("用时：");	
		if((b-a)/60000<10) printf("0");
		printf("%d:",(b-a)/60000);
		if(((b-a)/1000)%60<10) printf("0");
		printf("%d:",((b-a)/1000)%60);
		if(((b-a)/10)%100<10) printf("0");
		printf("%d",((b-a)/10)%100);
	}
	SetConsoleTextAttribute(handle_out, FORE_RED);
	position(5,5);
	if(game==1) printf("游戏结束！");
	else printf("恭喜通关！");
	position(5,8);
	printf("任意键重玩");
	scanf("%c%c",&spare,&spare);
	system("cls");
	position(0,0);
	goto Relife;
}                                       //windows23不敢相信制作 

