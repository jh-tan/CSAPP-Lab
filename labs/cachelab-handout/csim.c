#include "cachelab.h"
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdio.h>
#include <math.h>

typedef struct cacheLine{
    unsigned long tag;
    int valid;
    int time;
}cacheLine;

typedef cacheLine* cacheSet;
typedef cacheSet* Cache;
Cache cache;

int verbose,s,E,b,t;
int hits,misses,evictions;
FILE *fp;
char *help = "Usage: ./csim-ref [-hv] -s <num> -E <num> -b <num> -t <file>";

void parseArg(int , char*[]);
void walkCache(unsigned long);
int simulator();

int main(int argc, char* argv[]) {
    parseArg(argc,argv);
    simulator();
    printSummary(hits,misses,evictions);
    return 0;
}

void parseArg(int argc, char* argv[]){
    int opt;
    while ((opt = getopt(argc, argv, "hvs:E:b:t:")) != -1) {
        switch (opt) {
            case 'h':
                printf("%s\n",help); 
                exit(1);
            case 'v':
                verbose = 1;             
                break;
            case 's':
                s = atoi(optarg);
                break;
            case 'E':
                E = atoi(optarg);
                break;
            case 'b':
                b = atoi(optarg);
                break;
            case 't':
                fp = fopen(optarg, "r");
                if(fp == NULL){
                    fprintf(stderr, "File failed to open\n");
                    exit(-1);
                }
                break;
            default:
                printf("%s\n",help); 
                exit(1);
        }
    }
    if (optind - 1 >= argc) {
        printf("%s\n",help); 
        exit(EXIT_FAILURE);
    }
}

int simulator(){
    int S = pow(2,s); 
    char buf[32], ops;
    unsigned long addr;
    int size;
    cache = (Cache)malloc(sizeof(cacheSet) * S );
    if (cache == NULL) return -1;

    for (int i = 0; i < S; i++) {
        cache[i] = (cacheSet)calloc(E, sizeof(cacheLine));
        if (cache[i] == NULL) return -1;
    }

    while(fgets(buf,sizeof(buf),fp) != NULL){
        if(buf[0] == 'I')
            continue;
        sscanf(buf," %c %lx,%d",&ops,&addr,&size);

        switch(ops){
            case 'S':
            case 'L':
                if (verbose) printf("%c %lx, %d",ops,addr,size);
                walkCache(addr);
                break;
            case 'M': 
                /*
                 Modify = Load + Store
                 Possible case:
                 a. 2 hits
                 b. 1 hits + 1 miss
                 c. 1 hits + 1 miss + 1 evictions
                 */
                if (verbose) printf("%c %lx, %d",ops,addr,size);
                walkCache(addr);
                walkCache(addr);
                break;
        }
        if (verbose) printf("\n");
    }

    for (int i = 0; i < S; i++)
        free(cache[i]);
    free(cache);
    fclose(fp);
    return 0;
}

void walkCache(unsigned long addr){
    unsigned long tag = addr >> (s+b);
    unsigned int set = (addr >> b) & ((1 << s) - 1);
    int evict = 0;
    int empty = -1;
    cacheSet cacheSet = cache[set];

    for (int i = 0; i < E; i++){
        if(cacheSet[i].valid && cacheSet[i].tag == tag){
            hits++;
            cacheSet[i].time = 1;
            if(verbose) printf(" hit");
            return;
        }

        cacheSet[i].time++;

        if(cacheSet[evict].time <= cacheSet[i].time)
            evict = i;

        if(cacheSet[i].valid != 1){
            empty = i;
        }
    }

    misses++;
    if(verbose) printf(" miss");

    if(empty != -1){ // When the cache still have empty line
        cacheSet[empty].valid = 1;
        cacheSet[empty].tag = tag;
        cacheSet[empty].time = 1;
    }
    else{ // When all cache lines are occupied and replacement is needed
        cacheSet[evict].tag = tag;
        cacheSet[evict].time = 1;
        evictions++;
        if(verbose) printf(" eviction");
    }
}
