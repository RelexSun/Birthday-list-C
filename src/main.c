#include<stdio.h>
#include "../include/function.h"

void createBirthday();
void readBirthday();
void updateBirthday();
void deleteBirthday();
void searchBirthday();
void upcomming();
void todayParty();
void BirthdayCalculator();
void clearScreen();
void displayMenu();

int main() {
  int choice;
  clearScreen();
  while(1) {
    displayMenu();
    printf("\t\t\t\t\t Enter your choice: ");
    scanf("%d", &choice);
    
    switch (choice) {
      case 1: createBirthday(); break;
      case 2: readBirthday(); break;
      case 3: updateBirthday(); break;
      case 4: deleteBirthday(); break;
      case 5: searchBirthday(); break;
      case 6: upcomming(); break;
      case 7: BirthdayCalculator(); break;
      case 8: exit(0); break;
      default: printf("Invalid choice, Please enter the right one!!!!❌\n");
    }
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
  } 
  return 0;
}