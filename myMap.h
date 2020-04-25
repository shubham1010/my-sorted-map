#include <cstdlib>
#include <iostream>

template <typename t1, typename t2>
class myMap {
private:
	t1 *keys;
	t2 *values;
	const static int multiplier=2;
	unsigned int index;
	unsigned long long int totCapacity;
	void sort();
public:
	myMap();
	~myMap();
	
	void insert(const t1 key, const t2 value);
	void erase(const t1 key);
	void show();

	enum exception { MEMFAIL };
};


template <typename t1, typename t2>
myMap<t1,t2> :: myMap() {
	index=0;
	totCapacity=1;
	keys = (t1 *)malloc(sizeof(t1)*totCapacity);
	values = (t2 *)malloc(sizeof(t2)*totCapacity);

	if(keys==NULL || values==NULL)
		throw MEMFAIL;
}

template <typename t1, typename t2>
myMap<t1, t2> :: ~myMap() {
	if(keys && values) {
		free(keys);
		free(values);
		keys=NULL;
		values=NULL;
	}
}


template <typename t1, typename t2>
void myMap<t1, t2> :: sort(void) {
	for(int i=0; i < index ; i++) {
		for(int j=i ; j < index-1 ; j++) {
			if(keys[j]>keys[j+1]) {
				t1 temp1 = keys[i];
				keys[i] = keys[j+1];
				keys[j+1] = temp1;

				t2 temp2 = values[j];
				values[i] = values[j+1];
				values[j+1] = temp2;
			}
		}
	}
}


template <typename t1, typename t2>
void myMap <t1, t2> :: insert(const t1 key, const t2 value) {
	if(index==totCapacity) {
		totCapacity *= multiplier;
		keys = (t1 *)realloc(keys, sizeof(t1)*totCapacity);
		values = (t2 *)realloc(values, sizeof(t2)*totCapacity);

		if(!keys || !values)
			throw MEMFAIL;
	}	
	keys[index] = key;
	values[index] = value;
	index+=1;
}

template <typename t1, typename t2>
void myMap <t1, t2> :: erase(const t1 key) {
	for(int i=0 ; i<index ; i++) {
		if(keys[i]==key) {
			for(int j=i ; j<index-1 ; j++) {
				keys[j] = keys[j+1];
				values[j] = values[j+1];
			}
			index -= 1;
			break;
		}
			
	}
}

template <typename t1, typename t2>
void myMap <t1, t2> :: show() {
	sort();
	for(int i=0 ; i<index ; i++) 
		std::cout << "\t\t\t" << keys[i] << " = " << values[i] << std::endl;
}
