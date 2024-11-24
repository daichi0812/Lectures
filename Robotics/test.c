#include<stdio.h>
#include<math.h>

#define N M_PI/4
double radianToDegree(double radian) {
    double degree = radian * (180.0 / M_PI);
    return degree;
}
int main(){
	
	int a;
	double px,py,pz;
	double value,value1,value2,value3,value4,value5,value6;
	double theta1,theta2,theta3,theta4,theta5,theta6;
	
	double d2,d3;
	
	double r;
	
	
	px=0.4*cos(N);
	py=0.5;
	pz=0.4*sin(N);
	
	printf("px=%lf\n",px);
	printf("py=%lf\n",py);
	printf("pz=%lf\n",pz);
	
	d2 = 0.38;
	
	int nx=1,ny=0,nz=0,ox=0,oy=0,oz=-1,ax=0,ay=1,az=0;
	
	
r=px*px+py*py;
r=sqrt(r);
value=r*r-d2*d2;
value=sqrt(value);
value=d2/value;
theta1=atan2(py,px)-atan(value);

value1=pz;
value2=cos(theta1)*px+sin(theta1)*py;
theta2=atan2(value2,value1);
d3=sin(theta2)*(cos(theta1)*px+sin(theta1)*py)+cos(theta2)*pz;
value1=cos(theta2)*(cos(theta1)*ax+sin(theta1)*ay)-sin(theta2)*az;
value2=-sin(theta1)*ax+cos(theta1)*ay;
value=value2/value1;
theta4=atan(value); 
value1=sin(theta2)*(cos(theta1)*ax+sin(theta1)*ay)+cos(theta2)*az;
value2=cos(theta4)*(cos(theta2)*(cos(theta1)*ax+sin(theta1)*ay)-sin(theta2)*az)+sin(theta4)*(-sin(theta1)*ax+cos(theta1)*ay);

theta5=atan2(value2,value1); 
if(theta5<0){
	theta4=theta4+M_PI;
	value1=sin(theta2)*(cos(theta1)*ax+sin(theta1)*ay)+cos(theta2)*az;
value2=cos(theta4)*(cos(theta2)*(cos(theta1)*ax+sin(theta1)*ay)-sin(theta2)*az)+sin(theta4)*(-sin(theta1)*ax+cos(theta1)*ay);

theta5=atan2(value2,value1);
	
}

	
value1=(-1.0)*sin(theta4)*(cos(theta2)*(cos(theta1)*ox+sin(theta1)*oy)-sin(theta2)*oz)+cos(theta4)*(-sin(theta1)*ox+cos(theta1)*oy);

value2=(-1.0)*cos(theta5)*(cos(theta4)*(cos(theta2)*(cos(theta1)*ox+sin(theta1)*oy)-sin(theta2)*oz)+sin(theta4)*(-sin(theta1)*ox+cos(theta1)*oy))+sin(theta5)*(sin(theta2)*(cos(theta1)*ox+sin(theta1)*oy)+cos(theta2)*oz);




theta6=atan2(value2,value1); 

printf("theta1=%lf\n",radianToDegree(theta1));
	printf("theta2=%lf\n",radianToDegree(theta2));
	printf("theta3=%lf\n",radianToDegree(theta3));
	printf("theta4=%lf\n",radianToDegree(theta4));
	printf("theta5=%lf\n",radianToDegree(theta5));
	printf("theta6=%lf\n",radianToDegree(theta6));
	return 0;
}

	