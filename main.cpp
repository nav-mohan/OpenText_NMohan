#include <iostream>

// usage: main input.xml output.html
int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        fprintf(stderr, "USAGE: %s input.xml output.html\n",argv[0]);
        exit(1);
    }
}