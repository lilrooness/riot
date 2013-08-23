#include <allegro.h>
#include "rioter.h"

void draw_rioters(rioter *rioters, int n, BITMAP *buffer);
void init_rioters(int n, rioter *crowd);
void update_rioters(rioter *crowd, int n, lua_State *L);
lua_State* init_lua();

BITMAP *buffer;
rioter *crowd;
int crowdsize;
int clearcolor;


int main(int argc, char *argv[]) {
  if(allegro_init() != 0) {
    return 1;
  }
  printf("%s\n", allegro_id);
  install_keyboard();
  install_timer();
  lua_State *L = init_lua();
  clearcolor = makecol(0,0,0);
  if(set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0)!=0) {
    if(set_gfx_mode(GFX_SAFE, 640, 480, 0, 0)!=0) {
      set_gfx_mode(GFX_TEXT, 0,0,0,0);
      allegro_message("Unable to set ant graphics mode\n%s\n", allegro_error);
      return 1;
    }
  }
  buffer = create_bitmap(SCREEN_W, SCREEN_H);
  init_rioters(5, crowd);

  while(1) {
    update_rioters(crowd, crowdsize, L);
    clear_to_color(buffer, makecol(0,0,0));
    draw_rioters(crowd, crowdsize, buffer);
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    rest(1);
  }
destroy_bitmap(buffer);
return 0;
}

END_OF_MAIN()

void draw_rioters(rioter *rioters, int n, BITMAP *buffer) {
  int i;
  for(i=0; i<n; i++) {
    ellipsefill(buffer, rioters[i].x, rioters[i].y, 10, 10, makecol(0, 255, 0));
  }
}

void init_rioters(int n, rioter *croud) {
  srand(time(NULL));
  crowdsize = n;
  crowd = new_rioters(n);
  int i=0;
  for(i=0; i<n; i++) {
    crowd[i].x = rand() % SCREEN_W;
    crowd[i].y = rand() % SCREEN_H;
    crowd[i].vx = rand() % 5;
    crowd[i].vy = rand() % 5;
  }
}

void update_rioters(rioter *crowd, int n, lua_State *L) {
  int i;
  for(i=0; i<n; i++) {
    update_rioter(&crowd[i], L);
  }
}

int get_crowd(lua_State *L) {
  lua_pushlightuserdata(L, crowd);
  lua_pushinteger(L, crowdsize);
  return 2;
}

lua_State* init_lua() {
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);
  luaL_dofile(L, "crowd.lua");
  lua_register(L, "getinfo", getinfo);
  lua_register(L, "setinfo", setinfo);
  lua_register(L, "get_prox_rioters", get_prox_rioters);
  lua_register(L, "get_crowd", get_crowd);
  lua_register(L, "get_rioter_at_index", get_rioter_at_index);
  lua_pushinteger(L, SCREEN_W);
  lua_setglobal(L, "SCREEN_W");
  lua_pushinteger(L, SCREEN_H);
  lua_setglobal(L, "SCREEN_H");
  lua_register(L, "get_crowd", get_crowd);
  lua_register(L, "get_prox_rioters", get_prox_rioters);
  return L;
}

