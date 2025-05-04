size = 10
hashtable = [0] * size
hashtable1 = [0] * size

def hash_v(num):
    index = num % size
    while hashtable[index] != 0:
        index = (index + 1) % size
    hashtable[index] = num

def quadratic_v(num):
    index = num % size
    if hashtable1[index] == 0:
        hashtable1[index] = num
    else:
        for k in range(1, size):
            t = (index + k * k) % size
            if hashtable1[t] == 0:
                hashtable1[t] = num
                break

def find(num, hash_table):
    index = num % size
    start_index = index

    while hash_table[index] != 0:
        if hash_table[index] == num:
            print("Found", num)
            return
        index = (index + 1) % size
        if index == start_index:
            break
    print("Not found", num)

def main():
    while True:
        print("\n1. Linear Probing")
        print("2. Quadratic Probing")
        print("3. Find Element")
        print("4. Exit")
        cd = int(input("Enter choice: "))
        
        if cd == 1:
            n = int(input("Enter total elements: "))
            for j in range(n):
                h = int(input("Enter phone number: "))
                hash_v(h)
            print("Hashtable using linear probing is:", hashtable)
        
        elif cd == 2:
            m = int(input("Enter total elements: "))
            for j in range(m):
                q = int(input("Enter phone number: "))
                quadratic_v(q)
            print("Hashtable using quadratic probing is:", hashtable1)
        
        elif cd == 3:
            num = int(input("Enter number to be found: "))
            print("Search in linear probing:")
            find(num, hashtable)
            print("Search in quadratic probing:")
            find(num, hashtable1)
        
        elif cd == 4:
            print("End of Program")
            break
        else:
            print("Enter a valid choice")

main()
