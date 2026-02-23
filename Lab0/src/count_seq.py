import random
import time

# Number of elements
N = 100_000
TARGET = 42

# Create array
arr = [random.randint(0, 99) for _ in range(N)]

# Start timing
start = time.time()

# Count occurrences
count = sum(1 for x in arr if x == TARGET)

# End timing
end = time.time()

print(f"Count = {count}")
print(f"Time = {end - start:.2f} seconds")