
Primarina

    Disarming Voice
        dealDamage(30)
        applyCondition(Confused,POKEINDEX = ACTIVE, ENEMY)
    
    Sparkling Aria
        dealDamage(100)
        heal(30)
----------------------------------------------------------
Brionne 

    Wave Splash
        dealDamage(30)
    
    Disarming Voice 
        dealDamage(50)
        applyCondition(Confused, POKDEINDEX = ACTIVE, ENEMY)
-----------------------------------------------------------
Popplio

    Pound 
        dealDamage(10) 
    
    Water Gun 
        dealDamage(20)
-----------------------------------------------------------
Golduck 

    Scratch
        dealDamage(20) 
    
    Double Jet
        dmg = 0
       # if you DISCARD up to 2 water energies from hand. This attack does 60 damage for each card you discarded in this way.
    
-----------------------------------------------------------
Psyduck
    
    Confusion wave
        # both monsters are confused
        applyCondition(Confused, POKEINDEX = ACTIVE, SELF)
        applyCondition(Confused, POKEINDEX = ACTIVE, ENEMY)
-----------------------------------------------------------
Cloyster

    Headlock 
        dmg = 30
        # heads
        if(flipCoin(1))
            dmg += 30
            dealDamage(dmg)
        else:
            # paralyze opponent 

    Guard Press
        dealDamage(80)
        # next turn this monster takes 20 LESS damage; function
-----------------------------------------------------------
Wingull

    Roost
        # heal 30 & NO RETREAT THIS TURN
        heal(30)
-----------------------------------------------------------
Corsola

    Call for Family
        # search 2 basic in deck, put them on the bench, shuffle deck

    Surf
        dealDamage(60)
-----------------------------------------------------------
Shellder

    Tackle
        dealDamage(20)
-----------------------------------------------------------
Lantern

    Confused Ray
        applyCondition(Confused, POKEINDEX = ACTIVE, ENEMY)

    Aqua Spark
        dmg = 60
        # if water energy is attached to pokemon
            dmg += 60
        dealDamage(dmg)
------------------------------------------------------------
Chinchou

    Searching Light
        # look at 1 of face down price cards

    Electro ball
        dealDamage(30)
-----------------------------------------------------------
Togedemaru

    Defense Curl
        if(flipCoin(1))
            # prevent all damage done next turn (heal the amount that pokemon attacks)
    Discharge
        # discard all electricity energies on this monster
        # for each electricity card you DISCARD 
            dmg += 30 
        dealDamage(dmg)
-----------------------------------------------------------
Hedier 

    # ABILITY: when you play this monster from your hand to evolve 1 of your
    # monster during your turn you may put an item card from you discard pile in your hand

    Bite
        dealDamage(50)
-----------------------------------------------------------
Lillipup

    Work up 
        # During next turn this monster attacks 20+ (before applying weakness and resistance)

    Bite
        dealDamage(20)
-----------------------------------------------------------
Spearow 

    Peck Bugs
        dmg = 10
        if(opponent == earth)
            dmg += 30 
        dealDamage(dmg)
-----------------------------------------------------------


# energy card we have 12x Water and 8x lightning Energy
# OTHER CARDS Trainer and Item cards
-----------------------------------------------------------
Energy Retrieval Item

    # Put 2 basic Energy cards form your discard pile into your hand
    
-----------------------------------------------------------
Hau Supporter

    # Draw 3 cards
-----------------------------------------------------------
Lillie Supporter

    # Draw cards until you have 6 cards in your hand.
    #  If it's your first turn, draw cards until you have 8 cards in your hand. 	
-----------------------------------------------------------
Nest Ball Item 

    # Search your deck for a Basic Pokémon and put it onto your Bench.
    #  Then, shuffle your deck.	
-----------------------------------------------------------
Potion Item

    # Heal 30 damage from 1 of your Pokemon
-----------------------------------------------------------
Professor Kukui Supporter 

    # Draw 2 cards. 
    # During this turn


    # your Pokémon's attacks do 20 more damage to your opponent's Active Pokémon (before applying Weakness and Resistance).	
-----------------------------------------------------------
Timer Ball Item 

    # Flip 2 coins. 
    # For each heads, search your deck for an Evolution Pokémon, reveal it, and put it into your hand. 
    # Then, shuffle your deck.	
-----------------------------------------------------------
Ultra Ball Item 

    # Discard 2 cards from your hand. If you do,
    # Search your deck for a Pokémon, reveal it, and put it into your hand. Shuffle your deck afterward.	
-----------------------------------------------------------