#ifndef __SILLY_CONFIG_H_
#define __SILLY_CONFIG_H_

#include "log.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <yaml-cpp/yaml.h>
#include <list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <iostream>
#include <typeinfo>
#include <boost/lexical_cast.hpp>
#include <functional>

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

        //将string转换为相应的值
        virtual void fromString(const std::string & str) = 0;

        //将值序列化为string
        virtual std::string toString() = 0;

        virtual ~ConfigVarBase() {}
    protected:
        std::string m_name;
}; 

/*
 * F:from F type
 * T:covert to T type
 * */
template<typename F,typename T>
class LexicalCast
{
    public:
        T operator()(const F & val){
            try{
                return boost::lexical_cast<T>(val);
            }catch(boost::bad_lexical_cast &){
                SILLY_LOG_ERROR("") << "Bad Transform from " << typeid(F).name() << " to " << typeid(T).name();
            }
            return T();
        }
};

/*
 * 提供片特化版本，用于stl容器的转换
 * */

/*
 * 将vector<T>转换为string
 * */
template<typename T>
class LexicalCast<std::vector<T>,std::string>
{
    public:
        std::string operator()(const std::vector<T> & val){
            YAML::Node node(YAML::NodeType::Sequence);
            for(auto & i : val){
                node.push_back(YAML::Load(LexicalCast<T,std::string>()(i)));
            }
            std::stringstream ss;
            ss << node;
            return ss.str();
        }
};

/*
 * 将string转换为vector
 * */
template<typename T>
class LexicalCast<std::string,std::vector<T>>
{
    public:
        std::vector<T> operator()(const std::string & val){
            std::vector<T> vec;
            YAML::Node node = YAML::Load(val);
            std::stringstream ss;
            for(size_t i = 0; i < node.size(); ++i){
                ss.str("");
                ss << node[i];
                vec.push_back(LexicalCast<std::string,T>()(ss.str()));
            }
            return vec;
        }
};

/*
 * 将set转换成string
 * */
template<typename T>
class LexicalCast<std::set<T>,std::string>
{
    public:
        std::string operator()(const std::set<T> & val){
            YAML::Node node(YAML::NodeType::Sequence);
            for(auto & i : val){
                node.push_back(YAML::Load(LexicalCast<T,std::string>()(i)));
            }
            std::stringstream ss;
            ss << node;
            return ss.str();
        }
};

/*
 * 将string转换成set
 * */
template<typename T>
class LexicalCast<std::string,std::set<T>>
{
    public:
        std::set<T> operator()(const std::string & val){
            std::set<T> s;
            YAML::Node node = YAML::Node(val);
            std::stringstream ss;
            for(size_t i = 0; i < node.size(); ++i){
                ss.str("");
                ss << node[i];
                s.insert(LexicalCast<std::string,T>(ss.str()));
            }
            return s;
        }
};

/*
 * 将list转换为string
 * */
template<typename T>
class LexicalCast<std::list<T>,std::string>
{
    public:
        std::string operator()(const std::list<T> & val){
            YAML::Node node(YAML::NodeType::Sequence);
            for(auto & i : val){
                node.push_back(YAML::Load(LexicalCast<T,std::string>()(i)));
            }
            std::stringstream ss;
            ss << node;
            return ss.str();   
        }
};

/*
 * 将string转换为list
 * */
template<typename T>
class LexicalCast<std::string,std::list<T>>
{
    public:
        std::list<T> operator()(const std::string & val){
            std::list<T> l;
            YAML::Node node = YAML::Load(val);
            std::stringstream ss;
            for(size_t i = 0; i < node.size();++i){
                ss.str("");
                ss << node[i];
                l.push_back(LexicalCast<std::string,T>(ss.str()));
            }
            return l;
        }
};

/*
 * 将unordered_set转换为string
 * */
template<typename T>
class LexicalCast<std::unordered_set<T>,std::string>
{
    public:
        std::string operator()(const std::unordered_set<T> & val){
            YAML::Node node(YAML::NodeType::Sequence);
            for(auto & i : val){
                node.push_back(YAML::Load(LexicalCast<T,std::string>()(i)));
            }
            std::stringstream ss;
            ss << node;
            return ss.str();
        }
};

/*
 * 将string转换为unordered_set
 * */
template<typename T>
class LexicalCast<std::string,std::unordered_set<T>>
{
    public:
        std::unordered_set<T> operator()(const std::string & val){
            YAML::Node node = YAML::Load(val);
            std::unordered_set<T> us;
            std::stringstream ss;
            for(size_t i = 0; i < node.size(); ++i){
               ss.str("");
               ss << node[i];
               us.insert(LexicalCast<std::string,T>()(ss.str())); 
            }
            return us;
        }
};

/*
 * 将map转换为string
 * */
template<typename T>
class LexicalCast<std::map<std::string,T>,std::string>
{
    public:
        std::string operator()(const std::map<std::string,T> & val){
            YAML::Node node(YAML::NodeType::Map);
            for(auto & it : val){
                node.force_insert(it.first,LexicalCast<T,std::string>()(it.second));
            }
            std::stringstream ss;
            ss << node;
            return ss.str();
        }
};

/*
 * 将string转换为map
 * */
template<typename T>
class LexicalCast<std::string,std::map<std::string,T>>
{
    public:
        std::map<std::string,T> operator()(const std::string & val){
            std::map<std::string,T> m;
            YAML::Node node = YAML::Load(val);
            for(auto it = node.begin(); 
                    it != node.end(); ++it){
                m.insert(std::make_pair(it->first.Scalar(),it->second.as<T>()));
            }
           return m; 
        }
};

/*
 * 将unordered_map转换为string
 * */
template<typename T>
class LexicalCast<std::unordered_map<std::string,T>,std::string>
{
    public:
        std::string operator()(const std::unordered_map<std::string,T> & val){
            YAML::Node node(YAML::NodeType::Map);
            for(auto & it : val){
                node.force_insert(it.first,LexicalCast<T,std::string>()(it.second));
            }
            std::stringstream ss;
            ss << node;
            return ss.str();
        }
};

/*
 * 将string转换为unordered_map
 * */
template<typename T>
class LexicalCast<std::string,std::unordered_map<std::string,T>>
{
    public:
        std::unordered_map<std::string,T> operator()(const std::string & val){
            std::unordered_map<std::string,T> m;
            YAML::Node node = YAML::Load(val);
            for(auto it = node.begin(); 
                    it != node.end(); ++it){
                m.insert(std::make_pair(it->first.Scalar(),it->second.as<T>()));
            }
           return m; 
        }
};

template <class T,class FromStr = LexicalCast<std::string,T>,
         class ToStr = LexicalCast<T,std::string>>
class ConfigVar : public ConfigVarBase
{
    public:
       typedef std::function<void(const T & oldVal,const T & newVal)> on_change_cb;
       typedef std::shared_ptr<ConfigVar> ptr;
       ConfigVar(const std::string & name,T val)
       :ConfigVarBase(name),
        m_val(val)
        {  }
        
       T getVal() const { return m_val; }

       void setVal(T val){ 
           if(m_val == val){
                return;
           }
            m_val = val;
            for(auto & cb : m_cbs){
                cb.second(val,m_val);
            }
       }
    
       std::string toString() override{
           return ToStr()(m_val);
       }

       void addListener(on_change_cb cb){
            static int count = 0;
            m_cbs.insert(std::make_pair(count++,cb));
       }
       void fromString(const std::string & str) override {
            setVal(FromStr()(str));
       }

       void deleteListener(uint64_t key){
            m_cbs.erase(key);
       } 

       void clearListener(){
            m_cbs.clear();
       }

       on_change_cb getListener(uint64_t key){
            auto it = m_cbs.find(key);
            return it == m_cbs.end() ? nullptr : it->second;
       }

    private:
       T m_val;
       //使用64位做hash
       std::unordered_map<uint64_t,on_change_cb> m_cbs;
};

class Config
{
    public:
        typedef std::unordered_map<std::string,ConfigVarBase::ptr> ConfigVarMap;
        /*
         * brief:根据配置变量名查找变量
         * */
        template<typename T>
        static typename ConfigVar<T>::ptr lookup(const std::string & name,T val) {
             auto it = getData().find(name);
             if(it == getData().end()){
                 typename ConfigVar<T>::ptr v(new ConfigVar<T>(name,val));
                 getData()[name] = v;
                 return v;
             }
             else {
                 return std::dynamic_pointer_cast<ConfigVar<T>>(it->second);
             }
        }
        
        static ConfigVarBase::ptr lookupBase(const std::string & name){
            auto it = getData().find(name);
            return it == getData().end() ? nullptr : it->second;
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
