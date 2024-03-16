#include <script/ScriptContext.hpp>

namespace RNR {
  void* ScriptContext::luaAllocator(void* ud, void* ptr, size_t osize, size_t nsize) {
    if(nsize == 0)
      free(ptr);
    else
      return realloc(ptr, nsize);
    ScriptContext* stxt = (ScriptContext*)ud;
    stxt->mem_usage = nsize - osize;
    return NULL; 
  }

  ScriptContext::ScriptContext() {
    state = lua_newstate(luaAllocator, this);
  }

  void ScriptContext::addScript(Script* script) {
    pending_scripts.push_back(script);
  }

  void ScriptContext::removeScript(Script* script) {
    auto itty = std::find(scripts.begin(), scripts.end(), script);
    if(itty != scripts.end())
      scripts.erase(itty);
    itty = std::find(pending_scripts.begin(), pending_scripts.end(), script);
    if(itty != pending_scripts.end())
      pending_scripts.erase(itty);
  }
}