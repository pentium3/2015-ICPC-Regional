计算几何模板
  1 #include<math.h>
  2 #define MAXN 1000
  3 #define offset 10000
  4 #define eps 1e-8
  5 #define PI acos(-1.0)//3.14159265358979323846
  6 //判断一个数是否为0,是则返回true,否则返回false
  7 #define zero(x)(((x)>0?(x):-(x))<eps)
  8 //返回一个数的符号，正数返回1，负数返回2，否则返回0
  9 #define _sign(x)((x)>eps?1:((x)<-eps?2:0))
 10 struct point 
 11 {
 12     double x,y;
 13 };
 14 struct line
 15 {
 16     point a,b;
 17 };//直线通过的两个点，而不是一般式的三个系数
 18 //求矢量[p0,p1],[p0,p2]的叉积
 19 //p0是顶点
 20 //若结果等于0，则这三点共线
 21 //若结果大于0，则p0p2在p0p1的逆时针方向
 22 //若结果小于0，则p0p2在p0p1的顺时针方向
 23 double xmult(point p1,point p2,point p0)
 24 {
 25     return(p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
 26 }
 27 //计算dotproduct(P1-P0).(P2-P0)
 28 double dmult(point p1,point p2,point p0)
 29 {
 30     return(p1.x-p0.x)*(p2.x-p0.x)+(p1.y-p0.y)*(p2.y-p0.y);
 31 }
 32 //两点距离
 33 double distance(point p1,point p2)
 34 {
 35     return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
 36 }
 37 //判三点共线
 38 int dots_inline(point p1,point p2,point p3)
 39 {
 40     return zero(xmult(p1,p2,p3));
 41 }
 42 //判点是否在线段上,包括端点
 43 int dot_online_in(point p,line l)
 44 {
 45     return zero(xmult(p,l.a,l.b))&&(l.a.x-p.x)*(l.b.x-p.x)<eps&&(l.a.y-p.y)*(l.b.y-p.y)<eps;
 46 }
 47 //判点是否在线段上,不包括端点
 48 int dot_online_ex(point p,line l)
 49 {
 50     return dot_online_in(p,l)&&(!zero(p.x-l.a.x)||!zero(p.y-l.a.y))&&(!zero(p.x-l.b.x)||!zero(p.y-l.b.y));
 51 }
 52 //判两点在线段同侧,点在线段上返回0
 53 int same_side(point p1,point p2,line l)
 54 {
 55     return xmult(l.a,p1,l.b)*xmult(l.a,p2,l.b)>eps;
 56 }
 57 //判两点在线段异侧,点在线段上返回0
 58 int opposite_side(point p1,point p2,line l)
 59 {
 60     return xmult(l.a,p1,l.b)*xmult(l.a,p2,l.b)<-eps;
 61 }
 62 //判两直线平行
 63 int parallel(line u,line v)
 64 {
 65     return zero((u.a.x-u.b.x)*(v.a.y-v.b.y)-(v.a.x-v.b.x)*(u.a.y-u.b.y));
 66 }
 67 //判两直线垂直
 68 int perpendicular(line u,line v)
 69 {
 70     return zero((u.a.x-u.b.x)*(v.a.x-v.b.x)+(u.a.y-u.b.y)*(v.a.y-v.b.y));
 71 }
 72 //判两线段相交,包括端点和部分重合
 73 int intersect_in(line u,line v)
 74 {
 75     if(!dots_inline(u.a,u.b,v.a)||!dots_inline(u.a,u.b,v.b))
 76         return!same_side(u.a,u.b,v)&&!same_side(v.a,v.b,u);
 77     return dot_online_in(u.a,v)||dot_online_in(u.b,v)||dot_online_in(v.a,u)||dot_online_in(v.b,u);
 78 }
 79 //判两线段相交,不包括端点和部分重合
 80 int intersect_ex(line u,line v)
 81 {
 82     return opposite_side(u.a,u.b,v)&&opposite_side(v.a,v.b,u);
 83 }
 84 //计算两直线交点,注意事先判断直线是否平行!
 85 //线段交点请另外判线段相交(同时还是要判断是否平行!)
 86 point intersection(line u,line v)
 87 {
 88     point ret=u.a;
 89     double t=((u.a.x-v.a.x)*(v.a.y-v.b.y)-(u.a.y-v.a.y)*(v.a.x-v.b.x))/((u.a.x-u.b.x)*(v.a.y-v.b.y)-(u.a.y-u.b.y)*(v.a.x-v.b.x));
 90     ret.x+=(u.b.x-u.a.x)*t;
 91     ret.y+=(u.b.y-u.a.y)*t;
 92     return ret;
 93 }
 94 //点到直线上的最近点
 95 point ptoline(point p,line l)
 96 {
 97     point t=p;
 98     t.x+=l.a.y-l.b.y,t.y+=l.b.x-l.a.x;
 99     return intersection(p,t,l.a,l.b);
100 }
101 //点到直线距离
102 double disptoline(point p,line l)
103 {
104     return fabs(xmult(p,l.a,l.b))/distance(l.a,l.b);
105 }
106 //点到线段上的最近点
107 point ptoseg(point p,line l)
108 {
109     point t=p;
110     t.x+=l.a.y-l.b.y,t.y+=l.b.x-l.a.x;
111     if(xmult(l.a,t,p)*xmult(l.b,t,p)>eps)
112         return distance(p,l.a)<distance(p,l.b)?l.a:l.b;
113     return intersection(p,t,l.a,l.b);
114 }
115 //点到线段距离
116 double disptoseg(point p,line l)
117 {
118     point t=p;
119     t.x+=l.a.y-l.b.y,t.y+=l.b.x-l.a.x;
120     if(xmult(l.a,t,p)*xmult(l.b,t,p)>eps)
121         return distance(p,l.a)<distance(p,l.b)?distance(p,l.a):distance(p,l.b);
122     return fabs(xmult(p,l.a,l.b))/distance(l.a,l.b);
123 }
124 struct TPoint
125 {
126     double x,y;
127     TPoint operator-(TPoint&a)
128     {
129         TPoint p1;
130         p1.x=x-a.x;
131         p1.y=y-a.y;
132         return p1;
133     }
134 };
135 
136 struct TLine
137 {
138     double a,b,c;
139 };
140 
141 //求p1关于p2的对称点
142 TPoint symmetricalPoint(TPoint p1,TPoint p2)
143 {
144     TPoint p3;
145     p3.x=2*p2.x-p1.x;
146     p3.y=2*p2.y-p1.y;
147     return p3;
148 }
149 //p点关于直线L的对称点
150 TPoint symmetricalPointofLine(TPoint p,TLine L)
151 {
152     TPoint p2;
153     double d;
154     d=L.a*L.a+L.b*L.b;
155     p2.x=(L.b*L.b*p.x-L.a*L.a*p.x-2*L.a*L.b*p.y-2*L.a*L.c)/d;
156     p2.y=(L.a*L.a*p.y-L.b*L.b*p.y-2*L.a*L.b*p.x-2*L.b*L.c)/d;
157     return p2;
158 }
159 //求线段所在直线,返回直线方程的三个系数
160 //两点式化为一般式
161 TLine lineFromSegment(TPoint p1,TPoint p2)
162 {
163     TLine tmp;
164     tmp.a=p2.y-p1.y;
165     tmp.b=p1.x-p2.x;
166     tmp.c=p2.x*p1.y-p1.x*p2.y;
167     return tmp;
168 }
169 //求直线的交点
170 //求直线的交点，注意平行的情况无解，避免RE
171 TPoint LineInter(TLine l1,TLine l2)
172 {
173     //求两直线得交点坐标
174     TPoint tmp;
175     double a1=l1.a;
176     double b1=l1.b;
177     double c1=l1.c;
178     double a2=l2.a;
179     double b2=l2.b;
180     double c2=l2.c;
181     //注意这里b1=0
182     if(fabs(b1)<eps){
183         tmp.x=-c1/a1;
184         tmp.y=(-c2-a2*tmp.x)/b2;
185     }
186     else{
187         tmp.x=(c1*b2-b1*c2)/(b1*a2-b2*a1);
188         tmp.y=(-c1-a1*tmp.x)/b1;
189     }
190     //cout<<"交点坐标"<<endl;
191     //cout<<a1*tmp.x+b1*tmp.y+c1<<endl;
192     //cout<<a2*tmp.x+b2*tmp.y+c2<<endl;
193     return tmp;
194 }
195 //矢量（点）V以P为顶点逆时针旋转angle(弧度)并放大scale倍
196 point rotate(point v,point p,double angle,double scale){
197     point ret=p;
198     v.x-=p.x,v.y-=p.y;
199     p.x=scale*cos(angle);
200     p.y=scale*sin(angle);
201     ret.x+=v.x*p.x-v.y*p.y;
202     ret.y+=v.x*p.y+v.y*p.x;
203     return ret;
204 }
205 //矢量（点）V以P为顶点逆时针旋转angle(弧度)
206 point rotate(point v,point p,double angle){
207     double cs=cos(angle),sn=sin(angle);
208     v.x-=p.x,v.y-=p.y;
209     p.x+=v.x*cs-v.y*sn;
210     p.y+=v.x*sn+v.y*cs;
211     return p;
212 }
