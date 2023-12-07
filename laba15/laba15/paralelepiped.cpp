static int A, B, C;
static int ro;

// A - ������ � - ������� � - ������

int getA() {
	return A;
}
int getB() {
	return B;
}
int getC() {
	return C;
}
int getRo() {
	return ro;
}

void setA(int a) {
	A = a;
}
void setB(int a) {
	B = a;
}

void setC(int a) {
	C = a;
}

void swap(int& a, int& b) {
	int buff = a;
	a = b;
	b = buff;
}

bool setSize(int a, int b, int c, int RO) {
	if (a >= 1 && b >= 1 && c >= 1 && RO >= 1) {
		A = a, B = b, C = c;
		ro = RO;
		return true;
	}
	else return false;
}

int calcV() {
	return A * B * C;
}

int calcMass() {
	return calcV() * ro;
}

void Turn() {		// � ������� �� ����
	swap(A, B);
}
void Rotate() {		// � ����� �� ����������
	swap(B, C);
}
void Spoon() { 		// �� ��������
	swap(A, C);
}