import numpy as np
import matplotlib.pyplot as plt

# Example IOPS data for the four systems (replace with actual values as needed)
time_intervals = np.arange(0, 310, 10)  # Time intervals from 0 to 300 seconds, every 10 seconds

femu_without_hc =  [0,
    774.00, 158670.00, 150898.00, 146999.00, 147377.00, 147411.00, 148375.00, 147213.00,
    148471.00, 149082.00, 150415.00, 147444.00, 148757.00, 146231.00, 148189.00, 147685.00,
    146162.00, 146565.00, 146270.00, 146272.00, 148532.00, 148418.00, 149497.00, 147079.00,
    149592.00, 145426.00, 141506.00, 150222.00, 149074.00, 151170.00
]




femu_hc_a =[0,
    258.00, 73660.00, 139476.00, 142368.00, 142621.00, 141153.00, 130699.00, 137330.00,
    134010.00, 141701.00, 141845.00, 138542.00, 141600.00, 140602.00, 136731.00, 136331.00,
    139284.00, 134848.00, 140640.00, 142663.00, 143726.00, 145719.00, 144598.00, 146941.00,
    145789.00, 141234.00, 143311.00, 146546.00, 144767.00, 143411.00
]




femu_hc_b =  [0,
    521.00, 134089.00, 142342.00, 141166.00, 140230.00, 141037.00, 141417.00, 141624.00,
    139857.00, 144349.00, 141815.00, 140571.00, 141961.00, 140739.00, 141855.00, 142499.00,
    141552.00, 142359.00, 144456.00, 141384.00, 145561.00, 142254.00, 142942.00, 140542.00,
    146410.00, 140732.00, 144949.00, 144003.00, 144256.00, 135187.00
]








femu_hc_c = [0,265.00, 94767.00, 149459.00, 143574.00, 146584.00, 135776.00, 128226.00, 141012.00, 138441.00, 142493.00, 141424.00, 135551.00, 139119.00, 137008.00, 142200.00, 143556.00, 142528.00, 141888.00, 140438.00, 139624.00, 141849.00, 140466.00, 141267.00, 141863.00, 142882.00, 142388.00, 143596.00, 143518.00, 144097.00, 144239.00]








# Plot IOPS vs Time for the four systems
plt.figure(figsize=(12, 6))
plt.plot(time_intervals, femu_without_hc, label="FEMU without hot/cold separation")
plt.plot(time_intervals, femu_hc_a, label="FEMU with hot/cold separation (Threshold A)")
plt.plot(time_intervals, femu_hc_b, label="FEMU with hot/cold separation (Threshold B)")
plt.plot(time_intervals, femu_hc_c, label="FEMU with hot/cold separation (Threshold C)")

# Adding labels, title, legend, and grid
plt.title("IOPS vs Time ", fontsize=14)
plt.xlabel("Time (seconds, every 10s)", fontsize=12)
plt.ylabel("IOPS", fontsize=12)
plt.legend()
plt.grid(alpha=0.5)
plt.tight_layout()

# Display the plot
plt.show()