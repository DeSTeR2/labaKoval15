#include <iostream>
#include <random>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

#include "monte-carlo.hpp";
#include "rectangle.hpp";
#include "paralelepiped.h";
#include "fibRandom.hpp";

/*

	��������� fibRandom() ��������������� ��� ���������� ����� �� ��������� ����� ������ ������
	���������� �������� ������� (�����, ����� � �����)

	����������� - ������� ������ ����� ��� �� �� ����� � ������ ���� �����
	���������� ����� � ������ � ���������� � ������� (�� T0 (��������� �����������) >> T1 (������ �����������))


	�������� ������ �������� ������:
		������� �������� ����
		������ ����� �� ����������� ����

		������� �������� ��'���
		������ ����� �� ��'��� �����������

		������� ������� ����㳿
		������ ����㳿 �� ���� � ����� �� ����㳿 �������


		��������� ������� Put():
			1. Put()
			2. A B C (������ �������������)
			3. ������� ����� �������������

		��� ��� Drop() �� Accept()

*/

bool fly = false;

const int H = 10 + 4 % 10, W = 10 + 12 % 10, M_max = 2006 * 4, V_max = 2006 * 12;
int T0 = 282 /* 9 ������� �� ������ � ��������*/, T1 = (4 + (12 % 4)) /* ����������� � �������� */, Tp = 1083;
float n = 0.1;

int c = 2;		// ������ ���������� ������

int curM = 0, curV = 0;

long long Er,			// - ������ Rotate()
Et,			// - ������ Turn()
Es,			// - ������ Spoon()
Ep,			// - ������ Put()
Ed,			// - ������ Drop()
Ea,			// - ������ Accept()
Ec,			// - ������ Cut()

Ef,			// - ������ Fly()
E0;			// - ������ �������

void setSystem(int E, int E1) {

	srand(time(0));

	Er = rand() % E;
	Et = rand() % E;
	Es = rand() % E;
	Ep = rand() % E;
	Ed = rand() % E;
	Ea = rand() % E;
	Ec = rand() % E;

	Ef = (1000 + rand() % (E1* 400) );
	E0 = (1000 + rand() % E1) + Ep + Ed + Ea + Ec;

	while (Ef <= E0) {
		Ef = (1000 + rand() % (E1 * 400));
		E0 = (1000 + rand() % E1) + Ep + Ed + Ea + Ec;
	}
}
void genGold() {

	setFibRandomM(abs(rand()) % 5 + 10);

	int a = fibRandom();
	int b = fibRandom();
	int c = fibRandom();
	int ro = fibRandom();

	while (setSize(a, b, c, ro) == false) {
		a = fibRandom();
		b = fibRandom();
		c = fibRandom();
		ro = fibRandom();
	}
	//setFibRandomM(fibRandom());
	//resetFibRandom();
}
int heatNumber(int mass, int v, int t0, int t1) {
	float dt = t0 - t1;
	return mass * dt * c;
}
void AorD();
void recuperator(int t0, int t1) {
	float heat = heatNumber(calcMass(), calcV(), t0, t1) * n;
	E0 += heat;
}

void Cout_underline(int n) {
	for (int i = 0; i < n; i++) {
		cout << "_";
	}
	cout << "\n";
}

int spaces(int n) {
	return to_string(n).size();
}

void Cout_currentState() {
	Cout_underline(30);
	string current = "Current", need = "Need", energy = "Energy", mass = "Mass", volume = "Volume";

	int szs[] = { current.size(), spaces(curV) , spaces(curM), spaces(M_max), spaces(V_max), spaces(E0), spaces(Ef) };
	int sp = 0;
	for (int i = 0; i < 6; i++) {
		sp = max(sp, szs[i]);
	}
	//cout << sp;
	//return;
	

	for (int i = 0; i < volume.size() + 1; i++) cout << " ";
	cout << "| Current ";
	for (int i = 0; i < sp - ( current.size()) + 1; i++) cout << " ";
	cout << "| Need ";
	for (int i = 0; i < sp - (2 + need.size()) + 1; i++) cout << " ";
	for (int i = 0; i < volume.size() + 1; i++) cout << " ";
	cout << "\n";
	cout << mass << "   | " << curM;
	for (int i = 0; i < sp - spaces(curM) + 2; i++) cout << " ";
	cout << "| " << M_max << "\n";

	cout << volume << " | " << curV;
	for (int i = 0; i < sp - spaces(curV) + 2; i++) cout << " ";
	cout << "| " << V_max << "\n";
	
	cout.setf(ios::fixed);
	cout << energy << " | " << setprecision(0) << E0;
	for (int i = 0; i < sp - spaces(E0) + 2; i++) cout << " ";
	cout << "| " << setprecision(0) << Ef << "\n";
}

// ������ ������������ ������? 
void Put() {
	E0 -= Ep;
	genGold();
	Cout_underline(30);
	cout << "Put()\nA = " << getA() << ", B = " << getB() << ", C = " << getC() << "\nRo = " << getRo() << "\n";
}

// ��������, �� �� ��������
void Drop() {
	E0 -= Ed;
	Cout_underline(30);
	cout << "Drop()\n";
}

// �����������, ���� ������� ������� � ���������� ���� ������� HxM
void Accept();

// ���� ���������� ���� (�� ��� �� ��'���) ���������� ������ ����� ������� ������ ������� ��
// ��������� ����� ������ �� Fly() ������

void Cut();

void Fly() {
	if (E0 > Ef) {
		Cout_underline(30);
		cout << "Fly()\n";
		fly = true;
	}
}


int main() {
	setSystem(500,1000);
	setSides(H, W);
	setFibRandomM(20);

	//cout << E0 << " " << Ef;
	
	while (fly == false) {
		Put();
		AorD();
		//Cut();
		Cout_currentState();
		if (fly == true) break;
		//Fly();
	}
	
}



void AorD() {
	if (getC() <= H && getA() <= W) Accept();
	else Drop();
}

void Accept() {
	E0 -= Ea;
	recuperator(9, Tp);
	recuperator(Tp, T1);
	Cout_underline(30);
	cout << "Accept()\n";
	Cut();
}

void Cut() {
	E0 -= Ec;
	curM += calcMass();
	curV += calcV();

	if (curM > M_max || curV > V_max) {
		

		curM -= calcMass();
		curV -= calcV();

		int A = getA(), B = getB(), C = getC();
		int cntV = V_max - curV;
		int cntM = M_max - curM;
		int Min = min(cntM / getRo(), cntV);

		Cout_underline(30);
		int newA = Min / (B * C);
		if (newA >= 1) {
			cout << "Cut " <<  newA << " - -\n";
			setA(newA);
			curM += calcMass();
			curV += calcV();
			Fly();
			return;
		}

		int newB = Min / (A * C);
		if (newB >= 1) {
			cout << "Cut - " << newB << " -\n";
			setB(newB);
			curM += calcMass();
			curV += calcV();
			Fly();
			 
		}

		int newC = Min / (B * C);
		if (newC >= 1) {
			cout << "Cut - - " << newC << "\n";
			setC(newC);
			curM += calcMass();
			curV += calcV();
			Fly();
			return;
		}
	}
}