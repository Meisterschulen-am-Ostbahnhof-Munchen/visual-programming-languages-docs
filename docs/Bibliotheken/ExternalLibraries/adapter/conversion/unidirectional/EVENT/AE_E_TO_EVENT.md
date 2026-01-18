# AE_E_TO_EVENT

```{index} single: AE_E_TO_EVENT
```

<img width="1231" height="221" alt="image" src="https://github.com/user-attachments/assets/2194d39b-b5e1-4ac1-a0ec-3cc874a94b26" />

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