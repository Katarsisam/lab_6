
#include <vector>
#include<iostream>
#include<iomanip>
#include<cmath>

using namespace std;
vector<double> gaussJordan(vector<vector<double>> AMain,  int n);
void formCanonicalSystem(const vector<vector<double>>& A, const vector<double>& b, vector<vector<double>>& C, vector<double>& f, int n);
bool simpleIteration(const vector<vector<double>>& C, const vector<double>& f, vector<double>& x, int n, double epsilon);
void checkSpectralRadius(vector<vector<double>>& C);
int main()
{    
    vector<double> x(4, 0.0);
	 vector<vector<double>> matrix = {
        {0.79, -0.04,  0.21, -18.0, -1.24},
        { 0.25, -1.23, 0.18, -0.09, -0.86},
        {-0.21,  0.18,  0.80, -0.13,  2.56},
        { 0.15, -1.31,  0.06,  0.88, 0.79}
    };

    cout << "SLAY solutions with Gauss-Jordan method:\n" << endl;
    vector<double> solution = gaussJordan(matrix, 4);


    cout << "Matrix of SLAY solutions: " << endl;
    for (double x : solution) {
        cout << x << " ";
    }
    cout << endl;

    vector<vector<double>> A = {
        {0.79, -0.04,  0.21, -18.0},
        { 0.25, -1.23, 0.18, -0.09},
        {-0.21,  0.18,  0.80, -0.13},
        { 0.15, -1.31,  0.06,  0.88}
    };
    vector<double> b = {-1.24, -0.86, 2.56, 0.79};
   
    vector<vector<double>> C = {
        { 0.0, 0.0, 0.0, 0.0},
        { 0.0, 0.0, 0.0, 0.0},
        { 0.0, 0.0, 0.0, 0.0},
        { 0.0, 0.0, 0.0, 0.0}
    };
    vector<double> f(4, 0.0);

    formCanonicalSystem(A, b, C, f, 4);
    checkSpectralRadius(C);


    cout << "\nMethod of simple iterations:" << endl;
    simpleIteration(C, f, x, 4, 0.001);

    cout << "x1 = " << fixed << setprecision(3) << x[0] << endl;
    cout << "x2 = " << fixed << setprecision(3) << x[1] << endl;
    cout << "x3 = " << fixed << setprecision(3) << x[2] << endl;
    cout << "x4 = " << fixed << setprecision(3) << x[3] << endl;
    

return 0;
}


vector<double> gaussJordan(vector<vector<double>> AMain,  int n){
    vector<double> solution(n);
    vector<vector<double>> A = AMain;
	float temp;
	int i,j,k;

	

	cout<<fixed;
	for(j=0; j<n; j++){

		for(i=0; i<n; i++)
		if(i!=j)
		{
			temp=A[i][j]/A[j][j];

			for(k=0; k<n+1; k++){
				A[i][k]-=A[j][k]*temp;
                cout<<setw(8)<<setprecision(3)<<A[i][k];}
            cout<<endl;
           
		}else{
            for(int jk=0; jk<n+1; jk++)
		        cout<<setw(8)<<setprecision(3)<<A[i][jk];
		    cout<<endl;
        }
        cout<<"\n ---------------------------------\n";
        
    }
	cout<<"\n ---------------------------------\n";
	cout<<"\n Diagonal  Matrix is:\n\n";

	for(i=0; i<n; i++)
	{
		for(j=0; j<n+1; j++)
		cout<<setw(8)<<setprecision(3)<<A[i][j];
		cout<<endl;
	}

	
	cout<<"\n ---------------------------------\n";

	for(i=0; i<n; i++)
	    solution[i] = A[i][n]/A[i][i];

    return solution;

}

void formCanonicalSystem(const vector<vector<double>>& A, const vector<double>& b, vector<vector<double>>& C, vector<double>& f, int n) {
    for (int i = 0; i < n; i++) {
        f[i] = b[i] / A[i][i];
        for (int j = 0; j < n; j++) {
            if (j != i) {
                C[i][j] = -A[i][j] / A[i][i];
            } else {
                C[i][j] = 0.0;
            }
        }
    }
}


void checkSpectralRadius(vector<vector<double>>& C){
    double spectralRadius = 0.0;
    for (int i = 0; i < 4; i++) {
        double sum = 0.0;
        for (int j = 0; j < 4; j++) {
            sum += fabs(C[i][j]);
        }
        if (sum > spectralRadius) {
            spectralRadius = sum;
        }
    }

    cout << "\nMarix spetral radius C: " << spectralRadius << endl;

    if (spectralRadius >= 1.0) {
        cout << "The convergence condition of the simple iteration method is not met." << endl;
    } else {
        cout << "The convergence condition of the simple iteration method is met." << endl;
    }
}


//метод простых итераций
bool simpleIteration(const vector<vector<double>>& C, const vector<double>& f, vector<double>& x, int n, double epsilon) {
    vector<double> xNew(n);
    int k = 0;
    double maxDiff = 0.0;
    int maxIteration = 10;

    // Задаем начальное приближение
    for (int i = 0; i < n; i++) {
        x[i] = 0.0;
    }

    cout << "N" << setw(10) << "x1" << setw(10) << "x2" << setw(10) << "x3" << setw(10) << "x4" << setw(10) << "?n" << endl;

    do {
        // Вычисляем новое приближение
        for (int i = 0; i < n; i++) {
            double sum = f[i];
            for (int j = 0; j < n; j++) {
                sum += C[i][j] * x[j];
            }
            xNew[i] = sum;
        }

        // Проверяем условие остановки
        maxDiff = 0.0;
        for (int i = 0; i < n; i++) {
            if (fabs(xNew[i] - x[i]) > maxDiff) {
                maxDiff = fabs(xNew[i] - x[i]);
            }
            x[i] = xNew[i];
        }
        k++;

        // Вывод результатов в таблицу
        cout << k << fixed << setprecision(3) << setw(10) << x[0] << setw(10) << x[1] << setw(10) << x[2] << setw(10) << x[3] << setw(10) << maxDiff << endl;
    } while (maxDiff > epsilon && k < maxIteration);

    cout << "Number of iterations: " << k;
    if (k == 10){
        cout << "(max)";
    }

    // Вывод сообщения о сходимости или расходимости
    if (maxDiff <= epsilon) {
        cout << "\nThe method converges." << endl;
    } else {
        cout << "\nThe method diverges." << endl;
        return 1;
    }
    return 0;
}
