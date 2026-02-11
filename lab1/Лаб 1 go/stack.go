package main

type SNode struct {
	Data string
	Next *SNode
}

func VectorToStack(values []string) *SNode {
	var head *SNode
	for i := len(values) - 1; i >= 0; i-- {
		newNode := &SNode{
			Data: values[i],
			Next: head,
		}
		head = newNode
	}
	return head
}

func StackToVector(head *SNode) []string {
	values := []string{}
	current := head
	for current != nil {
		values = append(values, current.Data)
		current = current.Next
	}
	return values
}

func SPush(values *[]string, value string) bool {
	head := VectorToStack(*values)
	newNode := &SNode{
		Data: value,
		Next: head,
	}
	head = newNode
	*values = StackToVector(head)
	fmt.Printf("Элемент '%s' добавлен в стек\n", value)
	return true
}

func SPop(values *[]string) bool {
	head := VectorToStack(*values)
	if head == nil {
		fmt.Println("Ошибка: стек пуст")
		return false
	}
	poppedValue := head.Data
	head = head.Next
	*values = StackToVector(head)
	fmt.Printf("Элемент '%s' удален из стека\n", poppedValue)
	return true
}
