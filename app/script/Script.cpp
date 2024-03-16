#include "Script.hpp"
#include "Logger.hpp"

namespace RNR {
Script::Script() {
  bytecode = nullptr;
  bytecode_size = 0;
}

void Script::compile() {
  if (bytecode)
    free(bytecode);
  bytecode =
      luau_compile(content.c_str(), content.size(), NULL, &bytecode_size);
  DEV_LOGMSGF("Compiled script (%i bytes)", bytecode_size);
}

void Script::load(lua_State *L) {
  if (!state)
    throw new std::runtime_error("attempted to load script with no thread");
  if (!bytecode)
    throw new std::runtime_error("attempted to load uncompiled script");
  try {
    int result = luau_load(state, "script", bytecode, bytecode_size, 0);
    if (result == 0)
      lua_resume(state, L, 0);
    else
      DEV_LOGMSGF("failed (%i)", lua_gettop(L));
  } catch (std::exception &error) {
    DEV_LOGMSGF("runtime error '%s'\n%s", error.what(), lua_debugtrace(L));
  }
}
}; // namespace RNR