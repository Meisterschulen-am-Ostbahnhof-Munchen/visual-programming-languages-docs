# FB_CTUD

<img width="1337" height="340" alt="FB_CTUD" src="https://github.com/user-attachments/assets/c27b281b-91cd-4e44-8224-7fc42017d1a2" />

* * * * * * * * * *
## Einleitung
Der FB_CTUD (Up Down Counter) ist ein Funktionsblock, der als Zähler mit Aufwärts- und Abwärtszählfunktion dient. Er ermöglicht das Zählen von Ereignissen in beide Richtungen und bietet zusätzliche Funktionen wie Reset und Laden eines vordefinierten Wertes.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung. Dieser Ereigniseingang löst die Ausführung des Zählvorgangs aus und ist mit den Daten-Eingängen CU, CD, R, LD und PV verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung. Dieses Ereignis wird nach Abschluss des Zählvorgangs ausgegeben und ist mit den Daten-Ausgängen QU, QD und CV verknüpft.

### **Daten-Eingänge**
- **CU** (BOOL): Zählt nach oben (Count Up).
- **CD** (BOOL): Zählt nach unten (Count Down).
- **R** (BOOL): Setzt den Zählerwert auf 0 zurück (Reset).
- **LD** (BOOL): Lädt den vordefinierten Wert PV in den Zähler (Load).
- **PV** (INT): Vordefinierter Wert, der bei aktiviertem LD in den Zähler geladen wird (Preset Value).

### **Daten-Ausgänge**
- **QU** (BOOL): Signalisiert, ob der Zählerwert größer oder gleich dem vordefinierten Wert PV ist (Output Up).
- **QD** (BOOL): Signalisiert, ob der Zählerwert kleiner oder gleich 0 ist (Output Down).
- **CV** (INT): Aktueller Zählerwert (Count Value).

### **Adapter**
Der FB_CTUD verfügt über keine Adapter.

## Funktionsweise
Der Funktionsblock FB_CTUD führt folgende Operationen aus:
1. **Reset (R)**: Wenn R aktiviert ist, wird der Zählerwert (CV) auf 0 gesetzt.
2. **Laden (LD)**: Wenn LD aktiviert ist, wird der vordefinierte Wert (PV) in den Zähler (CV) geladen.
3. **Zählen (CU/CD)**:
   - Wenn CU aktiviert ist und der Zählerwert (CV) kleiner als 32767 ist, wird CV um 1 erhöht.
   - Wenn CD aktiviert ist und der Zählerwert (CV) größer als -32768 ist, wird CV um 1 verringert.
   - CU und CD dürfen nicht gleichzeitig aktiviert sein.
4. **Ausgänge (QU/QD)**:
   - QU wird aktiviert, wenn CV größer oder gleich PV ist.
   - QD wird aktiviert, wenn CV kleiner oder gleich 0 ist.

## Technische Besonderheiten
- Der Zählerwert (CV) ist vom Typ INT und hat einen Wertebereich von -32768 bis 32767.
- Der FB_CTUD ist ein einfacher Funktionsblock (SimpleFB) und verwendet einen ST-Algorithmus (Structured Text) zur Implementierung der Logik.

## Zustandsübersicht
Der FB_CTUD hat keine expliziten Zustände, aber der Zählerwert (CV) kann als Zustand betrachtet werden, der durch die Eingänge CU, CD, R und LD verändert wird.

## Anwendungsszenarien
- **Produktionslinien**: Zählen von produzierten Einheiten (Aufwärtszählen) oder verbleibenden Einheiten (Abwärtszählen).
- **Lagerverwaltung**: Überwachung des Lagerbestands.
- **Steuerungstechnik**: Zeitgesteuerte Prozesse oder Ereigniszählung.

## Vergleich mit ähnlichen Bausteinen
- **FB_CTU**: Einfacher Aufwärtszähler ohne Abwärtszählfunktion.
- **FB_CTD**: Einfacher Abwärtszähler ohne Aufwärtszählfunktion.
- **FB_CTUD**: Kombiniert beide Funktionen in einem Baustein und bietet zusätzlich Reset- und Lade-Funktionen.

## Fazit
Der FB_CTUD ist ein vielseitiger Funktionsblock, der sowohl Aufwärts- als auch Abwärtszählfunktionen in einem Baustein vereint. Durch die zusätzlichen Funktionen wie Reset und Laden eines vordefinierten Wertes eignet er sich für eine Vielzahl von Anwendungen in der Steuerungstechnik. Seine einfache Handhabung und klare Schnittstellenstruktur machen ihn zu einer praktischen Lösung für Zählaufgaben.
