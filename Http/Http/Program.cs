using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace Http
{
    class Program
    {
        static void Main(string[] args)
        {
            Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            IPEndPoint address = new IPEndPoint(IPAddress.Any, 8080);
            socket.Bind(address);
            socket.Listen(10);
            //int i = 0;
            //int N = 2;
            //Socket[] clients = new Socket[N];
            while (true)
            {
                Socket client = socket.Accept();

                String template = "HTTP/1.1 200 OK\r\n" +
                                  "Server: NataServer\r\n" +
                                  "Content-Type: text/plain; charset=UTF-8\r\n" +
                                  "Content-Length: {0}\r\n" +
                                  "\r\n" +
                                  "{1}";
                String s = DateTime.Now.ToString();
                String answer = String.Format(template, s.Length, s);
                Console.WriteLine(answer);
                byte[] msg = Encoding.UTF8.GetBytes(answer);
                client.Send(msg);

                client.Shutdown(SocketShutdown.Both);
                client.Close();
            }
        }
    }
}
