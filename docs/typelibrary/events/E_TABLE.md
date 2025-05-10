# E_TABLE

![E_TABLE Funktionsbaustein](https://user-images.githubusercontent.com/113907528/204904862-ebdcc4da-7a49-4931-b534-673c9449cf5e.png)

* * * * * * * * * *

## Einleitung
Der **E_TABLE** ist ein zusammengesetzter Funktionsbaustein nach IEC 61499, der zeitgesteuerte Ereignisse gemäß einer konfigurierbaren Tabelle generiert. Dieser Baustein ermöglicht komplexe Ablaufsteuerungen in industriellen Automatisierungssystemen.

## Struktur des E_TABLE-Bausteins

### **Ereignis-Eingänge**
- `START`: Startet die Ereignisgenerierung
- `STOP`: Bricht die aktive Generierung ab

### **Daten-Eingänge**
- `DT`: Zeitintervall zwischen den Ereignissen (TIME)
- `N`: Anzahl der zu generierenden Ereignisse (INT)

### **Ereignis-Ausgänge**
- `EO`: Generiertes Ausgangsereignis

### **Daten-Ausgänge**
- `CV`: Aktueller Zählerstand (INT)

## Funktionsweise

1. **Initialisierung**:
   - Bei `START`-Ereignis beginnt die Generierung der Ereignisse
   - Die Ereignisse werden im definierten `DT`-Intervall ausgegeben

2. **Laufzeitverhalten**:
   - Jedes generierte Ereignis erhöht `CV` um 1
   - Die Generierung stoppt automatisch nach `N` Ereignissen

3. **Abbruchmöglichkeit**:
   - Ein `STOP`-Ereignis unterbricht die aktive Generierung
   - `CV` behält dabei seinen aktuellen Wert

## Technische Besonderheiten

✔ **Tabellengesteuerte Ereignisgenerierung**  
✔ **Flexible Konfiguration** von Intervall und Anzahl  
✔ **Echtzeitfähige** Ausführung  
✔ **Einfache Integration** in IEC 61499-Systeme  

## Anwendungsszenarien

- **Ablaufsteuerungen**: Zeitgesteuerte Prozessschritte
- **Testautomation**: Generierung von Prüfmustern
- **Batch-Prozesse**: Steuerung von Chargenabläufen
- **Messsysteme**: Periodische Datenerfassung

## Vergleich mit ähnlichen Bausteinen

| Feature        | E_TABLE | E_CYCLE | E_DELAY |
|---------------|---------|---------|---------|
| Ereignisart   | Tabellengesteuert | Zyklisch | Einmalverzögerung |
| Konfiguration | DT + N  | DT      | DT      |
| Ausgänge      | EO + CV | EO      | EO      |

## Fazit

Der E_TABLE-Baustein ist ein leistungsstarkes Werkzeug für zeitkritische Steuerungsaufgaben in der Automatisierungstechnik. Seine Hauptvorteile sind:

- Präzise Generierung von Ereignisfolgen
- Flexible Parametrierung von Timing und Anzahl
- Zuverlässige Integration in verteilte Systeme

Durch seine tabellengesteuerte Arbeitsweise eignet er sich ideal für komplexe Ablaufsteuerungen und wiederkehrende Prozesse. Die Kombination aus einfacher Bedienbarkeit und präziser Zeitsteuerung macht ihn zu einer wertvollen Komponente in modernen Steuerungssystemen nach IEC 61499.