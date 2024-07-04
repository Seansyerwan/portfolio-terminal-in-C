#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


void printportfolio(); //function declaration

//have structure made to display the info of the user
struct info {
	char* languages;
	char* name;
	char* place_of_study;
	int age;
	int projectsTotal;
	_Bool isStudent;
	
};

void printportfolio(struct info* const userInfo,FILE* fp) {
	printf("\n----------------------------------------\n");
	printf("Name: %s\nAge: %d", userInfo->name, userInfo->age);
	printf("\nProgramming languages known: %s\nProjects made: %d projects", userInfo->languages, userInfo->projectsTotal);
	if (userInfo->isStudent == 1) {
		printf("\n%s is a Student at %s", userInfo->name, userInfo->place_of_study);
	}
	printf("\n----------------------------------------\n");

	fputs("\n----------------------------------------\n",fp);
	fprintf(fp,"Name: %s\nAge: %d", userInfo->name, userInfo->age);
	fprintf(fp,"\nProgramming languages known: %s\nProjects made: %d projects\n", userInfo->languages, userInfo->projectsTotal, fp);
	if (userInfo->isStudent == 1) {
		fprintf(fp,"%s is a Student at %s", userInfo->name, userInfo->place_of_study);
	}
	fputs("\n----------------------------------------\n", fp);


}

int main() {
	FILE* fp;
	fp = fopen("file.txt", "w"); 
	struct info* userInfo,user;
	userInfo = &user;
	/*
	*Much of what this program does is use the struct pointer as seen above, and store the data inputted
	* by the user into the struct.
	*/


	//we need to allocate memory to each of the char pointers. as such, we give them 50 characters each.
	userInfo->name = (char*)malloc(50 * sizeof(char));
	userInfo->languages = (char*)malloc(100 * sizeof(char));
	userInfo->place_of_study = (char*)malloc(50 * sizeof(char));

	printf("What is your name? ");
	
	//to allow for spaces, we will use fgets
	fgets(userInfo->name, 50 * sizeof(char), stdin);
	userInfo->name[strcspn(userInfo->name, "\n")] = '\0';

	printf("\nWhat languages are you familiar in? ");
	fgets(userInfo->languages, 50 * sizeof(char), stdin);

	
	printf("\nWhat is your age? ");
	scanf("%d", &userInfo->age); //but since this is merely an int, we can just use scanf
	
	//now we need to see if they can be a student or not.
	if ((userInfo->age) >= 16) {
		printf("\nAre you studying at a University or other educational institution? \n 1- yes\n 0- no\n");
		scanf("%d", &userInfo->isStudent);

		
		getchar(); //skip this char

		if (userInfo->isStudent ==1) {
			printf("\nWhere are you studying? ");
			fgets(userInfo->place_of_study, 50 * sizeof(char), stdin);
		}

	}
	else {
		//we do not allow portfolios for people under 16.
		printf("\nERROR: USER HAS INPUTTED INVALID AGE, PORTFOLIO REJECTED."); 
		return -1;
	}

	printf("\nHow many projects have you made? ");
	
	scanf("%d", &userInfo->projectsTotal);
	
	if ((userInfo->projectsTotal) < 0) {
		printf("\nERROR: USER HAS INPUTTED INVALID PROJECT NUMBER, PORTFOLIO REJECTED.");
		return -1;
	}
	
	
	printportfolio(userInfo,fp);
	/*
	*we also free all the memory after usage. 
	*/
	free(userInfo->place_of_study);
	free(userInfo->languages);
	free(userInfo->name);
	fclose(fp);
	return 0;
}