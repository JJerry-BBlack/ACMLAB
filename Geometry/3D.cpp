namespace Geometry3 {
	const double eps=1e-9;
	inline int dcmp(double x){
		if(fabs(x)<eps)return 0;
		return x<0?-1:1;
	}
	inline double Hypot(double a,double b,double c){
		return sqrt(a*a+b*b+c*c);
	}
	struct Point3{
		double x,y,z;
		Point3(){}
		Point3(double x,double y,double z):x(x),y(y),z(z){}
	};
	typedef Point3 Vector3;
	Vector3 operator + (const Vector3 &a,const Vector3 &b){
		return Vector3(a.x+b.x,a.y+b.y,a.z+b.z);
	}
	Vector3 operator - (const Vector3 &a,const Vector3 &b){
		return Vector3(a.x-b.x,a.y-b.y,a.z-b.z);
	}
	Vector3 operator * (const Vector3 &a,const double k){
		return Vector3(a.x*k,a.y*k,a.z*k);
	}
	Vector3 operator / (const Vector3 &a,const double k){
		return Vector3(a.x/k,a.y/k,a.z/k);
	}
	bool operator == (const Vector3 &a,const Vector3 &b){
		return dcmp(a.x-b.x)==0&&dcmp(a.y-b.y)==0&&dcmp(a.z-b.z)==0;
	}
	inline double Dot(Vector3 a,Vector3 b){
		return a.x*b.x+a.y*b.y+a.z*b.z;
	}
	inline double Length(Vector3 a){
		return sqrt(Dot(a,a));
	}
	inline Vector3 CrossVector(Vector3 v1,Vector3 v2){
		return Vector3(v1.y*v2.z-v1.z*v2.y,v1.z*v2.x-v1.x*v2.z,v1.x*v2.y-v1.y*v2.x);
	}
	inline double Cross(Vector3 a,Vector3 b){
		return Length(CrossVector(a,b));
	}
	inline double Distance(Point3 a,Point3 b){
		return Hypot(a.x-b.x,a.y-b.y,a.z-b.z);
	}
	struct Line3{
		Point3 s,e;
		Line3(){}
		Line3(Point3 _s,Point3 _e){
			s=_s;
			e=_e;
		}
		bool isPointOnSegment(Point3 &p){
			return dcmp(Cross(p-s,e-s))==0&&dcmp(Dot(p-s,p-e))<=0;
		}
		bool isPointOnLine(Point3 &p){
			return dcmp(Cross(p-s,e-s))==0;
		}
		bool isParallel(Line3 &l){
			return dcmp(Cross(e-s,l.e-l.s))==0;
		}
		double getDistance(Point3 &p){
			return fabs(Cross(p-s,p-e)/Distance(s,e));
		}
		double getDistanceToSegment(Point3 &p){
			if(Dot(e-s,p-s)<0)return Distance(s,p);
			if(Dot(s-e,p-e)<0)return Distance(e,p);
			return getDistance(p);
		}
		double getDistanceToLine(Line3 &l){
			Vector3 x=CrossVector(s-e,l.s-l.e);
			return fabs(Dot(x,s-l.s))/Length(x);
		}
		double getAngleCosineToLine(Line3 &l){
			return Dot(s-e,l.s-l.e)/Length(s-e)/Length(l.s-l.e);
		}
	};
	struct Plane{
		Point3 a,b,c,v;
		Plane(){}
		Plane(Point3 _a,Point3 _b,Point3 _c){
			a=_a;
			b=_b;
			c=_c;
			v=CrossVector(a-b,a-c);
		}
		Plane(Point3 _a,Vector3 _v){
			a=_a;
			v=_v;
		}
		bool isPointOnTriangle(Point3 &p){
			return dcmp(Cross(a-b,a-c)-Cross(p-a,p-b)-Cross(p-b,p-c)-Cross(p-c,p-a))==0;
		}
		bool isParallel(Plane &p){
			return dcmp(Cross(v,p.v))==0;
		}
		int getIntersectLine(Plane &p,Line3 &l){
			Vector3 r=CrossVector(v,p.v),v=CrossVector(v,r);
			double d=Dot(p.v,v);
			if(dcmp(d)==0) return 0;
			l.s=a+v*(Dot(p.v,p.a-a)/d);
			l.e=l.s+r;
			return 1;
		}
		double getDistance(Point3 &p){
			return fabs(Dot(v,p-a))/Length(v);
		}
		double getAngleCosineToPlane(Plane &p){
			return Dot(v,p.v)/Length(v)/Length(p.v);
		}
		double getAngleSineToLine(Line3 &l){
			return Dot(l.s-l.e,v)/Length(l.s-l.e)/Length(v);
		}
	};
	struct Circle3{
		Point3 o; double r;
		Circle3(){}
		Circle3(Point3 o,double r):o(o),r(r){}
		int getIntersectPoints(Line3 &l,vector<Point3> &vec){
			if(dcmp(l.getDistance(o)-r)>0)return 0;
			Vector3 v=l.e-l.s;
			Point3 p=l.s+v*(Dot(o-l.s,v))/Dot(v,v);
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
	};
}
using namespace Geometry3;