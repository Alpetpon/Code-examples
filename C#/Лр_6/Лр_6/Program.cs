using System;
using System.Runtime.InteropServices;

class Program
{
    [DllImport("linear_equations_solver.dll")]
    public static extern void solveLinearEquations(double[] matrixData, double[] rightHandSide, int matrixOrder, double[] solution);

    static void Main()
    {

        int matrixOrder = 3;
        double[] matrixData = { 1, 2, 3, 4, 5, 6, 7, 8, 10 };
        double[] rightHandSide = { 1, 2, 3 };
        double[] solution = new double[matrixOrder];

        solveLinearEquations(matrixData, rightHandSide, matrixOrder, solution);

        Console.WriteLine("Solution:");
        foreach (var val in solution)
        {
            Console.WriteLine(val);
        }
    }
}
