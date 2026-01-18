# AE_E_TO_EVENT

```{index} single: AE_E_TO_EVENT
```

<img width="1231" height="221" alt="image" src="https://github.com/user-attachments/assets/2194d39b-b5e1-4ac1-a0ec-3cc874a94b26" />

* * * * * * * * * *

## Einleitung
Der Funktionsblock AE_E_TO_EVENT ist ein Composite-Funktionsblock, der zur Konvertierung von Adapter-Ereignissen in Standard-Ereignisse dient. Er ermöglicht die Umwandlung von Adapter-Signalen in allgemein verwendbare Ereignisausgaben und dient als Brücke zwischen Adapter-Schnittstellen und standardisierten Event-basierten Kommunikationsstrukturen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*Keine direkten Ereigniseingänge vorhanden*

### **Ereignis-Ausgänge**
- **CNF** - Bestätigungsereignis vom Adapter

### **Daten-Eingänge**
*Keine Dateneingänge vorhanden*

### **Daten-Ausgänge**
*Keine Datenausgänge vorhanden*

### **Adapter**
- **AE_IN** - Adapter-Eingang vom Typ `adapter::types::unidirectional::AE`

## Funktionsweise
Der Funktionsblock leitet das E1-Ereignis vom Adapter-Eingang AE_IN direkt an den CNF-Ausgang weiter. Es handelt sich um eine einfache Durchschleif-Funktionalität, bei der Adapter-Ereignisse in standardisierte Funktionsblock-Ereignisse umgewandelt werden.

## Technische Besonderheiten
- Unidirektionale Signalverarbeitung
- Keine Datenverarbeitung oder -konvertierung
- Direkte Ereignisweiterleitung ohne Verzögerung
- Positionierung des CNF-Ausgangs bei Y-Position 46

## Zustandsübersicht
Der Funktionsblock besitzt einen einfachen Zustand:
- **Bereit**: Wartet auf E1-Ereignis vom Adapter
- Bei Eintreffen von E1 wird sofort CNF ausgelöst

## Anwendungsszenarien
- Integration von Adapter-Schnittstellen in bestehende Funktionsblock-Netzwerke
- Kopplung unterschiedlicher Kommunikationsprotokolle
- Erweiterung von Systemen mit speziellen Adapter-Anforderungen
- Protokollumsetzung in verteilten Automatisierungssystemen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen Konvertierungsbausteinen zeichnet sich AE_E_TO_EVENT durch seine Einfachheit aus. Während andere Konverter oft zusätzliche Datenverarbeitung oder Signalaufbereitung bieten, beschränkt sich dieser Baustein auf die reine Ereignisweiterleitung.

## Fazit
Der AE_E_TO_EVENT Funktionsblock stellt eine schlanke und effiziente Lösung zur Adapter-Integration dar. Seine Einfachheit macht ihn zuverlässig und leicht verständlich, während er gleichzeitig die notwendige Brückenfunktion zwischen Adapter-Schnittstellen und standardisierten Event-Systemen erfüllt.
