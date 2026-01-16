/*
ParkingSession (Subject)
 ├─ ParkingState (State)
 ├─ FeeStrategy (Strategy)
 │    ├─ HourlyFee
 │    └─ DailyMaxFee
 ├─ FeeStrategyFactory (Factory)
 ├─ Observers
 │    ├─ Display
 │    └─ Gate
 └─ Command History
      ├─ PayCommand
      └─ RefundCommand (Undo)
*/

#include <iostream>
#include <memory>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

/* ============ Observer ============ */
class Observer {
public:
    virtual ~Observer() = default;
    virtual void Update(const string& msg) const = 0;
};

class Display : public Observer {
public:
    void Update(const string& msg) const override {
        cout << "[Display] " << msg << endl;
    }
};

class Gate : public Observer {
public:
    void Update(const string& msg) const override {
        if (msg == "PAID") {
            cout << "[Gate] Open gate\n";
        } else if (msg == "REFUND") {
            cout << "[Gate] Close gate\n";
        }
    }
};

/* ============ Strategy ============ */
class FeeStrategy {
public:
    virtual ~FeeStrategy() = default;
    virtual int Calculate(const int hours) = 0;
};

class HourlyFee : public FeeStrategy {
public:
    int Calculate(const int hours) override {
        return hours * 50;
    }
};

class DailyMaxFee : public FeeStrategy {
public:
    int Calculate(const int hours) override {
        return min(hours * 50, 300);
    }
};

/* ============ Factory ============ */
class FeeStrategyFactory {
public:
    static unique_ptr<FeeStrategy> Create(int hours) {
        if (hours >= 6)
            return make_unique<DailyMaxFee>();
        return make_unique<HourlyFee>();
    }
};

class ParkingSession;  // Forward declaration

/* ============ State ============ */
class ParkingState {
public:
    virtual ~ParkingState() = default;
    virtual void Enter(ParkingSession&) {}
    virtual void Pay(ParkingSession&) {}
    virtual void Exit(ParkingSession&) {}
};

class ParkedState : public ParkingState {
public:
    void Pay(ParkingSession& session) override; /* {
        session.ExecuteCommand(make_unique<PayCommand>(session));
    } */
};

class PaidState : public ParkingState {
public:
    void Exit(ParkingSession& session) override; /* {
        cout << "Car exited\n";
        session.SetState(make_unique<ExitedState>());
    } */
};

class ExitedState : public ParkingState {};

/* ============ Command ============ */
class Command {
public:
    virtual ~Command() = default;
    virtual void Execute() = 0;
    virtual void Undo() = 0;
};

/* ============ Context ============ */
class ParkingSession {
    unique_ptr<FeeStrategy> m_strategy;
    unique_ptr<ParkingState> m_state;
    vector<Observer*> m_observers;
    stack<unique_ptr<Command>> m_history;
public:
    int hours;
    bool paid = false;
    
   explicit ParkingSession(int h) : hours(h), m_strategy(FeeStrategyFactory::Create(h)), m_state(make_unique<ParkedState>()) {}
    
    void AddObserver(Observer* observer) {
        m_observers.push_back(observer);
    }
    void Notify(const string& msg) {
        for (const auto& observer : m_observers) {
            observer->Update(msg);
        }
    }
    int Fee() {
        return m_strategy->Calculate(hours);
    }
    void SetState(unique_ptr<ParkingState> state) {
        m_state = std::move(state);
    }
    void ExecuteCommand(unique_ptr<Command> cmd) {
        cmd->Execute();
        m_history.push(std::move(cmd));
    }
    void Undo() {
        if (!m_history.empty()) {
            m_history.top()->Undo();
            m_history.pop();
        }
    }
    void Pay() { m_state->Pay(*this); }
    void Exit() { m_state->Exit(*this); }
};

/* ============ Commands ============ */
class PayCommand : public Command {
    ParkingSession& m_session;
public:
    explicit PayCommand(ParkingSession& session) : m_session(session) {}
    void Execute() override {
        cout << "Pay $" << m_session.Fee() << endl;
        m_session.paid = true;
        m_session.Notify("PAID");
        m_session.SetState(make_unique<PaidState>());
    }
    void Undo() override {
        cout << "Refund $" << m_session.Fee() << endl;
        m_session.paid = false;
        m_session.Notify("REFUND");
        m_session.SetState(make_unique<ParkedState>());
    }
};

/* ============ State Impl ============ */
void ParkedState::Pay(ParkingSession& session) {
    session.ExecuteCommand(make_unique<PayCommand>(session));
}

void PaidState::Exit(ParkingSession& session) {
    cout << "Car exited\n";
    session.SetState(make_unique<ExitedState>());
}

/* ============ main ============ */
int main() {
    cout << "=== Parking System ===\n";
    
    ParkingSession session(8);
    
    Display display;
    Gate gate;
    
    session.AddObserver(&display);
    session.AddObserver(&gate);
    
    session.Pay();  // execute command
    session.Undo(); // refund
    session.Pay();  // pay again
    session.Exit();  // exit
    
    return 0;
}

