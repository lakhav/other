#include <iostream>
#include <algorithm>

using namespace std;

struct Process
{
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    bool completed;
};

bool compareArrivalTime(Process a, Process b)
{
    return a.arrivalTime < b.arrivalTime;
}

int main()
{
    int arrivalTimes[] = {3, 1, 4, 0, 2};
    int burstTimes[] = {1, 4, 2, 6, 3};
    const int n = sizeof(arrivalTimes) / sizeof(arrivalTimes[0]);

    Process processes[n];

    cout << "=======SRTF=========\n\n";

    for (int i = 0; i < n; ++i)
    {
        processes[i].pid = i + 1;
        processes[i].arrivalTime = arrivalTimes[i];
        processes[i].burstTime = burstTimes[i];
        processes[i].remainingTime = burstTimes[i];
        processes[i].completed = false;
    }

    sort(processes, processes + n, compareArrivalTime);

    int currentTime = 0;
    int completedProcesses = 0;
    cout << "pid\tAT\tBT\tCT\tTAT\tWT" << endl;

    while (completedProcesses < n)
    {
        int shortest = -1;
        int shortestTime = INT_MAX;

        for (int i = 0; i < n; ++i)
        {
            if (processes[i].arrivalTime <= currentTime && processes[i].completed ==false &&
                processes[i].remainingTime < shortestTime)
            {
                shortest = i;
                shortestTime = processes[i].remainingTime;
            }
        }

        if (shortest == -1)
        {
            currentTime++;
            continue; // moves to the next iteration of the loop without executing the subsequent code inside the loop.
        }

        processes[shortest].remainingTime--;

        if (processes[shortest].remainingTime == 0)
        {
            completedProcesses++;
            processes[shortest].completionTime = currentTime + 1;
            processes[shortest].turnaroundTime = processes[shortest].completionTime - processes[shortest].arrivalTime;
            processes[shortest].waitingTime = processes[shortest].turnaroundTime - processes[shortest].burstTime;
            processes[shortest].completed = true;
            cout << processes[shortest].pid << "\t" << processes[shortest].arrivalTime << "\t"
                 << processes[shortest].burstTime << "\t" << processes[shortest].completionTime << "\t"
                 << processes[shortest].turnaroundTime << "\t" << processes[shortest].waitingTime << endl;
        }

        currentTime++;
    }

    float totalWaitingTime = 0;
    for (int i = 0; i < n; ++i)
    {
        totalWaitingTime += processes[i].waitingTime;
    }
    float averageWaitingTime = totalWaitingTime / n;
    cout << "Average Waiting Time: " << averageWaitingTime << endl;

    cout << "Execution Sequence: ";
    for (int i = 0; i < n; ++i)
    {
        cout << "P" << processes[i].pid << " ";
    }
    cout << endl;

    return 0;
}
