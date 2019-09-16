#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <set>
#include <limits>
#define NAN 0./0.

class OrderBook{
private:
  typedef std::pair<int, double> Order;

  //fuctor to sort the price order
  struct sort_price{
        bool operator()( Order orderA, Order orderB) {
               return (orderA.second>=orderB.second);
        }
  };

  //set is used to store the orders w.r.t. their prices, high -> low 
  std::set<Order, sort_price> Orders;

  // remove objects by id, time complexity: N
  void Erase(int &id, int &time){
       ProcessNum(time);
       std::set<Order>::iterator o=std::find_if(Orders.begin(),Orders.end(),  [&] ( Order o)->bool{ return o.first==id;});
       Orders.erase(o);
  }

  // insert object taking the price as the order : high to low, time complexity: logN, no more memory needed (in-place)
  void Insert(Order &order, int &time){
       ProcessNum(time);
       Orders.insert(order);
  }

  // to process the mean and check whether it is a new max
  void ProcessNum(int &time){
       if(Orders.size()>0){  //ignore the period where no order is inside the period
         average = (average*tot+Orders.begin()->second*(time-last))/(tot+(time-last));
         tot=tot+(time-last);
       }
       last = time; 
  }

public:
  OrderBook(std::string file):     //constrcutor for this orderbook facility
  average(NAN),tot(0){
    //open text file
    std::ifstream inFile(file);

    //declare variables to read the file   
    std::string entry, operation;
    int time=0;
    double price=0;
    int id;
    
    //actions on entries
    while(getline(inFile,entry)){
         if(average!=average) average=0;
         // subtract information from orders line by line
         std::istringstream iss(entry);
         iss>>time>>operation>>id;
         
         // operations, if it is an insertion, an order pair is created
         if(operation=="E") Erase(id,time);
         else{
           iss>>price; 
           std::pair<int, double> order(id, price);
           Insert(order,time);
         }
    }
  }
  
  ~OrderBook(){               //destructor to clear all the orders
    Orders.clear();
  }

  int   tot,last;
  double average;  
   
};

int main(int argv, char* argc[]){
    std::string inFile = argc[1];
   
    OrderBook runOrders(inFile); 
    std::cout<<runOrders.average<<std::endl;
}
