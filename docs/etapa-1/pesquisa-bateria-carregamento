# Pesquisa sobre Bateria e Carregamento

## 🔋 Escolha da Bateria
- **Modelo selecionado**: Célula 18650 Li-ion.  
- **Tensão nominal**: 3,6 V a 3,7 V.  
- **Faixa de operação**: 3,0 V (descarga mínima) até 4,2 V (carga máxima).  
- **Capacidade típica**: 2000 a 3000 mAh (dependendo do modelo).  
- **Justificativa**:  
  - Boa densidade energética.  
  - Fácil integração em projetos portáteis.  
  - Disponibilidade e baixo custo.  
  - Compatibilidade com circuitos de carregamento USB.  

---

## 🔌 Carregamento
- O carregamento é feito via **módulo USB (TP4056)**, que controla corrente e tensão de carga.  
- **Corrente de carga configurável** (tipicamente 1A).  
- Proteção contra sobrecarga e descarga profunda (dependendo da versão com proteção).  

Fluxo do carregamento:  
1. Entrada USB 5 V.  
2. Módulo TP4056 regula para a faixa adequada da célula Li-ion (4,2 V máx).  
3. Bateria 18650 é carregada de forma controlada (CC/CV – corrente constante / tensão constante).  

---

## ⚡ Conversão de Tensão
Após a bateria, o sistema precisa de diferentes níveis de tensão para alimentar os circuitos:

- **Conversor Boost**  
  - Eleva a tensão da bateria (3,6–4,2 V) para **7,5 V**.  
  - Necessário pois o regulador linear precisa de margem para estabilizar em 5 V.  

- **Regulador Linear**  
  - Converte os 7,5 V do conversor boost em **5 V estáveis**.  
  - Fornece alimentação principal dos circuitos digitais.  

- **Charge Pump (IC 7660S)**  
  - Gera tensão **-5 V** a partir de +5 V.  
  - Necessária para alimentar circuitos analógicos que requerem alimentação simétrica (por exemplo, amplificadores operacionais).  

---

## 🔄 Diagrama Simplificado
```text
Carregador USB → TP4056 → Bateria 18650 (3,6–4,2 V)
Bateria → Conversor Boost (7,5 V) → Regulador Linear (5 V)
5 V → Alimentação dos circuitos digitais
5 V → Charge Pump (7660S) → -5 V (alimentação analógica)
