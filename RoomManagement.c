#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

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

void InicializeRoomsAtNULL(ROOM  **room){
	if(*room == NULL){
		printf("FUNCTION InicializeRooms: structure is empty.\n");
		
		(*room)->ID_room 	= NULL;
		(*room)->countClients	= NULL;
		(*room)->s_nameRoom 	= NULL;
		(*room)->clients	= NULL;
	} 
	else
		printf("(%d)ERROR: accepted structure is not empty\n",__LINE__);
}

int SetRoomValues(ROOM **room, int *ID_room, char *s_roomName){
	if((*room)->ID_room == NULL){

		if(((*room)->ID_room = (int*)malloc(sizeof(int))) != NULL){
			*((*room)->ID_room) = *ID_room;
			
			if(((*room)->countClients = (int*)malloc(sizeof(int))) != NULL){
				(*room)->countClients = 0;
				
				// zisti ako je to s '\0' v prijatom retazci. ci treba mat strlen + 1 alebo sa prepise aj ukoncovaci znak
				if(((*room)->s_nameRoom = (char*)malloc((strlen(&s_roomName) + 1) * sizeof(char))) != NULL){
					if((strcpy((*room)->s_roomName, *s_roomName)) != NULL){
						
						// tu sa zavola funkcia pre inicializaciu prveho klienta?
						return 1;
						
					} else{
						printf("(%d)ERROR: error while copying string. (room->s_roomName)",__LINE__);
					}
				} else{
					printf("(%d)ERROR: error allocating memory. (room->s_roomName",__LINE__);
				}
			} else{
				printf("(%d)ERROR: error allocating memory. (room->countClients)",__LINE__);
			}
		} else{
			printf("(%d)ERROR: error allocating memory. (room->ID_room)", __LINE__);
		}
	}
	return 0;
}

void FreeRoom(ROOM **room){
	memset(*(*room)->s_roomName, '\0', sizeof((*room)->s_roomName));
	free((*room)->s_roomName);
	
	(*room)->countClients = 0;
	free((*room)->countClients);
	
	(*room)->ID_room = 0;
	free((*room)->ID_room);
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
		InicializeRoomsAtNULL(&rooms);
		
		int id = 3;
		int count = 0;
		char buffer[] = "hranolky";
		SetRoomValues(&rooms, &id, &count, &buffer);
	} else{
		printf("rooms is not NULL\n");
	}
	
	FreeRoom(&rooms);
	return 0;
}
