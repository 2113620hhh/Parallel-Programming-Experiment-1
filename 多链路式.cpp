#include <windows.h>
#include <bits/stdc++.h>
using namespace std;

class TimerCounter {
	public:
		TimerCounter(void);//构造函数
		~TimerCounter(void);//析构函数
	private:
		LARGE_INTEGER startCount;//记录开始时间

		LARGE_INTEGER endCount;//记录结束时间

		LARGE_INTEGER freq;//本机CPU时钟频率
	public:
		double dbTime;//程序运行的时间保存在这里

	public:
		void Start();//被测程序开始点处开始计时
		void Stop();//被测程序结束点处结束计时
};

TimerCounter::TimerCounter(void) {
	QueryPerformanceFrequency(&freq);//获取主机CPU时钟频率
}

TimerCounter::~TimerCounter(void) {
}

void TimerCounter::Start() {
	QueryPerformanceCounter(&startCount);//开始计时
}

void TimerCounter::Stop() {
	QueryPerformanceCounter(&endCount);//停止计时

	dbTime = ((double)endCount.QuadPart - (double)startCount.QuadPart) / (double)freq.QuadPart; //获取时间差

}

double run(int *arr, int n) {

	TimerCounter tc;

	int sum1 = 0, sum2 = 0, sum = 0;

	tc.Start();

	for (int i = 0; i < n; i += 2) {
		sum1 += arr[i];
		sum2 += arr[i + 1];
	}
	sum = sum1 + sum2;

	tc.Stop();

	cout << sum << " ";

	cout << "The run time is:" << tc.dbTime * 1000 << "ms" << endl;

	return tc.dbTime * 1000;

}

int num(int n) {

	if (n == 0) {

		return 1;

	} else {

		return 2 * num(n - 1);

	}

}

int main() {
	double sum = 0;
	int n = 50000;
	int *arr = new int [n];
	for (int i = 0; i < n; i++) {

		arr[i] = num(i);

	}
	for (int i = 0; i < 10; i++) {

		sum += run(arr, n);

	}

	cout << sum / 10 << "s" << endl;

}