import numpy as np
import matplotlib.pyplot as plt

# Example IOPS data for the four systems (replace with actual values as needed)
time_intervals = np.arange(0, 310, 10)  # Time intervals from 0 to 300 seconds, every 10 seconds

femu_without_hc = [
    1.00, 1.00, 1.00, 2.43, 2.79, 2.82, 2.84, 2.82, 2.79, 2.86, 
    2.77, 2.84, 2.79, 2.86, 2.81, 2.88, 2.83, 2.86, 2.81, 2.84, 
    2.87, 2.82, 2.86, 2.82, 2.85, 2.84, 2.83, 2.87, 2.82, 2.86, 
    2.82


]

femu_hc_a =  [
    1.00, 1.32, 2.48, 2.91, 2.83, 2.83, 2.84, 2.80, 2.82, 2.80, 
    2.81, 2.81, 2.91, 2.85, 2.84, 2.83, 2.84, 2.82, 2.74, 2.71, 
    2.62, 2.62, 2.66, 2.63, 2.66, 2.65, 2.63, 2.63, 2.65, 2.59, 
    2.65




]

femu_hc_b = [
    1.00, 1.00, 1.32, 2.51, 2.90, 2.84, 2.82, 2.83, 2.84, 2.80, 2.82, 
    2.80, 2.80, 2.90, 2.83, 2.84, 2.87, 2.80, 2.85, 2.78, 2.78, 2.76, 
    2.66, 2.66, 2.62, 2.65, 2.63, 2.67, 2.59, 2.62, 2.62

]


femu_hc_c =  [
    1.00, 2.03, 2.79, 2.80, 2.81, 2.83, 2.79, 2.80, 2.84, 2.88, 2.86, 
    2.84, 2.84, 2.83, 2.81, 2.82, 2.81, 2.84, 2.87, 2.82, 2.83, 2.82, 
    2.80, 2.75, 2.71, 2.63, 2.65, 2.65, 2.65, 2.63, 2.63
]


# Plot IOPS vs Time for the four systems
plt.figure(figsize=(12, 6))
colors = plt.cm.tab10(np.linspace(0, 1, 4))
plt.plot(time_intervals, femu_without_hc, marker='o', label="FEMU without Threshold", markersize=3)
plt.plot(time_intervals, femu_hc_a, marker='o', label="FEMU with Threshold 17", markersize=3)
plt.plot(time_intervals, femu_hc_b, marker='o', label="FEMU with Threshold 18", markersize=3)
plt.plot(time_intervals, femu_hc_c, marker='o', label="FEMU with Threshold 20", markersize=3)
# Adding labels, title, legend, and grid
plt.title("WAF vs Time", fontsize=14)
plt.xlabel("Time (Every 10s)", fontsize=12)
plt.ylabel("WAF", fontsize=12)
plt.legend()
plt.grid(alpha=0.5)
plt.xticks(np.arange(0, 310, 10))
plt.tight_layout()

# Display the plot
plt.show()