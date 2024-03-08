#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 5

typedef struct{
	int *ID_client;
	char *s_nameClient;
}CLIENT;

typedef struct{
	int *ID_room;
	int *countClients;
	char *s_nameRoom;
	CLIENT *clients;
}ROOM;

//ROOM *rooms = NULL;
int condition = 1;


void *thread_funct(void *arg){
	long t_ID = (long) arg;
	
	while(condition){
		printf("Hello from thread %ld/\n", t_ID);
		sleep(1);
	}
	
	printf("Release thread. ID: %ld\n", t_ID);
	pthread_exit NULL;
}

void InicializeRooms(ROOM  **room){
	if(room != NULL){
		printf("FUNCTION InicializeRooms: structure is not empty.\n");
		
		
	} 
	else
		printf("(%d)ERROR: accepted strusture is empty\n",__LINE__);
}

void _InicializeRooms(ROOM *rooms){
	if((rooms = (ROOM*)malloc(1 * sizeof(ROOM))) != NULL){
		if((rooms->ID_room = (int*)malloc(sizeof(int))) != NULL){
			if((rooms->countClients = (int*)malloc(sizeof(int))) != NULL){
				if((rooms->s_nameRoom = (char*)malloc(1 * sizeof(char))) != NULL){
					if((rooms->clients = (CLIENT*)malloc(1 * sizeof(CLIENT))) != NULL){
						if((rooms->clients->ID_client = (int*)malloc(sizeof(int))) != NULL){
							if((rooms->clients->s_nameClient = (char*)malloc(1 * sizeof(char))) != NULL){
								
								printf("(%d)SUCCESSFUL; successfully alocated memory.",__LINE__);
								
							}
							else{
								printf("(%d)ERROR: error allocating memory. (rooms.clients.s_nameClient)", __LINE__);
							}
						}
						else{
							printf("(%d)ERROR: error allocating memory. (rooms.clients.ID_client)", __LINE__);
						}
					}
					else{
						printf("(%d)ERROR: error allocating memory. (rooms.clients)",__LINE__);
						exit(1);
					}
				}
				else{
					printf("(%d)ERROR: error allocating memory. (rooms.s_name)",__LINE__);
					exit(1);
				}
			}
			else{
				printf("(%d)ERROR: error allocating memory. (rooms.countClients)",__LINE__);
				exit(1);
			}
		}
		else{
			printf("(%d)ERROR: error allocating memory. (rooms.ID_room)", __LINE__);
			exit(1);
		}
	}
	else{
		printf("(%d)ERROR: error allocating memory. (*rooms)", __LINE__);
		exit(1);
	}
}

void FreeRooms(){
	
}

int main(void){
	pthread_t threads[NUM_THREADS];
	int rc, t;
	
	ROOM *rooms = NULL;
	
	for(t = 0; t < NUM_THREADS; t++){
		rc = pthread_create(&threads[t], NULL, thread_funct, (void*)(intptr_t)t);
		if(rc){
			printf("ERROR: %d\n", rc);
			exit (-1);
		}
	} 
	
	getc(stdin);

	condition = 0;

	int exiting = 5;
	for( ;exiting > 0; exiting--){
		printf("exiting %d!\n", exiting);
		sleep(1);
	}

	for (t = 0; t < NUM_THREADS; t++){
		pthread_join(threads[t], NULL);
	}
	printf("All threads have completed.\n");
	
	if(rooms == NULL){
		printf("rooms is NULL\n");
		InicializeRooms(&rooms);
	}
	else
		printf("rooms is not NULL\n");
	
	return 0;
}
