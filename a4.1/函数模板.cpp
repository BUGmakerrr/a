#include <iostream>
using namespace std;

template<typename T>
bool compare(T a, T b) {
	cout << "template compare" << endl;
	return a > b;
}
template<>
bool compare<const char*>(const char* a, const char* b) {
	cout << "compare<const char*>" << endl;
	return strcmp(a, b) > 0;
}
bool compare(const char* a, const char* b) {
	cout << " normal compare" << endl;
	return strcmp(a, b) > 0;
}
