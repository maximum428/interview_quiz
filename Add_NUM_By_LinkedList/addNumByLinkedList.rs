#[derive(Debug)]
struct ListNode {
    val: i32,
    next: Option<Box<ListNode>>,
}

impl ListNode {
    fn new(value: i32) -> Self {
        ListNode {
            val: value,
            next: None,
        }
    }
}

fn add_num_by_list(list1: Option<Box<ListNode>>, list2: Option<Box<ListNode>>) -> i32 {
    let mut res = 0;
    let mut sum = 0;
    let mut pos = 1;
    let mut list1 = list1;
    let mut list2 = list2;

    while list1.is_some() || list2.is_some() {
        if let Some(l1) = list1 {
            sum += l1.val;
            list1 = l1.next;
        }
        if let Some(l2) = list2 {
            sum += l2.val;
            list2 = l2.next;
        }

        res += (sum % 10) * pos;
        sum /= 10;
        pos *= 10;
    }

    if sum > 0 {
        res += (sum % 10) * pos;
    }
    res
}

fn create_linked_list(values: Vec<i32>) -> Option<Box<ListNode>> {
    let mut head: Option<Box<ListNode>> = None;
    let mut current = &mut head;

    for &value in values.iter() {
        let new_node = Box::new(ListNode::new(value));
        *current = Some(new_node);
        current = &mut current.as_mut().unwrap().next;
    }
    head
}

fn main() {
    let root1 = create_linked_list(vec![4, 5, 7]);
    let root2 = create_linked_list(vec![3, 6]);

    println!("{}", add_num_by_list(root1, root2));
}
