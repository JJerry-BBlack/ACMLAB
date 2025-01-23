void ols(double n, double*x, double*y,double&k,double&b) {//ordinary least squares
	double sumx = 0, sumy = 0, sumxx = 0, sumxy = 0;
	for(int i=1;i<=n;++i){
		sumx += x[i];
		sumy += y[i];
		sumxx += x[i] * x[i];
		sumxy += x[i] * y[i];
	}
	k = (sumx * sumy - n * sumxy) / (sumx * sumx - sumxx * n);
	b = -(sumxx * sumy - sumx * sumxy) / (sumx * sumx - sumxx * n);
}
double variance(double* x, double* y, double& k, double& b) {
	double res = 0;
	for (int i = 1; i <= n; ++i) {
		res += (k * x[i] + b - y[i]) * (k * x[i] + b - y[i]);
	}
	return res;
}