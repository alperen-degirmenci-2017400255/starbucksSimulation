//
// Created by Alperen on 11/17/2017.
//
#include "Cashier.h"

Cashier::Cashier(int _id) {

    id = _id; //Cashier Id.
    busyTime = 0;  // Total Busy Time of the cashier
    workTime = 0; // Total work time of the cashier for utilization.

}

Cashier::~Cashier() {

}
