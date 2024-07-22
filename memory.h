/*

no of cards of each color for each player thrown
if it is 13 then make it vector clear  

4 vector for each color 

vector<int>v(4);
v.assign(size,value)
v.assign(4,0);
vector<vector<int>> vec(4); 


0=club
1=diamond
2=heart
3=spade

*/

#include<vector>
int helper_of_getMemoryCard(int , std::vector<int>& );



class Memory
{
    std::vector<int>club;
    std::vector<int>diamond;
    std::vector<int>heart;
    std::vector<int>spade;

    int noThrowCards[4];
    int PlayerUsePriorityColor[4][3]; //not include spade   0=club, 1=diamond, 2=heart

    public:
    Memory(){

    }

    //assigning vector
    void  assignVector();

    //add card into memory
    void addMemoryCard(int cardValue, int cardColor);

    //tell card is present in memory or not
    int getMemoryCard(int cardValue, int cardColor);

    //no of cards for that color throw till now
    int getnoThrowCardColor(int cardColor);

    //tell which player use priority card on which color
    int getPlayerUsePriorityColor(int player, int cardColor);

    // set that player use priority card on that cardcolor
    void setPlayerUsePriorityColor(int player, int cardColor);

    //initialise arrays
    void initialisePlayerUsePriorityColor();
};

void  Memory::assignVector()
{
    club.assign(13,-1);
    diamond.assign(13,-1);
    heart.assign(13,-1);
    spade.assign(13,-1);
}

void Memory::addMemoryCard(int cardValue, int cardColor)
{
    //add card
    if(cardColor==0)
    {
        club.push_back(cardValue);
    }
    else if(cardColor==1)
    {
        diamond.push_back(cardValue);
    }
    else if(cardColor==2)
    {
        heart.push_back(cardValue);
    }
    else
    {
        spade.push_back(cardValue);
    }
    //increase no of throw cards value;
    
    noThrowCards[cardColor]++;   
    
}

int Memory::getnoThrowCardColor(int cardColor)
{
    return noThrowCards[cardColor];
}

int Memory::getMemoryCard(int cardValue, int cardColor)
{
   
    if(cardColor==0)
    {
        return helper_of_getMemoryCard(cardValue,club);
    }
    else if(cardColor==1)
    {
        return helper_of_getMemoryCard(cardValue,diamond);
    }
    else if(cardColor==2)
    {
        return helper_of_getMemoryCard(cardValue,heart);
    }
    else
    {
        return helper_of_getMemoryCard(cardValue,spade);
    }
    

}


int helper_of_getMemoryCard(int cardValue, std::vector<int>& vec)
{
    
    sort(vec.begin(),vec.end());

    for(int i=0; i<vec.size(); i++)
    {
        if(vec[i]==cardValue)
        {
            return 1;
        }
    }
    return 0;
}

int Memory::getPlayerUsePriorityColor(int player, int cardColor)
{
    return PlayerUsePriorityColor[player][cardColor];    //return 0 or 1
}

void Memory::setPlayerUsePriorityColor(int player, int cardColor)
{
    PlayerUsePriorityColor[player][cardColor]=1;
}

void Memory::initialisePlayerUsePriorityColor()
{
  
    assignVector();
 
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<3; j++)
        {
            PlayerUsePriorityColor[i][j]=0;
        }
    }
    for(int i=0; i<4; i++)
    {
        noThrowCards[i]=0;
    }
}


