#include<stdio.h>
#include<math.h>
#define ITERATION 100
struct
{
	float feature1;
	float feature2;
	float feature3;
	float feature4;
}dataset[1000];

struct
{
	int row_number;
	float feature1;
	float feature2;
	float feature3;
	float feature4;
	int centroid_number;
}centroid_assigned[1000];

struct
{
	float feature1;
	float feature2;
	float feature3;
	float feature4;	
}centroid[10];

struct
{
	float feature1;
	float feature2;
	float feature3;
	float feature4;	
}new_centroid[10];

struct
{
	int cluster_number;
	float distance;
}distance_from_each_row[1000];

int main()
{
	int i,j,p,n,m;
	printf("ENTER THE NUMBER OF ROWS THE DATASET HAS:\n");
	scanf("%d",&n);
	if (n<3)
	{
		printf("THE DATASET IS TOO  SHORT FOR  K-MEANS CLUSTERING\n");
		exit(1);
	}
	for (i=0;i<n;i++)
	{
		printf("ENTER FEATURE 1 FOR %dTH ROW:\n",i+1);
		scanf("%f",&dataset[i].feature1);
		printf("ENTER FEATURE 2 FOR %dTH ROW:\n",i+1);
		scanf("%f",&dataset[i].feature2);
		printf("ENTER FEATURE 3 FOR %dTH ROW:\n",i+1);
		scanf("%f",&dataset[i].feature3);
		printf("ENTER FEATURE 4 FOR %dTH ROW:\n",i+1);
		scanf("%f",&dataset[i].feature4);
	}
	for (i=0;i<n;i++)
	{
		printf("%.2f\t%.2f\t%.2f\t%.2f\n",dataset[i].feature1,dataset[i].feature2,dataset[i].feature3,dataset[i].feature4);
	}
	int clusters=3;
	int index_centroid[10];
	printf("CHOOSE %d NOS. FROM 0 TO %d FOR INDEXES OF ROWS TO BE CHOSEN AS INITIAL CENTROIDS FROM YOUR DATASET.NOS. SHOULD NOT BE SAME.\n",clusters,n-1);
	
	for (i=0;i<clusters;i++)
	{
		printf("CHOOSE INDEX FOR CENTROID %d:\n",i+1);
		scanf("%d",&index_centroid[i]);
	}
	
	for(i=1;i<clusters;i++)
	{
		for (j=0;j<i;j++)
		{
			if (index_centroid[i]==index_centroid[j])
			{
				printf("CENTROIDS CAN NOT BE SAME");
				exit(1);
			}
		}
	}
	int index[10];
	for (i=0;i<clusters;i++)
	{
		centroid[i].feature1=dataset[index_centroid[i]].feature1;
		centroid[i].feature2=dataset[index_centroid[i]].feature2;
		centroid[i].feature3=dataset[index_centroid[i]].feature3;
		centroid[i].feature4=dataset[index_centroid[i]].feature4;
		index[i]=i;
	}
	for (i=0;i<clusters;i++)
	{
		printf("CENTROID %d:\n",i+1);
		printf("%.2f\t%.2f\t%.2f\t%.2f\n",centroid[i].feature1,centroid[i].feature2,centroid[i].feature3,centroid[i].feature4);
	}
	float distance_f1[10];
	float distance_f2[10];
	float distance_f3[10];
	float distance_f4[10];
	float distance_c[10];
	for(m=0;m<ITERATION;m++)
	{
		printf("\n\n ITERATION %d:\n\n",m+1);
		for (i=0;i<n;i++)
		{
			p=0;
			while(p<clusters)
			{
				if (m==0)
				{
					distance_f1[p]=(pow((centroid[p].feature1-dataset[i].feature1),2));
					distance_f2[p]=(pow((centroid[p].feature2-dataset[i].feature2),2));
					distance_f3[p]=(pow((centroid[p].feature3-dataset[i].feature3),2));
					distance_f4[p]=(pow((centroid[p].feature4-dataset[i].feature4),2));
					distance_c[p]=sqrt(distance_f1[p]+distance_f2[p]+distance_f3[p]+distance_f4[p]);
				}
				else
				{
					distance_f1[p]=(pow((new_centroid[p].feature1-dataset[i].feature1),2));
					distance_f2[p]=(pow((new_centroid[p].feature2-dataset[i].feature2),2));
					distance_f3[p]=(pow((new_centroid[p].feature3-dataset[i].feature3),2));
					distance_f4[p]=(pow((new_centroid[p].feature4-dataset[i].feature4),2));
					distance_c[p]=sqrt(distance_f1[p]+distance_f2[p]+distance_f3[p]+distance_f4[p]);
				}
				p=p+1;
			}
			for(j=0;j<clusters;j++)
			{
				distance_from_each_row[j].cluster_number=j+1;
				distance_from_each_row[j].distance=distance_c[j];
			}
			float min;
			int centroid_no;
			centroid_assigned[i].row_number=i+1;
			min=distance_from_each_row[0].distance;
			centroid_no=1;
			for(j=1;j<clusters;j++)
			{
				if(distance_from_each_row[j].distance<min)
				{
					min=distance_from_each_row[j].distance;
					centroid_no=j+1;
				}
					
				centroid_assigned[i].feature1=dataset[i].feature1;
				centroid_assigned[i].feature2=dataset[i].feature2;
				centroid_assigned[i].feature3=dataset[i].feature3;
				centroid_assigned[i].feature4=dataset[i].feature4;
				centroid_assigned[i].centroid_number=centroid_no;
			}
		}
			
		printf("ROW NUMBER\tFEATURE1\tFEATURE2\tFEATURE3\tFEATURE4\tCENTROID NUMBER\n");
		for(i=0;i<n;i++)
		{
			printf("%d\t\t%.2f\t\t%.2f\t\t%.2f\t\t%.2f\t\t%d\n",centroid_assigned[i].row_number,centroid_assigned[i].feature1,centroid_assigned[i].feature2,centroid_assigned[i].feature3,centroid_assigned[i].feature4,centroid_assigned[i].centroid_number);
		}
		int centroid_rows[1000];
		float f1_avg[10];
		float f2_avg[10];
		float f3_avg[10];
		float f4_avg[10];
		for(i=0;i<clusters;i++)
		{
			for(j=0;j<n;j++)
			{
				centroid_rows[j]=-1;
				if (centroid_assigned[j].centroid_number==i+1)
				{
					centroid_rows[j]=j;
				}
				else
				{
					continue;
				}
			}
			printf("\nCENTROID %d HAS ROWS:\n",i+1);
			for(j=0;j<n;j++)
			{
				if(centroid_rows[j]!=-1)
					printf("%d\t",centroid_rows[j]+1);
				else
					continue;
			}
			f1_avg[i]=0;
			f2_avg[i]=0;
			f3_avg[i]=0;
			f4_avg[i]=0;
			int count_rows=0;
			for(j=0;j<n;j++)
			{
				
				if(centroid_rows[j]!=-1)
				{
					f1_avg[i]+=dataset[centroid_rows[j]].feature1;
					f2_avg[i]+=dataset[centroid_rows[j]].feature2;
					f3_avg[i]+=dataset[centroid_rows[j]].feature3;
					f4_avg[i]+=dataset[centroid_rows[j]].feature4;
					count_rows++;
				}
				else
				{
					continue;
				}
			}
			f1_avg[i]=f1_avg[i]/count_rows;
			f2_avg[i]=f2_avg[i]/count_rows;
			f3_avg[i]=f3_avg[i]/count_rows;
			f4_avg[i]=f4_avg[i]/count_rows;
			new_centroid[i].feature1=f1_avg[i];
			new_centroid[i].feature2=f2_avg[i];
			new_centroid[i].feature3=f3_avg[i];
			new_centroid[i].feature4=f4_avg[i];
			
			printf("\nNEW CENTROID %d:\n",index[i]+1);
			printf("FEATURE1\tFEATURE2\tFEATURE3\tFEATURE4\n");
			printf("%.2f\t\t%.2f\t\t%.2f\t\t%.2f\n",new_centroid[i].feature1,new_centroid[i].feature2,new_centroid[i].feature3,new_centroid[i].feature4);
		}
	}
}
