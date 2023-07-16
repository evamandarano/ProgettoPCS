#include "empty_class.hpp"
#include<fstream>
#include<vector>
#include <iostream>
#include<cmath>
#include<algorithm>

using namespace std;
namespace ProjectLibrary {
    point::point() {
        _id = 0;
        _x = 0.0;
        _y = 0.0;
    }

    double point::getId() const {
        return _id;
    }

    double point::getX() const {
        return _x;
    }

    double point::getY() const {
        return _y;
    }

    vector<point> point::importFromFile(const string &filename) {
        ifstream file;
        file.open(filename);
        if (file.fail()) {
            cerr << "failed to open file" << endl;
        }
        string line;
        getline(file, line);
        vector<point> points;
        double id, x, y;
        while (file >> id >> x >> y) {
            points.emplace_back(point(id, x, y));
        }
        if (points.empty()) {
            // Errore nella lettura del file
            throw std::runtime_error("Errore nella lettura del file");
        }
        file.close();
        return points;
    }

    bool point::isEqual(const point &p) const {
        return getId() == p.getId() && getX() == p.getX() && getY() == p.getY();
    }

    segment::segment() {
        _startpoint = point();
        _endpoint = point();
    }

    point segment::getstartpoint() const {
        return _startpoint;
    }

    point segment::getendpoint() const {
        return _endpoint;
    }

    bool segment::isEqualseg(const segment &seg) const {
        return (getstartpoint().isEqual(seg.getstartpoint()) && getendpoint().isEqual(seg.getendpoint())) || (getstartpoint().isEqual(seg.getendpoint()) && getendpoint().isEqual(seg.getstartpoint()));
    }

    bool segment::intersect(const segment &segment1, const segment &segment2){
    // Returns 1 if the lines intersect, otherwise 0. In addition, if the lines
    // intersect the intersection point may be stored in the floats i_x and i_y.
        double x1 = segment1._startpoint.getX();
        double y1 = segment1._startpoint.getY();
        double x2 = segment1._endpoint.getX();
        double y2 = segment1._endpoint.getY();

        double x3 = segment2._startpoint.getX();
        double y3 = segment2._startpoint.getY();
        double x4 = segment2._endpoint.getX();
        double y4 = segment2._endpoint.getY();

        double denom = (y4-y3)*(x2-x1) - (x4-x3)*(y2-y1);

        if(denom == 0){ // parallel
            return false;
        }
        double ua = ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3))/ denom;
        if(ua < 0 or ua > 1){
            return false;
        }
        double ub = ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / denom;
        if(ub < 0 or ub > 1){
            return false;
        }
        double x = x1 + ua * (x2-x1);
        double y = y1 + ua * (y2-y1);
        if ((x==x1) && (y==y1)){
               return false;
        }
        if ((x==x2) && (y==y2)){
               return false;
        }
        if ((x==x3) && (y==y3)){
               return false;
        }
        if ((x==x4) && (y==y4)){
               return false;
        }
        return true;
    }

    double segment::calculateangle(vector<segment> &segments) {//passo due segmenti
        segment segment1 = segments[0];
        segment segment2 = segments[1];
        point p1= segment1.getstartpoint();
        point p2=segment1.getendpoint();
        point p3= segment2.getstartpoint();
        point p4=segment2.getendpoint();
        point commonP;
        point tmp_p1;
        point tmp_p2;
        if (p1.isEqual(p3)) {
                commonP = p1;
                tmp_p1= p2;
                tmp_p2 = p4;
            } else if (p1.isEqual(p4)) {
                commonP = p1;
                tmp_p1= p2;
                tmp_p2 = p3;
            } else if (p2.isEqual(p3)) {
                commonP = p2;
                tmp_p1= p1;
                tmp_p2 = p4;
            } else if (p2.isEqual(p4)) {
                commonP = p2;
                tmp_p1= p1;
                tmp_p2 = p3;
            } else {
                // I segmenti non hanno un punto comune
                return -1;
            }

            double A_x = tmp_p1.getX() - commonP.getX();
            double A_y = tmp_p1.getY() - commonP.getY();
            double B_x = tmp_p2.getX() - commonP.getX();
            double B_y = tmp_p2.getY() - commonP.getY();
            double lengthA = sqrt(A_x * A_x + A_y * A_y);
            double lengthB = sqrt(B_x * B_x + B_y * B_y);
            double dotProduct = A_x * B_x + A_y * B_y;
            double cosTheta = dotProduct / (lengthA * lengthB);
            double theta = acos(cosTheta);
            double angle = theta * 180.0 / M_PI;
            return angle;
    }

    vector<segment> segment::findConnectingSegments(const vector<segment>& inputSegments, const vector<point>& points)  {
        vector<segment> connectingSegments;
        for (unsigned int i= 0; i< inputSegments.size(); i++) {
            bool startPointFound = false;
            bool endPointFound = false;

            for (unsigned int j= 0; j< points.size(); j++) {

                if (!startPointFound && inputSegments[i].getstartpoint().isEqual(points[j]) ){
                    startPointFound = true;
                }

                if (!endPointFound && inputSegments[i].getendpoint().isEqual(points[j]) ) {
                    endPointFound = true;
                }

                if (startPointFound && endPointFound) {
                    connectingSegments.push_back(inputSegments[i]);
                    break;
                }
            }
        }

        return connectingSegments;
    }

    point triangle::getp1() const {
        return _p1;
    }

    point triangle::getp2() const {
        return _p2;
    }

    point triangle::getp3() const {
        return _p3;
    }

    segment triangle::getside1() const {
        return _side1;
    }

    segment triangle::getside2() const {
        return _side2;
    }

    segment triangle::getside3() const {
        return _side3;
    }

    bool triangle::isEqualtri(const triangle &t) const {
        return     (getside1().isEqualseg(t.getside1()) && getside2().isEqualseg(t.getside2()) && getside3().isEqualseg(t.getside3()))
                || (getside1().isEqualseg(t.getside2()) && getside2().isEqualseg(t.getside3()) && getside3().isEqualseg(t.getside1()))
                || (getside1().isEqualseg(t.getside3()) && getside2().isEqualseg(t.getside1()) && getside3().isEqualseg(t.getside2()))
                || (getside2().isEqualseg(t.getside1()) && getside3().isEqualseg(t.getside2()) && getside1().isEqualseg(t.getside3()))
                || (getside2().isEqualseg(t.getside2()) && getside3().isEqualseg(t.getside3()) && getside1().isEqualseg(t.getside1()))
                || (getside2().isEqualseg(t.getside3()) && getside3().isEqualseg(t.getside1()) && getside1().isEqualseg(t.getside2()))
                || (getside3().isEqualseg(t.getside1()) && getside1().isEqualseg(t.getside2()) && getside2().isEqualseg(t.getside3()))
                || (getside3().isEqualseg(t.getside2()) && getside1().isEqualseg(t.getside3()) && getside2().isEqualseg(t.getside1()))
                || (getside3().isEqualseg(t.getside3()) && getside1().isEqualseg(t.getside1()) && getside2().isEqualseg(t.getside2()));
    }

    double triangle::area(const point &p1, const point &p2, const point &p3) const {
        double x1 = p1.getX();
        double y1 = p1.getY();
        double x2 = p2.getX();
        double y2 = p2.getY();
        double x3 = p3.getX();
        double y3 = p3.getY();
        return 0.5 * abs(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));
    }

    void triangle::orderPoints(const point &p1, const point &p2, const point &p3) {
        double centerX = (p1.getX() + p2.getX() + p3.getX()) / 3.0;
        double centerY = (p1.getY() + p2.getY() + p3.getY()) / 3.0;
        vector<point> points = {p1, p2, p3};
        sort(begin(points), end(points), [centerX, centerY](const point &p1, const point &p2) {
            double angle1 = std::atan2(p1.getY() - centerY, p1.getX() - centerX);
            double angle2 = std::atan2(p2.getY() - centerY, p2.getX() - centerX);
            return angle1 < angle2;
        });
    }

    bool triangle::isPointInside(const point &p, const triangle &t) const {
        double x1 = t.getp1().getX();
        double y1 = t.getp1().getY();
        double x2 = t.getp2().getX();
        double y2 = t.getp2().getY();
        double x3 = t.getp3().getX();
        double y3 = t.getp3().getY();
        double xp = p.getX();
        double yp = p.getY();
        double det1 = ((xp - x1) * (y2 - y1)) - ((yp - y1) * (x2 - x1));
        double det2 = ((xp - x2) * (y3 - y2)) - ((yp - y2) * (x3 - x2));
        double det3 = ((xp - x3) * (y1 - y3)) - ((yp - y3) * (x1 - x3));
        // Verifica se i determinanti hanno lo stesso segno
        bool isInside = (det1 >= 0 && det2 >= 0 && det3 >= 0)
                || (det1 <= 0 && det2 <= 0 && det3 <= 0);
        return isInside;
    }

    bool triangle::isPointOnside(const point &p, const triangle &t) const {
        double x1 = t.getp1().getX();
        double y1 = t.getp1().getY();
        double x2 = t.getp2().getX();
        double y2 = t.getp2().getY();
        double x3 = t.getp3().getX();
        double y3 = t.getp3().getY();
        double xp = p.getX();
        double yp = p.getY();
        double det1 = ((xp - x1) * (y2 - y1)) - ((yp - y1) * (x2 - x1));
        double det2 = ((xp - x2) * (y3 - y2)) - ((yp - y2) * (x3 - x2));
        double det3 = ((xp - x3) * (y1 - y3)) - ((yp - y3) * (x1 - x3));
        bool isOnside = (det1 == 0 || det2 == 0 || det3 == 0);
        return isOnside;
    }

    vector<triangle> triangle::generateTriangles(const vector<point> &points) {
        vector<triangle> triangles;
        for (size_t i = 0; i < points.size() - 2; i++) {
            for (size_t j = i + 1; j < points.size() - 1; j++) {
                for (size_t k = j + 1; k < points.size(); k++) {
                    // Crea un triangolo con i tre punti
                    triangle t(points[i], points[j], points[k]);
                    triangles.push_back(t);
                }
            }
        }

        return triangles;
    }

    bool triangle::delaunay(const triangle &t1, const triangle &t2, const segment &seg) {//passo 2 triangoli e un segmento
        vector<segment> segments;
        vector<segment> segments2;

        // verifico quali sono i lati non adiacenti e li push nel segments
        if (!(t1.getside1().isEqualseg(seg))) {
            segments.push_back(t1.getside1());
        }
        if (!(t1.getside2().isEqualseg(seg))) {
            segments.push_back(t1.getside2());
        }
        if (!(t1.getside3().isEqualseg(seg))) {
            segments.push_back(t1.getside3());
        }

        // verifico quali sono i lati non adiacenti e li push nel segments2

        if (!(t2.getside1().isEqualseg(seg))) {
            segments2.push_back(t2.getside1());
        }
        if (!(t2.getside2().isEqualseg(seg))) {
            segments2.push_back(t2.getside2());
        }
        if (!(t2.getside3().isEqualseg(seg))) {
            segments2.push_back(t2.getside3());
        }

        double angle1 = segment::calculateangle(segments);// calcolo l'angolo 1
        double angle2 = segment::calculateangle(segments2);// calcolo l'angolo2
        return angle1 + angle2 <= 180;
    }

    bool triangle::commonsidebool(triangle &t1, triangle &t2) {
        vector<segment> segments;
        vector<segment> segments2;
        bool trovato=false;
        segments.push_back(t1.getside1());
        segments.push_back(t1.getside2());
        segments.push_back(t1.getside3());
        segments2.push_back(t2.getside1());
        segments2.push_back(t2.getside2());
        segments2.push_back(t2.getside3());
        for (unsigned int i = 0; i < 3; i++) {
            unsigned int j = 0;
            while (j < 3) {
                if (segments[i].isEqualseg(segments2[j])) {
                    trovato= true;
                    return trovato;
                }
                j++;
            }
        }
        return trovato;
    }

    segment triangle::commonside(triangle &t1, triangle &t2) {
        vector<segment> segments;
        vector<segment> segments2;
        segment trovato;
        segments.push_back(t1.getside1());
        segments.push_back(t1.getside2());
        segments.push_back(t1.getside3());
        segments2.push_back(t2.getside1());
        segments2.push_back(t2.getside2());
        segments2.push_back(t2.getside3());
        for (unsigned int i = 0; i < 3; i++) {
            unsigned int j = 0;
            while (j < 3) {
                if (segments[i].isEqualseg(segments2[j])) {
                    trovato = segments[i];
                    return trovato;
                }
                j++;
            }
        }
        return trovato;
    }

    vector<triangle> triangle::flip(segment &seg, const triangle &t1, const triangle &t2) {
        vector<triangle> triangles;
        vector<segment> segments = {t1.getside1(), t1.getside2(), t1.getside3()};
        vector<point> points = {t1.getp1(), t1.getp2(), t1.getp3()};//vettore punti del primo triangolo
        vector<point> points2 = {t2.getp1(), t2.getp2(), t2.getp3()};//vettore punti del secondo triangolo
        point notCommon1;
        point notCommon2;
        for (unsigned int i = 0; i < points.size(); i++) {
            if (!points[i].isEqual(seg.getstartpoint()) && !points[i].isEqual(seg.getendpoint())) {
                notCommon1 = points[i];
            }
        }

        for (unsigned int i = 0; i < points2.size(); i++) {
            if (!points2[i].isEqual(seg.getstartpoint()) && !points2[i].isEqual(seg.getendpoint())) {
                notCommon2 = points2[i];
            }
        }
        for (unsigned int i = 0; i < 3; i++) {
            if (segments[i].isEqualseg(seg)) {
                point p1 = segments[i].getstartpoint();
                point p2 = segments[i].getendpoint();

                triangle t1={notCommon1, notCommon2, p1};
                triangle t2={notCommon1, notCommon2, p2};
                triangles.push_back(t1);
                triangles.push_back(t2);
            }
        }
        return triangles;
    }
}
