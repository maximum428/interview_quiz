/*
The State Pattern allows an object to alter its behavior when its internal state changes. The object will appear to change its class.

State Pattern 的重點是：一個物件的行為 不是固定的，而是依照它的「內部狀態」決定。

也就是說，同一個物件在不同狀態下，對相同方法呼叫會有不同的反應。

總結：

State Pattern = 行為依狀態變化的策略封裝。

它解耦了物件的行為和狀態，使物件可以「動態改變行為」。

從外部看，物件好像「變了類別」，但其實只是內部狀態在切換而已。
*/
#include <iostream>
#include <string>

using namespace std;

class MusicPlayer;  // forward declaration

// ================= State Base =================
class MusicPlayerState {
    string m_name;
public:
    MusicPlayerState(string name) : m_name(name) {}
    virtual ~MusicPlayerState() {}

    virtual void Play(MusicPlayer *player) {
        cout << "Illegal state transition from " << GetName() << " to Playing\n";
    }
    virtual void Pause(MusicPlayer *player) {
        cout << "Illegal state transition from " << GetName() << " to Paused\n";
    }
    virtual void Stop(MusicPlayer *player) {
        cout << "Illegal state transition from " << GetName() << " to Stopped\n";
    }

    string GetName() const {
        return m_name;
    }
};

// ================= MusicPlayer =================
class MusicPlayer {
public:
    enum State { ST_STOPPED, ST_PLAYING, ST_PAUSED };

private:
    MusicPlayerState *m_State;

public:
    MusicPlayer();
    ~MusicPlayer();

    void Play()  { m_State->Play(this); }
    void Pause() { m_State->Pause(this); }
    void Stop()  { m_State->Stop(this); }

    void SetState(State state);
};

// ================= Concrete States =================
class PlayingState : public MusicPlayerState {
public:
    PlayingState() : MusicPlayerState("Playing") {}
    void Pause(MusicPlayer *player) override {
        player->SetState(MusicPlayer::ST_PAUSED);
    }
    void Stop(MusicPlayer *player) override {
        player->SetState(MusicPlayer::ST_STOPPED);
    }
};

class PausedState : public MusicPlayerState {
public:
    PausedState() : MusicPlayerState("Paused") {}
    void Play(MusicPlayer *player) override {
        player->SetState(MusicPlayer::ST_PLAYING);
    }
    void Stop(MusicPlayer *player) override {
        player->SetState(MusicPlayer::ST_STOPPED);
    }
};

class StoppedState : public MusicPlayerState {
public:
    StoppedState() : MusicPlayerState("Stopped") {}
    void Play(MusicPlayer *player) override {
        player->SetState(MusicPlayer::ST_PLAYING);
    }
};

// ================= MusicPlayer Impl =================
MusicPlayer::MusicPlayer() : m_State(new StoppedState()) {}

MusicPlayer::~MusicPlayer() {
    delete m_State;
}

void MusicPlayer::SetState(State state) {
    cout << "changing from " << m_State->GetName() << " to ";

    delete m_State;

    switch (state) {
        case ST_STOPPED: m_State = new StoppedState(); break;
        case ST_PLAYING: m_State = new PlayingState(); break;
        case ST_PAUSED:  m_State = new PausedState();  break;
    }

    cout << m_State->GetName() << " state\n";
}

// ================= main =================
int main() {
    MusicPlayer player;

    player.Play();
    player.Pause();
    player.Stop();

    return 0;
}


/******************************************************************************************
*********************************** Smart Pointer Version *********************************
*******************************************************************************************/

#include <iostream>
#include <string>

using namespace std;

class MusicPlayer;  // forward declaration

// ================= State Base =================
class MusicPlayerState {
    string m_name;
public:
    MusicPlayerState(string name) : m_name(name) {}
    virtual ~MusicPlayerState() {}

    virtual void Play(MusicPlayer *player) {
        cout << "Illegal state transition from " << GetName() << " to Playing\n";
    }
    virtual void Pause(MusicPlayer *player) {
        cout << "Illegal state transition from " << GetName() << " to Paused\n";
    }
    virtual void Stop(MusicPlayer *player) {
        cout << "Illegal state transition from " << GetName() << " to Stopped\n";
    }

    string GetName() const {
        return m_name;
    }
};

// ================= MusicPlayer =================
class MusicPlayer {
public:
    enum State { ST_STOPPED, ST_PLAYING, ST_PAUSED };

private:
    MusicPlayerState *m_State;

public:
    MusicPlayer();
    ~MusicPlayer();

    void Play()  { m_State->Play(this); }
    void Pause() { m_State->Pause(this); }
    void Stop()  { m_State->Stop(this); }

    void SetState(State state);
};

// ================= Concrete States =================
class PlayingState : public MusicPlayerState {
public:
    PlayingState() : MusicPlayerState("Playing") {}
    void Pause(MusicPlayer *player) override {
        player->SetState(MusicPlayer::ST_PAUSED);
    }
    void Stop(MusicPlayer *player) override {
        player->SetState(MusicPlayer::ST_STOPPED);
    }
};

class PausedState : public MusicPlayerState {
public:
    PausedState() : MusicPlayerState("Paused") {}
    void Play(MusicPlayer *player) override {
        player->SetState(MusicPlayer::ST_PLAYING);
    }
    void Stop(MusicPlayer *player) override {
        player->SetState(MusicPlayer::ST_STOPPED);
    }
};

class StoppedState : public MusicPlayerState {
public:
    StoppedState() : MusicPlayerState("Stopped") {}
    void Play(MusicPlayer *player) override {
        player->SetState(MusicPlayer::ST_PLAYING);
    }
};

// ================= MusicPlayer Impl =================
MusicPlayer::MusicPlayer() : m_State(new StoppedState()) {}

MusicPlayer::~MusicPlayer() {
    delete m_State;
}

void MusicPlayer::SetState(State state) {
    cout << "changing from " << m_State->GetName() << " to ";

    delete m_State;

    switch (state) {
        case ST_STOPPED: m_State = new StoppedState(); break;
        case ST_PLAYING: m_State = new PlayingState(); break;
        case ST_PAUSED:  m_State = new PausedState();  break;
    }

    cout << m_State->GetName() << " state\n";
}

// ================= main =================
int main() {
    MusicPlayer player;

    player.Play();
    player.Pause();
    player.Stop();

    return 0;
}
