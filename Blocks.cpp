#include<graphics.h>
#include<iostream>
using namespace std;

class TetrisPiece{
    public:
        int position[20][10];
        bool halt = false;
        int rotX;
        int rotY;
        int ID;
};

class StraightPiece: public TetrisPiece{
    public:
        StraightPiece(){
            construct();
        }
        void construct(){
            for(int i=0;i<20;i++){
                for (int j=0;j<10;j++){
                    if (j==5 && i<8 && i>3){
                        position[i][j]=9;
                    }else{
                        position[i][j]=0;
                    }
                }
            }
            rotX = 5;
            rotY = 5;
            ID=9;
    }

};

class LPiece: public TetrisPiece{
    public:
        LPiece(){
            construct();
        }
        void construct(){
            for(int i=0;i<20;i++){
                for (int j=0;j<10;j++){
                    if (j==5 && i<7 && i>3){
                        position[i][j]=14;
                    }else if(j==6 && i==4){
                        position[i][j]=14;
                    }else{
                        position[i][j]=0;
                    }
                }
            }
            rotX=5;
            rotY=4;
            ID=14;

        
    }

};

class LPieceRev: public TetrisPiece{
    public:
        LPieceRev(){
            construct();
        }
        void construct(){
            for(int i=0;i<20;i++){
                for (int j=0;j<10;j++){
                    if (j==5 && i<7 && i>3){
                        position[i][j]=1;
                    }else if(j==4 && i==4){
                        position[i][j]=1;
                    }else{
                        position[i][j]=0;
                    }
                }
            }
            rotX=5;
            rotY=4;
            ID=1;
        
    }

};

class TPiece: public TetrisPiece{
    public:
        TPiece(){
            construct();
        }
        void construct(){
            for(int i=0;i<20;i++){
                for (int j=0;j<10;j++){
                    if (i==5 && j<7 && j>3){
                        position[i][j]=5;
                    }else if(i==4 && j==5){
                        position[i][j]=5;
                    }else{
                        position[i][j]=0;
                    }
                }
            }
            rotX=5;
            rotY=5;
            ID=5;
        
    }

};

class NPiece: public TetrisPiece{
    public:
        NPiece(){
            construct();
        }
        void construct(){
            for(int i=0;i<20;i++){
                for (int j=0;j<10;j++){
                    if (i==4 && j<7 && j>4){
                        position[i][j]=4;
                    }else if(i==5 && j<6 && j>3){
                        position[i][j]=4;
                    }else{
                        position[i][j]=0;
                    }
                }
            }
            rotX=5;
            rotY=4;
            ID=4;
        
    }

};

class NPieceRev: public TetrisPiece{
    public:
        NPieceRev(){
            construct();
        }
        void construct(){
            for(int i=0;i<20;i++){
                for (int j=0;j<10;j++){
                    if (i==4 && j<6 && j>3){
                        position[i][j]=2;
                    }else if(i==5 && j<7 && j>4){
                        position[i][j]=2;
                    }else{
                        position[i][j]=0;
                    }
                }
            }
            rotX=5;
            rotY=4;
            ID=2;
        
    }

};

class Cube: public TetrisPiece{
    public:
        Cube(){
            construct();
        }
        void construct(){
            for(int i=0;i<20;i++){
                for (int j=0;j<10;j++){
                    if (i==4 && j<6 && j>3){
                        position[i][j]=11;
                    }else if(i==5 && j<6 && j>3){
                        position[i][j]=11;
                    }else{
                        position[i][j]=0;
                    }
                }
            }
            rotX=5;
            rotY=4;
            ID=11;
        
    }

};

class BlankPiece: public TetrisPiece{
    public:
        BlankPiece(){
            construct();
        }
        void construct(){
            for(int i=0;i<20;i++){
                for (int j=0;j<10;j++){
                    position[i][j]=0;
                }
            }
            rotX=0;
            rotY=0;
            ID=0;
        
    }

};