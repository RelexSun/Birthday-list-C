#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

const int NAME_LENGTH = 50;
const char FILE_NAME[50] = "Birthday_list.txt";

typedef struct {
  char name[NAME_LENGTH];
  int day, month, year;

} Birthday;

// int fileValidation () {}

void createBirthday() {
  system("clear");
  FILE *file = fopen(FILE_NAME, "a");
  int choice;
  if (file == NULL) {
    printf("Can't open file!!!");
    exit(0);
  }
  Birthday b;
  do {
  printf("Enter name: ");
  scanf("%s", b.name);
  do {
  printf("Enter Date of Birth (dd/mm/yy): ");
  scanf("%2d/%2d/%4d", &b.day, &b.month, &b.year);
    if (b.day <= 31 && b.month <= 12) {
      break;
    } else {
      printf("Please make sure the Date of Birth is valid.\n");
    }
  } while (1);
  fprintf(file, "%s %d %d %d\n", b.name, b.day, b.month, b.year);
  printf("Birthday added successfully!!!\n");
  printf("Press 1 to continue/ 0 to stop: ");
  scanf("%d", &choice);
  } while (choice != 0);
  fclose(file);
}
void readBirthday() {
  system("clear");
  FILE *file = fopen(FILE_NAME, "r");

    if (file == NULL) {
    printf("Can't open file!!!");
    exit(0);
  }

  Birthday b;
  printf("\t\t\t**Birthday List**\n");
  printf("\n");
  printf("\t\t%-30s\tDD/MM/YYYY\n", "NAME");
  printf("\t-------------------------------------------------------------\n");
  while (fscanf(file, "%s %d %d %d", b.name, &b.day, &b.month, &b.year) != EOF) {
      printf("\t\t%-30s\t%02d/%02d/%04d\n", b.name, b.day, b.month, b.year);
  }
  fclose(file);
}

void updateBirthday() {
  system("clear");
  Birthday b;
  char name[NAME_LENGTH];
  int choice; 
  int found = 0;

  do {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
      printf("Can't find file!!!");
      exit(0);
    }
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
      printf("Can't find file!!!");
      exit(0);
    }
    printf("Enter the name of the birthday to update: ");
    scanf("%s", name);
    while (fscanf(file, "%s %d %d %d", b.name, &b.day, &b.month, &b.year) != EOF) {
    if (strcmp(b.name, name) == 0) {
      found = 1;
      printf("Enter day: ");
      scanf("%d", &b.day);
      printf("Enter month: ");
      scanf("%d", &b.month);
      printf("Enter year: ");
      scanf("%d", &b.year);
    }
    fprintf(tempFile, "%s %d %d %d\n", b.name, b.day, b.month, b.year);
  }

  if (!found) {
    printf("Data not found!!!\n");
    remove("temp.txt");
  } else {
    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);
    printf("Birthday updated!!!\n");
  }
  printf("Press 1 to continue/ 0 to stop: ");
  scanf("%d", &choice);
  fclose(file);
  fclose(tempFile);
  } while (choice != 0);

}

void deleteBirthday() {
  system("clear");
  Birthday b;
  char name[NAME_LENGTH];
  int found = 0;
  int choice; 

  do {
      FILE *file = fopen(FILE_NAME, "r");
      if (file == NULL) {
        printf("Can't find file!!!");
        exit(0);
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
      printf("Can't find file!!!");
      exit(0);
    }
    printf("Enter the name of the birthday to delete: ");
    scanf("%s", name);
    while (fscanf(file, "%s %d %d %d", b.name, &b.day, &b.month, &b.year) != EOF) {
      if (strcmp(b.name, name) != 0) {
        fprintf(tempFile, "%s %d %d %d\n", b.name, b.day, b.month, b.year);
      } else {
        found = 1;
      }
  }
  fclose(file);
  fclose(tempFile);

  if (found) {
    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);
    printf("Birthday deleted!!!\n");

  } else {
    printf("Data not found!!!\n");
    remove("temp.txt");
  }
  printf("Press 1 to continue/ 0 to stop: ");
  scanf("%d", &choice);

  } while (choice != 0);

}
void searchBirthday() {
  system("clear");
  FILE *file = fopen(FILE_NAME, "r");
  if (file == NULL) {
    printf("Can't find file!!!");
    exit(0);
  }

  Birthday b;
  char name[NAME_LENGTH];
  int found = 0;
  printf("Enter the name to search: ");
  scanf("%s", name);

  while (fscanf(file, "%s %d %d %d", b.name, &b.day, &b.month, &b.year) != EOF) {
    if (strcmp(b.name, name) == 0) {
      printf("\t\t%-30s\t%02d/%02d/%04d\n", b.name, b.day, b.month, b.year);
      found = 1;
  }
  }
  fclose(file);

  if (!found) {
    printf("Data not found!!!\n");
  } 

}

void upcomming() {
  time_t t = time(NULL);
  struct tm date = *localtime(&t);
  Birthday b;
  printf("Current date is %02d-%02d-%d\n", date.tm_mday, date.tm_mon + 1, date.tm_year + 1900);

  FILE *file = fopen(FILE_NAME, "r");
  if (file == NULL) {
      printf("Can't find file!!!");
      exit(0);
  }

  int notFound = 1;
  while (fscanf(file, "%s %d %d %d", b.name, &b.day, &b.month, &b.year) != EOF) {
    if (b.month == date.tm_mon + 1) {
      int currentAge = (date.tm_year + 1900) - b.year;
      notFound = 0;
      printf("\n%s is turning %d this month.\n", b.name, currentAge);
    }
  }
  if (notFound) printf("\nNo upcomming birthday this month.\n");
}