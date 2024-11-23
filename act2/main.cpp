#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

// Algoritmo obtenido de 
// https://www.geeksforgeeks.org/convex-hull-using-jarvis-algorithm-or-wrapping/


struct Point {
    int x, y;
    int index;
};

bool onSegment(Point p, Point q, Point r) {
    return (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
            q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y));
}

int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0; // collinear
    return (val > 0) ? 1 : 2; // clock or counterclock wise
}

double distance(Point p1, Point p2) { // euclidean distance
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

bool comparePoints(Point a, Point b) {
    return (a.y < b.y) || (a.y == b.y && a.x < b.x);
} // if two points have the same y-coordinate, the one with the smaller x-coordinate comes first, else the one with the smaller y-coordinate comes first

bool areCollinear(const std::vector<Point>& points) {
    if (points.size() <= 2) return true;
    
    for (int i = 2; i < points.size(); i++) {
        if (orientation(points[0], points[1], points[i]) != 0)
            return false;
    }
    return true;
}

std::vector<Point> handleCollinearPoints(std::vector<Point>& points) {
    if (points.size() <= 2) return points;
    
    // Find the two most distant points
    double maxDist = 0;
    Point p1, p2;
    for (int i = 0; i < points.size(); i++) {
        for (int j = i + 1; j < points.size(); j++) {
            double dist = distance(points[i], points[j]);
            if (dist > maxDist) {
                maxDist = dist;
                p1 = points[i];
                p2 = points[j];
            }
        }
    }
    
    std::vector<Point> result;
    if (comparePoints(p1, p2)) {
        result.push_back(p1);
        result.push_back(p2);
    } else {
        result.push_back(p2);
        result.push_back(p1);
    }
    return result;
}

std::pair<double, std::vector<Point> > convexHull(std::vector<Point>& points) {
    int n = points.size();
    if (n <= 1) return std::make_pair(0.0, points);
    
    // Check if points are collinear
    if (areCollinear(points)) {
        auto endpoints = handleCollinearPoints(points);
        double perim = endpoints.size() <= 1 ? 0.0 : distance(endpoints[0], endpoints[1]) * 2;
        return std::make_pair(perim, endpoints);
    }

    std::vector<Point> hull;
    int l = 0;
    for (int i = 1; i < n; i++) {
        if (comparePoints(points[i], points[l]))
            l = i;
    }

    int p = l;
    do {
        hull.push_back(points[p]);
        int q = (p + 1) % n;
        
        for (int i = 0; i < n; i++) {
            if (orientation(points[p], points[i], points[q]) == 2)
                q = i;
        }
        
        p = q;
    } while (p != l);

    double perimeter = 0;
    for (size_t i = 0; i < hull.size(); i++) {
        perimeter += distance(hull[i], hull[(i + 1) % hull.size()]);
    }

    return {perimeter, hull};
}

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;

        std::vector<Point> points;
        for (int i = 0; i < n; i++) {
            Point p;
            std::cin >> p.x >> p.y;
            p.index = i + 1;
            
            bool isDuplicate = false;
            for (const Point& existing : points) {
                if (existing.x == p.x && existing.y == p.y) {
                    isDuplicate = true;
                    break;
                }
            }
            if (!isDuplicate) {
                points.push_back(p);
            }
        }

        auto result = convexHull(points);
        double perimeter = result.first;
        std::vector<Point>& hull = result.second;

        std::cout << std::fixed << std::setprecision(2) << perimeter << std::endl;
        for (size_t i = 0; i < hull.size(); i++) {
            std::cout << hull[i].index;
            if (i < hull.size() - 1) std::cout << " ";
        }
        std::cout << std::endl << std::endl;
    }

    return 0;
}