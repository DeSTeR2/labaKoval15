static long long R = 1;

long long setRadius(long long r) {
    if (r >= 0)
        R = r;
    return R;
}

long long isInCircle(long long x, long long y) {
    return x * x + y * y < R * R;
}