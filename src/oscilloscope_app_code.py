import serial
import matplotlib.pyplot as plt
import numpy as np

PORTA = "COM10"
BAUD = 1000000

# Configuração do ADC
VREF = 3.3
FS = 20000

# --- TEMA DARK ---
plt.style.use("dark_background")

# abre porta
ser = serial.Serial(PORTA, BAUD, timeout=1)

# prepara gráfico
plt.ion()
fig, ax = plt.subplots()

fig.patch.set_facecolor("black")
ax.set_facecolor("black")

linha_plot, = ax.plot([], [], color="#00ff00", linewidth=1.2)  # verde osciloscópio

ax.set_ylim(0, 1023)
ax.set_xlim(0, 500)

# grade em cinza escuro
ax.grid(color="#222222")

# texto de informações
info_text = ax.text(
    0.02, 0.98, "",
    transform=ax.transAxes,
    fontsize=12, color="yellow",
    verticalalignment="top",
    bbox=dict(facecolor='black', alpha=0.6)
)

print("Plotando em tempo real...")

while True:
    try:
        raw = ser.readline().decode(errors="ignore").strip()
        if not raw:
            continue

        partes = raw.split(",")[1:]
        dados = [int(x) for x in partes if x.isdigit()]
        if len(dados) == 0:
            continue

        arr = np.array(dados)

        # =============================
        # Cálculos ADC
        # =============================
        Vpp_counts = arr.max() - arr.min()
        Vmed_counts = arr.mean()
        Vrms_counts = np.sqrt(np.mean(arr**2))

        # Converter para volts
        Vpp = Vpp_counts * (VREF / 1023)
        Vmed = Vmed_counts * (VREF / 1023)
        Vrms = Vrms_counts * (VREF / 1023)

        # Frequência
        freq = 0
        cruz = np.where(np.diff(arr > Vmed_counts))[0]
        if len(cruz) > 1:
            periodo = np.mean(np.diff(cruz)) / FS
            freq = 1 / periodo

        # Atualiza texto na tela
        info_text.set_text(
            f"Vpp:  {Vpp:.3f} V\n"
            f"Vrms: {Vrms:.3f} V\n"
            f"Vmed: {Vmed:.3f} V\n"
            f"Freq: {freq:.1f} Hz"
        )

        # Atualiza o gráfico
        linha_plot.set_ydata(arr)
        linha_plot.set_xdata(np.arange(len(arr)))
        ax.set_xlim(0, len(arr))

        plt.pause(0.001)

    except KeyboardInterrupt:
        print("Encerrado.")
        break
    except Exception as e:
        print("Erro:", e)
