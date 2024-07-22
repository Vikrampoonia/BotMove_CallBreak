//show details of each round

//show each player position

void announceResult(playersInfo* ,int );

void announceResult(playersInfo* p,int roundNo)
{
    
    std::cout<<"\n\nscore  are\n";
    std::cout<<"Round No: 0   1   2   3 \n";
    int j=0;
    while(j<roundNo)
    {
        std::cout<<" "<<j+1<<"        "<<(p+0)->getScoreCard(j)<<"  "<<(p+1)->getScoreCard(j)<<"  "<<(p+2)->getScoreCard(j)<<"  "<<(p+3)->getScoreCard(j)<<"  "<<std::endl;
        j++;
    }



}