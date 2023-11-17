import matplotlib.pyplot as plt
import subprocess
import time

def run_program(program_path, input_size):
    start_time = time.time()
    result = subprocess.run([program_path, str(input_size)], capture_output=True, text=True)
    end_time = time.time()
    execution_time = end_time - start_time
    return execution_time

# Caminhos para os executáveis
serial_program_path = './exaustiva'
heuristic_1_program_path = './threads'
# heuristic_2_program_path = './seu_programa_heuristica_2'

# Tamanhos de entrada
input_sizes = [5, 10, 50, 100]

# Executar os programas e obter os tempos de execução
tempo_serial = []
tempo_heuristica_1 = []
# tempo_heuristica_2 = []

for size in input_sizes:
    tempo_serial.append(run_program(serial_program_path, size))
    tempo_heuristica_1.append(run_program(heuristic_1_program_path, size))
    # tempo_heuristica_2.append(run_program(heuristic_2_program_path, size))

# Calcular speedups
speedup_1 = [tempo_serial[i] / tempo_heuristica_1[i] for i in range(len(input_sizes))]
# speedup_2 = [tempo_serial[i] / tempo_heuristica_2[i] for i in range(len(input_sizes))]

# Criar gráficos
fig, ax1 = plt.subplots()

ax1.bar(input_sizes, tempo_serial, color='blue', label='Serial')
ax1.bar(input_sizes, tempo_heuristica_1, color='green', label='Heurística 1')
# ax1.bar(input_sizes, tempo_heuristica_2, color='orange', label='Heurística 2')

ax2 = ax1.twinx()
ax2.plot(input_sizes, speedup_1, color='red', linestyle='dashed', marker='o', label='Speedup (Heurística 1)')
# ax2.plot(input_sizes, speedup_2, color='purple', linestyle='dashed', marker='o', label='Speedup (Heurística 2)')

ax1.set_xlabel('Tamanho da Entrada')
ax1.set_ylabel('Tempo de Execução (s)', color='black')
ax2.set_ylabel('Speedup', color='black')
ax1.legend(loc='upper left')
ax2.legend(loc='upper right')

plt.title('Comparação de Tempo de Execução e Speedup')
plt.show()
