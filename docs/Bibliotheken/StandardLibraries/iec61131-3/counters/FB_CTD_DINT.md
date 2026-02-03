# FB_CTD_DINT

```{index} single: FB_CTD_DINT
```

<img width="1399" height="282" alt="FB_CTD_DINT" src="https://github.com/user-attachments/assets/a2d2a64a-c6b7-4d0e-9d5d-c1ab0452c96f" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `FB_CTD_DINT` ist ein Abwärtszähler (Down Counter) für 32-Bit Ganzzahlen (DINT). Er wird verwendet, um einen Wert schrittweise zu verringern und bei Erreichen eines bestimmten Schwellwerts ein Signal auszugeben.

![FB_CTD_DINT](FB_CTD_DINT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Normaler Ausführungsanforderung (Trigger für den Zählvorgang)

### **Ereignis-Ausgänge**
- `CNF`: Ausführungsbestätigung (wird nach Abschluss des Zählvorgangs ausgelöst)

### **Daten-Eingänge**
- `CD` (BOOL): Zählbefehl nach unten (Count Down)
- `LD` (BOOL): Ladebefehl (Load)
- `PV` (DINT): Voreingestellter Wert (Preset Value)

### **Daten-Ausgänge**
- `Q` (BOOL): Ausgangssignal (wird TRUE, wenn CV ≤ 0)
- `CV` (DINT): Aktueller Zählwert (Count Value)

## Funktionsweise
1. Bei Aktivierung des `REQ`-Ereignisses wird der Algorithmus ausgeführt:
   - Wenn `LD` TRUE ist, wird der Zähler auf den Wert von `PV` gesetzt
   - Wenn `CD` TRUE ist und der aktuelle Wert (`CV`) größer als -2147483648 ist, wird `CV` um 1 verringert
2. Das Ausgangssignal `Q` wird auf TRUE gesetzt, wenn `CV` kleiner oder gleich 0 ist
3. Nach Abschluss wird das `CNF`-Ereignis ausgelöst

## Technische Besonderheiten
- Verwendet 32-Bit Ganzzahlen (DINT) mit einem Wertebereich von -2147483648 bis 2147483647
- Der Zähler stoppt bei Erreichen des minimalen DINT-Werts (-2147483648)
- Der Block ist in der IEC 61131-3 Standardbibliothek unter `iec61131::counters` enthalten

## Zustandsübersicht
Der Funktionsblock hat keine expliziten Zustände, sondern arbeitet ereignisgesteuert:
1. Wartet auf `REQ`-Ereignis
2. Führt Zähloperation durch
3. Sendet `CNF`-Ereignis

## Anwendungsszenarien
- Abwärtszählung in Produktionsprozessen
- Zeitsteuerungen mit Countdown-Funktion
- Überwachung von Restmengen oder verbleibenden Schritten

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu Aufwärtszählern (CTU) verringert dieser Block den Zählerwert
- Im Vergleich zu 16-Bit Zählern (INT) bietet dieser Block einen größeren Wertebereich
- Ähnlich wie Timer, aber für allgemeine Zählzwecke ohne Zeitbezug

## Fazit
Der `FB_CTD_DINT` ist ein robuster und einfach zu verwendender Abwärtszähler für 32-Bit Werte. Seine klare Schnittstelle und deterministische Funktionsweise machen ihn ideal für Steuerungsaufgaben, bei denen eine zuverlässige Abwärtszählung benötigt wird.