
#define PAGE_SIZE 256
#define NUMBER_OF_FRAMS 128

extern char physical_memory[NUMBER_OF_FRAMS][PAGE_SIZE];

void initMemory(void);
void loadPage(int frameNumber, char *buffer);
char readyByte(int frameNumber, int offset);
void writeByte(int frameNumber, int offset, char value);
void displayMemory(void);
int loadPageFromBackingStore(int pageNumber, int frameNumber);

void generateBackingStore(void);

