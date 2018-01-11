import poke as p

def smackDown(h):
    if h.viewBench(p.PLAYER.ENEMY)[0].active().resistance()==p.TYPE.FIGHTING :
	    h.dealDamage(70)
    else:
    	h.dealDamage(20)
	
		
