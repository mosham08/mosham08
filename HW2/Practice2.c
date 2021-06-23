/******************************************************************************
* FILE: hello_arg2.c
* DESCRIPTION:
*   A "hello world" Pthreads program which demonstrates another safe way
*   to pass arguments to threads during thread creation.  In this case,
*   a structure is used to pass multiple arguments.
* AUTHOR: Blaise Barney
* LAST REVISED: 01/29/09
******************************************************************************/
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <time.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <pthread.h>


#define NUM_THREADS    10
#define MAX 10000
int numPros;

struct thread_data {
    int thread_id;
//    int sum;
//    char *message;
    struct Earthquakes *earth[10000];

    int size;
};
struct Earthquakes {
    char time[100];
    char latitude[20];
    char longitude[20];
    char depth[20];
    char mag[20];
};
struct thread_data thread_data_array[NUM_THREADS];

struct Earthquakes *earthquakes[MAX];
struct Earthquakes *earthquakes1[10000];
struct Earthquakes *earthquakes2[10000];
struct Earthquakes *earthquakes3[10000];
struct Earthquakes *earthquakes4[10000];
struct Earthquakes *earthquakes5[10000];
struct Earthquakes *earthquakes6[10000];
struct Earthquakes *earthquakes7[10000];
struct Earthquakes *earthquakes8[10000];
struct Earthquakes *earthquakes9[10000];
struct Earthquakes *earthquakes10[10000];

int read_file(char *fileName) {
//    fprintf(stderr, "Try to open file!\n");
    FILE *file = fopen(fileName, "r");
    const size_t line_size = 2049;
    char *line = malloc(line_size);
    // checking file error
    if (!file) {
        fprintf(stderr, "Unable to open file!\n");
        return -1;
    }
// instrumentaion start
    time_t t;
    t = time(NULL);

    fgets(line, line_size, file);


    fgets(line, line_size, file);
    int index = 0;
    while (fgets(line, line_size, file) && (index < MAX)) {
        // allocate mem for the earthquakes structure
        earthquakes[index] = (struct Earthquakes *) malloc(sizeof(struct Earthquakes));

        char *token;
        // get token from line
        token = strtok(line, ",");
        strcpy(earthquakes[index]->time, token);
        token = strtok(NULL, ",");
        strcpy(earthquakes[index]->latitude, token);
        token = strtok(NULL, ",");
        strcpy(earthquakes[index]->longitude, token);
        token = strtok(NULL, ",");
        strcpy(earthquakes[index]->depth, token);
        token = strtok(NULL, ",");
        strcpy(earthquakes[index]->mag, token);

        index++;
    }
    free(line);
    return 1;
}

void split1(int numPros) {

    // Split data into two seprate arrays, 5k data each
    if (numPros == 2) {
        for (int i = 0; i < 5000; ++i) {
            thread_data_array[0].earth[i] = earthquakes1[i];
//            earthquakes1[i] = (struct Earthquakes *) malloc(sizeof(struct Earthquakes));
//            earthquakes1[i] = earthquakes[i];
        }

        int j = 0;
        for (int i = 5000; i < 10000; ++i) {
            thread_data_array[1].earth[i] = earthquakes2[i];
            j++;
        }
    }

    // Split data into 4 different arrays, 2500 data each one
    if (numPros == 4) {
        for (int i = 0; i < 2500; ++i) {
            thread_data_array[0].earth[i] = earthquakes1[i];
        }

        int j = 0;
        for (int i = 2500; i < 5000; ++i) {
            thread_data_array[1].earth[i] = earthquakes2[i];
            j++;
        }

        j = 0;
        for (int i = 5000; i < 7500; ++i) {
            thread_data_array[2].earth[j] = earthquakes3[i];
            j++;
        }

        j = 0;
        for (int i = 7500; i < 10000; ++i) {
            thread_data_array[3].earth[j] = earthquakes4[i];
            j++;
        }
    }

    // Split all the data into 10 arrays, 1k of data each
    if (numPros == 10) {
        for (int i = 0; i < 1000; ++i) {
            thread_data_array[0].earth[i] = earthquakes1[i];
        }

        int j = 0;
        for (int i = 1000; i < 2000; ++i) {
            thread_data_array[1].earth[j] = earthquakes2[i];
            j++;
        }

        j = 0;
        for (int i = 2000; i < 3000; ++i) {
            thread_data_array[2].earth[j] = earthquakes3[i];
            j++;
        }

        j = 0;
        for (int i = 3000; i < 4000; ++i) {
            thread_data_array[3].earth[j] = earthquakes4[i];
            j++;
        }

        j = 0;
        for (int i = 4000; i < 5000; ++i) {
            thread_data_array[4].earth[j] = earthquakes5[i];
            j++;
        }

        j = 0;
        for (int i = 5000; i < 6000; ++i) {
            thread_data_array[5].earth[j] = earthquakes6[i];
            j++;
        }

        j = 0;
        for (int i = 6000; i < 7000; ++i) {
            thread_data_array[6].earth[j] = earthquakes7[i];
            j++;
        }

        j = 0;
        for (int i = 7000; i < 8000; ++i) {
            thread_data_array[7].earth[j] = earthquakes8[i];
            j++;
        }

        j = 0;
        for (int i = 8000; i < 9000; ++i) {
            thread_data_array[8].earth[j] = earthquakes9[i];
            j++;
        }

        j = 0;
        for (int i = 9000; i < 10000; ++i) {
            thread_data_array[9].earth[j] = earthquakes10[i];
            j++;
        }
    }
}

void split(int numPros) {

    // Split data into two seprate arrays, 5k data each
    if (numPros == 2) {
        for (int i = 0; i < 5000; ++i) {
            earthquakes1[i] = (struct Earthquakes *) malloc(sizeof(struct Earthquakes));
            earthquakes1[i] = earthquakes[i];
        }

        int j = 0;
        for (int i = 5000; i < 10000; ++i) {
            earthquakes2[j] = (struct Earthquakes *) malloc(sizeof(struct Earthquakes));
            earthquakes2[j] = earthquakes[i];
            j++;
        }
    }

    // Split data into 4 different arrays, 2500 data each one
    if (numPros == 4) {
        for (int i = 0; i < 2500; ++i) {
            earthquakes1[i] = (struct Earthquakes *) malloc(sizeof(struct Earthquakes));
            earthquakes1[i] = earthquakes[i];
        }

        int j = 0;
        for (int i = 2500; i < 5000; ++i) {
            earthquakes2[j] = (struct Earthquakes *) malloc(sizeof(struct Earthquakes));
            earthquakes2[j] = earthquakes[i];
            j++;
        }

        j = 0;
        for (int i = 5000; i < 7500; ++i) {
            earthquakes3[j] = (struct Earthquakes *) malloc(sizeof(struct Earthquakes));
            earthquakes3[j] = earthquakes[i];
            j++;
        }

        j = 0;
        for (int i = 7500; i < 10000; ++i) {
            earthquakes4[j] = (struct Earthquakes *) malloc(sizeof(struct Earthquakes));
            earthquakes4[j] = earthquakes[i];
            j++;
        }
    }

    // Split all the data into 10 arrays, 1k of data each
    if (numPros == 10) {
        for (int i = 0; i < 1000; ++i) {
            earthquakes1[i] = (struct Earthquakes *) malloc(sizeof(struct Earthquakes));
            earthquakes1[i] = earthquakes[i];
        }

        int j = 0;
        for (int i = 1000; i < 2000; ++i) {
            earthquakes2[j] = (struct Earthquakes *) malloc(sizeof(struct Earthquakes));
            earthquakes2[j] = earthquakes[i];
            j++;
        }

        j = 0;
        for (int i = 2000; i < 3000; ++i) {
            earthquakes3[j] = (struct Earthquakes *) malloc(sizeof(struct Earthquakes));
            earthquakes3[j] = earthquakes[i];
            j++;
        }

        j = 0;
        for (int i = 3000; i < 4000; ++i) {
            earthquakes4[j] = (struct Earthquakes *) malloc(sizeof(struct Earthquakes));
            earthquakes4[j] = earthquakes[i];
            j++;
        }

        j = 0;
        for (int i = 4000; i < 5000; ++i) {
            earthquakes5[j] = (struct Earthquakes *) malloc(sizeof(struct Earthquakes));
            earthquakes5[j] = earthquakes[i];
            j++;
        }

        j = 0;
        for (int i = 5000; i < 6000; ++i) {
            earthquakes6[j] = (struct Earthquakes *) malloc(sizeof(struct Earthquakes));
            earthquakes6[j] = earthquakes[i];
            j++;
        }

        j = 0;
        for (int i = 6000; i < 7000; ++i) {
            earthquakes7[j] = (struct Earthquakes *) malloc(sizeof(struct Earthquakes));
            earthquakes7[j] = earthquakes[i];
            j++;
        }

        j = 0;
        for (int i = 7000; i < 8000; ++i) {
            earthquakes8[j] = (struct Earthquakes *) malloc(sizeof(struct Earthquakes));
            earthquakes8[j] = earthquakes[i];
            j++;
        }

        j = 0;
        for (int i = 8000; i < 9000; ++i) {
            earthquakes9[j] = (struct Earthquakes *) malloc(sizeof(struct Earthquakes));
            earthquakes9[j] = earthquakes[i];
            j++;
        }

        j = 0;
        for (int i = 9000; i < 10000; ++i) {
            earthquakes10[j] = (struct Earthquakes *) malloc(sizeof(struct Earthquakes));
            earthquakes10[j] = earthquakes[i];
            j++;
        }
    }
}

void *Sort(void *threadarg) {
    int taskid, sum, size;
    char *hello_msg;
    struct thread_data *my_data;
    struct Earthquakes *earth;

    sleep(1);
    my_data = (struct thread_data *) threadarg;
    taskid = my_data->thread_id;
//    sum = my_data->sum;
//    hello_msg = my_data->message;
    size = my_data->size;

////    printf("Thread %d: %s  Sum=%d  Time= %s\n", taskid, hello_msg, sum, my_data->earthquakes1[0]->time);
//    printf("Thread %d: %s  Sum=%d  Time= %s\n", taskid, "hello_msg", 0, my_data->earthquakes1[0]->time);

    /// sorting code
    double time_spent = 0.0;
    clock_t begin = clock();

    struct Earthquakes *temp;

    printf("Before For\n");
    for (int i = 1; i < size; i++) {
        for (int j = 0; j < size - i; j++) {
            if (atof(my_data->earth[j]->latitude) > atof(my_data->earth[j + 1]->latitude)) {
                temp = my_data->earth[j];
                my_data->earth[j] = my_data->earth[j + 1];
                my_data->earth[j + 1] = temp;
            }
        }
    }
    printf("After For\n");
    clock_t end = clock();
    time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
    printf("\n%s: Time elpased is %f seconds\n", "hello_msg", time_spent);
    /// end sorting code
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    char *earthquake_filename = "./all_month.csv";
    read_file(earthquake_filename);

    int *taskids[NUM_THREADS];
    int rc, t, sum;

    sum = 0;

//    int numPros;
    printf("Enter number of Threads (1, 2, 4, 10): ");
    scanf("%d", &numPros);
    pthread_t threads[NUM_THREADS];

    // Split your data by number of processes user requests
    split(numPros);
    split1(numPros);
    printf("\nNumber of Running Threads: %d\n", numPros);
    char wait = "";

// this is my split
//    for (t = 0; t < numPros; t++) {
//        for (int k = 0; k < 1000; k++) {
//            thread_data_array[t].earthquakes1[k] = earthquakes[k];
//        }
//    }


    for (t = 0; t < numPros; t++) {
        sum = sum + t;
        thread_data_array[t].thread_id = t;
//        thread_data_array[t].sum = sum;
//        thread_data_array[t].message = messages[t];
        thread_data_array[t].size = 10000;

        printf("Creating thread %d\n", t);
        rc = pthread_create(&threads[t], NULL, Sort, (void *)
                &thread_data_array[t]);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

//    if (numPros == 1) {
//        sum = sum + 0;
//        thread_data_array[0].thread_id = 0;
////        thread_data_array[t].sum = sum;
////        thread_data_array[t].message = messages[t];
//        thread_data_array[0].size = 10000;
//
//        printf("Creating thread %d\n", 0);
//        rc = pthread_create(&threads[0], NULL, Sort, (void *)
//                &thread_data_array[0]);
//        if (rc) {
//            printf("ERROR; return code from pthread_create() is %d\n", rc);
//            exit(-1);
//        }
//    }
//
//    // checks if only 2 processes need to run
//    if (numPros == 2) {
//        for (t = 0; t < numPros; t++) {
////            sum = sum + t;
//            thread_data_array[t].thread_id = t;
////        thread_data_array[t].sum = sum;
////        thread_data_array[t].message = messages[t];
//            thread_data_array[t].size = 5000;
//
//            printf("Creating thread %d\n", t);
//            rc = pthread_create(&threads[t], NULL, Sort, (void *)
//                    &thread_data_array[t]);
//            if (rc) {
//                printf("ERROR; return code from pthread_create() is %d\n", rc);
//                exit(-1);
//            }
//        }
//
//        sleep(1);
//    }
//
//    // checks if only 4 processes need to run
//    if (numPros == 4) {
//        for (t = 0; t < numPros; t++) {
////            sum = sum + t;
//            thread_data_array[t].thread_id = t;
////        thread_data_array[t].sum = sum;
////        thread_data_array[t].message = messages[t];
//            thread_data_array[t].size = 2500;
//
//            printf("Creating thread %d\n", t);
//            rc = pthread_create(&threads[t], NULL, Sort, (void *)
//                    &thread_data_array[t]);
//            if (rc) {
//                printf("ERROR; return code from pthread_create() is %d\n", rc);
//                exit(-1);
//            }
//        }
//        sleep(1);
//    }
//    // checks if only 10 processes need to run
//    if (numPros == 10) {
//        for (t = 0; t < numPros; t++) {
////            sum = sum + t;
//            thread_data_array[t].thread_id = t;
////        thread_data_array[t].sum = sum;
////        thread_data_array[t].message = messages[t];
//            thread_data_array[t].size = 1000;
//
//            printf("Creating thread %d\n", t);
//            rc = pthread_create(&threads[t], NULL, Sort, (void *)
//                    &thread_data_array[t]);
//            if (rc) {
//                printf("ERROR; return code from pthread_create() is %d\n", rc);
//                exit(-1);
//            }
//        }
//
//        sleep(1);
//    }


    pthread_exit(NULL);
}