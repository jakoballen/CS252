#include <stdio.h>
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 

#define MAX 257 
#define PORT 9002 
#define SA struct sockaddr 

typedef struct results {
    unsigned short as;
    unsigned short cs;
    unsigned short gs;
    unsigned short ts;
} results;

results countBases(char* dnaString);
void convertNumbers(results* r);

/*
*CS252 - Lab 11
*Author: Jakob Allen (allenjd4061)
*/

// Function designed for chat between client and server. 
void func(int sockfd){
    int i;
    for(i=0; i<3; i++){
        //initialize the buffer and zero the contents
        char buff[MAX];
        bzero(buff, MAX);
        
        // read the message from client and copy it in buffer
        read(sockfd, buff, sizeof(buff));
        
        // parse buffer that contains the client's message
        results r = countBases(buff);
        printf("Output: A: %d, C: %d, G: %d, T: %d\n\n", r.as, r.cs, r.gs, r.ts);
        
        //convert number to client and send it
        convertNumbers(&r);
        write(sockfd,& r, sizeof(r));
    }
} 
  
// Driver function 
int main(){
    int sockfd, connfd, len; 
    struct sockaddr_in servaddr, cli; 
  
    // socket create and verification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created..\n"); 
    bzero(&servaddr, sizeof(servaddr)); 
  
    // assign IP, PORT 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(PORT); 
  
    // Binding newly created socket to given IP and verification 
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
        printf("socket bind failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully binded..\n"); 
  
    // Now server is ready to listen and verification 
    if ((listen(sockfd, 5)) != 0) { 
        printf("Listen failed...\n"); 
        exit(0); 
    } 
    else
        printf("Server listening..\n"); 
    len = sizeof(cli); 
  
    // Accept the data packet from client and verification 
    connfd = accept(sockfd, (SA*)&cli, &len); 
    if (connfd < 0) { 
        printf("server acccept failed...\n"); 
        exit(0); 
    } 
    else
        printf("server acccept the client...\n"); 
  
    // Function for exchanging DNA information
    func(connfd); 
  
    // After chatting close the socket 
    close(sockfd); 
} 

//counts the orruences of each letter in the string
results countBases(char* dnaString){
    results r;
    //set all numbers to zero before incrementing
    r.as = 0;
    r.cs = 0;
    r.gs = 0;
    r.ts = 0;
    
    int i = 0;
    while(dnaString[i] != '\0'){
        if(dnaString[i] == 'A'){
            r.as+=1;
        }else if(dnaString[i] == 'C'){
            r.cs+=1;
        }else if(dnaString[i] == 'G'){
            r.gs+=1;
        }else if(dnaString[i] == 'T'){
            r.ts += 1;
        }
        i++;
    }
    return r;
}

void convertNumbers(results* r){
    r->as = htons(r->as);
    r->cs = ntohs(r->cs);
    r->gs = htons(r->gs);
    r->ts = htons(r->ts);
}
