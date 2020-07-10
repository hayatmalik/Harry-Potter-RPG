#include <iostream>
#include <string>
#include "RPG3.cpp"
#include <windows.h> // library for sound
#include <mmsystem.h> // library for sound
#include <mciavi.h>

using namespace std;

int main()
{
    GameManager Game;
    bool gameend=false;
    string name="Mr. Potter";
    cout<<"Welcome "<<name<<"!"<<endl;
    //cout<<"Enter your Name"<<endl;
    mciSendString("open \"harry_potter.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
     cout<<"You are the Chosen One and you must defeat He-who-must-not-be-Named and save the Wizarding World. \nExplore the map to find items and Spells and Assemble the Deathly Hallows. But be warned for there may be enemies along your path "<<endl;
    int input=0;
    cout<<"You are currently at the left corner of a 7x7 map"<<endl;
    mciSendString("play mp3", NULL, 0, NULL);
    while(gameend==false)
    {
        cout<<"\n \n Map: "<<endl;
        Game.displayMap();
        cout<<" \n Menu: "<<endl;
        cout<<" 1)Move your player \n 2)Drop an item \n 3)Craft the Deathly Hallows \n 4)Show your status \n Press 0 to quit"<<endl;
        cin>> input;

        if (input==0)
        {
            cout<<"You have quit the game"<<endl;
            cout<<"Goodbye! "<<name<<endl;
            gameend==true;
            return 0;
        }
        else if (input==1)
        {
            int direction;
            cout<<"Enter direction you want to move. 1 for North, 2 for West, 3 for East, 4 for South"<<endl;
            cin>> direction;

            if (direction<1 || direction>4)
            {
                cout<<"Incorrect Entry"<<endl;
            }
            else
            {
                bool movep=Game.playerMove(direction);
                if (movep==false)
                {
                    cout<<"Harry did not move"<<endl;
                }
            }
        }

        else if (input==2)
        {
            Game.dropItem();
        }
        else if (input==3)
        {
            Game.craft();
        }
        else if (input==4)
        {
            Game.showPlayerStatus();
        }

        else if (input==7)
        {
            for (int i=0; i<7; i++)
            {
                for (int j=0; j<7; j++)
                {
                    cout<<Game.gamemap[i][j]<< "\t";
                }
                cout<<endl;
            }
        }
        bool alive=Game.isPlayerAlive();
        if(alive==false)
        {
            cout<<"Voldemort: HARRY POTTER IS DEAD!!"<<endl;
            mciSendString("close mp3", NULL, 0, NULL);
            mciSendString("open \"voldemorts_laugh.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
            mciSendString("play mp3", NULL, 0, NULL);
            gameend=true;
            int k;
            cin>> k;

        }

    }
    return 0;
}
