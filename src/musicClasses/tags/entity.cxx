#include "entity.hxx"
#include "tag.hxx"

Tag::type Tag::whatAmI(){
  return Entity;
}

std::unordered_map<std::string, std::string> Entity::getContactsAndWebsites(){
  return contactsOrWebsites;
}

bool Entity::removeContactOrWebsite(std::string key){
  if(contactsOrWebsites.count(key)!=0){
    contactsOrWebsites.erase(key);
    return true;
  }
  return false;
}

bool Entity::setContactOrWebsite(std::string key, std::string info){
  contactsOrWebsites[key]=info;
  return true;
}

