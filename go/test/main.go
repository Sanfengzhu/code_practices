package main

import (
    "fmt"
    //"math"
    //"runtime"
    //"time"
)

var(
    a bool = false
    b int = 2
    c int = 3
)

const(
    A = "aas"
    B int = 123
)

func main1() {
    //var d,e = "aaa",1231.2
    f := 123
    /*
    for f:=12 ;f > 0;f-- {
        e += float64(f)
    }
    */
    defer fmt.Println(f)
    defer fmt.Println("hahah")
    for f = 12; f > 0; f-=2 {
    }
    fmt.Println(f)
    /*
    var g int = int(e)
	fmt.Printf("hello %g\n", math.Nextafter(4, 3))
    fmt.Println(math.Pi)
    fmt.Println(add(1,2))
    fmt.Println(add2(2,3))
    x,y := swap("bao", "renyi")
    fmt.Println(y,x)
    fmt.Println(op(9))
    fmt.Println(a,b,c,d,e,f)
    fmt.Printf("%T(%v)\n",a,a)
    fmt.Println(e,g)
    fmt.Println(A,B)
    switch os:=runtime.GOOS; os {
    case "linux":
        fmt.Println(os)
    case "mac":
        fmt.Println("mac")
    default:
        fmt.Println("unknow")
    }
    t:=time.Now()
    fmt.Printf("%T(%v)\n",t,t)
    */
}

func op(a int) (b, c int) {
    b = a * 2
    c = a / 2
    return
}

func add(x int ,y int) int {
    return x+y
}

func add2(x, y int) int {
    return x + y
}

func swap(x, y string) (string, string) {
    return y, x
}

