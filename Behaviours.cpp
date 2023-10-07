#include<graphics.h>
#include<iostream>
#include "Blocks.cpp"
using namespace std;

TetrisPiece* RandomPiece(){
    srand((unsigned) time(NULL));
    switch (rand()%7){
        case 0: return new StraightPiece;
        case 1: return new LPiece;
        case 2: return new LPieceRev;
        case 3: return new TPiece;
        case 4: return new NPiece;
        case 5: return new NPieceRev;
        case 6: return new Cube;
    }
    return RandomPiece();
}

void Shift(TetrisPiece* p,bool right,int matrix[20][10]){
    for (int i=0; i<20; i++){
        for (int j=0; j<10; j++){
            if(p->position[i][j]!=0){
                if (j==0 && !right || matrix[i][j-1]!=0 && !right){
                    return;
                }else if (j==9 & right || matrix[i][j+1]!=0 && right){
                    return;
                }
            }
        }
    }

    int B[20][10];
    for (int i=0; i<20; i++){
        for (int j=0; j<10; j++){
            B[i][j]=p->position[i][j];
        }
    }

    for (int i=0; i<20; i++){
        for (int j=0; j<10; j++){
            if (p->position[i][j]!=0){
                if (!right){
                    B[i][j]=p->position[i][j+1];
                    B[i][j-1]=p->position[i][j];
                }else{
                    B[i][j]=p->position[i][j-1];
                    B[i][j+1]=p->position[i][j];
                }
            }
        }
    }
    if (right){
        p->rotX+=1;
    }else{
        p->rotX-=1;
    }
    memcpy(p->position,B,sizeof(B));
}

void RotationCalibrate(TetrisPiece* p,bool right){
    int B[20][10];
    for (int i=0; i<20; i++){
        for (int j=0; j<10; j++){
            B[i][j]=p->position[i][j];
        }
    }

    for (int i=0; i<20; i++){
        for (int j=0; j<10; j++){
            if (p->position[i][j]!=0){
                if (!right){
                    B[i][j]=p->position[i][j+1];
                    B[i][j-1]=p->position[i][j];
                }else{
                    B[i][j]=p->position[i][j-1];
                    B[i][j+1]=p->position[i][j];
                }
            }
        }
    }
    if (right){
        p->rotX+=1;
    }else{
        p->rotX-=1;
    }
    memcpy(p->position,B,sizeof(B));
}

bool movePieces(TetrisPiece* p,int matrix[20][10]){
    int B[20][10];
    for (int i=0; i<20; i++){
        for (int j=0; j<10; j++){
            B[i][j]=p->position[i][j];
        }
    }

    for (int i=0;i<20;i++){
        for (int j=0;j<10;j++){
            if (p->position[i][j]!=0){
                if (i==19) return true;
                if (matrix[i+1][j]!=0) return true;
                int temp = B[i][j];
                B[i][j]=p->position[i-1][j];
                B[i+1][j]=p->position[i][j];
            }
        }
    }
    p->rotY+=1;
    memcpy(p->position,B,sizeof(B));
    return false;
}

void rotate(TetrisPiece* p){
    if (p->ID==11) return;
    int count = 0;
    int right = false;
    TetrisPiece* B = new BlankPiece();

    for (int i=0; i<20; i++){
        for (int j=0; j<10; j++){
            if(p->position[i][j]!=0){
                int y = p->rotY+(j-p->rotX);
                int x = p->rotX-(i-p->rotY);
                if (x>9){
                    count+=1;
                }else if (x<0){
                    count+=1;
                    right=true;
                }
            }
        }
    }

    for (int i=0;i<count;i++){
        RotationCalibrate(p,right);
    }

    for (int i=0; i<20; i++){
        for (int j=0; j<10; j++){
            if(p->position[i][j]!=0){
                B->position[p->rotY+(j-p->rotX)][p->rotX-(i-p->rotY)]=p->position[i][j];
            }
        }
    }
    memcpy(p->position,B->position,sizeof(B->position));
}

TetrisPiece* holdPiece(int ID){
    switch(ID){
        case 9: return new StraightPiece();
        case 14: return new LPiece();
        case 5: return new TPiece();
        case 4: return new NPiece();
        case 1: return new LPieceRev();
        case 2: return new NPieceRev();
        case 11: return new Cube();
    }
    return RandomPiece();
}

void UpdateHold(TetrisPiece* x){
    for (int i=0;i<20;i++){
        for (int j=0;j<10;j++){
            if (x->position[i][j]!=0){
                setfillstyle(1,x->position[i][j]);
                rectangle(420+j*20,30+i*20,420+j*20+20,30+i*20+20);
                floodfill(421+j*20,31+i*20,15);
            }
        }
    }
}