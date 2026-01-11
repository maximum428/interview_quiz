/*
Observer Pattern（觀察者模式）是一種 行為型設計模式，它允許 一個對象（Subject/主題）在狀態改變時，通知一群依賴於它的對象（Observers/觀察者），而且這些觀察者可以自動更新自己。

它的核心目標是 解耦：Subject 不需要知道有多少 Observer，也不需要知道它們具體的行為，只要能通知它們即可。

主要角色

1. Subject（主題 / 被觀察者）

    - 保存觀察者列表。

    - 提供註冊（subscribe）和取消註冊（unsubscribe）功能。

    - 當自身狀態改變時，調用 Notify() 通知所有觀察者。

2. Observer（觀察者）

    - 定義一個接口（interface），通常有一個 update() 或 BlogUpdate() 方法。

    - 當 Subject 狀態改變時，該方法會被呼叫。

3. ConcreteSubject（具體主題）

    - 實作 Subject 接口，保存自身狀態（如 blog 內容）。

    - 當狀態改變時，呼叫 Notify() 通知觀察者。

4. ConcreteObserver（具體觀察者）

    - 實作 Observer 接口。

    - 保存對 Subject 的引用，以便在通知時取得最新狀態。


特點 / 優點

1. 解耦：Subject 不知道觀察者的具體類型。

2. 動態關聯：觀察者可以隨時訂閱或取消訂閱。

3. 支援多個觀察者：一個 Subject 可以有多個 Observer，互不影響。

4. 廣泛應用：GUI 事件監聽（button click）、數據變更通知（MVC 模式）、新聞/訊息推送系統。
*/


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
