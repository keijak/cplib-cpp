#include <bits/stdc++.h>
using i64 = long long;

// line: y = k*x + m
struct Line {
  mutable i64 k, m, p;
  bool operator<(const Line& o) const { return k < o.k; }
  bool operator<(i64 x) const { return p < x; }
};

struct LineContainer : public std::multiset<Line, std::less<>> {
  static const i64 INF = std::numeric_limits<i64>::max();

  void add(i64 k, i64 m) {
    auto z = insert({k, m, 0}), y = z++, x = y;
    while (isect(y, z)) z = erase(z);
    if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
  }

  i64 query(i64 x) const {
    assert(!empty());
    auto l = *lower_bound(x);
    return l.k * x + l.m;
  }

 private:
  static i64 div(i64 a, i64 b) {  // floored division
    return a / b - ((a ^ b) < 0 && a % b);
  }

  bool isect(iterator x, iterator y) {
    if (y == end()) {
      x->p = INF;
      return false;
    }
    if (x->k == y->k) {
      x->p = x->m > y->m ? INF : -INF;
    } else {
      x->p = div(y->m - x->m, x->k - y->k);
    }
    return x->p >= y->p;
  }
};
