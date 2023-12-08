import matplotlib.pyplot as plt
import plotly.graph_objs as go
from plotly.subplots import make_subplots

# Tempos fornecidos
tempos_serial = [0.00183143, 0.024659, 0.0167494, 52.9513, 33.8068]
tempos_mpi = [2.5065e-5, 2.7099e-5, 2.3233e-5, 3.9117e-5, 3.846e-5]

# Tamanhos de entrada
input_sizes = [5, 10, 15, 20, 25]

# Calcular speedups
speedup_mpi = [tempos_serial[i] / tempos_mpi[i] for i in range(len(tempos_serial))]

# Criar figura com subplots
fig = make_subplots(rows=1, cols=1, specs=[[{'secondary_y': True}]])

# Adicionar gráfico de barras para tempos de execução
fig.add_trace(
    go.Bar(x=input_sizes, y=tempos_mpi, name='MPI', marker=dict(color='blue')),
    secondary_y=False,
)

fig.add_trace(
    go.Bar(x=input_sizes, y=tempos_serial, name='Serial', marker=dict(color='green')),
    secondary_y=False,
)

# Adicionar gráfico de linha para speedup
fig.add_trace(
    go.Scatter(x=input_sizes, y=speedup_mpi, name='Speedup (MPI)', mode='lines+markers', line=dict(color='red', dash='dash')),
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
