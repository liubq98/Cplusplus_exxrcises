#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <string.h>
using namespace std;

class Matrix {
    public:
        Matrix() {
            name = "";
            width = height = 0;
            param = NULL;
        }
        Matrix(string, int, int, int**);
        Matrix(const Matrix &);
        ~Matrix();
        void setName(string newName) {
            name = newName;
        }
        string getName() {
            return name;
        }
        void print() {
            cout << name << " = [\n";
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    if (j == width-1) cout << param[i][j];
                    else cout << param[i][j] << ", ";
                }
                cout << "\n";
            }
            cout << "]\n";
        }
        // overload operator
        bool operator ==(const Matrix&);
        bool operator !=(const Matrix&);
        void operator +=(const Matrix&);
        void operator -=(const Matrix&);
        Matrix operator *(const Matrix&);
    private:
        string name;
        int width, height, **param;
};

#endif




Matrix::Matrix(string str, int hei, int wid, int** par){
	name = str;
	width = wid;
	height = hei;
	param = new int*[height];
	for(int i = 0; i < height; i++)
	{
		param[i] = new int[width];
	} 
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			param[i][j] = par[i][j];
		}
	}
}

Matrix::Matrix(const Matrix & mat){
	name = mat.name;
	width = mat.width;
	height = mat.height;
	param = new int*[height];
	for(int i = 0; i < mat.height; i++)
	{
		param[i] = new int[width];
	}
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			param[i][j] = mat.param[i][j];
		}
	}
}

Matrix::~Matrix(){
	for(int i = 0; i < height; i++)
	{
		delete []param[i];
	}
	delete []param;
}

        
// overload operator
bool Matrix::operator ==(const Matrix& mat){
	if((height != mat.height) || (width != mat.width))
	{
		return false;
	}
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			if(param[i][j] != mat.param[i][j])
			{
				return false;
			}
		}
	}
return true;
}

bool Matrix::operator !=(const Matrix& mat){
	if((height != mat.height) || (width != mat.width))
	{
		return true;
	}
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			if(param[i][j] != mat.param[i][j])
			{
				return true;
			}
		}
	}
return false;
}

void Matrix::operator +=(const Matrix& mat){
	if((height != mat.height) || (width != mat.width))
	{
		cout << "invalid addition." << endl;
		return;
	}
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			param[i][j] += mat.param[i][j];
		}
	}
}

void Matrix::operator -=(const Matrix& mat){
	if((height != mat.height) || (width != mat.width))
	{
		cout << "invalid substraction." << endl;
		return;
	}
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			param[i][j] -= mat.param[i][j];
		}
	}
}

Matrix Matrix::operator *(const Matrix& mat){
	Matrix mat2;
	if(width != mat.height)
	{
		cout << "invalid multiplication." << endl;
		return mat2;
	}
	
	mat2.name = "newMat";
	mat2.height = height;
	mat2.width = mat.width;
	mat2.param = new int*[height];
	for(int i = 0; i < height; i++)
	{
		mat2.param[i] = new int[mat2.width];
		for(int j = 0; j < mat2.width; j++)
		{
			mat2.param[i][j] = 0;
		}
	}
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < mat2.width; j++)
		{
			for(int k = 0; k < width; k++)
			{
				mat2.param[i][j] += param[i][k]*mat.param[k][j];
			}
		}
	}
return mat2;
}


#include <iostream>
using namespace std;

int main() {
    int h1, w1, h2, w2, n;
    string name1 = "Mat1";
    string name2 = "Mat2";
    cin >> h1 >> w1;
    int **mat1_arr = new int*[h1];
    for (int i = 0; i < h1; i++) {
        mat1_arr[i] = new int[w1];
        for (int j = 0; j < w1; j++) {
            cin >> mat1_arr[i][j];
        }
    }
    cin >> h2 >> w2;
    int **mat2_arr = new int*[h2];
    for (int i = 0; i < h2; i++) {
        mat2_arr[i] = new int[w2];
        for (int j = 0; j < w2; j++) {
            cin >> mat2_arr[i][j];
        }
    }
    Matrix mat1 = Matrix(name1, h1, w1, mat1_arr);
    mat1.print();
    Matrix mat2 = Matrix(name2, h2, w2, mat2_arr);
    mat2.print();
    cout << "\n(Mat1 += Mat2) addition result:\n";
    mat1 += mat2;
    mat1.print();
    cout << "\n(Mat1 -= Mat2) substraction result:\n";
    mat1 -= mat2;
    mat1.print();
    cout << "\n(Mat1 * Mat2) production result:\n";
    Matrix mat3 = mat1 * mat2;
    if (mat3.getName() != "") mat3.print();
    for (int i = 0; i < h1; i++) {
        delete [] mat1_arr[i];
    }
    delete [] mat1_arr;
    for (int i = 0; i < h2; i++) {
        delete [] mat2_arr[i];
    }
    delete []mat2_arr;
    return 0;
}

