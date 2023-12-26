#include "tag.hxx"



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

bool Tag::hasSubstringAsAlias(const std::string& substring) const{

  for(auto alias : aliases){
    //is the substring found in the given alias?
    if(alias.find(substring)!=-1){
      return true;
    }
  }
  return false;

}


