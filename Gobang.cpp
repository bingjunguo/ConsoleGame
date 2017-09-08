#include <iostream.h>
#include <stdlib.h>
#define N 15    //棋盘规格(N*N)

class Game
{
    public:
      Game();
      void welcome();
      void over();
      void heqi();
      void init();
      void start();
    private:
      int flag;             //胜负判定标志
      int row,line;         //行号和列号
      int a[N][N];
      int turn;             //轮换标志
      int computer[N*N][4]; //记录电脑子力
      int player[N*N][4];   //记录玩家子力
      int win();
      int valid();          //该点是否可下子
      void computerdo();    //电脑走棋
      void view(int);       //分析每个格的情况
      int direction[8][2];  //记录8个方向的情况
};
Game::Game()
{
   int i,j,k;
   turn=1;
   flag=0;
   for (i=0;i<N;i++)
   for (j=0;j<N;j++)
   {
      a[i][j]=0;                //全部置为空
      for(k=0;k<4;k++)
      {
         computer[i*N+j][k]=0;
         player[i*N+j][k]=0;
      }
   }
   //为8个方向赋初值
   direction[0][0]=1;direction[0][1]=0;
   direction[1][0]=1;direction[1][1]=1;
   direction[2][0]=0;direction[2][1]=1;
   direction[3][0]=-1;direction[3][1]=1;
   direction[4][0]=-1;direction[4][1]=0;
   direction[5][0]=-1;direction[5][1]=-1;
   direction[6][0]=0;direction[6][1]=-1;
   direction[7][0]=1;direction[7][1]=-1;
}
void Game::view(int chess)
{
    int chesskind_no,chesskind,i,j,k,x,y,value,n;
    if(chess==-1)                  //★电脑
    {
        chesskind=2;
        chesskind_no=1;
    }                              //●玩家
    else
    {
        chesskind=1;
        chesskind_no=2;
    }
    for(i=0;i<N;i++)
    {
     for(j=0;j<N;j++)
     {
       if(a[i][j]!=0)               //如果有子，则该点状态置为0
       {
         for(k=0;k<4;k++)
         {
           if(chess==-1)            //★电脑
             computer[i*N+j][k]=0;
           else                     //●玩家
             player[i*N+j][k]=0;
         }
       }
       else                         
       {
         for(k=0;k<4;k++)           //如果没子，则判断各方向情况
         {
			n=0;                    //用来计算连在一起或加一个就连一起的子的个数
            x=i;
            y=j;
            value=5;
            while((a[x+direction[k][0]][y+direction[k][1]]==chesskind)&&
			      (x+direction[k][0]<N)&&(y+direction[k][1]>=0)&&(y+direction[k][1]
					<N)&&(x+direction[k][0]>=0))
			//如果该点的direction方向是当前下棋玩家的子c，并且该方向没有出界
                 {
			         x=x+direction[k][0];
			         y=y+direction[k][1];
					 //将判定移动到c，对c进行判断
			         value=value*2;
					 n++;
				 }
			
			//循环判断直到不满足条件跳出，设判定移动到位置a
			if((a[x+direction[k][0]][y+direction[k][1]]==chesskind_no)&&
			      (x+direction[k][0]<N)&&(y+direction[k][1]>=0)&&(y+direction[k][1]
					<N)&&(x+direction[k][0]>=0))
			//如果a的direction方向是对方的棋子，则value减半
                 {
				      value=value/2;
				 }
			//还原x，y的值
			x=i;
			y=j;
			//判断对角方向的情况
			while((a[x+direction[k+4][0]][y+direction[k+4][1]]==chesskind)&&
			      (x+direction[k+4][0]<N)&&(y+direction[k+4][1]>=0)&&(y+direction[k+4][1]
					<N)&&(x+direction[k+4][0]>=0))
                   {
						  x=x+direction[k+4][0];
						  y=y+direction[k+4][1];
						  value=value*2;
						  n++;
		           }				
		    if((a[x+direction[k+4][0]][y+direction[k+4][1]]==chesskind_no)&&
			     (x+direction[k+4][0]<N)&&(y+direction[k+4][1]>=0)&&(y+direction[k+4][1]
				 <N)&&(x+direction[k+4][0]>=0)) 
			{
				value=value/2;			 
			}
			if(n>=4)           //如果有再加个子就能赢的位置，则优先级升到最高!
				value=value*10;
			if(chess==-1)
				computer[i*N+j][k]=value;
			else
				player[i*N+j][k]=value;
		 }
	   }
	 }
	}
}
/********电脑走棋********/
void Game::computerdo()
{
    int max_computer=0,max_player=0,i,j,k,xp,yp,xc,yc;
     view(1);    //玩家
    view(-1);   //电脑
/*                                   //测试数据
    for(i=0;i<N;i++)
    { for(j=0;j<N;j++)
        for(k=0;k<4;k++)
        cout<<computer[i*N+j][k]<<" ";
        cout<<endl;
    }
    cout<<endl;
      for(i=0;i<N;i++)
    { for(j=0;j<N;j++)
        for(k=0;k<4;k++)
        cout<<player[i*N+j][k]<<" ";
        cout<<endl;
    }
*/
  
    for(j=0;j<N;j++)
     for(i=0;i<N;i++)
      for(k=0;k<4;k++)
      {
        if(computer[j*N+i][k]>=max_computer)//找出电脑value最大的位置
        {
            max_computer=computer[j*N+i][k];
            xc=i;
            yc=j;
          //  cout<<"i="<<i<<"j="<<j<<endl;
        }
        if(player[j*N+i][k]>=max_player)   //找出玩家value最大的位置
        {
            max_player=player[j*N+i][k];
            xp=i;
            yp=j;
        }
      }
    if(max_computer>=max_player)  //进行比较，看谁的优先级最高，然后获取位置
    {line=xc;row=yc;}
    else
    {line=xp;row=yp;}
   // cout<<"max_computer="<<max_computer<<" xc="<<xc<<"yc="<<yc<<endl;
    a[row][line]=2;         //电脑下子地方置为2
    if (win())              //判断胜负，如果胜利
	    flag=turn;
    turn=1;
}

/****************游戏开始*******************/
void Game::welcome()
{
    cout<<"***********************************\n";
    cout<<"            Welcome!!!\n";
    cout<<"***********************************\n";
}
/****************游戏结束*******************/
void Game::over()
{

    cout<<"************************************\n";
    cout<<"            Game Over!!!\n";
    cout<<"************************************\n";
}
/****************和棋*******************/
void Game::heqi()
{
    cout<<"************************************\n";
    cout<<"             和棋!!!\n";
    cout<<"************************************\n";
}
/******建立棋盘******/
void Game::init()
{
   int x,y,i;
   cout<<"    ";
   for(i=0;i<N;i++)
   {
	 if(i>=9)cout<<i+1;
	 else cout<<i+1<<" ";
   }
   cout<<"\n";
   for (x=0;x<N;x++)
   {
	  if(x>=9)cout<<"  "<<x+1;
      else  cout<<"   "<<x+1;
      for (y=0;y<N;y++)
      {
        if (a[x][y]==2)
         {
          cout<<"★";
          continue;
         }
       if (a[x][y]==1)
        cout<<"●";
       else cout<<"□";
      }
      a[N/2][N/2]=2;
      cout<<"\n";
   }
}

/********判断胜利********/
int Game::win()
{
int x,y,count=0;
//行不变，判断列从右向左的五子序列
for (y=line;y<line+5&&y<N;y++)
{
  if (a[row][y]!=turn) break; count++;
}
if( count>=5 ) return 1;
//行不变，判断列从左向右的五子序列(和上面一起算)
for(y=line-1;y>line-5&&y>=0;y--)
{
	if(a[row][y]!=turn) break; count++;
}
if( count>=5 ) return 1;
count=0;
//列不变，判断行从上到下的五子序列
for (x=row;x<row+5&&x<N;x++)
{
if (a[x][line]!=turn) break; count++;
}
if( count>=5 ) return 1;
//列不变，判断行从下到上的五子序列(和上面一起算)
for (x=row-1;x>row-5&&x>=0;x--)
{
	if(a[x][line]!=turn) break; count++;
}
if( count>=5 ) return 1;
count = 0;
//判断沿左上角的五子序列
for (x=row,y=line;x<row+5&&x<N&&y<N;x++,y++)
{
if (a[x][y]!=turn) break;
count++;
}
if( count>=5 ) return 1;
//判断沿右下角的五子序列(和上面一起算)
for (x=row-1,y=line-1;x>row-5&&x>=0&&y>=0;x--,y--)
{
if (a[x][y]!=turn) break;
count++;
}
if( count>=5 ) return 1;
count = 0;
//判断沿左下角的五子序列
for (x=row,y=line;x<row+5&&x<N&&y>=0;x++,y--)
{
if (a[x][y]!=turn) break;
count++;
}
if( count>=5 ) return 1;
//判断沿右上角的五子序列(和上面一起算)
for (x=row-1,y=line+1;x<row+5&&x>=0&&y<N;x--,y++)
{
if (a[x][y]!=turn) break;
count++;
}
if( count>=5 ) return 1;
return 0;
}
/*******判断该点是否有子*******/
int Game::valid()
{
if (row>N-1||row<0) return 1;
if (line>N-1||line<0) return 1;
if (a[row][line]==0) return 0;
return 1;
}

//玩家下棋
void Game::start()
{
    int s1;
    for (s1=1;s1<N*N;s1++)
	{
	    if(turn==2)        //如果轮到电脑
	    computerdo();
	    else
	    {
	       cout<<"\n  玩家●:输入行号和列号，以空格分割，回车结束 ";
		   cin>>row>>line;
		   line--;
		   row--;
           if (valid())
	      {
		    s1=s1-1;
            cout<<"\n  该点已下子或超出范围!!\n";
		    turn=1;
            continue;
	      }
          else
           {
             a[row][line]=1;
             if (win())
	         flag=turn;     //纪录是哪边获胜
             turn=2;
           }
       }
       // cout<<"turn="<<turn<<"row="<<row+1<<"line="<<line+1<<endl;
        system("cls");
        welcome();
        init();
         // cout<<"s1="<<s1<<endl;
        if(turn==1)
          cout<<"\n  电脑★走了"<<row+1<<" "<<line+1<<endl;
        if(flag==2)          
        {
            cout<<"  真遗憾，你输了!"<<endl;
            break;
        }
        if(flag==1)
        {
            cout<<"  恭喜你，胜利了!"<<endl;
            break;
        }
	}
	if(s1==N*N) heqi();
}

/******主函数******/
void main()
{
    char k;
    Game game;
	game.welcome();
    game.init();
	game.start();
	while(k!='n'&&k!='N')
	{
      cout<<"  再来一盘?(Y/N) ";
      cin>>k;
      if(k=='y'||k=='Y')
      {
        Game game;
        system("cls");
        game.welcome();
        game.init();
        game.start();
      }
    }
   	game.over();
}
