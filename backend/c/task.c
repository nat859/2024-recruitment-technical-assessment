#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 50
#define MAX_CATEGORIES 10

struct File {
    int id;
    char name[MAX_STRING_LEN];
    char categories[MAX_CATEGORIES][MAX_STRING_LEN];
    int numCategories;
    int parent;
    int size;
};

int checkArray(char **cat, int numCat, int counter[MAX_CATEGORIES],
                char categories[MAX_CATEGORIES][MAX_STRING_LEN], int index); 

/**
 * Task 1
 * Returned list should contain copies of the names e.g. through strdup()
 */
char **leafFiles(struct File *files, int numFiles, int *numLeafFiles) {
    //if this flag is one, that means it is not a leaf node
    int flag = 0;
   
    //keeps track of the number of leaf files
    int counter = 0;

    //not sure how to do a list in c, so I just used an array (holds the copies 
    //of the names
    char **names = malloc(MAX_STRING_LEN * numFiles);
   
    //for each file
    for (int i = 0; i < numFiles; i++){
        //we want to check if it is a parent: if it is not a parent to any other
        //file than it is a leaf
        for (int j = 0; j < numFiles; j++) {
            if (files[j].parent == files[i].id) {
                flag = 1;
            }
        }

        // if flag = 0, that means the files[i] is not a parent i.e is a leaf
        if (flag == 0) {
            names[counter] = strdup(files[i].name);
            counter++;
        }
        
        //reset for next file
        flag = 0;
    }
    *numLeafFiles = counter;

    return names;
}

/**
 * Task 2
 * Returned list should contain copies of the categories e.g. through strdup()
 */
char **kLargestCategories(struct File *files, int numFiles, int k, int *numReturned) {
    //An array of category names
    char **cat = malloc(MAX_STRING_LEN * MAX_CATEGORIES);

    //An array that keeps a counter of the number of files in a category
    //Each index in the categories array corresponds to the index in this array
    //i dont know if this is the most efficient way, but its all I can think of
    int counter[MAX_CATEGORIES] = {};

    //number of categories discovered so far
    int numCat = 0;

    for (int i = 0; i < numFiles; i++) {
        for (int j = 0; j < files[i].numCategories; j++) {
            numCat = checkArray(cat, numCat, counter, files[i].categories, j);
        }
    }

    if (k > numCat) {
        k = numCat;
    }

    char **returns = malloc(MAX_STRING_LEN * MAX_CATEGORIES);
    //this would be a lot easier in javascript :((
    //find the kth max
    for (int i = 0; i < k; i++) {
        int max = counter[0];
        int index = 0;
        for (int j = 0; j < numCat - i; j++)  {
            if (max < counter[j]) {
                max = counter[j];
                index = j;
            } else if (max == counter[j]) {
                //doesnt account for lower case letters yet cause im running
                //out of time (i started a bit too late)
                if (strcmp(cat[index], cat[j]) > 0) {
                    max = counter[j];
                    index = j;
                }
            }
        }
     
        returns[i] = strdup(cat[index]);
        cat[index] = cat[numCat - i - 1];
        counter[index] = counter[numCat - i - 1];
    }
    
    *numReturned = k;
    return returns;
}

int checkArray(char **cat, int numCat, int counter[MAX_CATEGORIES],
                char categories[MAX_CATEGORIES][MAX_STRING_LEN], int index) {
    int flag = 0;
    for (int i = 0; i < numCat; i++) {
        if (strcmp(cat[i], categories[index]) == 0) {
            counter[i]++;
            flag = 1;
        }
    }

    //new category
    if (flag == 0) {
        cat[numCat] = strdup(categories[index]);
        counter[numCat]++;
        numCat++;
    }
    return numCat;
}

/**
 * Task 3
 */
 //VERY VERY SORRY I DIDN'T GET UP TO TASK 3 AS I ONLY STARTED THIS CODING SECTION
 //LIKE AN HOUR BEFORE IT WAS DUE AS FOR SOME REASON I DIDNT EXPECT IT
int largestFileSize(struct File *files, int numFiles) {
    return 0;
}


int qsortStrcmp(const void *a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}

int main(void) {
    struct File testFiles[] = {
        { .id = 1, .name = "Document.txt", .categories = {"Documents"}, .numCategories = 1, .parent = 3, .size = 1024 },
        { .id = 2, .name = "Image.jpg", .categories = {"Media", "Photos"}, .numCategories = 2, .parent = 34, .size = 2048 },
        { .id = 3, .name = "Folder", .categories = {"Folder"}, .numCategories = 1, .parent = -1, .size = 0 },
        { .id = 5, .name = "Spreadsheet.xlsx", .categories = {"Documents", "Excel"}, .numCategories = 2, .parent = 3, .size = 4096 },
        { .id = 8, .name = "Backup.zip", .categories = {"Backup"}, .numCategories = 1, .parent = 233, .size = 8192 },
        { .id = 13, .name = "Presentation.pptx", .categories = {"Documents", "Presentation"}, .numCategories = 2, .parent = 3, .size = 3072 },
        { .id = 21, .name = "Video.mp4", .categories = {"Media", "Videos"}, .numCategories = 2, .parent = 34, .size = 6144 },
        { .id = 34, .name = "Folder2", .categories = {"Folder"}, .numCategories = 1, .parent = 3, .size = 0 },
        { .id = 55, .name = "Code.py", .categories = {"Programming"}, .numCategories = 1, .parent = -1, .size = 1536 },
        { .id = 89, .name = "Audio.mp3", .categories = {"Media", "Audio"}, .numCategories = 2, .parent = 34, .size = 2560 },
        { .id = 144, .name = "Spreadsheet2.xlsx", .categories = {"Documents", "Excel"}, .numCategories = 2, .parent = 3, .size = 2048 },
        { .id = 233, .name = "Folder3", .categories = {"Folder"}, .numCategories = 1, .parent = -1, .size = 4096 },
    };

    int numLeafFiles;
    char *expectedLeafFiles[] = {
        "Audio.mp3",
        "Backup.zip",
        "Code.py",
        "Document.txt",
        "Image.jpg",
        "Presentation.pptx",
        "Spreadsheet.xlsx",
        "Spreadsheet2.xlsx",
        "Video.mp4"
    };
    char **returnedLeafFiles = leafFiles(testFiles, 12, &numLeafFiles);
    qsort(returnedLeafFiles, numLeafFiles, sizeof(char *), &qsortStrcmp);

    assert(numLeafFiles == 9);
    for (int i = 0; i < 9; i++) {
        assert(strcmp(returnedLeafFiles[i], expectedLeafFiles[i]) == 0);
        free(returnedLeafFiles[i]);
    }
    free(returnedLeafFiles);

    int numCategories;
    char *expectedCategories[] = {"Documents", "Folder", "Media"};
    char **returnedCategories = kLargestCategories(testFiles, 12, 3, &numCategories);
    assert(numCategories == 3);
        for (int i = 0; i < 3; i++) {
        assert(strcmp(returnedCategories[i], expectedCategories[i]) == 0);
        free(returnedCategories[i]);
    }
    free(returnedCategories);

    assert(largestFileSize(testFiles, 12) == 20992);

}
