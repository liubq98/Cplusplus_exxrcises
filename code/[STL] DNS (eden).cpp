#include "dns.h"
#include <string>
#include <map>
#include <vector>
#include <iostream>

using namespace std;

dns::dns(string ip){
    _ip = ip;
}  // constructor
vector<string>& dns::operator[](const string& domain){
    vector<string> v;
    map< string, vector<string> >::iterator it = _map.find(domain);
    if(it == _map.end())
    {
        _map.insert(make_pair(domain, v));
    }
    it = _map.find(domain);
    return it->second;
}  // return mutable ip_set

    /*
     *  if the domain maps at least one ip
     *  fot example, the dns server ip is 114.114.114.114
     *  the domain name is www.baidu.com
     *  and it maps 123.125.114.144, 220.181.57.217, 180.149.132.47
     *  then you should output like bellow
     *
     *  Server: 114.114.114.114
     *  Name: www.baidu.com
     *  Address: 123.125.114.144
     *  Name: www.baidu.com
     *  Address: 220.181.57.217
     *  Name: www.baidu.com
     *  Address: 180.149.132.47
     *
     *  if the domain doesn't map ip
     *  fot example, the dns server ip is 8.8.8.8
     *  the domain name is www.google.com, and doesn't map ip
     *  then you should output like bellow
     *
     *  Server: 8.8.8.8
     *  Server can't find www.google.com
     */
void dns::nslookup(const string& domain){
    vector<string> v;
    map< string, vector<string> >::iterator it = _map.find(domain);

    cout << "Server: " << _ip << endl;
    if(it == _map.end())
    {
        cout << "Server can't find " << domain << endl;
        return;
    }

    v = it->second;
    if(v.empty())
    {
        cout << "Server can't find " << domain << endl;
        return;
    }

    for(int i = 0; i < v.size(); i++)
    {
        cout << "Name: " << domain << endl;
        cout << "Address: " << v[i] << endl;
    }
}
