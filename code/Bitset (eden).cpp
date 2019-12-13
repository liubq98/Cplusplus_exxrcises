#ifndef BITSET_H
#define BITSET_H
#include<iostream>
#define N 5
const int max_length = 32 * N;
class bitset {
    private:
        int a[N];
    public:
        bitset();
        void set(int pos);
        void reset(int pos);
        int count() const;
        bool test(int pos) const;
        bool any() const;
        bool none() const;
        bool all() const;
        bitset& operator&= (const bitset& b);
        bitset& operator|= (const bitset& b);
        bitset& operator^= (const bitset& b);
        bitset& operator= (const bitset& b);
        bitset& operator <<= (int pos);
        bitset& operator >>= (int pos);
        bitset operator~() const;
        bitset operator&(const bitset& b) const;
        bitset operator|(const bitset& b) const;
        bitset operator^(const bitset& b) const;
        bitset operator<<(int pos) const;
        bitset operator>>(int pos) const;
        bool operator== (const bitset& b) const;
        bool operator!= (const bitset& b) const;
        bool operator[] (int pos) const;
        friend std::ostream& operator << (std::ostream& os, const bitset& s) {
            for (int i = N-1; i >= 0; i--) {
                for (int j = 31; j >= 0; j--) {
                    if (s.a[i] & (1 << j)) os << 1;
                    else os << 0;
                }
            }
            return os;
        }
};
#endif





bitset::bitset(){
	for(int i = 0; i < 5; i++)
	{
		a[i] = 0;
	}
}

void bitset::set(int pos){
	if(test(pos))
	{
		return;
	}
	else
	{
		a[pos / 32] += 1 << (pos % 32);
	}
}

void bitset::reset(int pos){
	if(test(pos))
	{
		a[pos / 32] -= 1 << (pos % 32);
	}
}

int bitset::count() const{
	int cou = 0;
	for(int i = 0; i < 160; i++)
	{
		if(test(i))
		{
			cou++;
		}
	}
return cou;
}

bool bitset::test(int pos) const{
	if(a[pos / 32] & (1 << (pos % 32)))
	{
		return true;
	} 
return false;
}

bool bitset::any() const{
	for(int i = 0; i < 160; i++)
	{
		if(test(i))
		{
			return true;
		}
	}
return false;
}

bool bitset::none() const{
	if(any())
	{
		return false;
	}
return true;
}

bool bitset::all() const{
	int cou = 0;
	for(int i = 0; i < 160; i++)
	{
		if(test(i))
		{
			cou++;
		}
	}
	
	if(cou == 160)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bitset& bitset::operator&= (const bitset& b){
	for(int i = 0; i < 160; i++)
	{
		if(test(i) && b.test(i))
		{
			set(i);
		}
		else
		{
			reset(i);
		}
	}
return *this;
}

bitset& bitset::operator|= (const bitset& b){
	for(int i = 0; i < 160; i++)
	{
		if(test(i) || b.test(i))
		{
			set(i);
		}
		else
		{
			reset(i);
		}
	}
return *this;
}

bitset& bitset::operator^= (const bitset& b){
	for(int i = 0; i < 160; i++)
	{
		if(test(i) != b.test(i))
		{
			set(i);
		}
		else
		{
			reset(i);
		}
	}
return *this;
}

bitset& bitset::operator= (const bitset& b){
	for(int i = 0; i < 160; i++)
	{
		if(b.test(i) != test(i))
		{
			if(test(i))
			{
				reset(i);
			}
			else
			{
				set(i);
			}
		}
	}
return *this;
}

bitset& bitset::operator <<= (int pos){
	for(int i = 159; i >= 0; i--)
	{
		if(i > pos)
		{
			if(test(i - pos))
			{
				set(i);
			}
			else
			{
				reset(i);
			}
		}
		else
		{
			reset(i);
		}
	}
return *this;
}

bitset& bitset::operator >>= (int pos){
	for(int i = 0; i < 160; i++)
	{
		if(i < 160 - pos)
		{
			if(test(i + pos))
			{
				set(i);
			}
			else
			{
				reset(i);
			}
		}
		else
		{
			set(i);
		}
	}
return *this;
}

bitset bitset::operator~() const{
	bitset temp;
	for(int i = 0; i < 160; i++)
	{
		if(test(i))
		{
			temp.reset(i);
		}
		else
		{
			temp.set(i);
		}
	}
return temp;
}

bitset bitset::operator&(const bitset& b) const{
	bitset temp;
	for(int i = 0; i < 160; i++)
	{
		if(test(i) && b.test(i))
		{
			temp.set(i);
		}
		else
		{
			temp.reset(i);
		}
	}
return temp;
}

bitset bitset::operator|(const bitset& b) const{
	bitset temp;
	for(int i = 0; i < 160; i++)
	{
		if(test(i) || b.test(i))
		{
			temp.set(i);
		}
		else
		{
			temp.reset(i);
		}
	}
return temp;
}

bitset bitset::operator^(const bitset& b) const{
	bitset temp;
	for(int i = 0; i < 160; i++)
	{
		if(test(i) != b.test(i))
		{
			temp.set(i);
		}
		else
		{
			temp.reset(i);
		}
	}
return temp;
}

bitset bitset::operator<<(int pos) const{
	bitset temp;
	for(int i = 0; i < 160; i++)
	{
		if(i < pos)
		{
			temp.reset(i);
		}
		else
		{
			if(test(i - pos))
			{
				temp.set(i);
			}
			else
			{
				temp.reset(i);
			}
		}
	}
return temp;
}

bitset bitset::operator>>(int pos) const{
	bitset temp;
	for(int i = 0; i < 160; i++)
	{
		if(i < 160 - pos)
		{
			if(test(i + pos))
			{
				temp.set(i);
			}
			else
			{
				temp.reset(i);
			}
		}
		else
		{
			temp.set(i);
		}
	}
return temp;
}

bool bitset::operator== (const bitset& b) const{
	for(int i = 0; i < 160; i++)
	{
		if(test(i) != b.test(i))
		{
			return false;
		}
	}
return true;
}

bool bitset::operator!= (const bitset& b) const{
	for(int i = 0; i < 160; i++)
	{
		if(test(i) != b.test(i))
		{
			return true;
		}
	}
return false;
}

bool bitset::operator[] (int pos) const{
	return test(pos);
}


#include<iostream>
using namespace std;
int main() {
    bitset a, b;
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a.set(x);
    }
    cout << "a.count() is " << a.count() << "\n";
    cout << "a.test(5) is " << (a.test(5) ? "true" : "false") << "\n";
    cout << "a.any() is " << (a.any() ? "true" : "false") << "\n";
    cout << "a.none() is " << (a.none() ? "true" : "false") << "\n";
    cout << "a.all() is " << (a.all() ? "true" : "false") << "\n";
    b = ~b;
    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        b.reset(x);
    }
    cout << a << "\n";
    cout << b << "\n";
    if (a == b) {
        cout << "hello\n";
    }
    if (a != b) {
        cout << "world\n";
    }
    bitset c;
    // test &
    c = a;
    c &= b;
    cout << c << "\n";
    c = a & b;
    cout << c << "\n";
    // test |
    c = a;
    c |= b;
    cout << c << "\n";
    c = a | b;
    cout << c << "\n";
    // test ^
    c = a;
    c ^= b;
    cout << c << "\n";
    c = a ^ b;
    cout << c << "\n";
    // test <<
    c = a;
    c <<= 2;
    cout << c << "\n";
    c = a << 2;
    cout << c << "\n";
    // test >>
    c = b;
    c >>= 2;
    cout << c << "\n";
    c = b >> 2;
    cout << c << "\n";
    // test []
    for (int i = 0; i < q; i++) {
        int x;
        cin >> x;
        if (a[i])
            cout << "Yes\n";
        else
            cout << "No\n";
    }
}


