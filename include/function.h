#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<ctype.h>

#define NAME_LENGTH 50
#define FILE_NAME "Birthday_list.txt"

struct Birthday{
  char name[NAME_LENGTH];
  int day, month, year;

} b;

FILE *openFile(const char *fileName, const char *mode) {
  FILE *file = fopen(fileName, mode); 
  if (file == NULL) {
    printf("Can't open file %s", fileName);
    exit(0);
  }
  return file;
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int stringCmp(char name1[], char name2[]) {
  int len1 = strlen(name1);
  int len2 = strlen(name2);

  if (len1 != len2) return 0;

  for (int i = 0; i < len1; i++) {
    if (tolower(name1[i]) != tolower(name2[i])) return 0;
  }

  return 1;
}

int DOBValidator(int day, int month, int year) {
  time_t t = time(NULL);
  struct tm date = *localtime(&t);
  int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  if (month < 1 || month > 12) return 0;
  if (year > date.tm_year + 1900) return 0;
  if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
    daysInMonth[1] = 29; 
  }
  if (day < 1 || day > daysInMonth[month - 1]) return 0;

  return 1;
}

void createBirthday() {
  clearScreen();
  FILE *file = openFile(FILE_NAME, "a");
  int choice;

  printf("\t\t\t**Add Birthday**\n");
  printf("\n");
  do {
  printf("Enter name: ");
  scanf("%s", b.name);
  do {
  printf("Enter Date of Birth (dd/mm/yy): ");
  scanf("%2d/%2d/%4d", &b.day, &b.month, &b.year);
    if (DOBValidator(b.day, b.month, b.year)) {
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
  clearScreen();
  FILE *file = openFile(FILE_NAME, "r");

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
  clearScreen();

  char name[NAME_LENGTH];
  int choice; 
  int found = 0;
  printf("\t\t\t**Update Birthday**\n");
  printf("\n");
  do {
    FILE *file = openFile(FILE_NAME, "r");
    FILE *tempFile = openFile("temp.txt", "w");

    printf("Enter the name of the birthday to update: ");
    scanf("%s", name);

    while (fscanf(file, "%s %d %d %d", b.name, &b.day, &b.month, &b.year) != EOF) {
    if (stringCmp(b.name, name)) {
      do {
      found = 1;
      printf("Enter Date of Birth tto update (dd/mm/yy): ");
      scanf("%2d/%2d/%4d", &b.day, &b.month, &b.year);
      if (DOBValidator(b.day, b.month, b.year)) {
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
  clearScreen();

  char name[NAME_LENGTH];
  int found = 0;
  int choice, n; 
  printf("\t\t\t**Delete Birthday**\n");
  printf("\n");
  do {
    FILE *file = openFile(FILE_NAME, "r");
    FILE *tempFile = openFile("temp.txt", "w");
    printf("Enter the name of the birthday to delete: ");
    scanf("%s", name);
    printf("Confirm your deletion (1 to confirm/0 to cancel): ");
    scanf("%d", &n);  
    while (fscanf(file, "%s %d %d %d", b.name, &b.day, &b.month, &b.year) != EOF) {
      if (!stringCmp(b.name, name)) {
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
  if (n) {
  printf("Press 1 to continue/ 0 to stop: ");
  scanf("%d", &choice);
  } else {
    choice = 0;
  }

  } while (choice != 0);

}
void searchBirthday() {
  clearScreen();
  FILE *file = openFile(FILE_NAME, "r");

  char name[NAME_LENGTH];
  int found = 0;
  printf("\t\t\t**Search Birthday**\n");
  printf("\n");
  printf("Enter the name to search: ");
  scanf("%s", name);

  while (fscanf(file, "%s %d %d %d", b.name, &b.day, &b.month, &b.year) != EOF) {
    if (stringCmp(b.name, name)) {
      printf("\t\t%-30s\t%02d/%02d/%04d\n", b.name, b.day, b.month, b.year);
      found = 1;
  }
  }
  fclose(file);

  if (!found) {
    printf("Data not found!!!❌\n");
  } 

}

void upcoming() {
  clearScreen();
  time_t t = time(NULL);
  struct tm date = *localtime(&t);

  printf("\t\t\t**Upcoming Birthday**\n");
  printf("Current date is %02d-%02d-%d\n", date.tm_mday, date.tm_mon + 1, date.tm_year + 1900);
  printf("\n");
  FILE *file = openFile(FILE_NAME, "r");
  int found = 0;
  while (fscanf(file, "%s %d %d %d", b.name, &b.day, &b.month, &b.year) != EOF) {
    if (b.month == date.tm_mon + 1) {
      int currentAge = (date.tm_year + 1900) - b.year;
      found = 1;
      printf("\n%s is turning %d this month.\n", b.name, currentAge);
    }
  }
  if (!found) printf("\nNo upcoming birthday this month.❌\n");
}

void todayParty() {
  time_t t = time(NULL);
  struct tm date = *localtime(&t);

  FILE *file = openFile(FILE_NAME, "r");

  int found = 0;
  while (fscanf(file, "%s %d %d %d", b.name, &b.day, &b.month, &b.year) != EOF) {
    if ((b.day == date.tm_mday) && (b.month == date.tm_mon + 1)) {
      found = 1;
      printf("\n\t\tToday is %s's birthday. Let's Party!!!🎉🥳\n", b.name);
    }
  }
  if (!found) printf("\nNo Birthday Today😢\n");

}