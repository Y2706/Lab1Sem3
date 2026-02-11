package main

type DualNode struct {
	Name string
	Prev *DualNode
	Next *DualNode
}

func VectorToDualList(values []string) *DualNode {
	var head, tail *DualNode
	for _, value := range values {
		newNode := &DualNode{
			Name: value,
			Next: nil,
		}
		if head == nil {
			newNode.Prev = nil
			head = newNode
			tail = newNode
		} else {
			newNode.Prev = tail
			tail.Next = newNode
			tail = newNode
		}
	}
	return head
}

func DualListToVector(head *DualNode) []string {
	values := []string{}
	current := head
	for current != nil {
		values = append(values, current.Name)
		current = current.Next
	}
	return values
}

func AddNodeBeginning(head *DualNode, name string) *DualNode {
	newNode := &DualNode{
		Name: name,
		Next: head,
		Prev: nil,
	}
	if head != nil {
		head.Prev = newNode
	}
	return newNode
}

func AddNodeEnd(head *DualNode, name string) {
	current := head
	for current.Next != nil {
		current = current.Next
	}
	newNode := &DualNode{
		Name: name,
		Prev: current,
		Next: nil,
	}
	current.Next = newNode
}

func AddNodeAfter(ptr *DualNode, name string) {
	newNode := &DualNode{
		Name: name,
		Next: ptr.Next,
		Prev: ptr,
	}
	ptr.Next = newNode
	if newNode.Next != nil {
		newNode.Next.Prev = newNode
	}
}

func AddNodeBefore(head, ptr *DualNode, name string) *DualNode {
	newNode := &DualNode{
		Name: name,
	}
	if ptr == head {
		newNode.Next = ptr
		newNode.Prev = nil
		ptr.Prev = newNode
		return newNode
	}
	newNode.Next = ptr
	newNode.Prev = ptr.Prev
	ptr.Prev.Next = newNode
	ptr.Prev = newNode
	return head
}

func NodeFound(head *DualNode, name string) *DualNode {
	current := head
	for current != nil {
		if current.Name == name {
			fmt.Println("Узел найден")
			return current
		}
		current = current.Next
	}
	fmt.Println("Узел не найден")
	return nil
}

func DeleteNode(head *DualNode, name string) *DualNode {
	ptr := head
	for ptr != nil && ptr.Name != name {
		ptr = ptr.Next
	}
	if ptr == nil {
		fmt.Println("Ошибка: узел не найден")
		return head
	}
	if ptr.Prev != nil {
		ptr.Prev.Next = ptr.Next
	} else {
		head = ptr.Next
	}
	if ptr.Next != nil {
		ptr.Next.Prev = ptr.Prev
	}
	return head
}

func LPushLeft(values *[]string, key string) bool {
	head := VectorToDualList(*values)
	head = AddNodeBeginning(head, key)
	*values = DualListToVector(head)
	return true
}

func LPushRight(values *[]string, key string) bool {
	head := VectorToDualList(*values)
	if head == nil {
		head = AddNodeBeginning(head, key)
	} else {
		AddNodeEnd(head, key)
	}
	*values = DualListToVector(head)
	return true
}

func LAddBefore(values *[]string, existingKey, newValue string) bool {
	head := VectorToDualList(*values)
	ptr := NodeFound(head, existingKey)
	success := false
	if ptr != nil {
		head = AddNodeBefore(head, ptr, newValue)
		success = true
	}
	*values = DualListToVector(head)
	return success
}

func LAddAfter(values *[]string, existingKey, newValue string) bool {
	head := VectorToDualList(*values)
	ptr := NodeFound(head, existingKey)
	success := false
	if ptr != nil {
		AddNodeAfter(ptr, newValue)
		success = true
	}
	*values = DualListToVector(head)
	return success
}

func LDel(values *[]string, key string) bool {
	head := VectorToDualList(*values)
	initialSize := len(*values)
	head = DeleteNode(head, key)
	*values = DualListToVector(head)
	success := len(*values) < initialSize
	return success
}

func LGet(values []string, key string) bool {
	head := VectorToDualList(values)
	NodeFound(head, key)
	return true
}
