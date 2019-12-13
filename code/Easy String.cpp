#include "EasyString.hpp"
#include <cstdlib>

void Assign(char * & str, int & length){
	str = (char*)malloc((length + 1)*sizeof(char));
}

void AddTwo(string & res, char * & str1, char * & str2){
	string st1 = str1;
	string st2 = str2;
    res = st1 + st2;
	free(str1);
	free(str2);
}
