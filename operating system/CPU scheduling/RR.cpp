#include <iostream>

using namespace std;

void queueUpdation(int queue[], int timer, int arrival[], int n, int maxProcessIndex)
{
    int zeroIndex;
    for (int i = 0; i < n; i++)
    {
        if (queue[i] == 0)
        {
            zeroIndex = i;
            break;
        }
    }
    queue[zeroIndex] = maxProcessIndex + 1;
}

void queueMaintenance(int queue[], int n)
{
    for (int i = 0; (i < n - 1) && (queue[i + 1] != 0); i++)
    {
        int temp = queue[i];
        queue[i] = queue[i + 1];
        queue[i + 1] = temp;
    }
}

void checkNewArrival(int timer, int arrival[], int n, int maxProcessIndex, int queue[])
{
    if (timer <= arrival[n - 1])
    {
        bool newArrival = false;
        for (int j = (maxProcessIndex + 1); j < n; j++)
        {
            if (arrival[j] <= timer)
            {
                if (maxProcessIndex < j)
                {
                    maxProcessIndex = j;
                    newArrival = true;
                }
            }
        }
        if (newArrival)
            queueUpdation(queue, timer, arrival, n, maxProcessIndex);
    }
}

int main()
{
    int n, timeQuantum, timer = 0, maxProcessIndex = 0;
    float avgWait = 0, avgTT = 0;

    cout << "Enter the time quantum: ";
    cin >> timeQuantum;

    int arrivalTimes[] = {0, 1, 2, 3, 4, 6}; // Example arrival times
    int burstTimes[] = {5, 6, 3, 1, 5, 4};   // Example burst times
    n = sizeof(arrivalTimes) / sizeof(arrivalTimes[0]);

    int arrival[n], burst[n], wait[n], turn[n], queue[n], tempBurst[n];
    bool complete[n];

    for (int i = 0; i < n; i++)
    {
        arrival[i] = arrivalTimes[i];
        burst[i] = burstTimes[i];
        tempBurst[i] = burst[i];
        complete[i] = false;
        queue[i] = 0;
    }

    while (timer < arrival[0])
        timer++;

    queue[0] = 1;

    while (true)
    {
        bool flag = true;
        for (int i = 0; i < n; i++)
        {
            if (tempBurst[i] != 0)
            {
                flag = false;
                break;
            }
        }
        if (flag)
            break;

        for (int i = 0; (i < n) && (queue[i] != 0); i++)
        {
            int ctr = 0;
            while ((ctr < timeQuantum) && (tempBurst[queue[0] - 1] > 0))
            {
                tempBurst[queue[0] - 1]--;
                timer++;
                ctr++;
                checkNewArrival(timer, arrival, n, maxProcessIndex, queue);
            }
            if ((tempBurst[queue[0] - 1] == 0) && (complete[queue[0] - 1] == false))
            {
                turn[queue[0] - 1] = timer;
                complete[queue[0] - 1] = true;
            }
            bool idle = true;
            if (queue[n - 1] == 0)
            {
                for (int i = 0; i < n && queue[i] != 0; i++)
                {
                    if (complete[queue[i] - 1] == false)
                    {
                        idle = false;
                    }
                }
            }
            else
                idle = false;
            if (idle)
            {
                timer++;
                checkNewArrival(timer, arrival, n, maxProcessIndex, queue);
            }
            queueMaintenance(queue, n);
        }
    }

    for (int i = 0; i < n; i++)
    {
        turn[i] = turn[i] - arrival[i];
        wait[i] = turn[i] - burst[i];
    }

    cout << "\nProgram No.\tArrival Time\tBurst Time\tWait Time\tTurnAround Time" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << i + 1 << "\t\t" << arrival[i] << "\t\t" << burst[i] << "\t\t" << wait[i] << "\t\t" << turn[i] << endl;
    }

    for (int i = 0; i < n; i++)
    {
        avgWait += wait[i];
        avgTT += turn[i];
    }
    cout << "\nAverage wait time : " << (avgWait / n) << "\nAverage Turn Around Time : " << (avgTT / n);

    return 0;
}
