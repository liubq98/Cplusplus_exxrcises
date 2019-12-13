#ifndef TOKEN_HPP_
#define TOKEN_HPP_
#include <string>
using std::string;

struct Token {
  // DATA, OPEN_TAG, CLOSE_TAG
  string type;
  string content;
  // nesting depth
  int depth;
};

#endif


#ifndef BULIDER_HPP_
#define BULIDER_HPP_
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)
#include <vector>
#include <stack>

class Bulider {
public:
 static Bulider* getInstance();
 static void destroyInstance();

  // check the token's validity in current nesting structure
  // if valid, record it in _tokens, if not, set _error true
  void handleOneToken(Token token);
  void display();

private:
  static Bulider* _instance;

  std::vector<Token> _tokens;
  std::stack<Token> _stack;
  bool _error;

  Bulider() { _error = false; }
  ~Bulider() {}
  DISALLOW_COPY_AND_ASSIGN(Bulider);
};

#endif


#include <vector>
#include <stack>
#include <string>
#include <iostream>

using namespace std;

Bulider* Bulider::_instance = NULL;

//static
Bulider* Bulider::getInstance(){
	if(_instance == NULL)
	{
		_instance = new Bulider;
	}
	return _instance;
}

void Bulider::destroyInstance(){
	if(_instance != NULL)
	{
	    delete _instance;
	}
}


// check the token's validity in current nesting structure
// if valid, record it in _tokens, if not, set _error true
void Bulider::handleOneToken(Token token){
	if(token.type == "OPEN_TAG")
	{
		if(!_stack.empty())
		{
			token.depth = _stack.top().depth + 1;
		}
		_stack.push(token);
		_tokens.push_back(token);
	}
	else if(token.type == "CLOSE_TAG")
	{
		if(_stack.top().content == token.content)
		{
			_stack.pop();
		}
		else
		{
			_error = true;
		}
	}
	else
	{
		_tokens.push_back(token);
	}
}

void Bulider::display(){
	if(_error)
	{
		cout << "INVALID INPUT" << endl;
		return;
	}
	int len = _tokens.size();
	for(int i = 0; i < len; i++)
	{
		if(_tokens[i].type == "OPEN_TAG")
		{
			for(int j = 0; j < _tokens[i].depth; j++)
			{
				cout << " ";
			}
			cout << _tokens[i].content << ":" << endl;
		}
		else if(_tokens[i].type == "DATA")
		{
			for(int j = 0; j < _tokens[i].depth; j++)
			{
				cout << " ";
			}
			cout << "  " << _tokens[i].content << endl;
		}
	} 
}




#ifndef STATE_HPP_
#define STATE_HPP_
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)
#include <string>

using std::string;

class Parser;

class State {
public:
  virtual ~State() {}
 // handle the parser's requests and change to next state if nessesary
  virtual void handleOneChar(Parser* parser, char ch) = 0;

protected:
  string _cache;
 // transfer cache string to a token and emit it to the bulider
 virtual void emit(Bulider* dest) = 0;
};


class DataState : public State {
public:
 static State* getInstance();
 static void destroyInstance();

 virtual void handleOneChar(Parser* parser, char ch);

private:
 static State* _instance;

  virtual void emit(Bulider* dest);

 DataState() {}
 virtual ~DataState() {}
 DISALLOW_COPY_AND_ASSIGN(DataState);
};


class TagNameState : public State {
public:
 static State* getInstance();
 static void destroyInstance();

 virtual void handleOneChar(Parser* parser, char ch);

private:
 static State* _instance;

  virtual void emit(Bulider* dest);

 TagNameState() {}
 virtual ~TagNameState() {}
 DISALLOW_COPY_AND_ASSIGN(TagNameState);
};

#endif



#include <string>
#include <iostream>

using namespace std;

State* DataState::_instance = NULL;
State* TagNameState::_instance = NULL;

//static 
State* DataState::getInstance(){
	if(_instance == NULL)
	{
		_instance = new DataState;
	}
	return _instance;
}

void DataState::destroyInstance(){
	if(_instance != NULL)
	{
	    delete _instance;
	}
}


//virtual 
void DataState::handleOneChar(Parser* parser, char ch){
	if(ch != '<')
	{
		_cache += ch;
	}
	else
	{
		int len = _cache.size();
		_cache.erase(0);
		_cache.erase(len - 1);
		parser->setState(TagNameState::getInstance());
		emit(parser->getBulider());
	}
}
 
void DataState::emit(Bulider* dest){
	Token temp;
	temp.content = _cache;
	temp.depth = 0;
	dest->handleOneToken(temp);
	_cache.clear();
}

//different class

 //static 
State* TagNameState::getInstance(){
 	if(_instance == NULL)
	{
		_instance = new TagNameState;
	}
 	return _instance;
}
 
void TagNameState::destroyInstance(){
	if(_instance != NULL)
	{
	    delete _instance;
	}
}

// virtual 
void TagNameState::handleOneChar(Parser* parser, char ch){
	if(ch != '>')
	{
		_cache += ch;
	}
	else
	{
		emit(parser->getBulider());
		parser->setState(DataState::getInstance());
	}
}

void TagNameState::emit(Bulider* dest){
	Token temp;
	temp.depth = 0;
	if(_cache[0] == '/')
	{
		int len = _cache.size();
		temp.content = _cache.substr(1, len - 1);
		temp.type = "CLOSE_TAG";
	}
	else
	{
		temp.content = _cache;
		temp.type = "OPEN_TAG";
	}
	dest->handleOneToken(temp);
	_cache.clear();
}


#ifndef PARSER_HPP_
#define PARSER_HPP_
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)
#include <string>
#include <iostream>
using std::string;

class Parser {
public:
 static Parser* getInstance();
 static void destroyInstance();

 void setState(State* state) { _state = state; }
  Bulider* getBulider() { return _bulider; }

  void read() {
    string line;
    while (std::getline(std::cin, line))
      _str += line;
  }
 void parse() {
    int index = 0;
    while (index < _str.size()) {
      consumeOneChar(_str[index]);
      ++index;
    }
    _bulider->display();
  }

private:
  static Parser* _instance;

  std::string _str;
 State* _state;
  Bulider* _bulider;

 Parser() {
    // default state
    _state = DataState::getInstance();
    _bulider = Bulider::getInstance();
  }
 ~Parser() {
    // destroy ALL states (not only the current one)
    DataState::destroyInstance();
    TagNameState::destroyInstance();
    // destroy the bulider
    Bulider::destroyInstance();
  }
  DISALLOW_COPY_AND_ASSIGN(Parser);

  void consumeOneChar(char ch);
};

#endif



#include <string>
#include <iostream>

Parser* Parser::_instance = NULL;

// static 
Parser* Parser::getInstance(){
 	if(_instance == NULL)
	{
		_instance = new Parser;
	}
	return _instance;
}

void Parser::destroyInstance(){
	if(_instance != NULL)
	{
	    delete _instance;
	}
}


void Parser::consumeOneChar(char ch){
	_state->handleOneChar(getInstance(), ch);
}



//#include "Parser.hpp"

void test() {
  Parser* parser = Parser::getInstance();
  parser->read();
  parser->parse();
  Parser::destroyInstance();
}

int main() {
  test();
  return 0;
}
