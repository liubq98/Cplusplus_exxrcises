#include <iostream>
#include <vector>

using namespace std;

int findmax(vector<int> v)
{
	int max = 0;
	for(int i = 0; i < v.size(); i++)
	{
		if(max < v[i] && v[i] != 10)
		{
			max = v[i];
		}
	}
	return max;
}

int main(){
	int c;
	int n, m, num;
	
	cin >> c;
	while(c--)
	{
		vector<int> v;
		cin >> n >> m;
		for(int i = 0; i < n; i++)
		{
			cin >> num;
			v.push_back(num);
		}

        int max = findmax(v);
		int time = 0;
		int flag = v[m];
		v[m] = 10;
		if(v.size() == 1)
		{
			cout << 1 << endl;
			continue;
		}
		while(1)
		{
			if(flag >= max && v[0] == 10)
			{
				time++;
				cout << time << endl;
				break;
			}
			else if(v[0] == max && flag <= max)
			{
				v.erase(v.begin());
				max = findmax(v);
				time++;
			}
			else
			{
				int temp = v[0];
				v.erase(v.begin());
				v.push_back(temp);
			}
			
		}
	}

return 0;
}
