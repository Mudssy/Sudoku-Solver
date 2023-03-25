#ifndef SUDOKUSQUARE_H
#define SUDOKUSQUARE_H



class SudokuSquareSet {

    
private:
    unsigned int value;
    unsigned int length;

    class SudokuSquareSetIterator{
    private:
        unsigned int currentValue;
        unsigned int ander;
        const SudokuSquareSet& s;
    public:
        SudokuSquareSetIterator(unsigned int currentValueIn, const SudokuSquareSet& sIn): s(sIn), currentValue(currentValueIn) {
            ander = 1 << currentValue-1;

        }
        int operator*(){
            return currentValue;
        }
        void operator++(){
            ander = ander << 1;
            currentValue += 1;
            
            while (!(s.value & ander) && ander <= s.value){
                ander = ander<<1;
                currentValue +=1;
            }



        }

        bool operator==(const SudokuSquareSetIterator& rhs){
            return(currentValue == rhs.currentValue && s == rhs.s);

        }
        bool operator!=(const SudokuSquareSetIterator& rhs){
            return (currentValue != rhs.currentValue|| s != rhs.s);
        }

        


    };
public:
    SudokuSquareSet(){
        length = 0;
        value = 0;
    }

    int size() const{
        return length;
    }
    bool empty(){
        return length == 0;
    }
    void clear(){
        value = 0;
        length = 0;
    }

    bool operator==(const SudokuSquareSet& rhs) const{
        return value == rhs.value;

    }
    bool operator!=(const SudokuSquareSet& rhs) const{
        return value != rhs.value;
    }

    SudokuSquareSetIterator begin() const{
        if (value == 0){
            return SudokuSquareSetIterator(0,*this);
        }
        unsigned int ander =  1;
        unsigned int firstValue = 1;
        while (!(value & ander)){
            ander = ander << 1;
            firstValue += 1;
        } 
        return SudokuSquareSetIterator(firstValue,*this);
    }
    SudokuSquareSetIterator end() const{
        if(value == 0){
            return SudokuSquareSetIterator(0,*this);
        }
        unsigned int ander = 1<<length;
        unsigned int lastValue = length;
        while (ander <= value){
            ander = ander << 1;
            lastValue += 1;
        }
        return SudokuSquareSetIterator(lastValue+1,*this);
    }

    SudokuSquareSetIterator find(unsigned int valueIn){
        unsigned int ander = 1 << valueIn - 1 ;
        if (value & ander){
            return SudokuSquareSetIterator(valueIn, *this );
        }
        else{
            return end();
        }
    }

    SudokuSquareSetIterator insert(unsigned int valueIn){
        
        
        unsigned int ander = 1 << valueIn -1;
        if(!(value & ander)){
            value |= ander;
            length += 1;
        }
        return SudokuSquareSetIterator(valueIn, *this);;

    }

    bool erase(unsigned int valueIn){
        unsigned int ander =  1<< valueIn -1;
        if(value & ander){
            value &= ~ander;
            length -= 1;
            return true;
        }
        return false;
    }
    bool erase(SudokuSquareSetIterator valueToDelete){
        return erase(*valueToDelete);
    }






};


#endif
