#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//LAYER
typedef struct Layer{//Every Layer has 2 or 3 strings
	char *str1;
	char *str2;
	char *str3;
}layer;

//STACK
typedef struct stackStruct { 
    int top; 
    int capacity; 
    layer* array; 
}Stack; 
  
Stack* createStack() { 

    Stack* stack = (Stack*) malloc(sizeof(Stack)); 
    stack->capacity = 4; 
    stack->top = -1; 
    stack->array = (layer*) malloc(stack->capacity * sizeof(layer)); 
    return stack; 
} 
  
// Stack is full when top is equal to the last index 
int isFull(Stack* stack) {
   return stack->top == stack->capacity - 1; 
} 
  
// Stack is empty when top is equal to -1 
int isEmpty(Stack* stack) {
   return stack->top == -1;  
} 
  
// Function to add an item to stack.  It increases top by 1 
void push(Stack* stack, layer item) { 

    if (isFull(stack)) 
        return; 
    stack->array[++stack->top] = item; 
} 
  
// Function to remove an item from stack.  It decreases top by 1 
layer pop(Stack* stack) {
 
    if (isEmpty(stack)) 
        return; 
    return stack->array[stack->top--]; 
} 

struct QNode { 
    
	Stack* frame; 
    struct QNode *next; 
     
}; 
  
//QUEUE
// front stores the front node of LinkedList and rear stores the last node in linkedList

struct Queue { 
    struct QNode *front, *rear; 
}; 
  
// A utility function to create a new linked list node. 
struct QNode* newNode(Stack* k) { 
    
	struct QNode *temp = (struct QNode*)malloc(sizeof(struct QNode)); 
    temp->frame = k; 
    temp->next = NULL; 
    return temp;  
} 
  
// A utility function to create an empty queue 
struct Queue *createQueue() { 
	
    struct Queue *q = (struct Queue*)malloc(sizeof(struct Queue)); 
	q->front = q->rear = NULL; 
    return q; 
} 
  
// The function to add a key k to q 
void enQueue(struct Queue *q,Stack* k) { 
    // Create a new LL node 
    struct QNode *temp = newNode(k); 
    
	// If queue is empty, then new node is front and rear both 
    if (q->rear == NULL) { 
       q->front = q->rear = temp; 
       return; 
    } 
    
	// Add the new node at the end of queue and change rear 
    q->rear->next = temp; 
    q->rear = temp; 
} 

// Function to remove a key from given queue q 
struct QNode *deQueue(struct Queue *q) { 
    // If queue is empty, return NULL. 
    if (q->front == NULL) 
       return NULL; 
    
	// Store previous front and move front one node ahead 
    struct QNode *temp = q->front; 
    q->front = q->front->next; 
    
	// If front becomes NULL, then change rear also as NULL 
    if (q->front == NULL) 
       q->rear = NULL; 
    return temp; 
} 
//CLIENTS
typedef struct ClientStruct {

	char clientID;			//keeps Client ID
	char *clientIP;			//keeps Client IP Address
	char *clientMAC;		//keeps Client MAC Address
	char **routing;			//keeps routing data for each clients
	struct Queue* incomingQueue;	//Incoming Queue of client
	struct Queue* outgoingQueue;	//Outgoing Queue of client
	int incoming_size;		//keeps size of Incoming Queue
	int outgoing_size;		//keeps size of Outgoing Queue 
	char *sender_portnum;	//keeps Sending Socket Port Number
	char *receiver_portnum;	//keeps Listening Socket Port Number
	char *between;			//keeps the clients ID's between sender and reciever client
	char* sending_msg;		//keeps the message
	int hops;				//keeps number of hops

}Clients;

//COMMANDS
typedef struct Commands {

	char *command_line;	//Command Line String
	char *command;		//Command(MESSAGE,SEND,SHOW_FRAME_INFO...)
	char *first_word;	//First word of Command Line
	char sender_id;		//Sender Client ID
	char receiver_id;	//Reciever Client ID
	char *message;		//Message
	char *which_queue;	//In or Out Queue?
	char client_id;		//Client ID
	int frame_number;	//Frame number of Queue

}commands;

void hops_calculation(int client_size,int routing_size,commands* CommandsArray,Clients* ClientsArray,int a,int b,int sender,int i){
	int j=0,k=0;
	for(j=0;j<client_size-1;j++){
		if(ClientsArray[a].routing[j][0]==CommandsArray[i].receiver_id){
			if(ClientsArray[a].routing[j][0]!=ClientsArray[a].routing[j][1]){
				ClientsArray[sender].between[ClientsArray[sender].hops]=ClientsArray[a].routing[j][1];
				ClientsArray[sender].hops=ClientsArray[sender].hops+1;
				}
	
			}
			else{
				ClientsArray[sender].between[ClientsArray[sender].hops]=ClientsArray[a].routing[j][1];
			}
		
	}
	for(k=0;k<client_size;k++){
		if(ClientsArray[sender].between[ClientsArray[sender].hops-1]==ClientsArray[k].clientID){
			b=a;
			a=k;
		}
	}
		for(j=0;j<routing_size;j++){
		if(ClientsArray[b].routing[j][0]==CommandsArray[i].receiver_id){
			if(ClientsArray[b].routing[j][0]!=ClientsArray[b].routing[j][1]){
				hops_calculation(client_size,routing_size,CommandsArray,ClientsArray,a,b,sender,i);
			}
		}
	}
		
	}
	

void commandsfunction(int client_size,int msg_max_size,int routing_size,int command_size,commands* CommandsArray,Clients* ClientsArray){
	int i,j,sender_i,reciever_i,between_i=0,f,count=0,remainder;
	
	for (i= 0; i < command_size; i++){	
		
		if(strcmp(CommandsArray[i].command,"MESSAGE")==0){
			sscanf(CommandsArray[i].command_line," %s %c %c #%[^\t\n'#']",CommandsArray[i].command,&CommandsArray[i].sender_id,&CommandsArray[i].receiver_id,CommandsArray[i].message);
			int message_size=strlen(CommandsArray[i].message);
					
			 ( "------------------------------------------------------------------------\n");
			printf( "Command: %s",CommandsArray[i].command_line);
			printf( "-------------------------------------------------------------------\n");
			printf( "Message to be sent : %s\n",CommandsArray[i].message);
					
			for(j=0;j<client_size;j++){
				if(ClientsArray[j].clientID==CommandsArray[i].sender_id){
					sender_i=j;
				}
				if(ClientsArray[j].clientID==CommandsArray[i].receiver_id){
					reciever_i=j;
				}
							
			}
			strcpy(ClientsArray[sender_i].sending_msg,CommandsArray[i].message);
			
			between_i=sender_i;
			
			ClientsArray[sender_i].hops=0;
			
			hops_calculation(client_size,routing_size, CommandsArray,ClientsArray,sender_i,reciever_i,sender_i,i);
			
			for(j=0;j<client_size;j++){
				if(ClientsArray[j].clientID==ClientsArray[sender_i].between[0]){
					between_i=j;
				}	
				
			}
			ClientsArray[sender_i].between[ClientsArray[sender_i].hops]=CommandsArray[i].receiver_id;
			remainder=message_size%msg_max_size;
			int frame_number;
			if(remainder==0){
				frame_number = message_size/msg_max_size;
			}
			else{
				frame_number = message_size/msg_max_size + 1;
			}
			
			ClientsArray[sender_i].outgoing_size=frame_number;
			ClientsArray[reciever_i].incoming_size=frame_number;
			
			for(f=0;f<frame_number; f++){
				Stack* frame = createStack();
				layer physicalLayer;
				layer networkLayer;
				layer transportLayer;
				layer applicationLayer;	
						
				//Physical Layer of Frame	(MAC Adresses)
				physicalLayer.str1 = malloc(sizeof(strlen(ClientsArray[sender_i].clientMAC)));
				strcpy(physicalLayer.str1, ClientsArray[sender_i].clientMAC);
						
				physicalLayer.str2 = malloc(strlen(ClientsArray[between_i].clientMAC)*sizeof(char));
				strcpy(physicalLayer.str2, ClientsArray[between_i].clientMAC);
						
				physicalLayer.str3 = NULL;
						
				//Network Layer of Frame 	(IP Adresses)
				networkLayer.str1 = malloc(sizeof(strlen(ClientsArray[sender_i].clientIP)));
				strcpy(networkLayer.str1, ClientsArray[sender_i].clientIP);
						
				networkLayer.str2 = malloc(sizeof(strlen(ClientsArray[reciever_i].clientIP)));
				strcpy(networkLayer.str2, ClientsArray[reciever_i].clientIP);
						
				networkLayer.str3 = NULL;
						
				//Transport Layer of Frame	(Port Numbers)
						
				transportLayer.str1 = malloc(sizeof(strlen(ClientsArray[sender_i].sender_portnum)));
				strcpy(transportLayer.str1, ClientsArray[sender_i].sender_portnum);
						
				transportLayer.str2 = malloc(sizeof(strlen(ClientsArray[reciever_i].receiver_portnum)));
				strcpy(transportLayer.str2, ClientsArray[reciever_i].receiver_portnum);
						
				transportLayer.str3 = NULL;
						
				//application layer of Frame	(Client ID's and Message)
				applicationLayer.str1 = malloc(sizeof(ClientsArray[sender_i].clientID));
				strcpy(applicationLayer.str1, &ClientsArray[sender_i].clientID);
						
				applicationLayer.str2 = malloc(sizeof(ClientsArray[reciever_i].clientID));
				strcpy(applicationLayer.str2, &ClientsArray[reciever_i].clientID);
						
				applicationLayer.str3 = malloc(sizeof(char)*msg_max_size+1);
					
				if((f+1)*msg_max_size>message_size){
					for(j=0;j<remainder;j++){
						(applicationLayer.str3)[j]=(CommandsArray[i].message)[count];	
						count++;
					}
					for(j=remainder;j<msg_max_size+1;j++){
						(applicationLayer.str3)[j] = '\0';
					}	
				}
				else{	
					for(j=0;j<msg_max_size;j++){
						(applicationLayer.str3)[j]=(CommandsArray[i].message)[count];	
						count++;
					}
					(applicationLayer.str3)[j+1] = '\0';
				}
				
				

  				push(frame,applicationLayer);	//Push Application Layer to Frame Stack
  				push(frame,transportLayer);		//Push Transport Layer to Frame Stack
  				push(frame,networkLayer);		//Push Network Layer to Frame Stack
  				push(frame,physicalLayer);		//Push Physical Layer to Frame Stack
  				enQueue(ClientsArray[reciever_i].incomingQueue,frame); 	//Enqueue Frame Stack in to Reciever Clients Incoming Queue
  				enQueue(ClientsArray[sender_i].outgoingQueue,frame);		//Enqueue Frame Stack in to Sender Clients Outgoing Queue
  				printf( "Frame #%d\nSender MAC address: %s, Receiver MAC address: %s \n",f+1,ClientsArray[sender_i].clientMAC,ClientsArray[between_i].clientMAC);
				printf( "Sender IP address: %s, Receiver IP address: %s\n",ClientsArray[sender_i].clientIP,ClientsArray[reciever_i].clientIP);
				printf( "Sender port number: %s, Receiver port number: %s\n",ClientsArray[sender_i].sender_portnum,ClientsArray[reciever_i].receiver_portnum);
				printf( "Sender ID: %c, Receiver ID: %c\n",ClientsArray[sender_i].clientID,ClientsArray[reciever_i].clientID);
				printf( "Message chunk carried: %s\n",applicationLayer.str3);
				printf( "-----------------\n");
			}
		}
		
		else if(strcmp(CommandsArray[i].command,"SHOW_FRAME_INFO")==0){
			sscanf(CommandsArray[i].command_line,"%s %s %s %d",CommandsArray[i].command,&CommandsArray[i].client_id,CommandsArray[i].which_queue,&CommandsArray[i].frame_number);
			printf( "--------------------------------------------------\n");
			printf( "Command: %s",CommandsArray[i].command_line);
			printf( "---------------------------------------------------\n");	
			int a,k,hops=0;
			for(j=0;j<sizeof(ClientsArray);j++){
				if(ClientsArray[j].clientID==CommandsArray[i].client_id){
					sender_i=j;	
				}	
			}	
			if(strcmp(CommandsArray[i].which_queue,"in")==0){
				if(ClientsArray[sender_i].incoming_size<CommandsArray[i].frame_number){
					printf( "No such frame.\n");
				}
				else{
					for(a=0;a<CommandsArray[i].frame_number-1;a++){
						ClientsArray[sender_i].outgoingQueue->front=ClientsArray[sender_i].outgoingQueue->front->next;
						
						
					}
					Stack* Frame = ClientsArray[sender_i].outgoingQueue->front->frame;
					layer physicalLayer=pop(Frame);
					layer networkLayer=pop(Frame);
					layer transportLayer=pop(Frame);
					layer applicationLayer=pop(Frame);
					for(k=0;k<ClientsArray[sender_i].hops;k++){
						if(physicalLayer.str2[0]==ClientsArray[sender_i].between[j]){
							hops=j;
						}
					}
					printf( "Current Frame #%d on the outgoing queue of client %c\n",CommandsArray[i].frame_number,CommandsArray[i].client_id);
					printf( "Carried Message: \"%s\"\n",applicationLayer.str3);
					printf( "Layer 0 info: Sender ID: %s, Receiver ID: %s\n",applicationLayer.str1,applicationLayer.str2);
					printf( "Layer 1 info: Sender port number: %s, Receiver port number: %s\n",transportLayer.str1,transportLayer.str2);
					printf( "Layer 2 info: Sender IP address: %s, Receiver IP address: %s\n",networkLayer.str1,networkLayer.str2);
					printf( "Layer 3 info: Sender MAC address: %s, Receiver MAC address: %s\n",physicalLayer.str1,physicalLayer.str2);
					printf( "Number of hops so far: %d\n",hops);
					push(Frame,applicationLayer);
  					push(Frame,transportLayer);
  					push(Frame,networkLayer);
  					push(Frame,physicalLayer);	
					

				}
			}
			
			if(strcmp(CommandsArray[i].which_queue,"out")==0){
				if(ClientsArray[sender_i].outgoing_size<CommandsArray[i].frame_number){
					printf( "No such frame.\n");
				}
				else{
					for(a=0;a<CommandsArray[i].frame_number-1;a++){
						ClientsArray[sender_i].outgoingQueue->front=ClientsArray[sender_i].outgoingQueue->front->next;
						
						
					}
					Stack* Frame = ClientsArray[sender_i].outgoingQueue->front->frame;
					layer physicalLayer=pop(Frame);
					layer networkLayer=pop(Frame);
					layer transportLayer=pop(Frame);
					layer applicationLayer=pop(Frame);
					
					for(k=0;k<ClientsArray[sender_i].hops;k++){
						if(physicalLayer.str2[0]==ClientsArray[sender_i].between[j]){
							hops=j;
						}
					}
					printf( "Current Frame #%d on the outgoing queue of client %c\n",CommandsArray[i].frame_number,CommandsArray[i].client_id);
					printf( "Carried Message: \"%s\"\n",applicationLayer.str3);
					printf( "Layer 0 info: Sender ID: %s, Receiver ID: %s\n",applicationLayer.str1,applicationLayer.str2);
					printf( "Layer 1 info: Sender port number: %s, Receiver port number: %s\n",transportLayer.str1,transportLayer.str2);
					printf( "Layer 2 info: Sender IP address: %s, Receiver IP address: %s\n",networkLayer.str1,networkLayer.str2);
					printf( "Layer 3 info: Sender MAC address: %s, Receiver MAC address: %s\n",physicalLayer.str1,physicalLayer.str2);
					printf( "Number of hops so far: %d\n",hops);
					push(Frame,applicationLayer);
  					push(Frame,transportLayer);
  					push(Frame,networkLayer);
  					push(Frame,physicalLayer);
				}
					
			}			
		}
		
		else if(strcmp(CommandsArray[i].command,"SHOW_Q_INFO")==0){
			sscanf(CommandsArray[i].command_line,"%s %s %s",CommandsArray[i].command,&CommandsArray[i].client_id,CommandsArray[i].which_queue);
			printf( "--------------------------------------------------\n");
			printf( "Command: %s",CommandsArray[i].command_line);
			printf( "--------------------------------------------------\n");
			for(j=0;j<sizeof(ClientsArray);j++){
				if(ClientsArray[j].clientID==CommandsArray[i].client_id){
					sender_i=j;	
				}
			}
			if(strcmp(CommandsArray[i].which_queue,"in")==0){
				printf( "Client %c Incoming Queue Status\n",CommandsArray[i].client_id);
				printf( "Current total number of frames: %d\n",ClientsArray[sender_i].incoming_size);
			}
			else if(strcmp(CommandsArray[i].which_queue,"out")==0){
				printf( "Client %c Outcoming Queue Status\n",CommandsArray[i].client_id);
				printf( "Current total number of frames: %d\n",ClientsArray[sender_i].outgoing_size);	
			}
			
		}
		
		else if(strcmp(CommandsArray[i].command,"SEND")==0){
			sscanf(CommandsArray[i].command_line,"%s %c",CommandsArray[i].command,&CommandsArray[i].client_id);
			printf( "-------------------------------------------------------------------------------------\n");
			printf( "Command: %s",CommandsArray[i].command_line);
			printf( "-------------------------------------------------------------------------------------\n");
			int sender,reciever;
			for(j=0;j<sizeof(ClientsArray);j++){
				if(ClientsArray[j].clientID==CommandsArray[i].client_id){
					sender_i=j;
				}
			}
			int a=0,k=0;
			for(j=0;j<ClientsArray[sender_i].hops;j++){
				for(a=0;a<sizeof(ClientsArray);a++){
					if(ClientsArray[a].clientID==ClientsArray[sender_i].between[k]){
						sender=a;
					}
					if(ClientsArray[a].clientID==ClientsArray[sender_i].between[k+1]){
						reciever=a;

					}
				}
				printf( "A message received by client %c, but intended for client %c. Forwarding...\n",ClientsArray[sender].clientID,ClientsArray[sender_i].between[ClientsArray[sender_i].hops]);

				for(a=0;a<ClientsArray[sender_i].outgoing_size;a++){
				
					printf( "Frame #%d MAC address change: New sender MAC %s, new receiver MAC %s\n",a+1,ClientsArray[sender].clientMAC,ClientsArray[reciever].clientMAC);
				}
				
				k++;
			}
			printf( "A message received by client %c from client %c after a total of %d hops.\n",ClientsArray[sender_i].between[ClientsArray[sender_i].hops],ClientsArray[sender_i].clientID,ClientsArray[sender_i].hops+1);
			printf( "Message: %s\n",ClientsArray[sender_i].sending_msg);
		}
		
		else if(strcmp(CommandsArray[i].command,"PRINT_LOG")==0){
			sscanf(CommandsArray[i].command_line,"%s %c",CommandsArray[i].command,&CommandsArray[i].client_id);
			printf( "-----------------------------------------------------\n");
			printf( "Command: %s",CommandsArray[i].command_line);
			printf( "-----------------------------------------------------\n");
			printf( "Client %c Logs:\n",CommandsArray[i].client_id);
			printf( "-----------------\n");
			
			
		}
		else{
			printf( "----------------------\n");
			printf( "Command: %s",CommandsArray[i].command_line);
			printf( "----------------------\n");
			printf( "Invalid command.");
		}
	}
}




int main(int argc, char *argv[]){
	
	FILE *fp ,*fp2,*fp3;
	fp=fopen(argv[1],"r");	//arg[1] = "clients.dat"
	fp2=fopen(argv[2],"r");	//arg[2] = "routing.dat"
	fp3=fopen(argv[3],"r");	//arg[3] = "commands.dat"

	int msg_max_size;		//arg[4] = max message size
	char *sender_port;		//arg[5] = outgoing port number
	char *reciever_port;	//arg[6] = incoming port number
	sender_port=(char*)malloc(sizeof(char)*4);
	reciever_port=(char*)malloc(sizeof(char)*4);
	sscanf(argv[4],"%d",&msg_max_size);
	sscanf(argv[5],"%s",sender_port);
	sscanf(argv[6],"%s",reciever_port);
	int a=0,i=0,j=0,k=0;
	
	int client_size;
	fscanf(fp, "%d\n", &client_size);
	
		int sizeofrouting=client_size*(client_size-1);

	Clients* ClientsArray = (Clients *)malloc(sizeof(Clients) * client_size);	
	for(i=0;i<client_size;i++){
	
		ClientsArray[i].routing=(char **)malloc(sizeofrouting*sizeof(char*));  
		for(a=0;a<sizeofrouting;a++){
			ClientsArray[i].routing[a]=(char *)malloc(2*sizeof(char));
		}
	
		ClientsArray[i].clientIP=(char *)malloc(sizeof(char)*7);
		ClientsArray[i].clientMAC=(char *)malloc(sizeof(char)*10);
		ClientsArray[i].sender_portnum=(char *)malloc(sizeof(char)*4);
		ClientsArray[i].receiver_portnum=(char *)malloc(sizeof(char)*4);
		ClientsArray[i].between=(char*)malloc(client_size*sizeof(char));
		ClientsArray[i].sending_msg=(char*)malloc(BUFSIZ*sizeof(char));

		ClientsArray[i].incomingQueue = createQueue();
		ClientsArray[i].outgoingQueue = createQueue();
		strcpy(ClientsArray[i].sender_portnum,sender_port);
		strcpy(ClientsArray[i].receiver_portnum,reciever_port);
		
	}

	int command_size;
	fscanf(fp3,"%d\n",&command_size);
	
	commands* CommandsArray = (commands *)malloc(sizeof(commands) * command_size);	
	
	for(i=0;i<command_size;i++){
		
		CommandsArray[i].command_line=(char *)malloc(BUFSIZ*sizeof(char));
		CommandsArray[i].first_word=(char *)malloc(BUFSIZ*sizeof(char));
		CommandsArray[i].message=(char *)malloc(BUFSIZ*sizeof(char));
		CommandsArray[i].which_queue=(char *)malloc(3*sizeof(char));

	}
	
	char *routingarray;
	routingarray=(char *)malloc(((sizeofrouting*2)+client_size-1)*sizeof(char));
	
	//ROUTING.DAT FILE READING
	i=0;
	if(fp2!=NULL){
		while(!feof(fp2)){
			fscanf(fp2,"%c ",&routingarray[i]);

			i++;
		}
	}
	k=0;
	for(i=0;i<client_size;i++){
		k=0;
			for(a=(0+i*((client_size-1)*2+1));a<=((client_size-1)*2-1)+i*(client_size*2+1);a=a+2){ 

				ClientsArray[i].routing[k][0]=routingarray[a];
				ClientsArray[i].routing[k][1]=routingarray[a+1];
				
				k++;
			}
	}
	
	//CLIENTS.DAT FILE READING
	if(fp!=NULL){
		while(!feof(fp)){
			for (i= 0; i < client_size; i++)
			{
				fscanf(fp, "%c %s %s\n", &ClientsArray[i].clientID, ClientsArray[i].clientIP, ClientsArray[i].clientMAC);
			}
		}
	}

	if(fp3!=NULL){
		while(!feof(fp3)){
			for (i= 0; i < command_size; i++){
				fgets(CommandsArray[i].command_line,100,fp3);
				strcpy(CommandsArray[i].first_word,CommandsArray[i].command_line);
				CommandsArray[i].command=strtok(CommandsArray[i].first_word," ");
			}
		}
	}
	
	commandsfunction(client_size,msg_max_size,sizeofrouting,command_size,CommandsArray,ClientsArray);


//	free(sender_port);
//	free(reciever_port);
//	free(routingarray);
//	free(ClientsArray);
//	free(CommandsArray);
	fclose(fp);
	fclose(fp2);
	fclose(fp3);
}
