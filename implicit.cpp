#include<iostream>
#include<fstream>
#include<math.h>
#define x 11
#define y 11
#define z 11
using namespace std;
int main()
{
	int i,j,k;
	double dx=1.0/(x-1),dy=1.0/(y-1),dz=1.0/(z-1),dt=0.001,mist=0.0,eps=0.001;
	double a[x][y][z],b[x][y][z],c[x][y][z],d[x][y][z],alpha[x],betta[x],next[x][y][z],prev[x][y][z];
	//nachalnoe uslovie
	for(i=0;i<x;i++){
		for(j=0;j<y;j++){
			for(k=0;k<z;k++){
				prev[i][j][k]=20.0;
				next[i][j][k]=20.0;
				if (i==5 && j==5 && k==5) {
					prev[i][j][k]=500.0;
					next[i][j][k]=500.0;
				}
			}
		}
	}

	for (int temp=0;temp<500;temp++){
/*==================================== 1st step by X ====================================*/
		for(i=0;i<x;i++){
			for(j=0;j<y;j++){
				for(k=0;k<z;k++){
					a[i][j][k]=-1.0/(2.0*dx*dx);
					b[i][j][k]=1.0/dt+1.0/(dx*dx);
					c[i][j][k]=-1.0/(2.0*dx*dx);
					d[i][j][k]=prev[i][j][k]/dt+(prev[i+1][j][k]-2.0*prev[i][j][k]+prev[i-1][j][k])/(2.0*dx*dx)+(prev[i][j+1][k]-2.0*prev[i][j][k]+prev[i][j-1][k])/(dy*dy)+(prev[i][j][k+1]-2.0*prev[i][j][k]+prev[i][j][k-1])/(dz*dz);
				}
			}
		}
		for(k=1;k<z-1;k++){
			for(j=1;j<y-1;j++){
				//U(0,y,z)=1
				alpha[1]=1.0;
				betta[1]=0.0;
				for(i=1;i<x-1;i++)
				{
					alpha[i+1]=-a[i][j][k]/(b[i][j][k]+c[i][j][k]*alpha[i]);
					betta[i+1]=(d[i][j][k]-c[i][j][k]*betta[i])/(b[i][j][k]+c[i][j][k]*alpha[i]);
				}

				//U(1,y,z)=1
				next[x-1][j][k]=next[x-2][j][k];
				for(i=x-2;i>=0;i--)
				next[i][j][k]=alpha[i+1]*next[i+1][j][k]+betta[i+1];
			}
		}
/*==================================== 2nd step by Y ====================================*/
		for(i=0;i<x;i++){		
			for(j=0;j<y;j++){
				for(k=0;k<z;k++){		
					a[i][j][k]=-1.0/(2.0*dy*dy);
					b[i][j][k]=1.0/dt+1.0/(dy*dy);
					c[i][j][k]=-1.0/(2.0*dy*dy);
					d[i][j][k]=next[i][j][k]/dt-(prev[i][j+1][k]-2.0*prev[i][j][k]+prev[i][j-1][k])/(2.0*dy*dy);
				}
			}
		}
		for(i=1;i<x-1;i++){
			for(k=1;k<z-1;k++){
				//U(x,0,z)=0
				alpha[1]=1.0;
				betta[1]=0.0;
				for(j=1;j<y-1;j++)
				{
					alpha[j+1]=-a[i][j][k]/(b[i][j][k]+c[i][j][k]*alpha[j]);
					betta[j+1]=(d[i][j][k]-c[i][j][k]*betta[j])/(b[i][j][k]+c[i][j][k]*alpha[j]);
				}
				//U(x,1,z)=0
				next[i][y-1][k]=next[i][y-2][k];
				for(j=y-2;j>=0;j--)
				next[i][j][k]=alpha[j+1]*next[i][j+1][k]+betta[j+1];
			}
		}
/*==================================== 3rd step by Z ====================================*/
		for(i=0;i<x;i++){		
			for(j=0;j<y;j++){
				for(k=0;k<z;k++){		
					a[i][j][k]=-1.0/(2.0*dz*dz);
					b[i][j][k]=1.0/dt+1.0/(dz*dz);
					c[i][j][k]=-1.0/(2.0*dz*dz);
					d[i][j][k]=next[i][j][k]/dt-(prev[i][j][k+1]-2.0*prev[i][j][k]+prev[i][j][k-1])/(2.0*dz*dz);
				}
			}
		}
			for(i=1;i<x-1;i++){
				for(j=1;j<y-1;j++){
					//U(x,y,0)=0
					alpha[1]=1.0;
					betta[1]=0.0;

					for(k=1;k<z-1;k++)
					{
						alpha[k+1]=-a[i][j][k]/(b[i][j][k]+c[i][j][k]*alpha[k]);
						betta[k+1]=(d[i][j][k]-c[i][j][k]*betta[k])/(b[i][j][k]+c[i][j][k]*alpha[k]);
					}

					//U(x,y,1)=0
					next[i][j][z-1]=next[i][j][z-2];

					for(k=z-2;k>=0;k--)
						next[i][j][k]=alpha[k+1]*next[i][j][k+1]+betta[k+1];
				}
			}

			mist=0.0;

			for(i=0;i<x;i++)
				for(j=0;j<y;j++)
					for(k=0;k<z;k++)
						if(mist<fabs(next[i][j][k]-prev[i][j][k]))
							mist=fabs(next[i][j][k]-prev[i][j][j]);

			for(i=0;i<x;i++)
				for(j=0;j<y;j++)
					for(k=0;k<z;k++)
						prev[i][j][k]=next[i][j][k];
	}
	ofstream fout("file.txt");
	for(i=0;i<x;i++){
		for(j=0;j<y;j++){
				fout<<next[i][j][5]<<'\t';
		}
		fout<<endl;
	}
system("pause");
return 0;
}
