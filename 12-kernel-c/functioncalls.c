#include <stdio.h>
int my_func(int arg); // Function prototype

int my_func(int arg) {
    return arg;
}

void caller() {
        int result = my_func(0xdede);
    printf("Result: %d\n", result); // Print the result for verification
}

int main() {
    caller(); // Call the caller function
    return 0; // Return success
}
