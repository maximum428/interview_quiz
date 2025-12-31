use std::rc::Rc;
use std::cell::RefCell;

type Link = Option<Rc<RefCell<ListNode>>>;

#[derive(Debug)]
struct ListNode {
    val: i32,
    next: Link,
}

fn has_cycle(head: &Link) -> Link {
    let mut slow = head.clone();
    let mut fast = head.clone();
    
    while fast.is_some() && fast.as_ref().unwrap().borrow().next.is_some() {
        slow = slow.unwrap().borrow().next.clone();
        fast = fast
            .unwrap()
            .borrow()
            .next
            .as_ref()
            .unwrap()
            .borrow()
            .next
            .clone();
        
        if let (Some(s), Some(f)) = (&slow, &fast) {
            if Rc::ptr_eq(s, f) {
                return slow;
            }
        }
    }
    None
}

fn find_cycle_entry(head: &Link) -> Link {
    let meet = has_cycle(head)?;
    let mut p1 = head.clone();
    let mut p2 = Some(meet);
    
    while let (Some(a), Some(b)) = (p1.clone(), p2.clone()) {
        if Rc::ptr_eq(&a, &b) {
            return p1;
        }
        p1 = a.borrow().next.clone();
        p2 = b.borrow().next.clone();
    }
    None
}

fn break_cycle(entry: &Rc<RefCell<ListNode>>) {
    let mut cur = entry.clone();
    
    loop {
        let next = cur.borrow().next.clone().unwrap();
        if Rc::ptr_eq(&next, entry) {
            cur.borrow_mut().next = None;
            break;
        }
        cur = next;
    }
}

fn main() {
    let n1 = Rc::new(RefCell::new(ListNode { val: 1, next: None }));
    let n2 = Rc::new(RefCell::new(ListNode { val: 2, next: None }));
    let n3 = Rc::new(RefCell::new(ListNode { val: 3, next: None }));
    
    let head = Some(n1.clone());
    
    println!("Has cycle: {}", has_cycle(&head).is_some());
    
    if let Some(entry) = find_cycle_entry(&head) {
        break_cycle(&entry);
    }
    
    println!("Cycle broken: {}", has_cycle(&head).is_some());
}
