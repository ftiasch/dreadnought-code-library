const double PI = acos(-1.0);
void discreteFourierTransform(Complex *x, int on, int n) {
	int k, id; long double r, tmp; Complex u, t;
	for(int i = 1, j = n >> 1; i < n - 1; ++ i) {
		if (i < j) swap(x[i], x[j]);
		for(k = n >> 1; j >= k; j -= k, k >>= 1);
		j += k;
	}
	for (int h = 2; h <= n; h <<= 1) {
		r = on * 2.0 * PI / h;  
		Complex wn(cos(r), sin(r));  
		for (int j = 0, p = h >> 1; j < n; j += h) {  
			Complex w(1, 0);  
			for (k = j; k < j + p; k++) {  
				u = x[k]; id = k + p;
				t.real = w.real * x[id].real - w.imag * x[id].imag;
				t.imag = w.real * x[id].imag + w.imag * x[id].real;
				x[k].real = u.real + t.real;
				x[k].imag = u.imag + t.imag;
				x[id].real = u.real - t.real;
				x[id].imag = u.imag - t.imag;
				tmp = w.real;
				w.real = w.real * wn.real - w.imag * wn.imag;
				w.imag = tmp * wn.imag + w.imag * wn.real;
}}}}
Complex xa[N], xb[N];
void multiply(int *a, int lenA, int *b, int lenB, long long *ans, int &lenAns) {
	for(lenAns = 1; lenAns < lenA + lenB; lenAns <<= 1);
	for(int i = 0; i < lenAns; ++ i)
		xa[i].real = xa[i].imag = xb[i].real = xb[i].imag = 0;
	for(int i = 0; i < lenA; ++ i) xa[i].real = a[i];
	for(int i = 0; i < lenB; ++ i) xb[i].real = b[i];
	discreteFourierTransform(xa, 1, lenAns);
	discreteFourierTransform(xb, 1, lenAns);
	for(int i = 0; i < lenAns; ++ i) xa[i] = xa[i] * xb[i];
	discreteFourierTransform(xa, -1, lenAns);
	for(int i = 0; i < lenAns; ++ i) ans[i]=(long long)(xa[i].real/lenAns+0.5);
}
