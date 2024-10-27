// COMSC-210 | lab 24 | Kent Kawashima
// IDE used: Visual Studio Code
#include <iostream>
#include <fstream>
#include <iomanip>
#include <list> // for std::list
#include <random>
#include <time.h> //for better randomization
#include "Goat.h"
using namespace std;

// global variables
const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

// function prototypes
int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string colors[], string names[]);
void display_trip(list<Goat> trip);
int main_menu();

int main()
{
    srand(time(0));

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++])
        ;
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++])
        ;
    fin1.close();

    // note: names/colors arrays now full of values
    list<Goat> trip; // list of goats is called a trip?

    // my code
    bool again = true;

    while (again)
    {
        int choice = main_menu();
        switch (choice)
        {
        case (1):
        {
            add_goat(trip, colors, names); // pass list of trips, colors[], names[]
            cout << "Added goat!\n"; 
            break;
        }
        case (2):
        {
            delete_goat(trip); 
            break;
        }
        case (3):
        {
            display_trip(trip);
            break;
        }
        case (4): // break
        {
            again = false;
            break;
        }
        //NOTE: no default needed, as int choice validation is in main_menu() function
        }
    }

    return 0;
}

// functions**********************************

int main_menu()
{
    int choice;
    cout << "\n*** GOAT MANAGER 3001 ***\n[1] Add a goat\n[2] Delete a goat\n[3] List goats\n[4] Quit\nChoice --> ";
    cin >> choice;
    
    while (choice > 4 || choice < 1) // validation loop
    {
        cout << "Invalid choice, please choose one (1-4): ";
        cin >> choice;
    }
    return (choice);
}

void display_trip(list<Goat> trip) // displays all goats in the "trip"
{
    if (trip.empty())
    {
        cout << "Trip is empty\n"; //infinite loop
        return;
    }
    int i = 1; // keep track of iterations
    
    cout << "\n"; //formatting
    for (auto it = trip.begin(); it != trip.end(); ++it, ++i) // for each element in trip
    {
        cout << "[" << i << "] " << it->get_name() << "(" << it->get_age() << ", " << it->get_color() << ")\n"; // messy to read line, outputs something like: [5] Lena (12, Teal)
    }
    
}

int select_goat(list<Goat> trip)
{
    int index = -1;

    if (trip.size() > 0)
    {
        display_trip(trip); // display list of all first

        cout << "What is the index of the Goat that you want to remove: ";
        cin >> index;

        while (index > trip.size() || index < 1) // logic may be faulty
        {
            cout << "Please enter a valid value from 1-" << trip.size() << "! ";
            cin >> index;
        }
    }
    else // case empty trip
        cout << "No valid goats, try adding some first!\n";

    return (index-1);
}

void delete_goat(list<Goat> &trip)
{
    int posToDelete = select_goat(trip); // correct implementation of select?
    if(posToDelete == -1)
        return; //no valid target
    
    auto it = trip.begin();
    for (int i = 0; i < posToDelete; ++it, i++) // iterate "it" to correct location
    {
    }

    trip.erase(it);
}

void add_goat(list<Goat> &trip, string colors[], string names[])
{
    Goat temp;

    temp.set_name(names[rand() % SZ_NAMES + 1]);    // set temp's name to a random index of names[] array (1-200)
    temp.set_color(colors[rand() % SZ_COLORS + 1]); // set temp's color to a random index of colors[]] array (1-25)
    temp.set_age(rand() % (MAX_AGE + 1));                // set temp age to random num 0-20

    trip.push_front(temp); // add temp to the front of the list? Or back? could use push_back() in case of other.
}