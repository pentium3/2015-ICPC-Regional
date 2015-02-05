/*
PROB:ratios
LANG:C++
*/

#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <iostream>
using namespace std;
#define maxn 5
double A[5][5],a[5][5];

typedef double Matrix[maxn][maxn];

void solve(Matrix A,int n)		//A为增广矩阵，n维
{
    int i,j,k,r;

    for (i=0;i<n;i++)
    {
        r=i;
        for (j=i+1;j<n;j++)
            if (fabs(A[j][i])>fabs(A[r][i]))
                r=j;
        if (r!=i)
            for (j=0;j<=n;j++)
                swap(A[r][j],A[i][j]);

        for (k=i+1;k<n;k++)
        {
            double f=A[k][i]/A[i][i];
            for (j=i;j<=n;j++)
                A[k][j]-=f*A[i][j];
        }
    }
    for (i=n-1;i>=0;i--)
    {
        for (j=i+1;j<n;j++)
            A[i][n]-=A[j][n]*A[i][j];
        A[i][n]/=A[i][i];
    }
}

bool satisify(double x,double y,double z)
{
    int t1=x+0.5,t2=y+0.5,t3=z+0.5;     //+0.5四舍五入，处理精度问题
                                        //比如原来是4.9999999，直接转成int就成了4，完蛋啦T^T
    double xx=x-t1,yy=y-t2,zz=z-t3;
    double comp=pow(10,-5);             //double的比较法= =，差值小于10^-10就算相等了
    if ((fabs(xx)<=comp)&&(fabs(yy)<=comp)&&(fabs(zz)<=comp))
        return true;
    else
        return false;
}

int main()
{
    freopen("ratios.in","r",stdin);
    freopen("ratios.out","w",stdout);

    int x,y,z,t1,t2,t3;
    double dx,dy,dz;
    bool sol=false;

    scanf("%d %d %d",&x,&y,&z);
    //A[0][3]=x;  A[1][3]=y;  A[2][3]=z;
    t1=x;   t2=y;   t3=z;
    scanf("%d %d %d",&x,&y,&z);
    A[0][0]=x;  A[1][0]=y;  A[2][0]=z;
    scanf("%d %d %d",&x,&y,&z);
    A[0][1]=x;  A[1][1]=y;  A[2][1]=z;
    scanf("%d %d %d",&x,&y,&z);
    A[0][2]=x;  A[1][2]=y;  A[2][2]=z;

    for (int i=1;i<=100;i++)
    {
        for (int i=0;i<=2;i++)
            for (int j=0;j<=3;j++)
                a[i][j]=A[i][j];
        a[0][3]=t1*i;
        a[1][3]=t2*i;
        a[2][3]=t3*i;
        //printf("%.8f %.8f %.8f\n",a[0][3],a[1][3],a[2][3]);
        solve(a,3);
        dx=a[0][3];     dy=a[1][3];     dz=a[2][3];
        //printf("%.8f %.8f %.8f\n",dx,dy,dz);
        if (satisify(dx,dy,dz))
        {
            sol=true;
            int xx=dx,yy=dy,zz=dz;
            //printf("%d %d %d\n",xx,yy,zz);
            if (xx<0||yy<0||zz<0)
                printf("NONE\n");
            else
            {
                xx=dx+0.5;  yy=dy+0.5;  zz=dz+0.5;
                printf("%d %d %d %d\n",xx,yy,zz,i);
            }
            break;
        }
        //printf("%.8f %.8f %.8f\n",a[0][3],a[1][3],a[2][3]);
    }
    if (!sol) printf("NONE\n");

}