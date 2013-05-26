#include <ControlledSharedMemory.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

using namespace std;

static int read_data;
static int write_data;

void* read_test_callback(void * in){
    char *g = (char*)in;
    printf("In test read callback: read out: %s.\n", g);
    read_data = 1;
    return NULL;
}



void* write_test_callback(void *_){
    printf("In test write callback.\n");
    write_data = 1;
    return NULL;
}

int main(int argc, char* argv[]){
    const char *test_seq = "helloworld!";
    ControlledSharedMemory x("/semaphore_test", "/shared_segment_test", strlen(test_seq)+1);
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
    if(x.updateSharedMemory(test_seq)){
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
