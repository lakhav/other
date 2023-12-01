#include <iostream>
#include <algorithm>

using namespace std;

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

bool compareArrivalTime(Process a, Process b) {
    return a.arrivalTime < b.arrivalTime;
}

bool compareBurstTime(Process a, Process b) {
    return a.burstTime < b.burstTime;
}

int main() {
    int arrivalTimes[] = {3, 1, 4, 0, 2};
    int burstTimes[] = {1, 4, 2, 6, 3};
    const int n = sizeof(arrivalTimes) / sizeof(arrivalTimes[0]);

    Process processes[n];
	
	cout<<"==Shortest Job First=="<<"\n\n";
	
    for (int i = 0; i < n; ++i) {
        processes[i].pid = i + 1;
        processes[i].arrivalTime = arrivalTimes[i];
        processes[i].burstTime = burstTimes[i];
    }

    sort(processes, processes + n, compareArrivalTime);

    int currentTime = 0;
    float totalWaitingTime = 0;

    cout << "pid\tAT\tBT\tCT\tTAT\tWT" << endl;

    for (int i = 0; i < n; ++i)  // It iterates through the list of processes.
    {
        int shortest = i;

        //This nested loop compares the burst times of subsequent processes after the current process.
        //-`shortest` initially holds the index of the current process (`i`).
        // It looks for a process with a shorter burst time than the current `shortest` process.
        for (int j = i + 1; j < n; ++j)  
        {
            if (processes[j].arrivalTime <= currentTime && processes[j].burstTime < processes[shortest].burstTime)
            {
                shortest = j;
            }
        }

        currentTime += processes[shortest].burstTime;
        processes[shortest].completionTime = currentTime;
        processes[shortest].turnaroundTime = processes[shortest].completionTime - processes[shortest].arrivalTime;
        processes[shortest].waitingTime = processes[shortest].turnaroundTime - processes[shortest].burstTime;

        totalWaitingTime += processes[shortest].waitingTime;

        swap(processes[i], processes[shortest]);
    }

    for (int i = 0; i < n; ++i)
    {
        cout << processes[i].pid << "\t" << processes[i].arrivalTime << "\t"
             << processes[i].burstTime << "\t" << processes[i].completionTime << "\t"
             << processes[i].turnaroundTime << "\t" << processes[i].waitingTime << endl;
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

