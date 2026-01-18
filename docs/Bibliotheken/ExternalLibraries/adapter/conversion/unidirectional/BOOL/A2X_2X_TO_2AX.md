# A2X_2X_TO_2AX

```{index} single: A2X_2X_TO_2AX
```

<img width="1288" height="205" alt="image" src="https://github.com/user-attachments/assets/4b63ce13-a3c7-4b18-908a-dc885376b86d" />

* * * * * * * * * *

## Einleitung
Der A2X_2X_TO_2AX ist ein Composite-Funktionsblock, der zur Konvertierung von A2X-Signalen in zwei separate AX-Signale dient. Dieser Baustein ermöglicht die Umwandlung bidirektionaler Steuersignale in unidirektionale Bewegungsbefehle.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- Keine direkten Ereignis-Eingänge vorhanden

### **Ereignis-Ausgänge**
- Keine direkten Ereignis-Ausgänge vorhanden

### **Daten-Eingänge**
- Keine direkten Daten-Eingänge vorhanden

### **Daten-Ausgänge**
- Keine direkten Daten-Ausgänge vorhanden

### **Adapter**

**Eingangsadapter:**
- `A2X_IN` (Socket) - Adapter-Eingang vom Typ `adapter::types::unidirectional::A2X`

**Ausgangsadapter:**
- `UP` (Plug) - Ausgang für positive Bewegungsrichtung (TRUE = vorwärts, oben, rechts, im Uhrzeigersinn)
- `DOWN` (Plug) - Ausgang für negative Bewegungsrichtung (TRUE = rückwärts, unten, links, gegen den Uhrzeigersinn)

## Funktionsweise
Der Composite-Funktionsblock leitet die Ereignisse und Daten direkt vom A2X_IN-Adapter an die entsprechenden UP- und DOWN-Ausgangsadapter weiter:

- Das E_UP-Ereignis wird an UP.E1 weitergeleitet
- Das E_DOWN-Ereignis wird an DOWN.E1 weitergeleitet
- Die UP-Daten werden an UP.D1 weitergeleitet
- Die DOWN-Daten werden an DOWN.D1 weitergeleitet

## Technische Besonderheiten
- Implementiert als Composite-FB ohne interne Logik
- Direkte Signalweiterleitung ohne Verzögerung
- Verwendet unidirektionale Adaptertypen für klare Signalflussrichtung

## Zustandsübersicht
Der Funktionsblock besitzt keinen internen Zustand und arbeitet stateless. Alle Eingangssignale werden sofort an die entsprechenden Ausgänge weitergeleitet.

## Anwendungsszenarien
- Umwandlung von bidirektionalen Antriebssignalen in separate Vorwärts/Rückwärts-Steuerungen
- Ansteuerung von Aktoren mit separaten Ein- und Ausfahrbefehlen
- Integration in Steuerungssysteme mit unterschiedlichen Signalformaten
- Drehzahlregelung mit separaten Rechts-/Linkslauf-Steuerungen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen Konverter-Bausteinen bietet dieser Composite-FB eine strukturierte Lösung für die Aufteilung bidirektionaler Signale in zwei unabhängige unidirektionale Kanäle. Die Verwendung standardisierter Adaptertypen gewährleistet Kompatibilität innerhalb des Adapter-Frameworks.

## Fazit
Der A2X_2X_TO_2AX Funktionsblock stellt eine effiziente und standardkonforme Lösung zur Signalumwandlung dar. Durch seine einfache, direkte Weiterleitungslogik und die Verwendung etablierter Adaptertypen eignet er sich ideal für die Integration in komplexere Steuerungssysteme, die eine Trennung von Bewegungsrichtungen erfordern.
