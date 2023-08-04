#pragma once
#include <App/V8/Tree/Instance.hpp>
#include <App/Script/Bridge.hpp>
#include <stdint.h>

#include <lua.h>

namespace RNR::Lua
{
    class ScriptContext;
    class Script : public Instance
    {
        ScriptContext* m_context;
        lua_State* m_state;
        std::string m_content;
        char* m_bytecode;
        size_t m_bytecodeSize;
    public:
        Script();
        Script(ScriptContext* context, std::string content);

        void compile();
        void load(lua_State* L);
        void setScriptContext(ScriptContext* context);
        void setScriptThread(lua_State* state);
        lua_State* getScriptThread() { return m_state; };
        virtual std::string getClassName() { return "Script"; }
        virtual void deserializeProperty(char* prop_name, pugi::xml_node prop);
    }; 
}