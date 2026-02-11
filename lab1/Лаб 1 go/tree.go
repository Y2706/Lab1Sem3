package main

type TreeNode struct {
	Data   string
	Left   *TreeNode
	Right  *TreeNode
	Parent *TreeNode
}

func VectorToTree(values []string) *TreeNode {
	if len(values) == 0 {
		return nil
	}
	root := &TreeNode{
		Data:   values[0],
		Left:   nil,
		Right:  nil,
		Parent: nil,
	}
	nodeQueue := []*TreeNode{root}
	i := 1
	for i < len(values) && len(nodeQueue) > 0 {
		current := nodeQueue[0]
		nodeQueue = nodeQueue[1:]
		if i < len(values) && values[i] != "NULL" {
			leftNode := &TreeNode{
				Data:   values[i],
				Left:   nil,
				Right:  nil,
				Parent: current,
			}
			current.Left = leftNode
			nodeQueue = append(nodeQueue, leftNode)
		}
		i++
		if i < len(values) && values[i] != "NULL" {
			rightNode := &TreeNode{
				Data:   values[i],
				Left:   nil,
				Right:  nil,
				Parent: current,
			}
			current.Right = rightNode
			nodeQueue = append(nodeQueue, rightNode)
		}
		i++
	}
	return root
}

func TreeToVector(root *TreeNode) []string {
	if root == nil {
		return []string{}
	}
	values := []string{}
	nodeQueue := []*TreeNode{root}
	for len(nodeQueue) > 0 {
		current := nodeQueue[0]
		nodeQueue = nodeQueue[1:]
		if current != nil {
			values = append(values, current.Data)
			nodeQueue = append(nodeQueue, current.Left)
			nodeQueue = append(nodeQueue, current.Right)
		} else {
			values = append(values, "NULL")
		}
	}
	for len(values) > 0 && values[len(values)-1] == "NULL" {
		values = values[:len(values)-1]
	}
	return values
}

func TAdd(values *[]string, value string) bool {
	_, err := strconv.Atoi(value)
	if err != nil {
		if strings.Contains(value, " ") {
			fmt.Println("Ошибка: неверный формат значения")
			return false
		}
	}
	root := VectorToTree(*values)
	newNode := &TreeNode{
		Data:   value,
		Left:   nil,
		Right:  nil,
		Parent: nil,
	}
	if root == nil {
		root = newNode
	} else {
		nodeQueue := []*TreeNode{root}
		for len(nodeQueue) > 0 {
			current := nodeQueue[0]
			nodeQueue = nodeQueue[1:]
			if current.Left == nil {
				current.Left = newNode
				newNode.Parent = current
				break
			} else if current.Right == nil {
				current.Right = newNode
				newNode.Parent = current
				break
			} else {
				nodeQueue = append(nodeQueue, current.Left)
				nodeQueue = append(nodeQueue, current.Right)
			}
		}
	}
	*values = TreeToVector(root)
	fmt.Printf("Элемент '%s' добавлен в дерево\n", value)
	return true
}

func TSearch(values []string, value string) bool {
	root := VectorToTree(values)
	if root == nil {
		return false
	}
	nodeQueue := []*TreeNode{root}
	for len(nodeQueue) > 0 {
		current := nodeQueue[0]
		nodeQueue = nodeQueue[1:]
		if current.Data == value {
			fmt.Printf("Элемент '%s' найден в дереве\n", value)
			return true
		}
		if current.Left != nil {
			nodeQueue = append(nodeQueue, current.Left)
		}
		if current.Right != nil {
			nodeQueue = append(nodeQueue, current.Right)
		}
	}
	fmt.Printf("Элемент '%s' не найден в дереве\n", value)
	return false
}

func isFullBinaryTree(root *TreeNode) bool {
	if root == nil {
		return true
	}
	if root.Left == nil && root.Right == nil {
		return true
	}
	if root.Left != nil && root.Right != nil {
		return isFullBinaryTree(root.Left) && isFullBinaryTree(root.Right)
	}
	return false
}

func TIsFull(values []string) bool {
	root := VectorToTree(values)
	result := isFullBinaryTree(root)
	if result {
		fmt.Println("Дерево является полным бинарным деревом")
	} else {
		fmt.Println("Дерево не является полным бинарным деревом")
	}
	return result
}

func printTree(root *TreeNode, level int) {
	if root == nil {
		return
	}
	printTree(root.Right, level+1)
	for i := 0; i < level; i++ {
		fmt.Print("    ")
	}
	fmt.Println(root.Data)
	printTree(root.Left, level+1)
}

func TPrint(values []string) {
	root := VectorToTree(values)
	if root == nil {
		fmt.Println("Дерево пусто")
		return
	}
	fmt.Println("Дерево:")
	printTree(root, 0)
}
