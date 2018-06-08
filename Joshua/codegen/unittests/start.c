#include <stdio.h>

int Main();  // note that Main now returns an integer!

int main(int argc, char **argv) {
    printf("starting Main...\n");
	printf("Main returned: %d\n", Main());
    return 0;
}
