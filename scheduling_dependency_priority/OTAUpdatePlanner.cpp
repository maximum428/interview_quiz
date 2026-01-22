/*
題目描述

You are designing an Automotive OTA update system.

A vehicle contains multiple ECUs.
Some ECUs must be updated before others due to firmware compatibility and safety constraints.

Each ECU also has a criticality level:

Safety-critical ECUs must be updated earlier when possible

Input

ECU dependency graph

ECU priority (lower number = higher criticality)

Output

Return a safe OTA update sequence that:

Respects all dependency constraints

Prioritizes safety-critical ECUs whenever possible
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>
#include <stdexcept>

using namespace std;

class OTAUpdatePlanner {
    unordered_map<string, vector<string>> graph;
    unordered_map<string, int> criticality;
    unordered_map<string, int> indegree;
public:
    void addECU(const string& ecuId, int level) {
        criticality[ecuId] = level;
        if (!indegree.count(ecuId)) {
            indegree[ecuId] = 0;
        }
    }
    
    void addDependency(const string& before, const string& after) {
        graph[before].push_back(after);
        indegree[after]++;
    }
    
    vector<string> planUpdateOrder() {
        auto cmp = [&](const string& a, const string& b) {
            return criticality[a] > criticality[b];
        };
        
        priority_queue<string, vector<string>, decltype(cmp)> pq(cmp);
        
        for (auto& [ecu, deg] : indegree) {
            if (deg == 0) {
                pq.push(ecu);
            }
        }
        
        vector<string> updateOrder;
        
        while (!pq.empty()) {
            string curr = pq.top();
            pq.pop();
            updateOrder.push_back(curr);
            
            for (const string& next : graph[curr]) {
                if (--indegree[next] == 0)
                    pq.push(next);
            }
        }
        
        if (updateOrder.size() != criticality.size()) {
            throw runtime_error("Invalid OTA plan: dependency cycle detected");
        }
        return updateOrder;
    }
};

int main() {
    OTAUpdatePlanner planner;
    
    // ECU criticality (lower = more critical)
    planner.addECU("BCM", 1);
    planner.addECU("ADAS", 2);
    planner.addECU("IVI", 3);
    planner.addECU("TCU", 4);
    
    // Dependencis
    planner.addDependency("BCM", "ADAS");
    planner.addDependency("ADAS", "IVI");
    planner.addDependency("BCM", "TCU");
    
    auto order = planner.planUpdateOrder();
    
    for (auto& ecu : order) {
        cout << ecu << " ";
    }
    return 0;
}
