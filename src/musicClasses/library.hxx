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



#include <unordered_map>
#include "tag.hxx"
#include "music/baseMusic.hxx"
#include "music/music.hxx"
#include "music/remix.hxx"
#include "music/mashup.hxx"


class Library{
  private:
    //stores all the music here
    std::vector<BaseMusic*> music;
    std::vector<Tag*> tags;
    std::vector<Artist*> artists;

    //what tags a song has
    //if it is a remix it should include tags that describe what was midified
    std::unordered_map<Tag*, std::vector<BaseMusic*>> tagToMusic;

    //you give it a song and it gives you a list of its remixes/mashups
    //this BaseMusic* as key because you can get a remix of a remix of a mashup of an original song
    std::unordered_map<BaseMusic*, std::vector<BaseMusic*>> MusicToAlters;

    //you give it a remix and it gives you the original
    std::unordered_map<Remix*, BaseMusic*> remixToOriginal;

    //you give it a mashup and it gives you the originals in the form of a vector
    std::unordered_map<Mashup*, std::vector<BaseMusic*>> mashupToOriginals;

    //get the songs an artist has made
    std::unordered_map<Artist*, std::vector<BaseMusic*>> artistToMusics;

    //get the artist of a song
    std::unordered_map<BaseMusic*, Artist*> musicToArtist;
    

    public:
      //makes an empty library
      Library();
  
      //deconstructor
      ~Library();

      //load library from a file path (tags, songs and everything)
      bool loadFromFile(std::string);
      
      //adds a song to the Library
      bool addMusic(Music*);
      bool addRemix(Remix*);
      bool addMashup(Remix*);
      
  
  
  
  
        
  
};
