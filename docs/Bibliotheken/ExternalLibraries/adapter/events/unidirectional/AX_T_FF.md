# AX_T_FF

```{index} single: AX_T_FF
```

<img width="1181" height="187" alt="image" src="https://github.com/user-attachments/assets/fe3f05c1-c201-42ef-a5d8-874b826680de" />

* * * * * * * * * *
## Einleitung
Der AX_T_FF (Toggle Flip-Flop) ist ein grundlegender Speicherbaustein in 4diac, der als Toggle-Flipflop fungiert. Bei jedem Taktereignis wechselt der Ausgabewert zwischen den beiden möglichen Zuständen. Der Baustein implementiert ein einfaches Schaltverhalten, bei dem der Ausgangswert bei jedem Taktimpuls umgeschaltet wird.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **CLK**: Takteingang, der eine Ausgangsumschaltung auslöst

### **Ereignis-Ausgänge**
- Keine direkten Ereignisausgänge vorhanden

### **Daten-Eingänge**
- Keine Dateneingänge vorhanden

### **Daten-Ausgänge**
- Keine direkten Datenausgänge vorhanden

### **Adapter**
- **Q**: Unidirektionaler Adapter vom Typ AX, der den aktuellen Flipflop-Wert bereitstellt

## Funktionsweise
Der AX_T_FF arbeitet als einfacher Toggle-Flipflop. Bei jedem eingehenden CLK-Ereignis wird der Algorithmus TOGGLE ausgeführt, der den aktuellen Wert des Adapters Q.D1 invertiert. Der Baustein beginnt im START-Zustand und wechselt bei jedem CLK-Ereignis in den SET-Zustand, wo die Umschaltung durchgeführt wird.

## Technische Besonderheiten
- Verwendet einen unidirektionalen Adapter für die Ausgabe
- Implementiert als Basic Function Block (BFB)
- Besitzt einen einfachen Zustandsautomaten mit zwei Zuständen
- Der Algorithmus TOGGLE führt eine logische Negation des Ausgabewerts durch

## Zustandsübersicht
Der Baustein verfügt über zwei Zustände:

1. **START**: Initialzustand, wartet auf CLK-Ereignis
2. **SET**: Aktiver Zustand, in dem der TOGGLE-Algorithmus ausgeführt wird

Zustandsübergänge:
- START → SET: Bei CLK-Ereignis
- SET → START: Immer (Condition "1" = wahr)

## Anwendungsszenarien
- Frequenzteilung von Taktsignalen
- Erzeugung von Rechtecksignalen mit halber Eingangsfrequenz
- Zähler- und Teiler-Schaltungen
- Zustandssteuerungen mit alternierendem Verhalten

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen Flipflop-Typen wie RS- oder D-Flipflops bietet der Toggle-Flipflop eine spezialisierte Funktionalität für reine Umschaltoperationen. Er ist einfacher aufgebaut als universellere Flipflop-Typen und benötigt keine zusätzlichen Dateneingänge.

Vergleich mit [E_T_FF](../../../../StandardLibraries/events/E_T_FF.md)

## Fazit
Der AX_T_FF ist ein spezialisierter und effizienter Baustein für Anwendungen, die ein reines Toggle-Verhalten benötigen. Seine einfache Struktur und klare Funktionsweise machen ihn zu einer zuverlässigen Komponente für Frequenzteilung und Zustandsalternierung in Steuerungssystemen.