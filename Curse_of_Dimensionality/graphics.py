import numpy as np
import matplotlib.pyplot as plt

plt.style.use('dark_background');  

maze=np.loadtxt('build/tablas.txt',dtype=int)

print(maze)

eje_x = ['0', '0.1', '0.2', '0.3','0.4','0.5','0.6','0.7','0.8','0.9','1']
eje_y = maze[0]
fig, ax = plt.subplots(3,2,constrained_layout=True,figsize=(8,7))

colors=['white','red','green','purple','orange','blue']
dim=['2','5','10','15','20','25']
r=0
for i in range(3):
    for j in range(2):
        ax[i,j].bar(eje_x, maze[r],color=colors[r%6])
        ax[i,j].set_ylabel('Frecuencia de Distancias')
        ax[i,j].set_xlabel('Distancias')
        ax[i,j].set_title(dim[r]+' Dimensiones')
        r=r+1

plt.savefig("Curse of Dimensionality.png")
plt.show()
