# AUI_UDINT_LT

![AUI_UDINT_LT](./AUI_UDINT_LT.svg)

* * * * * * * * * *
## Introduction

The function block **AUI_UDINT_LT** performs a less-than comparison between two values. The first value is provided as an input via an **AUI adapter**, the second value via a scalar **UDINT** data input. The result of the comparison (Boolean value) is output via an **AX adapter**. The function block is triggered by a **REQ** event.
## Interface Structure

### **Event Inputs**

| Event | Description |
|----------|--------------|
| REQ | Service Request – starts the comparison. The data value **IN2** is read along with this event. |

### **Event Outputs**

The function block does not have direct event outputs. The result is signaled via the **OUT adapter** (event **E1**).

### **Data Inputs**

| Name | Type | Description |
|------|-----|--------------|
| IN2 | UDINT | Second comparison value (unsigned double integer, 32 bits). |

### **Data Outputs**

No direct data outputs. The result is provided via the **OUT adapter** (data value **D1**).

### **Adapters**

| Role | Type | Description |
|-------|-----|---------------|
| IN1 | adapter::types::unidirectional::AUI | First comparison value (value 1). The **E1** event initiates the transfer of the data value **D1** to the internal logic. |
| OUT | adapter::types::unidirectional::AX | Output of the comparison result: **D1** returns `true` if value 1 (< Wert 2, andernfalls `false`. Das Ereignis **E1** signalisiert die Gültigkeit des Ergebnisses. |

## Funktionsweise

1. Der Baustein wartet auf ein Ereignis **REQ** (oder auf ein eingehendes Ereignis des **IN1**-Adapters).
2. Mit dem Ereignis werden die beiden Werte erfasst:
- **IN1.D1** (vom Adapter) als erster Wert
- **IN2** (Dateneingang) als zweiter Wert
3. Ein interner Funktionsbaustein **F_LT** (Typ `iec61131::comparison::F_LT`) führt den Kleiner-als-Vergleich durch.
4. Das boolesche Ergebnis wird über **OUT.D1** ausgegeben und auf dem **OUT**-Adapter das Ereignis **E1** ausgelöst.

## Technische Besonderheiten

- Der Baustein verwendet **Adapter** für die flexible Anbindung von Werten über standardisierte Schnittstellen (AUI für Eingang, AX für Ausgang).
- Der Vergleich basiert auf dem IEC 61131-3 Standardvergleich für **UDINT** (vorzeichenlose 32‑Bit‑Ganzzahl).
- Die eigentliche Vergleichslogik ist in den internen Baustein **F_LT** ausgelagert, sodass eine klare Trennung zwischen Adapteranbindung und Funktionslogik besteht.
- Die Kommunikation mit der Umgebung erfolgt ereignisgesteuert – sowohl der Aufruf als auch die Ergebnisrückmeldung werden über Ereignisse synchronisiert.

## Zustandsübersicht

Der Baustein besitzt keine explizite Zustandsmaschine (ECC). Er verhält sich wie ein **reiner Funktionsbaustein** ohne interne Zustände:

- Nach jedem **REQ**-Ereignis wird der Vergleich unverzögert durchgeführt und das Ergebnis am **OUT**-Adapter bereitgestellt.
- Es gibt keine Wartezustände oder zeitlichen Verzögerungen.

## Anwendungsszenarien

- **Grenzwertüberwachung**: Prüfen, ob ein von einem Sensor stammender Wert (über AUI) unter einem festgelegten Schwellenwert (UDINT) liegt.
- **Steuerungslogik**: Auslösen einer Aktion, wenn eine gemessene Größe einen bestimmten Wert unterschreitet.
- **Sicherheitsfunktionen**: Abschalten einer Anlage, wenn der Prozesswert unter einen Minimalwert fällt.

## Vergleich mit ähnlichen Bausteinen

- **AUI_UDINT_GT**: Führt einen Größer-als-Vergleich durch (Wert 1 > if value 2).
- **AUI_UDINT_EQ**: Checks for equality (value 1 = value 2).
- **AUI_UDINT_LE** / **AUI_UDINT_GE**: Perform less-than-or-equal-to and greater-than-or-equal-to comparisons, respectively.
- All these function blocks share the same structure with AUI/AX adapters and differ only in their internal comparison function.

## Conclusion

**AUI_UDINT_LT** is a compact, event-driven comparison function block for UDINT values. Its use of standardized adapters (AUI, AX) allows for flexible integration into industrial control systems. The clear separation of adapter logic and comparison simplifies maintenance and reuse. This module is particularly suitable for simple limit value checks and condition evaluations in automation technology.
