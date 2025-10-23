// Caleb Griffy

#include <iostream>
#include <iomanip>
#include <sys/time.h>

using namespace std;

// Arguments to pass to each thread
struct ThreadArguments{
    int id;
    int num_threads;
    int* data;
    int num_rows;
    int num_cols;
    int* sums;
};

// Work done by each thread
void* sumPart(void* arg){
    ThreadArguments args = *(static_cast<ThreadArguments*>(arg));
    int sum = 0;
    int rowsPer = args.num_rows / args.num_threads;
    int myRows = rowsPer;
	// If the last thread, take any remaining extra rows
    if (args.id == args.num_threads - 1)
        myRows += args.num_threads;
    for (int i = 0 + (args.id * rowsPer); i < myRows + (args.id * rowsPer) && i < args.num_rows; i++){
        for (int j = 0; j < args.num_cols; j++){
            sum += args.data[i * args.num_cols + j];
        }
    }
    *args.sums = sum;
    
    return nullptr;
}

int main (int argc, char *argv[])
{
    if (argc != 3){
        cout << "Usage: ./l2 seed num_threads (use 1 for serial)" << endl;
        return -1;
    }
    int seed = stof(argv[1]);
    int num_threads = stof(argv[2]);

    if (num_threads < 1){
        cout << "Need at least one thread!" << endl;
        return -1;
    }

    int num_rows = 10000;
    int num_cols = 10000;

    // The array, dynamic for large sizes
    int* data = new int[num_rows * num_cols]{0};
    int sums[num_threads] = {0};

    // Randomize data
    srand(seed);
    for (int i = 0; i < num_rows; i++){
        for (int j = 0; j < num_cols; j++){
            data[i * num_cols + j] = rand() % 100 + 1; // Random number 1-100
        }
    }

    // Get initial time
    struct timeval begin_time, end_time;
    gettimeofday(&begin_time, NULL);

    // Initialize pthread array, does not need to store main thread, though
    pthread_t threads[num_threads - 1];
    ThreadArguments args[num_threads];

    // Create threads to set to work
    for (int i = 0; i < num_threads - 1; i++){
        args[i + 1] = {(i + 1), num_threads, &data[0], num_rows, num_cols, &sums[i + 1]};
        pthread_create(&threads[i], NULL, sumPart, static_cast<void*>(&args[i + 1]));
    }
    // Set this thread to work, too
    args[0] = {0, num_threads, &data[0], num_rows, num_cols, &sums[0]};
    sumPart(static_cast<void*>(&args[0]));

    for (int i = 0; i < num_threads - 1; i++){
        pthread_join(threads[i], NULL);
    }

    int total = 0;
    for (int i = 0; i < num_threads; i++){
        total += sums[i];
    }

    // Get final time
    gettimeofday(&end_time, NULL);

    // Find time of all iterations
    float time_taken = (end_time.tv_sec + (end_time.tv_usec / 1000000.0)) - (begin_time.tv_sec + (begin_time.tv_usec / 1000000.0));

    cout << time_taken << endl;

	delete [] data;
    
    return 0;
}