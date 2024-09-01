using System;
using System.Collections.Generic;
using System.Linq;

class Program
{
    static void Main()
    {
        List<double> x = Enumerable.Repeat(0.0, 4).ToList();
        List<List<double>> matrix = new List<List<double>>
        {
            new List<double> {0.79, -0.04,  0.21, -18.0, -1.24},
            new List<double> {0.25, -1.23, 0.18, -0.09, -0.86},
            new List<double> {-0.21,  0.18,  0.80, -0.13,  2.56},
            new List<double> {0.15, -1.31,  0.06,  0.88, 0.79}
        };

        Console.WriteLine("SLAY solutions with Gauss-Jordan method:\n");
        List<double> solution = GaussJordan(matrix, 4);

        Console.WriteLine("Matrix of SLAY solutions: ");
        foreach (double val in solution)
        {
            Console.Write($"{val,8:F3}" + " ");
        }
        Console.WriteLine();

        List<List<double>> A = new List<List<double>>
        {
            new List<double> {0.79, -0.04,  0.21, -18.0},
            new List<double> {0.25, -1.23, 0.18, -0.09},
            new List<double> {-0.21,  0.18,  0.80, -0.13},
            new List<double> {0.15, -1.31,  0.06,  0.88}
        };
        List<double> b = new List<double> {-1.24, -0.86, 2.56, 0.79};

        List<List<double>> C = new List<List<double>>
        {
            new List<double> {0.0, 0.0, 0.0, 0.0},
            new List<double> {0.0, 0.0, 0.0, 0.0},
            new List<double> {0.0, 0.0, 0.0, 0.0},
            new List<double> {0.0, 0.0, 0.0, 0.0}
        };
        List<double> f = Enumerable.Repeat(0.0, 4).ToList();

        FormCanonicalSystem(A, b, C, f, 4);
        CheckSpectralRadius(C);

        Console.WriteLine("\nMethod of simple iterations:");
        SimpleIteration(C, f, x, 4, 0.001);

        Console.WriteLine("x1 = " + x[0].ToString("F3"));
        Console.WriteLine("x2 = " + x[1].ToString("F3"));
        Console.WriteLine("x3 = " + x[2].ToString("F3"));
        Console.WriteLine("x4 = " + x[3].ToString("F3"));
    }

    static List<double> GaussJordan(List<List<double>> AMain, int n)
    {
        List<double> solution = new List<double>(new double[n]);
        List<List<double>> A = AMain.Select(row => row.ToList()).ToList();
        double temp;

        for (int j = 0; j < n; j++)
        {
            for (int i = 0; i < n; i++)
            {
                if (i != j)
                {
                    temp = A[i][j] / A[j][j];
                    for (int k = 0; k < n + 1; k++)
                    {
                        A[i][k] -= A[j][k] * temp;
                        Console.Write($"{A[i][k],8:F3}");
                    }
                    Console.WriteLine();
                }
                else
                {
                    for (int jk = 0; jk < n + 1; jk++)
                        Console.Write($"{A[i][jk],8:F3}");
                    Console.WriteLine();
                }
                
            }
            Console.WriteLine("---------------------------------");
        }

        Console.WriteLine("\n ---------------------------------");
        Console.WriteLine("\n Diagonal  Matrix is:\n");

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n + 1; j++)
                Console.Write($"{A[i][j],8:F3}");
            Console.WriteLine();
        }

        Console.WriteLine("\n ---------------------------------");

        for (int i = 0; i < n; i++)
            solution[i] = A[i][n] / A[i][i];

        return solution;
    }

    static void FormCanonicalSystem(List<List<double>> A, List<double> b, List<List<double>> C, List<double> f, int n)
    {
        for (int i = 0; i < n; i++)
        {
            f[i] = b[i] / A[i][i];
            for (int j = 0; j < n; j++)
            {
                if (j != i)
                {
                    C[i][j] = -A[i][j] / A[i][i];
                }
                else
                {
                    C[i][j] = 0.0;
                }
            }
        }
    }

    static void CheckSpectralRadius(List<List<double>> C)
    {
        double spectralRadius = 0.0;
        for (int i = 0; i < 4; i++)
        {
            double sum = 0.0;
            for (int j = 0; j < 4; j++)
            {
                sum += Math.Abs(C[i][j]);
            }
            if (sum > spectralRadius)
            {
                spectralRadius = sum;
            }
        }

        Console.WriteLine("\nMatrix spectral radius C: " + spectralRadius);

        if (spectralRadius >= 1.0)
        {
            Console.WriteLine("The convergence condition of the simple iteration method is not met.");
        }
        else
        {
            Console.WriteLine("The convergence condition of the simple iteration method is met.");
        }
    }

    static bool SimpleIteration(List<List<double>> C, List<double> f, List<double> x, int n, double epsilon)
    {
        List<double> xNew = new List<double>(new double[n]);
        int k = 0;
        double maxDiff = 0.0;
        int maxIteration = 10;

        for (int i = 0; i < n; i++)
        {
            x[i] = 0.0;
        }

        Console.WriteLine("N" + $"{ "x1",10}" + $"{ "x2",10}" + $"{ "x3",10}" + $"{ "x4",10}" + $"{ "?n",10}");

        do
        {
            for (int i = 0; i < n; i++)
            {
                double sum = f[i];
                for (int j = 0; j < n; j++)
                {
                    sum += C[i][j] * x[j];
                }
                xNew[i] = sum;
            }

            maxDiff = 0.0;
            for (int i = 0; i < n; i++)
            {
                if (Math.Abs(xNew[i] - x[i]) > maxDiff)
                {
                    maxDiff = Math.Abs(xNew[i] - x[i]);
                }
                x[i] = xNew[i];
            }
            k++;

            Console.WriteLine(k + $"{x[0],10:F3}" + $"{x[1],10:F3}" + $"{x[2],10:F3}" + $"{x[3],10:F3}" + $"{maxDiff,10:F3}");
        } while (maxDiff > epsilon && k < maxIteration);

        Console.WriteLine("Number of iterations: " + k);
        if (k == 10)
        {
            Console.WriteLine("(max)");
        }

        if (maxDiff <= epsilon)
        {
            Console.WriteLine("\nThe method converges.");
        }
        else
        {
            Console.WriteLine("\nThe method diverges.");
            return true;
        }
        return false;
    }
}


