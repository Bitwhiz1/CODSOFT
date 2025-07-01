#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>
using namespace std;
int main(){
    srand(time(0));
    int choice,maxRange;
    cout<<"Welcome to Guess the Number: Level-Up Edition!"<<endl;
    cout<<"Choose your difficulty:"<<endl;
    cout<<"1. Easy (1-50)"<<endl;
    cout<<"2. Medium (1-100)"<<endl;
    cout<<"3. Hard (1-500)"<<endl;
    cout<<"Enter your choice (1-3): ";
    cin>>choice;
    if(choice==1){
        maxRange=50;
        cout<<"Easy Mode: Good luck!"<<endl;
    }else if(choice==2){
        maxRange=100;
        cout<<"Medium Mode: Let's spice it up!"<<endl;
    }else if(choice==3){
        maxRange=500;
        cout<<"Hard Mode: Bring it on!"<<endl;
    }else{
        cout<<"Invalid choice. Defaulting to Medium Mode."<<endl;
        maxRange=100;
    }
    int secretNumber=rand()%maxRange+1;
    int guess,attempts=0;
    cout<<"I'm thinking of a number between 1 and "<<maxRange<<"."<<endl;
    do{
        cout<<"Take a guess: ";
        cin>>guess;
        attempts++;
        int diff=abs(guess-secretNumber);
        if(guess<secretNumber){
            if(diff>maxRange/2){
                cout<<"Not even close. Way too low!"<<endl;
            }else if(diff>10){
                cout<<"A bit low. You're getting closer!"<<endl;
            }else{
                cout<<"Very close! Just a little low."<<endl;
            }
        }else if(guess>secretNumber){
            if(diff>maxRange/2){
                cout<<"Not even close. Way too high!"<<endl;
            }else if(diff>10){
                cout<<"A bit high. You're getting closer!"<<endl;
            }else{
                cout<<"Very close! Just a little high."<<endl;
            }
        }else{
            cout<<"Boom! You nailed it in "<<attempts<<" tries."<<endl;
        }
    }while(guess!=secretNumber);
    cout<<"Thanks for playing. See you next level."<<endl;
    return 0;
}
