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
  FILE *rfile = openFile(FILE_NAME, "r");
  int choice;

  printf("\t\t\t**Add Birthday**\n");
  printf("\n");
  do {
    int found;
    do {
      found = 0;
      FILE *rfile = openFile(FILE_NAME, "r");
      printf("Enter name: ");
      scanf("%s", b.name);
      int day, month, year;
      char name[NAME_LENGTH];

      while (fscanf(rfile, "%s %d %d %d", name, &day, &month, &year) != EOF) {
          if (strcmp(b.name, name) == 0) {
              found = 1;
              printf("\nName already exists.❌\n");
              break;
          }
      }
      fclose(rfile);
  } while (found);

  while (1) {
    printf("Enter Date of Birth (dd/mm/yyyy): ");
    if(scanf("%d/%d/%d", &b.day, &b.month, &b.year) == 3) {
      if (DOBValidator(b.day, b.month, b.year)) {
        break;
      } else {
        printf("Date of Birth is invalid.❌\n");
      }
    } else {
      printf("Date of birth is incomplete!!!\n");
    }
  }

  fprintf(file, "%s %2d %2d %4d\n", b.name, b.day, b.month, b.year);
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
  int choice = 0; 
  int found = 0;
  printf("\t\t\t**Update Birthday**\n");
  printf("\n");
  do {
    FILE *file = openFile(FILE_NAME, "r");
    FILE *tempFile = openFile("temp.txt", "w");

    printf("Enter the name of the birthday to update: ");
    scanf("%s", name);

    while (fscanf(file, "%s %d %d %d", b.name, &b.day, &b.month, &b.year) != EOF) {
    if (strcasecmp(b.name, name) == 0) {
      do {
        found = 1;
        printf("Enter Date of Birth to update (dd/mm/yyyy): ");
        if(scanf("%d/%d/%d", &b.day, &b.month, &b.year) == 3) {
          if (DOBValidator(b.day, b.month, b.year)) {
            break;
          } else {
            printf("Date of Birth is invalid.❌\n");
          }
        } else {
          printf("Date of birth is incomplete!!!\n");
        }
      } while (1);
    }
    fprintf(tempFile, "%s %2d %2d %4d\n", b.name, b.day, b.month, b.year);
  }

  if (!found) {
    printf("Data not found!!!\n");
    remove("temp.txt");
  } else {
    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);
    printf("Birthday updated!!!✅\n");
  }

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
    found = 0;
    while (fscanf(file, "%s %d %d %d", b.name, &b.day, &b.month, &b.year) != EOF) {
      if (strcasecmp(b.name, name) == 0) {
        found = 1;
        while (1) {
          printf("Confirm your deletion of %s's birthday (1 to confirm/0 to cancel): ", b.name);
          if (scanf("%d", &n) == 1 && (n == 1 || n == 0)) {
              break;
          } else {
              printf("Invalid input! Press any key...\n");
              getchar();
          }
        }
          if (n != 1) {
            fprintf(tempFile, "%s %d %d %d\n", b.name, b.day, b.month, b.year);
            found = 0;
        } 
      } else {
        fprintf(tempFile, "%s %d %d %d\n", b.name, b.day, b.month, b.year);
      }
      }

  fclose(file);
  fclose(tempFile);

  if (found) {
    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);
    printf("Birthday deleted!!!✅\n");
  
  } else {
    if (n == 0)
      printf("Deletion cancelled!!!\n");
    else
      printf("Data not found!!!❌\n");
    remove("temp.txt");
  }
    
    while (1) {
      printf("Press 1 to continue/ 0 to stop: ");
      if (scanf("%d", &choice) == 1 && (choice == 1 || choice == 0)) {
        break;
      } else {
        printf("Invalid input! Please enter 1 to continue or 0 to stop.\n");
        while (getchar() != '\n');
      }
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
    if (strcasecmp(b.name, name) == 0) {
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
  clearScreen();
  time_t t = time(NULL);
  struct tm date = *localtime(&t);

  printf("\t\t\t**Upcoming Birthday**\n");
  printf("Current date is %02d-%02d-%d\n", date.tm_mday, date.tm_mon + 1, date.tm_year + 1900);
  printf("\n");
  FILE *file = openFile(FILE_NAME, "r");
  int found = 0;
  int MonthDate[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if ((date.tm_year % 4 == 0 && date.tm_year % 100 != 0) || (date.tm_year % 400 == 0)) {
    MonthDate[1] = 29;
  }

  // int CurrentYear = date.tm_year + 1900;
  int CurrentMonth = date.tm_mon + 1;
  int CurrentDay = date.tm_mday;

  while (fscanf(file, "%s %d %d %d", b.name, &b.day, &b.month, &b.year) == 4) {
    int daysRemaining = 0;

    if (b.month == CurrentMonth && b.day > CurrentDay) {
      daysRemaining = b.day - CurrentDay;

    } else if (b.month > CurrentMonth) {
        daysRemaining = MonthDate[CurrentMonth - 1] - CurrentDay; 
        for (int i = CurrentMonth; i < b.month - 1; i++) {
          daysRemaining += MonthDate[i]; 
        }
      daysRemaining += b.day; 
    } else if (CurrentMonth == 12 && b.month == 1) {
      daysRemaining = MonthDate[11] - CurrentDay + b.day; 
    }

    if (daysRemaining <= 30 && daysRemaining > 0) {
      found = 1;
      int currentAge = (date.tm_year + 1900) - b.year;
      printf("%s's Birthday is in %d days and will be turning %d.\n", b.name, daysRemaining, currentAge);
    }
  }
    
  if (!found) printf("\nNo upcoming birthday this month.❌\n");
  fclose(file);
}

void todayParty() {
  time_t t = time(NULL);
  struct tm date = *localtime(&t);

  FILE *Pfile = openFile(FILE_NAME, "a+");
  FILE *file = openFile(FILE_NAME, "r");

  int found = 0;
  while (fscanf(file, "%s %d %d %d", b.name, &b.day, &b.month, &b.year) != EOF) {
    if ((b.day == date.tm_mday) && (b.month == date.tm_mon + 1)) {
      found = 1;
      printf("\n\t\t\t\tToday is %s's birthday. Let's Party!!!🎉🥳\n", b.name);
      printf("\n");
    }
  }
  if (!found) printf("\n\t\t\t\t\tNo Birthday Today😢\n");

  fclose(Pfile);
  fclose(file);

}

void BirthdayCalculator() {
  time_t t = time(NULL);
  struct tm date = *localtime(&t);
  int month, day, year;

  int CurrentYear = date.tm_year + 1900;
  int CurrentMonthDay = date.tm_mday;
  int CurrentMonth = date.tm_mon + 1;
  int daysLived = 0;
  int MonthDate[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if ((date.tm_year % 4 == 0 && date.tm_year % 100 != 0) || (date.tm_year % 400 == 0)) {
    MonthDate[1] = 29;
  }
  do {
    printf("Enter Date of Birth to calculate your age (dd/mm/yyyy): ");
    if(scanf("%d/%d/%d", &day, &month, &year) == 3) {
      if (DOBValidator(day, month, year)) {
        break;
      } else {
        printf("Date of Birth is invalid.❌\n");
      }
    } else {
      printf("Date of birth is incomplete!!!\n");
    }
  } while (1);

  int age = CurrentYear - year;
  if ((month > CurrentMonth) || (month == CurrentMonth && day > CurrentMonthDay)) {
    age -= 1;
  }

  daysLived = age * 365;
  for (int i = year; i <= CurrentYear; i++) {
    if ((i % 4 == 0 && i % 100 != 0) || (i % 400 == 0)) {
      daysLived += 1;
    }
  }
  daysLived += MonthDate[month - 1] - day;
  for (int i = month; i < CurrentMonth; i++) {
    daysLived += MonthDate[i];
  }
  daysLived -= MonthDate[CurrentMonth - 1] - CurrentMonthDay;

  printf("\n\t\t\t\tYour age is %d\n", age);
  printf("\n\t\t\t\tYou have live for %d days\n", daysLived);

}

void displayMenu() {
    clearScreen();
    printf("\n\t\t\t\t\t******************************\n");
    printf("\t\t\t\t\t*  Birthday List Management  *\n");
    printf("\t\t\t\t\t******************************\n");
    todayParty();
    printf("\t\t\t\t\t*                            *\n");
    printf("\t\t\t\t\t*  1. Add Birthday           *\n");
    printf("\t\t\t\t\t*  2. View Birthdays         *\n");
    printf("\t\t\t\t\t*  3. Update Birthday        *\n");
    printf("\t\t\t\t\t*  4. Delete Birthday        *\n");
    printf("\t\t\t\t\t*  5. Search Birthday        *\n");
    printf("\t\t\t\t\t*  6. Upcoming Birthday      *\n");
    printf("\t\t\t\t\t*  7. Birthday Calculator    *\n");
    printf("\t\t\t\t\t*  8. Exit                   *\n");
    printf("\t\t\t\t\t******************************\n");

}