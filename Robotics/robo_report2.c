#include<stdio.h>
#include<math.h>

double Degree(double radian);

int main(){
	double nx, ny, nz, ox, oy, oz, ax, ay, az, px, py, pz;
	double value, value1, value2, value4, value5, value6;
	double theta1, theta2, theta3, theta4, theta5, theta6;
	double d2, d3;
	double r;
	double i, N;
	
	N = M_PI / 4.0;
	
	i = 7.0;
	
	nx = ay = 1.0;
	ny = nz = ox = oy = ax = az =0.0;
	oz = -1.0;
	px = 0.0 + 1.0 * 0.4 * cos(i * N) + 0.0 * 0.4 * sin(i * N);
	py= 0.5 + 0.0 * 0.4 * cos(i * N) + 0.0 * 0.4 * sin(i * N);
	pz= 0.0 + 0.0 * 0.4 * cos(i * N) + 1.0 * 0.4 * sin(i * N);
	
	printf("px = %lf\n", px);
	printf("py = %lf\n", py);
	printf("pz = %lf\n", pz);
	printf("\n");
	
	d2 = 0.38;
	
	r = px * px + py * py;
	r = sqrt(r);
	
	value = r * r - d2 * d2;
	value = sqrt(value);
	value = d2 / value;
	
	theta1 = atan2(py, px) - atan(value);

	value1 = pz;
	value2 = cos(theta1) * px + sin(theta1) * py;
	
	theta2 = atan2(value2, value1);
	
	d3 = sin(theta2) * (cos(theta1) * px + sin(theta1) * py) + cos(theta2) * pz;
	
	value1 = cos(theta2) * (cos(theta1) * ax + sin(theta1) * ay) - sin(theta2) * az;
	value2 = -sin(theta1) * ax + cos(theta1) * ay;
	value = value2 / value1;
	
	theta4 = atan(value); 
	
	value1 = sin(theta2) * (cos(theta1) * ax + sin(theta1) * ay) + cos(theta2) * az;
	value2 = cos(theta4) * (cos(theta2) * (cos(theta1) * ax + sin(theta1) * ay) - 
			sin(theta2) * az) + sin(theta4) * (-sin(theta1) * ax + cos(theta1) * ay);

	theta5 = atan2(value2, value1); 
	
	if(theta5<0){
		theta4 = theta4 + M_PI;
		value1 = sin(theta2) * (cos(theta1) * ax + sin(theta1) * ay) + cos(theta2) * az;
		value2 = cos(theta4) * (cos(theta2) * (cos(theta1) * ax + sin(theta1) * ay) - 
				sin(theta2) * az) + sin(theta4) * (-sin(theta1) * ax + cos(theta1) * ay);

		theta5 = atan2(value2, value1);
	}

	value1 = (-1.0) * sin(theta4) * (cos(theta2) * (cos(theta1) * ox +
			sin(theta1) * oy) - sin(theta2) * oz) + cos(theta4) * (-sin(theta1) * ox + cos(theta1) * oy);
	value2 = (-1.0) * cos(theta5) * (cos(theta4) * (cos(theta2) * (cos(theta1) * ox + 
			sin(theta1) * oy) - sin(theta2) * oz) + sin(theta4) * (-sin(theta1) * ox + 
			cos(theta1) * oy)) + sin(theta5) * (sin(theta2) * (cos(theta1) * ox + 
			sin(theta1) * oy) + cos(theta2) * oz);

	theta6 = atan2(value2, value1); 
	
	printf("theta1 = %lf\n", Degree(theta1));
	printf("theta2 = %lf\n", Degree(theta2));
	printf("    d3 = %lf\n", d3);
	printf("theta4 = %lf\n", Degree(theta4));
	printf("theta5 = %lf\n", Degree(theta5));
	printf("theta6 = %lf\n", Degree(theta6));
	printf("\n");
	
	printf("%lf %lf %lf %lf %lf %lf", Degree(theta1), Degree(theta2), d3, Degree(theta4), Degree(theta5), Degree(theta6));
	
	return 0;
}

double Degree(double radian){
    double degree = radian * (180.0 / M_PI);
	
    return degree;
}