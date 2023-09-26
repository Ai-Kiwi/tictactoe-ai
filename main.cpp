#include <iostream>
#include <vector>


int testIfWin(std::vector<int> placements) {

    //vertical rows
    for (int i = 0; i <= 2; i++) {
            if (placements[0+i] == 1 && placements[3+i] == 1 && placements[6+i] == 1){
        return 1;
        }
        if (placements[0+i] == 2 && placements[3+i] == 2 && placements[6+i] == 2){
            return 2;
        }
    }


    //horizontal rows
    for (int i = 0; i <= 2; i++) {
        if (placements[0+(i*3)] == 1 && placements[1+(i*3)] == 1 && placements[2+(i*3)] == 1){
            return 1;
        }
        if (placements[0+(i*3)] == 2 && placements[1+(i*3)] == 2 && placements[2+(i*3)] == 2){
            return 2;
        }
    }


    //top left to bottom right
    if (placements[0] == 1 && placements[4] == 1 && placements[8] == 1){
        return 1;
    }
    if (placements[0] == 2 && placements[4] == 2 && placements[8] == 2){
        return 2;
    }


    //top right to bottom left
    if (placements[2] == 1 && placements[4] == 1 && placements[6] == 1){
        return 1;
    }
    if (placements[2] == 2 && placements[4] == 2 && placements[6] == 2){
        return 2;
    }



    return 0;
}






std::vector<int> getWinsForMove(std::vector<int> placements, bool aiTurn) {
    int winsCount = 0;
    int tieCount = 0;
    int loseCount = 0;

    int winOrLoseValue = testIfWin(placements);
    if (winOrLoseValue == 1){
        return { 1 , 0 , 0 };
    }else if (winOrLoseValue == 2){
        return { 0 , 0 , 1 };
    }
    
    
    //loop over items
    bool madeMove = false;
    for (int i = 0; i <= 8; i++) {
        std::vector<int> newPlacements = placements;
        if (newPlacements[i] == 0){
            madeMove = true;

            if (aiTurn == true){
                newPlacements[i] = 1;
            }else{
                newPlacements[i] = 2;
            }   

            std::vector<int> moveWinLoseRatio = getWinsForMove(newPlacements, !aiTurn);

            winsCount += moveWinLoseRatio[0];
            tieCount += moveWinLoseRatio[1];
            loseCount += moveWinLoseRatio[2];
            
        }
    }
    if (madeMove == false){
        tieCount++;
    }
    
    
    
    return { winsCount , tieCount , loseCount };
}

int findBestMove(std::vector<int> placements) {
    int bestSpotValue = -1000000;
    int bestSpot = -1;
        
    //loop over items
    bool madeMove = false;
    for (int i = 0; i <= 8; i++) {
        std::vector<int> newPlacements = placements;
        if (newPlacements[i] == 0){
            newPlacements[i] = 1;

            std::vector<int> moveWinLoseRatio = getWinsForMove(newPlacements, false);
            int spotValue = 0;

            //  { winsCount , tieCount , loseCount }
            spotValue += (moveWinLoseRatio[0]*100) + (moveWinLoseRatio[1]*1) + (moveWinLoseRatio[2]*-100);
            if (spotValue > bestSpotValue){
                bestSpotValue = spotValue;
                bestSpot = i;
            }
            
        }
    }
    
    
    
    return bestSpot;
}

const char* displayItemPlacement(int placementValue){
    if (placementValue == 1){
        return "X";
    }else if (placementValue == 2){
        return "O";
    }else if (placementValue == 3){
        return "%";
    }else{
        return " ";
    }
}

void displayPlacement(std::vector<int> placements){
    std::cout  << "---------\n";
    std::cout << " |" << displayItemPlacement(placements[0]) << "|" << displayItemPlacement(placements[1]) << "|" << displayItemPlacement(placements[2]) << "| \n";
    std::cout  << "---------\n";
    std::cout << " |" << displayItemPlacement(placements[3]) << "|" << displayItemPlacement(placements[4]) << "|" << displayItemPlacement(placements[5]) << "| \n";
    std::cout  << "---------\n";
    std::cout << " |" << displayItemPlacement(placements[6]) << "|" << displayItemPlacement(placements[7]) << "|" << displayItemPlacement(placements[8]) << "| \n";
    std::cout  << "---------\n";
}

//ai plays as 1
//other user plays as 2

int main() {
    std::vector<int> values = {
        0, 0, 0, 
        0, 0, 0, 
        0, 0, 0
    };
    
    while (true) {
        int userPlacement;
        std::cout << "Type placement (0  means ai go frist) : "; // Type a number and press enter
        std::cin >> userPlacement;
        if (userPlacement != 0){
            userPlacement = userPlacement - 1; //removes starting at 0
            values[userPlacement] = 2;
            
        }

        int moveToMake = findBestMove(values);
        values [moveToMake] = 1;
        std::vector<int> displayMovementData = values;
        displayMovementData[moveToMake] = 3;
        displayPlacement(displayMovementData);

        //std::cout << moveToMake << " ";

    }

    

    return 0;
}
