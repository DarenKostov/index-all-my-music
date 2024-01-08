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




#ifndef BASE_MUSIC
#define BASE_MUSIC

#include "../tags/tag.hxx"
#include "../tags/entity.hxx"
#include <string>
#include <vector>
#include <ctime>

class Artist;

class BaseMusic{

  public:

    enum type{Music, Remix, Mashup, Edit_Audio /*will never in my life use this but just in case*/};


  protected:


    //is this song fully documented? all tags, all artists?
    bool done;
    
    //tags used to identify the music
    std::vector<Tag*> Tags;
  
    //the name (title?) of the music
    std::string name;

    //the artist(s) who made the song
    std::vector<Entity*> artists;

    //the entity who uploaded the song on the given platform
    Entity* uploader;
  
    //when was this music made/published
    time_t dateOfMaking;

    //how long is this song? in seconds
    unsigned int duration;

    //where is this song saved locally? you can include multiple files for different formats like wav or mp3
    std::vector<std::string> paths;

    //where is this song hosted on the internet? you can include multiple sources like youtube, and soundcloud
    std::vector<std::string> url;

     
  public:

    //tells you what kind of music this is: original music, remix, mashup, etc
    virtual type whatAmI() = 0;


    //==setters
    void setName(std::string);
    void setLength(unsigned int);
    void setDate(time_t);
    void setPublisher(Artist*);
    
    //==getters
  
    std::string getName()const;
    unsigned int getLength()const;
    time_t getDate()const;
    std::vector<Artist*> getArtists()const;
    Artist* getPublisher()const;
    std::vector<Tag*> getTags()const;
    std::vector<std::string> getPaths()const;
    std::vector<std::string> getUrls()const;
    bool isFinished()const;
    
    //==adders
    void addPath(std::string);
    void addURL(std::string);
    void addTag(Tag);
    void addArtist(Artist*);
  
    //==removers

    //you need the index for these
    void removePath(int);
    void removeURL(int);
    void removeTag(int);
    void removeArtist(Artist*);


    //you need the things themselves for these
    void removeTag(Tag*);
  
  
  
    
};


#endif
