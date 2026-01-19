# PUBLISH_9

```{index} single: PUBLISH_9
```

<img width="1180" height="464" alt="image" src="https://github.com/user-attachments/assets/c5b7e507-1bcf-405c-b068-72840502bb8f" />

* * * * * * * * * *

## Einleitung
Der PUBLISH_9 Funktionsblock dient zum Veröffentlichen von Daten an einen oder mehrere SUBSCRIBE_9 Blöcke. Er ermöglicht die unbestätigte Übertragung von bis zu neun verschiedenen Datenwerten über ein Kommunikationsnetzwerk.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Initialisierungsereignis mit zugehörigen Daten QI und ID
- **REQ**: Sendeanforderung für unbestätigte Datenübertragung mit neun Datenwerten

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung mit QO und STATUS
- **CNF**: Bestätigung, dass Daten gesendet wurden, mit QO und STATUS

### **Daten-Eingänge**
- **QI** (BOOL): Qualifizierer für Initialisierung (TRUE = aktivieren, FALSE = deaktivieren)
- **ID** (WSTRING): Identifikator für den Kommunikationskanal
- **SD_1** bis **SD_9** (ANY): Neun verschiedene zu sendende Datenwerte beliebigen Typs

### **Daten-Ausgänge**
- **QO** (BOOL): Qualifizierer für Ausgangszustand
- **STATUS** (WSTRING): Statusinformationen über den Betriebszustand

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der PUBLISH_9 Block wird zunächst über das INIT-Ereignis initialisiert, wobei der ID-Parameter den Kommunikationskanal definiert. Bei aktiviertem QI-Eingang (TRUE) können Daten über das REQ-Ereignis gesendet werden. Der Block überträgt dabei alle neun SD_x Datenwerte gleichzeitig an alle angeschlossenen SUBSCRIBE_9 Blöcke. Die Übertragung erfolgt unbestätigt, jedoch signalisiert das CNF-Ereignis die erfolgreiche Abarbeitung der Sendeanforderung.

## Technische Besonderheiten
- Unterstützt bis zu neun verschiedene Datenwerte beliebigen Typs (ANY)
- Unbestätigte Kommunikation (fire-and-forget Prinzip)
- WSTRING-basierte Kanalidentifikation für flexible Adressierung
- Generische Implementierung durch GEN_PUBLISH Basisklasse

## Zustandsübersicht
Der Block verfügt über zwei Hauptzustände: initialisiert und nicht initialisiert. Nach erfolgreicher Initialisierung (INIT mit QI=TRUE) wechselt der Block in den aktiven Zustand und kann Daten senden. Bei Deaktivierung (INIT mit QI=FALSE) wird der Block deinitialisiert.

## Anwendungsszenarien
- Verteilte Systeme mit Publisher-Subscriber-Architektur
- Datenaustausch zwischen verschiedenen Steuerungskomponenten
- Broadcast-Kommunikation in Automatisierungsnetzwerken
- Systeme mit 1-zu-n Kommunikationsbeziehungen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu bestätigten Kommunikationsblöcken bietet PUBLISH_9 eine reduzierte Latenz durch den Verzicht auf Empfangsbestätigungen. Gegenüber Blöcken mit weniger Datenkanälen ermöglicht er die gleichzeitige Übertragung mehrerer Datenwerte, was die Systemeffizienz erhöht.

## Fazit
Der PUBLISH_9 Funktionsblock ist eine leistungsfähige Lösung für unbestätigte Mehrfachdatenübertragungen in verteilten Automatisierungssystemen. Seine Flexibilität bei der Datenübertragung und die Unterstützung für neun verschiedene Datenwerte machen ihn ideal für komplexe Kommunikationsszenarien in industriellen Steuerungssystemen.