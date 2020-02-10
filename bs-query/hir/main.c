#include <global.h>

#define MAX_V 1000
static V buffV[MAX_V];
static I buffS = 0;
const B opt_deep = true;

extern L CSV_FILE_SCALE;

/* a file contains library functions */
#include "libs.h"
/* a temp file for having all generated code */
#include "gencode.h"

static void init(int id){
    initBackend();
    //initTablesByQid(id); // load all tables
    initTableByName((S)"blackscholes");
    DOI(MAX_V, buffV[i]=allocNode())
}

int getId(char* str){
    S idStr = strchr(str,'-');
    if(idStr && !strncmp(idStr+1, "bs", 2)){
        return atoi(idStr+3);
    }
    else {
        EP("Not a valid executable: %s, but <prefix>-b<id> is expected", str);
    }
}

void run(int n, int id){
    init(id);
    L n2 = n; // n+1
    E *record=(E*)malloc(sizeof(E)*n2), total=0;
    L cur = getHeapOffset();
    DOI(n2, {setHeapOffset(cur); time_clear(); record[i]=horse_entry();})
    if(n>0){
        DOI(n2, total += record[i])
        P("bs%02d>> Run with %lld times, last %d average (ms): %g |",
                id,n2,n,total/n);
        DOI(n2, P(" %g",record[i])) P("\n");
    }
    else { // n==0
        P("bs%02d>> Run with 1 times, average (ms): %g | %g\n",
                id,record[0],record[0]);
    }
    free(record);
}

I main(int argc, char **argv){
    if(argc!=3){
        printf("[Usage]: %s <scale> <run>\n",argv[0]);
        exit(1);
    }
    I scale = atoi (argv[1]);
    I num   = atoi (argv[2]);
    I id    = getId(argv[0]);
    if(num<0) EP("# of runs must be >=0, but %d found",num);
    if(scale!=1 && scale!=2 && scale!=4 && scale!=8)
        EP("scale must be one of 1/2/4/8");
    CSV_FILE_SCALE = scale;
    run(num, id);
    R 0;
}

