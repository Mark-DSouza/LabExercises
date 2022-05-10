// 4. Chinese remainder method
#include<stdio.h>

int multiplicativeInverse(int a, int m)
{
	int curr = m;
	int first = 0, second = 1;
	if (m == 1)
		return 0;

	while (a > 1)
	{
		int quotient = a / m;
		int temp = m;
		m = a % m, a = temp;
		temp = first;
		first = second - quotient * first;
		second = temp;
	}
	if (second < 0)
		second += curr;

	return second;
}

int chineseRemainderTheorem(int a[], int b[],int size)
{
	int prod = 1;
	for (int i = 0; i < size; i++)
	{
		prod *= a[i];
	}

	int result = 0;
	for (int i = 0; i < size; i++)
	{
		result += b[i] * multiplicativeInverse((prod / a[i]), a[i]) * (prod / a[i]);
	}

	return result % prod;
}

int main()
{
	int size;
	printf("\nEnter the size: ");
	scanf("%d",&size);


  int *a = new int[size];
  int *b = new int[size];

	printf("\nEnter the elements for number array: ");
	for(int i=0; i<size; i++)
	{
		scanf("%d", &a[i]);
	}
	printf("\nEnter the Remainder: ");
	for(int i=0; i<size; i++)
	{
		scanf("%d", &b[i]);
	}

	printf("minimum Values x = %d ", chineseRemainderTheorem(a,b,size));
  delete[] a;
  delete[] b;
	return 0;
}
