//
// Created by Alperen on 11/15/2017.
//
#ifndef PROJECT2_ORDERS_H
#define PROJECT2_ORDERS_H


#include <iostream>
#include <string>

class Orders{
public:
    double arrTime;
    double ordTime;
    double brewTime;
    double price;
    double ordTaken;
    int order2index;
    double ordEnd;
    double brewTaken;
    double brewEnd;
    double turnAround;
    int orderId;
    bool brewed;

    Orders();
    Orders(double _arrTime, double _ordTime,double _brewTime, double _price);
    ~Orders();

};

#endif //PROJECT2_ORDERS_H
