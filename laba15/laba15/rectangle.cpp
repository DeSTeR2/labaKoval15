static long long A, B;

long long setSides(long long a, long long b) {
    if (a >= 0)
        A = a;
    if (b >= 0)
        B = b;
    return A * B;
}

long long isInRectangle(long long x, long long y) {
    return x <= A && y <= B;
}