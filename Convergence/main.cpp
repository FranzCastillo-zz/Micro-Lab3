using namespace std;

#include <iostream>

void separator() {
    cout << "-----------------------------------------------------------" << endl;
}

int askN() {
    separator();
    cout << "Ingrese el valor 'n' a evaluar: " << endl;
    int temp;
    cin >> temp;
    separator();
    return temp;
}

void *calcValue(void *arg) {
    int n = *(int *) arg;
    auto *value = new double;
    *value = 1.0 / (n * (n + 1));
    cout << "[i = " << n << "]\t" << *value << endl;
    pthread_exit(value);
}

int main() {
    // GETS USER INPUT
    int n = askN();

    // STORES THE THREAD ID, THE EXIT VALUE FOR THE pthread_join AND THE CONVERGENCE VALUE OF THE SUM
    pthread_t thread;
    double *exitValue;
    double convergenceValue = 0;

    for (long i = 1; i <= n; i++) {
        pthread_create(&thread, nullptr, &calcValue, &i);
        pthread_join(thread, (void **) &exitValue);
        convergenceValue += *exitValue;
    }
    separator();
    cout << "El valor de convergencia de la serie geometrica es: " << convergenceValue << endl;

    delete exitValue;
    return 0;
}
