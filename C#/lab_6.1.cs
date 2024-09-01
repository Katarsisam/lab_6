using System;
using System.Collections.Generic;
using System.Linq;

class Program
{
    static void Main()
    {
        int N, n, m;
        int X = 1;
        int Summ = 1;
        int fSumm = 0;
        List<List<int>> vec = new List<List<int>>();
        N = int.Parse(Console.ReadLine());
        switch (N)
        {
            case 1:
                n = int.Parse(Console.ReadLine());
                PrintVector(Task1(n));
                break;
            case 2:
                n = int.Parse(Console.ReadLine());
                m = int.Parse(Console.ReadLine());
                PrintVector(Task2(n, m));
                break;
            case 3:
                n = int.Parse(Console.ReadLine());
                m = int.Parse(Console.ReadLine());
                vec = Generator(n, m);
                PrintVector(vec);
                do
                {
                    Summ = Task3(X, vec, n, m);
                    fSumm += Summ;
                    Console.WriteLine($"{Summ} matrixes of {X} size");
                    X++;
                } while (Summ > 0);
                Console.WriteLine($"{fSumm} matrixes at all");
                PrintVector(vec);
                break;
            default:
                break;
        }
    }

    static List<List<int>> Task1(int n)
    {
        Random rand = new Random();
        List<List<int>> vec = new List<List<int>>(n);
        for (int i = 0; i < n; i++)
        {
            vec.Add(new List<int>(new int[n]));
            for (int j = 0; j < n; j++)
            {
                int cass = rand.Next(-50, 51);
                if ((j + 1) % 2 == 0)
                {
                    while (Math.Abs(cass) <= 10)
                    {
                        cass = rand.Next(-50, 51);
                    }
                }
                vec[i][j] = cass;
            }
        }
        return vec;
    }

    static List<List<int>> Task2(int n, int m)
    {
        Random rand = new Random();
        List<List<int>> vec = new List<List<int>>(n);
        for (int i = 0; i < n; i++)
        {
            vec.Add(new List<int>(new int[m]));
            for (int j = 0; j < m; j++)
            {
                int cass = rand.Next(-100, 101);
                vec[i][j] = cass;
                Console.Write($"{vec[i][j],4}|");
            }
            Console.WriteLine();
        }
        Console.WriteLine();

        for (int i = 0; i < m; i++)
        {
            int counter = 0;
            for (int j = 0; j < n; j++)
            {
                if (vec[j][i] > 0) counter++;
                else if (vec[j][i] < 0) counter--;
            }

            if (counter > 0)
            {
                List<int> vecX = new List<int>();
                for (int j = 0; j < n / 2; j++)
                    vecX.Add(vec[j][i]);
                vecX.Sort();
                for (int j = 0; j < n / 2; j++)
                    vec[j][i] = vecX[j];
            }
            else if (counter < 0)
            {
                for (int j = 0; j < n; j++)
                    vec[j][i] = vec[j][i] * vec[j][i];
            }
            else if (counter == 0)
            {
                for (int j = 0; j < n; j++)
                {
                    vec[j][i] = 0;
                }
            }
        }
        return vec;
    }

    static int Task3(int X, List<List<int>> vec, int n, int m)
    {
        int counter = 0;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                if (i != 0 && j != 0 && vec[i][j] != 0)
                    vec[i][j] = Math.Min(Math.Min(vec[i][j], vec[i - 1][j - 1]), Math.Min(vec[i][j - 1], vec[i - 1][j])) + 1;
                if (vec[i][j] == X)
                {
                    counter++;
                }
            }
        return counter;
    }

    static void PrintVector(List<List<int>> vec)
    {
        foreach (var row in vec)
        {
            foreach (var item in row)
                Console.Write($"{item,5}|");
            Console.WriteLine();
        }
    }

    static List<List<int>> Generator(int n, int m)
    {
        Random rand = new Random();
        List<List<int>> vecX = new List<List<int>>(n);
        for (int i = 0; i < n; i++)
        {
            vecX.Add(new List<int>(new int[m]));
            for (int j = 0; j < m; j++)
            {
                int cass = rand.Next(0, 2);
                vecX[i][j] = cass;
            }
        }
        return vecX;
    }
}

