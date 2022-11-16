#include <iostream>
#include <vector>

int recursive_fibonacci(int N) {
    std::vector<unsigned int> answer;
	if (N == 1 || N == 2) {
		answer.push_back(1);
        return 1;
}
    return recursive_fibonacci(N-1) + recursive_fibonacci(N-2);
}


int main(int argc, char const *argv[]) {
    
    recursive_fibonacci(3);
    return 0;
}