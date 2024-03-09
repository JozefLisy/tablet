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

void InicializeRoomsAtNULL(ROOM  **room){
	if(*room == NULL){
		printf("(%4d)REPORT: InicializeRooms: structure is empty.\n",__LINE__);
		
		if((*room = (ROOM*)realloc(*room, sizeof(ROOM))) != NULL){
			(*room)->ID_room 	= NULL;
			(*room)->countClients	= NULL;
			(*room)->s_nameRoom 	= NULL;
			(*room)->clients	= NULL;
			printf("(%4d)SUCCESFUL: inicialize was successfully.\n",__LINE__);
		} else{
			printf("(%4d)ERROR: error allocating memory. (*room)\n",__LINE__);
		}
	} else
		printf("(%4d)ERROR: accepted structure is not empty\n",__LINE__);
}

int SetRoomValues(ROOM **room, int *ID_room, char *s_nameRoom){
	if((*room)->ID_room == NULL){
		printf("(%4d)REPORT: room is NULL. (SetRoomValue)\n", __LINE__);
		
		if(((*room)->ID_room = (int*)malloc(sizeof(int))) != NULL){
			*((*room)->ID_room) = *ID_room;
			
			if(((*room)->countClients = (int*)malloc(sizeof(int))) != NULL){
				*(*room)->countClients = 0;
				
				// zisti ako je to s '\0' v prijatom retazci. ci treba mat strlen + 1 alebo sa prepise aj ukoncovaci znak
				
				if(((*room)->s_nameRoom = (char*)malloc((strlen(s_nameRoom) + 1) * sizeof(char))) != NULL){ // + 1?
					if((strcpy((*room)->s_nameRoom, s_nameRoom)) != NULL){
					
						// tu sa zavola funkcia pre inicializaciu prveho klienta?
						printf("(%4d)SUCCESSFUL: successfuly allocating memory for structure room.\n",__LINE__);
						printf("\tValues: ID_room > %d / countClients >%d / s_nameRoom > %s\n", *(*room)->ID_room, *(*room)->countClients, (*room)->s_nameRoom);
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
	} else{
		printf("(%d)ERROR: room is not null. (SetRoomValues)\n",__LINE__);
	}
	return 0;
}

void FreeRoom(ROOM **room){
	memset((*room)->s_nameRoom, '\0', strlen((*room)->s_nameRoom) + 1); //treba + 1?
	free((*room)->s_nameRoom); 
	(*room)->s_nameRoom = NULL;
	
	*(*room)->countClients = 0;
	free((*room)->countClients);
	(*room)->countClients = NULL;
	
	*(*room)->ID_room = 0;
	free((*room)->ID_room);
	(*room)->ID_room = NULL;	

	free((*room)->clients);
	(*room)->clients = NULL;

	free(*room);
	*room = NULL;
}

int main(void){
	pthread_t threads[NUM_THREADS];
	int rc, t;
	
	ROOM *rooms = NULL;
	
	InicializeRoomsAtNULL(&rooms);

	int id = 3;
	char buffer[] = "hello";

	if((SetRoomValues(&rooms, &id, buffer)) == 1){
		printf("(%d)SUCCESSFUL: Set room values was successfully.\n",__LINE__);
		//FreeRoom(&rooms);
	}
	
	FreeRoom(&rooms);
	printf("Bey");
	return 0;
}
