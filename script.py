import matplotlib.pyplot as plt
import subprocess
import time

def run_program(program_path):
    start_time = time.time()
    result = subprocess.run([program_path], capture_output=True, text=True)
    end_time = time.time()
    execution_time = end_time - start_time
    return execution_time

# Caminhos para os executáveis
serial_program_path = './exaustiva'
heuristic_1_program_path = './threads'
# heuristic_2_program_path = './seu_programa_heuristica_2'

# Executar os programas e obter os tempos de execução
tempo_serial = run_program(serial_program_path)
tempo_heuristica_1 = run_program(heuristic_1_program_path)
# tempo_heuristica_2 = run_program(heuristic_2_program_path)

speedup_1 = tempo_serial / tempo_heuristica_1
# speedup_2 = tempo_serial / tempo_heuristica_2

labels = ['Serial', 'Heurística 1']
times = [tempo_serial, tempo_heuristica_1]

plt.bar(labels, times, color=['blue', 'green'])
plt.ylabel('Tempo (s)')
plt.title(f'Speedup Heurística 1 : {speedup_1:.2f}x')
plt.show()