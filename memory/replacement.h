

#define NUMBER_OF_FRAMS 128


//extern frameTable[NUMBER_OF_FRAMS];

void initReplacement(void);

int replaceFIFO(void);

int allocateFrame(int pageNumber);
int getPageInFrame(int frameNumber);

int getFreeFrame(void);

