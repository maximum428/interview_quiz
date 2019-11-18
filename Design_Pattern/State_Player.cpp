#include <iostream>

using namespace std;

class MusicPlayerState {
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
    string GetName() {
        return m_name;
    }
private:
    string m_name;
};

class PlayingState : public MusicPlayerState {
    PlayingState() : MusicPlayerState(string("Playing")) {}
    virtual ~PlayingState() {}
    virtual void Pause(MusicPlayer *player) {
        player->setState(MusicPlayer::ST_PAUSED);
    }
    virtual void Stop(MusicPlayer *player) {
        player->SetState(MusicPlayer::ST_STOPPED);
    }
};

class PauseState : public MusicPlayerState {
public:
    PausedState() : MusicPalyerState(string("Paused")) {}
    virtual ~PausedState();
    
    virtual void Play(MusicPlayer *player) {
        player->SetState(MusicPlayer::ST_PLAYING);
    }
    virtual void Stop(MusicPlayer *player) {
        player->SetState(MusicPlayer::ST_STOPPED);
    }
};

class StoppedState : public MusicPlayerState {
public:
    StoppedState() : MusicPlayerState(string("Stopped")) {}
    virtual ~StoppedState() {}
    virtual void Play(MusticPlayer *player) {
        player->SetState(MusicPlayer::ST_PLAYING);
    }
};

class MusicPlayer {
public:
    enum State { ST_STOPPED, ST_PLAYING, ST_PAUSED };
    MusicePlayer() : m_pState(new StoppedState()) {}
    virtual ~MusicPlayer() {
        delete m_pState;
    }
    void Play() {
        m_pState->Play(this);
    }
    void Pause() {
        m_pState->Pause(this);
    }
    void Stop() {
        m_pState->Stop(this);
    }
    void SetState(State state) {
        cout << "changing from " << m_pState->GetName() << " to ";
        delete m_pState;
        
        if (state == ST_STOPPED) {
            m_pState = new StoppedState();
        } else if (state == ST_PLAYING) {
            m_pState = new PlayingState();
        } else {
            m_pState = new PausedState();
        }
        cout << m_pState->GetName() << " state\n";
    }
private:
    MusicPlayerState *m_pState;
};

int main() {
    MusicPlayer player;
    player.Play();
    player.Pause();
    player.Stop();
    
    return 0;
}
