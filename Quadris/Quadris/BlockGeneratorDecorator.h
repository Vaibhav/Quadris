#ifndef BLOCKGENERATOR_DECORATOR_H
#define BLOCKGENERATOR_DECORATOR_H

#include "BlockGenerator.h"
#include <memory>

class BlockGeneratorDecorator : public BlockGenerator {
public:
	BlockGeneratorDecorator(std::shared_ptr< BlockGenerator > component) : component{component} {}
private:
	std::shared_ptr< BlockGenerator > component;
};

#endif

/*
Class Pizza {
2 public :
3 virtual float price () const =0;
4 virtual string desc () const = 0;
5 virtual ~ pizza () ;
6 ) ;
7
8 Class CrustAndSauce : public Pizza {
9 public :
10 float price () const override { return 5.99;}
11 string desc () const override { return " Pizza " ;}
12 };
13
14 Class Decorator : public Pizza {
15 protected :
16 Pizza component ;
17 public :
18 Decorator ( PIzza * p) : Component {p }{}
19 virtual ~ Decorator () { delete component ;}
20 };
21
22 Class Topping : public Decorator {
23 string theTopping ;
24 public :
25 topping ( string t , pizza *p ) : Decorator { p } , theTopping {t }{}
26 float price () const override {
27 return component - > price () + .75;
28 }
29 string desc () const override {
30 return component - > desc () + " with " + theTopping ;
31 }
Lecture 9: November 10, 2016 9-4
32 };
33
34 int main () {
35 Pizza * p1 = new CrustandSauce ;
36 p1 = new Topping (" Cheese " , p1 ) ;
37 p1 = new Topping (" Cheese " , p1 ) ;
38
39 cout << p1 - > desc () << p1 - > price () ;
40
41 delete p1;
42 }



*/