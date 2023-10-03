//����������� ����������, ����������� ������� ������ ��������.
//������ ���� �������, ���������� ������� �� �������, � ������� �� ������� ���� ���� ���������.
//������ ����� ������ �������� � ������� � ����������� �� ������ ����������.
//���������� ��������� ���������� ������(������������, �����) � ��������� �������.

//������������� ����� ���������� �� �����.

/*

#include <iostream>
#include <string.h>
#include <time.h>
using namespace std;

class QueuePriority
{
	// �������
	int* Wait;
	// ���������
	int* Pri;
	// ������������ ������ �������
	int MaxQueueLength;
	// ������� ������ �������
	int QueueLength;

public:
	// �����������
	QueuePriority(int m);

	//����������
	~QueuePriority();

	// ���������� ��������
	void Add(int c, int p);

	// ���������� ��������
	int Extract();

	// ������� �������
	void Clear();

	// �������� ������������� ��������� � �������
	bool IsEmpty();

	// �������� �� ������������ �������
	bool IsFull();

	// ���������� ��������� � �������
	int GetCount();

	//������������ �������
	void Show();
};

void QueuePriority::Show() {
	cout << "\n-------------------------------------\n";
	//������������ �������
	for (int i = 0; i < QueueLength; i++) {
		cout << Wait[i] << " - " << Pri[i] << "\n\n";
	}
	cout << "\n-------------------------------------\n";
}

QueuePriority::~QueuePriority()
{
	//�������� �������
	delete[]Wait;
	delete[]Pri;
}

QueuePriority::QueuePriority(int m)
{
	//�������� ������
	MaxQueueLength = m;
	//������� �������
	Wait = new int[MaxQueueLength];
	Pri = new int[MaxQueueLength];
	// ���������� ������� �����
	QueueLength = 0;
}

void QueuePriority::Clear()
{
	// ����������� "�������" ������� 
	QueueLength = 0;
}

bool QueuePriority::IsEmpty()
{
	// ����?
	return QueueLength == 0;
}

bool QueuePriority::IsFull()
{
	// �����?
	return QueueLength == MaxQueueLength;
}

int QueuePriority::GetCount()
{
	// ���������� �������������� � ����� ���������
	return QueueLength;
}

void QueuePriority::Add(int c, int p)
{
	// ���� � ������� ���� ��������� �����, �� ����������� ����������
	// �������� � ��������� ����� �������
	if (!IsFull()) {
		Wait[QueueLength] = c;
		Pri[QueueLength] = p;
		QueueLength++;
	}
}

int QueuePriority::Extract()
{
	// ���� � ������� ���� ��������, �� ���������� ���, 
	// � �������� ��������� ��������� � �������� �������	
	if (!IsEmpty()) {


		//����� ������������ ������� - �������
		int max_pri = Pri[0];
		//� ������������ ������ = 0
		int pos_max_pri = 0;

		//���� ���������
		for (int i = 1; i < QueueLength; i++)
			//���� �������� ����� ������������ �������
			if (max_pri < Pri[i]) {
				max_pri = Pri[i];
				pos_max_pri = i;
			}

		//����������� ������������ �������
		int temp1 = Wait[pos_max_pri];
		int temp2 = Pri[pos_max_pri];

		//�������� ��� ��������
		for (int i = pos_max_pri; i < QueueLength - 1; i++) {
			Wait[i] = Wait[i + 1];
			Pri[i] = Pri[i + 1];
		}
		//��������� ����������
		QueueLength--;
		// ������� ������������ ��������	
		return temp1;

	}
	else return -1;
}

void main()
{
	srand(time(0));

	//�������� �������
	QueuePriority QUP(25);

	//���������� ����� ���������
	for (int i = 0; i < 25; i++) {

		// �������� �� 0 �� 99 (������������)
		// � ��������� �� 0 �� 11 (������������)
		QUP.Add(rand() % 100, rand() % 12);
	}
	//����� �������
	QUP.Show();

	//���������� ��������
	QUP.Extract();

	//����� �������
	QUP.Show();
}
 */
#pragma warning(disable: 4996)
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <ctime>

using namespace std;

struct PrintJob {
	string user;
	time_t time;
};

class PrinterQueue {
	PrintJob* printQueue;
	int maxQueueLength;
	int Length;
	PrintJob* printHistory;
	int historyLength;

public:
	PrinterQueue() {
		maxQueueLength = 0;
		printQueue = 0;
		Length = 0;
		historyLength = 0;
		printHistory = 0;
	}
	PrinterQueue(int maxQueueSize, int maxHistorySize) {
		maxQueueLength = maxQueueSize;
		printQueue = new PrintJob[maxQueueSize];
		Length = 0;
		historyLength = 0;
		printHistory = new PrintJob[maxHistorySize];
	}
	void AddJob(const string& user, int priority) {
		if (Length < maxQueueLength) {
			PrintJob job;
			job.user = user;
			job.time = time(0);
			if (priority >= 0 && priority < Length) {
				for (int i = Length; i > priority; --i) {
					printQueue[i] = printQueue[i - 1];
				}
				printQueue[priority] = job;
			}
			else {
				printQueue[Length] = job;
			}

			++Length;
		}
	}
	void Print() {
		if (Length > 0) {
			PrintJob job = printQueue[0];
			cout << "������ ������� ��� ������������: " << job.user << " (���������: " << Length - 1 << ")\n";

			if (historyLength < maxQueueLength) {
				printHistory[historyLength] = job;
				++historyLength;
			}
			else {
				for (int i = 0; i < maxQueueLength - 1; ++i) {
					printHistory[i] = printHistory[i + 1];
				}
				printHistory[maxQueueLength - 1] = job;
			}

			for (int i = 0; i < Length - 1; ++i) {
				printQueue[i] = printQueue[i + 1];
			}
			--Length;
		}
		else {
			cout << "������� ������ �����, ������ ���.\n";
		}
	}
	void ShowPrintHistory() {
		cout << "������� ������:\n";
		for (int i = 0; i < historyLength; ++i) {
			cout << "������������: " << printHistory[i].user << " - �����: " << ctime(&printHistory[i].time);
		}
	}
	~PrinterQueue() {
		delete[] printQueue;
		delete[] printHistory;
	}
};

int main() {
	srand(time(0));
	setlocale(LC_ALL, "ru");


	PrinterQueue printer(10, 10);

	for (int i = 0; i < 10; ++i) {
		string user = "User" + to_string(i);
		int priority = rand() % 5; // ���������� ��������� ��������� (0-4)
		printer.AddJob(user, priority);
	}
	for (int i = 0; i < 10; ++i) {
		printer.Print(); // �������� ������

		printer.ShowPrintHistory(); // ������� ������� ������
	}
	

	return 0;
}
