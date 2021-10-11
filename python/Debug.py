will_print = False

leaders = [
    "",
    "----> ",  # 1
    "      ",  # 2
    "====> ",  # 3
    "  ==> ",  # 4
    "    > ",  # 5
    "##### ",  # 6
]

def Print(text, leader=0):
    if will_print:
        print(leaders[leader], text, end="")

def Print_nline(text, leader=2):
    if will_print:
        print(leaders[leader], text)
