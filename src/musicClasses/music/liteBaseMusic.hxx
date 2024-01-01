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




#ifndef LITE_BASE_MUSIC
#define LITE_BASE_MUSIC

#include "../tag.hxx"
// #include "../artist.hxx"
#include <string>
#include <vector>
#include <ctime>

class Artist;

class BaseMusic{

  protected:

    enum type{Music, Remix, Mashup, Edit_Audio /*will never in my life use this but just in case*/};

    //is this music fully documented? all tags, all artists?
    bool done;
    
    // //tags used to identify the music
    // std::vector<Tag*> Tags;
  
    //the name of the music
    std::string name;

    // //the artist(s) who made the song
    // std::vector<Artist*> artists;

    // //the person who published the song on the given platform, not publisher of the song itself
    // Artist* publisher;
  
    // //when was this music made/published
    // time_t dateOfMaking;

    // //how long is this song? in seconds
    // unsigned int duration;

    //where is this song saved locally? you can include multiple files for different formats like wav or mp3
    std::vector<std::string> paths;

    //where is this song hosted on the internet? you can include multiple sources like youtube, and soundcloud
    std::vector<std::string> url;

     
  public:

    //tells you what kind of music this is: original music, remix, mashup, etc
    virtual type whatAmI() = 0;


    //==setters
    void setName(std::string);
    // void setLength(unsigned int);
    // void setDate(time_t);
    
    //==getters
  
    std::string getName();
    // unsigned int getLength();
    // time_t getDate();
    // std::vector<Artist*> getArtists();
    // Artist* getPublisher();
    // std::vector<Tag*> getTags();
    std::vector<std::string> getPaths();
    std::vector<std::string> getUrls();
    bool isFinished();
    
    //==adders
    void addPath(std::string);
    void addURL(std::string);
    // void addTag(Tag);
  
  
    //==removers

    //you need the index for these
    void removePath(int);
    void removeURL(int);
    // void removeTag(int);
  
  
  
  
    
};


#endif
