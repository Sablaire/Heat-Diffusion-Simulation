
#include<iostream>
#include<math.h>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#define n 11
using namespace std;
int main(){
int i,j,k,m=0;
double oldu[n][n][n],newu[n][n][n],f[n][n][n];
double dt,dy,dx,dz,a,eps,maxu;
int num;
dx=1.0/n; dy=1.0/n; dz=1.0/n; dt=0.25*dx*dy*dz/4; a=0.000019; eps=0.05;
for(i=0;i<n;i++){
	for(j=0;j<n;j++){
			for(k=0;k<n;k++){
		oldu[i][j][k]=20.0;
		newu[i][j][k]=20.0;
		f[i][j][k]=20.0;
		if (i==int(n/2) && j==int(n/2) && k==int(n/2)) f[i][j][k]=500.0;
	}
}
for(m=0;m<100000;m++){
	for(i=0;i<n;i++){
			for(j=0;j<n;j++){
		oldu[i][j][0]=oldu[i][j][1];
		newu[i][j][0]=newu[i][j][1];
		oldu[i][j][n-1]=oldu[i][j][n-2];
		newu[i][j][n-1]=newu[i][j][n-2];
			}
	}
				for(i=0;i<n;i++){
			for(k=0;k<n;k++){
		oldu[i][0][k]=oldu[i][1][k];
		newu[i][0][k]=newu[i][1][k];
		oldu[i][n-1][k]=oldu[i][n-2][k];
		newu[i][n-1][k]=newu[i][n-2][k];
			}
	}
	for(j=0;j<n;j++){
			for(k=0;k<n;k++){
		oldu[0][j][k]=oldu[1][j][k];
		newu[0][j][k]=newu[1][j][k];
		oldu[n-1][j][k]=oldu[n-2][j][k];
		newu[n-1][j][k]=newu[n-2][j][k];
			}
	}
	for(i=1;i<n-1;i++){
		for(j=1;j<n-1;j++){
					for(k=1;k<n-1;k++){
						newu[i][j][k]=oldu[i][j][k] + dt * (a * a *((oldu[i+1][j][k]-2*oldu[i][j][k]+oldu[i-1][j][k])/dx/dx 
												   + (oldu[i][j+1][k]-2*oldu[i][j][k]+oldu[i][j-1][k])/dy/dy)
												   + (oldu[i][j][k+1]-2*oldu[i][j][k]+oldu[i][j][k-1])/dz/dz)+ f[i][j]);
					}
		}
	}

	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			for(j=0;j<n;j++){
				oldu[i][j]=newu[i][j];
			}
		}
	}
	cout<<m<<endl;
	ofstream fout;	
}
ofstream fout_txt("file.txt");
for(i=0;i<n;i++){
	for(j=0;j<n;j++){
		fout_txt<<newu[i][j][5]<<'\t';
	}
	fout_txt<<endl;
}
return 1;
}
