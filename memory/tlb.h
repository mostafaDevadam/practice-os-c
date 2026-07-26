
#define TLB_SIZE 16

typedef struct {
    int page;
    int frame;
} TLBEntry;

extern TLBEntry tlb[TLB_SIZE];
extern int tlbIndex;

void initTLB(void);
int searchTLB(int pageNumber);
void addToTLB(int pageNumber, int frameNumber);
void displayTLB(void);

void invalidateTLBEntry(int pageNumber);

