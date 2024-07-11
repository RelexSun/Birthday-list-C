#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

const int NAME_LENGTH = 50;
const char FILE_NAME[50] = "Birthday_list.txt";

  struct Birthday{
  char name[NAME_LENGTH];
  int day, month, year;

} b;

void fileValidation (FILE *file) {
  if (file == NULL) {
      printf("Can't find file!!!");
      exit(0);
  }
}

void createBirthday() {
  system("clear");
  FILE *file = fopen(FILE_NAME, "a");
  int choice;

  fileValidation(&file);

  do {
  printf("Enter name: ");
  scanf("%s", b.name);
  do {
  printf("Enter Date of Birth (dd/mm/yy): ");
  scanf("%2d/%2d/%4d", &b.day, &b.month, &b.year);
    if ((b.day <= 31 && b.month <= 12) && (b.day > 0 && b.month > 0)) {
      break;
    } else {
      printf("Date of Birth is invalid.❌\n");
    }
  } while (1);
  fprintf(file, "%s %d %d %d\n", b.name, b.day, b.month, b.year);
  printf("Birthday added successfully!!!✅\n");
  printf("Press 1 to continue/ 0 to stop: ");
  scanf("%d", &choice);
  } while (choice != 0);
  fclose(file);
}

void readBirthday() {
  system("clear");
  FILE *file = fopen(FILE_NAME, "r");

  fileValidation(&file);

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

  char name[NAME_LENGTH];
  int choice; 
  int found = 0;

  do {
    FILE *file = fopen(FILE_NAME, "r");
    fileValidation(&file);
    FILE *tempFile = fopen("temp.txt", "w");
    fileValidation(&tempFile);
    printf("Enter the name of the birthday to update: ");
    scanf("%s", name);
    while (fscanf(file, "%s %d %d %d", b.name, &b.day, &b.month, &b.year) != EOF) {
    if (strcmp(b.name, name) == 0) {
      do {
      found = 1;
      printf("Enter Date of Birth tto update (dd/mm/yy): ");
      scanf("%2d/%2d/%4d", &b.day, &b.month, &b.year);
      if ((b.day <= 31 && b.month <= 12) && (b.day > 0 && b.month > 0)) {
        break;
      } else {
        printf("Date of Birth is invalid.❌\n");
      }
  } while (1);
    }
    fprintf(tempFile, "%s %d %d %d\n", b.name, b.day, b.month, b.year);
  }

  if (!found) {
    printf("Data not found!!!\n");
    remove("temp.txt");
  } else {
    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);
    printf("Birthday updated!!!✅\n");
  }
  printf("Press 1 to continue/ 0 to stop: ");
  scanf("%d", &choice);
  fclose(file);
  fclose(tempFile);
  } while (choice != 0);

}

void deleteBirthday() {
  system("clear");

  char name[NAME_LENGTH];
  int found = 0;
  int choice; 

  do {
    FILE *file = fopen(FILE_NAME, "r");
    fileValidation(&file);

    FILE *tempFile = fopen("temp.txt", "w");
    fileValidation(&tempFile);
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
    printf("Birthday deleted!!!✅\n");

  } else {
    printf("Data not found!!!❌\n");
    remove("temp.txt");
  }
  printf("Press 1 to continue/ 0 to stop: ");
  scanf("%d", &choice);

  } while (choice != 0);

}
void searchBirthday() {
  system("clear");
  FILE *file = fopen(FILE_NAME, "r");
  fileValidation(&file);

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
    printf("Data not found!!!❌\n");
  } 

}

void upcomming() {
  system("clear");
  time_t t = time(NULL);
  struct tm date = *localtime(&t);

  printf("Current date is %02d-%02d-%d\n", date.tm_mday, date.tm_mon + 1, date.tm_year + 1900);

  FILE *file = fopen(FILE_NAME, "r");
  fileValidation(&file);
  int found = 0;
  while (fscanf(file, "%s %d %d %d", b.name, &b.day, &b.month, &b.year) != EOF) {
    if (b.month == date.tm_mon + 1) {
      int currentAge = (date.tm_year + 1900) - b.year;
      found = 1;
      printf("\n%s is turning %d this month.\n", b.name, currentAge);
    }
  }
  if (!found) printf("\nNo upcomming birthday this month.❌\n");
}

void todayParty() {

  time_t t = time(NULL);
  struct tm date = *localtime(&t);

  FILE *file = fopen(FILE_NAME, "r");
  fileValidation(&file);
  int found = 0;
  while (fscanf(file, "%s %d %d %d", b.name, &b.day, &b.month, &b.year) != EOF) {
    if ((b.day == date.tm_mday) && (b.month == date.tm_mon + 1)) {
      found = 1;
      printf("\nToday is %s's birhday. Let's Party!!!🎉🥳\n", b.name);
    }
  }
  if (!found) printf("\nNo Birthday Today😢\n");

}