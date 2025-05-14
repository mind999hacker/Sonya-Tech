/*
 * SimpleMenu.h
 *
 *  Created on: May 7, 2025
 *      Author: mindhacker999
 */

//https://github.com/tinkersprojects/LCD-Simple-Menu-Library/blob/master/SimpleMenu.cpp

#ifndef INC_SIMPLEMENU_H_
#define INC_SIMPLEMENU_H_


#ifndef SimpleMenu_h
#define SimpleMenu_h

#include <cstddef>
#include <string>
#include <cstring>


char* stringToCharArray(const std::string& input);

class SimpleMenu
{
    public:
        SimpleMenu(int _numberMenuItems, SimpleMenu *_submenus); // Default constructor
        SimpleMenu(void (*_CallBack)()); // Constructor with callback function
        SimpleMenu(bool (*_ListCallBack)(int index), void (*_CallBack)()); // Constructor with list callback function and callback function
        SimpleMenu(bool (*_ListCallBack)(int index), SimpleMenu *_submenus); // Constructor with list callback function and submenus
        SimpleMenu(std::string _name,int _numberMenuItems, SimpleMenu *_submenus); // Constructor for sub menu
        SimpleMenu(std::string _name,int *_value); // Constructor for value menu
        SimpleMenu(std::string _name,int *_value, int _min, int _max); // Constructor for value menu with min and max
        SimpleMenu(std::string _name, void (*_CallBack)()); // Constructor for function menu
        SimpleMenu(std::string _name, bool (*_ListCallBack)(int index), SimpleMenu *_submenus); // Constructor for list menu with function
        SimpleMenu(std::string _name, bool (*_ListCallBack)(int index), void (*_CallBack)()); // Constructor for list menu with function

        void begin(); // Begin the menu
        void begin(void (*_displayCallBack)(SimpleMenu *_menu)); // Begin the menu with a display callback function
        void begin(void (*_displayCallBack)(SimpleMenu *_menu),void (*_valueCallBack)(SimpleMenu *_menu)); // Begin the menu with display and value callback functions
        void begin(SimpleMenu *_Top,void (*_displayCallBack)(SimpleMenu *_menu),void (*_valueCallBack)(SimpleMenu *_menu)); // Begin the menu with top menu, display callback, and value callback functions
        void setFunctions(void (*_displayCallBack)(SimpleMenu *_menu),void (*_valueCallBack)(SimpleMenu *_menu)); // Set the display and value callback functions

        void home(); // Go to the home menu
        void select(); // Select the current menu item
        void back(); // Go back to the previous menu
        void returned(); // Return to the previous menu
        void up(); // Move up in the menu
        void down(); // Move down in the menu
        void index(int _index); // Go to the menu item at the specified index

        SimpleMenu *next(); // Get the next menu item
        SimpleMenu *next(int index); // Get the next menu item starting from the specified index
        int getValue(); // Get the value of the current menu item
        bool hasValue(); // Check if the current menu item has a value
        int getIndex(); // Get the index of the current menu item
        void print(); // Print the menu

        std::string name; // Name of the menu
        bool selectMenu = false; // Flag indicating if the menu is selected
        int menuLocation = 0; // Current menu location

    private:
        SimpleMenu *Top_menu = NULL; // Top menu

        int numberMenuItems; // Number of menu items
        SimpleMenu *submenus = NULL; // Submenus
        SimpleMenu *subListmenus = NULL; // Submenus for list menu
        int *value = NULL; // Value of the menu item
        void (*CallBack) () = NULL; // Callback function
        bool (*ListCallBack)(int index) = NULL; // List callback function
        void (*displayCallBack)(SimpleMenu *_menu) = NULL; // Display callback function
        void (*valueCallBack)(SimpleMenu *_menu) = NULL; // Value callback function

        int min; // Minimum value for value menu
        int max; // Maximum value for value menu
        bool minMaxSet = false; // Flag indicating if min and max values are set
};






#endif

#endif /* INC_SIMPLEMENU_H_ */
