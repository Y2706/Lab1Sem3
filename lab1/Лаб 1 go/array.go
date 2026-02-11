package main

import (
	"fmt"
	"strconv"
	"strings"
)

type Array struct {
	Data     []int
	Size     int
	Capacity int
}

func VectorToArray(values []string) *Array {
	arr := &Array{
		Size:     len(values),
		Capacity: len(values),
		Data:     make([]int, len(values)),
	}
	for i, val := range values {
		num, err := strconv.Atoi(val)
		if err == nil {
			arr.Data[i] = num
		} else {
			arr.Data[i] = 0
		}
	}
	return arr
}

func ArrayToVector(arr *Array) []string {
	values := make([]string, arr.Size)
	for i := 0; i < arr.Size; i++ {
		values[i] = strconv.Itoa(arr.Data[i])
	}
	return values
}

func MArrayCreate(values *[]string, sizeStr string) bool {
	size, err := strconv.Atoi(sizeStr)
	if err != nil {
		fmt.Println("Ошибка: неверный формат размера массива")
		return false
	}
	if size < 0 {
		fmt.Println("Ошибка: размер массива не может быть отрицательным")
		return false
	}
	arr := &Array{
		Size:     size,
		Capacity: size,
		Data:     make([]int, size),
	}
	for i := 0; i < arr.Size; i++ {
		arr.Data[i] = 0
	}
	*values = ArrayToVector(arr)
	fmt.Printf("Массив создан, размер: %d\n", size)
	return true
}

func MAdd(values *[]string, value string) bool {
	num, err := strconv.Atoi(value)
	if err != nil {
		fmt.Println("Ошибка: неверный формат числа")
		return false
	}
	arr := VectorToArray(*values)
	if arr.Size >= arr.Capacity {
		arr.Capacity = arr.Capacity * 2
		if arr.Capacity == 0 {
			arr.Capacity = 1
		}
		newData := make([]int, arr.Capacity)
		for i := 0; i < arr.Size; i++ {
			newData[i] = arr.Data[i]
		}
		arr.Data = newData
	}
	arr.Data[arr.Size] = num
	arr.Size++
	*values = ArrayToVector(arr)
	fmt.Printf("Элемент '%s' добавлен в конец массива\n", value)
	return true
}

func MIndexAdd(values *[]string, indexStr, value string) bool {
	index, err := strconv.Atoi(indexStr)
	if err != nil {
		fmt.Println("Ошибка: неверный формат индекса")
		return false
	}
	num, err := strconv.Atoi(value)
	if err != nil {
		fmt.Println("Ошибка: неверный формат числа")
		return false
	}
	arr := VectorToArray(*values)
	if index < 0 || index > arr.Size {
		fmt.Printf("Ошибка: некорректный индекс (%d). Допустимый диапазон: 0-%d\n", index, arr.Size)
		return false
	}
	if arr.Size >= arr.Capacity {
		arr.Capacity = arr.Capacity * 2
		if arr.Capacity == 0 {
			arr.Capacity = 1
		}
		newData := make([]int, arr.Capacity)
		for i := 0; i < arr.Size; i++ {
			newData[i] = arr.Data[i]
		}
		arr.Data = newData
	}
	for i := arr.Size; i > index; i-- {
		arr.Data[i] = arr.Data[i-1]
	}
	arr.Data[index] = num
	arr.Size++
	*values = ArrayToVector(arr)
	fmt.Printf("Элемент '%s' добавлен по индексу %d\n", value, index)
	return true
}

func MGet(values []string, indexStr string) bool {
	index, err := strconv.Atoi(indexStr)
	if err != nil {
		fmt.Println("Ошибка: неверный формат индекса")
		return false
	}
	arr := VectorToArray(values)
	if index < 0 || index >= arr.Size {
		fmt.Printf("Ошибка: некорректный индекс (%d). Допустимый диапазон: 0-%d\n", index, arr.Size-1)
		return false
	}
	fmt.Printf("Элемент по индексу %d: %d\n", index, arr.Data[index])
	return true
}

func MDeleteIndex(values *[]string, indexStr string) bool {
	index, err := strconv.Atoi(indexStr)
	if err != nil {
		fmt.Println("Ошибка: неверный формат индекса")
		return false
	}
	arr := VectorToArray(*values)
	if index < 0 || index >= arr.Size {
		fmt.Printf("Ошибка: некорректный индекс (%d). Допустимый диапазон: 0-%d\n", index, arr.Size-1)
		return false
	}
	removedValue := arr.Data[index]
	for i := index; i < arr.Size-1; i++ {
		arr.Data[i] = arr.Data[i+1]
	}
	arr.Size--
	*values = ArrayToVector(arr)
	fmt.Printf("Элемент '%d' удален по индексу %d\n", removedValue, index)
	return true
}

func MReplace(values *[]string, indexStr, value string) bool {
	index, err := strconv.Atoi(indexStr)
	if err != nil {
		fmt.Println("Ошибка: неверный формат индекса")
		return false
	}
	num, err := strconv.Atoi(value)
	if err != nil {
		fmt.Println("Ошибка: неверный формат числа")
		return false
	}
	arr := VectorToArray(*values)
	if index < 0 || index >= arr.Size {
		fmt.Printf("Ошибка: некорректный индекс (%d). Допустимый диапазон: 0-%d\n", index, arr.Size-1)
		return false
	}
	oldValue := arr.Data[index]
	arr.Data[index] = num
	*values = ArrayToVector(arr)
	fmt.Printf("Элемент по индексу %d заменен: '%d' -> '%s'\n", index, oldValue, value)
	return true
}

func MLength(values []string) bool {
	arr := VectorToArray(values)
	fmt.Printf("Длина массива: %d\n", arr.Size)
	return true
}
