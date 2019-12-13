#ifndef WORLD_H
#define WORLD_H

#include <iostream>

using namespace std;

static int flag = 0;

struct person{
 	int id;
 	int fri[100];
 	int fnum;
 	person(){
 		id = flag;
 		flag++;
 		fnum = 0;
	}
};
 
class group {
    public:
    	group(){
    		num = 0;
		}
		
		~group(){
			
		}
		
 	    group(int _rel){
 	    	rel = _rel;
 	    	num = 0;
		}
		
        void displayGroup(){
        	for(int i = 0; i < num; i++)
        	{
        		cout << "Person_" << members[i].id << ": ";
        		if(members[i].fnum == 0)
        		{
        			cout << "null" << endl;
        			continue;
				}
				
        		for(int j = 0; j < members[i].fnum - 1; j++)
        		{
        			cout << members[i].fri[j] << ", ";
				}
				cout << members[i].fri[members[i].fnum - 1] << endl;
			}
			
		}
		
        bool addMember(person &p){
        	for(int i = 0; i < num; i++)
        	{
        		if(members[i].id == p.id)
        		{
        			return false;
				}
			}
			
			members[num++] = p;
			
			if(rel == 1)
			{
				for(int i = 0; i < num - 1; i++)
				{
					makeFriend(members[i], members[num - 1]);
				}
			}
		return true;
		}
		
        bool deleteMember(person &p){
        	int aim = -1;
        	for(int i = 0; i < num; i++)
        	{
        		if(members[i].id == p.id)
        		{
        			aim = i;
        			break;
				}
			}
			
			if(aim != -1)
			{
				members[aim] = members[num - 1];
				num--;
				return true;
			}
			else
			{
				return false;
			}
		}
		
        bool makeFriend(person &p1, person &p2){
        	int temp1 = -1;
        	int temp2 = -1;
        	for(int i = 0; i < num; i++)
        	{
        		if(members[i].id == p1.id)
        		{
        			temp1 = i;
				}
			}
			for(int i = 0; i < num; i++)
        	{
        		if(members[i].id == p2.id)
        		{
        			temp2 = i;
				}
			}
			
			if(temp1 != -1 && temp2 != -1)
			{
				for(int i = 0; i < members[temp1].fnum; i++)
				{
					if(members[temp1].fri[i] == members[temp2].id)
					{
						return false;
					}
				}
				for(int i = 0; i < members[temp2].fnum; i++)
				{
					if(members[temp2].fri[i] == members[temp1].id)
					{
						return false;
					}
				}
				
				members[temp1].fri[members[temp1].fnum++] = members[temp2].id;
				members[temp2].fri[members[temp2].fnum++] = members[temp1].id;
				return true;
			}
			else
			{
				return false;
			}
		}
		
        bool breakRelation(person &p1, person &p2){
        	int temp1 = -1;
        	int temp2 = -1;
        	for(int i = 0; i < num; i++)
        	{
        		if(members[i].id == p1.id)
        		{
        			temp1 = i;
        			break;
				}
			}
			for(int i = 0; i < num; i++)
        	{
        		if(members[i].id == p2.id)
        		{
        			temp2 = i;
        			break;
				}
			}
			int temp11 = -1;
			int temp22 = -1;
			if(temp1 != -1 && temp2 != -1)
			{
				for(int i = 0; i < members[temp1].fnum; i++)
				{
					if(members[temp1].fri[i] == members[temp2].id)
					{
						temp11 = i;
						break;
					}
				}
				for(int i = 0; i < members[temp2].fnum; i++)
				{
					if(members[temp2].fri[i] == members[temp1].id)
					{
						temp22 = i;
						break;
					}
				}
				if(temp11 != -1 && temp22 != -1)
				{
					members[temp1].fnum--;
					for(int i = temp11; i < members[temp1].fnum; i++)
					{
						members[temp1].fri[i] = members[temp1].fri[i + 1];
					}
					members[temp2].fnum--;
					for(int i = temp22; i < members[temp2].fnum; i++)
					{
						members[temp2].fri[i] = members[temp2].fri[i + 1];
					}
					return true;
				}
				else
				{
					return false;
				}
				
			}
			else
			{
				return false;
			}
		}
		
    private:
    	int rel;
    	person members[100];
    	int num;
};

#endif 


#include <iostream>

using namespace std;
 void test_1() {
    person mike, jack, lily, carson, sucie;
    group school(0), family_1(1), family_2(1);
    // make group (act as a society)
    school.addMember(mike);
    school.addMember(jack);
    school.addMember(lily);
    family_1.addMember(mike);
    family_1.addMember(carson);
    family_2.addMember(jack);
    family_2.addMember(lily);
    family_2.addMember(sucie);
    // construct relationship in the society
    school.makeFriend(mike, jack);
    school.makeFriend(mike, lily);
    // display the society
    cout << "\n------ SCHOOL -----\n";
    school.displayGroup();
    cout << "\n------ FAMILY_1 -----\n";
    family_1.displayGroup();
    cout << "\n------ FAMILY_2 -----\n";
    family_2.displayGroup();
}
 void test_2() {
    person Baidu, Alibaba, Tencent, NTES, Kingsoft_Antivirus, _360safe;
    group BAT(1), ECommerce(1), Security(1);
    // make group (act as a society)
    BAT.addMember(Baidu);
    BAT.addMember(Alibaba);
    BAT.addMember(Tencent);
    ECommerce.addMember(Baidu);
    ECommerce.addMember(Alibaba);
    ECommerce.addMember(Tencent);
    ECommerce.addMember(NTES);
    Security.addMember(Kingsoft_Antivirus);
    Security.addMember(_360safe);
    // display the society
    cout << "\n------ BAT -----\n";
    BAT.displayGroup();
    cout << "\n------ ECommerce -----\n";
    ECommerce.displayGroup();
    cout << "\n------ Security -----\n";
    Security.displayGroup();
}
 void test_3() {
    person p0, p1, p2, p3, p4;
    group g0(0), g1(0), g2(1);
    // make group (act as a society)
    g0.addMember(p0);
    g0.addMember(p1);
    g0.addMember(p2);
    g1.addMember(p0);
    g1.addMember(p3);
    g2.addMember(p3);
    g2.addMember(p4);
    // construct relationship in the society
    g1.makeFriend(p0, p3);
    g2.breakRelation(p3, p4);
    g0.deleteMember(p2);
    // display the society
    cout << "\n------ G0 -----\n";
    g0.displayGroup();
    cout << "\n------ G1 -----\n";
    g1.displayGroup();
    cout << "\n------ G2 -----\n";
    g2.displayGroup();
}
 void test_4() {
    person p[50];
    group g0(0), g1(1);
    int p_count;
    cin >> p_count;
    // make group (act as a society)
    for (int i = 0; i < p_count/2; i++)
        g0.addMember(p[i]);
    for (int i = p_count/2; i < p_count; i++)
        g1.addMember(p[i]);
    // construct relationship in the society
    for (int i = 0; i < p_count/5; i += 2)
        g0.makeFriend(p[i], p[i+1]);
    for (int i = p_count/2; i < p_count*3/4-1; i += 2)
        g1.breakRelation(p[i], p[i+1]);
    for (int i = p_count/4; i < p_count/2; i++)
        g0.deleteMember(p[i]);
    for (int i = p_count*3/4; i < p_count; i++)
        g1.deleteMember(p[i]);
    // display the society
    cout << "\n------ G0 -----\n";
    g0.displayGroup();
    cout << "\n------ G1 -----\n";
    g1.displayGroup();
}
 int main() {
    int test_id;
    cin >> test_id;
    switch (test_id) {
        case 1:
        test_1();
        break;
        case 2:
        test_2();
        break;
        case 3:
        test_3();
        break;
        case 4:
        test_4();
        break;
        default:
        cout << "wrong input\n";
    }
    return 0;
}
 /* ---------- structure for 'world.h' ----------
 * define the struct and the class functions by yourself #(^_^)#
 * the member function is not complete, add something as you need
 struct person;
 class group {
    void displayGroup();
    bool addMember(person &p);
    bool deleteMember(person &p);
    bool makeFriend(person &p1, person &p2);
    bool breakRelation(person &p1, person &p2);
};
 */
 
