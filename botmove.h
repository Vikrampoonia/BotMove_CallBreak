//move all function to botmove.h
int searchCardIndex(playersInfo* ,int ,int ,int );
int autoMove(int , int ,int [],playersInfo* ,int ,std::vector<int>& , Memory* );
int firstMove(playersInfo* , Memory* ,int ,std::vector<int>& );
int findPriorityHighestCard(playersInfo* , Memory* ,int );
int find_King_not_thrown_Ace(playersInfo* , Memory* ,int );
int find_maxColorCard(playersInfo* , Memory* ,int );
int find_kingAce(playersInfo* , Memory* ,int );
int find_lowestCard_exceptSpade(playersInfo* , Memory* ,std::vector<int>&  );
int find_lowestCardSpade(playersInfo* , Memory* ,int );
int MiddleMove(int ,int [],playersInfo* ,int ,std::vector<int>& , Memory* );
int check_validCards_greaterThan_pervious(int ,int [],int ,std::vector<int>& );
int lastMove(int ,int [],playersInfo* ,int ,std::vector<int>& , Memory* );
int searchCardIndex(playersInfo* ,int ,int ,int );
int check_other_player_use_priorityCard(int ,int ,int ,Memory* );
void helper_to_findDifferent_colorCard(std::vector<int>,int []);








int autoMove(int moves, int firstPlayer,int cardInstance[],playersInfo* p,int currentPlayer,std::vector<int>& validCard, Memory* m)
{

    if(moves==0)
    {
        return firstMove(p,m,currentPlayer,validCard);
    }
    else if(moves==1 || moves==2)
    {
        return MiddleMove( firstPlayer, cardInstance,p, currentPlayer,validCard, m);
    }
    else
    {
        return lastMove(firstPlayer,cardInstance,p,currentPlayer,validCard,m);
    }
}


//we have to check number of cards with you >=9 and want to put king then avoid it
int firstMove(playersInfo* p, Memory* m,int currentPlayer,std::vector<int>& validCard)
{
  
   
    //check spade highest card 
    int cardValue=findPriorityHighestCard(p,m,currentPlayer);
    int cardColor=(cardValue-2)/13;
    
    if(cardValue!=-1)
    {
        return searchCardIndex(p,cardColor,currentPlayer,cardValue)+1;
    }
    
    //check for king of that color whose ace is not have or not thrown and  then throw lower card from king
    cardValue=find_King_not_thrown_Ace(p,m,currentPlayer);
    cardColor=(cardValue-2)/13;
   
    if(cardValue!=-1)
    {
        return searchCardIndex(p,cardColor,currentPlayer,cardValue)+1;
    }

    //throw lowest of that color whose number of card with you is greater than or equal to 10 except spade
    cardValue=find_maxColorCard(p,m,currentPlayer);
    cardColor=(cardValue-2)/13;
    
    if(cardValue!=-1)
    {
        return searchCardIndex(p,cardColor,currentPlayer,cardValue)+1;
    }

    // throw ace and king
    cardValue=find_kingAce(p,m,currentPlayer);
    cardColor=(cardValue-2)/13;

    if(cardValue!=-1)
    {
        return searchCardIndex(p,cardColor,currentPlayer,cardValue)+1;
    }

    // throw any other color lowest cards except spade
    cardValue=find_lowestCard_exceptSpade(p,m,validCard);
    cardColor=(cardValue-2)/13;
    
    if(cardValue!=-1)
    {
        return searchCardIndex(p,cardColor,currentPlayer,cardValue)+1; 
    }

    // throw lowest spade card
    cardValue=find_lowestCardSpade(p,m,currentPlayer);
    cardColor=(cardValue-2)/13;
    
    if(cardValue!=-1)
    {
        return searchCardIndex(p,cardColor,currentPlayer,cardValue)+1;
    }

}

int findPriorityHighestCard(playersInfo* p, Memory* m,int currentPlayer)
{
    
    //finding highest priority card
    int initialIndex=(p+currentPlayer)->get_Initial_And_FinalIndex(3,0);

    if((p+currentPlayer)->getCard(initialIndex)==-1 || initialIndex==-1)
    {
        return -1;
    }
    int cardValue=(p+currentPlayer)->getCard(initialIndex);

    //check cardValue is highest or not mean above them are already thrown
    for(int i=(cardValue+1); i<54; i++)
    {
        if(!m->getMemoryCard(i,3))
        {
            return -1;
        }
    }
        
    return cardValue;
}

int find_King_not_thrown_Ace(playersInfo* p, Memory* m,int currentPlayer)
{
   
    //not check for spade
    int cardColor=2;
    while(cardColor>=0)
    {
        // check for having king and ace is not have or not not already thrown
        if((p+currentPlayer)->getKingAndAce(cardColor,0) && (!(p+currentPlayer)->getKingAndAce(cardColor,1) && !m->getMemoryCard(13*cardColor+14,cardColor)) )
        {
            //find lower than king of that color 
            int initialIndex=(p+currentPlayer)->get_Initial_And_FinalIndex(cardColor,0);
            int finalIndex=(p+currentPlayer)->get_Initial_And_FinalIndex(cardColor,1);
            if(initialIndex!=-1)
            {
                for(int i=initialIndex; i<=finalIndex; i++)
                {
                    //just lower card from king            
                    if((p+currentPlayer)->getCard(i)<(13*cardColor+13) && (p+currentPlayer)->getCard(i)!=-1)
                    {
                        return (p+currentPlayer)->getCard(i);
                    }
                }
            }
        }
        else if((p+currentPlayer)->getKingAndAce(cardColor,0) && (p+currentPlayer)->getKingAndAce(cardColor,1))
        {
            (p+currentPlayer)->setKingAndAce(cardColor,1);
            return 13*cardColor+14;
        }
      
        cardColor=cardColor-1;
    }
    return -1;
    
}

int find_maxColorCard(playersInfo* p, Memory* m,int currentPlayer)
{
    //no fo card you have and throw of that color card is greater or equal to 10 not for spade
  
    int colorCard=2;
    while(colorCard>=0)
    {
        int intialIndex=(p+currentPlayer)->get_Initial_And_FinalIndex(colorCard,0);
        int finalIndex=(p+currentPlayer)->get_Initial_And_FinalIndex(colorCard,1);

        int count=0; int cardValue=55;
        if(intialIndex!=-1)
        {
            for(int i=intialIndex; i<=finalIndex; i++)
            {
                if((p+currentPlayer)->getCard(i)!=-1)
                {
                    count++;
                }
                
                if((p+currentPlayer)->getCard(i)!=-1 && (p+currentPlayer)->getCard(i)<cardValue)
                {
                    cardValue=(p+currentPlayer)->getCard(i);
                }
            }
            
            if(count+m->getnoThrowCardColor(colorCard)>=10)
            {
                return cardValue;
            }
        }
        colorCard=colorCard-1;
    }
    return -1;
}

int find_kingAce(playersInfo* p, Memory* m,int currentPlayer)
{
    int cardColor=2;
    while(cardColor>=0)
    {
        //having king and ace already throw
        if((p+currentPlayer)->getKingAndAce(cardColor,0) && m->getMemoryCard(13*cardColor+14,cardColor)) 
        {
            return 13*cardColor+13;
        }
        //have ace
        else if((p+currentPlayer)->getKingAndAce(cardColor,1))
        {
            return 13*cardColor+14;
        }
        cardColor=cardColor-1;
    }
    return -1;
}

int find_lowestCard_exceptSpade(playersInfo* p, Memory* m,std::vector<int>& validCard)
{
    int minCard=54;
    int minCardValue=-1;
    int size=validCard.size();
    //now finding minimum card
    for(int i=0; i<size; i++)
    {
        int cardColor=(validCard[i]-2)/13;
        int value=validCard[i]-13*(cardColor); //C9=H9 to make distuinguish we use this
        if(value<minCard && cardColor!=3)
        {
            minCard=value;
            minCardValue=validCard[i]; //minimum card
        }
    }
    return minCardValue;
}

int find_lowestCardSpade(playersInfo* p, Memory* m,int currentPlayer)
{
    int minCard=54;
    //now finding minimum card

    int initialIndex=(p+currentPlayer)->get_Initial_And_FinalIndex(3,0);
    int finalIndex=(p+currentPlayer)->get_Initial_And_FinalIndex(3,1);

    if(initialIndex!=-1)
    {
        for(int i=initialIndex; i<=finalIndex; i++)
        {
            int value=(p+currentPlayer)->getCard(i); 
            if(value<minCard && value!=-1)
            {
                minCard=value;    
            }
        }
        return minCard;
    }
    else
    {
        return -1;
    }
}



int MiddleMove(int firstPlayer,int cardInstance[],playersInfo* p,int currentPlayer,std::vector<int>& validCard, Memory* m)
{
   
    int cardValue; int flag=1;
    int cardColor=(cardInstance[0]-2)/13; 
    sort(validCard.begin(),validCard.end());
    int size=validCard.size();

    //made one case of valids cards consist of smaller than first player card also for last move return 0 or 1
    flag=check_validCards_greaterThan_pervious(firstPlayer,cardInstance,currentPlayer,validCard);
    
    if(!flag)
    { 
        //throw smallest card
        if((validCard[0]-2)/13==cardColor)
        {
            cardValue=validCard[0];
            cardColor=(cardValue-2)/13;
        }
       //valid card does not have first player card and priority card
       else
       {
            cardValue=find_lowestCard_exceptSpade(p,m,validCard);
            if(cardValue==-1)
            {
                cardValue=find_lowestCardSpade(p,m,currentPlayer);
            }
            cardColor=(cardValue-2)/13;
       }

    }
    else
    {
        
        //first case:consisit of first player card color
        if((validCard[0]-2)/13==cardColor)
        {
            //check now that color ace is here or not
           
            if((p+currentPlayer)->getKingAndAce(cardColor,1))
            {
                //first player card 
                cardValue=13*(cardColor)+14;
            }
            else if((p+currentPlayer)->getKingAndAce(cardColor,0))
            {
                
                //check from memory ace is out or not
                if(m->getMemoryCard(13*cardColor+14,cardColor)) 
                {
                    //ace is already throw of that color
                    cardValue=13*(cardColor)+13;
                }
                else
                {
                    //ace is not thrown of that color 
                    // search lower card from king in valid vector cards
                    sort(validCard.begin(), validCard.end());
                    int size=validCard.size();
                    (size==1)?cardValue=validCard[0]:cardValue=validCard[size-2];

                } 

            }
            else if(m->getMemoryCard(13*cardColor+14,cardColor) && m->getMemoryCard(13*cardColor+13,cardColor))
            {
                cardValue=validCard[size-1];
            }
            else
            {
                cardValue=validCard[0];
            }
           
        }
         //second case: consisit of priority card
        else if((validCard[0]-2)/13==3)
        {
             
            //second case:
           
                //valid cards consist of priority cards
                //think it using memory card 
                //way of thinking is
                /*
                    first way is: throw largest card without thinking
                    second way is: 
                    first card color=color of card thrown by first player

                    no of card till now throw of first card color
                    if it is less than 8 and no other player(next to them) till now use priority cards on that color
                    then use smallest priority card
                    else throw largest card

                */
            
                cardValue=-1;
                /*if(m->getnoThrowCardColor(cardColor)<=8 && !check_other_player_use_priorityCard(currentPlayer,firstPlayer,cardColor,m))
                {
                    //std::cout<<"valid card consisit of priority card color No other player use priority card on this color \n";
                    //we have to use smaller priority card
                    cardValue=validCard[0];
                }
                else
                {
                    //we have to use highest priority card
                    //std::cout<<"valid card consisit of priority card color other player use priority card on this color \n";
                    //(size==1)?cardValue=validCard[0]:cardValue=validCard[size-1];
                    cardValue=validCard[size-1];
                }*/
                cardValue=validCard[size-1];
                
                cardColor=(cardValue-2)/13;

        }

        // third case: not have neither priority card nor same color card as first player  
        else
        {
            
            //find no of different color cards from validCard vector
            int differentColorCard[3]={0,0,0};
            //function to help to find Diffrernt Color Card and different king
            helper_to_findDifferent_colorCard(validCard,differentColorCard);
            //replace by this below function
            
            cardValue=find_lowestCard_exceptSpade(p,m,validCard);
            cardColor=(cardValue-2)/13;

        }
    }
    
    //return its index from search
    return searchCardIndex(p,cardColor,currentPlayer,cardValue)+1;   
}

//this function check that valid cards value are greater than pervious players or not

int check_validCards_greaterThan_pervious(int firstPlayer,int cardInstance[],int currentPlayer,std::vector<int>& validCard)
{
    int firstColor=(cardInstance[0]-2)/13;
    int maxCard=cardInstance[0];
    for(int i=1; cardInstance[i]!=-1; i++)
    {
        if(maxCard<cardInstance[i] && ((cardInstance[i]-2)/13 == firstColor || (cardInstance[i]-2)/13==3))
        {
            maxCard=cardInstance[i];
        }
    }
    for (int i = 0; i < validCard.size(); i++)
    {
        int cardColor=(validCard[i]-2)/13;
       if(validCard[i]>maxCard && (cardColor==firstColor || cardColor==3))
       {
            return 1;
       }
    }
    return 0;
}   

int lastMove(int firstPlayer,int cardInstance[],playersInfo* p,int currentPlayer,std::vector<int>& validCard, Memory* m)
{
    int cardColor=(cardInstance[0]-2)/13; 
    
    int cardValue=validCard[0];
    sort(validCard.begin(), validCard.end());
    int size=validCard.size();
    int flag=0;
    
    //made one case of valids cards consist of smaller than first player card also for last move return 0 or 1
    flag=check_validCards_greaterThan_pervious(firstPlayer,cardInstance,currentPlayer,validCard);
    
    if(!flag)
    {
       
        if((validCard[0]-2)/13==cardColor)
        {
            cardValue=validCard[0];
            cardColor=(cardValue-2)/13;
        }
       //valid card does not have first player card and priority card
       else
       {
            cardValue=find_lowestCard_exceptSpade(p,m,validCard);
            if(cardValue==-1)
            {
                cardValue=find_lowestCardSpade(p,m,currentPlayer);
            }
            cardColor=(cardValue-2)/13;
       }
    }
    else
    {
        if((validCard[0]-2)/13 == cardColor || (validCard[0]-2)/13 == 3)
        {
            // valid cards are of that same color as first player thrown
            // then we have to throw first smaller card from valid cards
            
            cardValue=validCard[0];
            cardColor=(cardValue-2)/13;

        }
        // third case: not have neither priority card nor same color card as first player 
        else
        { 
            //find minimum cards among colors
            
            //find no of different color cards from validCard vector
            int differentColorCard[3]={0,0,0};

            //function to help to find Diffrernt Color Card and different king
            helper_to_findDifferent_colorCard(validCard,differentColorCard);

            //replace this by a function
            cardValue=find_lowestCard_exceptSpade(p,m,validCard);
            cardColor=(cardValue-2)/13;
        }
    }

        //return its index from search
        return searchCardIndex(p,cardColor,currentPlayer,cardValue)+1;
}   


//returning index of cardValue from players card array
int searchCardIndex(playersInfo* p,int cardColor,int currentPlayer,int cardValue)
{
    int initialIndex=(p+currentPlayer)->get_Initial_And_FinalIndex(cardColor,  0);
    int finalIndex=(p+currentPlayer)->get_Initial_And_FinalIndex(cardColor,  1);
    if(initialIndex!=-1)
    {
        for(int i=initialIndex; i<=finalIndex; i++)
        {
            if(cardValue==(p+currentPlayer)->getCard(i))
            {
                return i;
            }
        }
    }
    return -2;

}



//helping to determine which player use priorty card in which color

int check_other_player_use_priorityCard(int currentPlayer,int firstPlayer,int cardColor,Memory* m)
{
    
    int nextPlayer=(currentPlayer+1)%4;
    while(nextPlayer!=firstPlayer)
    {
        if(m->getPlayerUsePriorityColor(nextPlayer,cardColor))
        {
            return 1;
        }
        nextPlayer+=(nextPlayer+1)%4;
    }
    return 0;
}


void helper_to_findDifferent_colorCard(std::vector<int>validCard,int differentColorCard[])
{
    // finding number of different color card
    for(int i=0; i<validCard.size(); i++)
    {
        int cardColor=(validCard[i]-2)/13;
        differentColorCard[cardColor]++;
    }

}




