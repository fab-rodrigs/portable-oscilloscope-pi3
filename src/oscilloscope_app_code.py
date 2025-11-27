import serial
import matplotlib.pyplot as plt
import numpy as np

PORTA = "COM10"
BAUD = 1000000

# abre porta
ser = serial.Serial(PORTA, BAUD, timeout=1)

# prepara gráfico
plt.ion()
fig, ax = plt.subplots()
linha_plot, = ax.plot([], [])
ax.set_ylim(0, 1023)      # resolução do ADC
ax.set_xlim(0, 500)       # assume ~500 pontos por frame (ajuste depois)

print("Plotando em tempo real...")

while True:
    try:
        raw = ser.readline().decode(errors="ignore").strip()

        if not raw:
            continue

        # remove a primeira vírgula e divide
        # exemplo: ",67,72,44"  -> ["67","72","44"]
        partes = raw.split(",")[1:]

        # converte para int
        dados = [int(x) for x in partes if x.isdigit()]

        if len(dados) == 0:
            continue

        # atualiza gráfico
        linha_plot.set_ydata(dados)
        linha_plot.set_xdata(np.arange(len(dados)))

        ax.set_xlim(0, len(dados))

        plt.pause(0.001)

    except KeyboardInterrupt:
        print("Encerrado.")
        break
    except Exception as e:
        print("Erro:", e)
