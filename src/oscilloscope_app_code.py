import serial
import matplotlib.pyplot as plt
import numpy as np

# =====================================================
# CONFIGURAÇÕES
# =====================================================
PORTA = "COM10"
BAUD = 1_000_000

ADC_MAX = 1023
VREF = 3.3

OFFSET_FISICO = 385        # offset DC do front-end (igual MCC)
GANHO_TOTAL = 1.0          # ajuste se houver amplificação

FS = 350_000               # Hz (mesma taxa do firmware)

# =====================================================
# TEMA OSCILOSCÓPIO
# =====================================================
plt.style.use("dark_background")

# =====================================================
# SERIAL
# =====================================================
ser = serial.Serial(PORTA, BAUD, timeout=1)

# =====================================================
# FIGURA
# =====================================================
plt.ion()
fig, ax = plt.subplots(figsize=(10, 5))

fig.patch.set_facecolor("black")
ax.set_facecolor("black")

linha_plot, = ax.plot([], [], color="#00ff00", linewidth=1.2)

ax.set_ylim(-512, 512)     # agora centrado em zero (pós-offset)
ax.set_xlim(0, 500)

ax.grid(color="#222222")

# =====================================================
# TEXTO NA TELA (HUD)
# =====================================================
info_text = ax.text(
    0.02, 0.98, "",
    transform=ax.transAxes,
    fontsize=12,
    color="yellow",
    verticalalignment="top",
    bbox=dict(facecolor="black", alpha=0.6)
)

print("Osciloscópio em execução...")

# =====================================================
# LOOP PRINCIPAL
# =====================================================
while True:
    try:
        raw = ser.readline().decode(errors="ignore").strip()
        if not raw:
            continue

        partes = raw.split(",")[1:]
        dados = [int(x) for x in partes if x.isdigit()]
        if len(dados) < 10:
            continue

        arr = np.array(dados)

        # =================================================
        # REMOVE OFFSET FÍSICO
        # =================================================
        arr_corr = arr - OFFSET_FISICO

        # =================================================
        # ESTATÍSTICAS (ADC)
        # =================================================
        min_val = np.min(arr_corr)
        max_val = np.max(arr_corr)

        vpp_adc = max_val - min_val
        vmed_adc = np.mean(arr_corr)
        vrms_adc = np.sqrt(np.mean(arr_corr ** 2))

        # =================================================
        # CONVERSÃO PARA VOLTS
        # ======================================
