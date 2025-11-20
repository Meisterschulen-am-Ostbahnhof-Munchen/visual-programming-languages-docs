# E_N_TABLE

![E_N_TABLE Funktionsbaustein](https://user-images.githubusercontent.com/113907528/204900000-9780540c-1565-4ef7-8669-5ff19940274e.png)

* * * * * * * * * *

## Einleitung
Der **E_N_TABLE** ist ein spezialisierter Funktionsbaustein nach IEC 61499 zur Erzeugung einer begrenzten Folge von Einzelereignissen. Im Gegensatz zu regelmäßigen Zeitgebern ermöglicht dieser Baustein die Generierung individuell getakteter Ereignisse.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `START`: Initiiert die Ereignisfolge
- `STOP`: Unterbricht die aktive Generierung

### **Daten-Eingänge**
- `DT`: Zeitparameter für die Ereignisabstände
- `N`: Maximale Anzahl der zu generierenden Ereignisse

### **Ereignis-Ausgänge**
- `EO`: Ausgang für die generierten Ereignisse

### **Daten-Ausgänge**
- `CV`: Aktueller Zählerstand der Ereignisse

## Funktionsprinzip

1. **Initialisierungsphase**:
   - Bei `START` beginnt die Generierung der Ereignisfolge
   - Der erste `EO`-Puls wird sofort ausgegeben

2. **Laufzeitverhalten**:
   - Jedes Ereignis wird nach dem konfigurierten `DT`-Intervall generiert
   - Der `CV`-Wert dokumentiert die Anzahl bereits ausgegebener Ereignisse

3. **Abschlusskriterien**:
   - Automatischer Stopp nach Erreichen von `N` Ereignissen
   - Sofortiger Abbruch bei `STOP`-Ereignis

## Technische Merkmale

✔ **Deterministische Ereignisgenerierung**  
✔ **Flexible Konfiguration** der Ereignisanzahl  
✔ **Präzise Zeitsteuerung** im Millisekundenbereich  
✔ **Echtzeitfähige** Architektur  

## Typische Anwendungen

- **Maschinensteuerung**: Getaktete Bewegungsabläufe
- **Produktionslinien**: Steuerung von Taktprozessen
- **Testsysteme**: Generierung von Prüfimpulsen
- **Prozessautomation**: Zeitgesteuerte Ventilsteuerungen

## Vergleich mit ähnlichen Bausteinen

| Merkmal       | E_N_TABLE | E_CYCLE | E_TABLE |
|--------------|-----------|---------|---------|
| Ereignistyp  | Begrenzte Folge | Dauerzyklus | Tabellengesteuert |
| Steuerung    | DT + N    | DT      | Komplexe Tabelle |
| Flexibilität | Mittel    | Niedrig | Hoch    |

## Fazit

Der E_N_TABLE-Baustein bietet eine optimale Lösung für Anwendungen, die eine genau definierte Anzahl von Steuerimpulsen erfordern. Seine besonderen Stärken liegen in:

- Zuverlässiger Generierung begrenzter Ereignisfolgen
- Präziser Einhaltung der Zeitintervalle
- Einfacher Parametrierbarkeit

Durch seinen spezialisierten Funktionsumfang ergänzt er ideal die Familie der Zeitgeber-Bausteine in IEC 61499-Systemen und eignet sich besonders für Taktsteuerungen in industriellen Automatisierungslösungen.