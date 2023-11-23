import matplotlib.pyplot as plt
import subprocess
import time
import plotly.graph_objs as go
from plotly.subplots import make_subplots

def run_program(program_path, input_size):
    # Modifique o caminho do programa para incluir o tamanho da entrada
    specific_program_path = f"{program_path}{input_size}"
    
    start_time = time.time()
    result = subprocess.run([specific_program_path], capture_output=True, text=True)
    end_time = time.time()
    execution_time = end_time - start_time
    
    # Aqui você pode querer verificar se result.returncode == 0 para ter certeza de que o programa foi executado com sucesso
    
    return execution_time

# Caminhos base para os executáveis
serial_program_base_path = './exaustiva'
heuristic_1_program_base_path = './threads'

# Tamanhos de entrada correspondem aos sufixos dos nomes dos executáveis
input_sizes = [5, 10, 15, 20, 25]

# Executar os programas e obter os tempos de execução
tempo_serial = []
tempo_heuristica_1 = []
# tempo_heuristica_2 = []


for size in input_sizes:
    tempo_serial.append(run_program(serial_program_base_path, size))
    tempo_heuristica_1.append(run_program(heuristic_1_program_base_path, size))
    # tempo_heuristica_2.append(run_program(heuristic_2_program_path, size))

# Calcular speedups
speedup_1 = [tempo_serial[i] / tempo_heuristica_1[i] for i in range(len(input_sizes))]
# speedup_2 = [tempo_serial[i] / tempo_heuristica_2[i] for i in range(len(input_sizes))]

# Criar figura com subplots
fig = make_subplots(rows=1, cols=1, specs=[[{'secondary_y': True}]])

# Adicionar gráfico de barras para tempos de execução
fig.add_trace(
    go.Bar(x=input_sizes, y=tempo_serial, name='Serial', marker=dict(color='blue')),
    secondary_y=False,
)

fig.add_trace(
    go.Bar(x=input_sizes, y=tempo_heuristica_1, name='Heurística 1 (OpenMP)', marker=dict(color='green')),
    secondary_y=False,
)

# Adicionar gráfico de linha para speedup
fig.add_trace(
    go.Scatter(x=input_sizes, y=speedup_1, name='Speedup (OpenMP)', mode='lines+markers', line=dict(color='red', dash='dash')),
    secondary_y=True,
)

# Configurações do eixo x
fig.update_xaxes(title_text='Tamanho da Entrada')

# Configurações do eixo y primário
fig.update_yaxes(title_text='Tempo de Execução (s)', secondary_y=False)

# Configurações do eixo y secundário
fig.update_yaxes(title_text='Speedup', secondary_y=True)

# Atualizar layout da figura
fig.update_layout(title='Comparação de Tempo de Execução e Speedup', barmode='group')

# Mostrar figura
fig.show()
