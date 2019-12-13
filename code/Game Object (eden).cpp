#ifndef HEADER_H
#define HEADER_H

#include <iostream>

using namespace std;

class gameobject{
	public:
		gameobject(){
			
		}
		gameobject(double _x, double _y, double sx, double sy){
			posx = _x;
			posy = _y;
			speedx = sx;
			speedy = sy;
			hp = 10;
		}
		~gameobject(){
			
		}
		
		void changehp(int e){
			if(e == 0)
			{
				hp = 10;
			}
			else
			{
				hp--;
			}
		}
		
		virtual void select() = 0;
		virtual void move() = 0;
		virtual int get_hp() = 0;
		
		double getpx(){
			return posx;
		}
		double getpy(){
			return posy;
		}
		void changep(){
			posx += speedx;
			posy += speedy;
		}
		int geth(){
			return hp;
		}
	private:
		int hp;
		double posx;
		double posy;
		double speedx;
		double speedy;
};

class worker: public gameobject{
	public:
		worker(){
			
		}
		
		worker(double _x, double _y): gameobject(_x, _y, 1, 1){
			
		}
		
		~worker(){
			
		}
		
		void select(){
			cout << "Scv good to go, sir!" << endl;
		}
		
		void move(){
			changep();
			cout << "Worker moves to (" << getpx() << ", " << getpy() << ")" << endl;
		}
		
		int get_hp(){
			return geth();
		}
		
		void repair(gameobject* g){
			g->changehp(0);
		}
		
		void build(int h){
			for(int i = 1; i <= h; i++)
			{
				for(int j = 0; j < h - i; j++)
				{
					cout << " ";
				}
				for(int j = 0; j < 2 * i - 1; j++)
				{
					cout << "*";
				}
				cout << endl;
			}
		}
};

class zealot: public gameobject{
	public:
		zealot(){
			
		}
		
		zealot(double _x, double _y): gameobject(_x, _y, 2, 2){
			
		}
		
		~zealot(){
			
		}
		
		void select(){
			cout << "My life for Aiur!" << endl;
		}
		
		void move(){
			changep();
			cout << "Zealot moves to (" << getpx() << ", " << getpy() << ")" << endl;
		}
		
		int get_hp(){
			return geth();
		}
		
		void attack(gameobject* g){
			g->changehp(1);
		}
};

class tower:public gameobject{
	public:
		tower(){
			
		}
		tower(double _x, double _y): gameobject(_x, _y, 0, 0){
			
		}
		~tower(){
			
		}
		
		void select(){
			cout << "~" << endl;
		}
		
		void move(){
			cout << "Tower cannot move." << endl;
		}
		
		int get_hp(){
			return geth();
		}
		
		void attack(gameobject* g){
			g->changehp(1);
		}
};


#endif



int main() {
    gameobject* g;  // gameobject是一个抽象类
    worker* w;  // worker zealot tower是派生类
    zealot* z;
    tower* t;
    double x, y;  // (x, y)表示坐标
    cin >> x >> y;
    w = new worker(x, y);
    cin >> x >> y;
    z = new zealot(x, y);
    cin >> x >> y;
    t = new tower(x, y);
    // test for select
    cout << "test for select:\n";

    g = w;
    g->select();
    g = z;
    g->select();
    g = t;
    g->select();
    // test for move
    cout << "\ntest for move:\n";

    g = w;
    g->move();
    g = z;
    g->move();
    g = t;
    g->move();
    // test for others
    cout << "\ntest for attack:\n";
    z->attack(t);
    t->attack(z);
    cout << "Zealot's hp is " << z->get_hp() << endl;
    cout << "Tower's hp is " << t->get_hp() << endl;
    cout << "\ntest for repair:\n";
    w->repair(z);  // worker将zealot的HP修复至10
    cout << "Zealot's hp is " << z->get_hp() << endl;
    int h;
    cin >> h;
    cout << "\ntest for build:\n";
    w->build(h);
    delete w;
    delete z;
    delete t;
    return 0;
}

