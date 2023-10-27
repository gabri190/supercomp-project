import matplotlib.pyplot as plt
# import subprocess

# for _ in range(10):
#     result = subprocess.run(['./seu_programa'], capture_output=True, text=True)
#     print(result.stdout)
#tempos ainda serão rodados pelo executavel
tempo_serial = 10
tempo_heuristica_1 = 2
tempo_heuristica_2 = 4
speedup_1 = tempo_serial / tempo_heuristica_1
speedup_2 = tempo_serial / tempo_heuristica_2

labels = ['Serial', 'paralelização','Threads']
times = [tempo_serial, tempo_heuristica_1,tempo_heuristica_2]

plt.bar(labels, times, color=['blue', 'green','red'])
plt.ylabel('Tempo (s)')
plt.title(f'Speedup Paralelização e por threads: {speedup_1:.2f}x e {speedup_2:.2f}x respectivamente')
plt.show()

