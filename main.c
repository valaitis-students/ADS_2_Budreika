#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool found = false, mir_X = false, mir_Y = false;

int** Mirror_Y(int** spot){
    for (int i = 0; i < 8; ++i){
        for (int j = 4; j < 8; ++j){
            int temp = spot[i][7 - j];
            spot[i][7 - j] = spot[i][j];
            spot[i][j] = temp;
        }
    }
    return spot;
}

int** Mirror_X(int **spot){
    for (int i = 4; i < 8; ++i){
        for (int j = 0; j < 8; ++j){
            int temp = spot[7 - i][j];
            spot[7 - i][j] = spot[i][j];
            spot[i][j] = temp;
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

void checkRow(int** spot, int row){ //queen is set to true, check next line

    if(found)
        return;

    if(row > 4){
        found = true;

        if(mir_X){
            spot = Mirror_X(spot);
        }

        if(mir_Y){
            spot = Mirror_Y(spot);
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
            checkRow(placeQueen(spot, row, i), row + 1);

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

    //init
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
            if(i > 4 || j > 4)
                availableSpots[i][j] = 0;
            else
                availableSpots[i][j] = 1;
        }
    }

    //impossible to place a queen on the following:
    availableSpots[0][3] = 0;
    availableSpots[3][0] = 0;
    availableSpots[2][2] = 0;

    printf("Enter a position for the 1st queen (x, y): ");
    scanf("%d%d", &start_col, &start_row);

    if(start_col > 3){
        start_col = 7 - start_col;
        mir_Y = true;
    }

    if(start_row > 3){
        start_row = 7 - start_row;
        mir_X = true;
    }

    if(availableSpots[start_row][start_col] == 0){
        printf("Neimanoma");
        return 0;
    }

    availableSpots = placeQueen(availableSpots, start_row, start_col);
    checkRow(availableSpots, row);

    free(availableSpots);
    free(values);

    return 0;
}
