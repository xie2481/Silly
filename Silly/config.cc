#include "config.h"
#include "log.h"
#include <iostream>

namespace Silly{

/*
 * 最后的形式为key:A.B.C value:val的形式
 * */
void Config::listAllMember(const std::string & prefix,const YAML::Node & node,
                            std::list<std::pair<std::string,YAML::Node>> & output){
    if(node.IsNull()){
        return;
    }
    if(node.IsScalar()){
        output.push_back(std::make_pair(prefix,node));
        return;
    }
    if(node.IsMap()){
        for(auto it = node.begin(); 
                it != node.end(); ++it){
            if(prefix.empty()){
                listAllMember(it->first.Scalar(),it->second,output);
            } else {
                listAllMember(prefix + "." + it->first.Scalar(),it->second,output);
            }
        }
    } else if(node.IsSequence()){
        for(size_t i = 0; i < node.size(); ++i){
            output.push_back(std::make_pair(prefix,node[i]));
        }
    }

}

void Config::loadFromYaml(const std::string & file){
    YAML::Node root = YAML::LoadFile(file); 
    std::list<std::pair<std::string,YAML::Node>> output;
    std::unordered_map<std::string,int> dict;
    listAllMember("",root,output);
    for(auto & e : output){
        if(e.second.IsSequence()){//数组类型
          int count = dict[e.first]++;
          Config::addConfig<YAML::Node>(e.first + std::to_string(count),e.second);           
        } else if(e.second.IsScalar()){//向量类型
            Config::addConfig<std::string>(e.first,e.second.Scalar());
        } else if(e.second.IsMap()){//map类型
          int count = dict[e.first]++;
          Config::addConfig<YAML::Node>(e.first + std::to_string(count),e.second);           
        }
    }
}

}// end of namespace
