#include <App/Script/ScriptContext.hpp>
#include <App/V8/World/World.hpp>
#include <lualib.h>

namespace RNR::Lua
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

        Vector3Bridge* v3b = new Vector3Bridge();
        registerBridge(v3b);
        InstanceBridge* ib = new InstanceBridge();
        registerBridge(ib);

        ib->fromInstance(m_state, world->getDatamodel());
        lua_setglobal(m_state, "game");
        ib->fromInstance(m_state, world->getWorkspace());
        lua_setglobal(m_state, "workspace");

        printf("ScriptContext::ScriptContext: created new lua state\n");
    }

    void ScriptContext::registerBridge(IBridge* bridge)
    {
        luaL_register(m_state, bridge->className().c_str(), bridge->classLibrary());
        lua_settop(m_state, -2);

        bridge->addMetatable(m_state);
    }

    void ScriptContext::addScript(Script* script)
    {
        printf("ScriptContext::addScript: new script %s pending\n", script->getName().c_str());
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

    void ScriptContext::update()
    {
        if(m_pendingScripts.size() != 0)
        {
            printf("ScriptContext::update: compiling %i new scripts\n", m_pendingScripts.size());
            for(auto script : m_pendingScripts)
            {
                lua_State* thread = lua_newthread(m_state);
                ((InstanceBridge*)IBridge::bridges["InstanceBridge"])->fromInstance(thread, script);
                lua_setglobal(thread, "script");
                script->compile();
                script->load(thread);
                m_scripts.push_back(script);
            }
            m_pendingScripts.clear();
        }
    }
}