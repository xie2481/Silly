#include "../Silly/config.h"
#include "../Silly/log.h"
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <vector>
#include <string.h>

using namespace Silly;
using namespace std;

ConfigVar<int>::ptr test_ptr = Config::lookup<int>("system.port",8080);
ConfigVar<std::vector<int>>::ptr p_test_vec_int = Config::lookup<std::vector<int>>("system.vec_int",{1,2,3});
ConfigVar<std::map<std::string,int>>::ptr p_test_map_int = Config::lookup<std::map<std::string,int>>("system.map_int",
        {std::make_pair("one",1),std::make_pair("two",2)});

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
namespace Silly{
struct Person{
    std::string name = "张三";
    int age = 35;
    std::string sex = "男";
    std::string toString(){
        std::stringstream ss;
        ss << "[Person name = " << name 
            << " age = " << age << " sex = " << sex << " ]";
        return ss.str();
    }    

    bool operator==(const Person & other){
        return name == other.name &&
            age == other.age && sex == other.sex;
    }
};

template<>
class LexicalCast<Person,std::string>
{
    public:
        std::string operator()(const Person & person){
            YAML::Node node(YAML::NodeType::Map);
            node["name"] = person.name;
            node["age"] = person.age;
            node["sex"] = person.sex;
            std::stringstream ss;
            ss << node;
            return ss.str();
        }
};

template<>
class LexicalCast<std::string,Person>
{
    public:
        Person operator()(const std::string & val){
            YAML::Node node = YAML::Load(val);
            Person p;
            p.name = node["name"].Scalar();
            p.age = node["age"].as<int>();
            p.sex = node["sex"].Scalar();
            return p;
        }
};
}
ConfigVar<Person>::ptr p_test_person = Config::lookup<Person>("system.person",Person()); 
void test1(){
    SILLY_LOG_INFO("") << "before change" << p_test_person->getVal().toString();
    p_test_person->addListener([](const Person & oldPerson,const Person & newPerson){
            SILLY_LOG_INFO("") << "Change Person";
            });
    Config::loadFromYaml("/home/xie2481/Silly/bin/conf/log.yml");
    std::map<std::string,int> e = p_test_map_int->getVal();
    for(auto & i : e){
        SILLY_LOG_INFO("") << "key " << i.first << " value: " << i.second;
    }
    SILLY_LOG_INFO("") << "after change" << p_test_person->getVal().toString();
}

void test2(){
    LoggerManager::loadFromYaml("/home/xie2481/Silly/bin/conf/log.yml");
    SILLY_LOG_INFO("root") << "test logs";
}
int main(){
    /*Config::addConfig<int>("test",1,"这是测试");
    auto var = Config::lookup<int>("test");
    cout << var->getVal() << endl;*/
    //YAML::Node config = YAML::LoadFile("/home/xie2481/Silly/bin/conf/log.yml");
    //test(config,0);
    //LoggerManager::loadFromYaml("/home/xie2481/Silly/bin/conf/log.yml");
    //int count = 0;
    //std::string name = "log";
    /*while(count < 2){
        auto logger = LoggerManager::getLogger((name + std::to_string(count++)).c_str());
        logger->info("test");
    }*/
    //SILLY_LOG_EMERG("") << "create test" << 1;
    //SILLY_LOG_EMERG("root") << "create test" << 1;
   test2(); 
    return 0;
}
