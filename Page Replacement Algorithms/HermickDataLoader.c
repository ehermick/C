/* 
 * SER 334 | Fall 2020 | Programming 11 | Page Replacement Algorithms
 * Data Loader Description: Loads the data file and returns a struct containing
 * its information. 
 * 
 * 
 * Completion Time: 30 minutes
 * 
 * @author Emma Hermick 
 * @version 1.0 | Nov 29, 2020
 */

#include <stdio.h>
#include <stdlib.h>

#include "DataLoader.h"

/**
 * Loads a test_scenario strut from a textfile.
 *
 * @param filename The name of the file to load.
 * @return A struct containing the loaded file.
 */
struct test_scenario* load_test_data(char* filename) {
    FILE* file;
    struct test_scenario* ts = malloc(sizeof(struct test_scenario));
    
    file = fopen(filename, "r");
    
    if (file == NULL) {
        printf("Error opening file");
        exit(1);
    }
    
    int numPages;
    int numFrames;
    int numEntries;
    
    fscanf(file, "%d", &numPages);
    fscanf(file, "%d", &numFrames);
    fscanf(file, "%d", &numEntries);
    
    ts->page_count = numPages;
    ts->frame_count = numFrames;
    ts->refstr_len = numEntries;
    
    int i;
    for (i = 0; i < numEntries; i++) {
        int entry;
        fscanf(file, "%d", &entry);
        ts->refstr[i] = entry;
    }
    
    fclose(file);
    return ts;

}

