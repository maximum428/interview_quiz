/*
Elevator System — 完整 UML（白板等級）

核心 Patterns：

State（電梯狀態）

Strategy（排程策略）

Command（按鈕請求）

Observer（顯示 / 監控）

Mediator（多電梯協調）

🧩 一、整體架構（先畫這個）
+---------------------+
| ElevatorController  |  <<Mediator>>
+---------------------+
| - elevators[]       |
| - strategy          |
+---------------------+
| + requestElevator() |
| + assignRequest()   |
+----------+----------+
           |
           | controls
           v
     +-----------+
     | Elevator  |  <<Context>>
     +-----------+
     | - state   |----------------------+
     | - queue   |                      |
     | - observers[]                    |
     +-----------+                      |
     | + move()  |                      |
     | + open()  |                      |
     | + close() |                      |
     +-----------+                      |
           |                             |
           | has                         |
           v                             |
   +-----------------+                  |
   | ElevatorState   |  <<State>>       |
   +-----------------+                  |
   | + handle()      |                  |
   +-----------------+                  |
    ^        ^        ^                  |
    |        |        |                  |
+--------+ +--------+ +----------+      |
| Idle   | | Moving | | DoorOpen |      |
+--------+ +--------+ +----------+      |
                                         |
                                         |
       +------------------+              |
       | Observer         | <<Observer>> |
       +------------------+              |
       | + update()       |              |
       +------------------+              |
        ^              ^                 |
        |              |                 |
+-------------+ +----------------+       |
| DisplayPanel| | ControlCenter  |       |
+-------------+ +----------------+       |

🧠 二、State Pattern（一定要畫清楚 ⭐）
           +--------------------+
           |   ElevatorState    | <<interface>>
           +--------------------+
           | + onRequest()      |
           | + onArrive()       |
           +--------------------+
                    ^
     ------------------------------------
     |           |            |         |
+--------+  +------------+ +-----------+ +-------------+
| Idle   |  | MovingUp   | | MovingDown| | DoorOpen    |
+--------+  +------------+ +-----------+ +-------------+


📌 白板講解重點

同一個 request

在不同 state → 行為不同

消除 if/else

🧠 三、Strategy Pattern（排程算法）
+----------------------------+
| SchedulingStrategy         | <<Strategy>>
+----------------------------+
| + nextFloor(requests)      |
+----------------------------+
           ^
   -------------------------
   |                       |
+---------+          +------------+
| SCAN    |          | Nearest    |
+---------+          +------------+


📌 面試官聽到會點頭：

We can switch scheduling strategies at runtime without modifying elevator logic.

🧠 四、Command Pattern（按鈕 = 請求）
+------------------+
| Command          | <<Command>>
+------------------+
| + execute()      |
+------------------+
        ^
        |
+----------------------+
| FloorRequestCommand  |
+----------------------+
| - floor              |
| - direction          |
+----------------------+


📌 為什麼用？

Queue

Replay

Logging

🧠 五、Observer Pattern（顯示 / 監控）
+------------------+
| Observer         |
+------------------+
| + update()       |
+------------------+
        ^
        |
--------------------------
|                        |
+-------------+   +----------------+
| DisplayPanel|   | MonitoringSys  |
+-------------+   +----------------+

Elevator ----notify()----> Observer


📌 狀態變化自動同步

🧠 六、Mediator（多電梯必加）
          +-----------------------+
          | ElevatorController    | <<Mediator>>
          +-----------------------+
          | + assignRequest()     |
          +-----------------------+
             ^        ^        ^
             |        |        |
         +-------+ +-------+ +-------+
         |Elev A | |Elev B | |Elev C |
         +-------+ +-------+ +-------+


📌 電梯彼此 不直接溝通

🧠 七、Facade（可選加分）
Client
  |
  v
+------------------+
| ElevatorSystem   | <<Facade>>
+------------------+
| + requestElev()  |
+------------------+

🧠 八、白板畫圖順序（超重要）

1️⃣ 畫 Elevator + State
2️⃣ 接 Strategy（排程）
3️⃣ 加 Command（按鈕）
4️⃣ 加 Observer（顯示）
5️⃣ 最後加 Mediator（多電梯）

👉 不要一次畫爆，會被打斷
*/

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <string>

using namespace std;

/* ==== Observer ==== */
class Observer {
public:
    virtual ~Observer() = default;
    virtual void Update(const string& msg) = 0;
};

class DisplayPanel : public Observer {
public:
    void Update(const string& msg) override {
        cout << "[Display] " << msg << endl;
    }
};

class MonitoringSys : public Observer {
public:
    void Update(const string& msg) override {
        cout << "[Monitor] " << msg << endl;
    }
};

class Elevator;

/* ==== Command ==== */
class Command {
public:
    virtual ~Command() = default;
    virtual void Execute() = 0;
};

class FloorRequestCommand : public Command {
    Elevator* m_elevator;
    int m_floor;
public:
    FloorRequestCommand(Elevator* elevator, int floor)
        : m_elevator(elevator), m_floor(floor) {}

    void Execute() override; /* {
        m_elevator->AddRequest(m_floor);
        m_elevator->HandleState();
    }*/
};

/* ==== Strategy ==== */
class ScheduleStrategy {
public:
    virtual ~ScheduleStrategy() = default;
    virtual int NextFloor(int currentFloor, const vector<int>& requests) = 0;
};

class NearestFloorStrategy : public ScheduleStrategy {
public:
    int NextFloor(int currentFloor, const vector<int>& requests) override {
        if (requests.empty()) return currentFloor;
        int nearest = requests[0];
        int minDist = abs(currentFloor - nearest);
        for (int f : requests) {
            int d = abs(currentFloor - f);
            if (d < minDist) {
                minDist = d;
                nearest = f;
            }
        }
        return nearest;
    }
};

/* ==== State ==== */
class ElevatorState {
public:
    virtual ~ElevatorState() = default;
    virtual void Handle(Elevator& elevator) = 0;
    virtual string Name() = 0;
};

/* ==== Elevator ==== */
class Elevator {
    unique_ptr<ElevatorState> m_state;
    vector<Observer*> m_observers;
    vector<int> m_requests;
    int m_currentFloor{0};

public:
    unique_ptr<ScheduleStrategy> m_strategy;
    Elevator() = default;
    void SetState(unique_ptr<ElevatorState> state) {
        m_state = std::move(state);
    }

    void AddObserver(Observer* observer) {
        m_observers.push_back(observer);
    }

    void Notify(const string& msg) {
        for (auto* observer : m_observers)
            observer->Update(msg);
    }

    int CurrentFloor() const { return m_currentFloor; }

    void AddRequest(int floor) {
        m_requests.push_back(floor);
        Notify("Request added: Floor " + to_string(floor));
    }

    vector<int>& Requests() { return m_requests; }

    void MoveToNextFloor() {
        if (!m_strategy || m_requests.empty()) return;
        int next = m_strategy->NextFloor(m_currentFloor, m_requests);
        cout << "Elevator moving from " << m_currentFloor << " to " << next << endl;
        m_currentFloor = next;
        m_requests.erase(
            remove(m_requests.begin(), m_requests.end(), next),
            m_requests.end()
        );
        Notify("Arrived at floor " + to_string(m_currentFloor));
    }

    void HandleState() {
        if (m_state) m_state->Handle(*this);
    }
    string CurrentStateName() {
        return m_state ? m_state->Name() : "None";
    }
};

/* ==== States Impl ==== */
class DoorOpenState : public ElevatorState {
public:
    void Handle(Elevator& elevator) override;
    string Name() override { return "DoorOpen"; }
};

class MovingState : public ElevatorState {
public:
    void Handle(Elevator& elevator) override {
        elevator.MoveToNextFloor();
        cout << "[State] Moving -> DoorOpen\n";
        elevator.SetState(make_unique<class DoorOpenState>());
    }
    string Name() override { return "Moving"; }
};

class IdleState : public ElevatorState {
public:
    void Handle(Elevator& elevator) override {
        if (!elevator.Requests().empty()) {
            cout << "[State] Idle -> Moving\n";
            elevator.SetState(make_unique<class MovingState>());
        }
    }
    string Name() override { return "Idle"; }
};

void DoorOpenState::Handle(Elevator& elevator) {
    cout << "[State] Door open at floor " << elevator.CurrentFloor() << endl;
    if (elevator.Requests().empty())
        elevator.SetState(make_unique<IdleState>());
    else
        elevator.SetState(make_unique<MovingState>());
}

/* ==== Command Impl ==== */
void FloorRequestCommand::Execute() {
    m_elevator->AddRequest(m_floor);
    m_elevator->HandleState();
}

/* ==== ElevatorController (Mediator) ==== */
class ElevatorController {
    vector<unique_ptr<Elevator>> m_elevators;
public:
    void AddElevator(unique_ptr<Elevator> elevator) {
        m_elevators.push_back(std::move(elevator));
    }

    void RequestElevator(int floor) {
        for (auto& elevator : m_elevators) {
            if (elevator->CurrentStateName() == "Idle") {
                FloorRequestCommand cmd(elevator.get(), floor);
                cmd.Execute();
                return;
            }
        }
        cout << "No idle elevator, request queued\n";
    }
};

/* ==== main ==== */
int main() {
    DisplayPanel display;
    MonitoringSys monitor;

    auto e1 = make_unique<Elevator>();
    e1->m_strategy = make_unique<NearestFloorStrategy>();
    e1->AddObserver(&display);
    e1->AddObserver(&monitor);
    e1->SetState(make_unique<IdleState>());

    ElevatorController controller;
    controller.AddElevator(std::move(e1));

    controller.RequestElevator(5);
    controller.RequestElevator(2);

    return 0;
}
