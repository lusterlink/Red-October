#include <ControlledSharedMemory.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

static int read_data;
static int write_data;

void* read_test_callback(void * in){
    int* g = (int*)in;
    printf("In test read callback: read out: %d.\n", *g);
    read_data = 1;
    return NULL;
}



void* write_test_callback(void *_){
    printf("In test write callback.\n");
    write_data = 1;
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
    read_data = 0;
    if(x.requestRead() < 0){
        fprintf(stderr, "Error in requesting read()\n");
    }
    while(!read_data){}

    write_data = 0;
    int a = 8;
    if(x.updateSharedMemory(&a)){
        fprintf(stderr, "Error in requestin update()\n");
    }
    while(!write_data){}

    read_data = 0;
    if(x.requestRead() < 0){
        fprintf(stderr, "Error in requesting read()\n");
    }
    while(!read_data){}

    sleep(2);
    x.unlinkMemorySegment();
}
