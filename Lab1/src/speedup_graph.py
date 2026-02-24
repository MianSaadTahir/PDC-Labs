import matplotlib.pyplot as plt

# Number of processes
processes = [1, 2, 4]

# Execution times from your experiment
times = [0.072654, 0.037879, 0.021391]

# Compute speedup
T1 = times[0]
speedup = [T1 / t for t in times]

# Ideal speedup
ideal = processes

# Plot
plt.figure()
plt.plot(processes, speedup, marker='o', label='Actual Speedup')
plt.plot(processes, ideal, linestyle='--', label='Ideal Speedup')

plt.xlabel("Number of Processes")
plt.ylabel("Speedup")
plt.title("MPI Counting Program Speedup")
plt.legend()
plt.grid(True)

# Save figure for LaTeX
plt.savefig("speedup_graph.png", dpi=300)

plt.show()