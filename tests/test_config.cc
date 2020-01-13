#include "../Silly/config.h"
#include "../Silly/log.h"
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <string.h>

using namespace Silly;
using namespace std;

void test(YAML::Node node,int level){
    if(node.IsScalar()){ 
        std::cout << node.Scalar() << "-" << node.Type();
    } else if(node.IsNull()){
        std::cout << "NULL -" << node.Type();
    } else if(node.IsMap()){
        for(auto it = node.begin();
                it != node.end(); ++it){
            std::cout << it->first << "-" << it->second.Type();        
            test(it->second,level+1);
        }
    } else if(node.IsSequence()){
        for(size_t i = 0; i < node.size(); ++i){
            std::cout << i << " - " << node[i].Type() << " - " << level;
            test(node[i],level+1);
        }
    }
}
int main(){
    /*Config::addConfig<int>("test",1,"这是测试");
    auto var = Config::lookup<int>("test");
    cout << var->getVal() << endl;*/
    //YAML::Node config = YAML::LoadFile("/home/xie2481/Silly/bin/conf/log.yml");
    //test(config,0);
    LoggerManager::loadFromYaml("/home/xie2481/Silly/bin/conf/log.yml");
    //int count = 0;
    //std::string name = "log";
    /*while(count < 2){
        auto logger = LoggerManager::getLogger((name + std::to_string(count++)).c_str());
        logger->info("test");
    }*/
    SILLY_LOG_EMERG("root") << "create test" << 1;
    SILLY_LOG_EMERG("root") << "create test" << 1;
    return 0;
}
