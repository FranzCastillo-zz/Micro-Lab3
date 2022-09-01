#include <iostream>
#include <pthread.h>
using namespace std;

struct threadParameters{
    int num, min, max, sum;
};

void separator(){
    cout << "==========================================================" << endl;
}
int askMax(){
    cout << "Ingrese el numero maximo: " << endl;
    int max;
    cin >> max;
    return max;
}
int askThreads(){
    cout << "Ingrese el numero de threads: " << endl;
    while(true){
        int nThreads;
        cin >> nThreads;
        if(nThreads < 1){
            cout << "Ingrese una cantidad valida de hilos" << endl;
        }else{
            return nThreads;
        }
    }
}

void* checkPrimes(void *arguments){

    auto args = (struct threadParameters*) arguments;
    int min = args->min;
    int max = args->max;
    int sum = 0;
    cout << "THREAD \t\t\t" << args->num << endl;
    cout << "Limite Inferior:\t" << min << endl;
    cout << "Limite superior:\t" << max << endl;

    // https://www.rookieslab.com/posts/fastest-way-to-check-if-a-number-is-prime-or-not
    bool isPrime;
    for(int now = min; now < max; now++){
        isPrime = true;
        if(now <= 1)
            isPrime = false;
        int i = 2;
        while(i*i <= now) {
            if (now % i == 0)
                isPrime = false;
            i++;
        }

        // IF IT'S PRIME IT SHOULD BE PRINTED AND ADDED TO THE SUM
        if(isPrime){
            sum += now;
            cout << now << endl;
        }
    }
    args->sum = sum;
    cout << "Suma hilo:\t\t" << sum << endl;
    separator();
    pthread_exit(nullptr);
}

int main() {
    // ASKS USER'S INPUT
    separator();
    int max = askMax();
    int nThreads = askThreads();
    separator();

    // CREATES THE THREADS, THREADS PARAMETERS AND GETS THE LIMITS
    int numsPerThread = max / nThreads;
    threadParameters paramArray[nThreads];

    pthread_t threads[nThreads];
    // IF THERE'S MORE THAN 1 THREAD
    int residue;
    int totalSum = 0;
    for(int i = 0; i < nThreads; i++) {
        // PREPARES THE THREADS PARAMETERS
        residue = 0;
        // IF IT'S THE LAST THREAD AND THERE'S MISSING NUMBERS TO CHECK
        if ((i == (nThreads - 1)) && (numsPerThread * nThreads < max)) {
            residue = max - (numsPerThread * nThreads);
        }
        paramArray[i].num = i;
        paramArray[i].min = i * numsPerThread;
        paramArray[i].max = ((i + 1) * numsPerThread) + residue;

        pthread_create(&threads[i], nullptr, checkPrimes, (void *) &paramArray[i]);
        pthread_join(threads[i], nullptr);
        totalSum += paramArray[i].sum;
    }
    cout << "Suma TOTAL:\t\t" << totalSum << endl;
    return 0;
}
