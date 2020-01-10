#ifndef __SILLY_CONFIG_H_
#define __SILLY_CONFIG_H_

#include <memory>
#include <string>
#include <unordered_map>

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
        ConfigVarBase(const std::string & name,const std::string & description)
        :m_name(name),
        m_description(description) 
        {  }
        
        std::string getName() const { return m_name;} 

        std::string getDescription() const { return m_description; }

        virtual ~ConfigVarBase() {}
    protected:
        std::string m_name;
        std::string m_description;
}; 

template <typename T>
class ConfigVar : public ConfigVarBase
{
    public:
       typedef std::shared_ptr<ConfigVar> ptr;
       ConfigVar(const std::string & name,T val , const std::string & description)
       :ConfigVarBase(name,description),
        m_val(val) 
        {  }

       T getVal() const { return m_val; }
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
        static void addConfig(const std::string & name,T val,const std::string & description){
            if(getData().find(name) == getData().end()){
                typename ConfigVar<T>::ptr v(new ConfigVar<T>(name,val,description));
                getData()[name] = v;
            } 
        }

    private:
        /*
         * brief:存储所有配置信息
         * */
        static ConfigVarMap & getData(){
            static ConfigVarMap configs;
            return configs;
        }
};

}// end of namespace 
#endif
