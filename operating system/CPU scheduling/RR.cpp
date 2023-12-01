#include <iostream>
#include <queue>

using namespace std;

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

int main() {
    int arrivalTimes[] = {0, 1, 2, 3, 4, 6};
    int burstTimes[] = {5, 6, 3, 1, 5, 4};
    const int n = sizeof(arrivalTimes) / sizeof(arrivalTimes[0]);
    const int timeQuantum = 4;

    Process processes[n];

    for (int i = 0; i < n; ++i) {
        processes[i].pid = i + 1;
        processes[i].arrivalTime = arrivalTimes[i];
        processes[i].burstTime = burstTimes[i];
        processes[i].remainingTime = burstTimes[i];
    }

    queue<Process> readyQueue;
    int currentTime = 0;

    cout << "pid\tAT\tBT\tCT\tTAT\tWT" << endl;

    while (true) {
        bool allCompleted = true;

        for (int i = 0; i < n; ++i) {
            if (processes[i].remainingTime > 0) {
                allCompleted = false;

                if (processes[i].remainingTime > timeQuantum) {
                    currentTime += timeQuantum;
                    processes[i].remainingTime -= timeQuantum;
                } else {
                    currentTime += processes[i].remainingTime;
                    processes[i].completionTime = currentTime;
                    processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
                    processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
                    processes[i].remainingTime = 0;

                    cout << processes[i].pid << "\t" << processes[i].arrivalTime << "\t"
                         << processes[i].burstTime << "\t" << processes[i].completionTime << "\t"
                         << processes[i].turnaroundTime << "\t" << processes[i].waitingTime << endl;
                }
            }
        }

        if (allCompleted) {
            break;
        }
    }

    float totalWaitingTime = 0;
    for (int i = 0; i < n; ++i) {
        totalWaitingTime += processes[i].waitingTime;
    }
    float averageWaitingTime = totalWaitingTime / n;
    cout << "Average Waiting Time: " << averageWaitingTime << endl;

    cout << "Execution Sequence: ";
    for (int i = 0; i < n; ++i) {
        cout << "P" << processes[i].pid << " ";
    }
    cout << endl;

    return 0;
}

