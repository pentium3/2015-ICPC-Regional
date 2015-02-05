//xudyh_gcd					hdu5019
//��x��y�ĵ�k��Լ��
#include ������������������������������������������������
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define all(x) (x).begin(),(x).end()
//#define fi first
#define se second						#define SZ(x) ((int)(x).size())
#define TWO(x) (1<<(x))				#define TWOL(x) (1ll<<(x))
#define clr(a) memset(a,0,sizeof(a))
#define POSIN(x,y) (0<=(x)&&(x)<n&&0<=(y)&&(y)<m)
typedef vector<int> VI;					typedef vector<string> VS;
typedef vector<double> VD;				typedef long long ll;
typedef long double LD;					typedef pair<int,int> PII;
typedef pair<ll,ll> PLL;					typedef vector<ll> VL;
typedef vector<PII> VPII;					typedef complex<double> CD;
const int inf=0x20202020;					const ll mod=1000000007;
const double eps=1e-9;

ll powmod(ll a,ll b)             //return (a*b)%mod
{ll res=1;a%=mod;for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll powmod(ll a,ll b,ll mod)     //return (a*b)%mod
{ll res=1;a%=mod;for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll gcd(ll a,ll b)                 //return gcd(a,b)
{ return b?gcd(b,a%b):a;}
// head

namespace Factor {
    const int N=1010000;
    ll C,fac[10010],n,mut,a[1001000];
    int T,cnt,i,l,prime[N],p[N],psize,_cnt;
    ll _e[100],_pr[100];
    vector<ll> d;

    inline ll mul(ll a,ll b,ll p) {     //return (a*b)%p
        if (p<=1000000000) return a*b%p;
        else if (p<=1000000000000ll) 
return (((a*(b>>20)%p)<<20)+(a*(b&((1<<20)-1))))%p;
        else {
            ll d=(ll)floor(a*(long double)b/p+0.5);
            ll ret=(a*b-d*p)%p;
            if (ret<0) ret+=p;
            return ret;
        }
    }

    void prime_table(){     //prime[1..tot]: prime[i]=ith prime
        int i,j,tot,t1;
        for (i=1;i<=psize;i++) p[i]=i;
        for (i=2,tot=0;i<=psize;i++){
            if (p[i]==i) prime[++tot]=i;
            for (j=1;j<=tot && (t1=prime[j]*i)<=psize;j++){
                p[t1]=prime[j];
                if (i%prime[j]==0) break;
            }
        }
    }

    void init(int ps) {                 //initial
        psize=ps;
        prime_table();
    }

    ll powl(ll a,ll n,ll p) {           //return (a^n)%p
        ll ans=1;
        for (;n;n>>=1) {
            if (n&1) ans=mul(ans,a,p);
            a=mul(a,a,p);
        }
        return ans;
    }

    bool witness(ll a,ll n) {
        int t=0;
        ll u=n-1;
        for (;~u&1;u>>=1) t++;
        ll x=powl(a,u,n),_x=0;
        for (;t;t--) {
            _x=mul(x,x,n);
            if (_x==1 && x!=1 && x!=n-1) return 1;
            x=_x;
        }
        return _x!=1;
    }

    bool miller(ll n) {
        if (n<2) return 0;
        if (n<=psize) return p[n]==n;
        if (~n&1) return 0;
        for (int j=0;j<=7;j++) if (witness(rand()%(n-1)+1,n)) return 0;
        return 1;
    }

    ll gcd(ll a,ll b) {
        ll ret=1;
        while (a!=0) {
            if ((~a&1) && (~b&1)) ret<<=1,a>>=1,b>>=1;
            else if (~a&1) a>>=1; else if (~b&1) b>>=1;
            else {
                if (a<b) swap(a,b);
                a-=b;
            }
        }
        return ret*b;
    }

    ll rho(ll n) {
        for (;;) {
            ll X=rand()%n,Y,Z,T=1,*lY=a,*lX=lY;
            int tmp=20;
            C=rand()%10+3;
            X=mul(X,X,n)+C;*(lY++)=X;lX++;
            Y=mul(X,X,n)+C;*(lY++)=Y;
            for(;X!=Y;) {
                ll t=X-Y+n;
                Z=mul(T,t,n);
                if(Z==0) return gcd(T,n);
                tmp--;
                if (tmp==0) {
                    tmp=20;
                    Z=gcd(Z,n);
                    if (Z!=1 && Z!=n) return Z;
                }
                T=Z;
                Y=*(lY++)=mul(Y,Y,n)+C;
                Y=*(lY++)=mul(Y,Y,n)+C;
                X=*(lX++);
            }
        }
    }

    void _factor(ll n) {
        for (int i=0;i<cnt;i++) {
            if (n%fac[i]==0) n/=fac[i],fac[cnt++]=fac[i];}
        if (n<=psize) {
            for (;n!=1;n/=p[n]) fac[cnt++]=p[n];
            return;
        }
        if (miller(n)) fac[cnt++]=n;
        else {
            ll x=rho(n);
            _factor(x);_factor(n/x);
        }
    }

    void dfs(ll x,int dep) {
        if (dep==_cnt) d.push_back(x);
        else {
            dfs(x,dep+1);
            for (int i=1;i<=_e[dep];i++) dfs(x*=_pr[dep],dep+1);
        }
    }

    void norm() {
        sort(fac,fac+cnt);
        _cnt=0;
        rep(i,0,cnt) 
if (i==0||fac[i]!=fac[i-1]) _pr[_cnt]=fac[i],_e[_cnt++]=1;
            else _e[_cnt-1]++;
    }

    vector<ll> getd() {
        d.clear();
        dfs(1,0);
        return d;
    }

vector<ll> factor(ll n) {      //return all factors of n        
//cnt:the number of factors
        cnt=0;
        _factor(n);
        norm();
        return getd();
    }

    vector<PLL> factorG(ll n) {
        cnt=0;
        _factor(n);
        norm();
        vector<PLL> d;
        rep(i,0,_cnt) d.push_back(make_pair(_pr[i],_e[i]));
        return d;
    }

    bool is_primitive(ll a,ll p) {
        //assert(miller(p));
        vector<PLL> D=factorG(p-1);
        rep(i,0,SZ(D)) if (powmod(a,(p-1)/D[i].first,p)==1) return 0;
        return 1;
    }
}

ll x,y,k;			int _;
int main() {
    Factor::init(200000);
    for (scanf("%d",&_);_;_--) {
        scanf("%I64d%I64d%I64d",&x,&y,&k);
        vector<ll> c=Factor::factor(gcd(x,y));      
//c:all factors of gcd(x,y)
        sort(all(c));                // =all common factors of x and y
        reverse(all(c));
        if (SZ(c)<k) puts("-1"); else printf("%I64d\n",c[k-1]);
    }
}
