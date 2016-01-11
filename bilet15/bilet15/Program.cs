using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace bilet15
{
    class Program
    {
        static void Main(string[] args)
        {
            MyNetwork net = new MyNetwork();
            try
            {
                net.GetDateFromClients();
            }
            catch (Exception e) { }
            finally { net.Close(); }
            Console.ReadKey();

        }
    }
}
