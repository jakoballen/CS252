#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#define MAX 257
#define PORT 9002 
#define SA struct sockaddr 

typedef struct results {
    unsigned short as;
    unsigned short cs;
    unsigned short gs;
    unsigned short ts;
} results;
void convertNumbers(results* r);

/*
 *CS252 - Lab 11
 *Author: Jakob Allen (allenjd4061)
 */

void func(int sockfd, char* dna){
    //copy the DNA string to the buffer and send it to the server
	char buff[257];
	strcpy(buff, dna);
	write(sockfd, buff, sizeof(buff));
    
    //read, convert, and print the counts from the server
    results r;
    read(sockfd, &r, sizeof(r));
    convertNumbers(&r);
    printf("Output: A: %d, C: %d, G: %d, T: %d\n", r.as, r.cs, r.gs, r.ts);
} 
  
int main(){
    int sockfd, connfd; 
    struct sockaddr_in servaddr, cli; 
  
    // socket create and varification 
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
    servaddr.sin_addr.s_addr = inet_addr("10.35.195.47"); // thing1
    //servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // localhost
    servaddr.sin_port = htons(PORT); 
  
    // connect the client socket to server socket 
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
        printf("connection with the server failed...\n"); 
        exit(0); 
    } 
    else
        printf("connected to the server..\n"); 
  
    // function for DNA count
    func(sockfd, "TGAAAATCCCTTGTCAACATCTAGGTCTTATCACATCACAAGTCCCACCTCAGACTCTGCAGGGTGATCCAACAACCTTAATAGAAACATTATTGTTAAAGGACAGCATTAGTTCACAGTCAAACAAGCAAGATTGAGAATTAACCTTGGTTTTGAACTTGAATACTTAGAGGATTGGAGATTCAACAACCCTAAAGCTTGGGGTAAAACATTGGAAATAGTTAAAAGACAAATTGCTCGGAATCACAACATTCCG"); 
    func(sockfd, "AGTATGGATTCTCGTCCTCAGAAAGTCTGGATGACGCCGAGTCTCACTGAATCTGACATGGATTACCACAAGATCTTGACAGCAGGTCTGTCCGTTCAACAGGGGATTGTTCGGCAAAGAGTCATCCCAGTGTATCAAGTAAACAATCTTGAGGAGATTTGCCAACTTATCATACAGGCCTTTGAAGCAGGTGTTGATTTTCAAGAGAGTGCGGACAGTTTCCTTCTCATGCTTTGTCTTCATCATGCGTACCAGG");
    func(sockfd, "ATCTAGTGGAAAAAACATTAAGAGAACACTTGCTGCCATGCCGGAAGAGGAGACAACTGAAGCTAATGCCGGTCAGTTTCTCTCCTTTGCAAGTCTATTCCTTCCGAAATTGGTAGTAGGAGAAAAGGCTTGTCTTGAGAAGGTTCAAAGGCAAATTCAAGTACATGCAGAGCAAGGACTGATACAATATCCAACAGCTTGGCAATCAGTAGGACACATGATGGTGATTTTCCGTTTGATGCGAACAAATTTTT");
    // close the socket 
    close(sockfd); 
} 

void convertNumbers(results* r){
    r->as = htons(r->as);
    r->cs = ntohs(r->cs);
    r->gs = htons(r->gs);
    r->ts = htons(r->ts);
}
