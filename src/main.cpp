#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <vector>
#include <queue>
#include <ctime>
#include "Orders.h"
#include "Cashier.h"
#include "Barista.h"

using namespace std;

template <class Container>
void split1(const string& str, Container& cont)
{
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(cont));
}

/*
 * Operator overloading for putting orders
 * into a min priority queue which holds orders
 * accordingly their orderEnd times.
 */
struct Comp{
    bool operator()(const Orders& a, Orders& b){
        return a.ordEnd>b.ordEnd;
    }
};

/*
 * Operator overloading for putting orders
 * into a max priority queue which holds orders
 * accordingly their prices.
 */

struct Comp2{
    bool operator()(const Orders& a, Orders& b){
        return a.price<b.price;
    }
};
/*
 * Operator overloading for putting orders
 * into a min priority queue which holds orders
 * accordingly their Identity numbers.
 */

struct Comp3{
    bool operator()(const Orders& a, Orders& b){
        return a.orderId>b.orderId;
    }
};


int main(int argc, char* argv[]) {

    std::clock_t start;
    double duration;

    start = std::clock();

    ifstream inputFile(argv[1]);
    string line;

    getline(inputFile, line);   // Take the first line in the input file.
    int cashierN = stoi(line); //Number of cashiers.

    getline(inputFile, line);   // Take the second line in the input file.
    int orderN = stoi(line);   //Number of orders.

    int barN = cashierN/3; //Defining barista number by dividing cashier numbers with 3.

    /*
     * Creating Order objects for given order inputs.
     * Then, adding them to the orderList vector.
    */
    vector<Orders> orderList;
    for(int i=0;i<orderN; i++){
        getline(inputFile,line);
        vector<string> orderDetails;
        split1(line, orderDetails);
        Orders newOrder(stod(orderDetails[0]),stod(orderDetails[1]),
                        stod(orderDetails[2]),stod(orderDetails[3]));
                newOrder.orderId = i+1;
        orderList.push_back(newOrder);
    }

    /*
     * Creating Cashier objects for given number of Cashiers.
     * Then, adding them to the Cashier vector named cashList.
    */
    vector<Cashier> cashList;
    for(int i=1; i<=cashierN;i++){
        Cashier cash(i);
        cashList.push_back(cash);
    }

    /*
     * Creating Barista objects for given Barista numbers.
     * Then, adding them to the Barista vector named barList.
     *
     */
    vector<Barista> barList;
    for(int i=1; i<=barN;i++){
        Barista bar(i);
        barList.push_back(bar);
    }

    priority_queue<Orders,vector<Orders>, Comp> pq1; // Priority queue which will hold orders according to their Order Finish times.

        double minBusyTime=0; // Variable which holds the minimum busy time for Cashiers, Orders will be directed to the least busy cashier.
        int lastOrder=0; //counter for the current order.
        int maxLengthCash=0;  // integer to hold Max Length of Cashier Queue.
        int tmpCash=0; // temporary integer for finding Max Length of Cashier queue.


        for(int i=0;i<cashierN;i++){  //Take first cashierN number of orders, which is number of cashiers.

            /*
             * Increment cashier's busyTime by order's arrival time + order giving time.
             * Increment cashier's workTime by order's order giving time for finding utilization of each cashier.
             * For first incoming orders, orderTaken variable is equal to arrival time.
             * Order end is equal to order's ordertaken time + order giving time.
             * Increment lastOrder so that keep track of orders one by one.
             */
            cashList[i].busyTime += orderList[i].arrTime + orderList[i].ordTime;
            cashList[i].workTime += orderList[i].ordTime;
            orderList[i].ordTaken = orderList[i].arrTime;
            orderList[i].ordEnd = orderList[i].ordTaken + orderList[i].ordTime;
            pq1.push(orderList[i]);
            lastOrder++;
        }
        /*
         * Finding least busy cashier, minBusyTime variable holds the first free cashier's busy time.
         * This is operation done fter every order's process.
         */
        minBusyTime = cashList[0].busyTime;
        for(int i=1;i<cashierN;i++){
            if(cashList[i].busyTime < minBusyTime){
                minBusyTime = cashList[i].busyTime;
            }
        }

        /*
         * Processing rest of the orders, after first Cashier Number of orders.
         * They will be sent to cashiers according to their arrival times.
         * If an order's arrival time is bigger than BusyTime of the minimum busy cashier
         * it will be processed differently,
         * otherwise it will be processed in a different way.
         */
        for(;lastOrder<orderN;lastOrder++){

            if(orderList[lastOrder].arrTime < minBusyTime){
                for(int j = lastOrder;j<orderN;j++){
                    if(orderList[j].arrTime<minBusyTime){
                        tmpCash++;
                    }
                }
                if(tmpCash>maxLengthCash){
                    maxLengthCash = tmpCash;
                }
                tmpCash = 0;
                for(int i=0;i<cashierN;i++){        // find the first least busy cashier.
                    if(minBusyTime == cashList[i].busyTime){
                        cashList[i].busyTime += orderList[lastOrder].ordTime;
                        cashList[i].workTime += orderList[lastOrder].ordTime;
                        orderList[lastOrder].ordTaken = minBusyTime;
                        orderList[lastOrder].ordEnd = orderList[lastOrder].ordTaken + orderList[lastOrder].ordTime;
                        pq1.push(orderList[lastOrder]);
                        minBusyTime = cashList[i].busyTime;
                        break;
                    }
                }
                for(int i=0;i<cashierN;i++){
                    if(cashList[i].busyTime < minBusyTime){
                        minBusyTime = cashList[i].busyTime;
                    }
                }
            }

            if(orderList[lastOrder].arrTime > minBusyTime){

                for(int i=0;i<cashierN;i++){
                    if(orderList[lastOrder].arrTime > cashList[i].busyTime){
                        cashList[i].busyTime = orderList[lastOrder].arrTime + orderList[lastOrder].ordTime;
                        cashList[i].workTime += orderList[lastOrder].ordTime;
                        orderList[lastOrder].ordTaken = orderList[lastOrder].arrTime;
                        orderList[lastOrder].ordEnd = orderList[lastOrder].ordTaken + orderList[lastOrder].ordTime;
                        pq1.push(orderList[lastOrder]);
                        minBusyTime = cashList[i].busyTime;
                        break;
                    }
                }
                for(int i=0;i<cashierN;i++){
                    if(cashList[i].busyTime < minBusyTime){
                        minBusyTime = cashList[i].busyTime;
                    }
                }
            }
        }
    vector<Orders> orderList2; // Order vector which will hold the vectors according to their order finishing times.
    int endCounter = 0; // a counter for finding index of a order in the barista operations.
    while(!pq1.empty()){
        orderList2.push_back(pq1.top());
        orderList2[endCounter].order2index = endCounter;
        endCounter++;
        pq1.pop();
    }       // empty the pq1 priority queue, add them to orderList2.

    /*
     * Priority queue which will be used in printing the orders' turnaround times to output file.
     * Holds them in increasing order with their Order Identity numbers.
     */
    priority_queue<Orders,vector<Orders>,Comp3> pq3;

        double minBarTime=0; // Variable which holds the minimum Busy Time of least busy Barista.
        int lastBarOrder=0;  // counter for processing orders one by one.
        int maxLengthBar=0;  // Variable which holds maximum Length of the Barista Queue.
        int tmpBar=0;        // Temporary max length of the Barista queue.

        /*
         * Add first barN numbers of orders to all baristas, which are all free in the beginning.
         * Increment worktimes for utilization of each barista.
         * Increment busyTimes for finding minimum busy times of baristas.
         */
        for(int i=0;i<barN;i++){
            barList[i].workTime += orderList2[i].brewTime;
            barList[i].busyTime += orderList2[i].ordEnd + orderList2[i].brewTime;
            orderList2[i].brewTaken = orderList2[i].ordEnd;
            orderList2[i].brewEnd = orderList2[i].brewTaken + orderList2[i].brewTime;
            orderList2[i].turnAround = orderList2[i].brewEnd - orderList2[i].arrTime;
            orderList2[i].brewed = true;
            lastBarOrder++;
            pq3.push(orderList2[i]);
        }

        /*
         * Finding the minimum busyTime for the Baristas.
         * Upcoming orders will be evaluated according to this variable.
         */

        minBarTime = barList[0].busyTime;
        for(int i=1;i<barN;i++){
            if(barList[i].busyTime < minBarTime){
            minBarTime = barList[i].busyTime;
            }
        }

        /*
        * Priority queue which sort orders by their price
        * in a descending order. To process next order,
        * always take top element of this priority queue in every operation.
        */
        priority_queue<Orders,vector<Orders>, Comp2> pq2;

        /*
         * Processing rest of the orders by Baristas.
         * Baristas pick the most expensive order in the queue.
         *
         */
        for(;lastBarOrder<orderN;lastBarOrder++){
            for(int k=0;k<orderN;k++){
                if(orderList2[k].ordEnd < minBarTime && !orderList2[k].brewed){
                    pq2.push(orderList2[k]);
                    tmpBar++;
                }
                else if(orderList2[k].ordEnd > minBarTime){
                    break;
                }
            }

            if(tmpBar>maxLengthBar){
                maxLengthBar = tmpBar;
            }

            Orders ord(pq2.top());
            orderList2[ord.order2index].brewed = true;
            pq2 = priority_queue<Orders,vector<Orders>, Comp2>();

            for(int i=0;i<barN;i++){
                if(minBarTime == barList[i].busyTime){
                    barList[i].workTime += orderList2[ord.order2index].brewTime;
                    barList[i].busyTime += orderList2[ord.order2index].brewTime;
                    orderList2[ord.order2index].brewTaken = minBarTime;
                    orderList2[ord.order2index].brewEnd = orderList2[ord.order2index].brewTaken + orderList2[ord.order2index].brewTime;
                    orderList2[ord.order2index].turnAround = orderList2[ord.order2index].brewEnd - orderList2[ord.order2index].arrTime;
                    minBarTime = barList[i].busyTime;
                    pq3.push(orderList2[ord.order2index]);
                    break;
                }
            }
            for(int i=0;i<barN;i++){
                if(barList[i].busyTime < minBarTime){
                    minBarTime = barList[i].busyTime;
                }
            }
            tmpBar = 0;
            }


    /*
     * Find the total running time by last brewed orders'
     * brewEnd time.
     */
        double tot =0;
        for(int i=0;i<orderList2.size();i++){
            if(orderList2[i].brewEnd>tot){
                tot = orderList2[i].brewEnd;
            }
        }
        double  totalRunTime = tot;


    /*
     * Writing to output file operations.
     */
    FILE *fp;
    fp = fopen(argv[2], "w");
    fprintf(fp, "%.2lf\n", totalRunTime);
    fprintf(fp,"%d\n", maxLengthCash);
    fprintf(fp,"%d\n", maxLengthBar);

    for(int i=0;i<cashierN;i++){
        fprintf(fp,"%.2lf\n",cashList[i].workTime/totalRunTime);
    }
    for(int i=0;i<barN;i++){
        fprintf(fp,"%.2lf\n",barList[i].workTime/totalRunTime);
    }


    while(!pq3.empty()){
        fprintf(fp,"%.2lf\n",pq3.top().turnAround);
        pq3.pop();
    }

    /*
     * I couldn't implement model2, so rest of output file is -1.
     */
        fprintf(fp, "\n");
        fprintf(fp, "-1\n");
        fprintf(fp, "-1\n");
        for(int k=0;k<barN;k++){
            fprintf(fp, "-1\n");
        }
        for(int k=0;k<cashierN;k++){
            fprintf(fp, "-1\n");
        }
        for(int k=0;k<barN;k++){
        fprintf(fp, "-1\n");
        }
        for(int k=0;k<orderN-1;k++){
            fprintf(fp, "-1\n");
        }
        fprintf(fp, "-1");




    fclose(fp);

    return 0;


}