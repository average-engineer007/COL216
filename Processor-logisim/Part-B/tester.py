import random


# Define the operations


def make_bin(x,r):
    ans = ""
    mask = 1

    for i in range(r):
        if (x & mask) != 0:
            ans = ans + '1'
        else:
            ans = ans + '0'
        mask = mask << 1
    return ans[::-1]


OPERATIONS = [0, 1, 2, 4, 5, 6, 7,8,9,11, 12, 13, 15]
operand_table = {
    0: "add",
    1: "sll",
    2: "slt",
    4: "xor",
    5: "srl",
    6: "or",
    7: "and",
    8: "mul",
    9: "mulh",
    11: "mulhu",
    12: "sub",
    13: "sra",
    15: "bsel"
}

def is_zero(x):
    mask = 1
    for i in range(32):
        if (x & mask) != 0:
            return False
        mask = mask << 1
    return  True



def get_5(x):
    temp = 0
    mask = 1
    r = 1
    for i in range(5):
        if (mask & x) != 0:
            temp = temp + r
        r = r * 2
        x = x >> 1
    return temp


def perform_operation(operand, A, B):
    if operand == 0:
        return A + B
    elif operand == 1:
        t = get_5(B)
        return A << t
    elif operand == 2:
        return 1 if A < B else 0
    elif operand == 4:
        return A ^ B
    elif operand == 5:
        t = get_5(B)
        return A >> t if A >= 0 else (A + 0x100000000) >> t
    elif operand == 6:
        return A | B
    elif operand == 7:
        return A & B
    elif operand == 8:
        return (A * B)
    elif operand == 9:
        return (A * B) >> 32
    elif operand == 11:
        return ((abs(A) * abs(B)) >> 32)
    elif operand == 12:
        return A - B
    elif operand == 13:
        t = get_5(B)
        return A >> t
    elif operand == 15:
        return B


# Function to perform the calculation
def calculate(a, b, operation):
    if operation == '+':
        return a + b
    elif operation == '-':
        return a - b
    elif operation == '*':
        return a * b
    elif operation == '/':
        if b != 0:
            return a // b
        else:
            return None


# Function to test the calculator with random inputs
def test_calculator(num_tests, output_file):
    with open(output_file, 'w') as file:
        file.write(f"A[32] B[32] ALUSel[4] Result[32] OverFlow Zero\n")
        for _ in range(num_tests):
            zero = 0
            a = random.randint(-(2 ** 31), 2 ** 31 - 1)  # 32-bit integer range
            b = random.randint(-(2 ** 31), 2 ** 31 - 1)
            operation = random.choice(OPERATIONS)
            # operation=0
            overflow=0
            result = perform_operation(operation, a, b)
            if(is_zero(result)):
                zero=1
            if operation == 0:
                if result > (2 ** 31 - 1) or result < -(2**31):
                    overflow = 1
                else:
                    overflow = 0
            if operation ==11 :
                a=abs(a)
                b = abs(b)
            file.write(f"{make_bin(a,32)} {make_bin(b,32)} {make_bin(operation,4)} {make_bin(result,32)} {overflow} {zero}\n")


# Test the calculator with 10 random inputs and write to "test_cases.txt"
test_calculator(10000, "test_cases.txt")
# print(make_bin(6))
# print(get_5(32))