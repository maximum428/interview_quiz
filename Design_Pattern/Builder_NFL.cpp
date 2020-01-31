#include <iostream>

using namespace std;

class Game {
public:
    Game() {}
    virtual ~Game() {}
    void SetTime(const string& time) { m_time = time; }
    void SetHomeTeam(const string& name) { m_homeTeam = name; }
    void SetAwayTeam(const string& name) { m_awayTeam = name; }
    
    string GetTime() const { return m_time; }
    string GetHomeTeam() const { return m_homeTeam; }
    string GetAwayTeam() const { return m_awayTeam; }
    void Display() const {
        cout << m_time << " : " << m_awayTeam << " at " << m_homeTeam << "\n";
    }
private:
    string m_time;
    string m_homeTeam;
    string m_awayTeam;
};

class GameDate {
public:
    GameDate(string date) : m_date(date) {}
    virtual ~GameDate() {}
    void AddGame(const unsigned int& gameNumber, Game *game) {
        m_games.insert(make_pair(gameNumber, game));
    }
    Game *GetGame(const unsigned int& gameNumber) {
        auto iter = m_games.find(gameNumber);
        if (iter != m_games.end()) {
            return iter->second;
        }
        return nullptr;
    }
    void Display() const {
        cout << m_date << "\n\n";
        for (auto iter = m_games.begin(); iter != m_games.end(); iter++) {
            iter->second->Display();
        }
    }
private:
    string m_date;
    map<unsigned int, Game*> m_games;
};

class GameSchedule {
public:
    virtual void Display() const = 0;
};

class SportsGameSchedule : public GameSchedule {
public:
    SportsGameSchedule() {}
    virtual ~SportsGameSchedule() {}
    void AddGameDate(const unsigned int& dateNumber, GameDate *date) {
        m_gameDates.insert(make_pair(dateNumber, date));
    }
    GameDate *GetGameDate(const unsigned int& dateNumber) const {
        auto iter = m_gameDates.find(dateNumber);
        if (iter != m_gameDates.end()) {
            GameDate *gameDate = iter->second;
            return gameDate;
        }
        return nullptr;
    }
    virtual void Display() const {
        for (auto iter = m_gameDates.begin(); iter != m_gameDates.end(); iter++) {
            GameDate *gameDate = iter->second;
            gameDate->Display();
            cout << "\n\n";
        }
    }
private:
    map<unsigned int, GameDate*> m_gameDates;
};

class GameScheduleBuilder {
public:
    virtual void BuildSchedule() = 0;
    virtual void BuildDate(unsigned int dateNumber, string date) = 0;
    virtual void BuildGame(unsigned int dateNumber, unsigned int gameNumber) = 0;
    virtual void AddTime(unsigned int dateNumber, unsigned int gameNumber, string time) = 0;
    virtual void AddHomeTeam(unsigned int dateNumber, unsigned int gameNumber, string name) = 0;
    virtual void AddAwayTeam(unsigned int dateNumber, unsigned int gameNumber, string name) = 0;
};

class SportsGameScheduleBuilder : public GameScheduleBuilder {
public:
    SportsGameScheduleBuilder() : m_gameSchedule(nullptr) {}
    virtual ~SportsGameScheduleBuilder() { delete m_gameSchedule; }
    virtual void BuildSchedule() {
        m_gameSchedule = new SportsGameSchedule();
    }
    virtual void BuildDate(unsigned int dateNumber, string date) {
        if (m_gameSchedule != nullptr)
            m_gameSchedule->AddGameDate(dateNumber, new GameDate(date));
    }
    virtual void BuildGame(unsigned int dateNumber, unsigned int gameNumber) {
        if (m_gameSchedule != nullptr) {
            GameDate *date = m_gameSchedule->GetGameDate(dateNumber);
            date->AddGame(gameNumber, new Game());
        }
    }
    virtual void AddTime(unsigned int dateNumber, unsigned int gameNumber, string time) {
        if (m_gameSchedule != nullptr) {
            GameDate *date = m_gameSchedule->GetGameDate(dateNumber);
            Game *game = date->GetGame(gameNumber);
            game->SetTime(time);
        }
    }
    virtual void AddHomeTeam(unsigned int dateNumber, unsigned int gameNumber, string name) {
        if (m_gameSchedule != nullptr) {
            GameDate *date = m_gameSchedule->GetGameDate(dateNumber);
            Game *game = date->GetGame(gameNumber);
            game->SetHomeTeam(name);
        }
    }
    virtual void AddAwayTeam(unsigned int dateNumber, unsigned int gameNumber, string name) {
        if (m_gameSchedule != nullptr) {
            GameDate *date = m_gameSchedule->GetGameDate(dateNumber);
            Game *game = date->GetGame(gameNumber);
            game->SetAwayTeam(name);
        }
    }
    GameSchedule *GetSchedule() {
        return m_gameSchedule;
    }
private:
    SportsGameSchedule *m_gameSchedule;
};

class NFLScheduler {
public:
    NFLScheduler(GameScheduleBuilder *builder) : m_gameScheduleBuilder(builder) {}
    virtual ~NFLScheduler() {}
    void ConstructSchedule() {
        unsigned int dateNumber = 0;
        unsigned int gameNumber = 0;
        
        m_gameScheduleBuilder->BuildSchedule();
        m_gameScheduleBuilder->BuildDate(dateNumber, string("09/07/17"));
        m_gameScheduleBuilder->BuildGame(dateNumber, gameNumber);
        m_gameScheduleBuilder->AddTime(dateNumber, gameNumber, string("8:30pm"));
        m_gameScheduleBuilder->AddHomeTeam(dateNumber, gameNumber, string("New England Patriots"));
        m_gameScheduleBuilder->AddAwayTeam(dateNumber, gameNumber, string("Kansas City Chiefs"));
        
        m_gameScheduleBuilder->BuildDate(++dateNumber, string("09/10/17"));
        m_gameScheduleBuilder->BuildGame(dateNumber, ++gameNumber);
        m_gameScheduleBuilder->AddTime(dateNumber, gameNumber, string("1:00pm"));
        m_gameScheduleBuilder->AddHomeTeam(dateNumber, gameNumber, string("New York Jets"));
        m_gameScheduleBuilder->AddAwayTeam(dateNumber, gameNumber, string("Buffalo Bills"));
        
        m_gameScheduleBuilder->BuildGame(dateNumber, ++gameNumber);
        m_gameScheduleBuilder->AddTime(dateNumber, gameNumber, string("1:00pm"));
        m_gameScheduleBuilder->AddHomeTeam(dateNumber, gameNumber, string("Washington Redskins"));
        m_gameScheduleBuilder->AddAwayTeam(dateNumber, gameNumber, string("Philadelphia Eagles"));
        
        m_gameScheduleBuilder->BuildGame(dateNumber, ++gameNumber);
        m_gameScheduleBuilder->AddTime(dateNumber, gameNumber, string("1:00pm"));
        m_gameScheduleBuilder->AddHomeTeam(dateNumber, gameNumber, string("Tennessee Titans"));
        m_gameScheduleBuilder->AddAwayTeam(dateNumber, gameNumber, string("Las Vegas Raiders"));
        
        m_gameScheduleBuilder->BuildGame(dateNumber, ++gameNumber);
        m_gameScheduleBuilder->AddTime(dateNumber, gameNumber, string("1:00pm"));
        m_gameScheduleBuilder->AddHomeTeam(dateNumber, gameNumber, string("Miami Dolphins"));
        m_gameScheduleBuilder->AddAwayTeam(dateNumber, gameNumber, string("Tampa Bay Buccaneers"));
        
        m_gameScheduleBuilder->BuildGame(dateNumber, ++gameNumber);
        m_gameScheduleBuilder->AddTime(dateNumber, gameNumber, string("1:00pm"));
        m_gameScheduleBuilder->AddHomeTeam(dateNumber, gameNumber, string("Houston Texans"));
        m_gameScheduleBuilder->AddAwayTeam(dateNumber, gameNumber, string("Jacksonville Jaguars"));
    }
private:
    GameScheduleBuilder *m_gameScheduleBuilder;
};

int main() {
    SportsGameScheduleBuilder *gameScheduleBuilder = new SportsGameScheduleBuilder();
    NFLScheduler scheduler(gameScheduleBuilder);
    scheduler.ConstructSchedule();
    GameSchedule *schedule = gameScheduleBuilder->GetSchedule();
    schedule->Display();
    return 0;
}
