#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool found = false;

int** RotateLeft(int** spot){
    //turn 90* counter clockwise
    for (int i = 0; i < 8 / 2; i = i + 1)
    {
        for (int j = i; j < 8 - i - 1; j = j + 1)
        {
            int temp = spot[i][j];
            spot[i][j] = spot[j][8-1-i];
            spot[j][8-1-i] = spot[8-1-i][8-1-j];
            spot[8-1-i][8-1-j] = spot[8-1-j][i];
            spot[8-1-j][i] = temp;
        }
    }
    return spot;
}

int** RotateRight(int **spot){
    //turn 90* clockwise
    for (int i = 0; i < 8 / 2; i++) {
        for (int j = i; j < 8 - i - 1; j++) {
            int temp = spot[i][j];
            spot[i][j] = spot[8 - 1 - j][i];
            spot[8 - 1 - j][i] = spot[8 - 1 - i][8 - 1 - j];
            spot[8 - 1 - i][8 - 1 - j] = spot[j][8 - 1 - i];
            spot[j][8 - 1 - i] = temp;
        }
    }
    return spot;
}

int** placeQueen(int** spot, int row, int col){
    //make all illegal spots false
    int temp_row = row, temp_col = col;

    for(int i = 0; i < 5; ++i){ //horizontally
        if(i != col)
            spot[row][i] = 0;
    }

    for(int i = 0; i < 5; ++i){ //vertically
        if(i != row)
            spot[i][col] = 0;
    }

    for(int i = col; (col + 1 < 5 && row + 1 < 5); ++i){ //diagonally down
        spot[++row][++col] = 0;
    }

    row = temp_row;
    col = temp_col;

    for(int i = col; (col - 1 >= 0 && row - 1 >= 0); --i){ //diagonally up
        spot[--row][--col] = 0;
    }

    return spot;
}

void checkRow(int** spot, int row, int quarter){ //queen is set to true, check next line

    if(found)
        return;

    if(row > 4){
        found = true;

        //visur nuliai kur netas ketvirtis
         for(int i = 0; i < 8; ++i){
            for(int j = 0; j < 8; ++j){
                if(i > 4 || j > 4)
                    spot[i][j] = 0;
            }
        }

        switch(quarter){
        case 1:
            spot = RotateRight(spot);
            break;
        case 2:
            spot = RotateRight(spot);
            spot = RotateRight(spot);
            break;
        case 3:
            spot = RotateLeft(spot);
            break;
        }

        printf("Answer: \n");
        for(int i = 0; i < 8; ++i){
            for(int j = 0; j < 8; ++j){
                printf("%d ", spot[i][j]);
            }
            printf("\n");
        }
        return;
    }

    int arr_temp[5][5];
    int x = 0; //how many times a function has been called inside a function

    for(int j = 0; j < 5; ++j){
        for(int k = 0; k < 5; ++k){
            arr_temp[j][k] = spot[j][k];
        }
    }

    for(int i = 0; i < 5; ++i){

        if(found)
            return;

        if(x > 0){
            for(int j = 0; j < 5; ++j){
                for(int k = 0; k < 5; ++k){
                    spot[j][k] = arr_temp[j][k];
                }
            }
        }

        if(spot[row][i] == 1){ //try to place a queen on the board
            checkRow(placeQueen(spot, row, i), row + 1, quarter);

            ++x;

            for(int j = 0; j < 5; ++j){
                for(int k = 0; k < 5; ++k){
                    spot[j][k] = arr_temp[j][k];
                }
            }
        }
    }
    return;
}

int main()
{

    int row = 0;
    int start_row, start_col;
    int temp_row, temp_col;

    int* values = calloc(8 * 8, sizeof(int));
    int** availableSpots = malloc(8 * sizeof(int *));

    for (int i = 0; i < 8; ++i){
        availableSpots[i] = values + i * 8;
    }

    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
            availableSpots[i][j] = 1;
        }
    }

    //impossible to place a queen on the following:
    availableSpots[0][3] = 0;
    availableSpots[0][4] = 0;
    availableSpots[3][0] = 0;
    availableSpots[4][0] = 0;
    availableSpots[3][7] = 0;
    availableSpots[4][7] = 0;
    availableSpots[7][3] = 0;
    availableSpots[7][4] = 0;
    availableSpots[2][2] = 0;
    availableSpots[2][5] = 0;
    availableSpots[5][2] = 0;
    availableSpots[5][5] = 0;//??

    printf("Enter a position for the 1st queen (x, y): ");
    scanf("%d%d", &start_col, &start_row);

    if(availableSpots[start_row][start_col] == 0){
        printf("Neimanoma");
        return 0;
    }

    //4ketvirciai
    if(start_col > 3 && start_row <= 3){//top right

        temp_row = 7 - start_col;
        temp_col = start_row;
        availableSpots[4][1] = 0;

        availableSpots = placeQueen(availableSpots, temp_row, temp_col);
        checkRow(availableSpots, row, 1);

    } else if(start_row > 3 && start_col <= 3){//bottom left

        temp_col = 7 - start_row;
        temp_row = start_col;
        availableSpots[4][1] = 0;

        availableSpots = placeQueen(availableSpots, temp_row, temp_col);
        checkRow(availableSpots, row, 3);

    } else if(start_row > 3 && start_col > 3){//bottom right

        temp_col = 7 - start_col;
        temp_row = 7 - start_row;

        availableSpots[4][1] = 0;
        availableSpots = placeQueen(availableSpots, temp_row, temp_col);
        checkRow(availableSpots, row, 2);

    } else{//top left

        availableSpots[4][1] = 0;
        availableSpots = placeQueen(availableSpots, start_row, start_col);
        checkRow(availableSpots, row, 4);
    }

    free(availableSpots);
    free(values);

    return 0;
}
