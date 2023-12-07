static long long fibNumModM0 = 0;
static long long fibNumModM1 = 1;

static int M = 20;

long long fibRandom() {
    long long next = (fibNumModM0 + fibNumModM1) % M;
    fibNumModM0 = fibNumModM1;
    fibNumModM1 = next;
    return fibNumModM0;
}

long long resetFibRandom() {
    fibNumModM0 = 0;
    fibNumModM1 = 1;
    return fibNumModM0;
}

long long setFibRandomM(long long m) {
    if (m > 1)
        M = m;
    return M;
}