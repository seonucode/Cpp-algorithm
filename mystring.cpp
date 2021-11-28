#define MAX_LEN 25
#include <iostream>
#include <string>
using namespace std;

class mystring {
public:
	mystring() : content(NULL), len(0) {}
	mystring(const char* str);
	mystring(const mystring& str);
	~mystring() { delete[] content; }

	int length() { return len; }

	const mystring shiftLeft(int n);
	const mystring shiftRight(int n);
	const mystring reverse();

	mystring& operator=(const mystring& str);
	char& operator[](int index);
	friend const mystring operator +(const mystring& s1, const mystring& s2);
	friend ostream& operator << (ostream& outputStream, const mystring& s);

private:
	char* content;
	int len;
};

mystring::mystring(const char* str) {
	//TODO
	int i = 0;
	while (*(str + i)) {
		i++;
	}
	len = i;
	content = new char[len];
	i = 0;
	while (*(str + i)) {
		*(content + i) = *(str + i);
		i++;
	}
}

mystring::mystring(const mystring& str) {
	//TODO
	len = str.len;
	content = new char[len];
	for (int i = 0; i < len; i++) {
		*(content + i) = *(str.content + i);
	}
}

const mystring mystring::shiftLeft(int n) {
	//TODO
	char *p_ch;
	p_ch = new char[len];
	for (int i = 0; i < len; i++) {
		if (i < n) {
			*(p_ch + i - n + len) = *(content + i);
		}
		else {
			*(p_ch + i - n) = *(content + i);
		}
	}
	return mystring(p_ch);
}

const mystring mystring::shiftRight(int n) {
	//TODO
	char *p_ch;
	p_ch = new char[len];
	for (int i = 0; i < len; i++) {
		if (i < len - n) {
			*(p_ch + i + n) = *(content + i);
		}
		else {
			*(p_ch + i + n - len) = *(content + i);
		}
	}
	return mystring(p_ch);
}

const mystring mystring::reverse() {
	//TODO
	char *p_ch;
	p_ch = new char[len];
	for (int i = 0; i < len; i++) {
		*(p_ch + len - 1 - i) = *(content + i);
	}
	return mystring(p_ch);
}

mystring& mystring::operator=(const mystring& str) {
	//TODO
	len = str.len;
	content = new char[len];
	for (int i = 0; i < str.len; i++) {
		*(content + i) = *(str.content + i);
	}
	return *this;
}

char& mystring::operator[](int index) {
	//TODO
	return *(content + index);
}

const mystring operator+(const mystring& s1, const mystring& s2) {
	//TODO
	mystring str;
	str.len = s1.len + s2.len;
	str.content = new char[str.len];
	for (int i = 0; i < str.len; i++) {
		if (i < s1.len) {
			*(str.content + i) = *(s1.content + i);
		}
		else {
			*(str.content + i) = *(s2.content + i - s1.len);
		}
	}
	return str;
}

ostream& operator <<(ostream& outputstream, const mystring& s) {
	//TODO
	for (int i = 0; i < s.len; i++) {
		cout << *(s.content + i);
	}
	return outputstream;
}

int main() {
	char temp[MAX_LEN];
	cout << "Enter string: " << endl;
	cin >> temp;

	cout << endl << endl;

	mystring s1, s2, s3;
	s1 = mystring(temp);
	s2 = mystring(s1);
	s3 = s1 + s2;

	cout << "Strings: " << endl;
	cout << s1 << endl;
	cout << s2 << endl;
	cout << s3 << endl;
	cout << endl << endl;

	cout << "After operations: " << endl;
	cout << s1.shiftLeft(2) << endl;
	cout << s2.shiftRight(2) << endl;
	cout << s3.reverse() << endl;

	return 0;
}
