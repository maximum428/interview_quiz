class ListNode:
    def __init__(self, value=0, next=None):
        self.val = value
        self.next = next

def add_num_by_list(list1, list2):
    res = 0
    sum = 0
    pos = 1

    while list1 or list2:
        if list1:
            sum += list1.val
            list1 = list1.next
        if list2:
            sum += list2.val
            list2 = list2.next

        res += (sum % 10) * pos
        sum //= 10
        pos *= 10

    if sum > 0:
        res += (sum % 10) * pos

    return res

def create_linked_list(values):
    head = None
    current = None
    for value in values:
        new_node = ListNode(value)
        if head is None:
            head = new_node
        else:
            current.next = new_node
        current = new_node
    return head

if __name__ == "__main__":
    root1 = create_linked_list([4, 5, 7])
    root2 = create_linked_list([3, 6])

    print(add_num_by_list(root1, root2))
