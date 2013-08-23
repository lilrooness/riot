--this is the crowd controller--

function update_rioter(rioter)
 x, y, vx, vy, anger = getinfo(rioter)
 vx, vy = process_vector(vx, vy)
 
 crowd, crowd_len = get_crowd()
 prox_rioters, prox_len = get_prox_rioters(10000, crowd_len, crowd, rioter)
 --setinfo(x+vx, y+vy, vx, vy, anger+1, rioter)
 flock_tick(rioter, prox_rioters, prox_len)
end

function flock_tick(rioter, prox_crowd, prox_len)
 avgx_pos = 0;
 avgy_pos = 0;

 avgx_h = 0;
 avgy_h = 0;
 rx, ry, rvx, rvy, ranger = getinfo(rioter);
 for i = 0,prox_len-1 do
  current_r = get_rioter_at_index(i, prox_crowd);
  avgx_pos = avgx_pos + x;
  avgy_pos = avgy_pos + y;
  avgx_h = avgx_h + vx;
  avgy_h = avgy_h + vy;
 end
 
 avgx_pos = avgx_pos / prox_len;
 avgy_pos = avgy_pos / prox_len;
 avgx_h = avgx_h / prox_len;
 avgy_h = avgy_h / prox_len;

 rvx = rx+avgx_h;
 rvy = ry+avgy_h;
 if rx > SCREEN_W or rx < 0 then
  avgx_h = -avgx_h;
 elseif ry > SCREEN_H or ry < 0 then
  avgy_h = -avgy_h;
 end
 setinfo(rx+avgx_h, ry+avgy_h, avgx_h, avgy_h, ranger, rioter);
end

function process_vector(vx, vy)
 if vx < 1 and vy < 1 then
  return 1,1
 else
  return vx, vy
 end
end

