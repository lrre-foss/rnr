#include <App/Script/Script.hpp>
#include <App/Script/ScriptContext.hpp>

#include <Luau/Parser.h>
#include <Luau/Bytecode.h>
#include <Luau/Error.h>
#include <luacode.h>
#include <lualib.h>

namespace RNR
{
    Script::Script()
    {
        setName("Script");
        m_context = NULL;
        m_content = std::string("");
        m_bytecode = 0;
    }

    Script::Script(ScriptContext* context, std::string content) : Instance()
    {
        Script();

        m_context = context;
        m_content = content;

        m_context->addScript(this);
    }

    void Script::compile()
    {
        m_bytecode = luau_compile(m_content.c_str(), m_content.size(), NULL, &m_bytecodeSize);
        printf("Script::compile: compiled script (%i bytes)\n", m_bytecodeSize);        
    }

    void Script::load(lua_State* L)
    {
        if(!m_bytecode)
            throw new std::runtime_error("attempted to load uncompiled script\n");
        int result = luau_load(L, getName().c_str(), m_bytecode, m_bytecodeSize, 0);        
        if(result == 0)
            lua_call(L, 0, 0);
        else
            printf("Script::load: failed (%i)\n", lua_gettop(L));
    }
}