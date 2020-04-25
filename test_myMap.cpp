#include "myMap.h"

int main(void) {

	// testing for both keys and values as float datatype
    myMap<float,float> type_float;
	std::cout << "_________________ This is float type testing _____________________\n" << std::endl;

    type_float.insert(1.125,2.356);
    type_float.insert(3.134,4.854);
    type_float.insert(5.695,6.223);

    std::cout << "\t\t*** Before Deletion ***" << std::endl;
    type_float.show();

    type_float.erase(3.134);

    std::cout << "\t\t*** After Deletion ***" << std::endl;
    type_float.show();
	std::cout << "_________________ This is float type testing _____________________\n" << std::endl;

//	testing for both keys and vales as char datatype

    myMap<char,char> type_char;
	std::cout << "_________________ This is char type testing _____________________\n" << std::endl;
    type_char.insert('a','b');
    type_char.insert('c','d');
    type_char.insert('e','f');

    std::cout << "\t\t*** Before Deletion ***" << std::endl;
    type_char.show();

    type_char.erase('a');

    std::cout << "\t\t*** After Deletion ***" << std::endl;
    type_char.show();
	std::cout << "_________________ This is char type testing _____________________\n" << std::endl;


//	testing for keys having string and values having int datatype

    myMap<std::string,int> type_string_int;
	std::cout << "_________________ This is string with int type testing _____________________\n" << std::endl;
    type_string_int.insert("Shubham",2);
    type_string_int.insert("Fulchand",4);
    type_string_int.insert("Jagdhane",6);
    type_string_int.insert("This is testing",6);
    type_string_int.insert("Shubham",15);


    std::cout << "\t\t*** Before Deletion ***" << std::endl;
    type_string_int.show();

	type_string_int.erase("Shubham");

    std::cout << "\t\t*** After Deletion ***" << std::endl;
    type_string_int.show();

	std::cout << "_________________ This is string with int type testing _____________________\n" << std::endl;
}
