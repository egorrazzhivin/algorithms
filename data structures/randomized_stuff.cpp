mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
cout << uniform_int_distribution<int>(l,r)(rng) << endl;

-----------

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int64_t> prior(0, 1e15);
int64_t value = prior(generator);
