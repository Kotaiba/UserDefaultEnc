

#include "UserDefaultEnc.h"
#define encKey "kotjbkji"
UserDefaultEnc *UserDefaultEnc::_instance = nullptr;

UserDefaultEnc *UserDefaultEnc::getInstance() {
    if (!_instance) {
        _instance = new UserDefaultEnc();
    }
    
    return _instance;
}
UserDefaultEnc::UserDefaultEnc() {

}

//Set
void UserDefaultEnc::setFloatForKey(std::string key,float value){
    setStringForKey(key, StringUtils::format("%f",value).c_str());
}
void UserDefaultEnc::setBoolForKey(std::string key,bool value){
    setStringForKey(key, StringUtils::format("%i",value).c_str());
}
void UserDefaultEnc::setIntegerForKey(std::string key,int value){
    setStringForKey(key, StringUtils::format("%i",value).c_str());
}
void UserDefaultEnc::setStringForKey(std::string key,std::string value){
    std::string data= encryptedData(value);
    UserDefault::getInstance()->setStringForKey(key.c_str(), data);
}

//Get
bool UserDefaultEnc::getBoolForKey(std::string key){
    std::string data= getStringForKey(key);
    if (data=="") {
        return false;
    }
    bool value=to_bool(data);
    return value;
}
float UserDefaultEnc::getFloatForKey(std::string key){
    std::string data= getStringForKey(key);
    if (data=="") {
        return 0.0f;
    }
    float value=atof(data.c_str());;
    return value;
}
int UserDefaultEnc::getIntegerForKey(std::string key){
    std::string data= getStringForKey(key);
    if (data=="") {
        return 0;
    }
    int value =atoi(data.c_str());
    return value;
}
std::string UserDefaultEnc::getStringForKey(std::string key){
    std::string data=UserDefault::getInstance()->getStringForKey(key.c_str());
    if (data=="") {
        return "";
    }
   std::string value= decryptedData(data);
    return value;
}
//encrypte you can add your encrypte decrypte code and every thing will work fine
std::string UserDefaultEnc::encrypteData(std::string data){

    std::string encoded = base64_encode(data);
    return encoded;
}
std::string UserDefaultEnc::decrypteData(std::string data){
 
    return base64_decode(data);
}

bool UserDefaultEnc::to_bool(std::string  s) {
    return s != "0";
}

 std::string UserDefaultEnc::base64_encode(const std::string &in) {
    
    std::string out;
    
    int val=0, valb=-6;
    for (auto c : in) {
        val = (val<<8) + c;
        valb += 8;
        while (valb>=0) {
            out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[(val>>valb)&0x3F]);
            valb-=6;
        }
    }
    if (valb>-6) out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[((val<<8)>>(valb+8))&0x3F]);
    while (out.size()%4) out.push_back('=');
    return out;
}

std::string UserDefaultEnc::base64_decode(const std::string &in) {
    
    std::string out;
    
    std::vector<int> T(256,-1);
    for (int i=0; i<64; i++) T["ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[i]] = i;
    
    int val=0, valb=-8;
    for (auto c : in) {
        if (T[c] == -1) break;
        val = (val<<6) + T[c];
        valb += 6;
        if (valb>=0) {
            out.push_back(char((val>>valb)&0xFF));
            valb-=8;
        }
    }
    return out;
}
