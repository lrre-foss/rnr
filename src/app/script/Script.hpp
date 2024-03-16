#pragma once
#include <v8tree/Instance.hpp>

#include <Luau/Parser.h>
#include <Luau/Bytecode.h>
#include <Luau/Error.h>
#include <lua.h>
#include <luacode.h>
#include <lualib.h>

namespace RNR {
  class ScriptContext;

  class Script : public Instance {
    std::string content;
    char* bytecode;
    size_t bytecode_size;

    lua_State* state;
    ScriptContext* context;
  public:
    Script();

    void compile();
    void load(lua_State* L);
    
    void setScriptState(lua_State* L) { state = L; }
    lua_State* getScriptState() { return state; }
    void setScriptContext(ScriptContext* context) { this->context = context; }
    ScriptContext* getScriptContext() { return context; }
  };
};