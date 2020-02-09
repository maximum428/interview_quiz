/*
The Command Pattern encapsulates a request as an object, thereby letting you parameterize other objects with different requests, 
queue or log requests, and support undoable operations.
*/

#include <iostream>

using namespace std;

class Command {
public:
    virtual void Execute() = 0;
    virtual void Undo() = 0;
};

class BasketballScoreboardTeamObserver {
public:
    virtual void TeamUpdate() = 0;
};

class BasketballScoreTeamSubject {
public:
    virtual void Subscribe(BasketballScoreboardTeamObserver *observer) = 0;
    virtual void Unsubscribe(BasketballScoreboardTeamObserver *observer) = 0;
    virtual void Notify() = 0;
};

class BasketballScoreboardTeam : public BasketballScoreTeamSubject {
public:
    BasketballScoreboardTeam(string name) : m_name(name) {}
    virtual ~BasketballScoreboardTeam() {}
    virtual void Subscribe(BasketballScoreboardTeamObserver *observer) {
        m_observers.push_back(observer);
    }
    virtual void Unsubscribe(BasketballScoreboardTeamObserver *observer) {
        vector<BasketballScoreboardTeamObserver*>::iterator iter;
        for (iter = m_observers.begin(); iter != m_observers.end(); iter++) {
            if (observer == *iter) {
                m_observers.erase(iter);
                break;
            }
        }
    }
    virtual void Notify() {
        vector<BasketballScoreboardTeamObserver*>::iterator iter;
        for (iter = m_observers.begin(); iter != m_observers.end(); iter++) {
            BasketballScoreboardTeamObserver *observer = *iter;
            observer->TeamUpdate();
        }
    }
    string GetName() const {
        return m_name;
    }
    int GetScore() const {
        return m_score;
    }
    void FreeThrowMade() {
        cout << GetName() << " : free throw made            | ";
        ScoringUpdate(1);
    }
    void WaiveOffFreeThrow() {
        cout << GetName() << " : free throw waived off          | ";
        ScoringUpdate(-1);
    }
    void TwoPointFieldGoalMade() {
        cout << GetName() << " : 2 point field goal made            | ";
        ScoringUpdate(2);
    }
    void WaiveOffTwoPointFieldGoalMade() {
        cout << GetName() << " : 2 point field goal waived off    | ";
        ScoringUpdate(-2);
    }
    void ThreePointFieldGoalMade() {
        cout << GetName() << " : 3 point field goal made        | ";
        ScoringUpdate(3);
    }
    void WaiveOffThreePointFieldGoalMade() {
        cout << GetName() << " : 3 point field goal waived off  | ";
        ScoringUpdate(-3);
    }
    void Display() {
        cout << m_name << " : " << m_score << endl;
    }
    void ScoringUpdate(int additionalPoints) {
        m_score += additionalPoints;
        if (m_score < 0) {
            m_score = 0;
        }
        Notify();
    }
private:
    string m_name;
    int m_score;
    vector<BasketballScoreboardTeamObserver*> m_observers;
};

class BasketballScoreboard : public BasketballScoreboardTeamObserver {
public:
    BasketballScoreboard(BasketballScoreboardTeam *awayTeam, BasketballScoreboardTeam *homeTeam) :
    m_awayTeam(awayTeam), m_homeTeam(homeTeam) {
        m_awayTeam->Subscribe(this);
        m_homeTeam->Subscribe(this);
    }
    virtual ~BasketballScoreboard() {}
    virtual void TeamUpdate() {
        DisplayScore();
    }
    void DisplayScore() {
        cout << "Score : " << m_awayTeam->GetName() << " " << m_awayTeam->GetScore() << ", "
            << m_homeTeam->GetName() << " " << m_homeTeam->GetScore() << endl;
    }
private:
    BasketballScoreboardTeam *m_awayTeam;
    BasketballScoreboardTeam *m_homeTeam;
};

class FreeThrowCommand : public Command {
public:
    FreeThrowCommand(BasketballScoreboardTeam *team) : m_Team(team) {}
    virtual ~FreeThrowCommand() {}
    virtual void Execute() {
        m_Team->FreeThrowMade();
    }
    virtual void Undo() {
        m_Team->WaiveOffFreeThrow();
    }
private:
    BasketballScoreboardTeam *m_Team;
};

class TwoPointFieldGoalCommand : public Command {
public:
    TwoPointFieldGoalCommand(BasketballScoreboardTeam *team) : m_Team(team) {}
    virtual ~TwoPointFieldGoalCommand() {}
    virtual void Execute() {
        m_Team->TwoPointFieldGoalMade();
    }
    virtual void Undo() {
        m_Team->WaiveOffTwoPointFieldGoalMade();
    }
private:
    BasketballScoreboardTeam *m_Team;
};

class ThreePointFieldGoalCommand : public Command {
public:
    ThreePointFieldGoalCommand(BasketballScoreboardTeam *team) : m_Team(team) {}
    virtual ~ThreePointFieldGoalCommand() {}
    virtual void Execute() {
        m_Team->ThreePointFieldGoalMade();
    }
    virtual void Undo() {
        m_Team->WaiveOffThreePointFieldGoalMade();
    }
private:
    BasketballScoreboardTeam *m_Team;
};

enum BasketballScoreboardButtonId {
    BSCI_AwayTeamFreeThrowButtonId,
    BSCI_AwayTeamTwoPointFieldGoalButtonId,
    BSCI_AwayTeamThreePointFieldGoalButtonId,
    BSCI_HomeTeamFreeThrowButtonId,
    BSCI_HomeTeamTwoPointFieldGoalButtonId,
    BSCI_HomeTeamThreePointFieldGoalButtonId
};

class BasketballScoreboardControl {
public:
    BasketballScoreboardControl() {}
    virtual ~BasketballScoreboardControl() {}
    void SetCommand(BasketballScoreboardButtonId buttonId, Command *command) {
        map<BasketballScoreboardButtonId, Command*>::iterator commandIter;
        if ((commandIter = m_commandMap.find(buttonId)) == m_commandMap.end()) {
            m_commandMap.insert(make_pair(buttonId, command));
        } else {
            cout << "buttonId " << buttonId << " map entry already exists.\n";
        }
    }
    void ButtonPressed(BasketballScoreboardButtonId buttonId) {
        map<BasketballScoreboardButtonId, Command*>::iterator iter;
        if ((iter = m_commandMap.find(buttonId)) != m_commandMap.end()) {
            Command *command = iter->second;
            command->Execute();
            m_commandHistory.push_front(command);
        }
    }
    void UndoLastButtonPress() {
        if (!m_commandHistory.empty()) {
            Command *command = m_commandHistory.front();
            command->Undo();
            m_commandHistory.pop_front();
        } else {
            cout << "no previous button press to undo!\n";
        }
    }
private:
     map<BasketballScoreboardButtonId, Command *> m_commandMap;
    deque<Command *> m_commandHistory;
};

int main() {
    cout << "Basketball Scoreboard\n";
    BasketballScoreboardTeam *homeTeam = new BasketballScoreboardTeam(string("Home Team"));
    BasketballScoreboardTeam *awayTeam = new BasketballScoreboardTeam(string("Away Team"));
    BasketballScoreboard *scoreBoard = new BasketballScoreboard(awayTeam, homeTeam);
    
    FreeThrowCommand *freeThrowCommandHomeTeam = new FreeThrowCommand(homeTeam);
    TwoPointFieldGoalCommand *twoPointFieldGoalCommandHomeTeam = 
        new TwoPointFieldGoalCommand(homeTeam);
    ThreePointFieldGoalCommand *threePointFieldGoalCommandHomeTeam = 
        new ThreePointFieldGoalCommand(homeTeam);
    
    FreeThrowCommand *freeThrowCommandAwayTeam = new FreeThrowCommand(awayTeam);
    TwoPointFieldGoalCommand *twoPointFieldGoalCommandAwayTeam =
        new TwoPointFieldGoalCommand(awayTeam);
    ThreePointFieldGoalCommand *threePointFieldGoalCommandAwayTeam = 
        new ThreePointFieldGoalCommand(awayTeam);
    
    BasketballScoreboardControl *basketballScoreboardControl = 
        new BasketballScoreboardControl();
    
    basketballScoreboardControl->SetCommand(BSCI_HomeTeamFreeThrowButtonId, freeThrowCommandHomeTeam);
    basketballScoreboardControl->SetCommand(BSCI_HomeTeamTwoPointFieldGoalButtonId, twoPointFieldGoalCommandHomeTeam);
    basketballScoreboardControl->SetCommand(BSCI_HomeTeamThreePointFieldGoalButtonId, threePointFieldGoalCommandHomeTeam);
    
    
    basketballScoreboardControl->SetCommand(BSCI_AwayTeamFreeThrowButtonId, freeThrowCommandAwayTeam);
    basketballScoreboardControl->SetCommand(BSCI_AwayTeamTwoPointFieldGoalButtonId, twoPointFieldGoalCommandAwayTeam);
    basketballScoreboardControl->SetCommand(BSCI_AwayTeamThreePointFieldGoalButtonId, threePointFieldGoalCommandAwayTeam);
    
    basketballScoreboardControl->ButtonPressed(BSCI_HomeTeamFreeThrowButtonId);
    basketballScoreboardControl->ButtonPressed(BSCI_HomeTeamTwoPointFieldGoalButtonId);
    basketballScoreboardControl->ButtonPressed(BSCI_HomeTeamThreePointFieldGoalButtonId);
    
    basketballScoreboardControl->UndoLastButtonPress();
    basketballScoreboardControl->UndoLastButtonPress();
    basketballScoreboardControl->UndoLastButtonPress();
    
    basketballScoreboardControl->ButtonPressed(BSCI_AwayTeamFreeThrowButtonId);
    basketballScoreboardControl->ButtonPressed(BSCI_AwayTeamTwoPointFieldGoalButtonId);
    basketballScoreboardControl->ButtonPressed(BSCI_AwayTeamThreePointFieldGoalButtonId);
    
    basketballScoreboardControl->UndoLastButtonPress();
    basketballScoreboardControl->UndoLastButtonPress();
    basketballScoreboardControl->UndoLastButtonPress();
    
    delete basketballScoreboardControl;
    delete homeTeam;
    delete freeThrowCommandHomeTeam;
    delete twoPointFieldGoalCommandHomeTeam;
    delete threePointFieldGoalCommandHomeTeam;
    delete awayTeam;
    delete freeThrowCommandAwayTeam;
    delete twoPointFieldGoalCommandAwayTeam;
    delete threePointFieldGoalCommandAwayTeam;
    return 0;
}
