#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int N = 1e5+10;
int nxt[N][26],fail[N],count1[N];
int tot;
int n,m;
char cd[N];
int newnode()
{
    fail[++tot]=0;
    count1[tot]=0;
    for(int i=0;i<26;i++)
        nxt[tot][i]=-1;
    return tot;
}

void insert(string str)
{
    int tmp=0;
    for(char i:str)
    {
        int idx = i-'a';
        if(~nxt[tmp][idx])
            nxt[tmp][idx] = newnode();
        tmp = nxt[tmp][idx];
        cd[tmp] = i;
    }
    count1[tmp]++;
}
int q[N],head,tail;

void get_fail()
{
    head=tail=0;
    int tmp=0;
    for(int i=0;i<26;i++)
    {
        if(~nxt[0][i])
        {
            fail[nxt[0][i]]=0;
            if(count1[nxt[0][i]])
            {
            	nxt[0][i]=0;
            	continue;
            }
            q[head++]=nxt[0][i];
        }
        else
            nxt[0][i] = 0;
    }
    while(head!=tail)
    {
        tmp = q[tail++];
        for(int i=0;i<26;i++)
        {
            if(~nxt[tmp][i])
            {
                int v =nxt[tmp][i];
                if(count1[v])
                {
                	nxt[tmp][i]=0;
                	continue;
                }
                fail[v] = nxt[fail[tmp]][i];
                if(count1[fail[v]])
                    nxt[tmp][i] = 0;
                else
                    q[head++]=v;
            }
            else
            {
                nxt[tmp][i]=nxt[fail[tmp]][i];
                if(count1[nxt[tmp][i]])
                    nxt[tmp][i] = 0;
            }
        }
    }
}

int stk[N],vis[N],dfn[N],low[N];
int top,dtot;
bool you;
int bbb;
int tarjan(int x)
{
	dfn[x]=low[x];
	stk[++top]=x;
	vis[x]=1;
	for(int i=0;i<26;i++)
	{
		int v = nxt[x][i];
		if(v == 0)continue;
		if(!dfn[v])
		{
			tarjan(v);
			low[x]=min(low[x],low[v]);
		}
		else if(vis[v]==1)
			low[x]=min(low[x],low[v]);
	}
	int v = fail[x];
	if(v != 0)
	{
		if(!dfn[v])
		{
			tarjan(v);
			low[x]=min(low[x],low[v]);
		}
		else if(vis[v]==1)
			low[x]=min(low[x],low[v]);
	}
	if(dfn[x]==low[x])
	{
		while(stk[top]!=x)
		{
			vis[stk[top]] = 0;
			top--;
			you = 1;
			bbb=x;
		}
		top--;
		vis[x]=0;
	}
}

int rd[N];
void dfs1(int x)
{
	cout<<x<<endl;
	for(int i=0;i<26;i++)
	{
		int v = nxt[x][i];
		if(v==0 || v==-1)continue;
		rd[v]++;
		if(rd[v]==1)
			dfs1(v);
	}
	int v = fail[x];
	if(v != 0)
	{
		rd[v]++;
		if(rd[v]==1)
			dfs1(v);
	}
}

int fa[N],longest[N];
bool ok;
void print(int x)
{
	int mtot=0;
	int marr[100000];
	for(;mtot<n;mtot++)
	{
		marr[mtot]=x;
		x=fa[x];
	}
	for(int i=mtot-1;i>=0;i--)
		printf("%d%c",cd[marr[i]],i==0?'\n':' ');
}
void tp(int x)
{
	vis[x]=1;
	if(ok)return;
	if(longest[x]==n)
	{
		print(x);
		ok=1;
		return;
	}
	for(int i=0;i<26;i++)
	{
		int v = nxt[x][i];
		if(v==0)continue;
		rd[v]--;
		if(longest[v]<longest[x]+1)
		{
			fa[v]=x;
			longest[v]=longest[x]+1;
		}
		if(rd[v]==0)
			tp(v);
	}
	int v = fail[x];
	if(v != 0)
	{
		if(longest[v]<longest[x]+1)
		{
			fa[v]=x;
			longest[v]=longest[x]+1;
		}
		rd[v]--;
		if(rd[v]==0)
		{
			tp(v);
		}
	}
}

void printbbb()
{
	int tmp = bbb;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<26;j++)
			if(low[nxt[tmp][j]]==low[bbb])
			{
				printf("%c%c",j+'a',i==n-1?'\n':' ');
				tmp = nxt[tmp][j];
				break;
			}
	}
}

string s;
int main()
{
    cin>>n>>m;
    for(int i=0;i<m;i++)
    {
        cin>>s;
        insert(s);
    }
    get_fail();
    //cout<<"getfail"<<endl;
    for(int i=0;i<26;i++)
    {
    	int v = nxt[0][i];
    	if(v!=0 && !dfn[v])
    		tarjan(v); 
    }
    //cout<<"tarjanok"<<endl;
    for(int i=1;i<=tot;i++)
    	if(!rd[i])
    		dfs1(i);
	//cout<<"dfs1ok"<<endl;
    if(you)
    {
    	printbbb();
    }
    else 
    {
    	memset(vis,0,sizeof(vis));
    	for(int i=1;i<=tot;i++)
    		if(!rd[i] && !vis[i])
    			tp(i);
    }
    return 0;
}
