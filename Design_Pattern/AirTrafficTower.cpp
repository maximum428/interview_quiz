/*
整體架構鳥瞰圖（先畫這張）
                +------------------+
                |  AirTrafficTower |
                |   (Mediator)     |
                +------------------+
                 ^       ^       ^
                 |       |       |
        +--------+       |       +---------+
        |                |                 |
+---------------+  +---------------+  +---------------+
|     Plane     |  |     Plane     |  |     Plane     |
| (Colleague)   |  | (Colleague)   |  | (Colleague)   |
+---------------+  +---------------+  +---------------+
        |
        v
+------------------+
|  FlightState     |   <--- State Pattern
+------------------+

AirTrafficTower ---> RadarDisplay      (Observer)
AirTrafficTower ---> WeatherSystem     (Observer)
AirTrafficTower ---> AlarmSystem       (Observer)


整合後「完整 UML 關係圖」
                  <<Mediator>>
              AirTrafficMediator
                       ▲
                       |
              +------------------+
              | AirTrafficTower  |
              |------------------|
              | observers        |
              | planes           |
              +------------------+
                ^            ^
                |            |
        observes |            | mediates
                |            |
     +----------------+   +----------------+
     | TowerObserver  |   |     Plane      |
     +----------------+   |----------------|
        ▲        ▲        | - state        |
        |        |        | - mediator     |
+-----------+ +-----------+ +----------------+
| Radar     | | Alarm     | |  FlightState   |
+-----------+ +-----------+ +----------------+
                                       ▲
                      --------------------------------
                      |        |        |             |
                +-----------+ +-----------+ +-----------+
                | OnGround  | | InAir     | | Landing   |
                +-----------+ +-----------+ +-----------+
*/

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

// Forward declarations
class Plane;
class PlaneState;

/*=====================
 Observer Interfaces
======================*/
class TowerObserver {
public:
    virtual ~TowerObserver() = default;
    virtual void update(const string& message) = 0;
};

/*=====================
 Mediator (Tower)
======================*/
class Tower {
    unordered_set<Plane*> m_planes;
    vector<TowerObserver*> m_observers;
    bool m_runwayAvailable = true;
    
    void notify(const string& msg) {
        for (const auto& observer : m_observers) {
            observer->update(msg);
        }
    }
public:
    void registerPlane(Plane* plane);
    void addObserver(TowerObserver* observer) {
        m_observers.push_back(observer);
    }
    bool requestTakeoff(Plane* plane);
    bool requestLanding(Plane* plane);
    void clearRunway();
};

/*===========================
 Plane (Context)
============================*/
class Plane {
    string m_name;
    Tower* m_tower{};
    unique_ptr<PlaneState> m_state;
public:
    explicit Plane(string name);
    void setTower(Tower* tower) { m_tower = tower; }
    Tower* getTower() { return m_tower; }
    string getName() const { return m_name; }
    
    void setState(unique_ptr<PlaneState> state);
    void requestTakeoff();
    void requestLanding();
};

/*=======================
 State Interface
========================*/
class PlaneState {
public:
    virtual ~PlaneState() = default;
    virtual void takeoff(Plane* plane) = 0;
    virtual void land(Plane* plane) = 0;
};

/*======================
 Concrete States
=======================*/
class OnGroundState : public PlaneState {
public:
    void takeoff(Plane* plane) override;
    void land(Plane* plane) override {
        cout << plane->getName() << " already on ground.\n";
    }
};

class InAirState : public PlaneState {
public:
    void takeoff(Plane* plane) override {
        cout << plane->getName() << " already in air.\n";
    }
    void land(Plane* plane) override;
};

/*===========================
 Tower Implementations
=========================*/
void Tower::registerPlane(Plane* plane) {
    m_planes.insert(plane);
    plane->setTower(this);
}

bool Tower::requestTakeoff(Plane* plane) {
    if (!m_runwayAvailable) {
        notify("X - Takeoff denied for " + plane->getName());
        return false;
    }
    m_runwayAvailable = false;
    notify("Takeoff approved for " + plane->getName());
    return true;
}

bool Tower::requestLanding(Plane* plane) {
    if (!m_runwayAvailable) {
        notify("X - Landing denifed for " + plane->getName());
        return false;
    }
    m_runwayAvailable= false;
    notify("Landing approved for " + plane->getName());
    return true;
};

void Tower::clearRunway() {
    m_runwayAvailable = true;
    notify("Runway is now clear\n");
}

/*=====================
 Plane Implementations
======================*/
Plane::Plane(string name) : m_name(name), m_state(make_unique<OnGroundState>()) {}

void Plane::setState(unique_ptr<PlaneState> state) {
    m_state = std::move(state);
}

void Plane::requestTakeoff() {
    m_state->takeoff(this);
}

void Plane::requestLanding() {
    m_state->land(this);
}

/*====================
 State Logic
=====================*/
void OnGroundState::takeoff(Plane* plane) {
    cout << plane->getName() << "  requests takeoff.\n";
    if (plane->getTower()->requestTakeoff(plane)) {
        plane->setState(make_unique<InAirState>());
        plane->getTower()->clearRunway();
    }
}

void InAirState::land(Plane* plane) {
    cout << plane->getName() << " request landing.\n";
    if (plane->getTower()->requestLanding(plane)) {
        plane->setState(make_unique<OnGroundState>());
        plane->getTower()->clearRunway();
    }
};

/*==================
 Concrete Observers
====================*/
class RadarDisplay : public TowerObserver {
public:
    void update(const string& message) override {
        cout << "[Radar] " << message << endl;
    }
};

class ControlTowerDisplay : public TowerObserver {
public:
    void update(const string& message) override {
        cout << "[Display] " << message << endl;
    }
};

int main() {
    Tower tower;
    
    RadarDisplay radar;
    ControlTowerDisplay display;
    
    tower.addObserver(&radar);
    tower.addObserver(&display);
    
    Plane plane1("Flight-101");
    Plane plane2("Flight-202");
    
    tower.registerPlane(&plane1);
    tower.registerPlane(&plane2);
    
    plane1.requestTakeoff();
    plane2.requestTakeoff();  // denied
    plane1.requestLanding();
    plane2.requestLanding();  // now allowed
    
    return 0;
}
