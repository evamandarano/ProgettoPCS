#ifndef __TEST_EMPTY_H
#define __TEST_EMPTY_H

#include <gtest/gtest.h>
#include "empty_class.hpp"
#include<iostream>
using namespace testing;
using namespace ProjectLibrary;

TEST(TestEmpty, TestisEqual)
{
    point p ={1, 5, 3};
    bool c = p.isEqual({2, 6, 7});
    EXPECT_FALSE(c);
}

TEST(TestEmpty, TestisEqualseg)
{
    point p1= {2, 6, 4};
    point p2 = {3, 7, 9};
    point p3= {5, 8, 12};
    point p4= {4, 12, 16};
    segment s1 ={p1, p2};
    segment s2 ={p3, p4};
    bool c = s1.isEqualseg(s2);
    EXPECT_FALSE(c);
}

//test intersezione
TEST(TestEmpty, Testintersect)
{
    point p1= {2, 1, 1};
    point p2 = {3, 3, 3};
    point p3= {2, 1, 2};
    point p4= {4, 3, 2};
    segment seg1={p1, p2};
    segment seg2={p3, p4};
    bool c = segment::intersect(seg1,seg2);
    EXPECT_TRUE(c);
}

//test intersezione caso punto in comune
TEST(TestEmpty, Testintersect2)
{
    point p1= {2, 1, 1};
    point p2 = {3, 3, 3};
    point p3= {2, 1, 1};
    point p4= {4, 2, 1};
    segment seg1={p1, p2};
    segment seg2={p3, p4};
    bool c = segment::intersect(seg1,seg2);
    EXPECT_FALSE(c);
}

TEST(TestEmpty, Testcalculateangle)
{
    point p1= {2, 3, 3};
    point p2 = {3, 5, 3};
    point p3= {5, 3,8 };
    segment seg1={p1, p2};
    segment seg2={p1, p3};
    vector<segment> segments ={seg1, seg2};
    double deg = segment::calculateangle(segments);
    double aspettativa= 90;
    EXPECT_EQ(deg,aspettativa);
}

TEST(TestEmpty, TestfindConnectingSegments)
{
    point p1= {2, 1, 1};
    point p2 = {3, 3, 1};
    point p3= {5, 2, 3};
    point p4= {4, 4, 2};
    segment seg1 (p1,p2);
    segment seg2 (p2,p3);
    segment seg3 (p3,p1);
    segment seg4 (p2,p4);
    segment seg5 (p3,p4);
    vector<segment>segments ={seg1,seg2,seg3,seg4,seg5};
    vector<point> points={p1,p2,p3};
    vector<segment> vec={seg1,seg2,seg3};
    vector<segment> vec1= segment::findConnectingSegments(segments, points);
    bool f;
    for(unsigned int i=0; i<vec.size();i++){
        for(unsigned int j=0; j<vec1.size();j++){
            if(vec[i].isEqualseg(vec1[j])){
                f=true;
            }
        }

    }
    EXPECT_TRUE(f);
}


TEST(TestEmpty, TestisEqualtri)
{
    point p1= {2, 6, 4};
    point p2 = {3, 7, 9};
    point p3= {5, 8, 12};
    point p4= {4, 12, 16};
    triangle t1 ={p1, p2, p3};
    triangle t2 ={p3, p1, p2};
    bool c = t1.isEqualtri(t2);
    EXPECT_TRUE(c);
}

TEST(TestEmpty, Testarea)
{
    point p1= {2, 0, 2};
    point p2= {3, 0, 0};
    point p3= {5, 2, 0};
    triangle tri = {p1,p2,p3};
    double c = tri.area(p1, p2, p3);
    double t = 2;
    EXPECT_EQ(c,t);
}

TEST(TestEmpty, TestisPointInside)
{
    point p1= {1, 1, 1};
    point p2= {13, 3,1};
    point p3= {6, 1, 3};
    point p= {5, 1,2 };
    triangle t={p1,p2,p3};
    bool f;
    if(t.isPointInside(p, t)){
        f=true;
    }
    EXPECT_TRUE(f);
}

TEST(TestEmpty, TestisPointOnside)
{
    point p1= {1, 1, 1};
    point p2= {13, 3,1};
    point p3= {6, 1, 3};
    point p= {5, 1,2 };
    triangle t={p1,p2,p3};
    bool f;
    if(t.isPointOnside(p, t)){
        f=true;
    }
    EXPECT_TRUE(f);
}

TEST(TestEmpty, TestisPointInside2)
{
    point p1= {1, 1, 1};
    point p2= {13, 3,1};
    point p3= {6, 1, 3};
    point p= {5, 1.5,1.5 };
    triangle t={p1,p2,p3};
    bool f;
    if(t.isPointInside(p, t)){
        f=true;
    }
    EXPECT_TRUE(f);
}

TEST(TestEmpty, TestisPointOnside2)
{
    point p1= {1, 1, 1};
    point p2= {13, 3,1};
    point p3= {6, 1, 3};
    point p= {5, 1.5,1.5 };
    triangle t={p1,p2,p3};
    bool f=false;
    if(t.isPointOnside(p, t)){
        f=true;
    }
    EXPECT_FALSE(f);
}

TEST(TestEmpty, TestgenerateTriangles)
{
    point p1= {1, 2, 2};
    point p2= {13, 0, 0};
    point p3= {6, 7, 10};
    point p4= {23, 11, 8};
    triangle t1{p1,p2,p3};
    triangle t2{p1,p3,p4};
    triangle t3{p1,p2,p4};
    triangle t4{p2,p3,p4};
    vector<point> p= {p1,p2,p3,p4};
    vector<triangle> t = triangle::generateTriangles(p);
    vector<triangle> a={t1,t2,t3,t4};
    bool f;
    for(unsigned int i=0; i<a.size();i++){
        for(unsigned int j=0; j<t.size();j++){
            if(a[i].isEqualtri(t[j])){
                f=true;
            }
        }

    }
    EXPECT_TRUE(f);
}

TEST(TestEmpty, Testdelaunay)
{
    point p1= {2, 1, 1};
    point p2 = {3, 3, 1};
    point p3= {5, 1,3};
    point p4= {4, 3, 3};
    triangle t1= {p1,p2,p3};
    triangle t2={p4,p2,p3};
    segment seg= {p1,p2};
    bool c= triangle::delaunay(t1,t2,seg);
    EXPECT_TRUE(c);
}


TEST(TestEmpty, Testcommonside)
{
    point p1= {2, 1, 1};
    point p2 = {3, 3, 1};
    point p3= {5, 1,3};
    point p4= {4, 3, 3};
    triangle t1= {p1,p2,p3};
    triangle t2={p4,p2,p3};
    segment seg = triangle::commonside(t1,t2);
    segment asp ={p2,p3};
    bool c;
    if(seg.isEqualseg(asp)){
         c = true;}
    EXPECT_TRUE(c);
}

TEST(TestEmpty, Testcommonsidebool)
{
    point p1= {2, 1, 1};
    point p2 = {3, 3, 1};
    point p3= {5, 1,3};
    point p4= {4, 3, 3};
    triangle t1= {p1,p2,p3};
    triangle t2={p4,p2,p3};
    bool seg = triangle::commonsidebool(t1,t2);
    EXPECT_TRUE(seg);
}


TEST(TestEmpty, Testflip)
{
    point p1= {2, 2,1};
    point p2 = {3, 4,1};
    point p3= {4, 1,3 };
    point p4 = {5, 3,3};
    triangle t1= {p1,p2,p3};
    triangle t2={p2,p3,p4};
    triangle t3= {p2,p1,p4};
    triangle t4={p3,p4,p1};
    segment seg= triangle::commonside(t1,t2);
    vector<triangle> tri = triangle::flip(seg, t1, t2);
    triangle t_1=tri[0];
    triangle t_2=tri[1];

    bool c=false;
    if((t3.isEqualtri(t_1) && t4.isEqualtri(t_2)) ){
        c=true;
    }
    else if((t4.isEqualtri(t_1) && t3.isEqualtri(t_2))){
        c=true;
    }
    EXPECT_TRUE(c);
}


#endif // __TEST_EMPTY_H
