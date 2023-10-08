/*
Copyright (c) 2023 Daren Kostov

This file is part of index-all-my-musi

index-all-my-musi is free software: you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation,
either version 3 of the License, or (at your option) any later version.

index-all-my-musi is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with index-all-my-musi
If not, see <https://www.gnu.org/licenses/>.
*/



#ifndef TAG
#define TAG

#include <string>
#include <vector>

class Tag{

  private:

    //all of the aliases of this tag
    std::vector<std::string> aliases;

    //the name of this Tag, a pointer to some alias in the aliases vector
    std::string* name;

    //a description of this tag
    std::string description;

 
  public:
    
    //constructor with name
    Tag(std::string);

    //constructor with an array of aliases, MUST have last element as NULL; 1st alias is set to the name
    Tag(std::string*);
  
    //constructor with a vector of aliases; 1st alias is set to the name
    Tag(std::vector<std::string>);

    //deconstructor
    ~Tag();

    //adds an alias
    void addAlias(std::string);

    //gives you the name of this tag (one of it's aliases)
    std::string getName();

    //sets the name of this tag given an index of one of its aliases
    void setName(int);

    //removes an alias at a certain index
    void removeAlias(int);

    //tells you weather or not this Tag has a certain alias
    bool hasAlias(std::string);

    //gives you a vector of all the aliases
    std::vector<std::string> getAliases();

};

#endif

