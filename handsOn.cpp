#include <iostream>
#include <map>
#include <utility>

void display(std::map<std:: string,int> &user);
int main(void) {
	std::map<std::string,int> users;

/*
	users.insert(std::make_pair("Shubham",10101997));
	users.insert(std::make_pair("abc",14102000));
	display(users);
	users.erase("shubham");
	std::cout << "After deleting shubham key: " << std::endl;

*/

	users["shubham"]=1010;
	users["abc"]=1231;
	display(users);
	users.erase("shubham");

	std::cout << "After erasing the shubham key: " << std::endl;
	display(users);
}

void display(std::map<std:: string,int> &users){
	for (auto const& entry: users) {
        std::cout << "Name: " << entry.first << " Birthdate: " << entry.second << std::endl;
    }

}
