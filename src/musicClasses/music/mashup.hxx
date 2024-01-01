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




#ifndef MASHUP
#define MASHUP

#include "baseMusic.hxx"

class Mashup : public BaseMusic{

  private:

    //tags are used to identify what was changed in the song
    //artists are the people who altered the music
    //name is irrelevent, could be "SONG_NAME1 X SONG_NAME2 (this and that was changed)" 

    //the original songs used
    std::vector<BaseMusic*> compundSongs;
     
  public:

    type whatAmI();

    //gives you the compund songs used to make this one
    std::vector<BaseMusic*> getCompounds();

    //removes a compound song
    void removeCompund(int);

    //adds a compound song
    void addCompound(BaseMusic*);



};

#endif









