# ASR2_4EVENTS_TO_SR2

```{index} single: ASR2_4EVENTS_TO_SR2
```

<img width="1146" height="210" alt="image" src="https://github.com/user-attachments/assets/73199e82-fa67-457f-b043-7f54b3d02af7" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock ASR2_4EVENTS_TO_SR2 ist ein Composite-Funktionsblock, der zur Konvertierung von 4 Ereignissen in das ASR2-Adapterformat dient. Er ermöglicht die bidirektionale Umwandlung zwischen einzelnen Set/Reset-Ereignissen und dem standardisierten ASR2-Adapter.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **EI_SET**: Set-Ereignis (Einschalten)
- **EI_RESET**: Reset-Ereignis (Ausschalten)

### **Ereignis-Ausgänge**
- **EO_SET**: Set-Ereignis (Einschalten)
- **EO_RESET**: Reset-Ereignis (Ausschalten)

### **Adapter**
- **ASR_OUT**: ASR2-Adapter-Ausgang (bidirektional)

## Funktionsweise
Der Funktionsblock fungiert als Brücke zwischen einzelnen Ereignissen und dem ASR2-Adapter. Er leitet eingehende Set- und Reset-Ereignisse an den ASR2-Adapter weiter und gibt gleichzeitig entsprechende Ereignisse vom ASR2-Adapter an die Ausgänge weiter. Dies ermöglicht eine nahtlose Integration von Einzelereignissen in Systeme, die das ASR2-Adapterformat verwenden.

## Technische Besonderheiten
- Bidirektionale Signalübertragung
- Direkte Ereignisweiterleitung ohne Datenverarbeitung
- Kompatibel mit dem ASR2-Adapterstandard
- Composite-Funktionsblock-Implementierung

## Zustandsübersicht
Der Funktionsblock besitzt keinen internen Zustand, da er ausschließlich als Durchschleif-Element fungiert. Alle Ereignisse werden direkt und ohne Verzögerung weitergeleitet.

## Anwendungsszenarien
- Integration von Einzelereignis-Systemen in ASR2-basierte Architekturen
- Protokollkonvertierung zwischen verschiedenen Steuerungssystemen
- Adapter-Lösungen für bestehende Automatisierungssysteme
- Bidirektionale Kommunikation zwischen verschiedenen Ereignisformaten

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen Ereignis-Bausteinen bietet ASR2_4EVENTS_TO_SR2 spezifische Adapter-Funktionalität für das ASR2-Format. Während Standard-Bausteine typischerweise nur unidirektionale Signalverarbeitung bieten, ermöglicht dieser Baustein bidirektionale Kommunikation mit ASR2-kompatiblen Systemen.

## Fazit
Der ASR2_4EVENTS_TO_SR2 Funktionsblock stellt eine effiziente Lösung für die Integration von Einzelereignissen in ASR2-basierte Systeme dar. Seine bidirektionale Funktionalität und direkte Ereignisweiterleitung machen ihn zu einem wertvollen Baustein für Systemintegration und Protokollkonvertierung in automatisierten Steuerungssystemen.