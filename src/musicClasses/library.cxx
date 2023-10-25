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


/*TODO
  MAKE SURE THAT EVERY deleteObject METHOD
  ALSO REMOVES THE POINTER OF OTHER OBJECTS
  THAT WERE POINTING TO IT

  FOR EXAMPLE REMOVE THE TAG FROM A MUSIC
  OBJECT THAT HAS THE TAG YOU ARE DELETEING
*/

#include "library.hxx"
#include "music/baseMusic.hxx"
#include <cctype>
#include <queue>
#include <type_traits>
#include <unordered_map>

//removes a specific elemnt from a vector
template<class T>
void removeFromVector(std::vector<T>&, T);

//gives you all the alters, simple! I use std::set because duplicates can exist and that would be less than ideal :/
std::set<BaseMusic*> giveMeAllAlters(const BaseMusic*, std::unordered_map<BaseMusic*, std::vector<BaseMusic*>>&);

//gives you an all upper case version of the string
std::string getUpperCase(std::string);

//gives you an all lower case version of the string
std::string getLowerCase(std::string);

Library::Library(){
  
  // do something
}

Library::~Library(){
  // do something
}

void Library::clearAndDeleteLibrary(){
  for(auto artist : artists){
    delete artist;
  }
  for(auto song : music){
    //MAKE DA DECONSTRUCTOR FOR EVRY MUSIC CLASS
    delete song;
  }
  for(auto tag : tags){
    delete tag;
  }
}


bool Library::loadFromFile(std::string path){

  //some wrong happened
  return false;

  //sucess
  return true;
}

//=== manage music

bool Library::removeMusic(BaseMusic* targetSong){

  //the song is no longer offcially saved
  music.erase(targetSong);

  //remove this song from every tag
  for(auto tag : targetSong->getTags()){
    removeFromVector(tagToMusic[tag], targetSong);
  }

  //remove this song from every artist
  for(auto artist : targetSong->getArtists()){
    removeFromVector(artistToMusics[artist], targetSong);
  }

  //remove this song from any of the hashmaps/sets as a key
  MusicToAlters.erase(targetSong);
  sortedByDate.erase(targetSong);
  sortedByLength.erase(targetSong);

  
  //if a remix, remove it as a remix, if mashup remove it as a mashup
  switch(targetSong->whatAmI()){
    case BaseMusic::Remix:
      // //removes it as a remix
      // remixToOriginal.erase(static_cast<Remix*>(targetSong));
      //removes it from other as a remix
      removeFromVector(MusicToAlters[static_cast<Remix*>(targetSong)->getOriginal()], targetSong);
      break;
    case BaseMusic::Mashup:
      //remove itself from all of it's compund songs
      for(auto compound : static_cast<Mashup*>(targetSong)->getCompounds()){
        removeFromVector(MusicToAlters[compound], targetSong);
      }
      break;
  }
  
  //some wrong happened
  return false;

  //sucess
  return true;
}


bool Library::deleteMusic(BaseMusic* targetSong){

  //check if we can even remove this song
  if(!removeMusic(targetSong))
    return false;


  //the prevous statement removes the song from the library, there are no pointers pointing to it,
  //safe to delete
  delete targetSong;

  return true;

}

//adds a song to the Library
bool Library::addMusic(BaseMusic* targetMusic){
  
  switch(targetMusic->whatAmI()){
    case BaseMusic::Music:
      return addMusic(static_cast<Music*>(targetMusic));
    case BaseMusic::Remix:
      return addRemix(static_cast<Remix*>(targetMusic));
    case BaseMusic::Mashup:
      return addMashup(static_cast<Mashup*>(targetMusic));
    default:
      return false;      
  }

  //add the music to basic sorting data structures
  music.insert(targetMusic);
  sortedByDate.insert(targetMusic);
  sortedByLength.insert(targetMusic);


  //add the music and connect it to all of its alters
  MusicToAlters[targetMusic]=std::vector<BaseMusic*>();
  //very, very slow, very:
  for(auto singularMusic : music){

    //if it exist in any of the originals add it to the vector of the targetMusic
    switch(singularMusic->whatAmI()){
      case BaseMusic::Music:
        break;
      case BaseMusic::Remix:
        if(static_cast<Remix*>(singularMusic)->getOriginal()==targetMusic){
          MusicToAlters[targetMusic].push_back(singularMusic);
        }
        break;
      case BaseMusic::Mashup:
        {
          for(auto compound: static_cast<Mashup*>(singularMusic)->getCompounds()){
            if(compound==targetMusic){
              MusicToAlters[targetMusic].push_back(singularMusic);
              break;
            }
          }
          break;
        }
      default:
        //wat
        break;      
    }
  }


  //add the music and connect it to all of its tags
  for(auto tag : targetMusic->getTags()){
    tagToMusic[tag].push_back(targetMusic);
  }

  //add the music and connect to all of its artists
  for(auto artist : targetMusic->getArtists()){
    artistToMusics[artist].push_back(targetMusic);
  }
  
  //add the music and connect to all of its publisher
  publisherToMusics[targetMusic->getPublisher()].push_back(targetMusic);

  MusicToAlters[targetMusic]=std::vector<BaseMusic*>();
}

//all pointless
bool Library::addMusic(Music* targetMusic){}
bool Library::addRemix(Remix* targetMusic){}
bool Library::addMashup(Mashup* targetMusic){}


bool Library::updateMusic(BaseMusic* targetMusic){
  //use this instead:
  /*
    removeMusic(myMysic);
    //change the music object in any way
    addMusic(myMysic);

  */

  return false;
}

//=== retrieve/manage tags

std::set<Tag*> Library::getTags(std::string substring){
  std::set<Tag*> outputTags;

  //go through all tags and then through all aliases and check if the inputeed string is a substring of any of the aliases
  for(auto tag : tags){
    for(auto alias : tag->getAliases()){
      if(alias.find(substring)!=-1){
        outputTags.push_back(tag);
        break;
      }
    }
  }
  
  return outputTags;  
}


bool Library::addTag(Tag* in){
  tags.push_back(in);
  tagToMusic[in]=std::vector<BaseMusic*>();
}

bool Library::removeTag(Tag* in){
  removeFromVector(tags, in);
  tagToMusic.erase(in);
}

bool Library::deleteTag(Tag* in){

  //make sure no song has this as a tag and points to it
  for(auto song : tagToMusic[in]){
    song->removeTag(in);
  }
  removeTag(in);
}

//=== manage artists & publishers


std::vector<Artist*> Library::getArtists(std::string pattern){
  pattern=getLowerCase(pattern);
  std::vector<Artist*> output;

  //find all artists' names that contain the pattern
  for(auto artist : artistToMusics){
    if(getLowerCase(artist.first->getName()).find(pattern)!=-1){
      output.push_back(artist.first);
    }
  }

  return output;  
}

std::vector<Artist*> Library::getPublishers(std::string pattern){
  pattern=getLowerCase(pattern);
  std::vector<Artist*> output;

  //find all publishers' names that contain the pattern
  for(auto publisher : publisherToMusics){
    if(getLowerCase(publisher.first->getName()).find(pattern)!=-1){
      output.push_back(publisher.first);
    }
  }

  return output;  
}

std::vector<Artist*> Library::getArtistsAndPublishers(std::string pattern){
  pattern=getLowerCase(pattern);
  std::vector<Artist*> output;

  //find all artists' names that contain the pattern
  for(auto artist : artists){
    if(getLowerCase(artist->getName()).find(pattern)!=-1){
      output.push_back(artist);
    }
  }

  return output;  
}




bool Library::addArtist(Artist* in){
  artists.push_back(in);
  artistToMusics[in]=std::vector<BaseMusic*>();
  //no need to add the artist to the actual songs, addMusic does that
  return true;
}

bool Library::addPublisher(Artist* in){
  artists.push_back(in);
  publisherToMusics[in]=std::vector<BaseMusic*>();
  return true;
}

bool Library::eraseAsArtist(Artist* artist){
  
  for(auto song : publisherToMusics[artist]){
    song->removeArtist(artist);
  }
  artistToMusics.erase(artist);
  return true;
}

bool Library::eraseAsPublisher(Artist* publisher){
  for(auto song : publisherToMusics[publisher]){
    song->setPublisher(nullptr);
  }
  publisherToMusics.erase(publisher);
  return true;

}





bool Library::deleteArtistAndPublisher(Artist* in){
  if(!(eraseAsArtist(in) && eraseAsPublisher(in)))
    return false;

  removeFromVector(artists, in);
  delete in;

  return true;
}



//=== song retreval

std::vector<BaseMusic*> Library::giveMeSongsBasedOnTag(std::string substring){
  std::vector<BaseMusic*> output;

  std::vector<Tag*> tags=getTags(substring);

  for(auto tag : tags){
    std::vector<BaseMusic*> currentMusicWithTag=giveMeSongsBasedOnTag(tag);
    //https://stackoverflow.com/questions/3177241/what-is-the-best-way-to-concatenate-two-vectors
    output.reserve(output.size()+currentMusicWithTag.size()); //speeds things up by not allocating again and again? idk
    output.insert(output.end(), currentMusicWithTag.begin(), currentMusicWithTag.end());
  }

  return output;  

}

std::vector<BaseMusic*> Library::giveMeSongsBasedOnTag(Tag* tag){
  //simple hashtable look up................
  return tagToMusic[tag];
}

//FIX THIS std::set AND std::vector MESS LATER VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
std::vector<BaseMusic*> Library::giveMeSongsBasenOnTagInclusive(std::string substring){
  
  std::set<BaseMusic*> allAlters;
  std::vector<BaseMusic*> output;

  std::vector<Tag*> tags=getTags(substring);

  for(auto tag : tags){
    auto currentMusicWithTag=giveMeSongsBasenOnTagInclusive(tag);
    allAlters.insert(currentMusicWithTag.begin(), currentMusicWithTag.end());
  }

  //https://www.geeksforgeeks.org/convert-set-to-vector-in-cpp/
  output.reserve(allAlters.size());
  output.assign(allAlters.begin(), allAlters.end());
  return output;
  
}

//FIX THIS std::set AND std::vector MESS LATER VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
//this feels like a very slow solution, look into it later
std::vector<BaseMusic*> Library::giveMeSongsBasenOnTagInclusive(Tag* tag){
  
  auto originalMusic = tagToMusic[tag];
  std::set<BaseMusic*> allAlters(originalMusic.begin(), originalMusic.end());
  std::vector<BaseMusic*> output;
  
  //get the alters of the music because they technically have the same tag (yeah ik remixes can change the genre of the music, blah, blah, blah)
  //also get the alters of the alters and so on

  for(auto original : originalMusic){
    auto alters=giveMeAllAlters(original, MusicToAlters);
    allAlters.insert(alters.begin(), alters.end());
  }

  //https://www.geeksforgeeks.org/convert-set-to-vector-in-cpp/
  output.reserve(allAlters.size());
  output.assign(allAlters.begin(), allAlters.end());
  return output;
  
}


std::set<BaseMusic*> giveMeAllAlters(const BaseMusic* alter, std::unordered_map<BaseMusic*, std::vector<BaseMusic*>>& lookUpTable){

  //https://stackoverflow.com/questions/20052674/how-to-convert-vector-to-set
  std::vector<BaseMusic*> subAlters=lookUpTable[(BaseMusic*)alter];
  std::set<BaseMusic*> output= std::set(subAlters.begin(), subAlters.end());



  for(auto subAlter : subAlters){
    //get all the sub sub alters
    auto subOutput=giveMeAllAlters(subAlter, lookUpTable);
    //https://stackoverflow.com/questions/7089494/how-to-merge-multiple-sets-into-a-single-stdset-set-union
    output.insert(subOutput.begin(), subOutput.end());
  }

  return output;
}

std::vector<BaseMusic*> Library::giveMeSongsBasesOnArtist(std::string artistSubSTring){


}
std::vector<BaseMusic*> Library::giveMeSongsBasesOnArtist(Artist* artist){

}



template<class T>
void removeFromVector(std::vector<T>& elements, T element){
  for(auto i=elements.begin(); i!=elements.end(); i++){
    if((*i)==element){
      elements.erase(i);
      break;
    }  
  }

}


std::string getUpperCase(std::string str){
  for(auto& c : str){
    c=toupper(c);
  }
  return str;
}

std::string getLowerCase(std::string str){
  for(auto& c : str){
    c=tolower(c);
  }
  return str;
}





