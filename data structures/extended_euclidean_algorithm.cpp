// a * x + b * y = gcd(a, b);

pair<int64_t, int64_t> extended_gcd(int64_t a, int64_t b) {
    if (b == 0) {
        return {1, 0};
    }
    pair<int64_t, int64_t> p = extended_gcd(b, a % b);
    int64_t x = p.second;
    int64_t y = p.first - (a / b) * p.second;
    return {x, y};
}
