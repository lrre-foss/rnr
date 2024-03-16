#pragma once
#include <v8tree/Instance.hpp>
#include <script/Script.hpp>
namespace RNR {
class ScriptContext : public Instance {
  lua_State* state;
  size_t mem_usage;

  std::vector<Script*> pending_scripts;
  std::vector<Script*> scripts;

  static void* luaAllocator(void* ud, void* ptr, size_t osize, size_t nsize);
public:
  ScriptContext();

  void addScript(Script* script);
  void removeScript(Script* script);
};
} // namespace RNR