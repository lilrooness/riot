--this is the crowd controller--

function update_rioter(rioter)
 x, y, anger = getinfo(rioter);
 setinfo(x+1, y+1, anger+1, rioter);
end

function update_vecs(vx, vy)
 if vx == 0 and vy == 0 then return 1,1
 else return vx, vy
 end
end
