 #include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set> 

using namespace std;



vector<string> getInfoSort(vector<string> info){
	map<string, string> m;
	for(int i = 0; i < info.size(); i++)
	{
		string temp = info[i];
		string key = temp.substr(temp.find_first_of("|") + 1, temp.size() - temp.find_first_of("|"));
		string date = temp.substr(0, temp.find_first_of("|"));
		m.insert(make_pair(key, date));
		if(date.compare(m[key]) < 0)
		{
			m[key] = date;
		}
	}
	
	vector<string> s;
	for(map<string, string>::iterator it = m.begin(); it != m.end(); it++)
	{
		s.push_back(it->second);
	}
	
	for(int i = 0; i < s.size() - 1; i++)
	{
		for(int j = i; j < s.size(); j++)
		{
			if(s[i].compare(s[j]) > 0)
			{
				string temp = s[i];
				s[i] = s[j];
				s[j] = temp;
			}
		}
	}
	
	vector<string> v;
	for(int i = 0; i < s.size(); i++)
	{
		for(map<string, string>::iterator it = m.begin(); it != m.end(); it++)
		{
			if(s[i] == it->second)
			{
				string str = it->second + " : " + it->first;
				v.push_back(str);
				break;
			}
		}
	}
	
	return v;
}



#include <iostream>
#include <vector>
#include <string>
//#include "Delivery.hpp"
 using std::string;
 int main() {
    std::vector<string> info;
    int n = 0;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::string temp;
        std::cin >> temp;
        info.push_back(temp);
    }
      std::vector<string> afterSort = getInfoSort(info);
     for (std::vector<string>::iterator it = afterSort.begin();
         it != afterSort.end();
         ++it) {
        std::cout << *it << std::endl;
    }
    return 0;
}
 
