#include <stdlib.h>
#include <iostream>
#include <string>
// 학번 : 201966241
// 이름 : 박승찬
// 인증번호 : 209404059
// 상기 3가지 미기재시 채점 대상 제외
// private은 수정 불가하다, string은 include하여 사용 가능하다

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
		// ename의 형식이 string*이어서 is가 뜻대로 돌아가지 않아서 바꿨습니다.
		string name;
		is >> name;
		e.ename = new string(name);
		e.dept = new Dept();
		is >> *(e.dept);
		return is;
	}
	// private 값 가져오기 위한 메소드 
	const string* getEname() const {
		return ename;
	}

	// private 값 가져오기 위한 메소드 
	Dept* getDept() const {
		return dept;
	}
};

Emp& changeName(Emp& e) {
	// ename을 변경한다.
	string newName;
	cout << "새로운 이름 입력 : " << e.ename << ": ";
	cin >> newName;
	*(e.ename) = newName;
	return e;
}

class Stack {
private:
	Emp* items[20];
	int top;	// top 변수는 현재 저장된 객체의 마지막 색인 번호 : 0부터 시작한다.
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

	void push(Emp&); // 중복 체크하여 같으면 입력하지 않는다. 중복은 ename만으로 체크한다.
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
		cout << "\n 선택 1: Push, 2. Pop, 3. 스택 모든 객체 출력, 4. Pop한 객체의 이름 변경, 5. 종료" << endl;

		cin >> select;
		switch (select) {
		case 1:
		{
			// 화면에서 입력받는데 operator>>()를 사용한다.
			for (int i = 0; i < 3; i++) {
				Emp e;
				e.ename = new string;
				cin >> *(e.ename) >> *(e.dept);
				s2.push(e);
			}

			//for () {

			//	// 최소 3회 이상
			//	Emp e = new Emp();
			//	cin >> e;
			//	s2.push(e);
			//}
			break;
		}

		case 2:
		{
			for (int i = 0; i < s2.getTop(); i++) {
				// 최소 3회 이상
				Emp e2 = s2.pop();
				cout << "NAME : " << *(e2.getEname()) << ", DEPT : " << *(e2.getDept()) << endl;
				cout << e2;	// Emp 출력은 Dept 출력까지 처리해야 한다
			}
			break;
		}

		case 3:	// 스택 출력 > Emp 출력 > Dept 출력
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
	// 프로그램 종료시에 run-time이 없도록 소멸자 구현과 delete 호출 사용
}