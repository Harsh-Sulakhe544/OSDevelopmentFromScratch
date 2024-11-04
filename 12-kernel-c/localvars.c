#include <stdio.h>
int my_function() {
    int my_var = 0xbaba;
    printf("%ls\n", &my_var); // Print 
    return my_var;
}

int main() {
    my_function(); // Call the function
    return 0; // Return success
}
