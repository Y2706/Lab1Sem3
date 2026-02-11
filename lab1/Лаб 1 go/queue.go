package main

type QNode struct {
	Data string
	Next *QNode
}

type Queue struct {
	Front *QNode
	Rear  *QNode
}

func VectorToQueue(values []string) *Queue {
	q := &Queue{
		Front: nil,
		Rear:  nil,
	}
	for _, value := range values {
		newNode := &QNode{
			Data: value,
			Next: nil,
		}
		if q.Rear == nil {
			q.Front = newNode
			q.Rear = newNode
		} else {
			q.Rear.Next = newNode
			q.Rear = newNode
		}
	}
	return q
}

func QueueToVector(q *Queue) []string {
	values := []string{}
	current := q.Front
	for current != nil {
		values = append(values, current.Data)
		current = current.Next
	}
	return values
}

func QPush(values *[]string, value string) bool {
	q := VectorToQueue(*values)
	newNode := &QNode{
		Data: value,
		Next: nil,
	}
	if q.Rear == nil {
		q.Front = newNode
		q.Rear = newNode
	} else {
		q.Rear.Next = newNode
		q.Rear = newNode
	}
	*values = QueueToVector(q)
	fmt.Printf("Элемент '%s' добавлен в очередь\n", value)
	return true
}

func QPop(values *[]string) bool {
	q := VectorToQueue(*values)
	if q.Front == nil {
		fmt.Println("Ошибка: очередь пуста")
		return false
	}
	poppedValue := q.Front.Data
	q.Front = q.Front.Next
	if q.Front == nil {
		q.Rear = nil
	}
	*values = QueueToVector(q)
	fmt.Printf("Элемент '%s' удален из очереди\n", poppedValue)
	return true
}
