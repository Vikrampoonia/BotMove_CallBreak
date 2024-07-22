
/*
    containing array of 52 numbers 
    functions:
    random shuffle
    distribute cards
    mapEach card with Color Face

    playnumber start from 0 to 3

*/
#include <bits/stdc++.h> 
#include<vector>

char mapping_color(int );
char mapping_number(int );
void sortCards(int* );
void divideArray(int* , int , int );
void MergeArray(int* ,int , int , int );

class cardInfo
{
    std::vector<int>deck{2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53};
    
    public:
    //using inbuilt function
    void shuffleCard();
    void distributeCards(int* arr, int playerNumber); // function that fill cardvalues and this find in CardInfo class
    void mapCard(char* arr1, int* arr2); // function that map cardvalues with card Color and this find in CardInfo class
    void showCard(int* arr);
    void showCard(char* arr);
};

void cardInfo::distributeCards(int* arr, int playerNumber)
{   
    int k=0;
    for(auto i=deck.begin()+playerNumber; i!=deck.end(); i+=4)
    {   
        *(arr+k)=(*i);
        k++;
        if(k==13)
        {
            break;
        }
    }
    sortCards(arr);
    //showCard(arr);
}

void cardInfo::mapCard(char* arr1, int* arr2) //arr1=containg array in which we have to put character arr2=containing values
{
    for(int i=0; i<13; i++)
    {
        *((arr1+i*2)+0)=mapping_color(*(arr2+i));
        *((arr1+i*2)+1)=mapping_number(*(arr2+i));
        std::cout<<*((arr1+i*2)+0)<<*((arr1+i*2)+1)<<" ";
    }std::cout<<std::endl;std::cout<<std::endl;
}

void cardInfo::shuffleCard()
{
    srand(unsigned(time(0)));
    random_shuffle(deck.begin(),deck.end());     
}


char mapping_number(int num) //used for mapping numbers
{
    if(num>14)
    {
        while(num>14)
        {
            num-=13;
        }
    }
    if(num==-1) //card is thrown
    {
        char ch='X';
        return ch;
    }
    if(num>=2 && num<=10)
    {
        char ch=(num+48)+'\0';
        if(num==10) //for ten use T
        {
            ch='T';
        }
        return ch;
    }
    else
    {
        char symbol[4]={'J','B','K','A'}; // number grater than 10 are(11,12,13,14)=>(J,B,K,A);
        num=num-11;
        return symbol[num];
    }
}

char mapping_color(int num) //used for mapping colors
{
    char symbol[5]={'C','D','H','S','X'}; // x is used for already card thrown
    if(num>=2 && num<=14)
    {
        num=0;
    }
    else if(num>=15 && num<=27)
    {
        num=1;
    }
    else if(num>=28 && num<=40)
    {
        num=2;
    }
    else if(num>=41 && num<=53)
    {
        num=3;
    }
    else //here num==-1
    {
        num=4;
    }
    return symbol[num];
}



void cardInfo::showCard(int* arr) //help to show cards values
{   
    for(int i=0; i<13; i++)
    {
        std::cout<<*(arr+i)<<" ";
    }std::cout<<std::endl;
}

void cardInfo::showCard(char* arr) //help to show cards map with colors and numbers
{   
    for(int i=0; i<13; i++)
    {
        std::cout<<*((arr+i*2)+0)<<*((arr+i*2)+1)<<" ";
    }std::cout<<std::endl;
}


void sortCards(int* arr) //implementing merge sort algorithm
{
    int start=0, end=12;
    divideArray(arr, start, end);
}

void MergeArray(int* arr,int start, int mid, int end)
{
    int n1=mid-start+1;
    int n2=end-mid;

    int a1[n1];
    int a2[n2];

    for(int i=0; i<n1; i++)
    {
        a1[i]=*(arr+start+i);
    }

    for(int i=0; i<n2; i++)
    {
        a2[i]=*(arr+mid+i+1);
    }
    int k=start;
    int i=0,j=0;
    while(i<n1 && j<n2)
    {
        if(a1[i]>a2[j])
        {
            *(arr+k++)=a1[i++];
        }
        else
        {
            *(arr+k++)=a2[j++];
        }
        
    }

    while(i<n1)
    {
        *(arr+k++)=a1[i++];   
    }
    while(j<n2)
    {
        *(arr+k++)=a2[j++];   
    }
}

void divideArray(int* arr, int start, int end)
{
    
    if(start<end)
    {
        int mid=start+(end-start)/2;
        divideArray(arr, start, mid);
        divideArray(arr, mid+1, end);
        MergeArray(arr,start,mid,end);
    }
    
}

