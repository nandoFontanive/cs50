import cs50
#ou
from cs50 import get_int

name = input("Digite nome: ")
if name == "Alice":
    print(f"Hello {name}")

list = [0, 1, 2]
list.append(3)
list.remove(0)

for _ in range(0,3,1):#(start(inclusive, end(exclusive, ou .len),step))
    print _

n = 0
while n < 3:
    print(i)
    n += 1

phrase = "wahoo"
phrase[0] = "w"
phrase[1:3:1] = "ah"

def function(x):
    return x

import sys
def main():
    if len(sys.argv) > 1:
        print(sys.argv[1])

for i in range(len(phrase) -1, -1, -1):
    print(phrase[i], end="")

songs = {"name": "Perfect, "tempo": 95.05}

songs["tempo"] = "100" #atualiza valor
songs["album": "divide"] #adiciona novo par chave-valor
songs.keys()# -> retorna keys
songs.values()# -> retorna values

with open(2018.csv) as file:
    file_reader = csv.DictReader(file)
#cada linha vira uma lista de dict
    for row in file_reader:
        ...
#############
def main():
    min_tempo = get_int("Minimum tempo: ")
    max_tempo = get_int("Maximum tempo: ")

    playlist = []
    with open("2018.csv") as file:
        reader = csv.DictReader(file)
        for song in reader:
        tempo = float(song["Tempo"])
        if tempo >= min_tempo and tempo <= max_tempo:
            playlist.append(song)

    for song in playlist:
        print(song["name"])

==============
#shorts
pizzas = {
    "cheese": 9,
    "pepperoni": 10,
    "vegetable": 11,
    "buffalo": 12
}

for pie in pizzas: #mostra sabores
    print()

for pie, price in pizzas.items(): #usa .items pra chamar os values
    print(price)
    print("A {} pizza costs {}".format(pie, price))
