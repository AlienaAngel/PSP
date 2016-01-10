using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Text.RegularExpressions;

namespace HttpClient
{
    class Program
    {
        static void Main(string[] args)
        {
            byte[] bytes = new byte[1024];
            //IPHostEntry ipHost = Dns.GetHostEntry("localhost");
            IPAddress ipAddr = IPAddress.Parse("127.0.0.1"); //ipHost.AddressList[0];
            IPEndPoint ipEndPoint = new IPEndPoint(ipAddr, 8080);
            Socket sender = new Socket(ipAddr.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
            sender.Connect(ipEndPoint);

            int bytesRec = sender.Receive(bytes);

            String answer = Encoding.UTF8.GetString(bytes, 0, bytesRec);


            Regex r = new Regex(@"\r\n\r\n");
            String[] data = r.Split(answer, 2);

            Console.WriteLine("\nОтвет от сервера: \n{0}\n", data[1] ?? "No Answer");
            Console.ReadKey();
        }
    }
}
