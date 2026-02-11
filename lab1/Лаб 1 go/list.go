package main

type Node struct {
	Num  string
	Next *Node
}

func VectorToList(values []string) *Node {
	var head, tail *Node
	for _, value := range values {
		newNode := &Node{
			Num:  value,
			Next: nil,
		}
		if head == nil {
			head = newNode
			tail = newNode
		} else {
			tail.Next = newNode
			tail = newNode
		}
	}
	return head
}

func ListToVector(head *Node) []string {
	values := []string{}
	current := head
	for current != nil {
		values = append(values, current.Num)
		current = current.Next
	}
	return values
}

func AddNodeAfter(ptr *Node, key string) {
	newNode := &Node{
		Num:  key,
		Next: ptr.Next,
	}
	ptr.Next = newNode
}

func AddNodeBeginning(ptr *Node, key string) *Node {
	newNode := &Node{
		Num:  key,
		Next: ptr,
	}
	return newNode
}

func AddNodeEnd(ptr *Node, key string) {
	current := ptr
	for current.Next != nil {
		current = current.Next
	}
	newNode := &Node{
		Num:  key,
		Next: nil,
	}
	current.Next = newNode
}

func DeleteNode(head *Node, key string) *Node {
	if head != nil && key == head.Num {
		newHead := head.Next
		return newHead
	}
	current := head
	var prev *Node
	for current != nil && current.Num != key {
		prev = current
		current = current.Next
	}
	if current == nil {
		fmt.Println("Узел не найден")
		return head
	}
	prev.Next = current.Next
	return head
}

func SearchNode(head *Node, foundKey string) *Node {
	current := head
	for current != nil {
		if current.Num == foundKey {
			fmt.Println("Узел найден")
			return current
		}
		current = current.Next
	}
	fmt.Println("Узел не найден")
	return nil
}

func FPushAfter(values *[]string, existingKey, newValue string) bool {
	head := VectorToList(*values)
	ptr := SearchNode(head, existingKey)
	success := false
	if ptr != nil {
		AddNodeAfter(ptr, newValue)
		success = true
	}
	*values = ListToVector(head)
	return success
}

func FPushBeginning(values *[]string, key string) bool {
	head := VectorToList(*values)
	head = AddNodeBeginning(head, key)
	*values = ListToVector(head)
	return true
}

func FPushEnd(values *[]string, key string) bool {
	head := VectorToList(*values)
	if head == nil {
		head = AddNodeBeginning(head, key)
	} else {
		AddNodeEnd(head, key)
	}
	*values = ListToVector(head)
	return true
}

func FDel(values *[]string, key string) bool {
	head := VectorToList(*values)
	initialSize := len(*values)
	head = DeleteNode(head, key)
	*values = ListToVector(head)
	success := len(*values) < initialSize
	return success
}

func FGet(values []string, key string) bool {
	head := VectorToList(values)
	result := SearchNode(head, key)
	return result != nil
}
