long double simpson(long double a, long double b) {
	return (f(a) + 4 * f((a + b) / 2) + f(b)) * (b - a) / 6;
}

long double integral(long double L, long double R, long double eps) {
	long double mid = (L + R) / 2;
	long double S_total = simpson(L, R);
	long double S_left = simpson(L, mid);
	long double S_right = simpson(mid, R);
	long double delta = S_left + S_right - S_total;
	if (fabs(delta) < 15 * eps)
	return S_left + S_right + delta / 15;
	return integral(L, mid, eps / 2) + integral(mid, R, eps / 2);
}