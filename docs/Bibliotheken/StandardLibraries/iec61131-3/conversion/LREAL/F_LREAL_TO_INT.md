# F_LREAL_TO_INT

```{index} single: F_LREAL_TO_INT
```

<img width="1436" height="210" alt="F_LREAL_TO_INT" src="https://github.com/user-attachments/assets/4ae1ab8e-2e6b-42e5-835c-dd7f427c8a55" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_LREAL_TO_INT` dient zur Konvertierung eines LREAL-Wertes (64-Bit Fließkommazahl) in einen INT-Wert (16-Bit Ganzzahl). Diese Konvertierung erfolgt durch Abrundung des LREAL-Wertes auf den nächstkleineren ganzzahligen Wert.

![F_LREAL_TO_INT](F_LREAL_TO_INT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Startet die Konvertierung des Eingabewertes. Der Eingabewert wird mit diesem Ereignis übergeben.

### **Ereignis-Ausgänge**
- `CNF`: Signalisiert den Abschluss der Konvertierung und gibt den konvertierten Wert aus.

### **Daten-Eingänge**
- `IN` (LREAL): Der Eingabewert, der in einen INT-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- `OUT` (INT): Der konvertierte Ganzzahlwert.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Bei Empfang des `REQ`-Ereignisses wird der Algorithmus ausgeführt, der den `IN`-Wert von LREAL zu INT konvertiert. Die Konvertierung erfolgt durch die Funktion `LREAL_TO_INT`, die den LREAL-Wert auf den nächstkleineren ganzzahligen Wert abrundet. Das Ergebnis wird an `OUT` ausgegeben und das `CNF`-Ereignis wird ausgelöst.

## Technische Besonderheiten
- Die Konvertierung schneidet Nachkommastellen ab (keine Rundung, sondern Abrundung).
- Bei Werten außerhalb des INT-Bereichs kann es zu Überlaufproblemen kommen.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- Konvertierung von Sensorwerten (z.B. Temperaturmessungen) für die Verarbeitung in Ganzzahl-basierten Systemen.
- Vorbereitung von Fließkommawerten für die Ausgabe auf Ganzzahl-Displays oder -Schnittstellen.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- `F_REAL_TO_INT`: Konvertiert REAL (32-Bit Fließkommazahl) zu INT.
- `F_LREAL_TO_DINT`: Konvertiert LREAL zu DINT (32-Bit Ganzzahl) für einen größeren Wertebereich.

## Fazit
Der `F_LREAL_TO_INT`-Funktionsblock ist ein einfaches, aber effektives Werkzeug zur Konvertierung von Fließkommazahlen in Ganzzahlen. Er eignet sich besonders für Anwendungen, bei denen eine schnelle und direkte Konvertierung ohne zusätzliche Logik erforderlich ist. Bei Werten, die den INT-Bereich überschreiten, sollten jedoch alternative Bausteine wie `F_LREAL_TO_DINT` in Betracht gezogen werden.