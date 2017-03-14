typedef enum { SM_NEW, SM_OLD, SM_SHORT, SM_LONG, SM_ALPHA, SM_OMEGA } sortmode_e;
extern unsigned long sortmode;
void sort_it(struct ftpparse *fp, int count);
