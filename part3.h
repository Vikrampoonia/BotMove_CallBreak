#include<vector>
#include "botmove.h"
#include "result.h"

void startGame(cardInfo* ,playersInfo* ,Memory* );

void firstPhase(cardInfo* , playersInfo* ,int  );
void showIndexes();

void secondPhase(cardInfo* , playersInfo* ,int  ,Memory* );
int setMadeBy(int ,int [], Memory* );
void showValidCard(int [], int , int , playersInfo* ,std::vector<int>& );
int countColorCard(int,  playersInfo* ,int );
void helper_of_showValidCard(int ,int ,int , int ,playersInfo* ,std::vector<int>& );
void helper_of_showValidCard(int ,playersInfo* ,std::vector<int>& );
void thirdPhase(int , playersInfo* );





void startGame(cardInfo* c, playersInfo* p, Memory* m)
{
    /*
    1: call Shuffle Card function
    2: call set Crad function(auto call of distribution card, mapping card function) and asking no of set by each player
    3:  step 1 and 2 for start of any game
    4: Now game is start 
    4.2: Run loop for 13 moves
    4.2.1: Each loop conatin 4 sub moves
    4.2.2: First card thrown by prioiryt player(change every next game)
    4.2.2.1: next card by next player(next to him) continue. When subloop is over then check whom set is belong so first card thrown by that player
    */
   /*
   
    firstphase function contain step 1 and step 2
    second phase function contain step 4
    third phase function conatin updation of set of each player and ending of 5 rounds declare winner of game and other players position
    
   */

    int roundNo=0;
    while(roundNo<10)
    {
        
        m->initialisePlayerUsePriorityColor();
        for(int i=0; i<4; i++)
        {
            (p+i)->initialiseMembers();
        }
        firstPhase(c,p,roundNo);
       
        secondPhase(c,p,(roundNo)%4, m);
        thirdPhase( roundNo, p);
        roundNo++;
    }

    //announcing result of each round 
    announceResult(p,roundNo);
}

void firstPhase(cardInfo* c, playersInfo* p,int roundNo)
{
    
    c->shuffleCard(); int set=0;
    showIndexes(); //show indexes
    
    for(int i=0; i<4; i++)
    {   
        (p+i)->setCard(i,c); //show cards with face value
        set=(p+i)->suggestionSet();
        std::cout<<"Suggetion: "<<set<<std::endl;
        //std::cout<<"Enter your Set: ";
        //std::cin>>set;
        (p+i)->setScoreCard(set);
    }
}


void showIndexes() //show index of each card associate with card Face value
{
    for(int i=0; i<13; i++)
    {
        if(i<9)
        {
            std::cout<<"0"<<(i+1)<<" ";
        }
        else
        std::cout<<(i+1)<<" ";
    }std::cout<<std::endl;
}


void secondPhase(cardInfo* c, playersInfo* p,int firstPlayer ,Memory* m)
{
    
    /*
        run a loop for 13 moves and each moves run for 4 sub moves
    */
   int moves=0; int indexInput=0;//index that taken as input from player
   int subMoves=0;   int nextPlayer=firstPlayer; 
   int cardInstance[4]={-1,-1,-1,-1};
   std::vector<int>validCard;
   validCard.clear();
   while(moves<13)
   {
        while(subMoves<4)
        {

            std::cout<<"\nPlayer Number: "<<nextPlayer<<std::endl;
            showIndexes();
            (p+nextPlayer)->showMapCard(0, 13);
            
            
            if(subMoves!=0)
            {
                showValidCard(cardInstance, nextPlayer, cardInstance[0],p,validCard);
            } 
            else
            {
                
                for(int i=0; i<13; i++)
                {
                    if((p+nextPlayer)->getCard(i)!=-1)
                    {
                        validCard.push_back((p+nextPlayer)->getCard(i));
                    }
                }
                firstPlayer=nextPlayer;
            }

            int indexInput1=autoMove( subMoves, firstPlayer, cardInstance, p,nextPlayer,validCard,m);
            std::cout<<"Suggested  Index by bot: "<<indexInput1<<"  "<<mapping_color((p+nextPlayer)->getCard(indexInput1-1))<<mapping_number((p+nextPlayer)->getCard(indexInput1-1))<<std::endl;
            indexInput=indexInput1;
            //std::cin>>indexInput;

            while((p+nextPlayer)->getCard(indexInput-1)==-1 || (indexInput>13 || indexInput<1) )
            {   
                std::cout<<"\n Wrong Input "<<std::endl;
                std::cout<<"Enter index: ";
                std::cin>>indexInput;
            }   
                   
            cardInstance[subMoves]=(p+nextPlayer)->getCard(indexInput-1);  

            if (cardInstance[subMoves]%13==0 || cardInstance[subMoves]%13==1)
            {
                (p+nextPlayer)->setKingAndAce((cardInstance[subMoves]-2)/13,cardInstance[subMoves]%13); 
            }
            
            (p+nextPlayer)->setCard(indexInput-1);
            (p+nextPlayer)->set_Initial_And_FinalIndex((cardInstance[subMoves]-2)/13);
            nextPlayer=(nextPlayer)%4+1;
            if(nextPlayer==4)
            {
                nextPlayer=0;
            }
            subMoves++;
            //clear vector
            validCard.clear();
        }
        subMoves=0;
        firstPlayer=setMadeBy(firstPlayer,cardInstance,m);
        std::cout<<"Set made by: "<<firstPlayer<<std::endl;
        (p+firstPlayer)->updateProgressingSet();
        nextPlayer=firstPlayer;
        moves++;
        //initialise cardinstance array
        for(int i=0; i<4; i++)
        {
            //add to memory
            m->addMemoryCard(cardInstance[i],(cardInstance[i]-2)/13);

            cardInstance[i]=-1;
        }
   }


}

//identify whom set is
int setMadeBy(int firstPlayer,int cardInstance[], Memory* m)
{
    int cardColor=(cardInstance[firstPlayer]-2)/13;
    
    int seter=firstPlayer;
    int max_card=-1;

    for(int i=0; i<4; i++)
    {   
        int setPlayer=(firstPlayer+i)%4;
        int card_type=(cardInstance[i]-2)/13;
        
        if(card_type== cardColor || card_type==3)
        {
            if(max_card<cardInstance[i])
            {
                seter=setPlayer;
                max_card=cardInstance[i];  
            }
        }
        //use to tell that this player use priority card on that color
        if(card_type== 3 && cardColor!=3)
        {
            m->setPlayerUsePriorityColor(setPlayer,cardColor);
        }
    }
    return seter;
}




void showValidCard(int cardInstance[], int currentPlayer, int firstPlayerCardValue, playersInfo* p,std::vector<int>& validCard)
{ 
        //finding greatest card
        int firstPlayerCardColor=(firstPlayerCardValue-2)/13;
        int maxCard=firstPlayerCardValue;
        
        for(int i=0; cardInstance[i]!=-1; i++)
        {  
            if( ( (cardInstance[i]-2)/13 == firstPlayerCardColor  ||  (cardInstance[i]-2)/13 == 3 ) &&  maxCard<cardInstance[i])
            {
                maxCard=cardInstance[i];
            }
        }

        
        //player have same color card as first player card color
        int noOfCard=countColorCard(currentPlayer,p,firstPlayerCardColor);
        
        //yes player have cards as first player card color 
        if(noOfCard>0)
        {
            int initialIndex=(p+currentPlayer)->get_Initial_And_FinalIndex(firstPlayerCardColor,0);
            int finalIndex=(p+currentPlayer)->get_Initial_And_FinalIndex(firstPlayerCardColor,1);
            helper_of_showValidCard(initialIndex,finalIndex,maxCard, currentPlayer,p,validCard);
        }
        //no player do not have first player card color check for priority color card
        else if(countColorCard(currentPlayer,p,3)>0)
        {    
            int initialIndex=(p+currentPlayer)->get_Initial_And_FinalIndex(3,0);
            int finalIndex=(p+currentPlayer)->get_Initial_And_FinalIndex(3,1);
            int flag=0;
            for(int i=initialIndex; i<=finalIndex; i++)
            {
                if((p+currentPlayer)->getCard(i)!=-1)
                {
                    if((p+currentPlayer)->getCard(i) > maxCard)
                    {
                        validCard.insert(validCard.begin(), (p+currentPlayer)->getCard(i)); 
                        flag=1;
                    }
                    else if(flag==0)
                    {
                        //store other color card except spade because first player card does not have and in spade do not have greater card
                        helper_of_showValidCard( currentPlayer,p,validCard);
                        break;
                    }
                }
            }
        }
        //player do not have first plyaer color card as well as priority color  card so store other color card 
        else
        {    
            helper_of_showValidCard( currentPlayer,p,validCard);
        }

}

//help to find no of cards in a color
int countColorCard(int currentPlayer,  playersInfo* p,int cardColor)
{
    int initialIndex=(p+currentPlayer)->get_Initial_And_FinalIndex(cardColor,0);
    int finalIndex=(p+currentPlayer)->get_Initial_And_FinalIndex(cardColor,1);
    int count=0;
    
    if(initialIndex!=-1)
    {
        for(int i=initialIndex; i<=finalIndex; i++)
        {
            if((p+currentPlayer)->getCard(i)!=-1)
            {
                count++;
            }
        }
    }

    return count;
}

//help to store valid card
void helper_of_showValidCard(int initialIndex,int finalIndex,int maxCard, int currentPlayer,playersInfo* p,std::vector<int>& validCard)
{
    //if maxcard color is same as firstplayercard
    int flag=0;
            
    for(int i=initialIndex; i<=finalIndex; i++)
    {  
        if((p+currentPlayer)->getCard(i) > maxCard && (p+currentPlayer)->getCard(i)!=-1)
        {
            validCard.insert(validCard.begin(), (p+currentPlayer)->getCard(i)); 
            flag=1;
        }
        else if(flag==0  && (p+currentPlayer)->getCard(i)!=-1)
        {
            validCard.insert(validCard.begin(), (p+currentPlayer)->getCard(i));         
        }
    }
}

//store other color card except priority color card
void helper_of_showValidCard( int currentPlayer,playersInfo* p,std::vector<int>& validCard)
{
    for(int i=0; i<13; i++)
    {
        if((p+currentPlayer)->getCard(i)!=-1)
        {
            validCard.insert(validCard.begin(), (p+currentPlayer)->getCard(i));        
        }
    }
}

void thirdPhase(int roundNo, playersInfo* p)  // result part 
{
    for(int i=0; i<4; i++)
    {
        (p+i)->update_Details_Round(roundNo);
    }

}



