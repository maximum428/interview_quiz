import Queue

class MovingAverage(object):
    def __init__(self, size):
        global sum
        sum = 0.0
        self.size = size
        self.stream = Queue.Queue()

    def next(self, val):
        global sum
        if self.stream.qsize() == self.size:
            sum -= self.stream.get()
        sum += val
        self.stream.put(val)
        return sum / self.stream.qsize()

if __name__ == "__main__":
    m = MovingAverage(3)
    print "m.next(1) = %f\n" % m.next(1)
    print "m.next(10) = %f\n" % m.next(10)
    print "m.next(3) = %f\n" % m.next(3)
    print "m.next(5) = %f\n" % m.next(5)
