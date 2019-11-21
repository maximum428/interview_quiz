from abc import ABC, abstractmethod
from random import randrange
from typing import List

class BlogObserver(ABC):
    @abstractmethod
    def BlogUpdate(self) -> None:
        pass

class BlogSubject(ABC):
    @abstractmethod
    def Subscribe(self, observer: BlogObserver) -> None:
        pass

    @abstractmethod
    def Unsubscribe(self, observer: BlogObserver) -> None:
        pass

    @abstractmethod
    def Notify(self) -> None:
        pass

class MyBlog(BlogSubject):
    _observers: List[BlogObserver] = []
    def __init__(self, data = None):
        self._data = data
        
    def Subscribe(self, observer: BlogObserver) -> None:
        self._observers.append(observer)

    def Unsubscribe(self, observer: BlogObserver) -> None:
        self._observers.remove(observer)

    def Notify(self) -> None:
        for observer in self._observers:
            observer.BlogUpdate(self)

    def GetData(self) -> str:
        return self._data

    def SetData(self, data) -> None:
        self._data = data
        self.Notify()
        
class Boss(BlogObserver):
    def BlogUpdate(self, blogsubject: BlogSubject) -> None:
        data = blogsubject.GetData()
        print("Boss receive ", data)

class Coworker(BlogObserver):
    def BlogUpdate(self, blogsubject: BlogSubject) -> None:
        data = blogsubject.GetData()
        print("Coworker receive", data)
        
class Friend(BlogObserver):
    def BlogUpdate(self, blogsubject: BlogSubject) -> None:
        data = blogsubject.GetData()
        print("Friend receive", data)

if __name__ == "__main__":
    myblog = MyBlog()
    boss = Boss()
    coworker = Coworker()
    friend = Friend()

    myblog.Subscribe(boss)
    myblog.Subscribe(coworker)
    myblog.SetData("My first blog")

    myblog.Unsubscribe(boss)
    myblog.Subscribe(friend)

    myblog.SetData("My second blog")

    myblog.Unsubscribe(coworker)
    myblog.SetData("My third blog")
