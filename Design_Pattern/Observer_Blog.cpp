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
        //pthread_mutex_init(&m_mutex, NULL);
    }
    virtual ~MyBlog() {
        delete m_pBlogData;
        //pthread_mutex_destroy(&m_mutex);
    }
    virtual void Subscribe(BlogObserver *observer) {
        std::lock_guard<std::mutex> guard(m_mutex);
        //pthread_mutex_lock(&m_mutex);
        m_observers.push_back(observer);
        //pthread_mutex_unlock(&m_mutex);
    }
    virtual void Unsubscribe(BlogObserver *observer) {
        vector<BlogObserver *>::iterator pos;
        std::lock_guard<std::mutex> guard(m_mutex);
        //pthread_mutex_lock(&m_mutex);
        for (pos = m_observers.begin(); pos != m_observers.end(); ++pos) {
            if (*pos == observer) {
                m_observers.erase(pos);
                break;
            }
        }
        //pthread_mutex_unlock(&m_mutex);
    }
    
    virtual void Notify() {
#if 1
        std::lock_guard<std::mutex> guard(m_mutex);
        for_each(m_observers.begin(), m_observers.end(), mem_fn(&BlogObserver::BlogUpdate));
#else
        vector<BlogObserver *>::iterator pos;
        pthread_mutex_lock(&m_mutex);
        for (pos = m_observers.begin(); pos != m_observers.end(); pos++) {
            BlogObserver *observer = *pos;
            observer->BlogUpdate();
        }
        pthread_mutex_unlock(&m_mutex);
#endif
    }
    
    BlogData *GetData() { return m_pBlogData; }
    
    void SetData(string data) {
        m_pBlogData->SetData(data);
        Notify();
    }
    
private:
    vector<BlogObserver*> m_observers;
    BlogData *m_pBlogData;
    //pthread_mutex_t m_mutex;
    std::mutex m_mutex;
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


/*****************************************************************************************
*************************** Smart Pointer Version ****************************************
******************************************************************************************/

#include <iostream>
#include <mutex>
#include <vector>
#include <memory>
#include <algorithm>
#include <functional>

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
    virtual void Subscribe(shared_ptr<BlogObserver> observer) = 0;
    virtual void Unsubscribe(shared_ptr<BlogObserver> observer) = 0;
    virtual void Notify() = 0;
};

class MyBlog : public BlogSubject, public enable_shared_from_this<MyBlog> {
public:
    class BlogData : public StringData {
        string m_data;
    public:
        BlogData() {}
        virtual ~BlogData() {}
        virtual string GetData() { return m_data; }
        void SetData(string data) { m_data = data; }
    };
    
    MyBlog() : m_BlogData(make_unique<BlogData>()) {}
    virtual ~MyBlog() {}
    virtual void Subscribe(shared_ptr<BlogObserver> observer) {
        lock_guard guard(m_mutex);
        m_observers.push_back(observer);
    }
    virtual void Unsubscribe(shared_ptr<BlogObserver> observer) {
        lock_guard guard(m_mutex);
        m_observers.erase(remove_if(
            m_observers.begin(), m_observers.end(),
            [&observer](const weak_ptr<BlogObserver>& wptr) {
                auto sp = wptr.lock();
                return sp == nullptr || sp == observer;
            }),
            m_observers.end()
        );
    }
    virtual void Notify() {
        lock_guard guard(m_mutex);
        for (auto& wptr : m_observers) {
            if (auto observer = wptr.lock())
                observer->BlogUpdate();
        }
    }
    BlogData *GetData() {
        return m_BlogData.get();
    }
    void SetData(const string& data) {
        m_BlogData->SetData(data);
        Notify();
    }
private:
    unique_ptr<BlogData> m_BlogData;
    mutex m_mutex;
    vector<weak_ptr<BlogObserver>> m_observers;  // use weak_ptr to avoid cycles
};

class Boss : public BlogObserver, public enable_shared_from_this<Boss> {
    shared_ptr<MyBlog> m_Blog;
public:
    Boss(shared_ptr<MyBlog> blog) : m_Blog(blog) {}
    virtual ~Boss() {}
    virtual void BlogUpdate() {
        string data = m_Blog->GetData()->GetData();
        cout << "Boss received \"" << data << "\"\n";
    }
};

class CoWorker : public BlogObserver, public enable_shared_from_this<CoWorker> {
    shared_ptr<MyBlog> m_Blog;
public:
    CoWorker(shared_ptr<MyBlog> blog) : m_Blog(blog) {}
    virtual ~CoWorker() {}
    virtual void BlogUpdate() {
        string data = m_Blog->GetData()->GetData();
        cout << "CoWorker received \"" << data << "\"\n";
    }
};

class Friend : public BlogObserver, public enable_shared_from_this<Friend> {
    shared_ptr<MyBlog> m_Blog;
public:
    Friend(shared_ptr<MyBlog> blog) : m_Blog(blog) {}
    virtual ~Friend() {}
    virtual void BlogUpdate() {
        string data = m_Blog->GetData()->GetData();
        cout << "Friend received \"" << data << "\"\n";
    }
};

int main(int argc, char** argv) {
    auto blog = make_shared<MyBlog>();
    auto boss = make_shared<Boss>(blog);
    auto coWorker = make_shared<CoWorker>(blog);
    auto myFriend = make_shared<Friend>(blog);
    
    blog->Subscribe(boss);
    blog->Subscribe(coWorker);
    
    blog->SetData("My first blog");
    
    blog->Unsubscribe(boss);
    blog->Subscribe(myFriend);
    
    blog->SetData("My second blog");
    
    blog->Unsubscribe(coWorker);
    blog->SetData("My third blog");
    
    return 0;
}
