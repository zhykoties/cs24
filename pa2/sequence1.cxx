// sequence1.cxx - implements sequence class as defined in sequence1.h
// Yunkai Zhang, 4/28/2017

#include <cassert>
#include "sequence1.h"

using namespace std;
namespace main_savitch_3
{
    sequence::sequence(){
        used = 0;
        current_index = -1;
        data[CAPACITY];
    }

    void sequence::start(){
        if(size() == 0){
            current_index = -1;
        }else{
            current_index = 0;
        }
    }

    void sequence::advance(){
        assert(is_item());
        if(current_index >= used-1){
	    current_index = -1;
        }else{
            current_index++;
        }
    }

    void sequence::insert(const value_type& entry){
        assert(size() < CAPACITY);
	if(current_index == -1){
	  current_index = 0;
	}
	for(size_type i = used; i > current_index; i--){
	  data[i] = data[i-1];
	}
	data[current_index] = entry;
	used++;
    }

    void sequence::attach(const value_type &entry){
        assert(size() < CAPACITY);
        if(current_index == -1){
            data[used] = entry;
            used++;
            current_index = used-1;
        }else{
            for(int i = used-1; i > current_index; i--){
                data[i+1] = data[i];
            }
            data[current_index+1] = entry;
            used++;
	    current_index++;
        }
    }

    void sequence::remove_current(){
        assert(is_item());
        for(int i = current_index; i < used-1; i++){
            data[i] = data[i+1];
        }
        used--;
	if(current_index == used){
	  current_index = -1;
	}
    }

    sequence::size_type sequence::size() const{
        return used;
    }

    bool sequence::is_item() const{
        return (current_index != -1);
    }

    sequence::value_type sequence::current() const{
        assert(is_item());
        return data[current_index];
    }
}
