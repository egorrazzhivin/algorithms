mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
cout << uniform_int_distribution<int>(l,r)(rng) << endl;

-----------

namespace generator {
  mt19937 generator(132132);
}

uniform_int_distribution<int64_t> prior(0, 1e9);
int64_t value = prior(generator::generator);
