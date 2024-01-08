/*
Copyright (c) 2024 Daren Kostov

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



#ifndef ENTITY
#define ENTITY

#include "tag.hxx"
#include <string>
#include <unordered_map>
#include <vector>



class Entity: public Tag{

  private:
    std::unordered_map<std::string, std::string> contactsOrWebsites;

  public:
    type whatAmI();

    //gives you all the contact information of the artist
    std::unordered_map<std::string, std::string> getContactsAndWebsites();

    //removes contact information of the artist  
    bool removeContactOrWebsite(std::string);

    //adds contact information to the artist
    bool setContactOrWebsite(std::string, std::string);
  
};

#endif
