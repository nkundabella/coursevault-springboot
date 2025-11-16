#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include <string>

using namespace std;

int main()
{
   string animals[] = {"elephant", "lion", "dolphin", "Dog", "Cat", "Tiger", "Lion", "Horse", "Monkey", "Bear", "Zebra"};

   string movies[] = {"Inception", "Spirited Away", "The Godfather", "Parasite", "Interstellar", "The Dark Knight", "Amélie",
                      "Everything Everywhere All at Once", "Gladiator", "The Grand Budapest Hotel"};

   string books[] = {"Harry Potter and the Sorcerer’s Stone", "The Lord of the Rings", "The Hobbit", "To Kill a Mockingbird", "1984", "Pride and Prejudice", "The Great Gatsby", "The Catcher in the Rye", "The Alchemist", "The Da Vinci Code"};

   string teams[] = {"FC Barcelona", "Real Madrid", "Atletico Madrid", "Sevilla FC", "Manchester United", "Liverpool FC", "Arsenal FC", "Chelsea FC", "Manchester City", "Tottenham Hotspur"};

   string districts[] = {"Gatsibo", "Nyabihu", "Kayonza", "Rwamagana", "Kirehe", "Ruhango", "Rulindo", "Muhanga", "Nyagatare", "Rubavu", "Nyarugenge", "Kicukiro", "Gasabo"};

   string exit;
   int chances = 10;

   while (exit != "exit")
   {

      exit = "";
      int choice;
      cout << setw(20) << "Choose a category you want" << endl;
      cout << "1:Animals" << endl;
      cout << "2:Movies" << endl;
      cout << "3:Books" << endl;
      cout << "4:Football teams" << endl;
      cout << "5:Districts(RW)" << endl
           << endl;
      cout << "-------------------------" << endl;
      cout << "Enter your choice: ";
      cin >> choice;

      if (cin.fail())
      {
         cin.clear();
         cin.ignore(1000, '\n');
         cout << "\n-------error----------\n";
         cout << "Invalid input";
         cout << "\n-------error----------" << endl;

         continue;
      }

      int size, index;
      char letter;
      string computerWord;

      if (choice == 1)
      {

         size = sizeof(animals) / sizeof(animals[0]);
         index = rand() % (size - 1);
         computerWord = animals[index];
         string guessedWord(computerWord.length(), ' ');

         for (int chances = 10; chances > 0; chances--)
         {
            cout << "Guess a letter in x animal:" << endl;
            cin >> letter;

            for (int j = 0; j < computerWord.length(); j++)
            {
               if (tolower(computerWord[j]) == tolower(letter))
               {
                  if (tolower(guessedWord[j]) != tolower(letter))
                  {
                     chances++;
                  }
                  guessedWord[j] = computerWord[j];
               }
               else
               {
                  if (!isalpha(guessedWord[j]))
                  {
                     guessedWord[j] = '_';
                  }
                  else
                  {
                     guessedWord[j] = guessedWord[j];
                  }
               }
            }
            cout << "Guessed " << guessedWord << endl;

            if (computerWord == guessedWord)
            {
               cout << "Congratulation you got it" << endl;
               cout << "Computer chose " << computerWord << endl;
               cout << "You guessed " << guessedWord << endl;
               break;
            }
         }

         if (computerWord != guessedWord)
         {
            cout << "Failed, the real animal was  " << computerWord << endl;
            cout << ".......Thank you for trying......." << endl;
         }
      }
      else if (choice == 2)
      {

         size = sizeof(movies) / sizeof(movies[0]);
         index = rand() % (size - 1);
         computerWord = movies[index];
         string guessedWord(computerWord.length(), ' ');
         for (int chances = 10; chances > 0; chances--)
         {
            cout << "Enter a letter in a movie name: " << endl;
            cin >> letter;
            for (int j = 0; j < computerWord.length(); j++)
            {
               if (tolower(computerWord[j]) == tolower(letter))
               {
                  if (tolower(guessedWord[j]) != tolower(letter))
                  {
                     chances++;
                  }
                  guessedWord[j] = computerWord[j];
               }
               else
               {
                  if (!isalpha(guessedWord[j]) && !isspace(guessedWord[j]))
                  {
                     guessedWord[j] = '_';
                  }
                  else
                  {
                     guessedWord[j] = guessedWord[j];
                  }
               }
            }
            cout << guessedWord << endl;
            if (computerWord == guessedWord)
            {
               cout << "........congratulations..........." << endl;
               cout << "You got it right!!" << endl;
               break;
            }
         }
         if (computerWord != guessedWord)
         {
            cout << "........Failed for now!.........." << endl;
            cout << "The real movie name was " << computerWord << endl;
         }
      }
      else if (choice == 3)
      {

         size = sizeof(books) / sizeof(books[0]);
         index = rand() % (size - 1);
         computerWord = books[index];
         string guessedBook(computerWord.length(), ' ');

         for (int chances = 10; chances > 0; chances--)
         {
            cout << "Guess the letter of the book name:" << endl;
            cin >> letter;
            for (int j = 0; j < computerWord.length(); j++)
            {
               if (tolower(computerWord[j]) == tolower(letter))
               {
                  if (tolower(guessedBook[j]) != tolower(letter))
                  {
                     chances++;
                  }
                  guessedBook[j] = computerWord[j];
               }
               else
               {
                  if (!isalpha(guessedBook[j]))
                  {     

                        guessedBook[j] = '_';
                    
                  }
                  else
                  {
                     guessedBook[j] = guessedBook[j];
                  }
               }
            }
            cout << "Guessed = " << guessedBook << endl;

            if (computerWord == guessedBook)
            {
               cout << "........congratulations..........." << endl;
               cout << "You got it right!!" << endl;
               break;
            }
         }
         if (computerWord != guessedBook)
         {
            cout << "........Failed for now!.........." << endl;
            cout << "The real book name was " << computerWord << endl;
         }
      }
      else if (choice == 4)
      {

         size = sizeof(teams) / sizeof(teams[0]);
         index = rand() % (size - 1);
         computerWord = teams[index];
         string guessedTeam(computerWord.length(), ' ');

         for (int chances = 10; chances > 0; chances--)
         {
            cout << "Enter the letter in any team:" << endl;
            cin >> letter;
            for (int j = 0; j < computerWord.length(); j++)
            {
               if (tolower(computerWord[j]) == towlower(letter))
               {
                  if (tolower(guessedTeam[j] != tolower(letter)))
                  {
                     chances++;
                  }
                  guessedTeam[j] = computerWord[j];
               }
               else
               {
                  if (!isalpha(guessedTeam[j]))
                  {
                     guessedTeam[j] = '_';
                  }
                  else
                  {
                     guessedTeam[j] = guessedTeam[j];
                  }
               }
            }
            cout << "Guessed = " << guessedTeam << endl;
            if (computerWord == guessedTeam)
            {
               cout << "........congratulations..........." << endl;
               cout << "You got it right!!" << endl;
               break;
            }
         }
         if (computerWord != guessedTeam)
         {
            cout << "........Failed for now!.........." << endl;
            cout << "The real book name was " << computerWord << endl;
         }
      }
      else if (choice == 5)
      {

         size = sizeof(districts) / sizeof(districts[0]);
         index = rand() % (size - 1);
         computerWord = districts[index];
         string guessedDistrict(computerWord.length(), ' ');

         for (int chances = 10; chances > 0; chances--)
         {
            cout << "Enter a letter in a district:" << endl;
            cin >> letter;

            for (int j = 0; j < computerWord.length(); j++)
            {
               if (tolower(computerWord[j]) == tolower(letter))
               {
                  if (towlower(guessedDistrict[j] != tolower(letter)))
                  {
                     chances++;
                  }
                  guessedDistrict[j] = computerWord[j];
               }
               else
               {
                  if (!isalpha(guessedDistrict[j]))
                  {
                     guessedDistrict[j] = '_';
                  }
                  else
                  {
                     guessedDistrict[j] = guessedDistrict[j];
                  }
               }
            }
            cout << "Guessed = " << guessedDistrict << endl;

            if (computerWord == guessedDistrict)
            {
               cout << "........congratulations..........." << endl;
               cout << "You got it right!!" << endl;
               break;
            }
         }
         if (computerWord != guessedDistrict)
         {
            cout << "........Failed for now!.........." << endl;
            cout << "The real book name was " << computerWord << endl;
         }
      }
      else
      {

         cout << "Option not found." << endl;
         break;
      }

      cout << "Type \"exit\" to exit: ";
      cin >> exit;
   }

   return 0;
}