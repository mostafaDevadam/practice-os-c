
#define NUMBER_OF_PAGES 256
 
typedef struct {
    int frame;
    int valid;
} PageTableEntry;

//extern PageTableEntry page_table[NUMBER_OF_PAGES];

void initPageTable(void);
int getFrame(int pageNumber);
void setFrame(int pageNumber, int frameNumber);
void invalidatePage(int pageNumber);
int isPageValid(int pageNumber);
void displayPageTable(void);