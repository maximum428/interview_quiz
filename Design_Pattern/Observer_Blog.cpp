#include <iostream>

using namespace std;

class BlogObserver {
public:
    virtual ~BlogObserver() {}
    virtual void BlogUpdate() = 0;
};

class StringData {
public:
    virtual ~StringData() {}
    virtual string GetData() = 0;
};

class BlogSubject {
public:
    virtual ~BlogSubject() {}
    virtual void Subscribe(BlogObserver *observer) = 0;
    virtual void Unsubscribe(BlogObserver *observer) = 0;
    virtual void Notify() = 0;
};

class MyBlog : public BlogSubject {
public:
    class BlogData : public StringData {
    public:
        BlogData() {}
        virtual ~BlogData() {}
        virtual string GetData() { return m_data; }
        void SetData(string data) { m_data = data; }
    private:
        string m_data;
    };
    
    MyBlog() : m_pBlogData(new BlogData()) {
        pthread_mutex_init(&m_mutex, NULL);
    }
    virtual ~MyBlog() {
        delete m_pBlogData;
        pthread_mutex_destroy(&m_mutex);
    }
    virtual void Subscribe(BlogObserver *observer) {
        pthread_mutex_lock(&m_mutex);
        m_observers.push_back(observer);
        pthread_mutex_unlock(&m_mutex);
    }
    virtual void Unsubscribe(BlogObserver *observer) {
        vector<BlogObserver *>::iterator pos;
        pthread_mutex_lock(&m_mutex);
        for (pos = m_observers.begin(); pos != m_observers.end(); ++pos) {
            if (*pos == observer) {
                m_observers.erase(pos);
                break;
            }
        }
        pthread_mutex_unlock(&m_mutex);
    }
    
    virtual void Notify() {
        vector<BlogObserver *>::iterator pos;
        pthread_mutex_lock(&m_mutex);
        for (pos = m_observers.begin(); pos != m_observers.end(); pos++) {
            BlogObserver *observer = *pos;
            observer->BlogUpdate();
        }
        pthread_mutex_unlock(&m_mutex);
    }
    
    BlogData *GetData() { return m_pBlogData; }
    
    void SetData(string data) {
        m_pBlogData->SetData(data);
        Notify();
    }
    
private:
    vector<BlogObserver*> m_observers;
    BlogData *m_pBlogData;
    pthread_mutex_t m_mutex;
};

class Boss : public BlogObserver {
public:
    Boss(MyBlog *blog) : m_pBlog(blog) {}
    virtual ~Boss() {}
    virtual void BlogUpdate() {
        StringData *stringData = m_pBlog->GetData();
        string data = stringData->GetData();
        cout << "Boss received \"" << data << "\"\n";
    }
    
private:
    MyBlog *m_pBlog;
};

class CoWorker : public BlogObserver {
public:
    CoWorker(MyBlog *blog) : m_pBlog(blog) {}
    virtual ~CoWorker() {}
    virtual void BlogUpdate() {
        StringData *stringData = m_pBlog->GetData();
        string data = stringData->GetData();
        cout << "CoWorker received \"" << data << "\"\n";
    }
private:
    MyBlog *m_pBlog;
};

class Friend : public BlogObserver {
public:
    Friend(MyBlog *blog) : m_pBlog(blog) {}
    virtual ~Friend() {}
    virtual void BlogUpdate() {
        StringData *stringData = m_pBlog->GetData();
        string data = stringData->GetData();
        cout << "Friend received \"" << data << "\"\n";
    }
private:
    MyBlog *m_pBlog;
};

int main() {
    MyBlog *blog = new MyBlog();
    Boss *boss = new Boss(blog);
    CoWorker *coWorker = new CoWorker(blog);
    Friend *myFriend = new Friend(blog);
    
    blog->Subscribe(boss);
    blog->Subscribe(coWorker);
    
    blog->SetData(string("My first blog"));
    
    blog->Unsubscribe(boss);
    blog->Subscribe(myFriend);
    
    blog->SetData(string("My second blog"));
    
    blog->Unsubscribe(coWorker);
    blog->SetData(string("My third blog"));
    
    delete boss;
    delete coWorker;
    delete myFriend;
    delete blog;
    
    return 0;
}
