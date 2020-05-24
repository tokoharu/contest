
double PI = 3.141592653589793238;
#define EPS (1e-10)
struct Point {
  LL x, y;
  Point() {}
  Point(LL x, LL y) : x(x), y(y) {}
  Point operator+(Point p) { return Point(x + p.x, y + p.y); }
  Point operator-(Point p) { return Point(x - p.x, y - p.y); }
  Point operator*(double k) { return Point(x * k, y * k); }
  Point operator/(double k) { return Point(x / k, y / k); }
  LL norm() { return x * x + y * y; }
  LL abs() { return sqrt(norm()); }

  bool operator<(const Point& p) const {
    return x != p.x ? x < p.x : y < p.y;
    // grid-point only
    // return !equals(x,p.x)?x<p.x:!equals(y,p.y)?y<p.y:0;
  }

  bool operator==(const Point& p) const {
    return fabs(x - p.x) < EPS && fabs(y - p.y) < EPS;
  }
};

LL dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }

LL cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }

static const int CCW_COUNTER_CLOCKWISE = 1;
static const int CCW_CLOCKWISE = -1;
static const int CCW_ONLINE_BACK = 2;
static const int CCW_ONLINE_FRONT = -2;
static const int CCW_ON_SEGMENT = 0;
int ccw(Point p0, Point p1, Point p2) {
  Point a = p1 - p0;
  Point b = p2 - p0;
  if (cross(a, b) > 0) return CCW_COUNTER_CLOCKWISE;
  if (cross(a, b) < 0) return CCW_CLOCKWISE;
  if (dot(a, b) < 0) return CCW_ONLINE_BACK;
  if (a.norm() < b.norm()) return CCW_ONLINE_FRONT;
  return CCW_ON_SEGMENT;
}

typedef vector<Point> Polygon;

/*
  反時計回りに凸包を出力する。
*/
Polygon andrewScan(Polygon s) {
  Polygon u, l;
  if (s.size() < 3) return s;
  sort(s.begin(), s.end());
  u.push_back(s[0]);
  u.push_back(s[1]);
  l.push_back(s[s.size() - 1]);
  l.push_back(s[s.size() - 2]);
  for (int i = 2; i < (int)s.size(); i++) {
    for (int n = u.size();
         n >= 2 && ccw(u[n - 2], u[n - 1], s[i]) != CCW_CLOCKWISE; n--) {
      u.pop_back();
    }
    u.push_back(s[i]);
  }
  for (int i = s.size() - 3; i >= 0; i--) {
    for (int n = l.size();
         n >= 2 && ccw(l[n - 2], l[n - 1], s[i]) != CCW_CLOCKWISE; n--) {
      l.pop_back();
    }
    l.push_back(s[i]);
  }
  reverse(l.begin(), l.end());
  for (int i = u.size() - 2; i >= 1; i--) l.push_back(u[i]);
  return l;
}