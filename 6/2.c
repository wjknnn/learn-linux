#include <unistd.h>

int main() {
	execl("1", "apple", "option", (char *)0);
}
