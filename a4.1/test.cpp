#include <iostream>

using namespace std;
template<typename T>
bool compare(T a, T b);

int main() {
	compare("aaa","bbb" );
	compare<const char*>("aaa", "bbb");
	return 0;
}
