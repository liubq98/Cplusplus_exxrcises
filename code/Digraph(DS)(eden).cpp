
//
//  Set.hpp
//  C++
//
//  Created by 李天培 on 16/2/25.
//  Copyright ? 2016年 lee. All rights reserved.
//

#ifndef Set_hpp
#define Set_hpp

#include <stdio.h>

#define MAX_MEMBERS 100

class Set {
private:
    int members[MAX_MEMBERS];
    int size;
public:
    // Create an empty set.
    Set();
    // Create an set with some element.
    Set(int* m, int s);
    // Copy Constructor
    Set(Set const &s);
    
    // append a element to set.
    // If element in the set, return false.
    // Or insert in set and return true.
    bool append(int e);
    
    // remove a element by its value from set.
    // If element in the set, then remove it and return true.
    // Or return false.
    bool remove(int e);
    
    // return true if the set is empty, or return false.
    bool isEmptySet();
    
    // return true if the element e is in the set, or return false.
    bool isInSet(int e);
    
    // & is intersection of two set
    Set operator&(const Set &s);
    // | is union of two set
    Set operator|(const Set &s);
    // A - B is the complement of B with respect to A
    Set operator-(const Set &s);
    // A + B is their symmetric difference. A + B = (A - B) | (B - A)
    Set operator+(const Set &s);
    
    
    // return set.
    int* getMembers();
    
    // return size of set.
    int getSize();
    
    int get(int pos);
};

#endif /* Set_hpp */


//
//  Set.cpp
//  C++
//
//  Created by 李天培 on 16/2/25.
//  Copyright ? 2016年 lee. All rights reserved.
//

//#include "Set.hpp"

Set::Set() {
    size = 0;
}

Set::Set(int* m, int s) {
    size = 0;
    for (int i = 0; i < s ; i++) {
        if (!isInSet(m[i])) {
            members[size++] = m[i];
        }
        if (size == MAX_MEMBERS) break;
    }
}

Set::Set(Set const &s) {
    size = s.size;
    for (int i = 0; i < size; i++) {
        members[i] = s.members[i];
    }
}

bool Set::append(int element) {
    if (size < MAX_MEMBERS && !isInSet(element)) {
        members[size] = element;
        size++;
        return true;
    } else {
        return false;
    }
}

bool Set::remove(int element) {
    for (int i = 0; i < size; i++) {
        if (members[i] == element) {
            members[i] = members[--size];
            return true;
        }
    }
    return false;
}

bool Set::isEmptySet() {
    return (size == 0) ? true : false;
}

int* Set::getMembers() {
    return members;
}

int Set::getSize() {
    return size;
}

int Set::get(int pos) {
    return members[pos - 1];
}

bool Set::isInSet(int element) {
    for (int i = 0; i < size; i++) {
        if (members[i] == element) {
            return true;
        }
    }
    return false;
}

Set Set::operator&(const Set &s) {
    Set temp;
    for (int i = 0; i < s.size; i++) {
        if (isInSet(s.members[i])) {
            temp.members[temp.size++] = s.members[i];
        }
    }
    return temp;
}

Set Set::operator|(const Set &s) {
    Set temp(*this);
    for (int i = 0; i < s.size; i++) {
        temp.append(s.members[i]);
    }
    return temp;
}

Set Set::operator-(const Set &s) {
    Set temp(s);
    Set temp2(*this);
    for (int i = 0; i < temp2.size; i++) {
        if (temp.isInSet(temp2.members[i])) {
            temp2.remove(temp2.members[i]);
        }
    }
    return temp2;
}

Set Set::operator+(const Set &s) {
    Set temp(s);
    return (*this - temp) | (temp - *this);
}









//
//  Matrix.hpp
//  C++
//
//  Created by 李天培 on 16/3/2.
//  Copyright ? 2016年 lee. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <stdio.h>
#include <iostream>
#include <assert.h>

#define ELEMENT_POS(x,y) (x - 1) * columns + y - 1

class Matrix {
private:
    // matrix element type
    typedef int matrix_element_type;
protected:
    int row, columns;
    matrix_element_type* matirx;
    
public:
    // copy constructor
    Matrix(Matrix const &);
    // creat a empty matrix with row and column, fill the matrix by 0
    Matrix(int r, int c);
    // delete
    ~Matrix();
    // creat a identify matrix with n which is row and column
    static Matrix identifyMatrix(int n);
    
    // replace the element in specific position and return true
    // return false if can't replace
    bool replace(matrix_element_type e, int r, int c);
    bool isDiagonalMatrix() const;
    bool isZeroMatrix() const;
    bool isSquareMatrix() const;
    bool isSymmetrix() const;
    
    void display() const {
        for (int i = 1; i <= row; i++) {
            for (int j = 1; j <= columns; j++) {
                std::cout << matirx[ELEMENT_POS(i, j)] << " ";
            }
            std::cout << std::endl;
        }
    }
    
    Matrix transpose() const;
    
    Matrix& operator=(const Matrix & m);
    Matrix operator+(const Matrix & m);
    Matrix operator*(const Matrix & m);
    
    bool operator==(const Matrix & m) const;
    
    
    int getRow() const;
    int getColums() const;
    matrix_element_type getElement(int r, int c) const;
};

#endif /* Matrix_hpp */


//
//  Matrix.cpp
//  C++
//
//  Created by 李天培 on 16/3/2.
//  Copyright ? 2016年 lee. All rights reserved.
//

//#include "Matrix.hpp"

Matrix::Matrix(Matrix const & m) {
    row = m.row;
    columns = m.columns;
    matirx = new matrix_element_type[row * columns];
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= columns; j++) {
            matirx[ELEMENT_POS(i, j)] = m.matirx[ELEMENT_POS(i, j)];
        }
    }
}

Matrix::Matrix(int r, int c) {
    row = r > 0 ? r : 1;
    columns = c > 0 ? c : 1;
    matirx = new matrix_element_type[row * columns];
    for (int i = 0; i < row * columns; i++) {
        matirx[i] = 0;
    }
}

Matrix::~Matrix() {
    delete [] matirx;
}

Matrix Matrix::identifyMatrix(int n) {
    Matrix temp = Matrix(n, n);
    for (int i = 1; i <= temp.columns * temp.row; i++) {
        temp.matirx[(i - 1) * n + i - 1] = 1;
    }
    return temp;
}

bool Matrix::replace(Matrix::matrix_element_type e, int r, int c) {
    if (r <= row && c <= columns && r > 0 && columns > 0) {
        matirx[ELEMENT_POS(r, c)] = e;
        return true;
    }
    return false;
}

Matrix::matrix_element_type Matrix::getElement(int r, int c) const {
    return matirx[ELEMENT_POS(r, c)];
}

int Matrix::getRow() const {
    return row;
}

int Matrix::getColums() const {
    return columns;
}

bool Matrix::isDiagonalMatrix() const {
    if (row != columns) {
        return false;
    }
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= columns; j++) {
            if (i != j && matirx[ELEMENT_POS(i, j)] != 0) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::isSquareMatrix() const {
    return row == columns;
}

bool Matrix::isZeroMatrix() const {
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= columns; j++) {
            if (matirx[ELEMENT_POS(i, j)] != 0) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::isSymmetrix() const {
    return *this == transpose();
}

Matrix& Matrix::operator=(const Matrix &m) {
    row = m.row;
    columns = m.columns;
    delete [] matirx;
    matirx = new matrix_element_type[row * columns];

    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= columns; j++) {
            matirx[ELEMENT_POS(i, j)] = m.matirx[ELEMENT_POS(i, j)];
        }
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix &m) {
    assert(m.row == row);
    assert(m.columns == columns);
    Matrix temp(*this);
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= columns; j++) {
            temp.matirx[ELEMENT_POS(i, j)] += m.matirx[ELEMENT_POS(i, j)];
        }
    }
    return temp;
}

Matrix Matrix::operator*(const Matrix &m) {
    assert(columns == m.row);
    Matrix temp(row, m.columns);
    for (int i = 1; i <= temp.row; i++) {
        for (int j = 1; j <= temp.columns; j++) {
            for (int s = 1; s <= columns; s++) {
                temp.matirx[(i - 1) * temp.columns + j - 1] +=
                matirx[ELEMENT_POS(i, s)] *
                m.matirx[(s - 1) * m.columns + j - 1];
            }
        }
    }
    return temp;
}

bool Matrix::operator==(const Matrix &m) const {
    if (row != m.row || columns != m.columns) {
        return false;
    }
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= columns; j++) {
            if (matirx[ELEMENT_POS(i, j)] != m.matirx[ELEMENT_POS(i, j)]) {
                return false;
            }
        }
    }
    return true;
}

Matrix Matrix::transpose() const {
    Matrix t(columns, row);
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= columns; j++) {
             t.matirx[(j - 1) * t.columns + i - 1] = matirx[ELEMENT_POS(i, j)];
        }
    }
    return t;
}










//
//  BooleanMatrix.hpp
//  C++
//
//  Created by 李天培 on 16/3/24.
//  Copyright ? 2016年 lee. All rights reserved.
//

#ifndef BooleanMatrix_hpp
#define BooleanMatrix_hpp

#include <stdio.h>
//#include "Matrix.hpp"

class BooleanMatrix: public Matrix {
private:
    typedef bool matrix_element_type;
public:
    BooleanMatrix(const BooleanMatrix &);
    BooleanMatrix(int r, int c);
    
    bool replace(matrix_element_type e, int r, int c);
    
    BooleanMatrix operator&(const BooleanMatrix &);
    BooleanMatrix operator|(const BooleanMatrix &);
    BooleanMatrix BooleanProduct(const BooleanMatrix &) const;
    
};

#endif /* BooleanMatrix_hpp */


#include <stdio.h>
#include <iostream> 
//#include "Matrix.hpp"

//#include "BooleanMatrix.hpp"

BooleanMatrix::BooleanMatrix(const BooleanMatrix &m):Matrix(m){
	
}

BooleanMatrix::BooleanMatrix(int r, int c):Matrix(r, c){
	
}

    
bool BooleanMatrix::replace(matrix_element_type e, int r, int c){
	Matrix::replace(e, r, c);
}

    
BooleanMatrix BooleanMatrix::operator&(const BooleanMatrix &m){
	if(getRow() != m.getRow() || getColums() != m.getColums())
	{
		return *this;
	}
	
	BooleanMatrix temp(*this);
	for(int i = 1; i <= getRow(); i++)
	{
		for(int j = 1;j <= getColums(); j++)
		{
			if(temp.getElement(i, j) != 1 || m.getElement(i, j) != 1)
			{
				temp.replace(0, i, j);
			}
			else
			{
				temp.replace(1, i, j);
			}
		}
	}
return temp;
}

BooleanMatrix BooleanMatrix::operator|(const BooleanMatrix &m){
	if(getRow() != m.getRow() || getColums() != m.getColums())
	{
		return *this;
	}
	
	BooleanMatrix temp(*this);
	for(int i = 1; i <= getRow(); i++)
	{
		for(int j = 1;j <= getColums(); j++)
		{
			if(temp.getElement(i, j) == 1 || m.getElement(i, j) == 1)
			{
				temp.replace(1, i, j);
			}
			else
			{
				temp.replace(0, i, j);
			}
		}
	}
return temp;	
}

BooleanMatrix BooleanMatrix::BooleanProduct(const BooleanMatrix &m) const{
	if(getColums() != m.getRow())
	{
		return *this;
	}
	
	BooleanMatrix temp(m);
	int flag = 0;
	for(int i = 1; i <= m.getColums(); i++)
	{
		for(int j = 1; j <= getRow(); j++)
		{
			flag = 0;
			for(int k = 1; k <= m.getRow(); k++)
			{
				if(getElement(j, k) == 1 && m.getElement(k, i) == 1)
				{
					flag = 1;
					break;
				}
			}
			temp.replace(flag, j, i);
		}
	}
return temp;
}








//
//  ProductSet.hpp
//  C++
//
//  Created by 李天培 on 16/4/6.
//  Copyright ? 2016年 lee. All rights reserved.
//

#ifndef ProductSet_hpp
#define ProductSet_hpp

#include <iostream>
//#include "Set.hpp"

using std::cout;
using std::endl;

class ProductSet {
protected:
    Set first;
    Set second;
public:
    ProductSet(Set a, Set b);
    
    Set getFirstSet() const;
    Set getSecondSet() const;

    
};

#endif /* ProductSet_hpp */


#include <iostream>
//#include "Set.hpp"

//#include "ProductSet.hpp"

ProductSet::ProductSet(Set a, Set b){
	first = a;
	second = b;
}

    
Set ProductSet::getFirstSet() const{
	return first;
}

Set ProductSet::getSecondSet() const{
	return second;
}






//relation file
#ifndef Relation_hpp
#define Relation_hpp

//#include "ProductSet.hpp"
//#include "BooleanMatrix.hpp"

class Relation{
	public:
		Relation(BooleanMatrix const & m);
		~Relation();
	protected:
		BooleanMatrix mat;
}; 

#endif

//#include "ProductSet.hpp"
//#include "BooleanMatrix.hpp"
//#include "Relation.hpp"

Relation::Relation(BooleanMatrix const &m): mat(m){
	
}

Relation::~Relation(){
	
}





//
//  Digraph.hpp
//  C++
//
//  Created by 李天培 on 16/4/7.
//  Copyright ? 2016年 lee. All rights reserved.
//

#ifndef Digraph_hpp
#define Digraph_hpp

#include <stdio.h>
//#include "BooleanMatrix.hpp"
//#include "Set.hpp"
//#include "ProductSet.hpp"
//#include "Relation.hpp"

class Digraph: Relation {
private:
    Set set;
    int getSetElePos(int);
public:
    Digraph(BooleanMatrix const &m, Set const &s);
    int inDegree(int);
    int outDegree(int);
    
    Digraph pathOfLength(int);
    
    // Properties of Relations.????
    bool isReflexive() const;
    bool isIrreflexive() const;
    bool isSymmetric() const;
    bool isAsymmetric() const;
    bool isAntisymmetric() const;
    
    bool isTransitive() const;
    
    BooleanMatrix getBooleanMatrix() const;
};

#endif /* Digraph_hpp */


#include <stdio.h>
//#include "BooleanMatrix.hpp"
//#include "Set.hpp"
//#include "ProductSet.hpp"
//#include "Relation.hpp"

//#include "Digraph.hpp"

//private function
int Digraph::getSetElePos(int e){
	for(int i = 0; i < set.getSize(); i++)
	{
		if(set.get(i) == e)
		{
			return i;
		}
	}
}

//public
Digraph::Digraph(BooleanMatrix const &m, Set const &s): Relation(m){
	set = s;
}

int Digraph::inDegree(int num){
	int i;
	for(i = 1; i <= set.getSize(); i++)
	{
		if(set.get(i) == num)
		{
			break;
		}
	}
	if(i == set.getSize() + 1)
	{
		return -1;
	}
	
	int sum = 0;
	for(int j = 1; j <= set.getSize(); j++)
	{
		if(mat.getElement(j, i) == 1)
		{
			sum++;
		}
	}
return sum;
}

int Digraph::outDegree(int num){
	int i;
	for(i = 1; i <= set.getSize(); i++)
	{
		if(set.get(i) == num)
		{
			break;
		}
	}
	if(i == set.getSize() + 1)
	{
		return -1;
	}
	
	int sum = 0;
	for(int j = 1; j <= set.getSize(); j++)
	{
		if(mat.getElement(i, j) == 1)
		{
			sum++;
		}
	}
return sum;
}

    
Digraph Digraph::pathOfLength(int n){
	Digraph temp(mat, set);
	if(n == 0)
	{
		return temp;
	}
	if(n > set.getSize())
	{
		n = set.getSize();
	}
	
	n--;
	while(n)
	{
		temp.mat = temp.mat.BooleanProduct(this->mat);
		n--;
	}
return temp;
}

    
// Properties of Relations.????
bool Digraph::isReflexive() const{
	for(int i = 1; i <= mat.getRow(); i++)
	{
		for(int j = 0; j <= mat.getColums(); j++)
		{
			if(i == j)
			{
				if(mat.getElement(i, j) != 1)
				{
					return false;
				}
			}
		}
	}
return true;
}

bool Digraph::isIrreflexive() const{
	for(int i = 1; i <= mat.getRow(); i++)
	{
		for(int j = 0; j <= mat.getColums(); j++)
		{
			if(i == j)
			{
				if(mat.getElement(i, j) != 0)
				{
					return false;
				}
			}
		}
	}
return true;
}

bool Digraph::isSymmetric() const{
	if(mat.isSymmetrix())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Digraph::isAsymmetric() const{
	for(int i = 1; i <= mat.getRow(); i++)
	{
		for(int j = 1; j <= mat.getColums(); j++)
		{
			if(mat.getElement(i, j) == 1)
			{
				if(mat.getElement(j, i) != 0)
				{
					return false;
				}
			} 
		}
	}
return true;
}

bool Digraph::isAntisymmetric() const{
	for(int i = 1; i <= mat.getRow(); i++)
	{
		for(int j = 1; j <= mat.getColums(); j++)
		{
			if(i != j)
			{
				if(mat.getElement(i, j) == 0 || mat.getElement(j, i) == 0)
				{
					
				}
				else
				{
					return false;
				}
			} 
		}
	}
return true;
}

    
bool Digraph::isTransitive() const{
	if(mat.getRow() != mat.getColums())
	{
		return false;
	}
	for(int i = 1; i <= mat.getRow(); i++)
	{
		for(int j = 1; j <= mat.getColums(); j++)
		{
			for(int k = 1; k <= mat.getRow(); k++)
			{
				if(mat.getElement(i, k) == 1 && mat.getElement(k, j) == 1)
				{
					if(mat.getElement(i, j) != 1)
					{
						return false;
					}
				}
			}
		}
	}
return true;
}

    
BooleanMatrix Digraph::getBooleanMatrix() const{
	return mat;
}







//
//  main.cpp
//  C++
//
//  Created by 李天培 on 16/2/25.
//  Copyright ? 2016年 lee. All rights reserved.
//

#include <iostream>

//#include "Set.hpp"
//#include "BooleanMatrix.hpp"
//#include "Matrix.hpp"
//#include "ProductSet.hpp"
//#include "Digraph.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::string;

void displayProductSet(ProductSet temp) {
    int *a, *b;

    a = temp.getFirstSet().getMembers();
    b = temp.getSecondSet().getMembers();

    cout << "{";
    for (int i = 0; i < temp.getFirstSet().getSize(); i++) {
        for (int j = 0; j < temp.getSecondSet().getSize(); j++) {
            cout << ((i + j) != 0 ? "," : "")
            << "(" << a[i] << "," << b[j] << ")";
        }
    }
    cout << "}" << endl;
}

void displaySet(int* members, int size) {
    std::cout << "{";
    for (int i = 0; i < size; i++) {
        if (i < size - 1) std::cout << members[i] << ", ";
        else std::cout << members[i];
    }
    std::cout << "}" << std::endl;
}

void testBooleanMatrix() {
    cout << "TEST BOOLEAN MATRIX" << endl;

    int r = 0, c = 0;
    cin >> r >> c;
    BooleanMatrix m1(r, r);
    BooleanMatrix m2(r, r);
    BooleanMatrix m3(r, c);

    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= r; j++) {
            int t = 0;
            cin >> t;
            m1.replace(t, i, j);
        }
    }
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= r; j++) {
            int t = 0;
            cin >> t;
            m2.replace(t, i, j);
        }
    }

    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            int t = 0;
            cin >> t;
            m3.replace(t, i, j);
        }
    }

    m1.display();
    cout << endl;
    m2.display();
    cout << endl;
    m3.display();
    cout << endl;
    (m1 | m2).display();
    cout << endl;
    (m1 & m2).display();
    cout << endl;
    (m1.BooleanProduct(m3)).display();
}

void testDigraph() {
    cout << "TEST DIGRAPH" << endl;
    unsigned int r = 1;
    cin >> r;

    BooleanMatrix matrix(r, r);
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= r; j++) {
            bool t = true;
            int x;
            cin >> x;
            t = (x == 1) ? 1 : 0;
            matrix.replace(t, i, j);
        }
    }
    cout << "matrix:" << endl;
    matrix.display();
    cout << endl;

    Set set;
    int *test;
    test = new int[r];
    for (int i = 0; i < r; i++) {
        cin >> test[i];
        while (set.isInSet(test[i])) {
            test[i]++;
        }
        set.append(test[i]);
    }
    cout << "set:" << endl;
    displaySet(set.getMembers(), set.getSize());
    cout << endl;

    Digraph d(matrix, set);

    int x;
    cin >> x;
    cout << test[x] << "'s in degree: " << d.inDegree(test[x]) << endl;

    cin >> x;
    cout << test[x] << "'s out degree: " << d.outDegree(test[x]) << endl;

    cin >> x;
    Digraph pathD = d.pathOfLength(x);
    pathD.getBooleanMatrix().display();
    cout << endl;

    cout << "reflexvie: " << d.isReflexive() << endl;
    cout << "reflexvie: " << pathD.isReflexive() << endl;

    cout << "irreflexvie: " << d.isIrreflexive() << endl;
    cout << "irreflexvie: " << pathD.isIrreflexive() << endl;

    cout << "symmetric: " << d.isSymmetric() << endl;
    cout << "symmetric: " << pathD.isSymmetric() << endl;

    cout << "Asymmetric: " << d.isAsymmetric() << endl;
    cout << "Asymmetric: " << pathD.isAsymmetric() << endl;

    cout << "Antisymmetric: " << d.isAntisymmetric() << endl;
    cout << "Antisymmetric: " << pathD.isAntisymmetric() << endl;

    cout << "transitive: " << d.isTransitive() << endl;
    cout << "transitive: " << pathD.isTransitive() << endl;

    delete [] test;
}

void testProductSet() {
    cout << "test ProductSet" << endl;
    Set a;
    Set b;

    int n = 0;
    // number of set a
    cin >> n;
    for (int i = 0; i < n; i++) {
        int temp = 0;
        cin >> temp;
        a.append(temp);
    }

    // number of set b
    cin >> n;
    for (int i = 0; i < n; i++) {
        int temp = 0;
        cin >> temp;
        b.append(temp);
    }

    ProductSet test(a, b);
    displaySet(test.getFirstSet().getMembers(), test.getFirstSet().getSize());
    displaySet(test.getSecondSet().getMembers(), test.getSecondSet().getSize());

    displayProductSet(test);
}

int main() {
    testBooleanMatrix();
    testDigraph();
    testProductSet();
}

