// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/ipc.h>
// #include <sys/shm.h>
// #include "sem.h"

// #define CHILD      			0  			/* Return value of child proc from fork call */
// #define TRUE       			0  
// #define FALSE      			1

// FILE *fp1, *fp2, *fp3, *fp4;			/* File Pointers */

// main()
// {
// 	int pid;						// Process ID after fork call
// 	int i;							// Loop index
// 	int N;							// Number of times dad does update
// 	int N_Att;						// Number of time sons allowed to do update
// 	int status;						// Exit status of child process
// 	int bal1, bal2;					// Balance read by processes
// 	int flag, flag1;				// End of loop variables
	
// 	//Initialize the file balance to be $100
// 	fp1 = fopen("balance","w");
// 	bal1 = 100;
// 	fprintf(fp1, "%d\n", bal1);
// 	fclose(fp1);
	
// 	//Initialize the number of attempts to be 20
// 	fp4 = fopen("attempt", "w");
// 	N_Att = 20;
// 	fprintf(fp4, "%d\n", N_Att);
// 	fclose(fp4);
	
// 	/* ============= ADD CODE START ================ */
// 	//Create semaphore 
// 	int semid = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
// 	if (semid == -1){
// 		perror("Error creating semaphore\n");
// 		exit(1);
// 	}
// 	//Initialize semaphore to 1
// 	sem_create(semid, 1);
// 	printf("Semaphore_ID = %d\n", semid);

// 	//wait time for each process to enter CS
// 	int dad_wait = 0;
// 	int son1_wait = 0;
// 	int son2_wait = 0;

// 	// process express interest in CS 
// 	int dad_flag = 1;
// 	int son1_flag = 1;
// 	int son2_flag = 1;

// 	/* ============= ADD CODE END ================ */


// 	//Create child processes that will do the updates
// 		if ((pid = fork()) == -1) 
// 	{
// 		//fork failed!
// 		perror("fork");
// 		exit(1);
// 	}
	
// 	if (pid == CHILD){
// 	//First Child Process. Dear old dad tries to do some updates.
	
// 		N=5;
// 		for(i=1;i<=N; i++)
// 		{	
// 			P(semid); //lock the process
// 			if(son1_flag != 0){ //increment process
// 				son1_wait += 1;
// 			}
// 			if(son2_flag != 0){
// 				son2_wait += 1;
// 			}
// 			printf("\nWait time for Son 1: %d, Son 2: %d\n", son1_wait, son2_wait);
// 			printf("Dear old dad is trying to do update.\n");

// 			fp1 = fopen("balance", "r+");
// 			fscanf(fp1, "%d", &bal2);
// 			printf("Dear old dad reads balance = %d \n", bal2);
			
// 			//Dad has to think (0-14 sec) if his son is really worth it
// 			sleep(rand()%15);
// 			fseek(fp1,0L,0);
// 			bal2 += 60;
// 			printf("Dear old dad writes new balance = %d \n", bal2);
// 			fprintf(fp1, "%d \n", bal2);
// 			fclose(fp1);

// 			printf("Dear old dad is done doing update. \n");
// 			sleep(rand()%5);	/* Go have coffee for 0-4 sec. */
			
// 			dad_flag = 0;
// 			V(semid); //release the lock on process
// 		}
// 	}
	
// 	else
// 	{
// 		//Parent Process. Fork off another child process.
// 		if ((pid = fork()) == -1)
// 		{
// 			//Fork failed!
// 			perror("fork");
// 			exit(1);
// 		}
// 		if (pid == CHILD)
// 		{	
// 			printf("First Son's Pid: %d\n",getpid());
// 			//Second child process. First poor son tries to do updates.
// 			flag = FALSE;
// 			while(flag == FALSE) 
// 			{	
// 				P(semid); //lock the process
// 				if(dad_flag != 0){ //increment process
// 					dad_wait += 1;
// 				}
// 				if(son2_flag != 0){
// 					son2_wait += 1;
// 				}
// 				printf("\nWait time for Dad: %d, Son 2: %d\n", dad_wait, son2_wait);

// 				fp3 = fopen("attempt" , "r+");
// 				fscanf(fp3, "%d", &N_Att);
// 				if(N_Att == 0)
// 				{
// 					fclose(fp3);
// 					flag = TRUE;
// 				}
// 				else
// 				{
// 					printf("Poor SON_1 wants to withdraw money.\n");
// 					fp2 = fopen("balance", "r+");
// 					fscanf(fp2,"%d", &bal2);
// 					printf("Poor SON_1 reads balance. Available Balance: %d \n", bal2);
// 					if (bal2 == 0)
// 					{
// 						fclose(fp2);
// 						fclose(fp3);
// 					}
// 					else
// 					{
// 						sleep(rand()%5);
// 						fseek(fp2,0L, 0);
// 						bal2 -=20;
// 						printf("Poor SON_1 write new balance: %d \n", bal2);
// 						fprintf(fp2,"%d\n", bal2);
// 						fclose(fp2);
// 						printf("poor SON_1 done doing update.\n");
// 						fseek(fp3,0L, 0);
// 						N_Att -=1;
// 						fprintf(fp3, "%d\n", N_Att);
// 						fclose(fp3);
// 					}
// 				}
// 				son1_flag = 0; //done with CS
// 				V(semid); //release the lock on process
// 			}
// 		}
// 		else
// 		{
// 		//Parent Process. Fork off one more child process.
// 			if ((pid = fork()) == -1) 
// 			{
// 				//fork failed!
// 				perror("fork");
// 				exit(1);
// 			}
// 			if (pid == CHILD)
// 			{
// 				printf("Second Son's Pid: %d\n",getpid());
// 				//Third child process. Second poor son tries to do updates.
// 				flag1 = FALSE;
// 				while(flag1 == FALSE) 
// 				{
// 					P(semid); //lock the process
// 					if(dad_flag != 0){ //increment process
// 						dad_wait += 1;
// 					}
// 					if(son1_flag != 0){
// 						son1_wait += 1;
// 					}
// 					printf("\nWait time for Dad: %d, Son 1: %d\n", dad_wait, son1_wait);

// 					fp3 = fopen("attempt" , "r+");
// 					fscanf(fp3, "%d", &N_Att);
// 					if(N_Att == 0)
// 					{
// 						fclose(fp3);
// 						flag1 = TRUE;
// 					}
// 					else
// 					{
// 						printf("Poor SON_2 wants to withdraw money.\n");
// 						fp2 = fopen("balance", "r+");
// 						fscanf(fp2,"%d", &bal2);
// 						printf("Poor SON_2 reads balance. Available Balance: %d \n", bal2);
// 						if (bal2 == 0)
// 						{
// 							fclose(fp2);
// 							fclose(fp3);
// 						}
// 						else
// 						{
// 							sleep(rand()%5);
// 							fseek(fp2,0L, 0);
// 							bal2 -=20;
// 							printf("Poor SON_2 write new balance: %d \n", bal2);
// 							fprintf(fp2,"%d\n", bal2);
// 							fclose(fp2);

// 							printf("poor SON_2 done doing update.\n");
// 							fseek(fp3,0L, 0);
// 							N_Att -=1;
// 							fprintf(fp3, "%d\n", N_Att);
// 							fclose(fp3);
// 						}
// 					}
// 					son2_flag = 0; //done with CS
// 					V(semid); //release the lock on process
// 				}
// 			}
// 			else
// 			{
// 				//Now parent process waits for the child processes to finish
// 				pid = wait(&status);
// 				printf("Process(pid = %d) exited with the status %d. \n", pid, status);
			
// 				pid = wait(&status);
// 				printf("Process(pid = %d) exited with the status %d. \n", pid, status);
			
// 				pid = wait(&status);
// 				printf("Process(pid = %d) exited with the status %d. \n", pid, status);

// 				semkill(semid);

// 			}
// 			exit(0);
// 		}
// 		exit(0);
// 	}
// 	exit(0);
// }




/* -------------------- SECOND VERSION WITH SEMAPHORE --------------------- */



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "sem.h"

#define CHILD      			0  			/* Return value of child proc from fork call */
#define TRUE       			0  
#define FALSE      			1

FILE *fp1, *fp2, *fp3, *fp4;			/* File Pointers */

main()
{
	int pid;						// Process ID after fork call
	int i;							// Loop index
	int N;							// Number of times dad does update
	int N_Att;						// Number of time sons allowed to do update
	int status;						// Exit status of child process
	int bal1, bal2;					// Balance read by processes
	int flag, flag1;				// End of loop variables
	
	//Initialize the file balance to be $100
	fp1 = fopen("balance","w");
	bal1 = 100;
	fprintf(fp1, "%d\n", bal1);
	fclose(fp1);
	
	//Initialize the number of attempts to be 20
	fp4 = fopen("attempt", "w");
	N_Att = 20;
	fprintf(fp4, "%d\n", N_Att);
	fclose(fp4);
	
	//create semaphore
	int semid = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
	if (semid == -1){
		perror("Error creating semaphore\n");
		exit(1);
	}
	sem_create(semid, 1);

	int sem_wait[3];
	int sem_flag[3];
	for (int i = 0; i < 3; i++){
		sem_wait[i] = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
		sem_flag[i] = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
		if (sem_wait[i] == -1 || sem_flag[i] == -1){
			perror("Error creating semaphore\n");
			exit(1);
		}
		semctl(sem_wait[i], 0, SETVAL, 0);
		semctl(sem_flag[i], 0, SETVAL, 0);
	}


	//Create child processes that will do the updates
		if ((pid = fork()) == -1) 
	{
		//fork failed!
		perror("fork");
		exit(1);
	}
	
	if (pid == CHILD){
	//First Child Process. Dear old dad tries to do some updates.
	
		N=25;
		for(i=1;i<=N; i++)
		{	
			semctl(sem_flag[0], 0, SETVAL, 1); //express interest in CS
			P(semid); // Dad is accessing the account, so wait until he's done
			if(semctl(sem_flag[1], 0, GETVAL)){ //increment process
				semctl(sem_wait[1], 0, SETVAL, semctl(sem_wait[1], 0, GETVAL) + 1);
			}
			if(semctl(sem_flag[2], 0, GETVAL)){
				semctl(sem_wait[2], 0, SETVAL, semctl(sem_wait[2], 0, GETVAL) + 1);
			}
			printf("\nWait time for Son 1: %d, Son 2: %d\n", semctl(sem_wait[1], 0, GETVAL), semctl(sem_wait[2], 0, GETVAL));
			printf("Dear old dad is trying to do update.\n");

			fp1 = fopen("balance", "r+");
			fscanf(fp1, "%d", &bal2);
			printf("Dear old dad reads balance = %d \n", bal2);
			
			//Dad has to think (0-14 sec) if his son is really worth it
			sleep(rand()%15);
			fseek(fp1,0L,0);
			bal2 += 60;
			printf("Dear old dad writes new balance = %d \n", bal2);
			fprintf(fp1, "%d \n", bal2);
			fclose(fp1);

			printf("Dear old dad is done doing update. \n");
			sleep(rand()%5);	/* Go have coffee for 0-4 sec. */

			// semctl(sem_flag[0], 0, SETVAL, 0); //done with CS 
			V(semid); //release the lock on process

		}
	}
	
	else
	{
		//Parent Process. Fork off another child process.
		if ((pid = fork()) == -1)
		{
			//Fork failed!
			perror("fork");
			exit(1);
		}
		if (pid == CHILD)
		{	
			printf("First Son's Pid: %d\n",getpid());
			//Second child process. First poor son tries to do updates.
			flag = FALSE;
			while(flag == FALSE) 
			{	
				semctl(sem_flag[1], 0, SETVAL, 1); //express interest in CS
				P(semid); //lock the process
				if(semctl(sem_flag[0], 0, GETVAL)){ //increment process
					semctl(sem_wait[0], 0, SETVAL, semctl(sem_wait[0], 0, GETVAL) + 1);
				}
				if(semctl(sem_flag[2], 0, GETVAL)){
					semctl(sem_wait[2], 0, SETVAL, semctl(sem_wait[2], 0, GETVAL) + 1);
				}
				printf("\nWait time for Dad: %d, Son 2: %d\n", semctl(sem_wait[0], 0, GETVAL), semctl(sem_wait[2], 0, GETVAL));

				fp3 = fopen("attempt" , "r+");
				fscanf(fp3, "%d", &N_Att);
				if(N_Att == 0)
				{
					fclose(fp3);
					flag = TRUE;
				}
				else
				{
					printf("Poor SON_1 wants to withdraw money.\n");
					fp2 = fopen("balance", "r+");
					fscanf(fp2,"%d", &bal2);
					printf("Poor SON_1 reads balance. Available Balance: %d \n", bal2);
					if (bal2 == 0)
					{
						fclose(fp2);
						fclose(fp3);
					}
					else
					{
						sleep(rand()%5);
						fseek(fp2,0L, 0);
						bal2 -=20;
						printf("Poor SON_1 write new balance: %d \n", bal2);
						fprintf(fp2,"%d\n", bal2);
						fclose(fp2);
						printf("poor SON_1 done doing update.\n");
						fseek(fp3,0L, 0);
						N_Att -=1;
						fprintf(fp3, "%d\n", N_Att);
						fclose(fp3);
					}
				}
				// semctl(sem_flag[1], 0, SETVAL, 0); //done with CS
				V(semid); //release the lock on process
			}
		}
		else
		{
		//Parent Process. Fork off one more child process.
			if ((pid = fork()) == -1) 
			{
				//fork failed!
				perror("fork");
				exit(1);
			}
			if (pid == CHILD)
			{
				printf("Second Son's Pid: %d\n",getpid());
				//Third child process. Second poor son tries to do updates.
				flag1 = FALSE;
				while(flag1 == FALSE) 
				{
					semctl(sem_flag[2], 0, SETVAL, 1); //express interest in CS
					P(semid); //lock the process
					if(semctl(sem_flag[0], 0, GETVAL)){ //increment process
						semctl(sem_wait[0], 0, SETVAL, semctl(sem_wait[0], 0, GETVAL) + 1);
					}
					if(semctl(sem_flag[1], 0, GETVAL)){
						semctl(sem_wait[1], 0, SETVAL, semctl(sem_wait[1], 0, GETVAL) + 1);
					}
					printf("\nWait time for Dad: %d, Son 1: %d\n", semctl(sem_wait[0], 0, GETVAL),
					semctl(sem_wait[1], 0, GETVAL));

					fp3 = fopen("attempt" , "r+");
					fscanf(fp3, "%d", &N_Att);
					if(N_Att == 0)
					{
						fclose(fp3);
						flag1 = TRUE;
					}
					else
					{
						printf("Poor SON_2 wants to withdraw money.\n");
						fp2 = fopen("balance", "r+");
						fscanf(fp2,"%d", &bal2);
						printf("Poor SON_2 reads balance. Available Balance: %d \n", bal2);
						if (bal2 == 0)
						{
							fclose(fp2);
							fclose(fp3);
						}
						else
						{
							sleep(rand()%5);
							fseek(fp2,0L, 0);
							bal2 -=20;
							printf("Poor SON_2 write new balance: %d \n", bal2);
							fprintf(fp2,"%d\n", bal2);
							fclose(fp2);

							printf("poor SON_2 done doing update.\n");
							fseek(fp3,0L, 0);
							N_Att -=1;
							fprintf(fp3, "%d\n", N_Att);
							fclose(fp3);
						}
					}
					// semctl(sem_flag[2], 0, SETVAL, 0); //done with CS
					V(semid); //release the lock on process
				}
			}
			else
			{
				//Now parent process waits for the child processes to finish
				pid = wait(&status);
				printf("Process(pid = %d) exited with the status %d. \n", pid, status);
			
				pid = wait(&status);
				printf("Process(pid = %d) exited with the status %d. \n", pid, status);
			
				pid = wait(&status);
				printf("Process(pid = %d) exited with the status %d. \n", pid, status);

				semkill(semid);
				semkill(sem_wait[0]);
				semkill(sem_wait[1]);
				semkill(sem_wait[2]);
				semkill(sem_flag[0]);
				semkill(sem_flag[1]);
				semkill(sem_flag[2]);

			}
			exit(0);
		}
		exit(0);
	}
	exit(0);
}
