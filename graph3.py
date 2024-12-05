import numpy as np
import matplotlib.pyplot as plt

# Example IOPS data for the four systems (replace with actual values as needed)
time_intervals = np.arange(0, 310, 10)  # Time intervals from 0 to 300 seconds, every 10 seconds

femu_without_hc = [
    1.00, 1.12, 1.76, 2.15, 2.40, 2.58, 2.72, 2.83, 2.91, 2.98, 3.04, 3.09, 3.13, 3.17,
    3.20, 3.23, 3.26, 3.28, 3.30, 3.33, 3.34, 3.36, 3.38, 3.39, 3.41, 3.42, 3.43, 3.44,
    3.45, 3.46, 3.47
]

femu_hc_a =   [
    1.00, 1.00, 1.41, 1.74, 1.97, 2.13, 2.26, 2.36, 2.45, 2.51, 2.57, 2.62, 2.66, 2.70,
    2.73, 2.76, 2.80, 2.82, 2.85, 2.87, 2.89, 2.91, 2.93, 2.94, 2.96, 2.97, 2.99, 3.00,
    3.02, 3.03, 3.04
]

femu_hc_b = [
    1.00, 1.04, 1.49, 1.73, 1.93, 2.11, 2.24, 2.33, 2.41, 2.47, 2.53, 2.58, 2.62, 2.66,
    2.69, 2.72, 2.74, 2.77, 2.79, 2.81, 2.83, 2.85, 2.86, 2.88, 2.89, 2.91, 2.92, 2.93,
    2.94, 2.96, 2.97
]


femu_hc_c =  [
    1.00, 1.04, 1.54, 1.78, 1.92, 2.03, 2.14, 2.24, 2.32, 2.40, 2.46, 2.50, 2.55, 2.58,
    2.62, 2.65, 2.67, 2.70, 2.72, 2.74, 2.75, 2.77, 2.79, 2.80, 2.82, 2.83, 2.84, 2.86,
    2.87, 2.88, 2.89
]


# Plot IOPS vs Time for the four systems
plt.figure(figsize=(12, 6))
colors = plt.cm.tab10(np.linspace(0, 1, 4))
plt.plot(time_intervals, femu_without_hc, marker='o', label="FEMU without Threshold", markersize=3)
plt.plot(time_intervals, femu_hc_a, marker='o', label="FEMU with Threshold 5", markersize=3)
plt.plot(time_intervals, femu_hc_b, marker='o', label="FEMU with Threshold 8", markersize=3)
plt.plot(time_intervals, femu_hc_c, marker='o', label="FEMU with Threshold 17", markersize=3)
# Adding labels, title, legend, and grid
plt.title("WAF vs Time (Zipfian distribution 0.8)", fontsize=14)
plt.xlabel("Time (Every 10s)", fontsize=12)
plt.ylabel("WAF", fontsize=12)
plt.legend()
plt.grid(alpha=0.5)
plt.xticks(np.arange(0, 310, 10))
plt.tight_layout()

# Display the plot
plt.show()