#include "func.h"
#include "util.h"

void func0(double *weights, double *arrayX, double *arrayY, int xr, int yr, int n)
{
	int i;
	double dn = 1/((double)(n));
	#pragma omp parallel for private(i)
	for(i = 0; i < n-2; i+=3){
		weights[i] = dn;
		arrayX[i] = xr;
		arrayY[i] = yr;
		
		weights[i+1] = dn;
		arrayX[i+1] = xr;
		arrayY[i+1] = yr;
		
		weights[i+2] = dn;
		arrayX[i+2] = xr;
		arrayY[i+2] = yr;
	}
	for(;i<n;i++){
		weights[i] = dn;
		arrayX[i] = xr;
		arrayY[i] = yr;	
	}
}

void func1(int *seed, int *array, double *arrayX, double *arrayY,
			double *probability, double *objxy, int *index,
			int Ones, int iter, int X, int Y, int Z, int n)
{
	int i, j;
   	int index_X, index_Y;
	int max_size = X*Y*Z;
	
	#pragma omp parallel for
   	for(i = 0; i < n; i++){
   		arrayX[i] += 1 + 5*rand2(seed, i);
   		arrayY[i] += -2 + 2*rand2(seed, i);
   	}
	
	double temp1,temp2,temp3;
	int *ip;
	#pragma omp parallel for private(temp1,temp2,ip,i,j,index_X,index_Y)
   	for(i = 0; i<n; i++){
	temp1 = round(arrayX[i]);
	temp2 = round(arrayY[i]);
	ip = &index[i*Ones];
	int yz = Y*Z;
   		for(j = 0; j < Ones-2; j+=3){
			int jj = j*2;
   			index_X = temp1 + objxy[jj + 1];
   			index_Y = temp2 + objxy[jj];
   			int j1 = fabs(index_X*yz  + index_Y*Z + iter);
   			ip[j] = (j1>max_size)? 0:j1;
			
			index_X = temp1 + objxy[jj + 3];
   			index_Y = temp2 + objxy[jj+2];
   			int j2 = fabs(index_X*yz  + index_Y*Z + iter);
   			ip[j+1] = (j2>max_size)? 0:j2;
			
			index_X = temp1 + objxy[jj + 5];
   			index_Y = temp2 + objxy[jj+4];
   			int j3 = fabs(index_X*yz  + index_Y*Z + iter);
   			ip[j+2] = (j3>max_size)? 0:j3;
   		}
		for(;j<Ones;j++){
			index_X = temp1 + objxy[j*2 + 1];
   			index_Y = temp2 + objxy[j*2];
   			ip[j] = fabs(index_X*yz  + index_Y*Z + iter);
   			if(ip[j] >= max_size)
   				ip[j] = 0;
		}
   	}

	#pragma omp parallel for private(temp3,ip,j)
	for(i = 0; i<n; i++){
		temp3 = 0;
		ip = &index[i*Ones];
	   	for(j = 0; j < Ones-2; j+=3) {
	   		double t1 = (pow((array[ ip[j] ] - 100),2) - pow((array[ ip[j] ]-228),2))/50.0;
			double t2 = (pow((array[ ip[j+1] ] - 100),2) - pow((array[ ip[j+1] ]-228),2))/50.0;
			double t3 = (pow((array[ ip[j+2] ] - 100),2) - pow((array[ ip[j+2] ]-228),2))/50.0;
			temp3 += t1+t2+t3;
	   	}
		for (;j<Ones;j++) {
			temp3 += (pow((array[ ip[j] ] - 100),2) - pow((array[ ip[j] ]-228),2))/50.0;
		}
		probability[i] = temp3/((double) Ones);
	}

}

void func2(double *weights, double *probability, int n)
{
	int i;
	double sumWeights=0;
	#pragma omp parallel for
	for(i = 0; i < n-2; i+=3){
   		weights[i] = weights[i] * exp(probability[i]);
		weights[i+1] = weights[i+1] * exp(probability[i+1]);
		weights[i+2] = weights[i+2] * exp(probability[i+2]);
	}
	for(;i<n;i++){
   		weights[i] = weights[i] * exp(probability[i]);
	}
	
	#pragma omp parallel for reduction(+:sumWeights)
   	for(i = 0; i < n; i++){
   		sumWeights += weights[i];
	}
	
	#pragma omp parallel for
	for(i = 0; i < n; i++){
		weights[i] = weights[i]/sumWeights;
	}
}

void func3(double *arrayX, double *arrayY, double *weights, double *x_e, double *y_e, int n)
{
	double estimate_x=0.0;
	double estimate_y=0.0;
    int i;

	#pragma omp parallel for reduction(+:estimate_x)
	for(i = 0; i < n; i++){
   		estimate_x += arrayX[i] * weights[i];
   	}
	#pragma omp parallel for reduction(+:estimate_y)
	for(i = 0; i < n; i++){
   		estimate_y += arrayY[i] * weights[i];
   	}
	

	*x_e = estimate_x;
	*y_e = estimate_y;

}

void func4(double *u, double u1, int n)
{
	int i;
	#pragma omp parallel for
	for(i = 0; i < n; i++){
   		u[i] = u1 + i/((double)(n));
   	}
}

void func5(double *x_j, double *y_j, double *arrayX, double *arrayY, double *weights, double *cfd, double *u, int n)
{
	int i, j;
	#pragma omp parallel for private(i)
	for(j = 0; j < n; j++){
   		//i = findIndex(cfd, n, u[j]);
   		i = findIndexBin(cfd, 0, n, u[j]);
   		if(i == -1)
   			i = n-1;
   		x_j[j] = arrayX[i];
   		y_j[j] = arrayY[i];

   	}
	
	double dn = 1/((double)(n));
	#pragma omp parallel for
	for(i = 0; i < n; i++){
		arrayX[i] = x_j[i];
		arrayY[i] = y_j[i];
		weights[i] = dn;
	}
}
