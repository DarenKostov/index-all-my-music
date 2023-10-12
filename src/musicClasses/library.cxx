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
#include <type_traits>

//removes a specific elemnt from a vector
template<class T>
void removeFromVector(std::vector<T>&, T);


Library::Library(){
  
  // do something
}

Library::~Library(){
  // do something
}

void Library::clearLibrary(){
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
  //very, very slow:
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

std::vector<Tag*> Library::getTags(std::string substring){
  std::vector<Tag*> outputTags;

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

  //make sure no song has this as a tag and point to it
  for(auto song : tagToMusic[in]){
    song->removeTag(in);
  }

  removeTag(in);
  
}


template<class T>
void removeFromVector(std::vector<T>& elements, T element){
  for(auto i=elements.begin(); i!=elements.end(); i++){
    if((*i)==element){
      elements.erase(i);
    }  
  }

}
