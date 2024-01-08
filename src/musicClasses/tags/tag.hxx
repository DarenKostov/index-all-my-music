/*
Copyright (c) 2023 Daren Kostov

This file is part of index-all-my-music

index-all-my-music is free software: you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation,
either version 3 of the License, or (at your option) any later version.

index-all-my-music is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with index-all-my-music
If not, see <https://www.gnu.org/licenses/>.
*/



#ifndef TAG
#define TAG

#include <string>
#include <vector>

class Tag{

  public:
    //an entity is aperson or a company, they might upload or create music
    enum type{Generic, Entity};
  
  private:

    //all of the aliases of this tag
    std::vector<std::string> aliases;
  
    //the tags this tag must include by default
    std::vector<Tag*> parents;

    //the name of this Tag, a pointer to some alias in the aliases vector
    int nameIndex;

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

    //tells you what kind of tag this is: generic, entity, etc
    virtual type whatAmI() = 0;
  
    //gives you the description of this particular tag
    virtual std::string getDescription();

    //sets the description of this particular tag
    virtual std::string setDescription();

    //gives you the name of this tag (one of it's aliases)
    std::string getName();

    //gives you the index of name of this tag (one of it's aliases)
    int getNameIndex();

    //sets the name of this tag given an index of one of its aliases
    void setName(int);

    //sets the name of this tag given a string, the string will be added as the last alias
    void setName(std::string);


    //adds an alias
    void addAlias(std::string);
  
    //removes an alias at a certain index
    void removeAlias(int);
  
    //removes an alias with a specific name
    void removeAlias(std::string);

    //tells you weather or not this Tag has a certain alias
    bool hasAlias(std::string);
  
    //gives you the index of the alias with the same name as inputted; if it doesnt exist if returns -1
    int getAliasIndex(std::string);

    //tells you whether there is an alias that has this particular substring
    bool hasSubstringAsAlias(const std::string&) const;

    //gives you a vector of all the aliases
    std::vector<std::string> getAliases();
  
    //adds an parent
    void addParent(Tag*);
  
    //removes an parent at a certain index
    void removeParent(Tag*);

    //tells you weather or not this Tag has a certain parent
    bool hasParent(Tag*);
  
    //gives you a vector of all the parents
    std::vector<Tag*> getParents();

 
  private:

    //tells you whetether this index is possible in the alias vector
    bool indexWithinAliasRange(int);
  
};

#endif

