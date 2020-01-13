#ifndef __SILLY_CONFIG_H_
#define __SILLY_CONFIG_H_

#include <memory>
#include <string>
#include <unordered_map>
#include <yaml-cpp/yaml.h>
#include <list>
#include <set>
#include <iostream>

namespace Silly{

class ConfigVarBase
{
    public:
        typedef std::shared_ptr<ConfigVarBase> ptr; 
        /*
         * brief:Constructor
         * parameter [in] name : 配置变量的名字
         * parameter [in] description : 对配置变量进行描述
         * */
        ConfigVarBase(const std::string & name)
        :m_name(name)
        {  }
        
        std::string getName() const { return m_name;} 


        virtual ~ConfigVarBase() {}
    protected:
        std::string m_name;
}; 

template <typename T>
class ConfigVar : public ConfigVarBase
{
    public:
       typedef std::shared_ptr<ConfigVar> ptr;
       ConfigVar(const std::string & name,T val)
       :ConfigVarBase(name),
        m_val(val)
        {  }

       T getVal() const { return m_val; }

       void setVal(T val) { m_val = val; }
    private:
       T m_val;
};

class Config
{
    public:
        typedef std::unordered_map<std::string,ConfigVarBase::ptr> ConfigVarMap;
        /*
         * brief:根据配置变量名查找变量
         * */
        template<typename T>
        static typename ConfigVar<T>::ptr lookup(const std::string & name) {
             auto it = getData().find(name);
             if(it == getData().end()){
                 return nullptr;
             }
             else {
                 return std::dynamic_pointer_cast<ConfigVar<T>>(it->second);
             }
        }
        /*
         * brief:添加配置变量
         * */
        template <typename T>
        static void addConfig(const std::string & name,T val){
            if(getData().find(name) == getData().end()){
                typename ConfigVar<T>::ptr v(new ConfigVar<T>(name,val));
                getData()[name] = v;
            } 
        }
        
        /*
         * brief:加载yaml文件
         * */
        static void loadFromYaml(const std::string & file);
    private:
        /*
         * brief:存储所有配置信息
         * */
        static ConfigVarMap & getData(){
            static ConfigVarMap configs;
            return configs;
        }

        /*
         * brief:对yaml文件进行扁平化处理
         * */
        static void listAllMember(const std::string & prefix,const YAML::Node & node,
                                  std::list<std::pair<std::string,YAML::Node>> & output);
};

}// end of namespace 
#endif
