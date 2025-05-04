TABLE_SIZE = 10

class Node:
    def __init__(self, fruit, rate):
        self.fruit = fruit
        self.rate = rate
        self.next = None

class Dictionary:
    def __init__(self):
        self.table = [None] * TABLE_SIZE

    def hash_function(self, key):
        return sum(ord(ch) for ch in key) % TABLE_SIZE

    def insert(self, fruit, rate):
        index = self.hash_function(fruit)
        current = self.table[index]

        while current:
            if current.fruit == fruit:
                print("Fruit already exists. Updating rate.")
                current.rate = rate
                return
            current = current.next

        new_node = Node(fruit, rate)
        new_node.next = self.table[index]
        self.table[index] = new_node
        print(f"Inserted at hash index {index}: ({fruit}, ₹{rate})")

    def find(self, fruit):
        index = self.hash_function(fruit)
        current = self.table[index]

        while current:
            if current.fruit == fruit:
                print(f"Found at index {index}: ({fruit}, ₹{current.rate})")
                return
            current = current.next

        print(f'Fruit "{fruit}" not found.')

    def remove(self, fruit):
        index = self.hash_function(fruit)
        current = self.table[index]
        prev = None

        while current:
            if current.fruit == fruit:
                if prev is None:
                    self.table[index] = current.next
                else:
                    prev.next = current.next
                print(f'Deleted fruit "{fruit}" from index {index}')
                return
            prev = current
            current = current.next

        print("Fruit not found.")

    def display(self):
        print("\nHash Table (Index → Fruit → Rate):")
        for i in range(TABLE_SIZE):
            print(f"Index {i}:", end=" ")
            current = self.table[i]
            if not current:
                print("Empty")
            else:
                while current:
                    print(f"({current.fruit}, ₹{current.rate})", end=" → " if current.next else "")
                    current = current.next
                print()

def main():
    dictionary = Dictionary()

    while True:
        print("\n--- Fruit Rate Dictionary Menu ---")
        print("1. Insert Fruit and Rate")
        print("2. Find Fruit Rate")
        print("3. Delete Fruit")
        print("4. Display All")
        print("5. Exit")

        choice = input("Enter your choice: ")

        if choice == '1':
            while True:
                fruit = input("Enter fruit name: ")
                try:
                    rate = float(input("Enter rate: ₹"))
                except ValueError:
                    print("Invalid rate. Please enter a number.")
                    continue
                dictionary.insert(fruit, rate)
                more = input("Do you want to add more fruits (y/n)? ")
                if more.lower() != 'y':
                    break

        elif choice == '2':
            fruit = input("Enter fruit name to find: ")
            dictionary.find(fruit)

        elif choice == '3':
            fruit = input("Enter fruit name to delete: ")
            dictionary.remove(fruit)

        elif choice == '4':
            dictionary.display()

        elif choice == '5':
            print("Thank you for using the Fruit Dictionary.")
            break

        else:
            print("Invalid input! Please enter a valid choice.")

if __name__ == "__main__":
    main()
