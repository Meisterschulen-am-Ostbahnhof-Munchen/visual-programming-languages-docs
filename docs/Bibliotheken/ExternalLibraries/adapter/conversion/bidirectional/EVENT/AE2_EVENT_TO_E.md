# AE2_EVENT_TO_E

```{index} single: AE2_EVENT_TO_E
```

<img width="1172" height="190" alt="image" src="https://github.com/user-attachments/assets/5d62029b-f8de-45fd-a75c-34b753c1edc3" />

* * * * * * * * * *

## 🎧 Podcast

* [E_TOF vs. FB_TOF: Der Event-Timer, der nicht zyklisch tickt – Revolution für Automatisierungssysteme?](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/E_TOF-vs--FB_TOF-Der-Event-Timer--der-nicht-zyklisch-tickt--Revolution-fr-Automatisierungssysteme-e3673qk)
* [EventFBs nach IEC 61499: Legosteine der Automatisierung – So funktionieren Ereignis-Funktionsbausteine](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/EventFBs-nach-IEC-61499-Legosteine-der-Automatisierung--So-funktionieren-Ereignis-Funktionsbausteine-e375gjm)
* [IEC 61499: Revolution der Automatisierung – Event-gesteuerte FBs und verteilte Systeme erklärt](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/IEC-61499-Revolution-der-Automatisierung--Event-gesteuerte-FBs-und-verteilte-Systeme-erklrt-e3671vb)
* [E_REND: Event Synchronization in IEC 61499](https://podcasters.spotify.com/pod/show/iec-61499-prime-course-en/episodes/E_REND-Event-Synchronization-in-IEC-61499-e368cv2)
* [The Unstoppable Counter: Why IEC 61499's ECTU Guarantees Safe, Event-Driven Control (and Never Overflows)](https://podcasters.spotify.com/pod/show/iec-61499-prime-course-en/episodes/The-Unstoppable-Counter-Why-IEC-61499s-ECTU-Guarantees-Safe--Event-Driven-Control-and-Never-Overflows-e3a9qsh)

## 📺 Video

* [D-Flip-Flop: E_D_FF aus der IEC 61499 (Übung 002c) als "Eventbremse"](https://www.youtube.com/watch?v=yGSx_0ggveE)
* [Doppeltes Lasthalteventil](https://www.youtube.com/watch?v=ZZ98nYTeWIc)
* [E_TOF vs. FB_TOF: Der Event-Timer, der nicht zyklisch tickt – Revolution für Automatisierungssyst...](https://www.youtube.com/watch?v=ZT3DCrHU-pA)
* [EventFBs nach IEC 61499: Legosteine der Automatisierung – So funktionieren Ereignis-Funktionsbaus...](https://www.youtube.com/watch?v=4Z9TjTT78rg)
* [The One Shot Signal  How PLCs Prevent Double Takes](https://www.youtube.com/watch?v=vu_iAothAu4)

## Einleitung
Der Funktionsblock AE2_EVENT_TO_E ist ein Composite-Funktionsblock, der zur Konvertierung von EVENT-Signalen in das AE2-Adapterformat dient. Er ermöglicht die bidirektionale Kommunikation zwischen Standard-Ereignissen und dem spezifischen AE2-Adapter.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ** (Request to Adapter): Startet die Konvertierung und sendet eine Anfrage an den AE2-usgangsadapter

### **Ereignis-Ausgänge**
- **CNF** (Confirmation from Adapter): Bestätigt den erfolgreichen Abschluss der Konvertierung und den Empfang der Antwort vom AE2-Adapter

### **Daten-Eingänge**
Keine Daten-Eingänge vorhanden

### **Daten-Ausgänge**
Keine Daten-Ausgänge vorhanden

### **Adapter**
- **AE2_OUT** (Adapter Output): Bidirektionaler AE2-Ausgangsadapter für die Kommunikation mit AE2-kompatiblen Systemen

## Funktionsweise
Der Funktionsblock leitet eingehende REQ-Ereignisse direkt an den AE2_OUT-Adapter weiter (EO1-Port). Gleichzeitig werden eingehende Bestätigungen vom AE2-Adapter (EI1-Port) als CNF-Ereignis ausgegeben. Dies ermöglicht eine transparente Konvertierung zwischen dem Standard-EVENT-Format und dem spezifischen AE2-Adapterprotokoll.

## Technische Besonderheiten
- Implementiert als Composite-Funktionsblock
- Unterstützt bidirektionale Kommunikation
- Verwendet den AE2-Adaptertyp aus dem adapter::types::bidirectional-Paket
- Positionierte Adapter-Schnittstelle für optimierte Visualisierung

## Zustandsübersicht
Der Funktionsblock verfügt über einen einfachen Zustandsautomaten:
1. **Idle-Zustand**: Wartet auf REQ-Ereignis
2. **Request-Zustand**: Nach REQ-Eingabe, Sendung an AE2_OUT.EO1
3. **Confirmation-Zustand**: Nach Empfang von AE2_OUT.EI1, Ausgabe von CNF

## Anwendungsszenarien
- Integration von EVENT-basierten Systemen in AE2-kompatible Umgebungen
- Protokollkonvertierung in verteilten Automatisierungssystemen
- Bidirektionale Kommunikationsbrücken zwischen verschiedenen Automatisierungskomponenten
- Adapter-basierte Systemintegration

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen EVENT-Konvertern bietet AE2_EVENT_TO_E spezifische AE2-Adapterunterstützung mit bidirektionaler Kommunikation. Während Standard-Konverter oft nur unidirektional arbeiten, ermöglicht dieser Baustein vollständige Request-Response-Zyklen mit dem AE2-Protokoll.

## Fazit
Der AE2_EVENT_TO_E Funktionsblock stellt eine zuverlässige Lösung für die Konvertierung zwischen Standard-EVENT-Signalen und dem AE2-Adapterprotokoll dar. Seine bidirektionale Funktionalität und einfache Integration machen ihn besonders geeignet für Systeme, die eine nahtlose Kommunikation zwischen verschiedenen Protokollwelten erfordern.