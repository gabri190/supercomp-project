import matplotlib.pyplot as plt
import subprocess
import time
import plotly.graph_objs as go
from plotly.subplots import make_subplots

def run_program(program_path, input_size, num_executions):
    specific_program_path = f"{program_path}{input_size}"
    times = []

    for _ in range(num_executions):
        start_time = time.time()
        result = subprocess.run([specific_program_path], capture_output=True, text=True)
        end_time = time.time()

        # Verificar se o programa foi executado com sucesso
        if result.returncode == 0:
            execution_time = end_time - start_time
            times.append(execution_time)

    return times

# Caminhos base para os executáveis
exaustiva_program_base_path = './exaustiva'
mpi_program_base_path = './mpi'

# Tamanhos de entrada correspondem aos sufixos dos nomes dos executáveis
input_sizes = [5, 10, 15, 20, 25]

# Número de execuções para cada tamanho de entrada
num_executions = 5

# Executar os programas e obter os tempos de execução
tempo_exaustiva = {size: run_program(exaustiva_program_base_path, size, num_executions) for size in input_sizes}
print(tempo_exaustiva)
tempo_mpi = {size: run_program(mpi_program_base_path, size, num_executions) for size in input_sizes}
print(tempo_mpi)
# Calcular médias dos tempos de execução
media_exaustiva = {size: sum(times) / len(times) if times else 0 for size, times in tempo_exaustiva.items()}
media_mpi = {size: sum(times) / len(times) if times else 0 for size, times in tempo_mpi.items()}

# Calcular speedups
speedup_mpi = {size: media_exaustiva[size] / media_mpi[size] for size in input_sizes}

# Criar figura com subplots
fig = make_subplots(rows=1, cols=1, specs=[[{'secondary_y': True}]])

# Adicionar gráfico de barras para tempos de execução
fig.add_trace(
    go.Bar(x=input_sizes, y=list(media_exaustiva.values()), name='MPI', marker=dict(color='blue')),
    secondary_y=False,
)

fig.add_trace(
    go.Bar(x=input_sizes, y=list(media_mpi.values()), name='Exaustiva', marker=dict(color='green')),
    secondary_y=False,
)

# Adicionar gráfico de linha para speedup
fig.add_trace(
    go.Scatter(x=input_sizes, y=list(speedup_mpi.values()), name='Speedup (MPI)', mode='lines+markers', line=dict(color='red', dash='dash')),
    secondary_y=True,
)

# Configurações do eixo x
fig.update_xaxes(title_text='Tamanho da Entrada')

# Configurações do eixo y primário
fig.update_yaxes(title_text='Tempo de Execução Médio (s)', secondary_y=False, range=[0, max(max(media_exaustiva.values()), max(media_mpi.values())) + 1])

# Configurações do eixo y secundário
fig.update_yaxes(title_text='Speedup', secondary_y=True, range=[0, max(speedup_mpi.values()) + 1])

# Atualizar layout da figura
fig.update_layout(title='Comparação de Tempo de Execução e Speedup', barmode='group')

# Mostrar figura
fig.show()
