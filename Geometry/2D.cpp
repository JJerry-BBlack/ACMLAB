namespace Geometry{
	const double eps=1e-9;
	const double PI=acos(-1.0);
	inline int dcmp(double x){
		if(fabs(x)<eps)return 0;
		return x<0?-1:1;
	}
	inline double Hypot(double a,double b){
		return sqrt(a*a+b*b);
	}
	struct Point{
		double x,y;
		Point(){}
		Point(double x,double y):x(x),y(y){}
	};
	typedef Point Vector;
	Vector operator + (const Vector &a,const Vector &b){
		return Vector(a.x+b.x,a.y+b.y);
	}
	Vector operator - (const Vector &a,const Vector &b){
		return Vector(a.x-b.x,a.y-b.y);
	}
	Vector operator * (const Vector &a,const double k){
		return Vector(a.x*k,a.y*k);
	}
	Vector operator / (const Vector &a,const double k){
		return Vector(a.x/k,a.y/k);
	}
	bool operator == (const Vector &a,const Vector &b){
		return dcmp(a.x-b.x)==0&&dcmp(a.y-b.y)==0;
	}
	inline double Dot(Vector a,Vector b){
		return a.x*b.x+a.y*b.y;
	}
	inline double Cross(Vector a,Vector b){
		return a.x*b.y-a.y*b.x;
	}
	inline double Length(Vector a){
		return sqrt(Dot(a,a));
	}
	inline double Angle(Vector a,Vector b){
		return acos(Dot(a,b)/(Length(a)*Length(b)));
	}
	inline double Distance(Point a,Point b){
		return Hypot(a.x-b.x,a.y-b.y);
	}
	inline double TriangleArea(Point &a,Point &b,Point &c){
		return fabs(Cross(b-a,c-a)/2);
	}
	inline Vector Rotate(Vector a,double ang){
		return Vector(a.x*cos(ang)-a.y*sin(ang),a.x*sin(ang)+a.y*cos(ang));
	}
	struct StdLine{
		double a,b,c,angle;
		Point s,e;
		StdLine(){}
		StdLine(Point _s,Point _e){
			s=_s;
			e=_e;
			a=s.y-e.y;
			b=e.x-s.x;
			c=s.x*e.y-e.x*s.y;
			angle=atan2(e.y-s.y,e.x-s.x);
		}
	};
	struct Line{
		Point s,e;
		Line(){}
		Line(Point _s,Point _e){
			s=_s;
			e=_e;
		}
		bool isPointOnSegment(Point &p){
			return dcmp(Cross(p-s,e-s))==0&&dcmp(Dot(p-s,p-e))<=0;
		}
		bool isPointOnLine(Point &p){
			return dcmp(Cross(p-s,e-s))==0;
		}
		bool isParallel(Line &l){
			return dcmp(Cross(e-s,l.e-l.s))==0;
		}
		double getDistance(Point &p){
			return fabs(Cross(p-s,p-e)/Distance(s,e));
		}
		double getDistanceToSegment(Point &p){
			if(Dot(e-s,p-s)<0)return Distance(s,p);
			if(Dot(s-e,p-e)<0)return Distance(e,p);
			return getDistance(p);
		}
		Point intersectPoint(Line &l){
			return s+(e-s)*(Cross(l.e-l.s,l.s-s)/Cross(l.e-l.s,e-s));
		}
		Point symmetryPoint(Point &p){
			double a=e.x-s.x,b=e.y-s.y;
			double t=((p.x-s.x)*a+(p.y-s.y)*b)/(a*a+b*b);
			return Point(2*s.x+2*a*t-p.x,2*s.y+2*b*t-p.y);
		}
		Line getPlumbLine(double inc=20.0){
			Point p=Point((s.x+e.x)/2.0,(s.y+e.y)/2.0);
			if(dcmp(s.x-e.x)==0)return Line(p,Point(p.x+inc,p.y));
			if(dcmp(s.y-e.y)==0)return Line(p,Point(p.x,p.y+inc));
			return Line(p,Point(p.x+inc,p.y-(inc/((s.y-e.y)/(s.x-e.x)))));
		}
	};
	typedef Point Segment;
	inline int getIntersectSegment(Segment a,Segment b,Segment &res){
		if(a.y<b.x||a.x>b.y){
			res=Segment(0,0);
			return 0;
		}
		if(a.x<=b.x&&a.y>=b.y)res=b;
		else if(b.x<=a.x&&b.y>=a.y)res=a;
		else res=Segment(max(a.x,b.x),min(a.y,b.y));
		return 1;
	}
	struct Rectangle{
		Point a,b;
		Rectangle(){}
		Rectangle(Point a,Point b):a(a),b(b){}
		double area(){
			return fabs((a.x-b.x)*(a.y-b.y));
		}
		Rectangle getIntersect(Rectangle &r){
			Segment x,y;
			getIntersectSegment(Segment(a.x,b.x),Segment(r.a.x,r.b.x),x);
			getIntersectSegment(Segment(a.y,b.y),Segment(r.a.y,r.b.y),y);
			return Rectangle(Point(x.x,y.x),Point(x.y,y.y));
		}
	};
	struct Polygon{
		int n; vector<Point> p;
		Polygon(){n=0;}
		void init(){
			p.clear();
			n=0;
		}
		void push(Point &a){
			p.push_back(a);
			n++;
		}
		void pop(){
			p.pop_back();
			n--;
		}
		Point back(){
			return p[n-1];
		}
		bool insidePolygon(Point &a){
			double ang=0;
			for(int i=0;i<n;i++)
			ang+=Angle(p[i]-a,p[(i+1)%n]-a);
			return dcmp(fabs(ang)-PI*2)==0;
		}
		double area(Point &o){
			double sum=0;
			for(int i=0;i<n;i++)
			sum+=Cross(p[i]-o,p[(i+1)%n]-o);
			return fabs(sum/2);
		}
		Polygon graham(){//凸包
			for(int i=1;i<n;i++)
			if(p[i].y<p[0].y||dcmp(p[i].y-p[0].y)==0&&p[i].x<p[0].x)
			swap(p[i],p[0]);
			sort(p.begin()+1,p.end(),[&](Point a,Point b){
				double r=Cross(a-p[0],b-p[0]);
				if(dcmp(r)==0)return dcmp(Distance(p[0],a)-Distance(p[0],b))<0;
				return r>0;
			});
			Polygon poly;
			poly.push(p[0]);
			poly.push(p[1]);
			for(int i=2;i<n;i++){
				while(poly.n>=2&&Cross(poly.p[poly.n-1]-poly.p[poly.n-2],p[i]-poly.p[poly.n-2])<0)
				poly.pop();
				poly.push(p[i]);
			}
			return poly;
		}
	};
	struct Circle{
		Point o; double r;
		Circle(){}
		Circle(Point o,double r):o(o),r(r){}
		double getArcLength(double ang){
			return ang*r;
		}
		double getSectorArea(double ang){
			return getArcLength(ang)*r/2;
		}
		Point getPoint(double ang){
			return Point(o.x+r*cos(ang),o.y+r*sin(ang));
		}
		int getTangentPoints(Point &p,vector<Point> &vec){
			double d=Distance(p,o),b=atan2(p.y-o.y,p.x-o.x);
			double delta=acos(r/d);
			vec.push_back(getPoint(b+delta));
			if(dcmp(delta)){
				vec.push_back(getPoint(b-delta));
				return 2;
			}
			return 1;
		}
		int getIntersectPoints(Line &l,vector<Point> &vec){
			if(dcmp(l.getDistance(o)-r)>0)return 0;
			Vector v=l.e-l.s;
			Point p=l.s+v*(Dot(o-l.s,v))/Dot(v,v);
			double b=sqrt(r*r-Dot(p-o,p-o));
			if(dcmp(b)==0){
				vec.push_back(p);
				return 1;
			}
			v=v/Length(v)*b;
			vec.push_back(p+v);
			vec.push_back(p-v);
			return 2;
		}
		int getIntersectPoints(Circle &c,vector<Point> &vec){
			double d=Distance(o,c.o);
			if(dcmp(d)==0){
				if(dcmp(r-c.r)==0)return -1;
				return 0;
			}
			if(dcmp(r+c.r-d)<0)return 0;
			if(dcmp(fabs(r-c.r)-d)>0)return 0;
			double ang=Angle(c.o-o,Vector(1,0));
			double delta=acos((r*r+d*d-c.r*c.r)/(2*r*d));
			vec.push_back(getPoint(ang+delta));
			if(dcmp(delta)){
				vec.push_back(getPoint(ang-delta));
				return 2;
			}
			return 1;
		}
	};
}
using namespace Geometry;