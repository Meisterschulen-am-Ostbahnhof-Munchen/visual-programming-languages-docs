# E_TABLE_CTRL

![E_TABLE_CTRL](https://user-images.githubusercontent.com/116869307/214142693-35103bc3-d636-442c-b299-b4d6becb832d.png)

* * * * * * * * * *

## Einleitung
Der **E_TABLE_CTRL** ist ein Unterstützungsbaustein für E_TABLE nach IEC 61499-1 (Annex A), unter EPL-2.0 Lizenz. Version 1.0 ermöglicht die präzise Steuerung von Ereignissequenzen basierend auf einer konfigurierbaren Zeit-Tabelle.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `INIT`: Initialisiert die Ereignistabelle (mit DT- und N-Parametern)
- `CLK`: Taktsignal für den Tabellenfortschritt

### **Ereignis-Ausgang**
- `CLKO`: Generiertes Taktereignis (mit DTO- und CV-Daten)

### **Daten-Eingänge**
- `DT` (TIME-Array): Zeitintervalle für die Ereignisgenerierung
- `N` (UINT): Anzahl der aktiven Zeitschritte

### **Daten-Ausgänge**
- `DTO` (TIME): Aktuelles Zeitintervall
- `CV` (UINT): Aktueller Ereignisindex (0..N-1)

## Funktionsweise

1. **Initialisierung**:
   - Bei `INIT`-Ereignis wird der Index (CV) auf 0 gesetzt
   - Erstes Zeitintervall (DTO) aus DT-Array übernommen

2. **Tabellensteuerung**:
   - Jedes `CLK`-Ereignis erhöht CV um 1
   - Nächstes Zeitintervall aus DT-Array wird geladen
   - `CLKO` wird bei jedem Schritt generiert

3. **Zustandsautomat** (ECC):
   - **START**: Wartezustand
   - **INIT**: Initialisierungsphase
   - **INIT1**: Erste Ereignisgenerierung
   - **NEXT_STEP**: Tabellenfortschritt

## Technische Besonderheiten

✔ **Tabellengesteuerte** Zeitplanung  
✔ **Array-basierte** Konfiguration (bis zu 4 Zeitschritte)  
✔ **Zustandsbasierte** Implementierung (BasicFB)  
✔ **Echtzeitfähige** Ereignisgenerierung  

## Anwendungsszenarien

- **Prozesssteuerung**: Komplexe Zeitabläufe
- **Testautomation**: Programmierbare Testsequenzen
- **Maschinensteuerung**: Bewegungsabläufe
- **Produktionslinien**: Taktgesteuerte Prozesse

## Vergleich mit E_TABLE

| Feature        | E_TABLE_CTRL | E_TABLE |
|---------------|--------------|---------|
| Steuerung     | Tabellenbasiert | Einfache Zeitsteuerung |
| Flexibilität  | Hoch (mehrere Intervalle) | Niedrig |
| Schnittstelle | Erweitert    | Grundlegend |

## Fazit

Der E_TABLE_CTRL-Baustein erweitert die Möglichkeiten der tabellengesteuerten Ereignisgenerierung:

- Flexible Konfiguration mehrerer Zeitintervalle
- Präzise Steuerung komplexer Abläufe
- Robuste Zustandsmaschinen-Implementierung

Durch seine Array-basierte Zeitsteuerung eignet er sich ideal für Anwendungen mit variablen Prozessschritten. Die Integration als BasicFB gewährleistet zuverlässige Operation in IEC 61499-basierten Steuerungssystemen.














































