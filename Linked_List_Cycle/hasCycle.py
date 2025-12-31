class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next
        
def has_cycle(head: ListNode) -> ListNode | None:
    slow = fast = head
    
    while fast and fast.next:
        slow = slow.next
        fast = fast.next.next
        if slow is fast:
            return slow
    return None

def find_cycle_entry(head: ListNode) -> ListNode | None:
    meet = has_cycle(head)
    if not meet:
        return None
    
    p1, p2 = head, meet
    while p1 is not p2:
        p1 = p1.next
        p2 = p2.next
    return p1

def break_cycle(entry: ListNode) -> None:
    cur = entry
    while cur.next is not entry:
        cur = cur.next
    cur.next = None

if __name__ == "__main__":
    head = ListNode(1)
    n2 = ListNode(2)
    n3 = ListNode(3)
    
    head.next = n2
    n2.next = n3
    n3.next = head
    
    print("Has cycle:", bool(has_cycle(head)))
    
    entry = find_cycle_entry(head)
    if entry:
        break_cycle(entry)
        
    print("Cycle broken:", bool(has_cycle(head)))
