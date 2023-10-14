#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include <unistd.h>

#define SERV_TCP_PORT 5035
int main(int argc, char **argv)
{
int sockfd,newsockfd,clength;
struct sockaddr_in serv_addr,cli_addr;

int i,j,keylen,msglen,remlen,flag=0;
char input[100], key[30],temp[30],quot[100],rem[30],key1[30],crc[30],retmessage[100];

sockfd=socket(AF_INET,SOCK_STREAM,0);
serv_addr.sin_family=AF_INET;
serv_addr.sin_addr.s_addr=INADDR_ANY;
serv_addr.sin_port=htons(SERV_TCP_PORT);

printf("\n Binding Done...");
bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
listen(sockfd,5);
clength=sizeof(cli_addr);
newsockfd=accept(sockfd,(struct sockaddr*)&cli_addr,&clength);
read(newsockfd,input,100);
read(newsockfd,rem,30);
read(newsockfd,key,30);



// Message Data After Error Introducing
// CRC Calculated from Original data message

printf("\nMessage Data Received From Client : %s",input);
printf("\nCrc : %s",rem);
printf("\nDivisor : %s",key);


// Crc Implementing

keylen=strlen(key);
        msglen=strlen(input);
        strcpy(key1,key);
        strcat(input,rem);
        for (i=0;i<keylen;i++)
        temp[i]=input[i];
        for (i=0;i<msglen;i++) {
            quot[i]=temp[0];
            if(quot[i]=='0')
            for (j=0;j<keylen;j++)
            key[j]='0'; else
            for (j=0;j<keylen;j++)
            key[j]=key1[j];
            for (j=keylen-1;j>0;j--)
           {
                if(temp[j]==key[j])
                 rem[j-1]='0'; else
                 rem[j-1]='1';
            }
            rem[keylen-1]=input[i+keylen];
            strcpy(temp,rem);
        }

        strcpy(rem,temp);
       printf("\nQuotient is ");
       for (i=0;i<msglen;i++)
       printf("%c",quot[i]);
       printf("\nRemainder or Crc is ");
       for (i=0;i<keylen-1;i++)
       printf("%c",rem[i]);
       printf("\n\n");
       remlen=strlen(rem);
       for(i=0;i<remlen;i++)
       {
          if(rem[i]!='0')
          flag++;
       }
       if(flag>0)
       // If Remainder is Not Zero
       strcpy(retmessage,"Message Received by Server , Message In Error Please Send Again");
       else
       // If Remainder is Zero
       strcpy(retmessage,"Message Received by Server Without Error");

      write(newsockfd,retmessage,200);
close(sockfd);
return 0;
}
