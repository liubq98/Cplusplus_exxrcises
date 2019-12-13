#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#ifndef SYMBOLS
#define HEAD '@'
#define BODY 'X'
#define EMPTY '+'
#define FOOD '$'
#endif  // !SYMBOLS

enum direction { up = 0, down = 1, left = 2, right = 4, freeze = 5 };

struct point {
  int x;
  int y;
  point(int x = 0, int y = 0) : x(x), y(y) {}
  point(const point& another) : x(another.x), y(another.y) {}
  point& operator=(const point& other) {
    x = other.x;
    y = other.y;
    return *this;
  }
  friend bool operator==(const point& point1, const point& point2) {
    return point1.x == point2.x && point1.y == point2.y;
  }
  point& move(direction d) {
    switch (d) {
      case up:
        x--;
        break;
      case down:
        x++;
        break;
      case left:
        y--;
        break;
      case right:
        y++;
        break;
      case freeze:
      default:
        break;
    }
    return *this;
  }
};

#endif  // !_GLOBAL_H_


#include <iostream>
#include <list>

#ifndef _MAP_H_
#define _MAP_H_


static int len = 0;

class map{
	public:
		map(){
			
		}
		
		map(point initial_size, point initial_head, std::list<point> initial_foods){
            this->initial_size = initial_size;
            this->initial_head = initial_head;
			for(int i = 0; i < initial_size.x; i++)
			{
				for(int j = 0; j < initial_size.y; j++)
				{
					if(i == initial_head.x && j == initial_head.y)
					{
						arr[i][j] = '@';
					}
					else
					{
						arr[i][j] = '+';
					}
					
				}
				arr[i][initial_size.y] = '\0';
			}
			
			
			std::list<point>::iterator i;
			
			for(i = initial_foods.begin(); i != initial_foods.end(); i++)
			{
				arr[(*i).x][(*i).y] = '$';
			}
		}
		
		~map(){
			
		}
		
		void print(){
			for(int i = 0; i < initial_size.x; i++)
			{
				std::cout << arr[i] << std::endl;
			}
			std::cout << std::endl;
		}
		
		void move(direction aim){
			char arr2[15][15];
			for(int i = 0; i < initial_size.x; i++)
			{
				for(int j = 0; j < initial_size.y; j++)
				{
					arr2[i][j] = arr[i][j];
				}
			}
			
			//move body
			int temp1, temp2;
			if(len != 0)
			{
				temp1 = bodyy[len - 1];
				temp2 = bodyx[len - 1];
				arr[bodyx[len - 1]][bodyy[len - 1]] = '+';
				for(int i = len - 1; i >= 0; i--)
				{
					bodyy[i] = bodyy[i - 1];
					bodyx[i] = bodyx[i - 1];
				}
				bodyy[0] = initial_head.y;
				bodyx[0] = initial_head.x;
			}
			else
			{
				temp1 = initial_head.y;
				temp2 = initial_head.x;
				arr[initial_head.x][initial_head.y] = '+';
			}
			
			
			//move head
			initial_head.move(aim);
			
			//if gameover, recover, print, exit 
			if(!isGameOver())
			{
				if(arr[initial_head.x][initial_head.y] == '$')
				{
					len++;
					bodyy[len - 1] = temp1;
					bodyx[len - 1] = temp2;
				}
			}
			else
			{
				
			    for(int i = 0; i < initial_size.x; i++)
			    {
				    for(int j = 0; j < initial_size.y; j++)
				    {
					    arr[i][j] = arr2[i][j];
				    }
			    }
			    print();
			    std::cout << "Game Over!" << std::endl;
			    exit(0);
			}
			
			arr[initial_head.x][initial_head.y] = '@';
			
			for(int i = 0; i < len; i++)
			{
				arr[bodyx[i]][bodyy[i]] = 'X';
			}
			
		}
		
		bool isGameOver(){
			if(initial_head.x < initial_size.x && initial_head.x >= 0 && initial_head.y < initial_size.y && initial_head.y >= 0 && arr[initial_head.x][initial_head.y] != 'X')
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		
	private:
	   char arr[16][16];
	   int bodyx[15];
	   int bodyy[15];
       point initial_size;
       point initial_head;
	   
};


#endif




#include <iostream>
#include <list>
#include <algorithm>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

class InvalidInputException {
 public:
  InvalidInputException() { cerr << "Invalid input!" << endl; }
};
class DuplicateInputException : public InvalidInputException {
 public:
  DuplicateInputException() { cerr << "Duplicate input!" << endl; }
};

class GameUI {
 private:
  map* world;
  point initial_size;
  point initial_head;
  std::list<point> initial_foods;

 public:
  GameUI() {
    cout << "please input two positive integers indicates the map size!"
         << endl;
    cin >> initial_size.x >> initial_size.y;
    if (initial_size.x <= 5 || initial_size.y <= 5 || initial_size.x > 15 ||
        initial_size.y > 15) {
      cout << "invalid input" << endl;
      throw InvalidInputException();
    }
    cout << "please input two positive integers(range(0, size_x-1), "
            "range(0,size_y-1)) the initialize snake head position!"
         << endl;
    cin >> initial_head.x >> initial_head.y;
    if (initial_head.x >= initial_size.x || initial_head.x < 0 ||
        initial_head.y >= initial_size.y || initial_head.y < 0) {
      cout << "invalid input" << endl;
      throw InvalidInputException();
    }
    int food_num;
    cout << "please input how many food you will put and then input food "
            "position which is different form each other"
         << endl;
    cin >> food_num;

    if (food_num <= 0) {
      throw InvalidInputException();
    }

    while (food_num > 0) {
      food_num--;
      point temp;
      cin >> temp.x >> temp.y;
      if (temp.x >= 0 && temp.x < initial_size.x && temp.y >= 0 &&
          temp.y < initial_size.y &&
          std::find(initial_foods.begin(), initial_foods.end(), temp) ==
              initial_foods.end() &&
          !(temp.x == initial_head.x && temp.y == initial_head.y)) {
        initial_foods.push_back(temp);
      } else {
        throw DuplicateInputException();
      }
    }

    world = new map(initial_size, initial_head, initial_foods);
  }

  ~GameUI() { delete world; }

  void GameLoop() {
    world->print();
    bool exit = false;
    while (true) {
      char operation = getInput();
      switch (operation) {
        case 'w':
        case 'W':
          this->world->move(up);
          break;
        case 's':
        case 'S':
          this->world->move(down);
          break;
        case 'a':
        case 'A':
          this->world->move(left);
          break;
        case 'd':
        case 'D':
          this->world->move(right);
          break;
        case 'q':
        case 'Q':
          exit = true;
          break;
        default:
          this->world->move(freeze);
      }
      world->print();
      if (world->isGameOver()) {
        cout << "Game Over!" << endl;
        break;
      }
      if (exit) {
        cout << "Bye!" << endl;
        break;
      }
    }
  }

  char getInput() {
    char temp;
    cin >> temp;
    return temp;
  }
};

int main() {
  GameUI greedySnake;
  greedySnake.GameLoop();
  return 0;
}


