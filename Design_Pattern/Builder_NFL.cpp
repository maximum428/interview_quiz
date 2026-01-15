/*
The Builder Pattern allows you to encapsulate the construction of a product and allow it to be constructed in steps.

白話解釋（最直覺）

Builder Pattern 把「怎麼蓋東西」藏起來，讓你可以一步一步把它蓋好。

重點有兩個：

封裝建構過程（encapsulate construction）

使用者 不用知道

物件怎麼 new

內部有哪些零件

建構順序怎麼安排

分步驟建構（constructed in steps）

可以：

先加這個

再加那個

最後才拿到成品

👉 就像 點漢堡

你只說：加牛肉、加起司、不加洋蔥

廚房怎麼做你不用管

結構圖（最經典 Builder 圖）
Client
  |
  | uses
  v
+-------------+
|   Builder   |  <---- 定義建構步驟
+-------------+
| addPartA()  |
| addPartB()  |
| build()     |
+-------------+
      ^
      |
+------------------+
| ConcreteBuilder  |  <---- 真正怎麼做
+------------------+
| addPartA()       |
| addPartB()       |
| build()          |
+------------------+
      |
      v
   Product
*/
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

    delete gameScheduleBuilder;
    return 0;
}


/*********************************************************************************
************************ Smart Pointer Version ************************
**********************************************************************************/

#include <iostream>
#include <map>
#include <string>
#include <memory>

using namespace std;
using namespace std::string_literals;

class Game {
    string m_time;
    string m_homeTeam;
    string m_awayTeam;
public:
    void SetTime(const string& time) { m_time = time; }
    void SetHomeTeam(const string& name) { m_homeTeam = name; }
    void SetAwayTeam(const string& name) { m_awayTeam = name; }
    
    string GetTime() const { return m_time; }
    string GetHomeTeam() const { return m_homeTeam; }
    string GetAwayTeam() const { return m_awayTeam; }
    void Display() const {
        cout << m_time << " : " << m_awayTeam << " at " << m_homeTeam << endl;
    }
};

class GameDate {
    string m_date;
    map<unsigned int, unique_ptr<Game>> m_games;
public:
    explicit GameDate(string date) : m_date(move(date)) {}
    void AddGame(unsigned int gameNumber) {
        m_games.emplace(gameNumber, make_unique<Game>());
    }
    Game* GetGame(unsigned int gameNumber) {
        auto it = m_games.find(gameNumber);
        return it != m_games.end() ? it->second.get() : nullptr;
    }
    void Display() const {
        cout << m_date << "\n\n";
        for (const auto& [_, game] : m_games) {
            game->Display();
        }
    }
};

class GameSchedule {
public:
    virtual ~GameSchedule() = default;
    virtual void Display() const = 0;
};

class SportsGameSchedule : public GameSchedule {
    map<unsigned int, unique_ptr<GameDate>> m_gameDates;
public:
    void AddGameDate(unsigned int dateNumber, string date) {
        m_gameDates.emplace(dateNumber, make_unique<GameDate>(move(date)));
    }
    GameDate *GetGameDate(unsigned int dateNumber) {
        auto it = m_gameDates.find(dateNumber);
        return it != m_gameDates.end() ? it->second.get() : nullptr;
    }
    void Display() const override {
        for (const auto& [_, date] : m_gameDates) {
            date->Display();
            cout << "\n";
        }
    }
};

class GameScheduleBuilder {
public:
    virtual ~GameScheduleBuilder() = default;
    virtual void BuildSchedule() = 0;
    virtual void BuildDate(unsigned int, string) = 0;
    virtual void BuildGame(unsigned int, unsigned int) = 0;
    virtual void AddTime(unsigned int, unsigned int, string) = 0;
    virtual void AddHomeTeam(unsigned int, unsigned int, string) = 0;
    virtual void AddAwayTeam(unsigned int, unsigned int, string) = 0;
};

class SportsGameScheduleBuilder : public GameScheduleBuilder {
    unique_ptr<SportsGameSchedule> m_gameSchedule;
public:
    void BuildSchedule() override {
        m_gameSchedule = make_unique<SportsGameSchedule>();
    }
    void BuildDate(unsigned int dateNumber, string date) override {
        m_gameSchedule->AddGameDate(dateNumber, move(date));
    }
    void BuildGame(unsigned int dateNumber, unsigned int gameNumber) override {
        m_gameSchedule->GetGameDate(dateNumber)->AddGame(gameNumber);
    }
    void AddTime(unsigned int dateNumber, unsigned int gameNumber, string time) override {
        m_gameSchedule->GetGameDate(dateNumber)->GetGame(gameNumber)->SetTime(move(time));
    }
    void AddHomeTeam(unsigned int dateNumber, unsigned int gameNumber, string name) override {
        m_gameSchedule->GetGameDate(dateNumber)->GetGame(gameNumber)->SetHomeTeam(move(name));
    }
    void AddAwayTeam(unsigned int dateNumber, unsigned int gameNumber, string name) override {
        m_gameSchedule->GetGameDate(dateNumber)->GetGame(gameNumber)->SetAwayTeam(move(name));
    }
    GameSchedule& GetSchedule() {
        return *m_gameSchedule;
    }
};

class NFLScheduler {
    GameScheduleBuilder& m_gameScheduleBuilder;
public:
    explicit NFLScheduler(GameScheduleBuilder& builder) : m_gameScheduleBuilder(builder) {}
    void ConstructSchedule() {
        unsigned int dateNumber = 0;
        unsigned int gameNumber = 0;
        
        m_gameScheduleBuilder.BuildSchedule();
        m_gameScheduleBuilder.BuildDate(dateNumber, "09/07/17"s);
        m_gameScheduleBuilder.BuildGame(dateNumber, gameNumber);
        m_gameScheduleBuilder.AddTime(dateNumber, gameNumber, "8:30pm"s);
        m_gameScheduleBuilder.AddHomeTeam(dateNumber, gameNumber, "New England Patriots"s);
        m_gameScheduleBuilder.AddAwayTeam(dateNumber, gameNumber, "Kansas City Chiefs"s);
        
        m_gameScheduleBuilder.BuildDate(++dateNumber, "09/10/17"s);
        m_gameScheduleBuilder.BuildGame(dateNumber, ++gameNumber);
        m_gameScheduleBuilder.AddTime(dateNumber, gameNumber, "1:00pm"s);
        m_gameScheduleBuilder.AddHomeTeam(dateNumber, gameNumber, "New York Jets"s);
        m_gameScheduleBuilder.AddAwayTeam(dateNumber, gameNumber, "Buffalo Bills"s);
        
        m_gameScheduleBuilder.BuildGame(dateNumber, ++gameNumber);
        m_gameScheduleBuilder.AddTime(dateNumber, gameNumber, "1:00pm"s);
        m_gameScheduleBuilder.AddHomeTeam(dateNumber, gameNumber, "Washington Redskins"s);
        m_gameScheduleBuilder.AddAwayTeam(dateNumber, gameNumber, "Philadelphia Eagles"s);
        
        m_gameScheduleBuilder.BuildGame(dateNumber, ++gameNumber);
        m_gameScheduleBuilder.AddTime(dateNumber, gameNumber, "1:00pm"s);
        m_gameScheduleBuilder.AddHomeTeam(dateNumber, gameNumber, "Tennessee Titans"s);
        m_gameScheduleBuilder.AddAwayTeam(dateNumber, gameNumber, "Las Vegas Raiders"s);
        
        m_gameScheduleBuilder.BuildGame(dateNumber, ++gameNumber);
        m_gameScheduleBuilder.AddTime(dateNumber, gameNumber, "1:00pm"s);
        m_gameScheduleBuilder.AddHomeTeam(dateNumber, gameNumber, "Miami Dolphins"s);
        m_gameScheduleBuilder.AddAwayTeam(dateNumber, gameNumber, "Tampa Bay Buccaneers"s);
        
        m_gameScheduleBuilder.BuildGame(dateNumber, ++gameNumber);
        m_gameScheduleBuilder.AddTime(dateNumber, gameNumber, "1:00pm"s);
        m_gameScheduleBuilder.AddHomeTeam(dateNumber, gameNumber, "Houston Texans"s);
        m_gameScheduleBuilder.AddAwayTeam(dateNumber, gameNumber, "Jacksonville Jaguars"s);
    }
};

int main(int argc, char** argv) {
    SportsGameScheduleBuilder gameScheduleBuilder;
    NFLScheduler scheduler(gameScheduleBuilder);
    scheduler.ConstructSchedule();
    gameScheduleBuilder.GetSchedule().Display();

    return 0;
}
