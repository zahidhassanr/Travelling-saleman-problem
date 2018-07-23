#include<bits/stdc++.h>
using namespace std;

int cityNum;
int cityLoc[20][2];
double disMatrix[20][20];
void AdjacencyMatrix();
int Nearest(vector<int> tour,int city);
vector<int> Construction();
void Cheapest();
int nearest(vector<int> tour);
void Nearest_insertion();
void TwoOpt(vector<int> tour);
double tourDistance(vector<int> tour);
vector<int> TwoOptSwap(vector<int> tour,int i, int k);
void ThreeOpt(vector<int> tour);
vector<int> ThreeOptSwap(vector<int> tour,int i,int j,int k);



int main()
{

    vector<int> tour;
    cin>>cityNum;
    for(int i=1; i<=cityNum; i++)
    {
        cin>>cityLoc[i][0];
        cin>>cityLoc[i][1];
    }
    AdjacencyMatrix();

    tour = Construction();

    double disCon=tourDistance(tour);
    cout<<"Construction distance :"<<disCon<<endl<<endl;
    Cheapest();
    Nearest_insertion();
    TwoOpt(tour);
    ThreeOpt(tour);

}

void AdjacencyMatrix()
{
    for(int i=1; i<=cityNum; i++)
    {
        for(int j=1; j<=cityNum; j++)
        {
            disMatrix[i][j]=sqrt(pow(cityLoc[i][0] - cityLoc[j][0],2) + pow(cityLoc[i][1] - cityLoc[j][1],2));
        }
    }

}

vector<int> Construction()
{
    vector<int> tour;

    int start=2;
    tour.push_back(start);

    int neighbor=Nearest(tour,start);
    while(neighbor !=-1)
    {
        tour.push_back(neighbor);
        neighbor= Nearest(tour,neighbor);
    }
cout<<"Construction tour: "<<endl;
    vector<int>::iterator it=tour.begin();

    while(it != tour.end())
    {
        cout<<*it<<"->";
        it++;
    }
    cout<< *tour.begin()<<endl<<endl;
    return tour;

}

bool find(vector<int> tour,int city)
{
    vector<int>::iterator it=tour.begin();

    while(it != tour.end())
    {
        if(*it == city) return true;
        it++;
    }
    return false;

}

int Nearest(vector<int> tour,int city)
{
    double temp=9999;
    int index=-1;
    for(int i=1; i<=cityNum; i++)
    {
        if((city!=i) && (disMatrix[city][i] < temp) && !find(tour,i))
        {
            temp=disMatrix[city][i];
            index=i;

        }
    }
    return index;
}


int nearest(vector<int> tour)
{
    double temp=999;
    int index=-1;

    for(int i=1; i<=cityNum; i++)
    {
        double sum=0;
        vector<int>::iterator it=tour.begin();
        if(find(tour,i)) continue;
        while(it != tour.end())
        {


            sum += disMatrix[i][*it];
            it++;


        }
        if(sum<temp)
        {
            temp=sum;
            index=i;
        }
    }
    return index;
}

void Cheapest()
{
    vector<int> tour;

    int start=2;
    tour.push_back(start);

    int neighbor=Nearest(tour,start);
    tour.push_back(neighbor);
    tour.push_back(start);

    vector<int>::iterator it=tour.begin();

    while(it != (tour.end()-1))
    {
        cout<<*it<<"->";
        it++;
    }
    cout<<*it<<endl;


    bool end=false;
    while(!end )
    {
        vector<int>::iterator pos;
        end=true;
        double temp=9999;
        int leastCity;
        for(int i=1; i<=cityNum; i++)
        {

            if(!find(tour,i))
            {
                end=false;
                vector<int>::iterator it=tour.begin();

                while(it != (tour.end()-1))
                {
                    if((disMatrix[*it][i]+disMatrix[i][*(it+1)]-disMatrix[*it][*(it+1)]) < temp)
                    {
                        temp=disMatrix[*it][i]+disMatrix[i][*(it+1)]-disMatrix[*it][*(it+1)];
                        leastCity=i;
                        pos=it+1;

                    }
                    it++;
                }
            }
        }
        cout<<leastCity<<' '<<endl;
        if(!end)
        {
            tour.insert(pos,leastCity);
        }
    }

    vector<int>::iterator it1=tour.begin();

cout<<"Cheapest path: "<<endl;
    while(it1 != (tour.end()-1))
    {
        cout<<*it1<<"->";
        it1++;
    }

    cout<<*it1<<endl<<endl;

    cout<<"Cheapest distance: "<<tourDistance(tour)<<endl<<endl;
}



void Nearest_insertion()
{
    vector<int> tour;

    int start=2;
    tour.push_back(start);

    int neighbor=Nearest(tour,start);
    tour.push_back(neighbor);
    tour.push_back(start);

    vector<int>::iterator it=tour.begin();

    while(it != (tour.end()-1))
    {
        cout<<*it<<"->";
        it++;
    }
    cout<<*it<<endl;

    int next=nearest(tour);
    while(next != -1)
    {
        double temp=9999;
        int leastCity;
        vector<int>::iterator pos;
        vector<int>::iterator it=tour.begin();

        while(it != (tour.end()-1))
        {
            if((disMatrix[*it][next]+disMatrix[next][*(it+1)]-disMatrix[*it][*(it+1)]) < temp)
            {
                temp=disMatrix[*it][next]+disMatrix[next][*(it+1)]-disMatrix[*it][*(it+1)];
                pos=it+1;

            }
            it++;
        }


        tour.insert(pos,next);
        next=nearest(tour);

    }

    cout<<"Nearest insertion path: "<<endl;
    vector<int>::iterator it1=tour.begin();
    while(it1 != (tour.end()-1))
    {
        cout<<*it1<<"->";
        it1++;
    }

    cout<<*it1<<endl<<endl;

    cout<<"Nearest insertion distance: "<<tourDistance(tour)<<endl<<endl;
}

double tourDistance(vector<int> tour)
{
    vector<int>::iterator it=tour.begin();
    double sum=0;
    while(it != (tour.end()-1))
    {
        sum +=disMatrix[*it][*(it+1)];
        it++;
    }
    return sum;
}

void TwoOpt(vector<int> tour)
{
    int size=tour.size();
    vector<int> newTour;
    int improve=0;

    while(improve <20)
    {
        double best_dis=tourDistance(tour);

        for(int i=0; i<size; i++)
        {
            for(int k=i+1; k<size; k++)
            {
                newTour=TwoOptSwap(tour,i,k);

                double new_dis= tourDistance(newTour);
                //cout<<"new dis"<<new_dis<<endl;

                if(new_dis < best_dis)
                {
                    improve=0;
                    tour=newTour;
                    best_dis=new_dis;
                }
            }

        }
        improve++;
    }
cout<<"2-Opt path: "<<endl;
    vector<int>::iterator it1=tour.begin();
    while(it1 != (tour.end()-1))
    {
        cout<<*it1<<"->";
        it1++;
    }

    cout<<*it1<<"->"<<*tour.begin()<<endl<<endl;

    cout<<"Improved 2-opt distance :"<<tourDistance(tour)<<endl;

}

vector<int> TwoOptSwap(vector<int> tour,int i, int k)
{
    int size=tour.size();
    vector<int> newTour(tour.size(),0);

    for(int c=0; c<=i-1; ++c)
    {
        newTour[c]=tour[c];
    }

    int dec=0;

    for(int c=i; c<=k; ++c)
    {

        newTour[c]=tour[k-dec];

        dec++;
    }

    for(int c=k+1; c<size; ++c)
    {
        newTour[c]=tour[c];
    }

    return newTour;

}


void ThreeOpt(vector<int> tour)
{
    int size=tour.size();
    vector<int> newTour;
    int improve=0;

    while(improve<30)
    {
        double best_dis=tourDistance(tour);

        for(int i=0; i<size; i++)
        {
            for(int j=i+1; j<size; j++)
            {
                for(int k=j+1; k<size; k++)
                {
                    newTour=ThreeOptSwap(tour,i,j,k);

                    double new_dis= tourDistance(newTour);

                    if(new_dis < best_dis)
                    {
                        improve=0;
                        tour=newTour;
                        best_dis=new_dis;
                    }
                }
            }
        }
        improve++;
    }

    cout<<"3-opt path: "<<endl;
    vector<int>::iterator it1=tour.begin();
    while(it1 != (tour.end()-1))
    {
        cout<<*it1<<"->";
        it1++;
    }

    cout<<*it1<<"->"<<*tour.begin()<<endl<<endl;
    cout<<"Improved 3-opt distance :"<<tourDistance(tour)<<endl<<endl;

}


vector<int> ThreeOptSwap(vector<int> tour,int i,int j,int k)
{
    int size=tour.size();
    vector<int> newTour1(tour.size(),0);
    vector<int> newTour2(tour.size(),0);
    vector<int> newTour3(tour.size(),0);
    vector<int> newTour4(tour.size(),0);
    vector<int> newTour5(tour.size(),0);

    int tour1Index;
    int tour2Index;
    int tour3Index;
    int tour4Index;
    int tour5Index;

    int c;
    for(c=0; c<=i-1; ++c)
    {
        newTour1[c]=tour[c];
        newTour2[c]=tour[c];
        newTour3[c]=tour[c];
        newTour4[c]=tour[c];
        newTour5[c]=tour[c];
    }
    tour1Index=c;
    tour2Index=c;
    tour3Index=c;
    tour4Index=c;
    tour5Index=c;

    for(int d=j; d<=k-1; d++)
    {
        newTour1[tour1Index++]=tour[d];
    }

    for(int d=i; d<=j-1; d++)
    {
        newTour1[tour1Index++]=tour[d];
    }

    for(int c=j; c>i-1; c--)
    {

        newTour2[tour2Index++]=tour[c];
    }
    for(int c=j+1; c<=k-1; c++)
    {
        newTour2[tour2Index++]=tour[c];
    }
    for(int c=i; c<=j-1; c++)
    {
        newTour3[tour3Index++]=tour[c];
    }
    for(int c=k-1; c>j-1; c--)
    {
        newTour3[tour3Index++]=tour[c];
    }
    for(int c=j; c>i-1; c--)
    {

        newTour4[tour4Index++]=tour[c];
    }
    for(int c=k-1; c>j; c--)
    {
        newTour4[tour4Index++]=tour[c];
    }
    for(int c=k-1; c>j; c--)
    {
        newTour5[tour5Index++]=tour[c];
    }
    for(int c=j; c>i-1; c--)
    {

        newTour5[tour5Index++]=tour[c];
    }



    for(int c=k; c<size; ++c)
    {
        newTour1[tour1Index++]=tour[c];
        newTour2[tour2Index++]=tour[c];
        newTour3[tour3Index++]=tour[c];
        newTour4[tour4Index++]=tour[c];
        newTour5[tour5Index++]=tour[c];

    }
    double array[6];


    array[1]=tourDistance(newTour1);
    array[2]=tourDistance(newTour2);
    array[3]=tourDistance(newTour3);
    array[4]=tourDistance(newTour4);
    array[5]=tourDistance(newTour5);

    double min=array[1];
    int index=1;
    for(int i=2; i<=5; i++)
    {
        if(array[i] < min)
        {
            min=array[i];
            index=i;
        }
    }

    switch(index)
    {
    case 1:
        return newTour1;
    case 2:
        return newTour2;
    case 3:
        return newTour3;
    case 4:
        return newTour4;
    case 5:
        return newTour5;

    }



}
/*


15
1 10
2 12
3 16
4 18
7 8
5 6
8 5
7 9
2 15
10 1
15 12
13 5
20 10
17 4
18 1
*/
