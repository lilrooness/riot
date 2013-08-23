#include <stdlib.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <math.h>

struct rioter{
  int x;
  int y;
  double vx;
  double vy;
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
  r->vx = 0.0;
  r->vy = 0.0;
  return r;
}

void update_rioter(rioter *r, lua_State *l) {
  lua_getglobal(l, "update_rioter");
  lua_pushlightuserdata(l, r);
  lua_pcall(l, 1, 0, 0);
}

int getinfo(lua_State *l) {
  rioter *r = (rioter*) lua_topointer(l, -1);
  lua_pop(l, 1);
  lua_pushinteger(l, r->x);
  lua_pushinteger(l, r->y);
  lua_pushnumber(l, r->vx);
  lua_pushnumber(l, r->vy);
  lua_pushinteger(l, r->anger);
  return 5;
}

int setinfo(lua_State *l) {
  rioter *r = (rioter*) lua_topointer(l, -1);
  lua_pop(l, 1);
  r->anger = lua_tointeger(l, -1);
  lua_pop(l, 1);
  r->vy = lua_tonumber(l, -1);
  lua_pop(l, 1);
  r->vx = lua_tonumber(l, -1);
  lua_pop(l, 1);
  r->y = lua_tointeger(l, -1);
  lua_pop(l, 1);
  r->x = lua_tointeger(l, -1);
  lua_pop(l, 1);
  return 0;
}

int get_prox_rioters(lua_State *l) {
  rioter *r = (rioter*) lua_topointer(l, -1);
  lua_pop(l, 1);
  rioter *crowd = (rioter*) lua_topointer(l, -1);
  lua_pop(l, 1);
  int crowd_len = lua_tointeger(l, -1);
  lua_pop(l, 1);
  double prox = lua_tonumber(l, -1);
  lua_pop(l, 1);
  rioter *prox_rioters[crowd_len];
  int prox_index = 0;
  int i;
  double current_x;
  double current_y;
  double x = r->x;
  double y = r->y;

  for(i=0; i<crowd_len; i++) {
    current_x = crowd[i].x;
    current_y = crowd[i].y;
    if(sqrt(((current_x-x)*(current_x-x) + ((current_y-y)*(current_y-y)))) < prox) {
      prox_rioters[prox_index] = &crowd[i];
      prox_index++;
    }
  }

  lua_pushlightuserdata(l, prox_rioters);//pointer to the first rioter in prox array
  lua_pushinteger(l, prox_index + 1);//the length of the array
  return 2;
}

int get_rioter_at_index(lua_State *l) {
  rioter *crowd = (rioter*) lua_topointer(l, -1);
  lua_pop(l, 1);
  int index = lua_tointeger(l, -1);
  lua_pop(l, 1);
  lua_pushlightuserdata(l, &crowd[index]);
  return 1;
}
