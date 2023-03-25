#ifndef SUDOKU_H
#define SUDOKU_H

#include "Searchable.h"
#include "SudokuSquare.h"

#include <vector>
using std:: vector;

#include <set>
using std::set;

#include <cmath>

#include <iostream>
using std::cout;
using std::endl;

#include <ostream>
using std::ostream;


#include <string>
using std::string;
using std::to_string;

#include <iomanip>
using std::setw;

#include <algorithm>
using std::max;
// TODO: Your Sudoku class goes here:

class Sudoku : public Searchable{
private:
    vector<vector<SudokuSquareSet>> grid;
    int gridSize;

public:
    Sudoku(int gridSizeIn): gridSize(gridSizeIn)
    {
    SudokuSquareSet possibleValues;
    for (int i = 1; i <= gridSizeIn; i++){
        possibleValues.insert(i);
    }
    vector<SudokuSquareSet> row;
    for(int i=1; i <= gridSizeIn; i++){
        row.push_back(possibleValues);
    }

    for(int i=1; i <= gridSizeIn;i++){
        grid.push_back(row);
    }
    }
    Sudoku(const Sudoku& rhs){
        grid = rhs.grid;
        gridSize = rhs.gridSize;
    }

    int getSquare(int row, int col){
        SudokuSquareSet possibleValues = grid[row][col];
        if (possibleValues.size() == 1){
            return  *(possibleValues.begin());
        }
        return -1;

    }
    bool setSquare(int row, int col, int value){

        grid[row][col].clear();
        grid[row][col].insert(value);

        for (int currentRow = 0; currentRow < gridSize; currentRow++){
            for(int currentCol = 0; currentCol < gridSize; currentCol++){
                if(grid[currentRow][currentCol].size() != 2){
                    continue;
                }
                bool found = false;
                for(int nextCol = currentCol + 1; nextCol < gridSize; nextCol++){
                    if(grid[currentRow][currentCol] == grid[currentRow][nextCol]){
                        bool didErase =  false;
                        for(int column= 0; column < gridSize; column++){
                            if(column != currentCol && column != nextCol){
                                for(int possibleValue : grid[currentRow][currentCol]){
                                    didErase = didErase || grid[currentRow][column].erase(possibleValue);

                                }

                            }
                        }
                        if (didErase){                        
                            for(int column= 0; column < gridSize; column++){
                                if(grid[currentRow][column].size() == 0){
                                    return false;
                                }
                                else if(grid[currentRow][column].size() == 1){
                                    if(!setSquare(currentRow,column,getSquare(currentRow,column))){
                                        return false;
                                    }
                                }
                            }
                        }
                    }

                }

            }
        }
        for (int currentCol = 0; currentCol < gridSize; currentCol++){
            for(int currentRow = 0; currentRow < gridSize; currentRow++){
                if(grid[currentRow][currentCol].size() != 2){
                    continue;
                }
                bool found = false;
                for(int nextRow = currentRow + 1; nextRow < gridSize; nextRow++){
                    if(grid[currentRow][currentCol] == grid[nextRow][currentCol]){
                        bool didErase =  false;
                        for(int row = 0; row < gridSize; row++){
                            if(row != currentRow && row != nextRow){
                                for(int possibleValue : grid[currentRow][currentCol]){
                                    didErase = didErase || grid[row][currentCol].erase(possibleValue);

                                }

                            }
                        }
                        if(didErase){
                            for(int row= 0; row < gridSize; row++){
                                if(grid[row][currentCol].size() == 0){
                                    return false;
                                }
                                else if(grid[row][currentCol].size() == 1){
                                    if(!setSquare(row,currentCol,getSquare(row,currentCol))){
                                        return false;
                                    }
                                }
                            }
                        }
                        
                    }

                }

            }
        }

        int root = sqrt(gridSize);
        int columnStart = ((int) (col / root)) * root;
        int rowStart = ((int)(row / root)) * root;


        
        for (int currentRow = 0; currentRow < gridSize; currentRow++){   //get rid of value from row
            if(currentRow == row){
                    continue;
            }
            bool didErase = grid[currentRow][col].erase(value);
            if (didErase){            
                if(grid[currentRow][col].size() == 0){
                    return false;
                }
                else if(grid[currentRow][col].size() == 1){
                    if (!setSquare(currentRow,col,getSquare(currentRow,col))){
                        return false;
                    }

                }
            }
        }
        for (int currentCol = 0; currentCol < gridSize;currentCol++){  //get rid of value from column
            if(currentCol== col ){
                    continue;
            }
            bool didErase = grid[row][currentCol].erase(value);
            if(didErase){
                if(grid[row][currentCol].size() == 0){
                    return false;
                }
                else if(grid[row][currentCol].size() == 1){
                    if (!setSquare(row,currentCol,getSquare(row,currentCol))){
                        return false;
                    }
                }
            }
        }
        for(int currentRow = rowStart; currentRow < rowStart + root; currentRow++ ){  //get rid of that value from square 


            for(int currentColumn = columnStart; currentColumn < columnStart + root;currentColumn++){
                if(currentColumn == col || currentRow == row){
                    continue;
                }
                bool didErase = grid[currentRow][currentColumn].erase(value);
                if(didErase){
                    if(grid[currentRow][currentColumn].size() == 0){
                        return false;
                    }
                    else if(grid[currentRow][currentColumn].size() == 1){
                        if (!setSquare(currentRow, currentColumn, getSquare(currentRow,currentColumn))){
                            return false;
                        }
                    }
                }
            }
        }
        //printGrid();
        return true;
    }
    bool isSolution() const {
        for (vector<SudokuSquareSet> row : grid){
            for(SudokuSquareSet tile : row){
                if(tile.size() > 1){
                    return false;
                }
                
            }
        }
        return true;
    }

    vector<unique_ptr<Searchable>> successors() const {
        vector<unique_ptr<Searchable>> newBoards;
        int foundRow = -1;
        int foundColumn = -1;
        bool found = false;
        for(int row = 0; row < gridSize;row++){
            for (int column = 0; column < gridSize; column++ ){
                if (grid[row][column].size() > 1){
                    foundRow =  row;
                    foundColumn = column;
                    found =  true;
                    break;
                }
            }
            if(found){
                break;
            }
        }
        if (found){
            for(int possibleValue : grid[foundRow][foundColumn]){
                Sudoku* newSudoku =  new Sudoku(*this);
                if(newSudoku->setSquare(foundRow,foundColumn,possibleValue)){
                    //newSudoku->printGrid();
                    newBoards.push_back(unique_ptr<Searchable>(newSudoku));
                }

            }
            if(newBoards.size() == 1 && !(newBoards[0].get()->isSolution())){
                return newBoards[0].get()->successors();
                
            }
        }

        return newBoards;

    }

    void write(ostream & o) const {
        int maxPossibility =  1;
        for(vector<SudokuSquareSet> row : grid){
            for (SudokuSquareSet tile : row){
                maxPossibility =  max(maxPossibility, (int)tile.size());
            }
        }

        string dash(gridSize*(maxPossibility+3)+1,'-');
        o<<dash<<"\n";
        for (vector<SudokuSquareSet> row : grid){
            o<<"| ";
            for (SudokuSquareSet tile : row){
                string possiblevalues = "";
                for (int value : tile){
                    possiblevalues += to_string(value);
                }
                o<<setw(maxPossibility) << possiblevalues;
                o<<" | ";
            }
            string dash(gridSize*(maxPossibility+3)+1,'-');
            o<<"\n";
            o<<dash<<"\n";
        }
        o<<"\n";
        
    }

    int heuristicValue() const{
        int num = 0;
        for(vector<SudokuSquareSet> row : grid){
            for(SudokuSquareSet tile : row){
                if(tile.size() > 1){
                    num+=1;

                }
            }
        }
        return num;
    }
    
};




#endif
