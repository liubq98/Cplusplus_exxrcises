#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <iostream>
#include <cmath>

using namespace std;

struct City {
    double x, y;          // position of the city
    string name;  // name of city
};

class Vehicle {
 public:
    explicit Vehicle(double _speed) : speed(_speed) {}
    virtual void doTravel(const City& src, const City& dest) = 0;
    virtual double getdistance() = 0;
    virtual string getname() = 0;
    double getSpeed() const {
        return speed;
    }
    virtual ~Vehicle() {}
 private:
    double speed;
};

class BicycleStrategy:public Vehicle
{
public:
	BicycleStrategy(double bsp):dis(0), name("Bicycle"), Vehicle(bsp){

	}

	~BicycleStrategy(){}

	double getdistance(){
		return dis;
	}

	string getname(){
		return name;
	}

	void doTravel(const City& src, const City& dest){
		dis = fabs(src.x - dest.x) + fabs(src.y - dest.y);
	}
private:
	double dis;
	string name;
};

class TrainStrategy:public Vehicle
{
public:
	TrainStrategy(double tsp):dis(0), name("Train"), Vehicle(tsp){
		
	}
	~TrainStrategy(){}

	double getdistance(){
		return dis;
	}

	string getname(){
		return name;
	}

	void doTravel(const City& src, const City& dest){
		dis = sqrt((src.x - dest.x)*(src.x - dest.x) + (src.y - dest.y)*(src.y - dest.y));
	}

private:
	double dis;
	string name;	
};

class AirplaneStrategy:public Vehicle
{
public:
	AirplaneStrategy(double asp):dis(0), name("Airplane"), Vehicle(asp){

	}
	~AirplaneStrategy(){}

	double getdistance(){
		return dis;
	}

	string getname(){
		return name;
	}

	void doTravel(const City& src, const City& dest){
		double dis1 = fabs(src.x - dest.x);
		double dis2 = fabs(src.y - dest.y);
		if(dis1 > dis2)
		{
			dis = dis1;
		}
		else
		{
			dis = dis2;
		}
	}

private:
	double dis;
	string name;
	
};


#endif


 #include <string>
#include <iostream>
#include "vehicle.h"

using namespace std;

class Tourist {
 public:


    explicit Tourist(Vehicle* strategy_){
    	strategy = strategy_;
    }

    void setStrategy(Vehicle* strategy_){
    	strategy = strategy_;
    }

    void travel(const City& src, const City& dest){
    	strategy->doTravel(src, dest);
    	double temp1 = strategy->getdistance();
    	double temp2 = strategy->getSpeed();
    	double time = temp1 / temp2;
    	cout << "It takes " << time << " hours to Travel from "
    	     << src.name << " to " << dest.name << " by " 
    	     << strategy->getname()<< "." << endl;
    }

 private:
    Vehicle* strategy;
};
