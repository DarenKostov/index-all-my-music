#include "tag.hxx"

bool Tag::indexWithinAliasRange(int index){
  if(index<0 || index>=aliases.size()){
    return false;
  }
  return true;
}


Tag::Tag(std::string initName){
  //add the only name and make its index the nameIndex
  aliases.push_back(initName);
  nameIndex=0;
}

Tag::Tag(std::string* initAlieases){
//add all the aliases from the pointer, make the 1st one the name
  for(std::string* i=0; i!=nullptr ;i++){
    aliases.push_back(*i);
  }
  nameIndex=0;

}

Tag::Tag(std::vector<std::string> initAliases){
  aliases=initAliases;
  nameIndex=0;
}

Tag::~Tag(){
  //do nothing
}

std::string Tag::getName(){
  if(nameIndex<0){
    return "no name";
  }
  
  return aliases[nameIndex];
}

int Tag::getNameIndex(){
  return nameIndex;
}

void Tag::setName(int newIndex){
  if(indexWithinAliasRange(newIndex)){
    //TODO handle exception
    return;
  }
  
  nameIndex=newIndex;
}

void Tag::addAlias(std::string newAlias){
  //TODO check if the alias already exists, don't add it if so
  aliases.push_back(newAlias);
}

void Tag::removeAlias(int aliasIndex){
  if(indexWithinAliasRange(aliasIndex)){
    //TODO handle exception
    return;
  }

  aliases.erase(aliases.begin()+aliasIndex);
  
  // if the current nameIndex is 0 and we wanna
  // delete the 0th index, the nameIndex will become
  // -1, meaning the getName method will return "no name"
  if(aliasIndex<=nameIndex){
    nameIndex--;
  }
  
}

void Tag::removeAlias(std::string alias){
  removeAlias(getAliasIndex(alias));
}

bool Tag::hasAlias(std::string alias){
  return getAliasIndex(alias)!=-1;
}

int Tag::getAliasIndex(std::string alias){
  for(int i=0; i<aliases.size(); i++){
    if(alias==aliases[i]){
      return i;
    }
  }

  //if we do not find the alias, the alias does not exist and we return -1;
  return -1;
  
}

bool Tag::hasSubstringAsAlias(const std::string& substring) const{

  for(auto alias : aliases){
    //is the substring found in the given alias?
    if(alias.find(substring)!=-1){
      return true;
    }
  }
  return false;

}

std::vector<std::string> Tag::getAliases(){
  return aliases;
}


void Tag::addParent(Tag* tag){
  //TODO check if the parent already exists, don't add it if so
  parents.push_back(tag);
}

void Tag::removeParent(Tag* tag){
  //TODO handle exception when tag doesn't exist
  
  for(auto i=parents.begin(); i!=parents.end(); i++){
    if((*i)==tag){
      parents.erase(i);
      break;
    }
  }

}

bool Tag::hasParent(Tag* tag){
  for(auto i=parents.begin(); i!=parents.end(); i++){
    if((*i)==tag){
      return true;
    }
  }
  
  return false;
}

std::vector<Tag*> Tag::getParents(){
  return parents;
}


