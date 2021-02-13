#include <unistd.h>

int main()
{
	write(1, "Hello, world!", sizeof("Hello, world!"));
	return 0;
}

