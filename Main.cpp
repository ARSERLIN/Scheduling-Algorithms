//Mohammadhossein Arsalan  Student ID: 98243005
#include <bits/stdc++.h>
using namespace std;
queue <int> RR_queue;
const long long max_n = 1e7+5;
int arrival [max_n];
int burst [max_n];
int priority [max_n];
int context [max_n];
bool terminated [max_n];
int wait[max_n];
int quantum,n;
static long t = 0;
double round_num(double wait_time){
    double rounded;
    rounded = round(wait_time * 100.0) / 100.0;
    return rounded;
}
void sync_queue(int running){
    for (int i = 1; i <= n; i++){
        if (arrival[i] <= t && wait[i] == -1 && !terminated[i] && i != running){
            RR_queue.push(i);
        }
    }
    
}
bool any_waiting_process(){
     for (int i = 1; i <= n; i++){
        if (!terminated[i]){
            return true;
        }
    }
    return false;
}
int process_number_with_min_burst(){
    int min = 1e7+5;
    int index = -1;
    for (int i = 1; i <= n; i++){
        if (burst[i] < min && arrival[i] <= t && !terminated[i]){
            min = burst[i];
            index = i;
        }
    }
    return index;
}
int process_number_with_high_priority(){
    int min = 1e7+5;
    int index = -1;
    for (int i = 1; i <= n; i++){
        if (priority[i] < min && arrival[i] <= t && !terminated[i]){
            min = priority[i];
            index = i;
        }
    }
    return index;
}
void avg_wait_RR(){
    long double wait_time = 0;
    for (int i = 1; i <= n; i++){
        wait_time += wait[i];
    }
    wait_time /= n;
    wait_time = round_num(wait_time);
    cout << "AVG Waiting Time: " << wait_time << "\n";
}
void avg_wait_SJF(){
    long double wait_time = 0;
    for (int i = 1; i <= n; i++){
        wait_time += wait[i] - arrival[i];
    }
    wait_time /= n;
    wait_time = round_num(wait_time);
    cout << "AVG Waiting Time: " << wait_time << "\n";
}
void avg_wait_PR_NP(){
    long double wait_time = 0;
    for (int i = 1; i <= n; i++){
        wait_time += wait[i] - arrival[i];
    }
    wait_time /= n;
    wait_time = round_num(wait_time);
    cout << "AVG Waiting Time: " << wait_time << "\n";
}
void avg_wait_PR_P(){
    long double wait_time = 0;
    for (int i = 1; i <= n; i++){
        wait_time += wait[i];
    }
    wait_time /= n;
    wait_time = round_num(wait_time);
    cout << "AVG Waiting Time: " << wait_time << "\n";
}
void RR(){
    int time_quantum = 0;
    int running_process = -1;
    int old_running_p = -1;
    bool quantum_reached = true;
    bool current_process_terminated = true;
       while (any_waiting_process()){
               sync_queue(running_process);
               if (quantum_reached || current_process_terminated){
                    if (running_process != -1 && !terminated[running_process]){
                    RR_queue.push(running_process);  
                    }
                    time_quantum = 0;                     
                    quantum_reached = false;
                    current_process_terminated = false;
                    running_process = RR_queue.front();
                    RR_queue.pop();
                    while (terminated[running_process]){
                    running_process = RR_queue.front();
                    RR_queue.pop();
                    }
                    
                    context[old_running_p] = t;
                    old_running_p = running_process;
                   if (wait[running_process] == -1){
                       wait[running_process] = t - arrival[running_process];
                   }else{
                       wait[running_process] += t - context[running_process]; 
                   }
                   cout << t << " " << running_process << "\n";
               }
           burst[running_process] -= 1;
           if (burst[running_process] == 0){
               terminated[running_process] = true;
               current_process_terminated = true;
           }
           time_quantum++; 
           if (time_quantum == quantum){
               quantum_reached = true;
           }
           t++;
       }

}
void SJF(){
    int running_process = -1;
    bool current_process_terminated = true;
    while (any_waiting_process()){
        if (current_process_terminated){        
            running_process = process_number_with_min_burst();
            if (running_process != -1){
                current_process_terminated = false;
                if (wait[running_process] == -1){
                    wait[running_process] = t;
                }
                cout << t << " " << running_process << "\n";
            }
        }
        burst[running_process] -= 1;
        if (burst[running_process] == 0){
            terminated[running_process] = true;
            current_process_terminated = true;
        }
        
        t++;
    }
    
}
void PR_P(){
    int running_process = -1;
    int old_running_p = -1;
       while (any_waiting_process()){        
               running_process = process_number_with_high_priority();
               if (running_process != old_running_p){
                       context[old_running_p] = t;
                       old_running_p = running_process;
                   if (wait[running_process] == -1){
                       wait[running_process] = t - arrival[running_process];
                   }else{
                       wait[running_process] += t - context[running_process]; 
                   }
                   cout << t << " " << running_process << "\n";
               }
           burst[running_process] -= 1;
           if (burst[running_process] == 0){
               terminated[running_process] = true;
           }

           t++;
       }

}
void PR_NP(){
    int running_process = -1;
    bool current_process_terminated = true;
    while (any_waiting_process()){
        if (current_process_terminated){        
            running_process = process_number_with_high_priority();
            if (running_process != -1){
                current_process_terminated = false;
                if (wait[running_process] == -1){
                    wait[running_process] = t;
                }
                cout << t << " " << running_process << "\n";
            }
        }
        burst[running_process] -= 1;
        if (burst[running_process] == 0){
            terminated[running_process] = true;
            current_process_terminated = true;
        }
        
        t++;
    }
    
}
int main(){
    string algorithm;
    cin >> algorithm;
    if (algorithm == "RR"){
        cin >> quantum;
    }
    int process_number;
    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> process_number;
        cin >> arrival[process_number];
        cin >> burst[process_number];
        cin >> priority[process_number];
        terminated[process_number] = false;
        wait[process_number] = -1;
        context[process_number] = -1;
    }
    
    if(algorithm == "RR"){
        cout<< "RR" << " " << quantum << "\n";
        RR();
        avg_wait_RR();
    }else if(algorithm == "SJF"){
        cout<< "SJF" << "\n";
        SJF();
        avg_wait_SJF();
    }else if(algorithm == "PR_withPREMP"){
        cout<< "PR_withPREMP" << "\n";
        PR_P();
        avg_wait_PR_P();
    }else {
        cout<< "PR_noPREMP" << "\n";
        PR_NP();
        avg_wait_PR_NP();
    }
    
    return 0;
}