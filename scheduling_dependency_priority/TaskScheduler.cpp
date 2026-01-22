/*
範例一（入門）：Priority-based Topological Scheduler
題目描述

Design and implement a scheduler that executes tasks based on:

Dependency constraints

Task priority

Each task may depend on other tasks, and a task can only be executed after all its dependencies are completed.

When multiple tasks are available to run, the scheduler must always pick the task with the highest priority.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>

using namespace std;

class TaskScheduler {
    unordered_map<string, vector<string>> graph;
    unordered_map<string, int> indegree;
    unordered_map<string, int> priority;
public:
    void addTask(const string& taskId, int p) {
        priority[taskId] = p;
        if (!indegree.count(taskId)) {
            indegree[taskId] = 0;
        }
    }
    void addDependency(const string& before, const string& after) {
        graph[before].push_back(after);
        indegree[after]++;
    }
    
    vector<string> getExecutionOrder() {
        // min-heap based on priority
        auto cmp = [&](const string& a, const string& b) {
            return priority[a] > priority[b];
        };
        priority_queue<string, vector<string>, decltype(cmp)> pq(cmp);
        
        // push all tasks with indegree = 0
        for (auto& [task, deg] : indegree) {
            if (deg == 0) {
                pq.push(task);
            }
        }
        
        vector<string> res;
        
        while (!pq.empty()) {
            string cur = pq.top();
            pq.pop();
            res.push_back(cur);
            
            for (const string& next : graph[cur]) {
                if (--indegree[next] == 0) {
                    pq.push(next);
                }
            }
        }
        
        if (res.size() != priority.size()) {
            throw runtime_error("Cycle detected in task dependencies");
        }
        return res;
    }
};

int main() {
    TaskScheduler scheduler;
    
    scheduler.addTask("A", 1);
    scheduler.addTask("B", 2);
    scheduler.addTask("C", 3);
    scheduler.addTask("D", 4);
    
    scheduler.addDependency("A", "B");
    scheduler.addDependency("A", "C");
    scheduler.addDependency("C", "B");
    scheduler.addDependency("B", "D");
    
    auto order = scheduler.getExecutionOrder();
    
    for (auto& s : order) {
        cout << s << " ";
    }
    return 0;
}
