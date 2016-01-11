using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;

namespace Client
{
    public class MyNetwork
    {
        byte[] bytes = new byte[1024];
        static IPAddress ipAddr = IPAddress.Parse("127.0.0.1");
        Socket sender;

        public MyNetwork()
        {
            IPEndPoint ipEndPoint = new IPEndPoint(ipAddr, 8088);
            sender = new Socket(ipAddr.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
            sender.Connect(ipEndPoint);
        }

        public void SendDateToServer()
        {
            String answer = DateTime.Now.ToString();
            Console.WriteLine(answer);
            byte[] msg = Encoding.UTF8.GetBytes(answer);
            sender.Send(msg);
        }
    }
}
