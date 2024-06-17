/*
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
using namespace std;

class ExceptionTest{
private:
	int prime[100]; //存前100个素数（质数）
public:
	//求分数，分子分母为a和b；分母为零异常
	double fraction(double a, double b) {
		if (b == 0) {
			cout << "分母不能为零！" << endl;
			exit(-1);
		}
		else
			return a / b;
	}
	//求底数为10的对数，真数为a；真数为负异常
	double logarithm(double a) {
		if (a < 0) {
			cout << "真数不能为负！" << endl;
			exit(-1);
		}
		else
			return log10(a);
	}
	//求算出前100个素数，放在prime中，并写入文件；文件打开失败异常
	void calPrime(const char* address) {
		ofstream out_file(address, ios::out);
		if (!out_file) {
			cout << "文件打开失败！" << endl;
			exit(-1);
		}
		else {
			int count = 0;
			for (int i = 2; ; i++) {
				bool is_prime = true;
				for (int j = 2; j * j <= i; j++) {
					if (i % j == 0) {
						is_prime = false;
						break;
					}
				}
				if (is_prime) {
					prime[count] = i;
					count += 1;
				}
				if (count == 100)
					break;
			}
			for (int k = 0; k < 100; k++) {
				out_file << prime[k] << ' ';
				if (k % 10 == 9)
					out_file << '\n';
			}
			out_file.close();
		}
	}
	//从prime中获取第i个素数；数组下标越界异常
	int getPrime(int i) {
		if (i > 100 || i < 1) {
			cout << "数组下标越界！" << endl;
			exit(-1);
		}
		else
			return prime[i - 1];
	}
};

int main() {
	ExceptionTest Exp;
	int a, b, c, d;
	cout << "请输入分子和分母：";
	cin >> a >> b;
	cout << "分数为：" << Exp.fraction(a, b) << endl;
	cout << "请输入真数：";
	cin >> c;
	cout << "底数为10的对数为：" << Exp.logarithm(c) << endl;
	//Exp.calPrime("prime.txt");
	cout << "请输入素数的序号：";
	cin >> d;
	cout << "第" << d << "个素数是" << Exp.getPrime(d) << endl;
	return 0;
}
*/

/*
#include <iostream>
#include <fstream>
using namespace std;
#pragma warning (disable:4996)

class Web {
	char temp_name[30];
	int temp_age;
	char temp_phone[20];
	char temp_file[40];
public:
	void inputName() {
		cin >> temp_name;
	}
	void inputAge() {
		int age;
		cin >> age;
		if (age > 18 || age < 11)
			throw age;
		temp_age = age;
	}
	void inputPhone() {
		char phone[20];
		cin >> phone;
		for (int i = 0; phone[i] != '\0'; i++) {
			if (!(phone[i] >= 48 && phone[i] <= 57) && phone[i] != '-')
				throw phone;
		}
		strcpy(temp_phone, phone);
	}
	void uploadFile() {
		char file_name[50];
		cin >> file_name;
		ifstream in_file(file_name, ios::in);
		if (!in_file)
			throw file_name;
		char temp[50];
		strcpy(temp, temp_name);
		strcat(temp, ".txt");
		strcpy(temp_file, temp);
		ofstream out_file(temp_file, ios::out);
		if (!out_file)
			throw temp_file;
		out_file << "姓名：" << temp_name << endl;
		out_file << "年龄：" << temp_age << endl;
		out_file << "电话：" << temp_phone << "\n" << endl;
		char buffer[101];
		while (!in_file.eof()) {
			in_file.getline(buffer, 99);
			out_file << buffer << endl;
		}
		in_file.close();
		out_file.close();
	}
	void enroll() {
		cout << "请输入姓名：";
		inputName();
		cout << "请输入年龄：";
		try { inputAge(); }
		catch (int age) {
			if (age < 11)
				cout << "需要年满11周岁方能报名！" << endl;
			else if (age > 18)
				cout << "超过18周岁不能报名！" << endl;
			exit(0);
		}
		cout << "请输入电话：";
		try { inputPhone(); }
		catch (char* phone) {
			while (1) {
				cout << "电话号码" << phone << "包含非法字符，请重新输入：";
				try { inputPhone(); }
				catch (char* phone) { continue; }
				break;
			}
		}
		cout << "请输入作文文件名：";
		try { uploadFile(); }
		catch (char* file) {
			if (strcmp(file, temp_file)) {
				while (1) {
					cout << "无法打开文件" << file << "，请重新输入文件名：";
					try { uploadFile(); }
					catch (char* file) { continue; }
					break;
				}
			}
			else {
				cout << "无法创建报名文件！" << endl;
				exit(-1);
			}
		}
	}
};

int main() {
	Web WEB;
	WEB.enroll();
	return 0;
}
*/

/*
#include <iostream>
using namespace std;

void* memcpy(void* dst, void* src, unsigned count) {
	if (dst == nullptr)
		throw 1;
	if (src == nullptr)
		throw 2;
	memmove(dst, src, count);
}

int main()
{
	char *a = nullptr;
	char *b = nullptr;
	char temp[] = "ERROR";
	try { memcpy(a, b, 6); }
	catch (int error) {
		if (error == 1) {
			a = new char[6];
			try { memcpy(a, b, 6); }
			catch (int error) {
				b = temp;
				memcpy(a, b, 6);
			}
		}
		else if (error == 2) {
			b = temp;
			memcpy(a, b, 6);
		}
	}
	cout << a << endl;
	char str[] = "memmove can be very useful......";
	memcpy(str + 20, str + 15, 11);
	puts(str);
	return 0;
}
*/

#include <iostream>
#include <list>
using namespace std;
int main()
{
	int m, n; //m用于存储要报的数，n用于存储小孩个数
	cout << "请输入小孩的个数和要报的数：";
	cin >> n >> m;
	while (n <= 0 || m <= 0) {
		cout << "小孩个数和要报的数必须为正数，请重新输入：";
		cin >> n >> m;
	}
	//构建圈子
	list<int> children; //children是用于存储小孩编号的容器
	for (int i = 0; i < n; i++) //循环创建容器元素
		children.push_back(i); //把i（小孩的编号）从容器
						//尾部放入容器
  //开始报数
	list<int>::iterator current; //current为指向容器元素的迭代器
	current = children.begin(); //current初始化成指向容器的第一个元素
	while (children.size() > 1) //只要容器元素个数大于1，就执行循环
	{
		for (int count = 1; count < m; count++)  //报数，循环m-1次
		{
			current++; //current指向下一个元素
			//如果current指向的是容器末尾，current指向第一个元素
			if (current == children.end()) current = children.begin();
		}
		//循环结束时，current指向将要离开圈子的小孩
		current = children.erase(current);  //小孩离开圈子，current指向
							//下一个元素
		//如果current指向的是容器末尾，current指向第一个元素
		if (current == children.end()) current = children.begin();
	} //循环结束时，current指向容器中剩下的唯一的一个元素，即胜利者
	//输出胜利者的编号
	cout << "The winner is No." << *current << "\n";
	return 0;
}