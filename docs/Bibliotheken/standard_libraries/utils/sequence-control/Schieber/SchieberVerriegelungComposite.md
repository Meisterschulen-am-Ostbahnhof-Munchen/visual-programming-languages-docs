# SchieberVerriegelungComposite

<img width="1403" height="323" alt="SchieberVerriegelungComposite" src="https://github.com/user-attachments/assets/34a032b1-1459-439a-8625-6e2a138d8673" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `SchieberVerriegelungComposite` ist ein Composite-FB, der andere Funktionsblökte kapselt und zur Steuerung von Schieberverriegelungen dient. Er ermöglicht die zentrale Verwaltung von Verriegelungszuständen für Haupt- und Seitenschieber.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `INIT`: Initialisierungsanforderung (mit `QI` verbunden)
- `EI1`: Allgemeines Eingangsereignis (mit `DI_LINKS_GESPERRT` und `DI_RECHTS_GESPERRT` verbunden)

### **Ereignis-Ausgänge**
- `INITO`: Initialisierungsbestätigung (mit `QO` verbunden)

### **Daten-Eingänge**
- `QI`: Eingangsereignis-Qualifizierer (BOOL)
- `DI_LINKS_GESPERRT`: Status linker Schieber (BOOL)
- `DI_RECHTS_GESPERRT`: Status rechter Schieber (BOOL)

### **Daten-Ausgänge**
- `QO`: Ausgangsereignis-Qualifizierer (BOOL)

### **Adapter**
- `Hauptschieber`: Adapter für Hauptschieber (Typ ASR2)
- `SchieberLinks`: Adapter für linken Schieber (Typ ASR2)
- `SchieberRechts`: Adapter für rechten Schieber (Typ ASR2)

## Funktionsweise
Der Composite-FB dient als Wrapper für den `SchieberVerriegelung`-Funktionsblock und verbindet dessen Schnittstellen mit den externen Adaptern. Er leitet:
- Initialisierungsereignisse weiter
- Schieberstatusinformationen (gesperrt/entsperrt)
- Steuerbefehle an die entsprechenden Schieberadapter

Die Hauptfunktionalität liegt im gekapselten `SchieberVerriegelung`-FB, der die eigentliche Verriegelungslogik implementiert.

## Technische Besonderheiten
- Verwendet drei ASR2-Adapter für die Schiebersteuerung
- Kapselt die gesamte Verriegelungslogik in einem Sub-FB
- Ermöglicht zentrale Initialisierung aller Komponenten

## Zustandsübersicht
1. **Initialisierungszustand**: Wartet auf INIT-Ereignis
2. **Betriebszustand**: Verarbeitet Schieberstatus und Steuerbefehle
3. **Verriegelungszustand**: Verwaltet Sperrzustände der Seitenschieber

## Anwendungsszenarien
- Steuerung von industriellen Schiebersystemen
- Sicherheitskritische Verriegelungen in Anlagen
- Zentrale Verwaltung mehrerer Schieberkomponenten

## Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu einfachen Verriegelungs-FBs bietet dieser Composite-Baustein:
- Integration mehrerer Schiebertypen
- Zentralisierte Initialisierung
- Kapselung der gesamten Verriegelungslogik

## Fazit
Der `SchieberVerriegelungComposite`-FB bietet eine elegante Lösung für die Steuerung komplexer Schiebersysteme mit integrierter Verriegelungslogik. Durch die Kapselung der Kernfunktionalität und die Bereitstellung standardisierter Adapterschnittstellen ermöglicht er eine einfache Integration in größere Steuerungssysteme.
