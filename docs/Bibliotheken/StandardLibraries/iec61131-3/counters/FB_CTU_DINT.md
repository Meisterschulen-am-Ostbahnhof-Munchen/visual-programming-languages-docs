# FB_CTU_DINT

```{index} single: FB_CTU_DINT
```

<img width="1396" height="277" alt="" src="https://github.com/user-attachments/assets/36c696fb-4dfc-457a-bd17-1842876fa432" />

* * * * * * * * * *

## Einleitung
Der FB_CTU_DINT ist ein Aufwärtszähler (Counter Up) für den Datentyp DINT (32-Bit Ganzahl). Er zählt bei jedem Zählimpuls hoch und kann auf einen vordefinierten Wert zurückgesetzt werden. Der Baustein ist besonders geeignet für Anwendungen, die große Zählbereiche erfordern.

![FB_CTU_DINT](FB_CTU_DINT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsrequest (triggert den Zählvorgang)

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung (wird nach Abschluss des Zählvorgangs ausgelöst)

### **Daten-Eingänge**
- **CU** (BOOL): Zähl-Eingang (bei TRUE wird hochgezählt)
- **R** (BOOL): Reset-Eingang (bei TRUE wird der Zählerwert auf 0 gesetzt)
- **PV** (DINT): Preset-Wert (definiert den Vergleichswert für den Q-Ausgang)

### **Daten-Ausgänge**
- **Q** (BOOL): Statusausgang (wird TRUE, wenn CV ≥ PV)
- **CV** (DINT): Aktueller Zählerwert (Count Value)

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der FB_CTU_DINT arbeitet nach folgenden Regeln:
1. Bei aktivem Reset (R=TRUE) wird der Zählerwert (CV) auf 0 zurückgesetzt
2. Bei aktivem Zähleingang (CU=TRUE) und nicht aktivem Reset wird der Zählerwert um 1 erhöht (bis zum Maximalwert von 2147483647)
3. Der Ausgang Q wird auf TRUE gesetzt, sobald der Zählerwert (CV) den Preset-Wert (PV) erreicht oder überschreitet

## Technische Besonderheiten
- Verwendet 32-Bit Integer (DINT) für Zählwerte
- Maximaler Zählerwert: 2.147.483.647
- Implementiert als einfacher Funktionsblock (SimpleFB)
- Unterstützt den IEC 61131-3 Standard

## Zustandsübersicht
Der Baustein hat keinen internen Zustandsautomaten. Die Logik wird bei jedem REQ-Ereignis ausgeführt.

## Anwendungsszenarien
- Produktionszählung in Fertigungsanlagen
- Ereigniszählung in Prozesssteuerungen
- Überwachung von Zykluszeiten
- Allgemeine Zählaufgaben in der Automatisierungstechnik

## Vergleich mit ähnlichen Bausteinen
- Gegenüber FB_CTU_INT bietet FB_CTU_DINT einen größeren Zählbereich (32-Bit vs. 16-Bit)
- Im Vergleich zu FB_CTU_LINT hat FB_CTU_DINT einen kleineren Wertebereich, aber geringeren Speicherbedarf
- Ähnlich zu IEC 61131-3 CTU-Funktionsblöcken, aber in 4diac-IDE Implementierung

## Fazit
Der FB_CTU_DINT ist ein robuster und einfach zu verwendender Aufwärtszähler für Anwendungen mit mittleren bis großen Zählbereichen. Durch seine klare Schnittstelle und einfache Funktionsweise eignet er sich besonders für Standard-Zählaufgaben in der Automatisierungstechnik.