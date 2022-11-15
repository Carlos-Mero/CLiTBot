// Here is the definition of data structures used in our project.

struct Position{
    int x, y; // This is the position of the object, x refers to the columns and y the rows.
};

struct Light{
    Position pos;
    bool turned_on; // This describes whether the light is turned on or not.
};


