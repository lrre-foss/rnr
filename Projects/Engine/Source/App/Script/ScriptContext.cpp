#include <App/Script/ScriptContext.hpp>
#include <lualib.h>

namespace RNR
{
    static void* lua_allocator(void* ud, void* ptr, size_t osize, size_t nsize)
    {
        if(nsize == 0)
            free(ptr);
        else
            return realloc(ptr, nsize);
        return NULL;
    }

    ScriptContext::ScriptContext()
    {
        setName("Script Context");

        m_state = lua_newstate(lua_allocator, this);

        int libs = luaopen_base(m_state);
        lua_settop(m_state, -1 - libs);
        lua_pushcclosure(m_state, luaopen_string, "luaopen_string", 0);
        lua_pushstring(m_state, "string");
        lua_call(m_state, 1, 0);

        lua_pushcclosure(m_state, luaopen_math, "luaopen_math", 0);
        lua_pushstring(m_state, "math");
        lua_call(m_state, 1, 0);

        lua_pushcclosure(m_state, luaopen_table, "luaopen_table", 0);
        lua_pushstring(m_state, "table");
        lua_call(m_state, 1, 0);

        printf("ScriptContext::ScriptContext: created new lua state\n");
    }

    void ScriptContext::addScript(Script* script)
    {
        m_pendingScripts.push_back(script);
    }

    void ScriptContext::removeScript(Script* script)
    {
        auto script_it = std::find(m_scripts.begin(),m_scripts.end(),script);
        if(script_it != m_scripts.end())
        {
            m_scripts.erase(script_it);
        }
        script_it = std::find(m_pendingScripts.begin(), m_pendingScripts.end(), script);
        if(script_it != m_pendingScripts.end())
        {
            m_pendingScripts.erase(script_it);
        }
    }
}