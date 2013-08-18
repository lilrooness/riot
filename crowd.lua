--this is the crowd controller--

function update_rioter(rioter)
 x,y,anger = getinfo(rioter);
 setinfo(x+1, y+1, anger+1, rioter);
end
