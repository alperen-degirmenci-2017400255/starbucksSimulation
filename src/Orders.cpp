//
// Created by Alperen on 11/15/2017.
//
#include "Orders.h"

Orders::Orders(){

}

Orders::Orders(double _arrTime, double _ordTime, double _brewTime, double _price) {

    arrTime = _arrTime; // Arrival time of the order.
    ordTime = _ordTime; // Order giving time of the order to the cashier.
    brewTime = _brewTime; // Brew time of orders' coffee.
    order2index = 0;
    brewed = false;  //boolean for if the order is all done, brewed and served or not.
    brewTaken = 0;  //variable which holds order's starting time of brewing.
    brewEnd = 0;    // variable which holds order's brew end time.
    turnAround = 0;  //variable which holds order's turnaround time.
    price = _price; // Price of the order.
    ordTaken = 0; // Order's arrival to the cashier.
    ordEnd = 0;  // Order's finishing time of giving order.
    orderId = 0;  //Order Id. For printing to the output file.

}



Orders::~Orders() {

}

