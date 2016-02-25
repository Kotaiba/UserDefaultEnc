#ifndef __UserDefaultEnc__
#define __UserDefaultEnc__
//by Kotaiba Jabkji
#include <iostream>
#include "cocos2d.h"
#include "LevelHelper2API.h"

class UserDefaultEnc : public Node{
public:
    static UserDefaultEnc *getInstance();
    UserDefaultEnc();
    
    void setBoolForKey(std::string key,bool value);
    void setFloatForKey(std::string key,float value);
    void setIntegerForKey(std::string key,int value);
    void setStringForKey(std::string key,std::string value);
    
    bool getBoolForKey(std::string key);
    float getFloatForKey(std::string key);
    int getIntegerForKey(std::string key);
    std::string getStringForKey(std::string key);
    
private:
    static UserDefaultEnc *_instance;
    bool to_bool(std::string s);
    std::string encrypteData(std::string data);
    std::string decrypteData(std::string data);
    std::string base64_encode(const std::string &in) ;
    std::string base64_decode(const std::string &in) ;
};
#endif