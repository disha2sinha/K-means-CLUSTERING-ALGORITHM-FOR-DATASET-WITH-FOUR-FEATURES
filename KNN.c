#include<stdio.h>
#include<stdlib.h>
#include<math.h>
struct
{
	float feature1;
	float feature2;
	float feature3;
	float feature4;
	int knn_prediction;
	int actual_output;
}results[250];
struct testcase
{
	float feature1;
	float feature2;
	float feature3;
	float feature4;
	int output;
	float distance;
}each_testcase[750];
struct
{
	float feature1;
	float feature2;
	float feature3;
	float feature4;
	int output;
}dataset[1000];
struct
{
	float feature1;
	float feature2;
	float feature3;
	float feature4;	
}testing[250];
struct
{
	float feature1;
	float feature2;
	float feature3;
	float feature4;
	int output;
}training[750];


int main()
{
	int i,j,m,p,n,K,q,x;
	printf("ENTER THE NUMBER OF ROWS THE DATASET HAS:\n");
	scanf("%d",&n);
	if (n<3)
	{
		printf("THE DATASET IS TOO  SHORT FOR  KNN PREDICTION\n");
		exit(0);
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
		printf("ENTER OUTPUT FOR %dTH ROW:\n",i+1);
		scanf("%d",&dataset[i].output);
	}
	for (i=0;i<n;i++)
	{
		printf("%.2f\t%.2f\t%.2f\t%.2f\t%d\n",dataset[i].feature1,dataset[i].feature2,dataset[i].feature3,dataset[i].feature4,dataset[i].output);
	}
	int split=0.75*n;
	int rem=n-split;
	int actual_results[250];
	
	//splitting dataset into training and testing datasets
	
	printf("YOUR TRAINING DATASET:\n");
	for(i=0;i<split;i++)
	{
		training[i].feature1=dataset[i].feature1;
		training[i].feature2=dataset[i].feature2;
		training[i].feature3=dataset[i].feature3;
		training[i].feature4=dataset[i].feature4;
		training[i].output=dataset[i].output;
	}
	for(i=0;i<split;i++)
	{
		printf("%.2f\t%.2f\t%.2f\t%.2f\t%d\n",training[i].feature1,training[i].feature2,training[i].feature3,training[i].feature4,training[i].output);	
	}
	j=0;
	for(i=split;i<n;i++)
	{
		testing[j].feature1=dataset[i].feature1;
		testing[j].feature2=dataset[i].feature2;
		testing[j].feature3=dataset[i].feature3;
		testing[j].feature4=dataset[i].feature4;
		j=j+1;
	}
	printf("YOUR TESTING DATASET:\n");
	for(i=0;i<rem;i++)
	{
		printf("%.2f\t%.2f\t%.2f\t%.2f\n",testing[i].feature1,testing[i].feature2,testing[i].feature3,testing[i].feature4);	
	}
	j=split;
	for (i=0;i<rem;i++)
	{
		actual_results[i]=dataset[j].output;
		j=j+1;
	}
	
	printf("CHOOSE AN OPTIMUM VALUE FOR K_NEIGHBORS(K_NEIGHBORS>=2):\n");
	scanf("%d",&K);
	if(K>=split)
	{
		printf("NO. OF NEAREST NEIGHBOURS CAN NOT BE GREATER THAN THE SIZE OF THE TRAINING DATASET...CHOOSE A REASONABLE VALUE NEXT TIME");
		exit(0);
	}
	
	//finding out distance of each testpoints from the training points and finding out the most occuring category among K nearest neighvours
	
	float distance_f1[750];
	float distance_f2[750];
	float distance_f3[750];
	float distance_f4[750];
	float distance_f[750];
	for (i=0;i<rem;i++)
	{
		p=0;
		while(p<split)
		{
			distance_f1[p]=(pow((testing[i].feature1-training[p].feature1),2));
			distance_f2[p]=(pow((testing[i].feature2-training[p].feature2),2));
			distance_f3[p]=(pow((testing[i].feature3-training[p].feature3),2));
			distance_f4[p]=(pow((testing[i].feature4-training[p].feature4),2));
			distance_f[p]=sqrt(distance_f1[p]+distance_f2[p]+distance_f3[p]+distance_f4[p]);
			p=p+1;
		}
		for (j=0;j<split;j++)
		{
			each_testcase[j].feature1=training[j].feature1;
			each_testcase[j].feature2=training[j].feature2;
			each_testcase[j].feature3=training[j].feature3;
			each_testcase[j].feature4=training[j].feature4;
			each_testcase[j].output=training[j].output;
			each_testcase[j].distance=distance_f[j];
		}
		for (j=0;j<split-1;j++)
		{
			for (m=j+1;m<split;m++)	
			{
				if(each_testcase[m].distance<each_testcase[j].distance)
				{
					struct testcase temp=each_testcase[j];
					each_testcase[j]=each_testcase[m];
					each_testcase[m]=temp;
				}
			}
		}
				
		results[i].feature1=testing[i].feature1;
		results[i].feature2=testing[i].feature2;
		results[i].feature3=testing[i].feature3;
		results[i].feature4=testing[i].feature4;
		int max_votes=0,result=each_testcase[0].output;
		for(j=0;j<K;j++)
		{
			int votes=1;
			for(m=j+1;m<K;m++)
			{
				if (each_testcase[j].output==each_testcase[m].output)
				{
					votes++;
					if (votes>max_votes)
					{
						max_votes=votes;
						result=each_testcase[m].output;
					}
				}
			}
		}
		results[i].knn_prediction=result;
		results[i].actual_output=actual_results[i];
	}
	printf("FEATURE1\tFEATURE2\tFEATURE3\tFEATURE4\tKNN_PREDICTION\tACTUAL_OUTPUT\n");
	for (j=0;j<rem;j++)
	{
		printf("%.2f\t\t%.2f\t\t%.2f\t\t%.2f\t\t%d\t\t%d\n",results[j].feature1,results[j].feature2,results[j].feature3,results[j].feature4,results[j].knn_prediction,results[j].actual_output);	
	}
	return 0;
}
