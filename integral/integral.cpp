//g++ -Wall -o "%e" "%f" -lwsock32
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <math.h>

#define PORT 9999

double f(double x) {
	return sin(x);
}

double calc(double a, double b) {
	//return - a + b;
	double step = (b-a)/1000;
	double s = 0;
	for(double x = a;x<(b-step/2);x+=step)
	{
		s+= 0.5*step*(f(x) + f(x+step)); 
	}	
	
	return s;
}

int server(char *ip, int n, double a, double b) {
	printf(">> server >> %s %d %lf %lf\n",ip, n,a,b);
    char sendbuff[1024];
	if (WSAStartup(0x0202,(WSADATA *) &sendbuff[0])) 
    {
        printf("Error WSAStartup %d\n", WSAGetLastError());
        return -1;
    }
    
    SOCKET servSock;
    if ((servSock=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        printf("Error socket %d\n",WSAGetLastError());
        WSACleanup();
        return -1;
    }
    
    struct sockaddr_in local_addr;
    local_addr.sin_family=AF_INET;
    local_addr.sin_port=htons(PORT);
    local_addr.sin_addr.s_addr=0;
    
    if (bind(servSock,(struct sockaddr *) &local_addr,sizeof(local_addr)))
    {
      
      printf("Error bind %d\n",WSAGetLastError());
      closesocket(servSock);  
      WSACleanup();
      return -1;
    }
    
    if (listen(servSock, 4))
    {
      printf("Error listen %d\n",WSAGetLastError());
      closesocket(servSock);
      WSACleanup();
      return -1;
    }
    
    const int N_CLIENTS = n;
    SOCKET client_sockets[N_CLIENTS];    
    struct sockaddr_in client_addr;    
    int client_addr_size=sizeof(client_addr);
    int nclients = 0;
    
    while(nclients<N_CLIENTS) {
        client_sockets[nclients++]=accept(servSock, (struct sockaddr *)&client_addr, &client_addr_size);
        printf("client %d connected\n",nclients);
    }
    
    
    double dx = (b - a)/N_CLIENTS;
    
    for(int i = 0; i< N_CLIENTS; i++)
    {
		sprintf(sendbuff,"%lf",a+i*dx);
        send(client_sockets[i], &sendbuff[0], sizeof(sendbuff), 0);
        sprintf(sendbuff,"%lf",a+dx*(i+1));
        send(client_sockets[i], &sendbuff[0], sizeof(sendbuff), 0);
	}
	
	double res = 0;
	for(int i = 0; i< N_CLIENTS; i++)
    {
        recv(client_sockets[i], &sendbuff[0], sizeof(sendbuff), 0);
        res += atof(sendbuff);
	}
	printf("res = %lf\n",res);
    
	return 0;
}

int client(char *ip) {
	printf(">> client >> %s\n",ip);
	char buff[1024];
    
    if (WSAStartup(0x0202,(WSADATA *)&buff[0]))
    {
      printf("WSAStart error %d\n",WSAGetLastError());
      return -1;
    }
    
    SOCKET servSock;
    servSock=socket(AF_INET,SOCK_STREAM,0);
    
    if (servSock < 0)
    {
      printf("Socket() error %d\n",WSAGetLastError());
      return -1;
    }
    
    struct sockaddr_in dest_addr;
    dest_addr.sin_family=AF_INET;
    dest_addr.sin_port=htons(PORT);
    
    HOSTENT *hst;
    if (inet_addr(ip)!=INADDR_NONE) {
      dest_addr.sin_addr.s_addr=inet_addr(ip);
    } else {
      if ((hst=gethostbyname(ip)))
      ((unsigned long *)&dest_addr.sin_addr)[0]=((unsigned long **)hst->h_addr_list)[0][0];
      else 
      {
        printf("Invalid address %s\n",ip);
        closesocket(servSock);
        WSACleanup();
        return -1;
      }
    }
    
    if (connect(servSock,(struct sockaddr *)&dest_addr,sizeof(dest_addr))) {
        printf("Connect error %d\n",WSAGetLastError());
        return -1;
    }
    
     recv(servSock, &buff[0], sizeof(buff), 0);
     double a = atof(buff);
     recv(servSock, &buff[0], sizeof(buff), 0);
	 double b = atof(buff);
    
    double result = calc(a,b);
    
    sprintf(buff, "%lf", result);
    send(servSock, buff, sizeof(buff), 0);
    
	return 0;
}

int main(int argc, char *argv[]) {
	
	if( argc < 2 ) {
      printf("Illegarl argument count integral 0|1 127.0.0.1 N a b\n");
      return -1;
	}
   
  	int isServer = atoi(argv[1]);
  	char *ipString = argv[2];
  	
  	printf("%s\n", ipString);
	
	if(isServer) {
		
		if( argc < 5 ) {
		  printf("Illegarl argument count integral 0|1 127.0.0.1 N a b\n");
		  return -1;
		}
		
		int n = atoi(argv[3]);
		double a = atof(argv[4]);
		double b = atof(argv[5]);
		server(ipString, n, a,b);
	} else {
		client(ipString);
	}
	
	return 0;
}
