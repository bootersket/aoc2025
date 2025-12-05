import random

count = 6
DIAL_SIZE = 4
for i in range(count):
    direction = random.choice(["R", "L"])
    distance = random.randint(1, DIAL_SIZE*40)
    print(f"{direction}{distance}")
