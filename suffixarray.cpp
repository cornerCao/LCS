/* 
 * Problem: POI2000 pow 
 * Author: Guo Jiabao 
 * Time: 2009.4.16 21:00 
 * State: Solved 
 * Memo: 多串最长公共子串 后缀数组 二分答案 
*/  
#include <iostream>  
#include <cstdio>  
#include <fstream>
#include <cstdlib>  
#include <cmath>  
#include <cstring>  
#include <stack>
#include <vector>
#include <exception>
const int MAXL=0x1000f,MAXN=5002;  
using namespace std;
class stkele{
public:
    int height;
    int loc;
     bool ba[MAXN];
    stkele(){
        height = 0;
        loc = 0;
        memset(ba,0,sizeof(ba));
    }
    stkele(int h,int l,int idx1,int idx2){
        height = h;
        loc = l;
        memset(ba,0,sizeof(ba));
         ba[idx1]=true;
         ba[idx2] = true;
    }
};
class resele{
public:
    int height;
    int cover;
    int loc;
   
    resele(){
        height = 0;
        cover = 0;
        loc = 0;
        
    }
    resele(int h,int c,int l){
        height = h;
        cover = c;
        loc = l;   
    }
};  
struct SuffixArray  
{  
    struct RadixElement  
    {  
        int id,k[2];  
    }RE[MAXL],RT[MAXL];  
    int N,A[MAXL],SA[MAXL],Rank[MAXL],Height[MAXL],C[MAXL];  
    void RadixSort()  
    {  
        int i,y;  
        for (y=1;y>=0;y--)  
        {  
            memset(C,0,sizeof(C));  
            for (i=1;i<=N;i++) C[RE[i].k[y]]++;  
            for (i=1;i<MAXL;i++) C[i]+=C[i-1];  
            for (i=N;i>=1;i--) RT[C[RE[i].k[y]]--]=RE[i];  
            for (i=1;i<=N;i++) RE[i]=RT[i];  
        }  
        for (i=1;i<=N;i++)  
        {  
            Rank[ RE[i].id ]=Rank[ RE[i-1].id ];  
            if (RE[i].k[0]!=RE[i-1].k[0] || RE[i].k[1]!=RE[i-1].k[1])  
                Rank[ RE[i].id ]++;  
        }  
    }  
    void CalcSA()  
    {  
        int i,k;  
        RE[0].k[0]=-1;  
        for (i=1;i<=N;i++)  
            RE[i].id=i,RE[i].k[0]=A[i],RE[i].k[1]=0;  
        RadixSort();  
        for (k=1;k+1<=N;k*=2)  
        {  
            for (i=1;i<=N;i++)  
                RE[i].id=i,RE[i].k[0]=Rank[i],RE[i].k[1]=i+k<=N?Rank[i+k]:0;  
            RadixSort();  
        }  
        for (i=1;i<=N;i++)  
            SA[ Rank[i] ]=i;  
    }  
    void CalcHeight()  
    {  
        int i,k,h=0;  
        for (i=1;i<=N;i++)  
        {  
            if (Rank[i]==1)  
                h=0;  
            else  
            {  
                k=SA[Rank[i]-1];  
                if (--h<0) h=0;  
                for (;A[i+h]==A[k+h];h++);  
            }  
            Height[Rank[i]]=h;  
        }  
    }  
}SA;  
int N,Ans,Bel[MAXL];  
char S[MAXL];  
void init()  
{  
    int i;  
    ifstream in("pow.in");
    in>>N;
    SA.N=0;  
    for (i=1;i<=N;i++)  
    {  
       int len = 0; 
       in>>len; 
       for(int p = 0;p<len;p++){
            int tmp = 0;
            in>>tmp;
          //  scanf("%d",&tmp);
            SA.A[++SA.N] = tmp;
            Bel[SA.N]=i;
        }    
        if (i<N)  
            SA.A[++SA.N]=1000+i;  
    } 
   in.close(); 
}  
bool check(int A)  
{  
    int i,j,k;  
    bool ba[MAXN];  
    for (i=1;i<=SA.N;i++)  
    {  
        if (SA.Height[i]>=A)  
        {  
            for (j=i;SA.Height[j]>=A && j<=SA.N;j++);  
            j--;  
            memset(ba,0,sizeof(ba));  
            for (k=i-1;k<=j;k++)  
                ba[Bel[SA.SA[k]]]=true;  
            for (k=1;ba[k] && k<=N;k++);  
            if (k==N+1)  
                return true;  
            i=j;  
        }  
    }  
    return false;  
}  
void mysolve()  
{  
    int i,j,k;  
    stack<stkele>stk;
    std::vector<resele> v;
    ofstream out("pow.out");
    SA.CalcSA();  
    SA.CalcHeight();  
//    for(i = 1;i<=SA.N;i++)printf("%d ",SA.SA[i]);
//    printf("\n");
    for(i = 1;i<=SA.N;i++)
 out<<SA.Rank[i]<<"\t";
 out<<endl;
 int maxlen = 0;
 int maxcover = 0;
 int maxidx = 0;
    for (i=1;i<=SA.N;i++)  
    {
        if(stk.empty()||SA.Height[i]>=stk.top().height)
            stk.push(stkele(SA.Height[i],i-1,Bel[SA.SA[i]],Bel[SA.SA[i-1]]));
        else{
            bool ba[MAXN];
            int cover = 0;
            memset(ba,0,sizeof(ba));
            while(!stk.empty()&&SA.Height[i]<stk.top().height){
                stkele top(stk.top());
                stk.pop();
                for(int i =1;i<=N;i++){
                    if(ba[i]==false&&top.ba[i]==true){
                        cover+=1;
                        ba[i] = true;
                    }
                }
              //  v.push_back(resele(top.height,cover,top.loc));
              //  printf("%d\t%d\t%d\n",top.height,cover,top.loc);
              if(top.height*cover>maxlen*maxcover){
                  maxlen = top.height;
                  maxcover = cover;
                  maxidx = top.loc;
              }
          //  out<<top.height<<'\t'<<cover<<'\t'<<top.loc<<endl;
            }
            ba[Bel[SA.SA[i]]] = true;
            ba[Bel[SA.SA[i-1]]] = true;
            stkele tmp(SA.Height[i],i-1,Bel[SA.SA[i]],Bel[SA.SA[i-1]]);
            memcpy(&tmp.ba[0],&ba[0],sizeof(ba));
            stk.push(tmp);
        }
    }
            bool ba[MAXN];
            int cover2 = 0;
            memset(ba,0,sizeof(ba));
            while(!stk.empty()){
                stkele top2(stk.top());
                stk.pop();
                for(int i =1;i<=N;i++){
                    if(ba[i]==false&&top2.ba[i]==true){
                        cover2+=1;
                        ba[i] = true;
                    }
                }
              //  v.push_back(resele(top.height,cover,top.loc));
              if(top2.height*cover2>maxlen*maxcover){
                  maxlen = top2.height;
                  maxcover = cover2;
                  maxidx = top2.loc;
              }
           out<<maxlen<<'\t'<<maxcover<<'\t'<<maxidx<<endl;
            }
    /*
        if (SA.Height[i]>=A)  
        {  
            for (j=i;SA.Height[j]>=A && j<=SA.N;j++);  
            j--;  
            memset(ba,0,sizeof(ba));  
            for (k=i-1;k<=j;k++)  
                ba[Bel[SA.SA[k]]]=true;  
            for (k=1;ba[k] && k<=N;k++);  
            if (k==N+1)  
                return true;  
            i=j;  
        }*/    
            out.close();
} 
/*
void solve()  
{  
    int a,b,m;  
    SA.CalcSA();  
    SA.CalcHeight();  
    a=0;b=SA.N;  
    while (a+1<b)  
    {  
        m=(a+b)/2;  
        if (check(m))  
            a=m;  
        else  
            b=m-1;  
    }  
    if (check(b))  
        a=b;  
    Ans=a;  
}*/  
extern "C"{
    int solve(){
        try{
        init();
        mysolve();
        }
        catch(exception e){
            fstream out("pow.out");
            out<<0<<endl;
            out<<0<<'\t'<<0<<'\t'<<0<<endl;
            out.close();
          //  cout<<e.what()<<endl;
        
        //    return 0;
        }
        return 1;
    }
}
