//
// Created by Alperen on 11/20/2017.
//
#include "Barista.h"

Barista::Barista(int _id){
    id = _id;       // id of the Barista.
    busyTime = 0; // Total busy time of the barista.
    workTime = 0;  // Total work time of the barista for the utilization.

}

Barista::~Barista() {

}
