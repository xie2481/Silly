#include "config.h"
#include "log.h"
#include <iostream>

namespace Silly{

/*
 * 最后的形式为key:A.B.C value:val的形式
 * */
void Config::listAllMember(const std::string & prefix,const YAML::Node & node,
                            std::list<std::pair<std::string,YAML::Node>> & output){
    if(prefix.find_first_not_of("abcdefghijklmnopqrstuvwxyz._123456789") 
            != std::string::npos){
        SILLY_LOG_ERROR("") << "Invalid config name: " << prefix;
        return;
    }
    output.push_back(std::make_pair(prefix,node));
    if(node.IsMap()){
        for(auto it = node.begin(); 
                it != node.end(); ++it){
            if(prefix.empty()){
                listAllMember(it->first.Scalar(),it->second,output);
            } else {
                listAllMember(prefix + "." + it->first.Scalar(),it->second,output);
            }
        }
    }

}

void Config::loadFromYaml(const std::string & file){
    ReadScopeMutexLock<RWMutex> lock(getMutex());
    YAML::Node root = YAML::LoadFile(file); 
    std::list<std::pair<std::string,YAML::Node>> output;
    std::unordered_map<std::string,int> dict;
    listAllMember("",root,output);
    for(auto & e : output){
        std::string key = e.first;
        if(key.empty()){
            continue;
        }    
        auto var = Config::lookupBase(key);
        if(var){
            if(e.second.IsScalar()){
                var->fromString(e.second.Scalar());
            } else {
                std::stringstream ss;
                ss << e.second;
                var->fromString(ss.str());
            }
        }
    }
}

}// end of namespace
