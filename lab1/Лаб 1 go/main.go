package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

type Structure struct {
	Type   string
	Values []string
}

type DataBase map[string]Structure

func LoadData(filename string) DataBase {
	db := make(DataBase)
	file, err := os.Open(filename)
	if err != nil {
		fmt.Println("Файл не найден или пуст. Создание новой базы.")
		return db
	}
	defer file.Close()
	scanner := bufio.NewScanner(file)
	var currentName, currentType string
	for scanner.Scan() {
		line := scanner.Text()
		if line == "" {
			continue
		}
		if line[0] == '#' {
			header := line[1:]
			ss := strings.NewReader(header)
			var typeStr, name string
			if _, err := fmt.Fscanf(ss, "%s %s", &typeStr, &name); err == nil {
				currentName = name
				currentType = typeStr
				db[name] = Structure{
					Type:   typeStr,
					Values: []string{},
				}
			}
		} else if currentName != "" {
			s := db[currentName]
			s.Values = append(s.Values, line)
			db[currentName] = s
		}
	}
	return db
}

func SaveData(filename string, db DataBase) {
	file, err := os.Create(filename)
	if err != nil {
		fmt.Printf("Ошибка: Не удалось открыть файл для записи: %s\n", filename)
		return
	}
	defer file.Close()
	for name, s := range db {
		file.WriteString(fmt.Sprintf("# %s %s\n", s.Type, name))
		for _, value := range s.Values {
			file.WriteString(fmt.Sprintf("%s\n", value))
		}
	}
}

func main() {
	if len(os.Args) != 5 {
		fmt.Println("Ошибка: Неверный формат аргументов")
		os.Exit(1)
	}
	key1 := os.Args[1]
	key2 := os.Args[3]
	if key1 != "--file" || key2 != "--query" {
		fmt.Println("Ошибка: Неверный формат аргументов")
		os.Exit(1)
	}
	file := os.Args[2]
	query := os.Args[4]
	db := LoadData(file)
	parts := strings.Fields(query)
	if len(parts) < 2 {
		fmt.Println("Ошибка: Неверный формат ввода")
		os.Exit(1)
	}
	command := parts[0]
	structName := parts[1]
	var param1, param2 string
	if len(parts) > 2 {
		param1 = parts[2]
	}
	if len(parts) > 3 {
		param2 = parts[3]
	}
	if command == "PRINT" {
		s, exists := db[structName]
		if !exists {
			fmt.Printf("Структура %s не существует\n", structName)
			os.Exit(1)
		}
		fmt.Printf("Содержимое %s (%s): ", structName, s.Type)
		if len(s.Values) == 0 {
			fmt.Println("Пусто")
		} else {
			for _, val := range s.Values {
				fmt.Printf("%s ", val)
			}
			fmt.Println()
		}
	} else {
		s := db[structName]
		if s.Type == "" {
			if len(command) > 0 {
				switch command[0] {
				case 'M':
					s.Type = "ARRAY"
				case 'F':
					s.Type = "LIST"
				case 'L':
					s.Type = "DUAL_LIST"
				case 'Q':
					s.Type = "QUEUE"
				case 'S':
					s.Type = "STACK"
				case 'T':
					s.Type = "TREE"
				}
			}
		}
		values := s.Values
		if s.Type == "" {
			fmt.Printf("Ошибка: Структура %s не имеет определённого типа\n", structName)
			os.Exit(1)
		}
		var success bool
		if s.Type == "LIST" {
			switch command {
			case "FPUSH":
				success = FPushBeginning(&values, param1)
			case "FADD_END":
				success = FPushEnd(&values, param1)
			case "FADD_AFTER":
				success = FPushAfter(&values, param1, param2)
			case "FDEL":
				success = FDel(&values, param1)
			case "FGET":
				success = FGet(values, param1)
			default:
				fmt.Printf("Ошибка: Неизвестная команда LIST: %s\n", command)
				os.Exit(1)
			}
		} else if s.Type == "DUAL_LIST" {
			switch command {
			case "LPUSH_LEFT":
				success = LPushLeft(&values, param1)
			case "LPUSH_RIGHT":
				success = LPushRight(&values, param1)
			case "LADD_BEFORE":
				success = LAddBefore(&values, param1, param2)
			case "LADD_AFTER":
				success = LAddAfter(&values, param1, param2)
			case "LDEL":
				success = LDel(&values, param1)
			case "LGET":
				success = LGet(values, param1)
			default:
				fmt.Printf("Ошибка: Неизвестная команда DUAL_LIST: %s\n", command)
				os.Exit(1)
			}
		} else if s.Type == "ARRAY" {
			switch command {
			case "MARRAY":
				success = MArrayCreate(&values, param1)
			case "MADD":
				success = MAdd(&values, param1)
			case "MINDEXADD":
				success = MIndexAdd(&values, param1, param2)
			case "MGET":
				success = MGet(values, param1)
			case "MDELETE":
				success = MDeleteIndex(&values, param1)
			case "MREPLACE":
				success = MReplace(&values, param1, param2)
			case "MLENGTH":
				success = MLength(values)
			default:
				fmt.Printf("Ошибка: Неизвестная команда ARRAY: %s\n", command)
				os.Exit(1)
			}
		} else if s.Type == "QUEUE" {
			switch command {
			case "QPUSH":
				success = QPush(&values, param1)
			case "QPOP":
				success = QPop(&values)
			default:
				fmt.Printf("Ошибка: Неизвестная команда QUEUE: %s\n", command)
				os.Exit(1)
			}
		} else if s.Type == "STACK" {
			switch command {
			case "SPUSH":
				success = SPush(&values, param1)
			case "SPOP":
				success = SPop(&values)
			default:
				fmt.Printf("Ошибка: Неизвестная команда STACK: %s\n", command)
				os.Exit(1)
			}
		} else if s.Type == "TREE" {
			switch command {
			case "TADD":
				success = TAdd(&values, param1)
			case "TSEARCH":
				success = TSearch(values, param1)
			case "TISFULL":
				success = TIsFull(values)
			case "TPRINT":
				TPrint(values)
				success = true
			default:
				fmt.Printf("Ошибка: Неизвестная команда TREE: %s\n", command)
				os.Exit(1)
			}
		} else {
			fmt.Printf("Ошибка: Неизвестный тип структуры: %s\n", s.Type)
			os.Exit(1)
		}
		if !success {
			os.Exit(1)
		}
		s.Values = values
		db[structName] = s
	}
	SaveData(file, db)
}
