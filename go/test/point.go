package main

import(
    "fmt"
)

type Person struct {
    name string
    sex bool
}

var (
    p = Person{"baorenyi",true}
    ptpr = &p
    arr [2]string
    sli = []int{12,23,24}
)

func main(){
    var i int = 10
    iptr :=&i
    fmt.Println(i,iptr,*iptr)
    p.name = "he"
    ptpr.name = "aaa"
    p1 := Person {name:"yangliu"}
    fmt.Println(p1)
    fmt.Println(*ptpr)
    arr[0] = "bao"
    arr[1] = "renyi"
    fmt.Println(arr)
    fmt.Println(arr[0],arr[1])
    for i:=0; i< len(arr) && i < len(sli); i++ {
        fmt.Printf(arr[i])
        fmt.Printf("%v",sli[i])
    }

    p := sli[1:2]
    fmt.Println(p)

    q := make([]int, 5, 5)
    fmt.Printf("%d %d\n",len(q),cap(q))
    for i:=0; i< cap(q); i++ {
        q[i] = i
    }

    r := make([]int, 0, 0)
    var s []int
    switch {
        case r == nil:
            fmt.Println("r")
        case s == nil:
            fmt.Println("s")
    }
    if r == nil {
        fmt.Println("aaa")
    }

    fmt.Println("Before S %d, %d",len(s),cap(s))
    s1 := append(s,1,2,3,4)
    fmt.Println("After S %d, %d",len(s),cap(s))
    fmt.Println("New S1 %d, %d",len(s1),cap(s1))
    for i,v:=range s1 {
        fmt.Printf("%d=%d\t",i,v)
    }
    for i:=range s1 {
        fmt.Printf("%d\t",i)
    }
    for _, v:=range s1 {
        fmt.Printf("%d\t",v)
    }
    fmt.Println()

    var m = make(map[string]Person)
    m["NB"] = p1
    m["NB2"] = p1
    var m1 =  map[string]Person{
        "NB3":p1,
    }
    fmt.Println(m)
    fmt.Println(m1)
    for k,v :=range m {
        fmt.Printf("%s,%T,%s,%v\n",k,v,v.name,v.sex)
    }
    delete(m,"NB2")
    v,k := m["MB3"]
    fmt.Printf("k=%g,v=%v\n",k,v)
    for k,v :=range m {
        fmt.Printf("%s,%T,%s,%v\n",k,v,v.name,v.sex)
    }
}
