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
    matrix_element_type* matrix;

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
                std::cout << matrix[ELEMENT_POS(i, j)] << " ";
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


Matrix::Matrix(Matrix const & m) {
    row = m.row;
    columns = m.columns;
    matrix = new matrix_element_type[row * columns];
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= columns; j++) {
            matrix[ELEMENT_POS(i, j)] = m.matrix[ELEMENT_POS(i, j)];
        }
    }
}

Matrix::Matrix(int r, int c) {
    row = r > 0 ? r : 1;
    columns = c > 0 ? c : 1;
    matrix = new matrix_element_type[row * columns];
    for (int i = 0; i < row * columns; i++) {
        matrix[i] = 0;
    }
}

Matrix::~Matrix() {
    delete [] matrix;
}

Matrix Matrix::identifyMatrix(int n) {
    Matrix temp = Matrix(n, n);
    for (int i = 1; i <= temp.columns * temp.row; i++) {
        temp.matrix[(i - 1) * n + i - 1] = 1;
    }
    return temp;
}

bool Matrix::replace(Matrix::matrix_element_type e, int r, int c) {
    if (r <= row && c <= columns && r > 0 && columns > 0) {
        matrix[ELEMENT_POS(r, c)] = e;
        return true;
    }
    return false;
}

Matrix::matrix_element_type Matrix::getElement(int r, int c) const {
    return matrix[ELEMENT_POS(r, c)];
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
            if (i != j && matrix[ELEMENT_POS(i, j)] != 0) {
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
            if (matrix[ELEMENT_POS(i, j)] != 0) {
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
    delete [] matrix;
    matrix = new matrix_element_type[row * columns];

    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= columns; j++) {
            matrix[ELEMENT_POS(i, j)] = m.matrix[ELEMENT_POS(i, j)];
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
            temp.matrix[ELEMENT_POS(i, j)] += m.matrix[ELEMENT_POS(i, j)];
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
                temp.matrix[(i - 1) * temp.columns + j - 1] +=
                matrix[ELEMENT_POS(i, s)] *
                m.matrix[(s - 1) * m.columns + j - 1];
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
            if (matrix[ELEMENT_POS(i, j)] != m.matrix[ELEMENT_POS(i, j)]) {
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
             t.matrix[(j - 1) * t.columns + i - 1] = matrix[ELEMENT_POS(i, j)];
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

    BooleanMatrix transpose() const;
};

#endif /* BooleanMatrix_hpp */

//
//  BooleanMatrix.cpp
//  C++
//
//  Created by 李天培 on 16/3/24.
//  Copyright ? 2016年 lee. All rights reserved.
//


bool BooleanMatrix::replace(matrix_element_type e, int r, int c) {
    if (r <= row && c <= columns && r > 0 && columns > 0) {
        matrix[ELEMENT_POS(r, c)] = e;
        return true;
    }
    return false;
}

BooleanMatrix::BooleanMatrix(const BooleanMatrix & bm) : Matrix(bm) {
}

BooleanMatrix::BooleanMatrix(int r, int c) : Matrix(r, c) {
}

BooleanMatrix BooleanMatrix::operator&(const BooleanMatrix & bm) {
    assert(row == bm.row);
    assert(columns == bm.columns);
    BooleanMatrix temp(row, columns);
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= columns; j++) {
            temp.matrix[ELEMENT_POS(i, j)] =
            matrix[ELEMENT_POS(i, j)] & bm.matrix[ELEMENT_POS(i, j)];
        }
    }
    return temp;
}

BooleanMatrix BooleanMatrix::operator|(const BooleanMatrix & bm) {
    assert(row == bm.row);
    assert(columns == bm.columns);
    BooleanMatrix temp(row, columns);
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= columns; j++) {
            temp.matrix[ELEMENT_POS(i, j)] =
            matrix[ELEMENT_POS(i, j)] | bm.matrix[ELEMENT_POS(i, j)];
        }
    }
    return temp;
}

BooleanMatrix BooleanMatrix::BooleanProduct(const BooleanMatrix & bm) const {
    assert(getColums() == bm.getRow());
    BooleanMatrix temp(getRow(), bm.getColums());
    for (int i = 1; i <= getRow(); i++) {
        for (int j = 1; j <= bm.getColums(); j++) {
            for (int k = 1; k <= getColums(); k++) {
                temp.matrix[(i - 1) * temp.columns + j - 1] |=
                getElement(i, k) & bm.getElement(k, j);
            }
        }
    }
    return temp;
}

BooleanMatrix BooleanMatrix::transpose() const {
    BooleanMatrix t(columns, row);
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= columns; j++) {
            t.matrix[(j - 1) * t.columns + i - 1] = matrix[ELEMENT_POS(i, j)];
        }
    }
    return t;
}

//
//  Relation.hpp
//  C++
//
//  Created by 李天培 on 16/4/9.
//  Copyright ? 2016年 lee. All rights reserved.
//

#ifndef Relation_hpp
#define Relation_hpp

#include <iostream>

class Relation {
protected:
    BooleanMatrix matrix;
public:
    Relation(BooleanMatrix const &);

    BooleanMatrix getBooleanMatrix() const;

    // Operations on Relations
    Relation complementary() const;
    Relation inverse() const;
    Relation operator&(const Relation &);
    Relation operator|(const Relation &);
};

#endif /* Relation_hpp */


Relation::Relation(BooleanMatrix const &m): matrix(m){
	
}

BooleanMatrix Relation::getBooleanMatrix() const{
	return matrix;
}


    // Operations on Relations
Relation Relation::complementary() const{
	Relation temp(matrix);
	for(int i = 1; i <= matrix.getRow(); i++)
	{
		for(int j = 1; j <= matrix.getColums(); j++)
		{
			if(matrix.getElement(i, j) == 1)
			{
				temp.matrix.replace(0, i, j);
			}
			else
			{
				temp.matrix.replace(1, i, j);
			}
		}
	}
return temp;
}

Relation Relation::inverse() const{
	BooleanMatrix mat(matrix.getColums(), matrix.getRow());
	Relation temp(mat);
	for(int i = 1; i <= matrix.getColums(); i++)
	{
		for(int j = 1; j <= matrix.getRow(); j++)
		{
			temp.matrix.replace(matrix.getElement(j, i), i, j);
		}
	}
return temp;
}

Relation Relation::operator&(const Relation &r){
	Relation temp(matrix);
	for(int i = 1; i <= matrix.getRow(); i++)
	{
		for(int j = 1; j <= matrix.getColums(); j++)
		{
			if(matrix.getElement(i, j) == 0 || r.matrix.getElement(i, j) == 0)
			{
				temp.matrix.replace(0, i, j);
			}
		}
	}
return temp;
}

Relation Relation::operator|(const Relation &r){
	Relation temp(matrix);
	for(int i = 1; i <= matrix.getRow(); i++)
	{
		for(int j = 1; j <= matrix.getColums(); j++)
		{
			if(matrix.getElement(i, j) == 1 || r.matrix.getElement(i, j) == 1)
			{
				temp.matrix.replace(1, i, j);
			}
		}
	}
return temp;
}




//
//  BinaryRelation.hpp
//  C++
//
//  Created by 李天培 on 16/4/7.
//  Copyright ? 2016年 lee. All rights reserved.
//

#ifndef BINARYRELATION_HPP_
#define BINARYRELATION_HPP_

#include <stdio.h>

class BinaryRelation: public Relation {
private:
    Set set;
    int getSetElePos(int);
public:
    BinaryRelation(BooleanMatrix const &m, Set const &s);
    int inDegree(int);
    int outDegree(int);

    BinaryRelation pathOfLength(int);

    // Properties of Relations.????
    bool isReflexive() const;
    bool isIrreflexive() const;
    bool isSymmetric() const;
    bool isAsymmetric() const;
    bool isAntisymmetric() const;
    bool isTransitive() const;

    bool isEquivalence() const;
    
    BinaryRelation composition(const BinaryRelation &);

    BinaryRelation reflexiveClosure() const;
    BinaryRelation symmetricClosure() const;
    BinaryRelation transitiveClosure() const;
    
};

#endif


//private
int BinaryRelation::getSetElePos(int e){
	for(int i = 0; i < set.getSize(); i++)
	{
		if(set.get(i) == e)
		{
			return i;
		}
	}
}

//public
BinaryRelation::BinaryRelation(BooleanMatrix const &m, Set const &s):Relation(m){
	set = s;
}

int BinaryRelation::inDegree(int num){
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
		if(matrix.getElement(j, i) == 1)
		{
			sum++;
		}
	}
return sum;
}

int BinaryRelation::outDegree(int num){
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
		if(matrix.getElement(i, j) == 1)
		{
			sum++;
		}
	}
return sum;
}


BinaryRelation BinaryRelation::pathOfLength(int n){
	BinaryRelation temp(matrix, set);
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
		temp.matrix = temp.matrix.BooleanProduct(this->matrix);
		n--;
	}
return temp;
}


// Properties of Relations.????
bool BinaryRelation::isReflexive() const{
	for(int i = 1; i <= matrix.getRow(); i++)
	{
		for(int j = 0; j <= matrix.getColums(); j++)
		{
			if(i == j)
			{
				if(matrix.getElement(i, j) != 1)
				{
					return false;
				}
			}
		}
	}
return true;
}

bool BinaryRelation::isIrreflexive() const{
	for(int i = 1; i <= matrix.getRow(); i++)
	{
		for(int j = 0; j <= matrix.getColums(); j++)
		{
			if(i == j)
			{
				if(matrix.getElement(i, j) != 0)
				{
					return false;
				}
			}
		}
	}
return true;
}

bool BinaryRelation::isSymmetric() const{
	if(matrix.isSymmetrix())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BinaryRelation::isAsymmetric() const{
	for(int i = 1; i <= matrix.getRow(); i++)
	{
		for(int j = 1; j <= matrix.getColums(); j++)
		{
			if(matrix.getElement(i, j) == 1)
			{
				if(matrix.getElement(j, i) != 0)
				{
					return false;
				}
			} 
		}
	}
return true;
}

bool BinaryRelation::isAntisymmetric() const{
	for(int i = 1; i <= matrix.getRow(); i++)
	{
		for(int j = 1; j <= matrix.getColums(); j++)
		{
			if(i != j)
			{
				if(matrix.getElement(i, j) == 0 || matrix.getElement(j, i) == 0)
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

bool BinaryRelation::isTransitive() const{
	if(matrix.getRow() != matrix.getColums())
	{
		return false;
	}
	for(int i = 1; i <= matrix.getRow(); i++)
	{
		for(int j = 1; j <= matrix.getColums(); j++)
		{
			for(int k = 1; k <= matrix.getRow(); k++)
			{
				if(matrix.getElement(i, k) == 1 && matrix.getElement(k, j) == 1)
				{
					if(matrix.getElement(i, j) != 1)
					{
						return false;
					}
				}
			}
		}
	}
return true;
}


bool BinaryRelation::isEquivalence() const{
	if(isReflexive() && isSymmetric() && isTransitive())
	{
		return true;
	}
	else
	{
		return false;
	}
}

    
BinaryRelation BinaryRelation::composition(const BinaryRelation &r){
	BinaryRelation br(matrix, set);
	br.matrix = matrix.BooleanProduct(r.matrix);
return br;
}


BinaryRelation BinaryRelation::reflexiveClosure() const{
	BinaryRelation br(matrix, set);
	for(int i = 1; i <= matrix.getRow(); i++)
	{
		for(int j = 1; j <= matrix.getColums(); j++)
		{
			if(matrix.getElement(i, j) == 0 && i == j)
			{
				br.matrix.replace(1, i, j);
			} 
		}
	}
return br;
}

BinaryRelation BinaryRelation::symmetricClosure() const{
	BinaryRelation br(matrix, set);
	br.matrix = br.matrix | br.inverse().getBooleanMatrix();
return br;
}

BinaryRelation BinaryRelation::transitiveClosure() const{
	BinaryRelation br(matrix, set);
	int n = matrix.getRow();
	for(int k = 1; k <= n; k++)
	{
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= n; j++)
			{
				if(br.matrix.getElement(i, k) == 1 && br.matrix.getElement(k, j) == 1)
				{
					if(br.matrix.getElement(i, j) != 1)
					{
						br.matrix.replace(1, i, j);
					}
				}
			}
		}
	}
return br;
}




//
//  main.cpp
//  C++
//
//  Created by 李天培 on 16/2/25.
//  Copyright ? 2016年 lee. All rights reserved.
//



using std::cin;
using std::cout;
using std::endl;
using std::string;

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
    cout << "TEST BinaryRelation" << endl;
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

    BinaryRelation d(matrix, set);

    int x;
    cin >> x;
    cout << test[x] << "'s in degree: " << d.inDegree(test[x]) << endl;

    cin >> x;
    cout << test[x] << "'s out degree: " << d.outDegree(test[x]) << endl;

    cin >> x;
    BinaryRelation pathD = d.pathOfLength(x);
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

    cout << "Equivalence: " << d.isEquivalence() << endl;
    cout << "Equivalence: " << pathD.isEquivalence() << endl;

    cout << "reflexive closure: " << endl;
    d.reflexiveClosure().getBooleanMatrix().display();
    cout << "reflexvie: " << d.reflexiveClosure().isReflexive() << endl;

    cout << "symmetric closure: " << endl;
    d.symmetricClosure().getBooleanMatrix().display();
    cout << "symmetric: " << d.symmetricClosure().isSymmetric() << endl;

    cout << "transitive closure: " << endl;
    d.transitiveClosure().getBooleanMatrix().display();
    cout << "transitive: " << d.transitiveClosure().isTransitive() << endl;

    cout << "composition: " << endl;
    d.composition(pathD).getBooleanMatrix().display();


    delete [] test;
}



void testRelation() {
    cout << "test relation" << endl;
    unsigned int r = 1, c = 1;
    cin >> r >> c;

    BooleanMatrix matrix1(r, c);
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            bool t = true;
            int x;
            cin >> x;
            t = (x == 1) ? 1 : 0;
            matrix1.replace(t, i, j);
        }
    }
    cout << "matrix1:" << endl;
    matrix1.display();
    cout << endl;

    BooleanMatrix matrix2(r, c);
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            bool t = true;
            int x;
            cin >> x;
            t = (x == 1) ? 1 : 0;
            matrix2.replace(t, i, j);
        }
    }
    cout << "matrix2:" << endl;
    matrix2.display();
    cout << endl;

    Relation r1(matrix1);
    r1.getBooleanMatrix().display();
    cout << endl;

    Relation r2(matrix2);
    r2.getBooleanMatrix().display();
    cout << endl;

    r1.complementary().getBooleanMatrix().display();
    cout << endl;
    r1.inverse().getBooleanMatrix().display();
    cout << endl;

    (r1 & r2).getBooleanMatrix().display();
    cout << endl;
    (r1 | r2).getBooleanMatrix().display();
    cout << endl;
}

int main() {
    testBooleanMatrix();
    testDigraph();
    testRelation();
}



