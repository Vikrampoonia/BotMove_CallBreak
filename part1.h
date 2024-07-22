


/*
contain class in which 
array conting players card
total score mady by them

0=club
1=diamond
2=heart
3=spade

*/

void initialiseArrays(int* , int , int );  //function initialsing arrays
void initialiseArrays(int* , int ,int , int ); //function initialise color card array
float findActualSet(int ,int ); //find actual set mean AND NoSet= Number of set made by player in that round
int helper_Of_set_Initial_And_FinalIndex(int , int* , int* , int ); //used to reduce number of codes lines of set_Initial and FinalIndex function
int helper_Of_suggestionSet(int* , int* , int* ,int* , int );


class playersInfo
{
    int playerCard[13]; //cards array
    char mapPlayerCard[13][2]; //map each card with its color and values Here 10 Symbol is T, {(index)(color,value)}
   
    int progressingSet; //track number of set in current round made by player
    std::vector<float>scoreCard; //containg score of each round
    
    //arrays used to tell valid card so it help to reduce time complixity take reference from playerCard 
    //containing inital and final index of each color 
    int colorCard[4][2];

    //containing info of king and ace containing or not of each color 1=containing  0=Not containing
    int kingAndAce[4][2]; 

    public:
    playersInfo(){}
    //show mapCard
    void showMapCard(int start, int end);

    //initialise member of class
    void initialiseMembers();

    // used to allocate cards into playerCard array and map it with card Color starting of each round
    void setCard(int playerNumber,cardInfo* c); 

    //used to set value -1 to tell that card is thrown
    void setCard(int index);

    // return value associated with that card and take input from user
    int getCard(int cardIndex);

    //set value of each card start and final index in those array value allocate in starting of each round and use in show valid card
    void set_Initial_And_FinalIndex();

    //Update value of each card start and final index in those array value allocate after starting of each round means when initil or final index card thrown then update its value
    void set_Initial_And_FinalIndex(int color);

    // get initial and final index
    int get_Initial_And_FinalIndex(int color, int index);

    //update progressing Set
    void updateProgressingSet();

    //set current number of set of each round
    void setScoreCard(int No_Set);

    

    //update after roundComplete (totalscore,scorecard)
    void update_Details_Round(int roundNo);

    //to get scorecard value
    float getScoreCard(int roundNo);

    //give suggestion that how many set you can made
    int suggestionSet();

   // void showInitialIndex();


    // return whether king or ace is present or not index for king or ace
    int getKingAndAce(int color,int index);

    // set value of king and ace 
    void setKingAndAce(int color,int index);

};

void playersInfo::showMapCard(int start, int end)
{
    for(int i=start; i<end; i++)
    {
        for(int j=0; j<2; j++)
        {
            std::cout<<mapPlayerCard[i][j];
        }   std::cout<<" ";
    }   std::cout<<std::endl;
}


void playersInfo::initialiseMembers()
{
    //intialise variables and arrays=0; and each color array such as spadeCard,heartCard to be -1;
    progressingSet=0;

    //function initialsing arrays parameter as array,its length, value intialise (0/-1);
    initialiseArrays(&playerCard[0],13,0);
    initialiseArrays(&colorCard[0][0],4,2,-1);
    initialiseArrays(&kingAndAce[0][0],4,2,0);
}


void initialiseArrays(int* arr, int len, int value)  //function initialsing arrays
{
    for(int i=0; i<len; i++)
    {
        *(arr+i)=value;
    }
}


void initialiseArrays(int* arr, int len1,int len2, int value)  //color Card initialsing arrays
{
    for(int j=0; j<len1; j++)
    {
        for(int i=0; i<len2; i++)
        {
            *(arr+(j*len2)+i)=value;
        }
    }
}

//call at starting of game
void playersInfo::setCard(int playerNumber,cardInfo* c)
{
    initialiseMembers();

    c->distributeCards(&playerCard[0], playerNumber); // function that fill cardvalues and this find in CardInfo class
    c->mapCard(&mapPlayerCard[0][0],&playerCard[0]); // function that map cardvalues with card Color and this find in CardInfo class
}


void playersInfo::setCard(int index)
{
    playerCard[index]=-1;
    mapPlayerCard[index][0]='X';
    mapPlayerCard[index][1]='X';
}


int playersInfo::getCard(int cardIndex)
{
    return playerCard[cardIndex];
}


void playersInfo::set_Initial_And_FinalIndex()
{
    
    //this function return last index +1 of color for which we find
    int start=helper_Of_set_Initial_And_FinalIndex(0,&playerCard[0],&colorCard[0][0], 3); //for spade
    start=helper_Of_set_Initial_And_FinalIndex(start,&playerCard[0],&colorCard[0][0], 2); //for heart
    start=helper_Of_set_Initial_And_FinalIndex(start,&playerCard[0],&colorCard[0][0], 1); //for diamond
    start=helper_Of_set_Initial_And_FinalIndex(start,&playerCard[0],&colorCard[0][0], 0); //for club

    //this function show only initial and final index of eaxh color
    //showInitialIndex();
}

int helper_Of_set_Initial_And_FinalIndex(int start, int* playerCard, int* colorCard, int color)
{

    for(int i=start; i<13; i++)
    {  
        
        if(*(playerCard+i) >=(2+13*color) && *(playerCard+i) <=(2+13*color+12) )
        {
            if(*((colorCard+2*color)+0) == -1)
            {   
                *((colorCard+2*color)+0) = i;
                *((colorCard+2*color)+1) = i;
            }
            else
            {
                if(*((colorCard+2*color)+1) <i)
                {
                    *((colorCard+2*color)+1) =i;
                }
            }
              
        }
        else
        {
            return i;
        }
    }
}


//index tell which card want to set, color which array, state means inital or final
void playersInfo::set_Initial_And_FinalIndex(int color)
{
  
    int min=colorCard[color][0],max=colorCard[color][1]; int flag=0;
    

    for(int i=colorCard[color][0]; i<=colorCard[color][1]; i++)
    {
        if(playerCard[i]!=-1)
        {
            if(min<=i && flag==0)
            {
                min=i;
                max=i;
                flag=1;
            }
            else if(max<i)
            {
                max=i;
            }
        }
    }
    if(min==colorCard[color][0] && (max==colorCard[color][1] && playerCard[min]==-1) )
    {
        max=-1;
        min=max;
    }
    colorCard[color][0]=min;
    colorCard[color][1]=max;
    
}

// get initial and final index
int playersInfo::get_Initial_And_FinalIndex(int color, int index)
{
    return colorCard[color][index];
}



void playersInfo::updateProgressingSet()
{
    progressingSet++;
}

//store no of set in each round here roundNo is not used
void playersInfo::setScoreCard(int No_Set)
{
    scoreCard.push_back(No_Set);
}



//to get scorecard value
float playersInfo::getScoreCard(int roundNo)
{
    return scoreCard[roundNo];
}



void playersInfo::update_Details_Round(int roundNo)
{
    float ActualSet=findActualSet(scoreCard[roundNo],progressingSet); 
    scoreCard.push_back(ActualSet);
}


float findActualSet(int currentSet,int NoSet) 
{
    
    float diff;
    if(NoSet>=currentSet) 
    {
        diff=NoSet-currentSet;   
        (diff>9)?diff/=100:diff/=10; 
        diff=(float)(currentSet)+diff;
    }
    else
    {
        diff=-currentSet;
    }
    return diff;
}


int playersInfo::suggestionSet()
{

    set_Initial_And_FinalIndex();

    int priorityCardSet=0; //Set we make with the help of priority Card
    int faceCardSet=0;

    int No_Of_Spade_Card=0;
    
    //for club card   
    if(colorCard[0][1]-colorCard[0][0] + 1 <=2)
    {
        
        priorityCardSet+=(3-(colorCard[0][1]-colorCard[0][0] + 1));
    }
    
    //for Diamond card    
    if(colorCard[1][1]-colorCard[1][0] + 1 <=2)
    {
        
        priorityCardSet+=(3-(colorCard[1][1]-colorCard[1][0] + 1));
    }

    //for heart card
    if(colorCard[2][1]-colorCard[2][0] + 1 <=2)
    {
        
        priorityCardSet+=(3-(colorCard[2][1]-colorCard[2][0] + 1));
    }

    //for spade first check we have enough spade card or not if enough then check for faceCardSet
    
    if(colorCard[3][1]-colorCard[3][0] + 1 <=priorityCardSet)
    {
        
        priorityCardSet=colorCard[3][1]-colorCard[3][0] + 1;
    }
    else
    {
        for(int i=colorCard[3][0]; i<=(colorCard[3][1]-priorityCardSet); i++)
        {
            if(playerCard[i]==53 || playerCard[i]==52 || playerCard[i]==51)
            {
                faceCardSet++;
            }
            if(playerCard[i]==53)
            {
                kingAndAce[3][1]=1;
            }
            else if(playerCard[i]==52)
            {
                kingAndAce[3][0]=1;
            }
        }
    }
    
    //face card for other colors
    // for heart
    faceCardSet=helper_Of_suggestionSet(&faceCardSet, &playerCard[0], &colorCard[0][0],&kingAndAce[2][0],2);
    // for Diamond
    faceCardSet=helper_Of_suggestionSet(&faceCardSet, &playerCard[0], &colorCard[0][0],&kingAndAce[1][0], 1);
    // for club
    faceCardSet=helper_Of_suggestionSet(&faceCardSet, &playerCard[0], &colorCard[0][0],&kingAndAce[0][0], 0);


    return ((faceCardSet+priorityCardSet)==0)?1:(faceCardSet+priorityCardSet);
}



int helper_Of_suggestionSet(int* faceCardSet, int* playerCard, int* colorCard, int* kingAndAce,int color)
{   
    
    for(int i=*((colorCard+2*color)+0); i<=*((colorCard+2*color)+1); i++)
    {   
        
        if(*(playerCard+i)==(2+(13*color)+12)) //ace
        {
            
            *(faceCardSet)=*(faceCardSet)+1;
            *(kingAndAce+1)=1; // ace is present
        }
        else if(*(playerCard+i)==(2+(13*color)+11)) // king
        {
            *(kingAndAce+0)=1; //king is present
            if(*((colorCard+2*color)+1)-*((colorCard+2*color)+0) >5)
            {                
                break;
            }
            else
            {
                if(*((colorCard+2*color)+1)-*((colorCard+2*color)+0) >=1)
                {
                    if(*(playerCard+i-1)==(2+(13*color)+12))
                    {
                        
                        *(faceCardSet)=*(faceCardSet)+1;
                        break;
                    }
                    else
                    {
                        for(int j=i+1; j<*((colorCard+2*color)+1)+1; j++)
                        {
                            if(*(playerCard+j)>(2+(13*color)+7))
                            {    
                                *(faceCardSet)=*(faceCardSet)+1;
                                break;
                            }
                        }
                    }
                }
            }
            break;
        }
        
    }
    return *faceCardSet;
}


// used to show initial and final index of each color used as temp only for testing purpose
/*void playersInfo::showInitialIndex()
{
    char sym[4]={'C','D','H','S'};

    for(int i=0; i<4; i++)
    {
        std::cout<<"For "<<sym[i]<<" Initial index: "<<colorCard[i][0]<<"  Final index: "<<colorCard[i][1]<<std::endl;
    }
}*/


int playersInfo::getKingAndAce(int color,int index)
{
    return kingAndAce[color][index];
}

void playersInfo::setKingAndAce(int color,int index)
{
    kingAndAce[color][index]=0;
}




