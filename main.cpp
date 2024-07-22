/*
Rules: 
Sets
Players=4;
Each player have 13 cards
Priority color= Hukum(Spade)
COLOR:     Club>Diamond>Heart>Spade
Spade/Hukum=13 cards((1-10)(J,B,K,Ace)); (41-53)
Heart/Pan=13 cards((1-10)(J,B,K,Ace)); (28-40)
Diamond/Ent=13 cards((1-10)(J,B,K,Ace)); (15-27)
Club/Chidi=13 cards((1-10)(J,B,K,Ace)); (2-14)


Number assign to face cards
J=11; B=12; K=13; Ace=14;


Steps evolved in game
a) Distribute 52 cards in 4 player
a.1) Distribute 13 cards into 4 player so each get different cards not same cards

b) Ask each player how many sets he want to make
b.1) if not able then subtract current set from total sets
b.2) if able then add current sets to total sets


start game now 
c) next player must be put higher card from max card that put below 
c.1) if donot have put lowest card

d) if player donot have that color then move priority color

e) if no priority color then move lower cards among given cards

runt loop to 13 players.



store value of 2 to 53 into vector 
make random shuffle into four players

a) assign S,H,D,C to ,J,B,K,A as different symbol so it make easier to sorting

*/


#include "part2.h"
#include "part1.h"
#include "memory.h"
#include "part3.h"


int main()
{
        static cardInfo* c=new cardInfo();
        static  playersInfo* p=new playersInfo[4];
        static Memory* m=new Memory();
        startGame(c,p,m);
       
    return 0;
}

