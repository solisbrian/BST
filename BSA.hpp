//Arren De manuel
//Brian Solis

#ifndef BSA_HPP
#define BSA_HPP

#include <vector>
using namespace std;

template<typename Data>

/** This class implements a binary search array */
class BSA {
    
    private:
        vector<Data> v;

        /** Helper method used to either find an element if it exists
         * or else find where it should be inserted.
         */
        virtual size_t binarySearch(const Data& item) const {
	    if(v.size() == 0){
            	return 0;
	    } 
            return binarySearch(item, 0,  v.size() - 1);
          
        }
	//Recursive helper method for binary search
	virtual size_t binarySearch(const Data& item, size_t i, size_t j) const{
		
		if(i == j){
			return i;
		}
		size_t mid = (i + j) /2;
		if(item < v[mid]){
			return binarySearch(item, i, mid);
		}
		else if(v[mid] < item){
			return binarySearch(item, mid + 1, j);
		}
		else{
			return mid;
		}
	}

    public:
        /** Return the position of item, otherwise v.cend() */
        virtual typename vector<Data>::const_iterator find(const Data& item) const {
            size_t index = binarySearch(item);
	    //If empty, return cent();
	    if(v.size() == 0){
		return v.cend();
	    }
	    if(v[index] < item || item < v[index]){
		return v.cend();
	    }
            else{
		typename vector<Data>::const_iterator itr = v.cbegin();
		for(; *itr < v[index]  ; ++itr){
		}
		return itr;
	    }
        }

        /** Insert item into sorted position */
        virtual bool insert(const Data& item) {
            typename vector<Data>::const_iterator itr_check = find(item);
	    if(itr_check != v.cend()){
		return false;
		
	    }
	    else{
		
	    	if(v.size() == 0){
			v.insert(v.begin(), item);
			return true;
		}
		else{

	            	size_t index = binarySearch(item);
			typename vector<Data>::iterator itr = v.begin();
			for(; *itr < v[index]  ; ++itr){
			}
			v.insert(itr, item);
			return true;
		}
	    }
            
        }

        typename vector<Data>::iterator begin() const {
            return v.begin();
        }

        typename vector<Data>::iterator end() const {
            return v.end();
        }
};

#endif
