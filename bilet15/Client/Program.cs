using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Client
{
    class Program
    {
        static void Main(string[] args)
        {
            MyNetwork net = new MyNetwork();
            net.SendDateToServer();

        }
    }
}
