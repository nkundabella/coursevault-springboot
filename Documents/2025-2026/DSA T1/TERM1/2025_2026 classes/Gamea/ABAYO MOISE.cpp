#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

void entering()
{
  cout << "Welcome to word guessing game \n";
  cout << "What you have to, is simply guess a word \n";
  cout << "Only ten attemps you have \n";
  cout << "+==================HERE WE GO====================+";
}

string readLine(int x)
{

  ifstream inputFile("word.txt");

  string line;

  int lineCount = 0;

  while (lineCount < x && getline(inputFile, line))
  {
    lineCount++;
  }

  inputFile.close();

  return line;
}

void display(int count, string some)
{
  for (int i = 0; i < count; i++)
  {

    cout << some[i] << "";
  }
  cout << endl;
}

string firstOne(int x)
{
  string newOne;
  newOne = "";
  newOne = string(x, '_');

  display(x, newOne);
  return newOne;
}
int main()
{
  srand(time(0));
  entering();
  string line, some;

  line = readLine(1 + (rand() % 25));
  int count = line.length();
  some = firstOne(count);
  cout << "\n It is " << count << " letter,  guess which it is \n\n";
  int counter = 10;

  while ((counter > 0) && (some.find('_') != string::npos))
  {
    char c;
    cin >> c;
    bool flag = false;
    int indexx = line.find(c);
    while (indexx != string::npos)
    {
      if (some[indexx] != c)
      {
        flag = true;
        some[indexx] = c;
      }
      else
      {
        cout << "You gave this letter before \n";
        break;
      }

      indexx = line.find(c, indexx + 1);
    }
    if (flag)
    {
      cout << "Correct guess \n";
    }
    else
    {
      cout << "Wrong guess \n";
      counter = counter - 1;
    }

    display(count, some);
    cout << "Attempts left: " << counter << "\n\n\n";
  }
  if (counter > 0)
  {
    cout << "You guessed correctly \n";
  }
  else
  {
    cout << "Attempts completed - Better luck next time \n";
  }
  cout << "The line was: " << line << endl;
}