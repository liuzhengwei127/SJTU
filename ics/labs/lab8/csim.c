/*
name: Liu Zhengwei
loginID: 517021910758
*/

#include "cachelab.h"
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>

typedef struct TimeLine {
    struct TimeLine *later;
    int index;
}TimeLine;

typedef struct {
    int b,E,s,v;
    int *line;
    TimeLine **head;

}Cache;

int hits=0,misses=0,evictions=0;

void visit(Cache* cache, long address, long size) {
    //get tag and set
    long tag,set;
    address >>= cache->b;
    set = address & ((1 << cache->s) - 1);
    tag = address >> cache->s;

    int empty = -1;
    int hit = -1 ;
    for (int i=set*cache->E;i<(set+1)*cache->E;i++) {
        if (cache->line[i] == -1)
            empty = i;
        if (cache->line[i] == tag) {
            hit = i;
            break;
        }
    }

    if (hit == -1) {
        misses++;
        if (cache->v == 1)
            printf("miss ");
        if (empty >= 0) {
            cache->line[empty] = tag;

            //update timeline
            if (cache->E > 1) {
                TimeLine *update = NULL;
                TimeLine *tmp = cache->head[set];
                if (tmp->index == empty) {
                    update = tmp;
                    cache->head[set] = update->later;
                    update->later = NULL;
                    tmp = cache->head[set];
                    for (int i=0;i<cache->E-2;i++) {
                        tmp = tmp->later;
                    }
                    tmp->later = update;
                } else {
                    for (int i=0;i<cache->E-2;i++) {
                        if (tmp->later->index == empty) {
                            update = tmp->later;
                            tmp->later = tmp->later->later;
                            update->later = NULL;
                        }
                        tmp = tmp->later;
                    }

                    if (update != NULL) {
                        tmp->later = update;
                    }
                }
            }

        } else {
            evictions++;
            if (cache->v == 1)
                printf("eviction ");
            if (cache->E >1) {
                TimeLine *update = cache->head[set];
                cache->head[set] = update->later;
                update->later = NULL;
                TimeLine *tmp = cache->head[set];
                for (int i=0;i<cache->E-2;i++) {
                    tmp = tmp->later;
                }
                tmp->later = update;

                cache->line[update->index] = tag;
            } else {
                cache->line[set] = tag;
            }
        }
    } else {
        hits++;
        if (cache->v == 1)
            printf("hit ");
        //update timeline
        if (cache->E > 1) {
            TimeLine *update = NULL;
            TimeLine *tmp = cache->head[set];
            if (tmp->index == hit) {
                update = tmp;
                cache->head[set] = update->later;
                update->later = NULL;
                tmp = cache->head[set];
                for (int i=0;i<cache->E-2;i++) {
                    tmp = tmp->later;
                }
                tmp->later = update;
            } else {
                for (int i=0;i<cache->E-2;i++) {
                    if (tmp->later->index == hit) {
                        update = tmp->later;
                        tmp->later = tmp->later->later;
                        update->later = NULL;
                    }
                    tmp = tmp->later;
                }

                if (update != NULL) {
                    tmp->later = update;
                }
            }
        }
    }
}

int main(int argc, char **argv)
{
    int b,E,s,v,S;
    char *filename;
    char ch;

    //read arguments
    while ((ch = getopt(argc, argv, "hvs:E:b:t:")) != -1) {
        switch (ch) {
        case 'h':
            printf(
                   "Usage: %s [-hv] -s <num> -E <num> -b <num> -t <file>\n"
                   "Options:\n"
                   "  -h         Print this help message.\n"
                   "  -v         Optional verbose flag.\n"
                   "  -s <num>   Number of set index bits.\n"
                   "  -E <num>   Number of lines per set.\n"
                   "  -b <num>   Number of block offset bits.\n"
                   "  -t <file>  Trace file.\n\n"
                   "Examples:\n"
                   "    linux>  %s -s 4 -E 1 -b 4 -t traces/yi.trace\n"
                   "    linux>  %s -v -s 8 -E 2 -b 4 -t traces/yi.trace\n", argv[0], argv[0], argv[0]);

            return 0;
        case 'v':
            v = 1;
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
            filename = optarg;
            break;
        default:
            printf("wrong arg");
        }
    }

    //initialize cache
    Cache *cache = (Cache *)malloc(sizeof(Cache));
    cache->b = b;
    cache->E = E;
    cache->s = s;
    cache->v = v;
    S = 1 << s;
    size_t size = sizeof(int) * E * S;
    size_t cacheline = sizeof(TimeLine *) * S;
    cache->line = (int *)malloc(size);
    memset(cache->line, -1, size);
    cache->head = (TimeLine **)malloc(cacheline);
    for (int i=0;i<S;i++) {
        cache->head[i] = (TimeLine *) malloc(sizeof(TimeLine));
        TimeLine *tmp = cache->head[i];
        for (int j=0;j<E-1;j++) {
            tmp->index = i*E+j;
            tmp->later = (TimeLine *) malloc(sizeof(TimeLine));
            tmp = tmp->later;
        }
        tmp->index = (i+1)*E-1;
        tmp->later = NULL;
    }

    FILE *file = fopen(filename, "r");

    char line[64];
    while (fgets(line, 64, file) != NULL) {
        if (line[0] != ' ')
            continue;
        char operation;
        long address, size;
        sscanf(line, " %c %lx,%lx", &operation, &address, &size);
        if (v == 1) {
            printf("%c %lx,%lx ", operation, address, size);
        }
        visit(cache, address, size);
        if (operation == 'M') {
            visit(cache, address, size);
        }
        if (v == 1) {
            printf("\n");
        }
    }

    free(cache->line);
    for (int i=0;i<S;i++)
        free(cache->head[i]);
    free(cache->head);
    free(cache);

    printSummary(hits, misses, evictions);

    fclose(file);
    return 0;
}
