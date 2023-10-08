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




#ifndef MUSIC
#define MUSIC

#include "baseMusic.hxx"

class Music : public BaseMusic{

  private:

    //tags are normal
    //artists are the original creators
    //name is relevant

    //the compaund songs/remixes used to make this one
    std::vector<BaseMusic*> remixesNMashups;
     
  public:


    type whatAmI();

    //get the remixes/mashups of this song
    std::vector<BaseMusic*> getAlterartions();
  
    //removes an altered version of the song
    void removeAlteration(int);

    //adds an altered version of the song
    void addAlteration(BaseMusic*);




};

#endif
