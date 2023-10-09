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



#include <set>
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

    // //get the artist of a song
    // std::unordered_map<BaseMusic*, Artist*> musicToArtist;

    struct MusicDateComparator{
      bool operator()(const BaseMusic* music1, const BaseMusic* music2)const{
        return music1->getDate()<music2->getDate();
      }
    };
    struct MusicLengthComparator{
      bool operator()(const BaseMusic* music1, const BaseMusic* music2)const{
        return music1->getLength()<music2->getLength();
      }
    };

    //get music by date using equal_range, lower_bound, and upper_bound    
    std::set<BaseMusic*, MusicDateComparator> sortedByDate;

    //get music by duration equal_range, lower_bound, and upper_bound    
    std::set<BaseMusic*, MusicLengthComparator> sortedByLength;


    
    public:
      //makes an empty library
      Library();
  
      //deconstructor
      ~Library();

      //load library from a file path (tags, songs and everything)
      bool loadFromFile(std::string);

      //removes a song from the library
      bool removeMusic(BaseMusic*);
      
      //adds a song to the Library
      bool addMusic(Music*);
      bool addRemix(Remix*);
      bool addMashup(Remix*);


      //=== retrieve songs
      
      //gives you a list of songs, give you provide a tag in the form of a string or the a Tag itself
      std::vector<BaseMusic*> giveMeSongasBasedOnTag(std::string);
      std::vector<BaseMusic*> giveMeSongasBasedOnTag(Tag*);
      
      //gives you a list of songs (including remixes and mashups), give you provide a tag in the form of a string or the a Tag itself
      std::vector<BaseMusic*> giveMeSongsBasenOnTagInclusive(std::string);
      std::vector<BaseMusic*> giveMeSongsBasenOnTagInclusive(Tag*);
      
      //gives you a list of songs based on who's artist's name or pointer you give
      std::vector<BaseMusic*> giveMeSongsBasesOnArtist(std::string);
      std::vector<BaseMusic*> giveMeSongsBasesOnArtist(Artist*);
  
      //gives you a list of songs based on who's publisher's name or pointer you give
      std::vector<BaseMusic*> giveMeSongsBasesOnPublisher(std::string);
      std::vector<BaseMusic*> giveMeSongsBasesOnPublisher(Artist*);

      //gives you all the remixes of this song
      std::vector<BaseMusic*> giveMeRemixesOfSong(BaseMusic*);
        
      //gives you all the mashups that use this song
      std::vector<BaseMusic*> giveMeMashupsOfSong(BaseMusic*);

      //gives you all the remixes and mashups of this song
      std::vector<BaseMusic*> giveMeAltersOfSong(BaseMusic*);
  
      //gives you the original song of a particular remix
      BaseMusic* giveMeOriginalOfRemix(Remix*);
  
      //gives you the compound songs of a particular mashup
      std::vector<BaseMusic*> giveMeOriginalsOfMashup(Mashup*);

      //give it a tag and a vector of songs and itll remove songs with the specified tag
      void removeSongsWithATag(std::string, std::vector<BaseMusic*>&);
      void removeSongsWithATag(Tag*, std::vector<BaseMusic*>&);

      //give it a artist and a vector of songs and itll remove songs with the specified artist
      void removeSongsWithAnArtist(std::string, std::vector<BaseMusic*>&);
      void removeSongsWithAnArtist(Tag*, std::vector<BaseMusic*>&);
    
      //give it a publisher and a vector of songs and itll remove songs with the specified publisher
      void removeSongsWithAPublisher(std::string, std::vector<BaseMusic*>&);
      void removeSongsWithAPublisher(Tag*, std::vector<BaseMusic*>&);

      //get a list of songs that have the given substring in their name
      std::vector<BaseMusic*> getSongsWithName(std::string);
      
      //get a list of songs that have the given substring in their name, case sensitive
      std::vector<BaseMusic*> getSongsWithNameCaseSensitive(std::string);

      //gives you songs that were made/published in a specific time range
      std::vector<BaseMusic*> getSongsInTimeRange(time_t, time_t);
  
      //gives you songs that last a duration a between specific durations
      std::vector<BaseMusic*> getSongsInDurationRange(uint, uint);

      
  
  
  
  
  
  
};
