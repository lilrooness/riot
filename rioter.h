#include <stdlib.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

struct rioter{
  int x;
  int y;
  int anger;
};

typedef struct rioter rioter;

rioter* new_rioters(int n) {
  rioter *r = (rioter*) malloc(sizeof(rioter)*n);
  return r;
}

rioter* new_rioter(int x, int y) {
  rioter *r = (rioter*) malloc(sizeof(rioter));
  r->x = x;
  r->y = y;
  return r;
}

void update_rioter(rioter *r, lua_State *l) {
  lua_getglobal(l, "update_rioter");
  lua_pushlightuserdata(l, r);
  lua_pcall(l, 1, 0, 0);
}

int getinfo(lua_State *l) {
  rioter *r = (rioter*) lua_topointer(l, -1);
  lua_pushinteger(l, r->x);
  lua_pushinteger(l, r->y);
  lua_pushinteger(l, r->anger);
  return 3;
}

int setinfo(lua_State *l) {
  rioter *r = (rioter*) lua_topointer(l, -1);
  lua_pop(l, 1);
  r->anger = lua_tointeger(l, -1);
  lua_pop(l, 1);
  r->y = lua_tointeger(l, -1);
  lua_pop(l, 1);
  r->x = lua_tointeger(l, -1);
  lua_pop(l, 1);
  return 0;
}
