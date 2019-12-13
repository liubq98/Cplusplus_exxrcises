#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int main()
{
 int num[4];
 int number,flag=0;
 int i,j;
 void paixu(int *num);
 int maxium(int *num);
 int minium(int *num);
 while(flag==0)
 {
  printf("请输入数字：");
  scanf("%d",&number);
  fflush(stdin);//清空输入缓存
  for(i=0;i<4;i++)
   num[i]=(int)(number/pow(10.0,(double)i))%10;//将四位数每一个分别取出
  for(i=0,flag=1;i<3;i++)//判定是否有重复的数字
  {
   for(j=i+1;j<4;j++)
    if(num[i]==num[j])
    { 
     flag=0;
     break;
    }
   if(flag==0)
    break;
  }
 }
 paixu(num);
 number=maxium(num)-minium(num);//求出最大数减去最小数所得的数
 printf("%d-%d=%d\n",maxium(num),minium(num),number);//输出每次运算步骤
 while(number!=6174)
 {
  for(i=0;i<4;i++)
   num[i]=(int)(number/pow(10.0,(double)i))%10;
  paixu(num);
  number=maxium(num)-minium(num);
  printf("%d-%d=%d\n",maxium(num),minium(num),number);//输出每次运算步骤
 }
}
void paixu(int *num)//将四个数从大到小排序
{
 int i,j,temp;
 for(i=0;i<4;i++)
  for(j=0;j<3-i;j++)
   if(num[j]<num[j+1])//冒泡排序
   {
    temp=num[j];
    num[j]=num[j+1];
    num[j+1]=temp;
   }
}
int maxium(int *num)//求出四个数组成的最大数
{
 int max=0,i;
 for(i=0;i<4;i++)
  max=max+(int)(num[i]*pow(10.0,3-i));
 return max;
}
int minium(int *num)//求出四个数组成的最小数
{
 int min=0,i;
 for(i=0;i<4;i++)
  min=min+(int)(num[i]*pow(10.0,i));
 return min;
}
