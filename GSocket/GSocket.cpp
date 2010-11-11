//C-
//C- This software is subject to, and may be distributed under, the
//C- GNU General Public License, either Version 2 of the license,
//C- or (at your option) any later version. The license should have
//C- accompanied the software or you may obtain a copy of the license
//C- from the Free Software Foundation at http://www.fsf.org .
//C-
//C- This program is distributed in the hope that it will be useful,
//C- but WITHOUT ANY WARRANTY; without even the implied warranty of
//C- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//C- GNU General Public License for more details.
//C-
# include "GSocket.h"
# include "config.h"
#include <string.h>
#include <stdio.h>


namespace ocr{
	GSocket::GSocket(){
	}
	
	void GSocket::destroy(void)
	{
	}
	
	
/******** pipeLine() *********************
 There is a separate instance of this function 
 for each connection.  It handles all communication
 once a connnection has been established. 
 Socket client can be C++, PHP script or Flash 
 Socket data is XML based
 *****************************************/

int GSocket::pipeLineXML (commandData *inputData, int sockfd){
#ifdef MACOS
	int n;
	char buffer[MAXDATASIZE];
	//char buffer_send[MAXDATASIZE_SEND];
	//char bufMode[5];
	int print=1;
	string srcLine,destLine,dataStr, postData;
	while(1){
		//cout<<"start pipe "<<END;
		bzero(buffer,MAXDATASIZE);
		n = recv(sockfd,buffer,MAXDATASIZE,0);
		//cout<<"get msg"<<END;
		//n = read(sock,buffer,255);		
		if (n <= 0){
			cout<<"ERROR reading from socket"<<END;
		    //exit(0);
			return 0;
		}
		dataStr=buffer;
		if(!dataStr.size())return 0;
		DT("        get message0:"<<buffer<<END);

		destLine=processInput(inputData,dataStr);
        if(destLine.size()){
			DT("        send1 msg size="<<destLine.size()<<END);
			char *buffer_=(char*)malloc(destLine.size()+10);
			bzero(buffer_,destLine.size()+10);
			memcpy(buffer_, destLine.c_str(), destLine.size());
			//n = send(sockfd,buffer_send,MAXDATASIZE_SEND,0);            /* no flags used         */
			n = send(sockfd,buffer_,destLine.size(),0);            /* no flags used         */
			////sleep(1);
			//n = write(sock,buffer,255);
			if (n <= 0) error("ERROR writing to socket");
		}
		/*if(inputData->data["m"]=="draw"||
		   inputData->data["m"]=="save"||
		   inputData->data["m"]=="free"||
		   inputData->data["m"]=="main"||
		   inputData->data["m"]=="test"||
		   inputData->data["m"]=="plus"){
		   destLine="StartOCR";
		   writeText(destLine,"signal.xml");
		}
		*/
		return 0;
			
	}
#endif
	return 0;
}//__________________________________________________________________





#ifdef MACOS
/* A simple server in the internet domain using TCP
 The port number is passed as an argument
 This version runs forever, forking off a separate
 process for each connection
 gcc server2.c -lsocket
 */
int GSocket::startSocketServer(commandData *inputData){

	int sockfd, newsockfd, portno, clilen, pid;
	struct sockaddr_in serv_addr, cli_addr;
	int print=1;
	int status;
	//if (argc < 2) {
	//	fprintf(stderr,"ERROR, no port provided\n");
	//	exit(1);
	//}
	GImageEditor *imageEditor=(GImageEditor*)inputData->imageEditor;
	GLogicProcessor *logicProcessor=(GLogicProcessor*)inputData->logicProcessor;
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) error("ERROR opening socket");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = PORT;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) error("ERROR on binding");
	listen(sockfd,5);
	clilen = sizeof(cli_addr);
	cout <<"start listen "<<PORT<<END;
	while (1) {
		while (1) {
			newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t*)&clilen);
			if (-1==newsockfd) {
				perror("ERROR1 on accept");
				if (EINTR==errno) {
					continue; /* Restart accept */
				}
				else {
					perror("Ouch ouch accept");
					exit(0);//end_of_the_show=TRUE;
				}
			}
			else {
				break;
				//process_connection(sock);
			}
			cout<<".";
		}	
		
		pid = fork();   //create child process for handle socket connection
		if (pid < 0)error("ERROR on fork");
		if (pid == 0)  {  //in child process
			pipeLineXML(inputData, newsockfd);
			DT("close socket."<<END);
			close(newsockfd);
			exit(0);
		}else close(newsockfd);
		//in parent process wait exit code of child;
		if(pid)waitpid(pid, &status,0);
		
		string str=readText("signal.xml");
		if(str=="StartOCR"){ //need reload data;
			str=""; writeText(str, "signal.xml");
			imageEditor->readInputAction(inputData);
		} 
		
		
		
	} /* end of while */

	return 0; /* we never get here */
}
	
	
int sendText(const char *data, int size){
				
				int sockfd=0, portno, n;
				struct sockaddr_in serv_addr;
				static struct hostent *server;
				//int print=0;
					portno = PORT;
					sockfd = socket(AF_INET, SOCK_STREAM, 0);
					if (sockfd < 0){
					    error("ERROR opening socket");
						return 0;
					}
					server = gethostbyname("localhost");
					if (server == NULL) {
						fprintf(stderr,"ERROR, no such host\n");
						return 0;
					}
					bzero((char *) &serv_addr, sizeof(serv_addr));
					serv_addr.sin_family = AF_INET;
					bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
					serv_addr.sin_port = htons(portno);
					if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0){
					   error("ERROR connecting");
					   close(sockfd);
					   return 0;	
					}

				
				n = send(sockfd,data,size,0);            /* no flags used         */
	            if (n <= 0) error("ERROR writing to socket");
				close(sockfd);
				return n;
	
};
	
/** Open socket connection and send string by socket (wrapper)*/
int GSocket::sendTextBySocket(const char *data){
	int n=sendText(data, strlen(data));
	return n;
}
	
/** Open socket connection and send string by socket (wrapper)*/
int GSocket::sendTextBySocket(string &data){
	int n=sendText(data.c_str(), data.size());
	return n;
}
	
#endif


#ifdef WIN32
	//http://support.microsoft.com/kb/830597
HANDLE hRecvEvent;

DWORD WINAPI NormalHandler(LPVOID inputData_){
	int nErr,nRecv_len;
	int print=1;
	BYTE buffer[2048];   //MAXDATASIZE
	fd_set fdread;

	commandData *inputData=(commandData *)inputData_;
	SOCKET remoteSocket=(SOCKET)(inputData->socketFD);

	//printf("Waiting");
	//for (int i=0; i<10; i++) {
	//		printf("*");
	//	Sleep(1000);
	//}
	//DT("Normal handler ready!\n");

	//while(1) {
		//Always clear the set before you call the select method.
		FD_ZERO(&fdread);
		//Add sockets to the sets.
		FD_SET(remoteSocket, &fdread);

		nErr=select(0,&fdread,0,0,0);

		if(nErr==SOCKET_ERROR){
			//printf("Select() failed: %d\n",WSAGetLastError());
			closesocket(remoteSocket);
			return 1;
		}

		if(FD_ISSET(remoteSocket,&fdread)){
			WaitForSingleObject(hRecvEvent,INFINITE);
			//nRecv_len=recv(remoteSocket,(char *)&buffer,sizeof(buffer) - 1,0);
			int dataSize=1; nRecv_len=0;
			memset(buffer,0,sizeof(buffer));
			dataSize=recv(remoteSocket,(char *)&buffer,2048,0);
			//buffer[dataSize] = '\0';
			//printf("dataSize=%d",dataSize);//<<" bufer="<<buffer<<endl);
			///while(dataSize!=SOCKET_ERROR&&dataSize>0&&count<10){
			//	  recv(remoteSocket,(char *)&buffer,sizeof(buffer),0);
			//	  cout<<"dataSize="<<dataSize<<" bufer="<<buffer<<endl;
			//	  count++ ;
			//      nRecv_len+=dataSize;
			//}


			if (dataSize==SOCKET_ERROR) {
				//printf("Recv() failed. Win32 error is 0x%lx\n", WSAGetLastError());
				closesocket(remoteSocket);
				return 1;
			}

			if(dataSize!=0){
				string dataStr=(char*)buffer;

				string destString=processInput(inputData,dataStr);
				//char *data=(char*)malloc(destString.size());
				//memcpy(data,destString.c_str(),destString.size());

				//DT("size="<<destString.size());
				if(destString.size()){
					int count=send(remoteSocket,destString.c_str(),destString.size(),0);
					if(destString.size()>100000)Sleep(1000);
					//DT("send "<<count);
					if (count <= 0) error("ERROR writing to socket");

				}
				closesocket(remoteSocket); //DT("close\n");
				//break;
			}else{
			  //printf("Connection Closed!\n");
			  closesocket(remoteSocket); //DT("close\n");
			 //break;

			}
		}

	//}
	//closesocket(remoteSocket);
	return 0;
}

int startSocket(commandData *inputData){

	WSADATA wsaData;
	int nErr;
	SOCKET myListener = INVALID_SOCKET;
	struct sockaddr_in localIp;
	unsigned short nPort;
	DWORD dwThreadId;
	HANDLE hThread=NULL;
	//DWORD (WINAPI *pfn)(LPVOID);
	//pfn=NormalHandler;

	nPort =PORT ;

	nErr = WSAStartup(MAKEWORD(2,0),&wsaData);
	assert(nErr==0);
	assert(wsaData.wVersion == MAKEWORD(2,0));

	myListener = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	assert(myListener!=INVALID_SOCKET);

	// Bind the listen socket to any local IP address.
	localIp.sin_family = AF_INET;
	localIp.sin_port = htons(nPort);;
	localIp.sin_addr.S_un.S_addr = INADDR_ANY;

	nErr = bind(myListener,(SOCKADDR *)&localIp,sizeof(localIp));
	assert(nErr!=SOCKET_ERROR);

	nErr = listen(myListener, 5);
	assert(nErr==0);

	//Create a manual-reset event object.
	hRecvEvent=CreateEvent(NULL,TRUE,TRUE,"RecvEvent");
	if (hRecvEvent == NULL)
	{
		printf("CreateEvent failed with error 0x%lx\n", GetLastError());
		return 1;
	}

	printf("The server is ready!\n");

	while (1) {
		struct sockaddr_in remoteIp;
		SOCKET remoteSocket = INVALID_SOCKET;
		int nAddrLen = sizeof(SOCKADDR);

		remoteSocket = accept(myListener, (SOCKADDR *)(&remoteIp), &nAddrLen);
		if(remoteSocket == INVALID_SOCKET) {
			int error = WSAGetLastError();
			printf("Accept() failed. Win32 error is 0x%lx\n", GetLastError());
			//goto Cleanup;
		} else {
			// cout<<"New connect\n";
			//printf("Connected from %d.%d.%d.%d:%d\n",
			//	remoteIp.sin_addr.S_un.S_un_b.s_b1,
			//	remoteIp.sin_addr.S_un.S_un_b.s_b2,
			//	remoteIp.sin_addr.S_un.S_un_b.s_b3,
			//	remoteIp.sin_addr.S_un.S_un_b.s_b4,
			//	ntohs(remoteIp.sin_port));

			  inputData->socketFD=remoteSocket;

			  hThread=CreateThread(0,
								   0,
								   NormalHandler,
								   (LPVOID)inputData,
								   0,
								   &dwThreadId
								   );
			  //unsigned int
			  //hThread=_beginthreadex(0,
			   //						0,
			   //						NormalHandler,
			   //						(LPVOID)inputData,
			   //						0,
			   //						&dwThreadId
			   //						);



			if(hThread==0){
				printf("CreateThread() failed: %d\n",GetLastError());
				return 1;
			}
			Sleep(100);
			CloseHandle(hThread);
			string str=readText("signal.xml");
			if (str=="StartOCR") {
                str=""; writeText(str,"signal.xml");
				GImageEditor *imageEditor=(GImageEditor*)inputData->imageEditor;
				imageEditor->readInputAction(inputData);
			}

			//_endthread(hThread);

		}
	}
	closesocket(myListener);

Cleanup:
	WSACleanup();
	return 0;


};


int GSocket::startSocketServer(commandData *inputData){

	startSocket(inputData);
	return 0;


};

/** Open socket connection and send string by socket*/
int sendText(const char *data, int size){

	int nErr, nSize;
	WSADATA wsaData;
	SOCKET myOOBSocket = INVALID_SOCKET;
	SOCKET myNormalSocket = INVALID_SOCKET;
	unsigned short nPort=PORT; // Listen for the port number.
	struct sockaddr_in remoteIp;

	// The Init Socket API.
	nErr = WSAStartup(MAKEWORD(1,1),&wsaData);
	assert(nErr==0);

	//myOOBSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	//assert(myOOBSocket!=INVALID_SOCKET);

	myNormalSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	assert(myNormalSocket!=INVALID_SOCKET);

	// Connect to the remote address.
	remoteIp.sin_family = AF_INET;
	remoteIp.sin_port = htons(nPort);;
	remoteIp.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

		// Bind the listen socket to any local IP address.
	//localIp.sin_family = AF_INET;
	//localIp.sin_port = htons(nPort);;
	//localIp.sin_addr.S_un.S_addr = INADDR_ANY;


	nErr = connect(myNormalSocket, (SOCKADDR *)&remoteIp, sizeof(remoteIp));
	if (nErr == SOCKET_ERROR) {
		int error = WSAGetLastError();
		printf("Connect failed because of %lX\n", error);
		goto Cleanup;
	}

	nSize = send(myNormalSocket, data,size, 0);
	if (nSize == SOCKET_ERROR) {
		printf("Send failed because of %lX\n", WSAGetLastError());
		goto Cleanup;
	}

	Sleep(1000);
Cleanup:
	if (myNormalSocket!=INVALID_SOCKET)
		closesocket(myNormalSocket);
	WSACleanup();
	return nSize;
}

/** Open socket connection and send string by socket (wrapper)*/
int GSocket::sendTextBySocket(const char *data){
	sendText(data, strlen(data));
}

/** Open socket connection and send string by socket (wrapper)*/
int GSocket::sendTextBySocket(string &data){
	sendText(data.c_str(), data.size());
}
#endif

};













