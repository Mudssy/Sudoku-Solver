#ifndef BEST_FIRST_SEARCH_H
#define BEST_FIRST_SEARCH_H

#include "Searchable.h"

#include <memory>
using std::unique_ptr;

#include <queue>
using std::priority_queue;

struct compareLessThan{
    bool operator()(const unique_ptr<Searchable>& lhs, const unique_ptr<Searchable>& rhs) const {
        return lhs.get()->heuristicValue() > rhs.get()->heuristicValue();
    }
};

class BestFirstSearch {

protected:

          
    int nodes = 0;
    priority_queue<unique_ptr<Searchable>,vector<unique_ptr<Searchable>>,compareLessThan> Q;
    
    
public:

    BestFirstSearch(std::unique_ptr<Searchable> && startFrom) {
        // TODO Put startFrom onto the queue:
        Q.push(std::move(startFrom));
    }
    
    int getNodesExpanded() const {
        return nodes;
    }
    
    Searchable * solve() {
            
        // TODO Implement search, returning a pointer to the solution (if one is found)
        while(!Q.empty()){
            if(Q.top()->isSolution()){
                return Q.top().get();
            }
        
            ++nodes;
            vector<unique_ptr<Searchable>> successors = Q.top().get()->successors();
            Q.pop();


            for (auto & successor : successors) {
                // and push each one onto the back of queue.
                Q.push(std::move(successor));
            }
        }
        return nullptr;
    }
};



#endif
