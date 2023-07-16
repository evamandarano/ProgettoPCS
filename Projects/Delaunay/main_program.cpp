#include "src/empty_class.hpp"
#include <cmath>
#include <algorithm>
#include <limits>
#include <set>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;
using namespace ProjectLibrary;


bool lies_in_segment(double x1, double y1, double x2, double y2, double px, double py){
    double crossproduct = ((py - y1) * (x2 - x1)) - ((px - x1) * (y2-y1));
    if(abs(crossproduct) > std::numeric_limits<double>::epsilon()){
        return false;
    }
    double dotproduct = ((px - x1) * (x2-x1)) + ((py - y1) * (y2 - y1));
    if(dotproduct < 0){
        return false;
    }

    double squaredlengthba = ((x2 - x1) * (x2 - x1)) + ((y2-y1)*(y2-y1));
    if(dotproduct > squaredlengthba){
        return false;
    }
    return true;
}

std::pair<vector<triangle>, vector<segment>> delunay_internal(triangle t, triangle tri_index, unsigned int index, unsigned int internaltriangle, point point_i, vector<triangle> triangles, vector<segment> segments){
    segment adj= triangle::commonside(t, tri_index);
    if(!(triangle::delaunay(t, tri_index, adj))){//maggiore 180 devo fare il flip
        vector<triangle> tri= triangle::flip(adj, t, tri_index);

        triangles.erase(triangles.begin()+index);
        segment seg = triangle::commonside(tri[0], tri[1]);
        segments.push_back(seg);
        for(unsigned int f=0; f<segments.size(); f++){
            if(adj.isEqualseg(segments[f])){
                segments.erase(segments.begin()+f);
            }
        }
        cout << " Triangolo 1.1:" << endl;
        cout << "Punto 1: (" << tri[0].getp1().getX() << ", " << tri[0].getp1().getY() << ")" << endl;
        cout << "Punto 2: (" << tri[0].getp2().getX() << ", " << tri[0].getp2().getY() << ")" << endl;
        cout << "Punto 3: (" << tri[0].getp3().getX() << ", " << tri[0].getp3().getY() << ")" << endl;
        cout << " Triangolo 1.2:" << endl;
        cout << "Punto 1: (" << tri[1].getp1().getX() << ", " << tri[1].getp1().getY() << ")" << endl;
        cout << "Punto 2: (" << tri[1].getp2().getX() << ", " << tri[1].getp2().getY() << ")" << endl;
        cout << "Punto 3: (" << tri[1].getp3().getX() << ", " << tri[1].getp3().getY() << ")" << endl;


        unsigned int p;
        bool adiacenti =false;
        p=0;
        while (p < triangles.size()){ //verifico se il triangolo è adiacente rispetto a tutti i triangoli del vettore triangoli
            if(!(triangle::commonsidebool(tri[0],triangles[p])) || (triangles[p].isEqualtri(tri[1]))){
                p++;
            }else{

                adiacenti= true; //se è adiacente a un triangolo mi salvo l'indice di quale triangolo è adiacente, metto la condizione per vedere appunto che è adiacente e esco dal while
                index= p;
                break;
            }
        }
        if(adiacenti){
           segment seg_adj = triangle::commonside(tri[0], triangles[index]);
           if(!(triangle::delaunay(tri[0], triangles[index], seg_adj))){
               vector<triangle> tri_v2= triangle::flip(seg_adj, tri[0], triangles[index]);
               triangles.push_back(tri_v2[0]);
               triangles.push_back(tri_v2[1]);
               triangles.erase(triangles.begin()+index);
               segment seg = triangle::commonside(tri_v2[0], tri_v2[1]);
               segments.push_back(seg);
               for(unsigned int f=0; f<segments.size(); f++){
                   if(adj.isEqualseg(segments[f])){
                       segments.erase(segments.begin()+f);
                   }
               }
               cout << " Triangolo 1.1:" << endl;
               cout << "Punto 1: (" << tri_v2[0].getp1().getX() << ", " << tri_v2[0].getp1().getY() << ")" << endl;
               cout << "Punto 2: (" << tri_v2[0].getp2().getX() << ", " << tri_v2[0].getp2().getY() << ")" << endl;
               cout << "Punto 3: (" << tri_v2[0].getp3().getX() << ", " << tri_v2[0].getp3().getY() << ")" << endl;
               cout << " Triangolo 1.2:" << endl;
               cout << "Punto 1: (" << tri_v2[1].getp1().getX() << ", " << tri_v2[1].getp1().getY() << ")" << endl;
               cout << "Punto 2: (" << tri_v2[1].getp2().getX() << ", " << tri_v2[1].getp2().getY() << ")" << endl;
               cout << "Punto 3: (" << tri_v2[1].getp3().getX() << ", " << tri_v2[1].getp3().getY() << ")" << endl;
           }
           else{
               triangles.push_back(tri[0]);
           }
        }else{
            triangles.push_back(tri[0]);
        }


        adiacenti = false;
        p=0;
        while (p < triangles.size()){ //verifico se il triangolo è adiacente rispetto a tutti i triangoli del vettore triangoli
            if(!(triangle::commonsidebool(tri[1],triangles[p])) || (triangles[p].isEqualtri(tri[0]))){
                p++;
            }else{

                adiacenti= true; //se è adiacente a un triangolo mi salvo l'indice di quale triangolo è adiacente, metto la condizione per vedere appunto che è adiacente e esco dal while
                index= p;
                break;
            }
        }
        if(adiacenti){
           segment seg_adj = triangle::commonside(tri[1], triangles[index]);
           if(!(triangle::delaunay(tri[1], triangles[index], seg_adj))){
               vector<triangle> tri_v2= triangle::flip(seg_adj, tri[1], triangles[index]);
               triangles.push_back(tri_v2[0]);
               triangles.push_back(tri_v2[1]);
               triangles.erase(triangles.begin()+index);
               segment seg = triangle::commonside(tri_v2[0], tri_v2[1]);
               segments.push_back(seg);
               for(unsigned int f=0; f<segments.size(); f++){
                   if(adj.isEqualseg(segments[f])){
                       segments.erase(segments.begin()+f);
                   }
               }
               cout << " Triangolo 1.1:" << endl;
               cout << "Punto 1: (" << tri_v2[0].getp1().getX() << ", " << tri_v2[0].getp1().getY() << ")" << endl;
               cout << "Punto 2: (" << tri_v2[0].getp2().getX() << ", " << tri_v2[0].getp2().getY() << ")" << endl;
               cout << "Punto 3: (" << tri_v2[0].getp3().getX() << ", " << tri_v2[0].getp3().getY() << ")" << endl;
               cout << " Triangolo 1.2:" << endl;
               cout << "Punto 1: (" << tri_v2[1].getp1().getX() << ", " << tri_v2[1].getp1().getY() << ")" << endl;
               cout << "Punto 2: (" << tri_v2[1].getp2().getX() << ", " << tri_v2[1].getp2().getY() << ")" << endl;
               cout << "Punto 3: (" << tri_v2[1].getp3().getX() << ", " << tri_v2[1].getp3().getY() << ")" << endl;
           }
           else{
               triangles.push_back(tri[1]);
           }
        }else{
            triangles.push_back(tri[1]);
        }
    }
    else{//minore
        triangles.push_back(t);
        segment seg1= {point_i, triangles[internaltriangle].getp1()} ;
        segments.push_back(seg1); //aggiungo i segmenti al vettore segmenti
        cout << " Triangolo 1:" << endl;
        cout << "Punto 1: (" << t.getp1().getX() << ", " << t.getp1().getY() << ")" << endl;
        cout << "Punto 2: (" << t.getp2().getX() << ", " << t.getp2().getY() << ")" << endl;
        cout << "Punto 3: (" << t.getp3().getX() << ", " << t.getp3().getY() << ")" << endl;
    }
    return std::make_pair(triangles, segments);
}

std::pair<vector<triangle>, vector<segment>> delunay_esternal(triangle t, triangle tri_index, unsigned int index, vector<triangle> triangles, vector<segment> segments){
    segment adj= triangle::commonside(t, tri_index);
    if(!(triangle::delaunay(t, tri_index, adj))){//maggiore 180 devo fare il flip
        vector<triangle> tri= triangle::flip(adj, t, tri_index);
        unsigned int f = 0;
        bool uguale=false;
        while( f<triangles.size()){
            if(!(tri[0].isEqualtri(triangles[f]))){
                f++;
            }
            else{uguale=true;
                break;
            }
        }
        if(uguale==false){
            triangles.push_back(tri[0]);
        }
        unsigned int f1 = 0;
        bool uguale1=false;
        while(f1<triangles.size()){
            if(!(tri[1].isEqualtri(triangles[f1]))){
                f1++;
            }
            else{
                uguale1=true;
                break;
            }
        }
        if(uguale1==false){
            triangles.push_back(tri[1]);
        }
        triangles.erase(triangles.begin()+index);
        segment seg = triangle::commonside(tri[0], tri[1]);
        segments.push_back(seg);
        for(unsigned int f=0; f<segments.size(); f++){
            if(adj.isEqualseg(segments[f])){
                segments.erase(segments.begin()+f);
            }
        }
        cout << " Triangolo 1.1:" << endl;
        cout << "Punto 1: (" << tri[0].getp1().getX() << ", " << tri[0].getp1().getY() << ")" << endl;
        cout << "Punto 2: (" << tri[0].getp2().getX() << ", " << tri[0].getp2().getY() << ")" << endl;
        cout << "Punto 3: (" << tri[0].getp3().getX() << ", " << tri[0].getp3().getY() << ")" << endl;
        cout << " Triangolo 1.2:" << endl;
        cout << "Punto 1: (" << tri[1].getp1().getX() << ", " << tri[1].getp1().getY() << ")" << endl;
        cout << "Punto 2: (" << tri[1].getp2().getX() << ", " << tri[1].getp2().getY() << ")" << endl;
        cout << "Punto 3: (" << tri[1].getp3().getX() << ", " << tri[1].getp3().getY() << ")" << endl;
    }
    else{//minore
        triangles.push_back(t);
        cout << " Triangolo 1:" << endl;
        cout << "Punto 1: (" << t.getp1().getX() << ", " << t.getp1().getY() << ")" << endl;
        cout << "Punto 2: (" << t.getp2().getX() << ", " << t.getp2().getY() << ")" << endl;
        cout << "Punto 3: (" << t.getp3().getX() << ", " << t.getp3().getY() << ")" << endl;
    }

    return std::make_pair(triangles, segments);

}

int main() {
    vector<point> points = point::importFromFile("C:/Users/manda/Desktop/Progetto/Projects/Delaunay/Dataset/Test2.csv");
    for (const auto &point: points) {
        cout << "coordinate del punto:" << point.getId() << ", " << point.getX() << ", " << point.getY() << endl;
    }
    triangle t;

    vector<triangle> trianglesarea = triangle::generateTriangles(points);
    for (auto &t: trianglesarea) {
        t.orderPoints(t.getp1(), t.getp2(), t.getp3());
    }

    double maxArea = 0.0;
    triangle maxAreaTriangle;
    for (const auto &t: trianglesarea) {
        double area = t.area(t.getp1(), t.getp2(), t.getp3());
        if (area > maxArea) {
            maxArea = area;
            maxAreaTriangle = t;
        }
    }
    vector<triangle> triangles; //vettore dei triangoli della triangolazione
    vector<segment> segments; //vettore dei segmenti della triangolazione
    vector<point> pointact; //vettore dei punti della triangolazione
    cout << "il triangolo con area massima ha le seguenti coordinate:" << endl;
    cout << "Punto 1: (" << maxAreaTriangle.getp1().getX() << ", " << maxAreaTriangle.getp1().getY() << ")" << endl;
    cout << "Punto 2: (" << maxAreaTriangle.getp2().getX() << ", " << maxAreaTriangle.getp2().getY() << ")" << endl;
    cout << "Punto 3: (" << maxAreaTriangle.getp3().getX() << ", " << maxAreaTriangle.getp3().getY() << ")" << endl;
    triangles.push_back(maxAreaTriangle); // aggiungo al vettore triangoli il triangolo di area massima
    segments.push_back(maxAreaTriangle.getside1());
    segments.push_back(maxAreaTriangle.getside2());
    segments.push_back(maxAreaTriangle.getside3()); //aggiungo i segmenti del triangolo di area massima
    pointact.push_back(maxAreaTriangle.getp1());
    pointact.push_back(maxAreaTriangle.getp2());
    pointact.push_back(maxAreaTriangle.getp3()); // aggiungo i punti del triangolo di area massima

    bool locIsInternal;
    bool locIsOnside;
    bool adiacenti;
    unsigned int index;
    unsigned int internaltriangle;
    unsigned int onsidetri;
    for(unsigned int i=0; i< points.size() ; i++) { //per ogni punto i del vettore di punti caricato da file
        if ((points[i].getId() != maxAreaTriangle.getp1().getId()) &&
            (points[i].getId() != maxAreaTriangle.getp2().getId()) &&
            (points[i].getId() != maxAreaTriangle.getp3().getId())){
            // Se il punto non è un vertice del triangolo iniziale

            unsigned int j;
            locIsInternal=false;
            locIsOnside=false;
            j=0;
            while (j<triangles.size()){ //verifico se il punto è esterno a tutti i triangoli del vettore triangoli
                if(!(triangles[j].isPointInside(points[i], triangles[j]))){
                    j++;
                }else
                {
                    if(triangles[j].isPointOnside(points[i], triangles[j])){
                        locIsOnside=true;
                        onsidetri=j;
                        break;
                    }
                    else{
                        locIsInternal= true; //se è interno a un triangolo mi salvo l'indice di quale triangolo è interno, metto la condizione per vedere appunto che è interno e esco dal while
                        internaltriangle= j;
                        break;
                    }
                }
            }

            cout << "Numero Triangoli al giro " << i << " : " << triangles.size() << endl;

            //PUNTO SU LATO
            if(locIsOnside==true){//il punto è su un lato
                cout<<"il punto " << points[i].getX() << "," << points[i].getY() << " e sul lato "<< endl;
                j=0;
                unsigned int indexadj=0;
                bool ad=false;
                if (points[i].isEqual(triangles[onsidetri].getp1()) || points[i].isEqual(triangles[onsidetri].getp2()) ||points[i].isEqual(triangles[onsidetri].getp3())){
                    cout << " il punto è gia un vertice" << endl;
                }
                else{
                    segment seg1(triangles[onsidetri].getside1());//lato 1 del triangolo
                    segment seg2(triangles[onsidetri].getside2());//lato 2 del triangolo
                    segment seg3(triangles[onsidetri].getside3());//lato 3 del triangolo
                    segment seg;
                    bool is_seg1 = lies_in_segment(seg1.getstartpoint().getX(),seg1.getstartpoint().getY(),
                                    seg1.getendpoint().getX(),seg1.getendpoint().getY(),
                                    points[i].getX(), points[i].getY());
                    bool is_seg2 = lies_in_segment(seg2.getstartpoint().getX(),seg2.getstartpoint().getY(),
                                    seg2.getendpoint().getX(),seg2.getendpoint().getY(),
                                    points[i].getX(), points[i].getY());
                    bool is_seg3 =lies_in_segment(seg3.getstartpoint().getX(),seg3.getstartpoint().getY(),
                                    seg3.getendpoint().getX(),seg3.getendpoint().getY(),
                                    points[i].getX(), points[i].getY());
                    if(is_seg1){
                        seg=seg1;
                    } else if(is_seg2){
                        seg=seg2;
                    } else if(is_seg3){
                        seg=seg3;
                    }
                    while(j<triangles.size()){
                        segment adj= triangle::commonside(triangles[onsidetri],triangles[j]);
                        if(seg.isEqualseg(adj)){
                            indexadj=j;
                            ad=true;
                            break;
                        }
                        else{
                            j++;
                        }
                    }
                    if(ad){//se ad è vero allora siamo nel caso tra due triangoli
                        segment adj=triangle::commonside(triangles[onsidetri],triangles[indexadj]);
                        point p;
                        point q;
                        if(adj.isEqualseg(triangles[onsidetri].getside1())){
                            p=triangles[onsidetri].getp3();
                        } else if(adj.isEqualseg(triangles[onsidetri].getside2())){
                            p=triangles[onsidetri].getp1();
                        } else if(adj.isEqualseg(triangles[onsidetri].getside3())){
                            p=triangles[onsidetri].getp2();
                        }
                        if(adj.isEqualseg(triangles[indexadj].getside1())){
                            q=triangles[indexadj].getp3();
                        } else if(adj.isEqualseg(triangles[indexadj].getside2())){
                            q=triangles[indexadj].getp1();
                        } else if(adj.isEqualseg(triangles[indexadj].getside3())){
                            q=triangles[indexadj].getp2();
                        }
                        triangle t1(points[i], adj.getstartpoint(), p);
                        triangle t2(points[i], adj.getendpoint(), p);
                        triangle t3(points[i], adj.getstartpoint(), q);
                        triangle t4(points[i], adj.getendpoint(), q);
                        vector<triangle> tri={t1,t2,t3,t4};
                        triangles.erase(triangles.begin() + indexadj);
                        triangles.erase(triangles.begin() + onsidetri);
                        for(unsigned int g=0; g<tri.size(); g++){
                            unsigned int u;
                            adiacenti =false;
                            u=0;
                            while (u < triangles.size()){ //verifico se il triangolo è adiacente rispetto a tutti i triangoli del vettore triangoli
                                if(!(triangle::commonsidebool(tri[g],triangles[u]))){
                                    u++;
                                }else
                                {
                                    adiacenti= true; //se è adiacente a un triangolo mi salvo l'indice di quale triangolo è adiacente, metto la condizione per vedere appunto che è adiacente e esco dal while
                                    index= u;
                                    break;
                                }
                            }
                            if(adiacenti==true){
                                segment adj= triangle::commonside(tri[g], triangles[index]);
                                if(!(triangle::delaunay(tri[g], triangles[index], adj))){//maggiore 180 devo fare il flip
                                    cout<<"non vale delaunay tra t e il triangolo "<<u <<endl;
                                    vector<triangle> newtri= triangle::flip(adj, tri[g], triangles[index]);
                                    triangles.push_back(newtri[0]);
                                    triangles.push_back(newtri[1]);
                                    triangles.erase(triangles.begin()+index);
                                    segment seg = triangle::commonside(newtri[0], newtri[1]);
                                    segments.push_back(seg);
                                    for(unsigned int f=0; f<segments.size(); f++){
                                        if(adj.isEqualseg(segments[f])){
                                            segments.erase(segments.begin()+f);
                                        }
                                    }
                                    cout << " Triangolo 1.1:" << endl;
                                    cout << "Punto 1: (" << newtri[0].getp1().getX() << ", " << newtri[0].getp1().getY() << ")" << endl;
                                    cout << "Punto 2: (" << newtri[0].getp2().getX() << ", " << newtri[0].getp2().getY() << ")" << endl;
                                    cout << "Punto 3: (" << newtri[0].getp3().getX() << ", " << newtri[0].getp3().getY() << ")" << endl;
                                    cout << " Triangolo 1.2:" << endl;
                                    cout << "Punto 1: (" << newtri[1].getp1().getX() << ", " << newtri[1].getp1().getY() << ")" << endl;
                                    cout << "Punto 2: (" << newtri[1].getp2().getX() << ", " << newtri[1].getp2().getY() << ")" << endl;
                                    cout << "Punto 3: (" << newtri[1].getp3().getX() << ", " << newtri[1].getp3().getY() << ")" << endl;
                                }
                                else{//minore
                                    cout<<" vale delaunay tra t e il triangolo "<<u <<endl;
                                    triangles.push_back(tri[g]);
                                    segment seg1= {points[i], triangles[onsidetri].getp1()} ;
                                    segment seg2= {points[i], triangles[onsidetri].getp2()} ;
                                    segment seg3= {points[i], triangles[onsidetri].getp3()} ;
                                    segments.push_back(seg1); //aggiungo i segmenti al vettore segmenti
                                    segments.push_back(seg2); //aggiungo i segmenti al vettore segmenti
                                    segments.push_back(seg3); //aggiungo i segmenti al vettore segmenti

                                    cout << " Triangolo 1:" << endl;
                                    cout << "Punto 1: (" << tri[g].getp1().getX() << ", " << tri[g].getp1().getY() << ")" << endl;
                                    cout << "Punto 2: (" << tri[g].getp2().getX() << ", " << tri[g].getp2().getY() << ")" << endl;
                                    cout << "Punto 3: (" << tri[g].getp3().getX() << ", " << tri[g].getp3().getY() << ")" << endl;
                                }
                            }
                            else{//non adiacenti
                                cout<<"non adiacenti t e il triangolo "<<u <<endl;
                                triangles.push_back(tri[g]);
                                segment seg1= {points[i], triangles[onsidetri].getp1()} ;
                                segment seg2= {points[i], triangles[onsidetri].getp2()} ;
                                segment seg3= {points[i], triangles[onsidetri].getp3()} ;
                                segments.push_back(seg1); //aggiungo i segmenti al vettore segmenti
                                segments.push_back(seg2); //aggiungo i segmenti al vettore segmenti
                                segments.push_back(seg3); //aggiungo i segmenti al vettore segmenti
                                cout << " Triangolo 1:" << endl;
                                cout << "Punto 1: (" << tri[g].getp1().getX() << ", " << tri[g].getp1().getY() << ")" << endl;
                                cout << "Punto 2: (" << tri[g].getp2().getX() << ", " << tri[g].getp2().getY() << ")" << endl;
                                cout << "Punto 3: (" << tri[g].getp3().getX() << ", " << tri[g].getp3().getY() << ")" << endl;
                            }
                        }

                    }
                    else{// ad è falsa e allora il segmento su cui giace il punto è esterno
                        point p;
                        if(seg.isEqualseg(triangles[onsidetri].getside1())){
                            p=triangles[onsidetri].getp3();
                        } else if(seg.isEqualseg(triangles[onsidetri].getside2())){
                            p=triangles[onsidetri].getp1();
                        } else if(seg.isEqualseg(triangles[onsidetri].getside3())){
                            p=triangles[onsidetri].getp2();
                        }
                        triangle t1(points[i], seg.getstartpoint(), p);
                        triangle t2(points[i], seg.getendpoint(), p);
                        vector<triangle> tri={t1,t2};
                        triangles.erase(triangles.begin() + onsidetri);
                        for(unsigned int g=0; g<tri.size(); g++){
                            unsigned int u;
                            adiacenti =false;
                            u=0;
                            while (u < triangles.size()){ //verifico se il triangolo è adiacente rispetto a tutti i triangoli del vettore triangoli
                                if(!(triangle::commonsidebool(tri[g],triangles[u]))){
                                    u++;
                                }else
                                {
                                    adiacenti= true; //se è adiacente a un triangolo mi salvo l'indice di quale triangolo è adiacente, metto la condizione per vedere appunto che è adiacente e esco dal while
                                    index= u;
                                    break;
                                }
                            }
                            if(adiacenti==true){
                                segment adj= triangle::commonside(tri[g], triangles[index]);
                                if(!(triangle::delaunay(tri[g], triangles[index], adj))){//maggiore 180 devo fare il flip
                                    cout<<"non vale delaunay tra t e il triangolo "<<u <<endl;
                                    vector<triangle> newtri= triangle::flip(adj, tri[g], triangles[index]);
                                    triangles.push_back(newtri[0]);
                                    triangles.push_back(newtri[1]);
                                    triangles.erase(triangles.begin()+index);
                                    segment seg = triangle::commonside(newtri[0], newtri[1]);
                                    segments.push_back(seg);
                                    for(unsigned int f=0; f<segments.size(); f++){
                                        if(adj.isEqualseg(segments[f])){
                                            segments.erase(segments.begin()+f);
                                        }
                                    }
                                    cout << " Triangolo 1.1:" << endl;
                                    cout << "Punto 1: (" << newtri[0].getp1().getX() << ", " << newtri[0].getp1().getY() << ")" << endl;
                                    cout << "Punto 2: (" << newtri[0].getp2().getX() << ", " << newtri[0].getp2().getY() << ")" << endl;
                                    cout << "Punto 3: (" << newtri[0].getp3().getX() << ", " << newtri[0].getp3().getY() << ")" << endl;
                                    cout << " Triangolo 1.2:" << endl;
                                    cout << "Punto 1: (" << newtri[1].getp1().getX() << ", " << newtri[1].getp1().getY() << ")" << endl;
                                    cout << "Punto 2: (" << newtri[1].getp2().getX() << ", " << newtri[1].getp2().getY() << ")" << endl;
                                    cout << "Punto 3: (" << newtri[1].getp3().getX() << ", " << newtri[1].getp3().getY() << ")" << endl;
                                }
                                else{//minore
                                    cout<<" vale delaunay tra t e il triangolo "<<u <<endl;
                                    triangles.push_back(tri[g]);
                                    segment seg1= {points[i], triangles[onsidetri].getp1()} ;
                                    segment seg2= {points[i], triangles[onsidetri].getp2()} ;
                                    segment seg3= {points[i], triangles[onsidetri].getp3()} ;
                                    segments.push_back(seg1); //aggiungo i segmenti al vettore segmenti
                                    segments.push_back(seg2); //aggiungo i segmenti al vettore segmenti
                                    segments.push_back(seg3); //aggiungo i segmenti al vettore segmenti

                                    cout << " Triangolo 1:" << endl;
                                    cout << "Punto 1: (" << tri[g].getp1().getX() << ", " << tri[g].getp1().getY() << ")" << endl;
                                    cout << "Punto 2: (" << tri[g].getp2().getX() << ", " << tri[g].getp2().getY() << ")" << endl;
                                    cout << "Punto 3: (" << tri[g].getp3().getX() << ", " << tri[g].getp3().getY() << ")" << endl;
                                }
                            }
                            else{//non adiacenti
                                cout<<"non adiacenti t e il triangolo "<<u <<endl;
                                triangles.push_back(tri[g]);
                                segment seg1= {points[i], triangles[onsidetri].getp1()} ;
                                segment seg2= {points[i], triangles[onsidetri].getp2()} ;
                                segment seg3= {points[i], triangles[onsidetri].getp3()} ;
                                segments.push_back(seg1); //aggiungo i segmenti al vettore segmenti
                                segments.push_back(seg2); //aggiungo i segmenti al vettore segmenti
                                segments.push_back(seg3); //aggiungo i segmenti al vettore segmenti
                                cout << " Triangolo 1:" << endl;
                                cout << "Punto 1: (" << tri[g].getp1().getX() << ", " << tri[g].getp1().getY() << ")" << endl;
                                cout << "Punto 2: (" << tri[g].getp2().getX() << ", " << tri[g].getp2().getY() << ")" << endl;
                                cout << "Punto 3: (" << tri[g].getp3().getX() << ", " << tri[g].getp3().getY() << ")" << endl;
                            }
                        }
                    }
                }
            }


            //PUNTO INTERNO
            else if(locIsInternal==true){//il punto è interno
                if (points[i].isEqual(triangles[internaltriangle].getp1()) || points[i].isEqual(triangles[internaltriangle].getp2()) ||points[i].isEqual(triangles[internaltriangle].getp3())){
                    cout << " il punto è gia un vertice" << endl;
                } else{
                    cout<<"il punto " << points[i].getX() << "," << points[i].getY() << " e interno al triangolo "<< internaltriangle << endl;
                    triangle t1(triangles[internaltriangle].getp1(), triangles[internaltriangle].getp2(), points[i]);
                    triangle t2(triangles[internaltriangle].getp2(), triangles[internaltriangle].getp3(), points[i]);
                    triangle t3(triangles[internaltriangle].getp3(), triangles[internaltriangle].getp1(), points[i]);
                    vector<triangle> vectri= {t1,t2,t3};

                    triangles.erase(triangles.begin() + internaltriangle);

                    cout << "Aggiunta nuovi triangoli con le coordinate:" << endl;

                    for(unsigned int g=0; g<vectri.size(); g++){
                        unsigned int p;
                        adiacenti =false;
                        p=0;
                        while (p < triangles.size()){ //verifico se il triangolo è adiacente rispetto a tutti i triangoli del vettore triangoli
                            if(!(triangle::commonsidebool(vectri[g],triangles[p]))){
                                p++;
                            }else
                            {
                                adiacenti= true; //se è adiacente a un triangolo mi salvo l'indice di quale triangolo è adiacente, metto la condizione per vedere appunto che è adiacente e esco dal while
                                index= p;
                                break;
                            }
                        }
                        if(adiacenti==true){
                            // Delaunay
                            pair<vector<triangle>, vector<segment>> result = delunay_internal(vectri[g], triangles[index], index, internaltriangle, points[i], triangles, segments);
                            triangles = result.first;
                            segments = result.second;

                        }
                        else{//non adiacenti
                            cout<<"non adiacenti t e il triangolo "<<p <<endl;
                            triangles.push_back(vectri[g]);
                            segment seg1= {points[i], triangles[internaltriangle].getp1()} ;
                            segments.push_back(seg1); //aggiungo i segmenti al vettore segmenti
                            cout << " Triangolo 1:" << endl;
                            cout << "Punto 1: (" << vectri[g].getp1().getX() << ", " << vectri[g].getp1().getY() << ")" << endl;
                            cout << "Punto 2: (" << vectri[g].getp2().getX() << ", " << vectri[g].getp2().getY() << ")" << endl;
                            cout << "Punto 3: (" << vectri[g].getp3().getX() << ", " << vectri[g].getp3().getY() << ")" << endl;
                        }
                    }
                }
            }


            //PUNTO ESTERNO
            else{ //il punto è esterno (locIsinternal è rimasta false)
                cout<<"il punto " << points[i].getX() << "," << points[i].getY() << " \'e esterno alla triangolazione "<< endl;
                vector<segment> locseg; //vettore locale di segmenti
                for(unsigned int k=0; k < pointact.size();k++){ //per ogni k punto della triangolazione
                    if(!points[i].isEqual(pointact[k])){ //controlla se il punto i è uguale a quelli salvati
                        bool inter = false;
                        for (unsigned int q = 0; q < segments.size();q++) { //per ogni j segmenti dei triangolazione
                            if(segment::intersect(segment(pointact[k], points[i]), segments[q])){
                                inter = true;
                            }
                        }
                        if(!inter){
                            locseg.push_back(segment(points[i], pointact[k]));//se il segmento non ha intersezione lo aggiungo ai segmenti locali
                        }
                    }
                }
                vector<point> locpoint; // creo un vettore locale di punti
                for(unsigned int j=0; j<locseg.size();j++){
                    if(points[i].isEqual(locseg[j].getstartpoint())){
                        locpoint.push_back(locseg[j].getendpoint());
                    }
                    else{
                        locpoint.push_back(locseg[j].getstartpoint());
                    }
                }
                vector<segment> connectseg; //vettore locale di segmenti
                connectseg = ProjectLibrary::segment::findConnectingSegments(segments, locpoint); //gli do tutti i segmenti della triangolazione, il vettore locale di punti e lui mi restituisce i vettori che mi servono
                for(unsigned int k=0; k<connectseg.size(); k++){
                    triangle tmp(points[i],connectseg[k].getstartpoint(), connectseg[k].getendpoint());
                    bool check_internal = false;
                    for(unsigned int s=0; s < pointact.size(); s++){
                        if((pointact[s].getId()!=connectseg[k].getstartpoint().getId()) &&
                            (pointact[s].getId()!=connectseg[k].getendpoint().getId()) &&
                            (pointact[s].getId()!=points[i].getId())){
                            if (tmp.isPointInside(pointact[s], tmp)){
                                check_internal = true;
                                break;
                            }
                        }
                    }
                    if(!check_internal){
                        triangle t = {points[i],connectseg[k].getstartpoint(), connectseg[k].getendpoint()};
                        unsigned int p;
                        adiacenti =false;
                        p=0;
                        while (p < triangles.size()){ //verifico se il triangolo è adiacente rispetto a tutti i triangoli del vettore triangoli
                            if(!(triangle::commonsidebool(t,triangles[p]))){
                                p++;
                            }else
                            {
                                adiacenti= true; //se è adiacente a un triangolo mi salvo l'indice di quale triangolo è adiacente, metto la condizione per vedere appunto che è adiacente e esco dal while
                                index= p;
                                break;
                            }
                        }

                        if(adiacenti==true){
                            // Delunay
                            pair<vector<triangle>, vector<segment>> result = delunay_esternal(t, triangles[index], index, triangles, segments);
                            triangles = result.first;
                            segments = result.second;
                        }
                        else{//non adiacenti
                            cout<<"non adiacenti t e il triangolo "<<p <<endl;
                            triangles.push_back(t);
                            cout << " Triangolo 1:" << endl;
                            cout << "Punto 1: (" << t.getp1().getX() << ", " << t.getp1().getY() << ")" << endl;
                            cout << "Punto 2: (" << t.getp2().getX() << ", " << t.getp2().getY() << ")" << endl;
                            cout << "Punto 3: (" << t.getp3().getX() << ", " << t.getp3().getY() << ")" << endl;
                        }
                    }
                }
                for(unsigned int k=0; k<locseg.size(); k++){/*aggiungo i segmenti che ho appena creato*/
                    segments.push_back(locseg[k]);
                }
                locpoint.clear();
                connectseg.clear();
                locseg.clear(); //a ogni nuova iterazione si puliscono
            }

        pointact.push_back(points[i]); /*aggiungo il nuovo punto all'elenco di punti*/
        cout << " Fine" << endl;
        }


        ofstream outputFile("C:/Users/manda/Desktop/Progetto/Projects/Delaunay/Outputs/output_" +  std::to_string(i) + ".txt");
        if (!outputFile) {
            cerr << "Impossibile aprire il file per la scrittura." << endl;
            return 1;
        }

        for (unsigned int i = 0; i < triangles.size(); i++) {
            const triangle &t = triangles[i];

            // Scrivi le coordinate dei punti del triangolo nel file
            outputFile << "Triangolo " << i + 1 << ":" << endl;
            outputFile << "Punto 1: (" << t.getp1().getX() << ", " << t.getp1().getY() << ")" << endl;
            outputFile << "Punto 2: (" << t.getp2().getX() << ", " << t.getp2().getY() << ")" << endl;
            outputFile << "Punto 3: (" << t.getp3().getX() << ", " << t.getp3().getY() << ")" << endl;
            outputFile << endl;
        }

        // Chiudi il file dopo aver scritto i dati
        outputFile.close();

    }

    ofstream outputFile("C:/Users/manda/Desktop/Progetto/Projects/Delaunay/output.txt");
    if (!outputFile) {
        cerr << "Impossibile aprire il file per la scrittura." << endl;
        return 1;
    }

    for (unsigned int i = 0; i < triangles.size(); i++) {
        const triangle &t = triangles[i];

        // Scrivi le coordinate dei punti del triangolo nel file
        outputFile << "Triangolo " << i + 1 << ":" << endl;
        outputFile << "Punto 1: (" << t.getp1().getX() << ", " << t.getp1().getY() << ")" << endl;
        outputFile << "Punto 2: (" << t.getp2().getX() << ", " << t.getp2().getY() << ")" << endl;
        outputFile << "Punto 3: (" << t.getp3().getX() << ", " << t.getp3().getY() << ")" << endl;
        outputFile << endl;
    }

    // Chiudi il file dopo aver scritto i dati
    outputFile.close();

    return 0;
}


