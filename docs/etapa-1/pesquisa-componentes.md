
# Pesquisa de Componentes e Integração
> Projeto-alvo: osciloscópio portátil baseado em **FRDM-K64F** + **TFT touch (ILI9341)** + **bateria Li‑ion 1S (TP4056)**. Este documento lista componentes possíveis, como integrá‑los, cálculos iniciais de consumo e orçamento preliminar por componente.

---

## 1. Componente central: FRDM‑K64F (MCU / processamento)
- **Por que:** Cortex‑M4 com ADCs internos de alta velocidade (configuráveis), DMA, Ethernet/USB e amplo suporte SDK/mbed. Boa RAM/Flash para buffers e drivers gráficos.
- **Pontos a verificar:** taxa máxima ADC em modo differential / single ended (veja datasheet K64); número de canais ADC livres para seu mapeamento.
---

## 2. Tela + touch
- **Parte sugerida:** 2.8″ SPI ILI9341 + XPT2046 (resistive touch) — boa disponibilidade, bibliotecas e performance. Display controller consome ~10 mA; backlight LEDs tipicamente 50–100 mA dependendo brilho. Controlar backlight com PWM.
- **Integração:** SPI (MOSI, SCLK, CS, DC, RST) + CS touch (SPI or separate ADC). DMA para transferir bitmap para display.

---

## 3. Fonte de carga / bateria
- **Carregador:** TP4056 module (1A configurable via Rprog) + proteção DW01 / dual MOSFETs para proteção de bateria; simples e barato. Módulo com proteção.
- **Recomendação de bateria:** 1× 18650 (2000–3500 mAh) ou pack Li‑ion 3.7V. Para portabilidade, uma célula 18650 é prática. Circuito de power path (ideal diode) se quiser alimentar e carregar ao mesmo tempo com menos stress térmico.

---

## 4. ADC — opções e integração (crítico para desempenho)
### 4.1 Usar ADC interno do K64F
- **Prós:** menos custo; uso direto do MCU (PDB/timers/DMA).  
- **Contras:** taxa por canal e ruído podem limitar a banda prática; para >250–500 kS/s por canal verifique datasheet. O K64F suporta conversão rápida (sub‑μs por conversão dependendo resolução) mas usar differential/sampling em altas taxas precisa de configuração cuidadosa.

### 4.2 ADC externo SAR recomendado (quando precisar de 16‑bit / 500 kS/s)
- **Opções:** TI ADS8327 / ADS8331 / ADS8329 series (16‑bit, 500 kS/s, variantes 1ch/4ch, consumo baixo). Esses chips oferecem melhor S/N e interface SPI compatível com MCU. Preço unitário (DigiKey/Mouser) ~US$8–$20 dependendo do modelo e embalagem; módulos e EVMs também estão disponíveis.
- **Integração:** ADC externo em SPI (ou serial parallel) → usar DMA para coletar dados para RAM; gerar clock de conversão compatível; cuidar do layout e do RC anti‑aliasing simétrico se operar em differential/pseudo‑bipolar.

---

## 5. Front‑end analógico (componentes principais)
- **Op‑amp (buffer / preamp):** MCP6002 (dual, rail‑to‑rail, low power, 1 MHz GBW) é uma escolha usada em projetos DIY; corrente quiescente baixa (~100 µA por amp típica). Bom custo e disponibilidade.
- **Switch analogico / multiplexer:** 74HC4052 / CD74HC4052 (dual SP4T) para seleção de ganho/faixa. Verificar R_ON e capacitância para calcular tempos de settling.
- **Charge pump (opcional):** ICL7660S para gerar −2.5 V se optar por front‑end bipolar; eficiência e consumo devem ser considerados (impacta autonomia). Alternativamente, usar bias mid‑rail se eliminar rail negative.
- **Proteção:** diodos rápidos (1N4148/Schottky), TVS no conector, resistores série e fusível de entrada.

---

## 6. Integração prática — pontos de atenção elétricos e de firmware
1. **Anti‑aliasing RC simétrico / filtro diferencial**: projetar RC em cada linha antes do ADC (se diferencial) e garantir fc < Nyquist/2. Documente o cálculo do polo para cada faixa.
2. **Settling time**: após mudar faixa com 74HC4052, aguardar 5–10× RC (RON × Cnode) antes de amostrar. Pode exigir 10s–100s μs.
3. **Proteção de entrada**: TVS + diodos clamp + resistor série (100–5kΩ) para proteger ADC e MCU. Inclua fusível lento ou PTC no conector BNC.
4. **Power path**: para carregar e alimentar simultaneamente, considerar ideal‑diode circuit (MOSFET) ou power multiplexer, evitando que TP4056 dissipe todo o calor no LDO.
5. **Layout**: separar planos analógico/digital, star ground perto do conector BNC, decouplagem próxima a ICs (100 nF + 10 μF). Minimizar loops de retorno de sinal de alta frequência.
6. **Firmware design**: ADC via PDB/timer + DMA; buffer circular; trigger por software/hardware; display render com DMA e rolagem parcial. Low‑power modes para reduzir consumo quando o instrumento está inativo.

---

## 7. Próximos passos recomendados (implementação)
1. **Escolher estratégia de ADC**: K64F interno (prototipagem rápida) vs ADC externo (ADS8327/ADS8331) para target de 500 kS/s e 16 bits efetivos.
2. **Decidir rail negative**: optar por Vmid‑bias (recomendado) ou manter ICL7660 (quando necessário para medir sinais centrais).
3. **Desenhar schematic de alimentação** com TP4056 + proteção + LDO 3.3 V + (opcional) boost converter.
4. **Prototipar front‑end** em placa de ensaio (ou small PCB), medir ruído, ganho, offset e tempo de settling. Comparar ADC interno vs ADC externo.
5. **Criar firmware mínimo**: ADC sampling via DMA + basic UI + backlight control; medir consumo real.

---

## Referências / Datasheets citadas
- [Datasheet FRDM-K64F / Kinetis K64](https://www.nxp.com/design/development-boards/freedom-development-boards/mcu-boards/freedom-development-platform-for-kinetis-k64-k63-and-k24-mcus:FRDM-K64F)  
- [Datasheet TP4056](https://www.electronics-lab.com/wp-content/uploads/2016/07/tp4056.pdf)  
- [Datasheet ILI9341](https://cdn-shop.adafruit.com/datasheets/ILI9341.pdf)  
- [Datasheet MCP6002](https://www.microchip.com/en-us/product/MCP6002)  
- [Datasheet CD74HC4052](https://www.ti.com/lit/ds/symlink/cd74hc4052.pdf)  
- [Datasheet ADS8327](https://www.ti.com/lit/ds/symlink/ads8327.pdf) / [ADS8331](https://www.ti.com/lit/ds/symlink/ads8331.pdf)  




