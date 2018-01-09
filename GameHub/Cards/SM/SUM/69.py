import poke as p

def smackDown(h):
    if viewBench(p.PLAYER.ENEMY)[0].active().resistance()==p.TYPE.FIGHTING :
	h.dealdamage(70)
    else:
    	h.dealDamage(20)
	
		
