#include <stdlib.h>
#include <iostream>
#include <string>
// �й� : 201966241
// �̸� : �ڽ���
// ������ȣ : 209404059
// ��� 3���� �̱���� ä�� ��� ����
// private�� ���� �Ұ��ϴ�, string�� include�Ͽ� ��� �����ϴ�

using namespace std;


class Dept {
private:
	string dname;
	char* city;
public:
	friend ostream& operator<<(ostream& os, Dept& d) {
		os << "dName : " << d.dname << ", City : " << d.city;
	}
	friend istream& operator>>(istream& is, Dept& d) {
		is >> d.dname >> d.city;
	}

	const string& GetCity() const {
		return city;
	}

	const string& GetDname() const {
		return dname;
	}
};

class Emp {
private:
	friend class Stack;
	string* ename;
	Dept* dept;

public:
	Emp() : ename(nullptr), dept(nullptr) {}
	Emp(string* name, Dept* dept) {
		ename = new string(*name);
		this->dept = new Dept(*dept);
	}

	~Emp() {
		delete ename;
		delete[] dept;
	}



	friend Emp& changeName(Emp&);
	friend ostream& operator<<(ostream& os, Emp& e) {
		os << "NAME : " << e.ename << ", DEPT : " << e.dept;
		return os;
	}

	friend istream& operator>>(istream& is, Emp& e) {
		// ename�� ������ string*�̾ is�� ���� ���ư��� �ʾƼ� �ٲ���ϴ�.
		string name;
		is >> name;
		e.ename = new string(name);
		e.dept = new Dept();
		is >> *(e.dept);
		return is;
	}
	// private �� �������� ���� �޼ҵ� 
	const string* getEname() const {
		return ename;
	}

	// private �� �������� ���� �޼ҵ� 
	Dept* getDept() const {
		return dept;
	}
};

Emp& changeName(Emp& e) {
	// ename�� �����Ѵ�.
	string newName;
	cout << "���ο� �̸� �Է� : " << e.ename << ": ";
	cin >> newName;
	*(e.ename) = newName;
	return e;
}

class Stack {
private:
	Emp* items[20];
	int top;	// top ������ ���� ����� ��ü�� ������ ���� ��ȣ : 0���� �����Ѵ�.
public:
	Stack() {
		top = 0;
	}
	~Stack() {
		for (int i = 0; i < top; i++) {
			delete items[i];
		}
	}

	friend ostream& operator<<(ostream& os, Stack& s) {
		for (int i = 0; i < s.top; i++) {
			os << *s.items[i] << endl;
		}
		return os;
	}

	void push(Emp&); // �ߺ� üũ�Ͽ� ������ �Է����� �ʴ´�. �ߺ��� ename������ üũ�Ѵ�.
	Emp& pop();

	int getTop() {
		return top;
	}
};

void Stack::push(Emp& e) {
	this->items[top] = new Emp(e.ename, e.dept);
	cout << "Name : " << e.ename << " dept : " << e.dept << endl;
}

Emp& Stack::pop() {
	Emp* e = items[top - 1];
	top--;
	return *e;
}


int main() {
	while (1)
	{
		Stack s2;

		int select;
		cout << "\n ���� 1: Push, 2. Pop, 3. ���� ��� ��ü ���, 4. Pop�� ��ü�� �̸� ����, 5. ����" << endl;

		cin >> select;
		switch (select) {
		case 1:
		{
			// ȭ�鿡�� �Է¹޴µ� operator>>()�� ����Ѵ�.
			for (int i = 0; i < 3; i++) {
				Emp e;
				e.ename = new string;
				cin >> *(e.ename) >> *(e.dept);
				s2.push(e);
			}

			//for () {

			//	// �ּ� 3ȸ �̻�
			//	Emp e = new Emp();
			//	cin >> e;
			//	s2.push(e);
			//}
			break;
		}

		case 2:
		{
			for (int i = 0; i < s2.getTop(); i++) {
				// �ּ� 3ȸ �̻�
				Emp e2 = s2.pop();
				cout << "NAME : " << *(e2.getEname()) << ", DEPT : " << *(e2.getDept()) << endl;
				cout << e2;	// Emp ����� Dept ��±��� ó���ؾ� �Ѵ�
			}
			break;
		}

		case 3:	// ���� ��� > Emp ��� > Dept ���
		{
			cout << s2;
			break;
		}

		case 4:
		{
			Emp e3 = s2.pop();
			Emp e4 = changeName(e3);
			s2.push(e4);
			break;
		}

		default:
			exit(0);
			break;
		}
	}
	system("pause");
	return 1;
	// ���α׷� ����ÿ� run-time�� ������ �Ҹ��� ������ delete ȣ�� ���
}