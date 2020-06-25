#include <string>
#include <map>
#include <GarrysMod/Lua/Interface.h>

using namespace GarrysMod;

void mapToLuaTable(Lua::ILuaBase *LUA, const std::map<std::string, std::string>& map);
std::map<std::string, std::string> mapFromLuaTable(Lua::ILuaBase *LUA, int index);
