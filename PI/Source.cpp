//#include <stdio.h>

//#include <windows.h>
//#include <iostream>
//#include <time.h> 
//#include <ppl.h>
//#include <iomanip>
//
//using namespace std;
//
//int monte_carlo_count_pi(int n)
//{
//	int c = 0;
//	for (int i = 0; i < n; i++)
//	{
//		double x = (double)rand() / (RAND_MAX);
//		double y = (double)rand() / (RAND_MAX);
//		if (x * x + y * y <= 1.0)
//		{
//			c++;
//		}
//	}
//	return c;
//}
//void gotoxy(int x, int y)
//{
//	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
//	COORD c = { x, y };
//	SetConsoleCursorPosition(hOut, c);
//}
//int main()
//{
//	//pi = 2 + 1 / 3 * (2 + 2 / 5 * (2 + 3 / 7 * (2 + ... (2 + k / 2k + 1 * (2 + ...))...)))
//	//long   a = 10000, b = 0, c = 3500, d = 0, e = 0, f = 0, g[3501];
//	//for (; b - c;)	g[b++] = a / 5;
//	//for (; d = 0, f = c * 2; c -= 14, printf("%.4d ", e + d / a), e = d % a)
//	//	for (b = c; d += g[b] * a, g[b] = d % --f, d /= f--, --b; d *= b);
//	//return 0;
//
//	//pi = 2 + 1 / 3 * (2 + 2 / 5 * (2 + 3 / 7 * (2 + ... (2 + k / 2k + 1 * (2 + ...))...)))
//	long   a = 10000, b = 0, c = 5000, d = 0, e = 0, f = 0, g[5001];
//	for (; b - c;)	g[b++] = a / 5;	//制作一个数组全部放2000
//
//	for (; f = c * 2; c -= 14) 
//	{
//		d = 0;
//
//		for (b = c; --b; ) 
//		{
//			
//			d += g[b] * a;
//			g[b] = d % --f;
//			d /= f--;
//			d *= b;
//
//		}
//		printf("%.4d ", e + d / a);
//		e = d % a;
//
//	}
//	
//	return 0;
//}


//#include "pch.h"
#include <amp.h>
#include <iostream>
#include <vector>
using namespace Concurrency;
constexpr auto PI = 3.14159265358979323846;
const int size = 999999999;//循环次数

//GPU计算
void GPUCompute(std::vector<double> vec)
{
	DWORD t1, t2;
	t1 = GetTickCount();
	std::vector<double> resultVec;
	resultVec.resize(size);

	array_view<const double, 1> array1(size, vec);
	array_view<const double, 1> array2(size, vec);
	array_view<double, 1> result(size, resultVec);
	//GPU计算部分
	parallel_for_each(result.extent, [=](index<1> idx) restrict(amp)
		{
			result[idx] = array1[idx] * array1[idx] * array2[idx] / array2[idx];
		});
	t2 = GetTickCount();
	std::cout << "GPU Use Time:" << (t2 - t1) * 1.0 / 1000 << "\n";
}

//CPU计算
void CPUCompute(std::vector<double> vec)
{
	DWORD t1, t2;
	t1 = GetTickCount();
	std::vector<double> result;
	result.resize(size);

	for (size_t i = 0; i < size; i++)
	{
		result[i] = vec[i] * vec[i] * vec[i] / vec[i];
	}
	t2 = GetTickCount();
	std::cout << "CPU Use Time:" << (t2 - t1) * 1.0 / 1000 << "\n";
}

int main()
{
	std::vector<double> nums;
	for (size_t i = 0; i < size; i++)
	{
		nums.push_back(PI);
	}
	GPUCompute(nums);
	CPUCompute(nums);

	system("PAUSE ");
}


//int main2()
//{
//	srand(time(NULL));
//	const int N1 = 100000;
//	const int N2 = 100000;
//	int n = 0;
//	int c = 0;
//	int i = 9000;
//	Concurrency::critical_section cs;
//	// it is better that N1 >> N2 for better performance
//
//	i = 0;
//	Concurrency::parallel_for(0, N1, [&](int i)
//		{
//			int t = monte_carlo_count_pi(N2);
//			cs.lock(); // race condition
//			n += N2;   // total sampling points
//			c += t;    // points fall in the circle
//			cs.unlock();
//			i++;
//			//if (i % 1000 == 9) {
//			//	i = 0;
//			//	gotoxy(0, 0);
//			//	cout << "pi ~= " << setprecision(900) << (double)c / n * 4.0 << endl;
//			//	//printf("%lf", (double)c / n * 4.0);
//			//}
//		});
//	cout << "pi ~= " << setprecision(900) << (double)c / n * 4.0 << endl;
//	return 0;
//}


