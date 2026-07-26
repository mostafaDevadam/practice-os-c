 #include "replacement.h"

 static int nextFreeFrame = 0;
 static int fifoPointer = 0;

 int frameTable[NUMBER_OF_FRAMS];
 
void initReplacement(void){

    nextFreeFrame = 0;
    fifoPointer = 0;

}

int getFreeFrame(void){
    if(nextFreeFrame < NUMBER_OF_FRAMS){
        return nextFreeFrame++;
    }
    return -1;
}

int replaceFIFO(void){

    int frame = fifoPointer;
    fifoPointer = (fifoPointer + 1) % NUMBER_OF_FRAMS;
    return frame;

}


int allocateFrame(int pageNumber){
    int frame;

    if(nextFreeFrame < NUMBER_OF_FRAMS){
        frame = nextFreeFrame;
        frameTable[frame] = pageNumber;
        return frame;
    }

    frame = fifoPointer;
    frameTable[frame] = pageNumber;

    fifoPointer++;

    if(fifoPointer == NUMBER_OF_FRAMS){
        fifoPointer = 0;
    }
    return frame;
}

int getPageInFrame(int frameNumber){
    if(frameNumber < 0 || frameNumber >= NUMBER_OF_FRAMS){
        return -1;
    }

    return frameTable[frameNumber];
}
