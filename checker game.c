#include <stdio.h>
#include <stdlib.h>


int position(char move){
    switch (move)
    {
    case 'a':return 0;break;
    case 'b':return 1;break;
    case 'c':return 2;break;
    case 'd':return 3;break;
    case 'e':return 4;break;
    case 'f':return 5;break;
    case 'g':return 6;break;
    case 'h':return 7;break;
    }
}

// this 4 func eat an unit with checker (is iti eateble control and is target empty )
int isOnlyOneOppositeUnitRight(char table[8][8], int constant, int src, int dest, char e1, char e2, int *y){  //example e1 = w  e2 = W
     int i;
     int counter = 0;
     src++;    dest--;
    for(i=src;i<=dest;i++){
        if(table[constant][i] != ' '){
            if((table[constant][i] == e1) || (table[constant][i] == e2)){
                *y = i;
             counter++;
            }else{
                return 0;
            }
        }

    }
    if((counter == 1) || (counter == 0)){
        return 1;
    }else{
        return 0;
    }
    
}

int isOnlyOneOppositeUnitLeft(char table[8][8], int constant, int src, int dest, char e1, char e2, int *y ){
    int i;
    int counter = 0;
    src--;    dest++;
    for(i=src;i>=dest;i--){
        if(table[constant][i] != ' '){
            if((table[constant][i] == e1) || (table[constant][i] == e2)){
                *y = i;
             counter++;
            }else{
                return 0;
            }
        }

    }
    if((counter == 1) || (counter == 0)){
        return 1;
    }else{
        return 0;
    }
}

int isOnlyOneOppositeUnitUp(char table[8][8], int constant, int src, int dest, char e1, char e2, int *x ){
    int i;
    int counter = 0;
    src--;   dest++;
    for(i=src;i>=dest;i--){
        if(table[i][constant] != ' '){
            if((table[i][constant] == e1) || (table[i][constant] == e2)){
                *x = i;
             counter++;
            }else{
                return 0;
            }
        }

    }
    if((counter == 1) || (counter == 0)){
        return 1;
    }else{
        return 0;
    }
}

int isOnlyOneOppositeUnitDown(char table[8][8], int constant, int src, int dest, char e1, char e2, int *x ){
    int i;
    int counter = 0;
    src++;   dest--;
    for(i=src;i<=dest;i++){
        if(table[i][constant] != ' '){
            if((table[i][constant] == e1) || (table[i][constant] == e2)){
                *x = i;
             counter++;
            }else{
                return 0;
            }
        }

    }
    if((counter == 1) || (counter == 0)){
        return 1;
    }else{
        return 0;
    }
}

//this 4 func move control func for every unit
int checkerRightMoveController(char table[8][8], int constant, int src, int dest){
    int i;
    for(i=src+1;i<=dest;i++){
        if(table[constant][i] != ' '){
            return 0;
        }
    }
    return 1;
}


int checkerLefttMoveController(char table[8][8], int constant, int src, int dest){
    int i;
    for(i=src-1;i>=dest;i--){
        if(table[constant][i] != ' '){
            return 0;
        }
    }
    return 1;
}


int checkerUpMoveController(char table[8][8], int constant, int src, int dest){
    int i;
    for(i=src-1;i>=dest;i--){
        if(table[i][constant] != ' '){
            return 0;
        }
    }
    return 1;
}


int checkerDownMoveController(char table[8][8], int constant, int src, int dest){
    int i;
    for(i=src+1;i<=dest;i++){
        if(table[i][constant] != ' '){
            return 0;
        }
    }
    return 1;
}




int main()
{
  

 
 /*-----------------------------------variables----------------------------------------*/
     char table[8][8] = {   //default table for new game
        {' ', ' ', ' ', ' ', ' ', ' ', ' ',' '},
        {'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
        {'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ',' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ',' '},
        {'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b'},
        {'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ',' '},
    };

    char turn = 'W';

    char harf[8] = {'A', 'B', 'C','D','E','F','G','H'};
    int rakam[8] = { 8,7,6,5,4,3,2,1 };

    
    int i,j,k;
    int current = 1;
    int choice;
    int row;
    char move[4];
    int h1,h2; //horizontal 1 , horizontal 2    a,b,c,...,f
    int v1,v2; //vertical 1, vertical 2         1,2,3,...,8
    int turnController = 0;
    char ch,c1,c2;    // for fgetc
    int moveControl;    // our move legal or illegal 
    int extraMove; // taş yersek turumuzun devam etmesi için
    FILE *f;    //file for read and write
    FILE *fr;   //file for read
    FILE *mf;  // move file

    int eatenV,eatenH;

    int afterEat;   // this variable control -> if we eat an unit our next move should be eat another unit  -- 

    int x,y;
 /*-----------------------------------variables----------------------------------------*/
    int checkTrueInput = 1;
    while(checkTrueInput){
    printf("1-New Game\n2-Continue Game\n3-End Game\n");
    printf("Please select one: ");
    scanf("%d",&choice);
    if( choice != 1 && choice != 2 && choice != 3 ){
        printf("\nNot existing selection, please try again!\n");
    }else{
        checkTrueInput = 0;
    }
    }

    /*---------------------------menu and menu operations-----------------------------*/
     switch (choice)
    {
    case 1:     //new game
    mf = fopen("moveList.txt","w+");

    fclose(mf);
        
    f = fopen("table.txt", "w+");  //update file for new game
    for (i = 0; i < 8; i++)
    {
       
        for (j = 0; j < 8; j++)
        {

            if(table[i][j] == 'w'){
                fputc('w',f);
                fputc(' ',f);
            }else if(table[i][j] == 'b'){
                fputc('b',f);
                fputc(' ',f);
            }else{
                fputc(' ',f);
                fputc(' ',f);
            }

            if(j != 7){
                fputc('\t',f);
            }
            
        }
        fputc('\n',f);
    }
    fputc(turn,f);
    
    fclose(f);    

        break;
   
    case 2:     //continue game
    // 00 w0 b0 ww bb       0=' '
    fr=fopen("table.txt", "r");
    int row = 0;
    int column = 0;
        while(1)    //loop for reading from file and update our table matrix
    {
        c1 = fgetc(fr);
       if(feof(fr)) { 
         break ;
      }
      


      if(c1 == '\t'){
          continue;

      }else if(c1 == '\n'){
          continue;
      }else{
         
      c2 = fgetc(fr);
       if(feof(fr)) { 
         turn = c1;
         break ;
      }

        if(c1 == ' '){
            table[row][column] = ' ';
            column++;
            if(column == 8){
                column = 0;
                row++;
            }
        }else if(c1 == 'w'){
            if(c2 == 'w'){
                table[row][column] = 'W';
                column++;
                if(column == 8){
                    column = 0;
                    row++;
                }
            }else if(c2 == ' '){
                table[row][column] = 'w';
                column++;
                if(column == 8){
                    column = 0;
                    row++;
               
                }
            }

        }else if(c1 == 'b'){
            if(c2 == 'b'){
                table[row][column] = 'B';
                column++;
                if(column == 8){
                    column = 0;
                    row++;
                }
            }else if(c2 == ' '){
                table[row][column] = 'b';
                column++;
                if(column == 8){
                    column = 0;
                    row++;
                }
            }

            }
        }// end of else
    }   //end of while
    
    fclose(fr);
        break;
    
    case 3:     //end game
    current=0;  // close the loop
        break;
    }

    /*--------------------------------^^end of menu and menu operations^^-----------------------------------*/
 
    /*----------------------------update screen-----------------------------------*/        
    
    if(current != 0){
    for (i = 0; i < 8; i++) //update screen
    {
        printf("%d",rakam[i]);
        for (j = 0; j < 8; j++)
        {
            printf("\t");
            if(table[i][j] == 'w'){
                printf("w ");
            }else if(table[i][j] == 'W'){
                printf("ww");
            }else if(table[i][j] == 'b'){
                printf("b ");
            }else if(table[i][j] == 'B'){
                printf("bb");
            }else{
                printf("  ");
            }

        }
        printf("\n");
    }
    printf("%c",turn);

    for(i=0;i<8;i++){
        printf("\t%c",harf[i]);
    }
    }

 /*----------------------------^^end of update screen^^-----------------------------------*/



    afterEat = 0;

    while (current) // this loop is our game
    {
    
    int moveInputController = 1;                          
    while(moveInputController){
        int moveLoop = 1;
        while (moveLoop)
        {
            printf("\nMake your move! \t(exm:a2a3)(p for pass)(0 for exit)\n");
            scanf("%s",move);

            if(move[0]=='p'){  
             afterEat = 0;
             //update turn 
             if(turn == 'W'){   
                    turn = 'B'; 
                    printf("\n Black turn\n");
               }else if(turn == 'B'){
                 turn = 'W';
                      printf("\n White turn\n");
                 }



                        for (i = 0; i < 8; i++) //update screen WİTH  NEW TURN
                        {
                         printf("%d",rakam[i]);
                         for (j = 0; j < 8; j++)
                         {
                             printf("\t");
                             if(table[i][j] == 'w'){
                                 printf("w ");
                             }else if(table[i][j] == 'W'){
                                 printf("ww");
                             }else if(table[i][j] == 'b'){
                                 printf("b ");
                             }else if(table[i][j] == 'B'){
                                 printf("bb");
                             }else{
                                 printf("  ");
                             }

                          }
                          printf("\n");
                     }
                     printf("%c",turn);

                     for(i=0;i<8;i++){
                          printf("\t%c",harf[i]);
                     }
                
                }else{
                    break;
                }

                
                
        }
            
        
        
    

    

    if(move[0]=='0'){   // finish the game
    printf("\n See you later ! \n");
        current=0;
        moveInputController = 0;
        }

        

    if(moveInputController == 1){
       if(move[0]!='a' && move[0]!='b' && move[0]!='c' && move[0]!='d' && move[0]!='e' && move[0]!='f' && move[0]!='g' && move[0]!='h'){
           printf("\nWrong move input please try again!\n");
       }else if(move[2]!='a' && move[2]!='b' && move[2]!='c' && move[2]!='d' && move[2]!='e' && move[2]!='f' && move[2]!='g' && move[2]!='h'){
           printf("\nWrong move input please try again!\n");
       }else if(move[1]!='1' && move[1]!='2' && move[1]!='3' && move[1]!='4' && move[1]!='5' && move[1]!='6' && move[1]!='7' && move[1]!='8'){
           printf("\nWrong move input please try again!\n");
       }else if(move[3]!='1' && move[3]!='2' && move[3]!='3' && move[3]!='4' && move[3]!='5' && move[3]!='6' && move[3]!='7' && move[3]!='8'){
           printf("\nWrong move input please try again!\n");
       }else if( (move[0] != move[2]) && (move[1] != move[3]) ){
           printf("\nWrong move input please try again!\n");
       }
       else{
           moveInputController = 0;
       }
    }

    }

    if(move[0] != '0'){
        // horizontal  and vertical
    h1 = position(move[0]);
    h2 = position(move[2]);
    v1 = 7 - ((move[1] - '0') - 1);
    v2 = 7 - ((move[3] - '0') - 1);
    
   
   
   //true start move controllers
    if(turn == 'W'){
        if(table[v1][h1] == 'w' || table[v1][h1] =='W'){
            
            turnController = 1;
        }else{
            printf("WRONG MOVE, you should start with white\n");
            turnController = 0;
            
        }
    }else if(turn == 'B'){
        if(table[v1][h1] == 'b' || table[v1][h1] == 'B'){
            
            turnController = 1;
        }else{
            printf("WRONG MOVE, you should start with black\n");
            turnController = 0;
            
        }
    }

    char src = table[v1][h1];   //start point
    char dest = table[v2][h2];  //end point

 /*----------------------------move controler----------------------------------------------*/   
    
   
   extraMove = 0;
   
    switch (turn)
    {
    case 'W':

        switch (src)
        {
        case 'w':

            if(v1>v2){
                printf("You can not go back with w!!");
                //yanlış hamle
                turnController = 0;
                moveControl = 0;
            }else if( (table[v1+2][h1] == ' ') && (table[v1+1][h1] == 'b' || table[v1+1][h1] == 'B') && (v1+2 == v2) ){
                // doğru hamle dikey yeme
                turnController = 1;
                moveControl = 11;
            }else if( (table[v1+1][h1] == ' ') && (v1+1 == v2) ){
                //doğru hamle dikey 
                turnController = 1;
                moveControl = 1;
            }else if( (table[v1][h1+1] == ' ') && (h1+1 == h2) ){
                //doğru hamle yatay sola
                turnController = 1;
                moveControl = 1;
            }else if( (table[v1][h1-1] == ' ') && (h1-1 == h2) ){
                //doğru hamle yatay sağa
                turnController = 1;
                moveControl = 1;
            }else if( (table[v1][h1-2] == ' ') && (table[v1][h1-1] == 'b' || table[v1][h1-1] == 'B') && (h1-2 == h2) ){
                //doğru hamle yatay sola yeme
                turnController = 1;
                moveControl = 12;
            }else if( (table[v1][h1+2] == ' ') && (table[v1][h1+1] == 'b' || table[v1][h1+1] == 'B') && (h1+2 == h2) ){
                //doğru hamle yatay sağa yeme
                turnController = 1;
                moveControl = 13;
            }
            
            

            break;
        
        case 'W':

            if( (v1==v2) && (h1<h2) && (checkerRightMoveController(table,v1,h1,h2) == 1)  ){
                //sağa doğru hamle
                turnController = 1;
                moveControl = 2;
            }else if( (v1==v2) && (h1>h2) && (checkerLefttMoveController(table,v1,h1,h2) == 1) ){
                //sola doğru hamle
                turnController = 1;
                moveControl = 2;
            }else if((v1>v2) && (h1==h2) && (checkerUpMoveController(table,h1,v1,v2) == 1) ){
                //yukarı doğru hamle
                turnController = 1;
                moveControl = 2;
            }else if( (v1<v2) && (h1==h2) && (checkerDownMoveController(table,h1,v1,v2) == 1) ){
                //aşağı doğru hamle
                turnController = 1;
                moveControl = 2;
            }
            
            else if( (v1==v2) && (h1<h2) && (table[v2][h2] == ' ') && (isOnlyOneOppositeUnitRight(table,v1,h1,h2,'b','B',&y))  ){
                //sağa doğru yeme
                turnController = 1;
                moveControl = 21;
            }else if( (v1==v2) && (h1>h2) && (table[v2][h2] == ' ') && (isOnlyOneOppositeUnitLeft(table,v1,h1,h2,'b','B',&y)) ){
                //sola doğru yeme
                turnController = 1;
                moveControl = 22;
            }else if((v1>v2) && (h1==h2) && (table[v2][h2] == ' ') && (isOnlyOneOppositeUnitUp(table,h1,v1,v2,'b','B',&x)) ){
                //yukarı doğru yeme
                turnController = 1;
                moveControl = 23;
            }else if( (v1<v2) && (h1==h2) && (table[v2][h2] == ' ') &&  (isOnlyOneOppositeUnitDown(table,h1,v1,v2,'b','B',&x)) ){
                //aşağı doğru yeme
                turnController = 1;
                moveControl = 24;
            }


            break;

        default:
            moveControl = 0;
            break;    
        }

        break;
    
    case 'B':
        switch(src){
        case 'b':

            if(v1<v2){
                printf("You can not go back with b!!");
                //yanlış hamle
                turnController = 0;
                moveControl = 0;
            }else if( (table[v1-2][h1] == ' ') && (table[v1-1][h1] == 'w' || table[v1-1][h1] == 'W') && (v1-2 == v2) ){
                // doğru hamle dikey yeme
                turnController = 1;
                moveControl = 31;
            }else if( (table[v1-1][h1] == ' ') && (v1-1 == v2) ){
                //doğru hamle dikey 
                turnController = 1;
                moveControl = 3;
            }else if( (table[v1][h1-1] == ' ') && (h1-1 == h2) ){
                //doğru hamle yatay sola
                turnController = 1;
                moveControl = 3;
            }else if( (table[v1][h1+1] == ' ') && (h1+1 == h2) ){
                //doğru hamle yatay sağa
                turnController = 1;
                moveControl = 3;
            }else if( (table[v1][h1-2] == ' ') && (table[v1][h1-1] == 'w' || table[v1][h1-1] == 'W') && (h1-2 == h2) ){
                //doğru hamle yatay sola yeme
                turnController = 1;
                moveControl = 32;
            }else if( (table[v1][h1+2] == ' ') && (table[v1][h1+1] == 'w' || table[v1][h1+1] == 'W') && (h1+2 == h2) ){
                //doğru hamle yatay sağa yeme
                turnController = 1;
                moveControl = 33;
            }

            break;
        
        case 'B':

            if( (v1==v2) && (h1<h2) && (checkerRightMoveController(table,v1,h1,h2) == 1)  ){
                //sağa doğru hamle
                turnController = 1;
                moveControl = 4;
            }else if( (v1==v2) && (h1>h2) && (checkerLefttMoveController(table,v1,h1,h2) == 1) ){
                //sola doğru hamle
                turnController = 1;
                moveControl = 4;
            }else if((v1>v2) && (h1==h2) && (checkerUpMoveController(table,h1,v1,v2) == 1) ){
                //yukarı doğru hamle
                turnController = 1;
                moveControl = 4;
            }else if( (v1<v2) && (h1==h2) && (checkerDownMoveController(table,h1,v1,v2) == 1) ){
                //aşağı doğru hamle
                turnController = 1;
                moveControl = 4;
            }
            
            else if( (v1==v2) && (h1<h2) && (table[v2][h2] == ' ') && (isOnlyOneOppositeUnitRight(table,v1,h1,h2,'w','W',&y))  ){
                //sağa doğru yeme
                turnController = 1;
                moveControl = 41;
            }else if( (v1==v2) && (h1>h2) && (table[v2][h2] == ' ') && (isOnlyOneOppositeUnitLeft(table,v1,h1,h2,'w','W',&y))  ){
                //sola doğru yeme
                turnController = 1;
                moveControl = 42;
            }else if((v1>v2) && (h1==h2) && (table[v2][h2] == ' ') && (isOnlyOneOppositeUnitUp(table,h1,v1,v2,'w','W',&x))  ){
                //yukarı doğru yeme
                turnController = 1;
                moveControl = 43;
            }else if( (v1<v2) && (h1==h2) && (table[v2][h2] == ' ') && (isOnlyOneOppositeUnitDown(table,h1,v1,v2,'w','W',&x))  ){
                //aşağı doğru yeme
                turnController = 1;
                moveControl = 44;
            }


            break; 

        default:
            moveControl = 0;
            break;    
        }

        break;
    }

 /*----------------------------^^end of move controler^^-----------------------------------*/   

 /*----------------------------make move----------------------------------------*/ 
 
  if((moveControl == 1) ){
      if(afterEat == 0){
        table[v1][h1] = ' ';
         if(v2 == 7){
              table[v2][h2] = 'W';
         }else{
              table[v2][h2] = 'w';
         }
      }else if(afterEat == 1){
          printf("\nYou should eat an unit or pass!\n");
          extraMove = 1;
      }
      
  }else if (moveControl == 11){
      table[v1][h1] = ' ';
      table[v1+1][h1] = ' ';
      eatenV = v1+1;
      eatenH = h1;
      extraMove = 1;
      afterEat = 1;
      if(v2 == 7){
          table[v2][h2] = 'W';
      }else{
          table[v2][h2] = 'w';
      }
  }else if (moveControl == 12){
      table[v1][h1] = ' ';
      table[v1][h1-1] = ' ';
      eatenV = v1;
      eatenH = h1-1;
      extraMove= 1;
      afterEat = 1;
      table[v2][h2] = 'w';
      
      }else if (moveControl == 13){
      table[v1][h1] = ' ';
      table[v1][h1+1] = ' ';
      eatenV = v1;
      eatenH = h1+1;
      extraMove = 1;
      afterEat = 1;
      table[v2][h2] = 'w';
    
      }
      



      else if((moveControl == 2) ){
          if(afterEat == 0){
              table[v1][h1] = ' ';
               table[v2][h2] = 'W';
          }else if(afterEat == 1){
              printf("\nYou should eat an unit or pass!\n");
              extraMove = 1;
          }
    }else if(moveControl == 21){
        table[v1][h1] = ' ';
        table[v2][y] = ' ';//h2-1
        table[v2][h2] = 'W';
        eatenV = v2;
        eatenH = y;
        extraMove = 1;
        afterEat = 1;
    }else if(moveControl == 22){
        table[v1][h1] = ' ';
        table[v2][y] = ' ';  //h2+1
        eatenV = v2;
        eatenH = y;
        table[v2][h2] = 'W';
        extraMove = 1;
        afterEat = 1;
    }else if(moveControl == 23){
        table[v1][h1] = ' ';
        table[x][h2] = ' ';  //v2+1
        eatenV = x;
      eatenH = h2;
        table[v2][h2] = 'W';
        extraMove = 1;
        afterEat = 1;
    }else if(moveControl == 24){
        table[v1][h1] = ' ';
        table[x][h2] = ' ';  //v2-1
        eatenV = x;
      eatenH = h2;
        table[v2][h2] = 'W';
        extraMove = 1;
        afterEat = 1;
    }



  
  else if((moveControl == 3) ){

      if(afterEat == 0){
          table[v1][h1] = ' ';
      if(v2 == 0){
          table[v2][h2] = 'B';
      }else{
          table[v2][h2] = 'b';
      }
      }else if(afterEat == 1){
          printf("\nYou should eat an unit or pass!\n");
          extraMove = 1;
      }
      
  }else if(moveControl == 31){
      table[v1][h1] = ' ';
      table[v1-1][h1] = ' ';
      eatenV = v1-1;
      eatenH = h1;
      extraMove = 1;
      afterEat = 1;
      if(v2 == 0){
          table[v2][h2] = 'B';
      }else{
          table[v2][h2] = 'b';
      }
  }else if(moveControl == 32){
      table[v1][h1] = ' ';
      table[v1][h1-1] = ' ';
      eatenV = v1;
      eatenH = h1-1;
      extraMove = 1;
      afterEat = 1;
      table[v2][h2] = 'b';
      
  }else if(moveControl == 33){
      table[v1][h1] = ' ';
      table[v1][h1+1] = ' ';
      eatenV = v1;
      eatenH = h1+1;
      extraMove = 1;
      afterEat = 1;
      table[v2][h2] = 'b';
      
  }

  else if((moveControl == 4) ){
      if(afterEat == 0){
          table[v1][h1] = ' ';
      table[v2][h2] = 'B';
      }else if(afterEat == 1){
          printf("\nYou should eat an unit or pass!\n");
          extraMove = 1;
      }
    }else if(moveControl == 41){
        table[v1][h1] = ' ';
        table[v2][y] = ' ';//h2-1
        eatenV = v2;
        eatenH = y;
        table[v2][h2] = 'B';
        extraMove = 1;
        afterEat = 1;
    }else if(moveControl == 42){
        table[v1][h1] = ' ';
        table[v2][y] = ' ';//h2+1
        eatenV = v2;
        eatenH = y;
        table[v2][h2] = 'B';
        extraMove = 1;
        afterEat = 1;
    }else if(moveControl == 43){
        table[v1][h1] = ' ';
        table[x][h2] = ' ';//v2+1
        eatenV = x;
        eatenH = h2;
        table[v2][h2] = 'B';
        extraMove = 1;
        afterEat = 1;
    }else if(moveControl == 44){
        table[v1][h1] = ' ';
        table[x][h2] = ' ';//v2-1
        eatenV = x;
        eatenH = h2;
        table[v2][h2] = 'B';
        extraMove = 1;
        afterEat = 1;
    }
  



  
  else if(moveControl == 0){
      printf("Wrong move, please make your move again!!\n");
      extraMove = 1;
  }
  /*----------------------------^^make move^^-----------------------------------*/ 



        

       
   /*----------------------------update file and screen-----------------------------------*/ 

    if(turnController == 1){

    mf = fopen("moveList.txt","a");    // save move list 
    
    fputc(turn,mf);
    fputc(':',mf);
    fputc(move[0],mf);
    fputc(move[1],mf);
    fputc(move[2],mf);
    fputc(move[3],mf);
    fputc('\n',mf);

    fclose(mf);    

    }
    

    

     


    if(move[0] == '0' || extraMove == 0){
        if(turnController){ //update turn after move
        if(turn == 'W'){   
            turn = 'B'; 
        }else if(turn == 'B'){
            turn = 'W';
            }
        }
    }


    if(turnController == 1){
    f = fopen("table.txt","r+");
    int newLine = 1;
    char temp;
    int instantRow = 0;
    int targetRow = v2;
    if(targetRow != 0){
        while(newLine){    // find true row
            temp = fgetc(f);
            
         if(temp == '\n'){
               instantRow++;
               if(instantRow == targetRow){
                   newLine = 0;
               }

            }
      }
    }
     

    long updatePosition = (h2)*3;

    fseek(f,updatePosition,SEEK_CUR);

    if(table[v2][h2] == 'w'){
                fputc('w',f);
                fputc(' ',f);
            }else if(table[v2][h2] == 'W'){
                fputc('w',f);   
                fputc('w',f);
            }else if(table[v2][h2] == 'b'){
                fputc('b',f);
                fputc(' ',f);
            }else if(table[v2][h2] == 'B'){
                fputc('b',f);
                fputc('b',f);
            }

    fclose(f);

    FILE *fd;
    fd= fopen("table.txt","r+");        //delete starting position
    
    int deleteRow = v1;
    instantRow = 0;
    long deletePosition = (h1)*3;
    int deleteLoop = 1;
    if(deleteRow != 0){
        while(deleteLoop){    // find true column for deleting
            temp = fgetc(fd);

            if(temp == '\n'){
               instantRow++;

                     if(instantRow == deleteRow){  
                        break;
                    }
            }
      }
    }
    
      fseek(fd,deletePosition,SEEK_CUR);        
             fputc(' ',fd);
             fputc(' ',fd);
    fclose(fd);


    if(extraMove == 1){

         fd= fopen("table.txt","r+");    // delete eaten unit
    
    deleteRow = eatenV;
    instantRow = 0;
     deletePosition = (eatenH)*3;
     deleteLoop = 1;
     if(instantRow != 0){
         while(deleteLoop){    // find true column for deleting
            temp = fgetc(fd);

            if(temp == '\n'){
               instantRow++;

                     if(instantRow == deleteRow){  
                        break;
                    }
            }
      }
     }
    
      fseek(fd,deletePosition,SEEK_CUR);        
             fputc(' ',fd);
             fputc(' ',fd);
    fclose(fd);

    }

   
    }

    



    for (i = 0; i < 8; i++) //update screen after move
    {
        printf("%d",rakam[i]);
        for (j = 0; j < 8; j++)
        {
            printf("\t");
            if(table[i][j] == 'w'){
                printf("w ");
            }else if(table[i][j] == 'W'){
                printf("ww");
            }else if(table[i][j] == 'b'){
                printf("b ");
            }else if(table[i][j] == 'B'){
                printf("bb");
            }else{
                printf("  ");
            }

        }
        printf("\n");
    }
    printf("%c",turn);

    for(i=0;i<8;i++){
        printf("\t%c",harf[i]);
    }

 /*------------------------------^^end of update file and screen^^---------------------------------*/

                // WİNNER CONTROL

    int wCounter = 0;
    int bCounter = 0;
    for(i = 0;i < 8;i++){
        for(j = 0;j < 8; j++){
            if( (table[i][j] == 'w') || (table[i][j] == 'W') ){
                wCounter++;
            }else if( (table[i][j] == 'b') || (table[i][j] == 'B') ){
                bCounter++;
            }
        }
    }

    if(wCounter == 0){
        printf("Black win!!");
        current = 0;

    }else if(bCounter == 0){
        printf("White win!!");
        current = 0;
        
    }else if( ( (bCounter == 1) && (wCounter == 2) ) || ( (bCounter == 2) && (wCounter == 1) ) ){
        printf("DRAW !!");
        current = 0;
    }

    }
    
    
       
    }   //end of while


    
    


    
}