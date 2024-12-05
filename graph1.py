import numpy as np
import matplotlib.pyplot as plt

access_counts = [0,
  107388.00,    7075.00,     223.00,       1.00,       1.00,
      2.00,      15.00,      85.00,     254.00,     760.00,
   1912.00,    3868.00,    7239.00,   11589.00,   15891.00,
  19778.00,   21016.00,   19915.00,   16847.00,   12413.00,
   7841.00,    4525.00,    2119.00,     914.00,     335.00,
    106.00,      26.00,       6.00,
]


lpn = np.zeros(len(access_counts))
lpn[:len(access_counts)] = np.arange(0, len(access_counts))

# 누적 분포 계산
cumulative_distribution = np.cumsum(access_counts) / np.sum(access_counts)

# 그래프 그리기
plt.figure(figsize=(10, 6))
plt.plot(lpn, cumulative_distribution, linestyle='-', label="Cumulative Distribution of LPNs")

# x축 눈금 설정
xticks_positions = np.concatenate((
    np.arange(0, 27, 1),   # 0부터 400까지 100단위
))
xticks_labels = [str(int(x)) for x in xticks_positions]
plt.xticks(xticks_positions, xticks_labels)

# 레이블 및 제목 추가
plt.title("Cumulative Distribution of LPNs vs Access Count", fontsize=14)
plt.xlabel("Access Count (LPNs)", fontsize=12)
plt.ylabel("Cumulative Distribution (CDF)", fontsize=12)
plt.grid(alpha=0.5)
plt.legend()
plt.tight_layout()

# 그래프 표시
plt.show()