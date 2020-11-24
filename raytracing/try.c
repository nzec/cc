#include <bits/stdc++.h>
#include "vec3.h"

using namespace std;

int main(void) {
	vec3 a(2, 3, 4);
	a[2] = 0;
	a /= 2;
	cout << a.len_sq();
}
