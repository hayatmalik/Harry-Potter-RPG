#include <iostream>
#include <string>
#include  <time.h>
#include  <cstdlib>
#include "RPG.h"
#include <windows.h> // library for sound
#include <mmsystem.h> // library for sound
#include <mciavi.h>

using namespace std;

GameManager::GameManager()
{
    gamemap= new string*[7];
    for (int i=0; i<7; i++)
    {
        gamemap[i]= new string[7];
    }

    for (int i=0; i<7; i++)
    {
         for (int j=0; j<7; j++)
         {
            gamemap[i][j]= "-0/N/_";
         }
    }


    srand(time(NULL));


    minionNodesSize=0;
    Node** minionNodes= new Node*[4];
    for (int i=0; i<4; i++)
        {
            minionNodes[i]=NULL;
        }

    for (int i=0; i<4; i++)
    {
        bool done=false;
        while (done==false)
        {
        int mi=rand() % 7;
        int mj=rand() % 7;
        if (gamemap[mi][mj][3]== 'N')
                {
                    gamemap[mi][mj][3]= 'D';
                    done=true;
                }
        }
    }
    bool done=false;
    while (done==false)
    {
        int bi=rand() % 7;
        int bj=rand() % 7;
        if (gamemap[bi][bj][3]== 'N')
                {
                    gamemap[bi][bj][3]= 'V';
                    done=true;
                }
    }

        done=false;
        while (done==false)
        {
        int ci=rand() % 7;
        int cj=rand() % 7;
        if (gamemap[ci][cj][5]== '_')
                {
                    gamemap[ci][cj][5]= 'C';
                    done=true;
                }
        }


        done=false;
        while (done==false)
        {
        int di=rand() % 7;
        int dj=rand() % 7;
        if (gamemap[di][dj][5]== '_')
                {
                    gamemap[di][dj][5]= 'R';
                    done=true;
                }
        }


        done=false;
        while (done==false)
        {
        int ei=rand() % 7;
        int ej=rand() % 7;
        if (gamemap[ei][ej][5]== '_')
                {
                    gamemap[ei][ej][5]= 'E';
                    done=true;
                }
        }

        done=false;
        while (done==false)
        {
        int ai=rand() % 7;
        int aj=rand() % 7;
        if (gamemap[ai][aj][5]== '_')
                {
                    gamemap[ai][aj][5]= 'S';
                    done=true;
                }
        }



        done=false;
        while (done==false)
        {
        int hi=rand() % 7;
        int hj=rand() % 7;
        if (gamemap[hi][hj][5]== '_')
                {
                    gamemap[hi][hj][5]= 'H';
                    done=true;
                }
        }


    Character Player;
    Player.characterType="Mr. Potter";
    Player.HP=100;
    Player.inventorySize=2;
    Player.inventory= new Item[Player.inventorySize];
    Player.inventory[0].itemName="Expelliarmus";
    Player.inventory[0].itemCategory=1;
    Player.inventory[0].points=20;
    Player.inventory[1].itemName="Health Potion";
    Player.inventory[1].itemCategory=2;
    Player.inventory[1].points=20;

    head = new Node;
    head->c= new Character;
    *head->c= Player;
    head->nodePosition[0]=0;
    head->nodePosition[1]=0;
    head->North=NULL;
    head->South=NULL;
    head->East=NULL;
    head->West=NULL;

    gamemap[0][0][3]='P';
    gamemap[0][0][1]='1';
    playerNode=head;

}
/*~GameManager()
{
    delete gamemap;
    delete Player;
    delete minionNodes;
    delete head;
}
*/

void GameManager::searchNode(Node*& temp, Node* calling, int position[2], int direction)
{
    if (calling==NULL)
    {
        return;
    }
    if (calling->nodePosition[0]==position[0] && calling->nodePosition[1]==position[1])
    {
        temp=calling;
        return;
    }
    if (calling->North==NULL && calling->South==NULL && calling->East==NULL && calling->West==NULL)
    {
        return;
    }

    calling->isVisited=1;

    if (temp==NULL && direction!=4)
    {
        if (calling->North!=NULL && calling->North->isVisited!=1)
        {
            searchNode(temp, calling->North, position, 1);
        }
    }
    if (temp==NULL && direction!=1)
    {
        if (calling->South!=NULL && calling->South->isVisited!=1)
        {
            searchNode(temp, calling->South, position, 4);
        }
    }
    if (temp==NULL && direction!=2)
    {
        if (calling->East!=NULL && calling->East->isVisited!=1)
        {
            searchNode(temp, calling->East, position, 3);
        }
    }
    if (temp==NULL && direction!=3)
    {
        if (calling->West!=NULL && calling->West->isVisited!=1)
        {
            searchNode(temp, calling->West, position, 2);
        }
    }

    head->isVisited=0;
    return;
}

void Node::linkNode(Node* n,int direction)
{
   if(direction==1)
   {
        North=n;
   }

   else if(direction==4)
   {
       South=n;
   }

   else if(direction==2)
    {
        West=n;
    }

    else if(direction==3)
    {
        East=n;
    }


     return;
}

bool GameManager::playerMove(int direction)
{

Node* temp;
int ni;
int nj;

    //Moving North

    if (direction==1)
    {
        if(playerNode->nodePosition[0]==0)
        {
            cout<<"You are at the top of the map"<<endl;
            return false;
        }
        else if(playerNode->North==NULL)
        {
            //creating new Node
            temp=new Node;
            ni=playerNode->nodePosition[0] - 1;
            nj=playerNode->nodePosition[1];
            temp->nodePosition[0]=ni;
            temp->nodePosition[1]=nj;
            gamemap[ni][nj][1]='1';
            //cout<<"New Node has been created"<<endl;

            //linking with current Node
            playerNode->North=temp;
            temp->South=playerNode;
            //linking with other existing Nodes
            //North
            if (ni-1>=0 && gamemap[ni-1][nj][1]=='1')
            {
            Node* temp2=NULL;
            int arr[2]={ni-1,nj};
            searchNode(temp2,head,arr,0);
            temp->linkNode(temp2, 1);
            }
            //West
            if (nj-1>=0 && gamemap[ni][nj-1][1]=='1')
            {
            Node* temp2=NULL;
            int arr[2]={ni,nj-1};
            searchNode(temp2,head,arr,0);
            temp->linkNode(temp2, 2);
            }
            //East
            if (nj+1<=6 && gamemap[ni][nj+1][1]=='1')
            {
            Node* temp2=NULL;
            int arr[2]={ni,nj+1};
            searchNode(temp2,head,arr,0);
            temp->linkNode(temp2, 3);
            }
        }

        else
        {
            temp=playerNode->North;
            ni=playerNode->nodePosition[0] - 1;
            nj=playerNode->nodePosition[1];
        }
    }

    //moving South
    if (direction==4)
    {
        if(playerNode->nodePosition[0]==6)
        {
            cout<<"You are at the bottom of the map"<<endl;
            return false;
        }
        if(playerNode->South==NULL)
        {
            //creating new Node
            temp=new Node;
            ni=playerNode->nodePosition[0] + 1;
            nj=playerNode->nodePosition[1];
            temp->nodePosition[0]=ni;
            temp->nodePosition[1]=nj;
            gamemap[ni][nj][1]='1';
            //cout<<"New Node has been created"<<endl;

            //linking with current Node
            playerNode->South=temp;
            temp->North=playerNode;
            //linking with other existing Nodes
            //South
            if (ni+1<=6 && gamemap[ni+1][nj][1]=='1')
            {
            Node* temp2=NULL;
            int arr[2]={ni+1,nj};
            searchNode(temp2,head,arr,0);
            temp->linkNode(temp2, 4);
            }
            //West
            if (nj-1>=0 && gamemap[ni][nj-1][1]=='1')
            {
            Node* temp2=NULL;
            int arr[2]={ni,nj-1};
            searchNode(temp2,head,arr,0);
            temp->linkNode(temp2, 2);
            }
            //East
            if (nj+1<=6 && gamemap[ni][nj+1][1]=='1')
            {
            Node* temp2=NULL;
            int arr[2]={ni,nj+1};
            searchNode(temp2,head,arr,0);
            temp->linkNode(temp2, 3);
            }
        }
        else
        {
            temp=playerNode->South;
            ni=playerNode->nodePosition[0] + 1;
            nj=playerNode->nodePosition[1];
        }

    }

    //moving West
    if (direction==2)
    {
        if(playerNode->nodePosition[1]==0)
        {
            cout<<"You are at the left most of the map"<<endl;
            return false;
        }
        if(playerNode->West==NULL)
        {
            //creating new Node
            temp=new Node;
            ni=playerNode->nodePosition[0];
            nj=playerNode->nodePosition[1]-1;
            temp->nodePosition[0]=ni;
            temp->nodePosition[1]=nj;
            gamemap[ni][nj][1]='1';
            //cout<<"New Node has been created"<<endl;

            //linking with current Node
            playerNode->West=temp;
            temp->East=playerNode;
            //linking with other existing Nodes
            //North
            if (ni-1>=0 && gamemap[ni-1][nj][1]=='1')
            {
            Node* temp2=NULL;
            int arr[2]={ni-1,nj};
            searchNode(temp2,head,arr,0);
            temp->linkNode(temp2, 1);
            }
            //South
            if (ni+1<=6 && gamemap[ni+1][nj][1]=='1')
            {
            Node* temp2=NULL;
            int arr[2]={ni+1,nj};
            searchNode(temp2,head,arr,0);
            temp->linkNode(temp2, 4);
            }
            //West
            if (nj-1>=0 && gamemap[ni][nj-1][1]=='1')
            {
            Node* temp2=NULL;
            int arr[2]={ni,nj-1};
            searchNode(temp2,head,arr,0);
            temp->linkNode(temp2, 2);
            }
        }

        else
        {
            temp=playerNode->West;
            ni=playerNode->nodePosition[0];
            nj=playerNode->nodePosition[1]-1;
        }

    }

        //moving East
    if (direction==3)
    {
        if(playerNode->nodePosition[1]==6)
        {
            cout<<"You are at the right most of the map"<<endl;
            return false;
        }
        if(playerNode->East==NULL)
        {
            //creating new Node
            temp=new Node;
            ni=playerNode->nodePosition[0];
            nj=playerNode->nodePosition[1]+1;
            temp->nodePosition[0]=ni;
            temp->nodePosition[1]=nj;
            gamemap[ni][nj][1]='1';
            //cout<<"New Node has been created"<<endl;
            //linking with current Node
            playerNode->East=temp;
            temp->West=playerNode;
            //linking with other existing Nodes
            //North
            if (ni-1>=0 && gamemap[ni-1][nj][1]=='1')
            {
            Node* temp2=NULL;
            int arr[2]={ni-1,nj};
            searchNode(temp2,head,arr,0);
            temp->linkNode(temp2, 1);
            }
            //South
            if (ni+1<=6 && gamemap[ni+1][nj][1]=='1')
            {
            Node* temp2=NULL;
            int arr[2]={ni+1,nj};
            searchNode(temp2,head,arr,0);
            temp->linkNode(temp2, 4);
            }
            //East
            if (nj+1<=6 && gamemap[ni][nj+1][1]=='1')
            {
            Node* temp2=NULL;
            int arr[2]={ni,nj+1};
            searchNode(temp2,head,arr,0);
            temp->linkNode(temp2, 3);
            }
        }
        else
        {
            temp=playerNode->East;
            ni=playerNode->nodePosition[0];
            nj=playerNode->nodePosition[1]+1;
        }
    }

    //cout<<"Node has been linked"<<endl;
        //check for character

 if (gamemap[ni][nj][3]=='D')
        {
           cout<<"You have encountered a Death Eater"<<endl;
           if (temp->c==NULL)
           {
           Character Minion;
           Minion.characterType="Death Eater";
           Minion.HP=100;
           Minion.inventorySize=1;
           Minion.inventory= new Item;
           Minion.inventory->itemName="Crucio";
           Minion.inventory->itemCategory=1;
           Minion.inventory->points=15;
           temp->c=new Character;
           *temp->c=Minion;
           //cout<<"MNS: "<<minionNodesSize<<endl;
            //minionNodes[minionNodesSize]= new Node;
            //minionNodes[minionNodesSize]=temp;
            //minionNodesSize++;
            //cout<<"Enemy created"<<endl;
           }

           cout<<"Are you ready to fight. Press 1 for yes or 0 for no"<<endl;
           int k;
           cin >> k;
           if (k==0)
           {
               return false;
           }
           else if (k==1)
           {
               cout<<"Death Eater: Well Well, if it isn't Potter"<<endl;
               bool win=false;
               win= fight(temp);
               if (win==true)
               {
                   gamemap[playerNode->nodePosition[0]][playerNode->nodePosition[1]][3]='N';
                   temp->c=playerNode->c;
                   playerNode=temp;
                   gamemap[ni][nj][3]='P';
               }
               else
               {
                   cout<<"You lost the fight"<<endl;
                   return false;
               }
           }
        }
    else if (gamemap[ni][nj][3]=='V')
        {
           cout<<"You have encountered Voldemort"<<endl;
           if (temp->c==NULL)
           {

            Character Boss;
            Boss.characterType="Voldemort";
            Boss.HP=100;
            Boss.inventorySize=1;
            Boss.inventory= new Item;
            Boss.inventory->itemName="Avada Kedavra";
            Boss.inventory->itemCategory=1;
            Boss.inventory->points=80;
            temp->c=new Character;
           *temp->c=Boss;
           //cout<<"boss created"<<endl;
           }

           cout<<"Are you ready to fight. Press 1 for yes or 0 for no"<<endl;
           int k;
           cin >> k;
           if (k==0)
           {
               return false;
           }
           else if (k==1)
           {
                cout<<"Voldemort: Harry Potter. The Boy who lived. Come to Die"<<endl;
                mciSendString("close mp3", NULL, 0, NULL);
                mciSendString("open \"voldemort_harry.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
                mciSendString("play mp3", NULL, 0, NULL);
               bool win;
               win= fight(temp);
               if (win==true)
               {
                   gamemap[playerNode->nodePosition[0]][playerNode->nodePosition[1]][3]='N';
                   temp->c=playerNode->c;
                   playerNode=temp;
                   gamemap[ni][nj][3]='P';
                   gamewon();
                   return true;
               }
               else
               {
                   cout<<"You lost the fight"<<endl;
                   return false;
               }
           }
        }

    else if (gamemap[ni][nj][3]=='N')
        {
            gamemap[playerNode->nodePosition[0]][playerNode->nodePosition[1]][3]='N';
            temp->c=playerNode->c;
            playerNode=temp;
            gamemap[ni][nj][3]='P';
        }
    else
    {
        cout<<"Error"<<endl;
    }

    //cout<<"Player has moved"<<endl;
    //check for item
    if (gamemap[ni][nj][5]!='_')
    {
        cout<<"You have found an item. Do you want to pick it up? Press 1 for yes and 0 for no"<<endl;

        if (gamemap[ni][nj][5]=='S')
        {
            Item Axe;
            Axe.itemName= "RictoSempra";
            Axe.itemCategory=1;
            Axe.points=40;
            playerNode->item= new Item;
            *playerNode->item=Axe;
        }
        else if (gamemap[ni][nj][5]=='H')
        {
            Item HealthPotion;
            HealthPotion.itemName="Health Potion";
            HealthPotion.itemCategory=2;
            HealthPotion.points=20;
            playerNode->item= new Item;
            *playerNode->item=HealthPotion;
        }
        else if (gamemap[ni][nj][5]=='C')
        {
            Item DSpiece;
            DSpiece.itemName= "The Invisibility Cloak";
            DSpiece.itemCategory=3;
            DSpiece.points=0;
            playerNode->item= new Item;
            *playerNode->item=DSpiece;
        }
        else if (gamemap[ni][nj][5]=='R')
        {
            Item DSpiece;
            DSpiece.itemName= "The Resurrection Stone";
            DSpiece.itemCategory=3;
            DSpiece.points=0;
            playerNode->item= new Item;
            *playerNode->item=DSpiece;
        }
        else if (gamemap[ni][nj][5]=='E')
        {
            Item DSpiece;
            DSpiece.itemName= "The Elder Wand";
            DSpiece.itemCategory=3;
            DSpiece.points=0;
            playerNode->item= new Item;
            *playerNode->item=DSpiece;
        }
        else if (gamemap[ni][nj][5]=='I')
        {
            cout<<"It is the item you dropped"<<endl;
        }
        else
        {
            cout<<"Error"<<endl;
        }

        int p;
        cin>> p;

        if (p==1)
        {
            pickItem();
            //mciSendString("close mp3", NULL, 0, NULL);
        }
        else if (p==0)
        {
            cout<<"You did not pick up item"<<endl;
        }
        else
        {
            cout<<"Error"<<endl;
        }

    }
    return true;
}

bool GameManager::fight(Node* enemyNode)
{

    bool fightend=false;

    while(fightend==false)
    {
        showEnemy(enemyNode);
        showPlayerStatus();

        if(playerNode->c->HP>0)
        cout<<"You are in attack phase"<<endl;
        cout<<"Choose the Spell you want to use or press -1 to not attack"<<endl;
        int choice;
        cin>> choice;
        if (choice!=-1 && choice<playerNode->c->inventorySize)
        {
        srand(time(NULL));
        int a=rand() % 3;
        useItem(playerNode->c->inventory[choice], enemyNode, a);
        }
        else if(choice==-1)
        {
            cout<<"You did not attack"<<endl;
        }
        else
        {
            cout<<"Invalid Entry"<<endl;
        }
        if(enemyNode->c->HP>0)
        {
            cout<<"You are in defense phase"<<endl;
            cout<<"Press 1 to dodge and 2 to defend"<<endl;
            int d;
            cin >> d;

            if (d==1)
            {
                d=rand() % 2;
                useItem(*(enemyNode->c->inventory),playerNode,d);
            }

            else if (d==2)
            {
                useItem(*(enemyNode->c->inventory),playerNode,d);
            }
            else
            {
                cout<<"Invalid Entry"<<endl;
                useItem(*(enemyNode->c->inventory),playerNode,1);
            }
        }

        if (playerNode->c->HP<=0 || enemyNode->c->HP<=0)
        {
            fightend=true;
        }

    }
    bool win=isPlayerAlive();
    if (win==true)
        {
            cout<<"Congratulations you have defeated the enemy"<<endl;
            return true;
        }
    else
    {
        return false;
    }

}


void GameManager::showEnemy (Node* enemyNode)
{
    cout<<"-----------------------"<<endl;
    cout<<"Character:"<<enemyNode->c->characterType<<endl;
    cout<<"HP: "<<enemyNode->c->HP<<endl;
    cout<<"Items in inventory: "<<enemyNode->c->inventorySize<<endl;
    cout<<enemyNode->c->inventory->itemName<< "\t " <<enemyNode->c->inventory->points<<" points"<<endl;
    cout<<"-----------------------"<<endl;
}

void GameManager::showPlayerStatus()
{
    cout<<"-----------------------"<<endl;
    cout<<playerNode->c->characterType<<endl;
    cout<<"HP: "<<playerNode->c->HP<<endl;
    cout<<"Inventory: "<<playerNode->c->inventorySize<<endl;
    for (int i=0; i<playerNode->c->inventorySize; i++)
    {
        cout<<i<<") "<<playerNode->c->inventory[i].itemName<<" \t "<<playerNode->c->inventory[i].points<<" points"<<endl;
    }
    cout<<"-----------------------"<<endl;
}

bool GameManager::isPlayerAlive()
{
    if(playerNode->c->HP<=0)
    {
        return false;
    }

    else
        return true;

}

void GameManager::pickItem()
{
    mciSendString("close mp3", NULL, 0, NULL);
   mciSendString("open \"magic_wand.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
   mciSendString("play mp3", NULL, 0, NULL);
    int iv=(playerNode->c->inventorySize)+1;
    Item* tempinv= new Item[iv];
    for (int i=0; i<iv-1; i++)
    {
        tempinv[i]= playerNode->c->inventory[i];
    }
    tempinv[iv-1]= *(playerNode->item);
    playerNode->c->inventorySize++;
    playerNode->c->inventory=tempinv;

    int pi=playerNode->nodePosition[0];
    int pj=playerNode->nodePosition[1];
    gamemap[pi][pj][5]='_';
    playerNode->item=NULL;
    showPlayerStatus();

}

void GameManager::dropItem()
{
    int ci=playerNode->nodePosition[0];
    int cj=playerNode->nodePosition[1];

    if (gamemap[ci][cj][5]!='_')
    {
        cout<<"You cannot drop an item here"<<endl;
        return;
    }

    showPlayerStatus();
    cout<<"Which item do you want to drop"<<endl;
    int k;
    cin>>k;
    if(k>=playerNode->c->inventorySize)
    {
        cout<<"Invalid Entry"<<endl;
        return;
    }
    playerNode->item=new Item;
    *playerNode->item=playerNode->c->inventory[k];
    gamemap[playerNode->nodePosition[0]][playerNode->nodePosition[1]][5]='I';
    int si=playerNode->c->inventorySize;
    Item* temp=new Item[si-1];
    int j=0;
    for (int i=0; i<si; i++)
    {
        if (i!=k)
        {
            temp[j]=playerNode->c->inventory[i];
            j++;
        }
    }
    playerNode->c->inventory=temp;
    playerNode->c->inventorySize--;
    cout<<"You have dropped an item"<<endl;

}

void GameManager::useItem(Item item, Node* character,int choice)
{
    if (item.itemCategory==2)
    {
        if (playerNode->c->HP>80)
        {
            cout<<"You cannot use Health Potion right now"<<endl;
            return;
        }
        playerNode->c->HP= playerNode->c->HP + item.points;
        int si=playerNode->c->inventorySize;
        Item* temp=new Item[si-1];
        int k;
        for (int i=0; i<si; i++)
        {
            if (playerNode->c->inventory[i].itemName=="Health Potion")
                {k=i;}
        }
        int j=0;
        for (int i=0; i<si; i++)
        {
            if (i!=k)
            {
                temp[j]=playerNode->c->inventory[i];
                j++;
            }
        }
        playerNode->c->inventory=temp;
        playerNode->c->inventorySize--;
        cout<<"You used a health potion. You HP has been increased"<<endl;
    }

    else if (item.itemCategory==1)
    {
        if (choice==0)
        {
            cout<<"The attack was not dodged"<<endl;
            character->c->HP= character->c->HP - item.points;
        }

        else if (choice==1)
        {
            cout<<"The attack was dodged"<<endl;
        }
        else if (choice==2)
        {
            character->c->HP= character->c->HP - (item.points * 0.5);
            cout<<"The attack was defended"<<endl;
        }
    }
    else
    {
        cout<<"You cannot attack with this item"<<endl;
    }
    return;
}
void GameManager::displayMap()
{
    for (int i=0; i<7; i++)
    {
        for (int j=0; j<7; j++)
        {
            if (gamemap[i][j][1]=='0')
            {
                cout<<" ";
            }
            if (gamemap[i][j][1]=='1')
            {
                if(gamemap[i][j][3]!='N')
                {
                    cout<<gamemap[i][j][3];
                }
                else if (gamemap[i][j][5]!='_')
                {
                    cout<<gamemap[i][j][5];
                }
                else
                {
                    cout<<"1";
                }
            }
        }
        cout<<endl;
    }
}
void GameManager::gamewon()
{
    cout<<"You have won the game"<<endl;
    cout<<"Press zero to quit now"<<endl;
}
void GameManager::craft()
{
    int counter=0;
    int k=playerNode->c->inventorySize;
    for (int i=0; i<k;  i++)
    {
        if (playerNode->c->inventory[i].itemCategory==3)
        {
            counter++;
        }
    }
    cout<<"counter is equal to: "<<counter<<endl;
    if(counter==3)
    {
            cout<<"You have all the hallows"<<endl;
            int j=0;
            Item* temp=new Item[k-3+1];
            for (int i=0; i<k; i++)
            {
                if(playerNode->c->inventory[i].itemCategory!=3)
                {
                    temp[j]= playerNode->c->inventory[i];
                    j++;
                }
            }
            //cout<<"temp made"<<endl;
            Item DS;
            DS.itemName="The Deathly Hallows";
            DS.itemCategory=1;
            DS.points=85;
            temp[k-2-1]=DS;
            playerNode->c->inventorySize= (playerNode->c->inventorySize)-2;
            playerNode->c->inventory=temp;
            cout<<"You have created the Deathly Hallows"<<endl;

        }

    else
    {
        cout<<"you do not have enough hallows"<<endl;
        return;
    }

}
