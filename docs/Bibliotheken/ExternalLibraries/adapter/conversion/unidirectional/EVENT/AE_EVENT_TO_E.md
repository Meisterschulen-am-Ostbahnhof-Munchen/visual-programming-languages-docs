# AE_EVENT_TO_E

```{index} single: AE_EVENT_TO_E
```

<img width="1310" height="249" alt="image" src="https://github.com/user-attachments/assets/4eca9bad-6eed-4dfd-9643-3b25d2e4cfc3" />

* * * * * * * * * *

## Einleitung
Der Funktionsblock AE_EVENT_TO_E ist ein Composite-Funktionsblock, der zur Konvertierung von Ereignissen in AE-Adapter-Signale dient. Er ermöglicht die Umwandlung eines einfachen Ereignisses in ein Adapter-basiertes Ausgangssignal, was insbesondere bei der Integration verschiedener Kommunikationsschnittstellen nützlich ist.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Anfrage-Ereignis zur Auslösung der Adapter-Konvertierung

### **Ereignis-Ausgänge**
- Keine direkten Ereignis-Ausgänge vorhanden

### **Daten-Eingänge**
- Keine Daten-Eingänge vorhanden

### **Daten-Ausgänge**
- Keine Daten-Ausgänge vorhanden

### **Adapter**
- **AE_OUT**: Unidirektionaler AE-Adapter-Ausgang für die Weiterleitung der konvertierten Ereignisse

## Funktionsweise
Der Funktionsblock arbeitet als einfacher Konverter, der eingehende REQ-Ereignisse direkt an den AE_OUT-Adapter weiterleitet. Bei jedem Eintreffen eines REQ-Ereignisses wird das entsprechende E1-Ereignis am AE-Adapter-Ausgang ausgelöst. Es findet keine Datenverarbeitung oder -transformation statt, da der Block ausschließlich Ereignisse weiterleitet.

## Technische Besonderheiten
- Composite-Funktionsblock mit einfacher Netzwerkstruktur
- Verwendet unidirektionale AE-Adapter-Schnittstelle
- Keine Datenverarbeitungskomponenten enthalten
- Direkte Ereignisweiterleitung ohne Verzögerung

## Zustandsübersicht
Der Funktionsblock besitzt einen einfachen Zustand:
- **Bereit**: Wartet auf eingehende REQ-Ereignisse
- Bei Eintreffen von REQ wird sofort AE_OUT.E1 ausgelöst und der Block kehrt in den Bereitschaftszustand zurück

## Anwendungsszenarien
- Integration von ereignisbasierten Systemen in Adapter-basierte Architekturen
- Kopplung unterschiedlicher Kommunikationsprotokolle
- Als Brücke zwischen einfachen Ereignissen und komplexeren Adapter-Schnittstellen
- In Systemen, die eine standardisierte AE-Schnittstelle erfordern

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen Konvertierungsbausteinen zeichnet sich AE_EVENT_TO_E durch seine Einfachheit aus. Während andere Konverter oft Datenverarbeitung oder Protokollumsetzung durchführen, beschränkt sich dieser Block auf die reine Ereignisweiterleitung. Er ist speziell für die Integration in Adapter-basierte Systeme optimiert.

## Fazit
AE_EVENT_TO_E ist ein spezialisierter Funktionsblock für die einfache Konvertierung von Ereignissen in AE-Adapter-Signale. Seine Stärke liegt in der minimalistischen Implementierung und der zuverlässigen Ereignisweiterleitung, was ihn ideal für Systemintegrationen macht, bei denen keine Datenverarbeitung erforderlich ist.