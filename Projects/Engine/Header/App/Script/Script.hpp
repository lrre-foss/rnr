#pragma once
#include <App/V8/Tree/Instance.hpp>
#include <stdint.h>

#include <lua.h>

namespace RNR
{
    class ScriptContext;
    class Script : public Instance
    {
        ScriptContext* m_context;
        std::string m_content;
        char* m_bytecode;
        size_t m_bytecodeSize;
    public:
        Script();
        Script(ScriptContext* context, std::string content);

        void compile();
        void load(lua_State* L);
        virtual std::string getClassName() { return "Script"; }
    }; 
}