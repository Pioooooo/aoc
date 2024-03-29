with open('in') as f:
    dat = [ln.strip().split(' @ ') for ln in f]
    dat = [([int(x) for x in p.split(',')], [int(x) for x in v.split(',')]) for p, v in dat]

import numpy as np

(p1, v1), (p2, v2), (p3, v3) = dat[:3]

A = np.array([
    [-(v1[1] - v2[1]), v1[0] - v2[0], 0, p1[1] - p2[1], -(p1[0] - p2[0]), 0],
    [-(v1[1] - v3[1]), v1[0] - v3[0], 0, p1[1] - p3[1], -(p1[0] - p3[0]), 0],

    [0, -(v1[2] - v2[2]), v1[1] - v2[1],  0, p1[2] - p2[2], -(p1[1] - p2[1])],
    [0, -(v1[2] - v3[2]), v1[1] - v3[1],  0, p1[2] - p3[2], -(p1[1] - p3[1])],

    [-(v1[2] - v2[2]), 0, v1[0] - v2[0],  p1[2] - p2[2], 0, -(p1[0] - p2[0])],
    [-(v1[2] - v3[2]), 0, v1[0] - v3[0],  p1[2] - p3[2], 0, -(p1[0] - p3[0])]
    ])

b = [
        (p1[1] * v1[0] - p2[1] * v2[0]) - (p1[0] * v1[1] - p2[0] * v2[1]),
        (p1[1] * v1[0] - p3[1] * v3[0]) - (p1[0] * v1[1] - p3[0] * v3[1]),

        (p1[2] * v1[1] - p2[2] * v2[1]) - (p1[1] * v1[2] - p2[1] * v2[2]),
        (p1[2] * v1[1] - p3[2] * v3[1]) - (p1[1] * v1[2] - p3[1] * v3[2]),

        (p1[2] * v1[0] - p2[2] * v2[0]) - (p1[0] * v1[2] - p2[0] * v2[2]),
        (p1[2] * v1[0] - p3[2] * v3[0]) - (p1[0] * v1[2] - p3[0] * v3[2])
     ]

x = np.linalg.solve(A, b)
print(round(sum(x[:3])))

