std::ostream &operator<<(std::ostream &os, i128 n) {
    std::string s;
    while (n) {
        s += '0' + n % 10;
        n /= 10;
    }
    std::reverse(s.begin(), s.end());
    return os << s;
}

i128 sqrt(i128 x)//开方
{
    i128 y=(i128)ceil(sqrt((long double)x));
    for(;y*y<=x;++y);
    for(--y;y*y>x;--y);
    return y;
}