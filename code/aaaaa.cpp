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
  printf("���������֣�");
  scanf("%d",&number);
  fflush(stdin);//������뻺��
  for(i=0;i<4;i++)
   num[i]=(int)(number/pow(10.0,(double)i))%10;//����λ��ÿһ���ֱ�ȡ��
  for(i=0,flag=1;i<3;i++)//�ж��Ƿ����ظ�������
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
 number=maxium(num)-minium(num);//����������ȥ��С�����õ���
 printf("%d-%d=%d\n",maxium(num),minium(num),number);//���ÿ�����㲽��
 while(number!=6174)
 {
  for(i=0;i<4;i++)
   num[i]=(int)(number/pow(10.0,(double)i))%10;
  paixu(num);
  number=maxium(num)-minium(num);
  printf("%d-%d=%d\n",maxium(num),minium(num),number);//���ÿ�����㲽��
 }
}
void paixu(int *num)//���ĸ����Ӵ�С����
{
 int i,j,temp;
 for(i=0;i<4;i++)
  for(j=0;j<3-i;j++)
   if(num[j]<num[j+1])//ð������
   {
    temp=num[j];
    num[j]=num[j+1];
    num[j+1]=temp;
   }
}
int maxium(int *num)//����ĸ�����ɵ������
{
 int max=0,i;
 for(i=0;i<4;i++)
  max=max+(int)(num[i]*pow(10.0,3-i));
 return max;
}
int minium(int *num)//����ĸ�����ɵ���С��
{
 int min=0,i;
 for(i=0;i<4;i++)
  min=min+(int)(num[i]*pow(10.0,i));
 return min;
}
