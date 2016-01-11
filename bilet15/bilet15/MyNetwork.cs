using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;

namespace bilet15
{
    class MyNetwork
    {
        Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        byte[] bytes = new byte[1024];
        IPEndPoint address = new IPEndPoint(IPAddress.Any, 8088);

        public MyNetwork()
        {
            socket.Bind(address);
            socket.Listen(10);

        }

        public void GetDateFromClients()
        {
            while (true)
            {
                Socket client = socket.Accept();
                int bytesRec = client.Receive(bytes);
                String answer = Encoding.UTF8.GetString(bytes, 0, bytesRec);
                Console.WriteLine(answer);
            }

        }

        public void Close()
        {
            socket.Shutdown(SocketShutdown.Both);
            socket.Close();
        }


    }
}
