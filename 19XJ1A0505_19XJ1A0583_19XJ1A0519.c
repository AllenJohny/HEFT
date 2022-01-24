#include<stdio.h>


void rankloop(int index, int transpose[][20], float avg_exe[], float rank[], int N, int n)       //index is the current task number
{ float maxim,temp;
   
  for(int i=0;i<N;i++)
  { if(transpose[i][index]>0)
    { temp = transpose[i][index] + rank[i];
      if(temp>maxim)
      {
        maxim = temp;
      }
    }
  }
  rank[index] = avg_exe[index] + maxim ;
   
  index--;
  if(index>=0)
  {
  rankloop(index,transpose,avg_exe,rank,N,n);
  }

}

void sort(float sort_rank[][10],int N)           //function to sort the rank array in descending order
{
  for (int j = 0; j < N; ++j)
   { for (int k =(j + 1); k < N; ++k)
     {	int a=0,b=0;
       if (sort_rank[1][j] < sort_rank[1][k])
        {
         a = sort_rank[1][j];
         sort_rank[1][j] =sort_rank[1][k];
         sort_rank[1][k] = a;
         b = sort_rank[0][j];
         sort_rank[0][j] =sort_rank[0][k];
         sort_rank[0][k] = b;
        }
     }
   }
}


int prede(int i,int m,int temp_index,int maxterm,int aft[],int tree[][10],int pred[],int pred_proc[])
{
  int maxterm1[3];

  for(int j=0;j<m;j++)
  {
    if(pred_proc[j]==i+1)
    {
      maxterm1[j]=aft[pred[j]];
    }
    else
    {
      maxterm1[j]=aft[pred[j]]+tree[pred[j]][temp_index];
    }
  }

  maxterm = maxterm1[0];
 
  for (int a = 1; a < m; a++)
  { 
    if (maxterm1[a] > maxterm)
    {  
      maxterm = maxterm1[a];
    }
  }
  return maxterm;
}


void calc(int proctime[],int proc_id[],int est[][10],int eft[][10],float sort_rank[][10],int tree[][10],int exe[][10],int n,int N,int num,int aft[])
{ int temp_index;
  temp_index=sort_rank[0][num];
  temp_index=temp_index-1;
  
  int pred[3],pred_proc[3],maxterm,k=0,m=0;
  for(int i=0;i<N;i++)
  {
    if(tree[i][temp_index]>0)
    {
      pred[m]=i;        
      pred_proc[m] = proc_id[i];
      m++;
    }
  }
    

  for(int i=0;i<n;i++)
  {
    int avail;
    avail=proctime[i];

    maxterm = prede(i,m,temp_index,maxterm,aft,tree,pred,pred_proc);

    if(avail>maxterm)
    {
      est[i][temp_index]=avail;
    }
    else
    {
      est[i][temp_index]=maxterm;
    }
    eft[i][temp_index]=est[i][temp_index]+exe[i][temp_index]; 
  }

  int proc=0;
  for(int i=1;i<n;i++)
  {
   if(eft[i][temp_index]<eft[proc][temp_index])
   {
     proc=i;
     aft[temp_index]=eft[i][temp_index];
   }
   else if(eft[proc][temp_index]<eft[i][temp_index])
   {
      aft[temp_index]=eft[proc][temp_index];
   }
  }
 
  proc_id[temp_index]=proc+1;//the processor that will run is selected
  proctime[proc]=eft[proc][temp_index];//updated its time

  num++;
  if(num<=N-1)
  {
  calc(proctime,proc_id,est,eft,sort_rank,tree,exe,n,N,num,aft);
  }


}



int main()
{
  int i,j,N,n;

  FILE *input;
  input= fopen("input.txt","r");

  // number of tasks
  fscanf(input,"%d",&N);

  // number of processors
  fscanf(input,"%d",&n);

  int exe[n][N];        //executing on processor
  float avg_exe[N];     //avg of all processors fr a task
  int tree[20][N];      //edge tree
  int transpose[N][20]; //transpose tree for edge tree
  float sort_rank[2][N];// storing the sorted rank array

  for(i=0;i<n;i++)
   { for(j=0;j<N;j++)
      {
        fscanf(input,"%d",&exe[i][j]);
      }
   }

  for(i=0;i<N;i++)
  { for(j=0;j<N;j++)
      {
        fscanf(input,"%d",&tree[i][j]);
      }
  }
 

  for(i=0;i<N;i++)
  {
    avg_exe[i]=0;
  }



  for(j=0;j<N;j++)      //for getting the average cost fr each task
  {
    for(i=0;i<n;i++)
    {
    avg_exe[j]=avg_exe[j]+exe[i][j];
    }

    avg_exe[j]=avg_exe[j]/n;
  }
   
   float rank[N];

  //exit rank
   rank[N-1]=avg_exe[N-1];
 

    // computing the transpose
  for (int i = 0; i < 20; ++i)
  {
    for (int j = 0; j < N; ++j)
    {
        transpose[j][i]=tree[i][j];
    }
  }

  printf("No. of tasks:%d\n",N);
  printf("No. of processors:%d",n);
  printf("\n\n");
  printf("The upward rank values:\n");
  
  rankloop(N-2,transpose,avg_exe,rank,N,n);

  for(int i=1;i<=N;i++)
  {
   printf("Task %d:  %f\n",i,rank[i-1]);
  }


  // we next sort the array


    for (int j = 0; j < N; ++j)
    {
        sort_rank[0][j]=j+1;
        sort_rank[1][j]=rank[j];
        
    }

  sort(sort_rank,N);
  // sorting done

  printf("\n\n\n");


  int proctime[n];  //avail time of each processor
  int est[n][N];    //est storing for all processors
  int eft[n][N];    //eft storing for all processors
  int temp_index;   //what is the current task for which we need to calculate
  int proc_id[N];   //stores the processor used by each task
  int aft[N];       //stores the aft of each task

  temp_index=sort_rank[0][0];
  temp_index=temp_index-1;


  for(int i=0;i<n;i++)
  {
    proctime[i]=0;
    est[i][temp_index]=0;
  }

  for(int i=0;i<n;i++)
  {
    eft[i][temp_index]=exe[i][temp_index];
  } 

  proc_id[temp_index]=0;

  int proc=0;

  for(i=1;i<n;i++)
  {
    if(eft[i][temp_index]<eft[proc][temp_index])
    {
     proc=i;
     aft[temp_index]=eft[i][temp_index];
    }

  }

  proc_id[temp_index]=proc+1;//the processor that will run is selected
  proctime[proc]=proctime[proc]+eft[proc][temp_index];//updated its time
  
  int num=1;      //sort of an index fr the sorted rank array

  calc(proctime,proc_id,est,eft,sort_rank,tree,exe,n,N,num,aft);     //est and eft

  int schedule[N];
  printf("The order of tasks to be scheduled:\n");
  for(i=0;i<N;i++)
  { schedule[i]=sort_rank[0][i];
    printf("%d ",schedule[i]);
  }
  printf("\n\n");
  printf("EST and EFT on different processor\n");
  for(i=0;i<N;i++)
  {
   printf("Task: %d\n",i+1);
   for(j=0;j<n;j++)
   {
    printf("processor %d||est:%d eft:%d ||\n",j+1,est[j][i],eft[j][i]);
   }
   printf("\n");
}

printf("\nFinal Schedule:\n");

for(i=0;i<N;i++)
{
  printf("Task %d is executed on processor %d from time %d to %d\n",i+1,proc_id[i],est[proc_id[i]-1][i],aft[i]);
}

int maxaft=aft[0];
for(i=0;i<N;i++)
{
  if(aft[i]>maxaft)
  {
    maxaft=aft[i];
  }
}

printf("\n");
printf("Hence, the makespan length from the schedule: %d\n",maxaft);

return 0;


}