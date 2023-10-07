#include<graphics.h>
#include<iostream>
#include<random>
#include<time.h>
#include <stdio.h>
#include <stdlib.h>
#include "Behaviours.cpp"

using namespace std;

void UpdateGraph(int matrix[20][10]){
    for (int i=0;i<20;i++){
        for (int j=0;j<10;j++){
            if (matrix[i][j]!=0){
                setfillstyle(1,matrix[i][j]);
                rectangle(200+j*20,80+i*20,200+j*20+20,80+i*20+20);
                floodfill(201+j*20,81+i*20,15);
            }
        }
    }
}

void UpdateMatrix(int matrix[20][10],int pos[20][10]){
    int B[20][10];
    for (int i=0; i<20; i++){
        for (int j=0; j<10; j++){
            B[i][j]=matrix[i][j];
        }
    }

    for (int i=0;i<20;i++){
        for(int j=0;j<10;j++){
            if (pos[i][j]!=0) B[i][j]=pos[i][j];
        }
    }

    memcpy(matrix,B,sizeof(B));
}

void Refresh(int master[20][10],int pos[20][10],TetrisPiece* x, int score){
    cleardevice();
    setfillstyle(1,15);
    bar(190,100,200,500);
    bar(400,100,410,500);
    bar(200,479,400,480);
    rectangle(480,50,580,150);
    setfillstyle(1,15);

    for (int i=0;i<10;i++){
        bar(220+20*i,100,221+20*i,500);
        if (i<4) bar(500+i*20,50,501+i*20,150);
    }
    for (int i=0;i<20;i++){
        bar(200,100+20*i,400,101+20*i);
        if (i<4) bar(480,70+20*i,580,71+20*i);
    }
    char buffer[100];
    itoa(score,buffer,10);
    outtextxy(500,350,"Score");
    outtextxy(515,400,buffer);
    UpdateGraph(master);
    UpdateGraph(pos);
    UpdateHold(x);
}

void SnapDown(int matrix[20][10],TetrisPiece* p,TetrisPiece* x,int score){
    while(true){
        if (movePieces(p,matrix)){
            Refresh(matrix,p->position,x,score);
            break;
        }
    }
}

int score(int matrix[20][10],int scoreCount){
    int B[20][10];
    int count = 0;
    int lowestPoint=0;
    for (int i=0;i<20;i++){
        bool row = true;
        for (int j=0;j<10;j++){
            if (matrix[i][j]==0){
                row = false;
            }
            B[i][j]=matrix[i][j];
        }
        if (row){
            count+=1;
            lowestPoint = i;
        }
    }
    if (count>0){
        switch(count){
            case 1: scoreCount+=200;
            case 2: scoreCount+=500;
            case 3: scoreCount+=1000;
            case 4: scoreCount+=2000;
        }
        for(lowestPoint;lowestPoint>0;lowestPoint--){
            for (int j=0;j<10;j++){
                B[lowestPoint][j]=matrix[lowestPoint-count][j];
                if((lowestPoint-count)<0){
                    B[lowestPoint][j]=0;
                }
            }
        }
    }
    memcpy(matrix,B,sizeof(B));
    return scoreCount;
}


int main(int argc,char *argv[]){
    int gd = DETECT, gm;
    static int masterArray[20][10];
    initgraph(&gd,&gm,"");
    int scoreCount = 0;
    TetrisPiece* Mem = new BlankPiece();
    TetrisPiece* p = RandomPiece();
    int i=1000;
    while (i>0){
        scoreCount=score(masterArray,scoreCount);
        Refresh(masterArray,p->position,Mem,scoreCount);
        bool shiftstate = false;
        bool rotState = false;
        bool right = false;
        for (int j=0;j<10;j++){
            if (GetKeyState(VK_RIGHT) & 0x8000){
                right = true;
                Shift(p,right,masterArray);
                Refresh(masterArray,p->position,Mem,scoreCount);
                right=false;
            }else if (GetKeyState(VK_LEFT) & 0x8000){
                Shift(p,right,masterArray);
                Refresh(masterArray,p->position,Mem,scoreCount);
            }else if (GetKeyState(VK_SPACE) & 0x8000){
                SnapDown(masterArray,p,Mem,scoreCount);
                Sleep(100);
                p->halt = true;
                break;
            }else if (GetKeyState(VK_UP) & 0x8000){
                rotate(p);
                Refresh(masterArray,p->position,Mem,scoreCount);
            }else if (GetKeyState(0x43) & 0x8000){
                int ID = Mem->ID;
                Mem = holdPiece(p->ID);
                p = holdPiece(ID);
            }
            Sleep(100-scoreCount/1000);
        }
        if (!p->halt){
            p->halt = movePieces(p,masterArray);
        }else{
            bool end = false;
            for (int j=0;j<10;j++){
                if (p->position[7][j]!=0){
                    end = true;
                }
            }
            if (end) break;
            UpdateMatrix(masterArray,p->position);
            p = RandomPiece();
        }
        i--;
    }
    getch();
    return 0;
}