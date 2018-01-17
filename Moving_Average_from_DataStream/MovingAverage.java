import java.util.Queue;
import java.util.LinkedList;

public class MovingAverage {
    private Queue<Integer> queue;
    private double sum = 0;
    private int size;
    
    public MovingAverage(int size) {
        queue = new LinkedList<>();
        this.size = size;
    }
    
    public double next(int val) {
        if (queue.size() == size) {
            sum -= queue.remove();
        }
        sum += val;
        queue.offer(val);
        return sum / queue.size();
    }
    
    public static void main(String[] args) {
        MovingAverage m = new MovingAverage(3);
        System.out.println("m.next(1) = "+m.next(1));
        System.out.println("m.next(10) = "+m.next(10));
        System.out.println("m.next(3) = "+m.next(3));
        System.out.println("m.next(5) = "+m.next(5));
    }
}
