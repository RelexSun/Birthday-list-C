#include<stdio.h>
#include "../include/function.h"

void createBirthday();
void readBirthday();
void updateBirthday();
void deleteBirthday();
void searchBirthday();
void upcomming();
void todayParty();

int main() {
  int choice;
  system("clear");
  while(1) {
    printf("\nBirthday List Management System\n");
    todayParty();
    printf("\n1. Add Birthday\n");
    printf("2. View Birthdays\n");
    printf("3. Update Birthday\n");
    printf("4. Delete Birthday\n");
    printf("5. Search Birthday\n");
    printf("6. Upcomming Birthday\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");

    if (scanf("%d", &choice) != 1) {
      printf("Invalid input. Please enter an integer.❌\n");

      // Clear the input buffer
      while (getchar() != '\n');

      continue;
  }
    switch (choice) {
      case 1: createBirthday(); break;
      case 2: readBirthday(); break;
      case 3: updateBirthday(); break;
      case 4: deleteBirthday(); break;
      case 5: searchBirthday(); break;
      case 6: upcomming(); break;
      case 7: exit(0); break;
      default: printf("Invalid choice, Please enter the right one!!!!❌\n");
    }
    choice = 0;
  } 

  return 0;
}