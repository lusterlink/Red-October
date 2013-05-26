#include <ControlledSharedMemory.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void* read_test_callback(void * in){
    int* g = (int*)in;
    printf("got back: %d\n", *g);
    printf("In test read callback.\n");
    return NULL;
}

void* write_test_callback(void *_){
    printf("In test write callback.\n");
    return NULL;
}

int main(int argc, char* argv[]){
    ControlledSharedMemory x("/semaphore_test", "/shared_segment_test", sizeof(int));
    x.initialize();

    if(x.registerReadCallback((Callback) read_test_callback) != 0){
        printf("Error adding read callback.\n");
    }

    if(x.registerUpdateCallback((Callback) write_test_callback) != 0){
        printf("Error adding write callback.\n");
    }
    printf("Read Got: %d\n", x.requestRead());

    int a = 15;
    printf("Write Got: %d\n", x.updateSharedMemory(&a));


}
