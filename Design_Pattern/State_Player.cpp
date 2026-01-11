/*
The State Pattern allows an object to alter its behavior when its internal state changes. The object will appear to change its class.
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
