/*
範例三（高階）：Distributed Job Orchestrator

（偏 Google / Meta style）

題目描述

Design a distributed job orchestrator where:

Jobs have dependencies

Jobs have priorities

Workers pull executable jobs

Jobs can fail, retry, or timeout.

Requirements

Only dispatch jobs whose dependencies are completed

Always dispatch highest-priority ready jobs

System must be horizontally scalable

Expected Discussion

Metadata storage (DB vs in-memory)

Leader election

Shard by job ID

Exactly-once vs at-least-once execution

Interview Focus

Distributed systems

State machines

Scalability trade-offs
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>
#include <stdexcept>

using namespace std;

enum class JobState { PENDING, RUNNING, COMPLETED, FAILED };

struct Job {
    string id;
    int priority;
    int retriesLeft;
    JobState state = JobState::PENDING;
};

struct JobComparator {
    unordered_map<string, Job>* jobs;
    bool operator()(const string& a, const string& b) const {
        return (*jobs)[a].priority > (*jobs)[b].priority;
    }
};

class JobOrchestrator {
    unordered_map<string, Job> jobs;
    unordered_map<string, vector<string>> graph;
    unordered_map<string, int> indegree;

    // Min-heap by priority
    /*auto cmp = [&](const string& a, const string& b) {
        return jobs[a].priority > jobs[b].priority;
    };*/
    JobComparator cmp;
    priority_queue<string, vector<string>, decltype(cmp)> readyQueue;
public:
    JobOrchestrator() : cmp{&jobs}, readyQueue(cmp) {}
    
    void addJob(const string& id, int priority, int retries = 1) {
        jobs[id] = {id, priority, retries, JobState::PENDING};
        indegree[id] = 0;
    }
    void addDependency(const string& before, const string& after) {
        graph[before].push_back(after);
        indegree[after]++;
    }
    
    // Intialize ready queue
    void initialize() {
        for (auto& [id, deg] : indegree) {
            if (deg == 0) {
                readyQueue.push(id);
            }
        }
    }
    
    // Worker pulls a job
    string dispatchJob() {
        if (readyQueue.empty()) {
            return "";
        }
        string jobId = readyQueue.top();
        readyQueue.pop();
        
        jobs[jobId].state = JobState::RUNNING;
        return jobId;
    }
    
    // Mark job sucess
    void completeJob(const string& jobId) {
        jobs[jobId].state = JobState::COMPLETED;
        
        for (const auto& next : graph[jobId]) {
            if (--indegree[next] == 0) {
                readyQueue.push(next);
            }
        }
    }
    
    void failJob(const string& jobId) {
        Job& job = jobs[jobId];
        
        if (job.retriesLeft > 0) {
            job.retriesLeft--;
            job.state = JobState::PENDING;
            readyQueue.push(jobId); 
        } else {
            job.state = JobState::FAILED;
        }
    }
    
    bool allDone() const {
        for (const auto& [_, job] : jobs) {
            if (job.state != JobState::COMPLETED && job.state != JobState::FAILED) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    JobOrchestrator orchestrator;
    
    orchestrator.addJob("JobA", 1);
    orchestrator.addJob("JobB", 2);
    orchestrator.addJob("JobC", 3);
    orchestrator.addJob("JobD", 4);
    
    orchestrator.addDependency("JobA", "JobB");
    orchestrator.addDependency("JobA", "JobC");
    orchestrator.addDependency("JobB", "JobD");
    
    orchestrator.initialize();
    
    while (!orchestrator.allDone()) {
        string job = orchestrator.dispatchJob();
        if (job.empty()) break;
        
        cout << "Worker executing: " << job << endl;
        
        // Simulate success/failure
        if (job == "JobB") {
            cout << "JobB failed, retrying...\n";
            orchestrator.failJob(job);
        } else {
            orchestrator.completeJob(job);
        }
    }
    cout << "All jobs finished\n";
}
