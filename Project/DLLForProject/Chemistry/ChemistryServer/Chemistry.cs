using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace ManagedServerForInterop
{
    //public interface IMath
    public interface IChem
    {
        //int MultiplicationValue { get; set; }
        //int DivisionValue { get; set; }
        double HeatVal { get; set; }
        double RefVal { get; set; }
        double ACVal { get; set; }

        //int MultiplicationOfTwoIntegers(int num1, int num2);
        //int DivisionOfTwoIntegers(int num1, int num2);

        double HeatCalculation(double w, double q1);
        double RefCalculation(double q2, double w);
        double ACCalculation(double q1, double w);

    }/* end interface IMath */

    [ClassInterface(ClassInterfaceType.AutoDual)]
    public class Chemistry:IChem
    //public class Math:IMath
    {
        //public int MultiplicationValue { get; set; }
        //public int DivisionValue { get; set; }

        public double HeatVal { get; set; }
        public double RefVal { get; set; }
        public double ACVal { get; set; }


        public Chemistry()
        {
            //empty
        }
        //public int MultiplicationOfTwoIntegers(int num1, int num2)
        //{
        //    MultiplicationValue = num1 * num2;
        //    MessageBox.Show("Multiplication of two integers " + MultiplicationValue);
        //    return MultiplicationValue;
        //}

        //public int DivisionOfTwoIntegers(int num1, int num2)
        //{
        //    DivisionValue = num1 / num2;
        //    MessageBox.Show("Division of two integers " + DivisionValue);
        //    return DivisionValue;
        //}

        public double HeatCalculation(double w, double q1)
        {
            HeatVal = w / q1;
            return HeatVal;
        }

        public double RefCalculation(double q2, double w)
        {
            RefVal = q2 / w;
            return RefVal;
        }

        public double ACCalculation(double q1, double w)
        {
            ACVal = q1 / w;
            return ACVal;
        }
    }
}
