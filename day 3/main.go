package main

import (
	"bufio"
	"fmt"
	"os"
	"regexp"
	"strconv"
	"time"
)

func day3Test() int {
	file, err := os.Open("inputDay3.txt")
	if err != nil {
		fmt.Println("Error opening file:", err)
		return -1
	}
	defer file.Close()
	scanner := bufio.NewScanner(file)

	patternMul := `mul\(\d{1,3},\d{1,3}\)`
	patternDigit := `\d{1,}`

	regexMul := regexp.MustCompile(patternMul)
	regexDigit := regexp.MustCompile(patternDigit)

	sumAll := 0

	for scanner.Scan() {
		line := scanner.Text()
		matches := regexMul.FindAllString(line, -1)
		for _, match := range matches {
			digitMatches := regexDigit.FindAllString(match, -1)
			i := 1
			for _, d := range digitMatches {
				temp, _ := strconv.Atoi(d)
				i *= temp
			}
			sumAll += i

		}

	}
	return sumAll
}

func day3Part2() int {
	file, err := os.Open("inputDay3.txt")
	if err != nil {
		fmt.Println("Error opening file:", err)
		return -1
	}
	defer file.Close()
	scanner := bufio.NewScanner(file)

	patternMul := `mul\(\d{1,3},\d{1,3}\)|do\(\)|don't\(\)`

	patternDigit := `\d{1,}`

	regexMul := regexp.MustCompile(patternMul)
	regexDigit := regexp.MustCompile(patternDigit)

	sumAll := 0

	isDo := true

	for scanner.Scan() {
		line := scanner.Text()
		matches := regexMul.FindAllString(line, -1)
		for _, match := range matches {

			if match == "do()" {
				isDo = true
			} else if match == "don't()" {
				isDo = false

			} else {
				if isDo {
					digitMatches := regexDigit.FindAllString(match, -1)
					i := 1
					for _, d := range digitMatches {
						temp, _ := strconv.Atoi(d)
						i *= temp
					}
					sumAll += i
				}

			}

		}

	}
	return sumAll
}

// avg 1.1 ms for 2 parts

func main() {
	start := time.Now()
	i := day3Test()
	elapsed := time.Since(start)
	fmt.Println("The integer value is:", i)
	fmt.Printf("Time taken: %v\n", elapsed)

	start = time.Now()
	i = day3Part2()
	elapsed = time.Since(start)
	fmt.Println("The integer value is:", i)
	fmt.Printf("Time taken: %v\n", elapsed)

}
