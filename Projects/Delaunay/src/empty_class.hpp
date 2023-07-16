#ifndef __EMPTY_H
#define __EMPTY_H

#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<algorithm>


using namespace std;

namespace ProjectLibrary {

    class point {
    private:
        double _id;
        double _x;
        double _y;

    public:
        point();

        point(const double &id, const double &x, const double &y) {
            _id = id;
            _x = x;
            _y = y;
        };

        double getId() const;

        double getX() const;

        double getY() const;

        static vector<point> importFromFile(const string &filename);

        bool isEqual(const point &p1) const;
    };

    class segment {
    private:
        point _startpoint;
        point _endpoint;
    public:
        segment();

        segment(const point &startpoint, const point &endpoint) {
            _startpoint = startpoint;
            _endpoint = endpoint;
        };

        point getstartpoint() const;

        point getendpoint() const;

        bool isEqualseg(const segment &seg) const;

        static bool intersect(const segment &segment1, const segment &segment2);

        static double calculateangle(vector<segment> &segments);

        static vector<segment> findConnectingSegments(const vector<segment>& inputSegments, const vector<point>& points) ;


    };

    class triangle {
    private:
        point _p1;
        point _p2;
        point _p3;
        mutable vector<segment> _segments;
        segment _side1;
        segment _side2;
        segment _side3;

    public:
        triangle() {};

        triangle(const point &p1, const point &p2, const point &p3) : _p1(p1), _p2(p2), _p3(p3), _side1(p1, p2),
                                                                      _side2(p2, p3), _side3(p3, p1) {};

        point getp1() const;

        point getp2() const;

        point getp3() const;

        segment getside1() const;

        segment getside2() const;

        segment getside3() const;

        bool isEqualtri(const triangle &t) const;

        double area(const point &p1, const point &p2, const point &p3) const;

        void orderPoints(const point &p1, const point &p2, const point &p3);

        bool isPointInside(const point &p, const triangle &t) const;

        bool isPointOnside(const point &p, const triangle &t) const;

        static vector<triangle> generateTriangles(const vector<point> &points);

        static bool delaunay(const triangle &t1, const triangle &t2, const segment &segment);

        static bool commonsidebool(triangle &t1, triangle &t2);

        static segment commonside(triangle &t1, triangle &t2);

        static vector<triangle> flip(segment &segment, const triangle &t1, const triangle &t2);


    };


}
#endif // __EMPTY_H
