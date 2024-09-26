//1. process scheduling algorithm using FIFO approach
 
#include <stdio.h>
 
struct Process {
    int pid;        // Process ID
    int arrivalTime;  // Arrival time
    int burstTime;    // Burst time
    int waitingTime;  // Waiting time
    int turnaroundTime; // Turnaround time
};
 
void calculateTimes(struct Process p[], int n) {
    int totalWaitingTime = 0, totalTurnaroundTime = 0;
    p[0].waitingTime = 0;  // First process has no waiting time
    p[0].turnaroundTime = p[0].burstTime;  // Turnaround time is burst time
 
    // Calculate waiting time and turnaround time for each process
    for (int i = 1; i < n; i++) {
        p[i].waitingTime = p[i-1].waitingTime + p[i-1].burstTime;
        p[i].turnaroundTime = p[i].waitingTime + p[i].burstTime;
    }
 
    // Calculate total waiting time and total turnaround time
    for (int i = 0; i < n; i++) {
        totalWaitingTime += p[i].waitingTime;
        totalTurnaroundTime += p[i].turnaroundTime;
    }
 
    // Display results
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrivalTime, p[i].burstTime, p[i].waitingTime, p[i].turnaroundTime);
    }
 
    printf("\nAverage Waiting Time: %.2f", (float)totalWaitingTime / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)totalTurnaroundTime / n);
}
 
int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
 
    struct Process p[n];
 
    // Input process information
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", p[i].pid);
        scanf("%d %d", &p[i].arrivalTime, &p[i].burstTime);
    }
 
    // Sorting by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].arrivalTime > p[j].arrivalTime) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
 
    // Calculate and display times
    calculateTimes(p, n);
 
    return 0;
}
 
//input
Enter the number of processes: 3
Enter arrival time and burst time for process 1: 0 4
Enter arrival time and burst time for process 2: 1 3
Enter arrival time and burst time for process 3: 2 1
 
//2. Banker's algorithm
 
#include <stdio.h>
 
int main() {
    int n, m, i, j, k;
 
    // n: number of processes, m: number of resource types
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resource types: ");
    scanf("%d", &m);
 
    // Allocation matrix (the resources currently allocated to each process)
    int allocation[n][m];
 
    // Maximum matrix (the maximum demand of each process)
    int maximum[n][m];
 
    // Available vector (the available resources for each resource type)
    int available[m];
 
    // Need matrix (the remaining resource need of each process)
    int need[n][m];
 
    // Finish array (to check if process is finished)
    int finish[n];
 
    // Safe sequence
    int safeSequence[n];
    int count = 0;
 
    // Input Allocation matrix
    printf("\nEnter the Allocation matrix:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        for (j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }
 
    // Input Maximum matrix
    printf("\nEnter the Maximum matrix:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        for (j = 0; j < m; j++) {
            scanf("%d", &maximum[i][j]);
        }
    }
 
    // Input Available resources
    printf("\nEnter the Available resources:\n");
    for (i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }
 
    // Calculate the Need matrix (Need = Maximum - Allocation)
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
 
    // Initialize Finish array to 0 (false), meaning no process is finished
    for (i = 0; i < n; i++) {
        finish[i] = 0;
    }
 
    // Banker's Algorithm
    while (count < n) {
        int found = 0;
        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {  // If process is not yet finished
                for (j = 0; j < m; j++) {
                    if (need[i][j] > available[j]) {
                        break;  // Resources can't be allocated
                    }
                }
                if (j == m) {  // All resources can be allocated
                    // Add the allocated resources of this process to the available resources
                    for (k = 0; k < m; k++) {
                        available[k] += allocation[i][k];
                    }
                    safeSequence[count++] = i;
                    finish[i] = 1;  // Mark the process as finished
                    found = 1;
                }
            }
        }
        if (found == 0) {
            printf("System is in an unsafe state.\n");
            return 0;
        }
    }
 
    // Safe sequence found
    printf("\nSystem is in a safe state.\nSafe sequence is: ");
    for (i = 0; i < n; i++) {
        printf("P%d ", safeSequence[i] + 1);
    }
    printf("\n");
 
    return 0;
}
 
//input
Enter the number of processes: 5
Enter the number of resource types: 3
 
Enter the Allocation matrix:
Process 1: 0 1 0
Process 2: 2 0 0
Process 3: 3 0 2
Process 4: 2 1 1
Process 5: 0 0 2
 
Enter the Maximum matrix:
Process 1: 7 5 3
Process 2: 3 2 2
Process 3: 9 0 2
Process 4: 2 2 2
Process 5: 4 3 3
 
Enter the Available resources:
3 3 2
 
//3. Page replacement algorithm using LRU approach
 
#include <stdio.h>
 
int findLRU(int time[], int n) {
    int i, minimum = time[0], pos = 0;
    for (i = 1; i < n; i++) {
        if (time[i] < minimum) {
            minimum = time[i];
            pos = i;
        }
    }
    return pos;
}
 
int main() {
    int no_of_frames, no_of_pages, frames[10], pages[30], counter = 0, time[10], flag1, flag2, i, j, pos, faults = 0;
 
    printf("Enter number of frames: ");
    scanf("%d", &no_of_frames);
 
    printf("Enter number of pages: ");
    scanf("%d", &no_of_pages);
 
    printf("Enter reference string (page numbers): ");
    for (i = 0; i < no_of_pages; i++) {
        scanf("%d", &pages[i]);
    }
 
    // Initialize frames and time
    for (i = 0; i < no_of_frames; i++) {
        frames[i] = -1;
    }
 
    // Page replacement logic
    for (i = 0; i < no_of_pages; i++) {
        flag1 = flag2 = 0;
 
        // Check if page is already in a frame
        for (j = 0; j < no_of_frames; j++) {
            if (frames[j] == pages[i]) {
                counter++;
                time[j] = counter; // Update time for LRU
                flag1 = flag2 = 1;
                break;
            }
        }
 
        // If page is not present in any frame
        if (flag1 == 0) {
            for (j = 0; j < no_of_frames; j++) {
                if (frames[j] == -1) {
                    counter++;
                    frames[j] = pages[i];
                    time[j] = counter;
                    flag2 = 1;
                    faults++;
                    break;
                }
            }
        }
 
        // If no empty frame, replace using LRU
        if (flag2 == 0) {
            pos = findLRU(time, no_of_frames);
            counter++;
            frames[pos] = pages[i];
            time[pos] = counter;
            faults++;
        }
 
        // Print current frame status
        printf("\nFrames: ");
        for (j = 0; j < no_of_frames; j++) {
            if (frames[j] == -1) {
                printf("- ");
            } else {
                printf("%d ", frames[j]);
            }
        }
    }
 
    printf("\n\nTotal Page Faults = %d\n", faults);
    return 0;
}
 
//input
 
Enter number of frames: 3
Enter number of pages: 12
Enter reference string (page numbers): 7 0 1 2 0 3 0 4 2 3 0 3
 
 
//4. Disk scheduling algorithm using shortest seek time first approach.
 
#include <stdio.h>
#include <stdlib.h>
 
int main() {
    int n, i, j, currentHead, totalSeekTime = 0;
 
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);
 
    int requests[n], visited[n];
 
    printf("Enter the disk requests: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
        visited[i] = 0;  // Mark each request as not yet processed
    }
 
    printf("Enter the initial head position: ");
    scanf("%d", &currentHead);
 
    printf("\nSeek Sequence: %d ", currentHead);
 
    // Processing all requests using SSTF
    for (i = 0; i < n; i++) {
        int minDistance = 9999, nextRequest = -1;
 
        // Find the closest request
        for (j = 0; j < n; j++) {
            if (!visited[j]) {
                int distance = abs(requests[j] - currentHead);
                if (distance < minDistance) {
                    minDistance = distance;
                    nextRequest = j;
                }
            }
        }
 
        // Move the head to the closest request
        visited[nextRequest] = 1;
        totalSeekTime += minDistance;
        currentHead = requests[nextRequest];
        printf("-> %d ", currentHead);
    }
 
    printf("\nTotal Seek Time: %d\n", totalSeekTime);
    printf("Average Seek Time: %.2f\n", (float)totalSeekTime / n);
 
    return 0;
}
 
//input
 
Enter the number of disk requests: 8
Enter the disk requests: 176 79 34 60 92 11 41 114
Enter the initial head position: 50
