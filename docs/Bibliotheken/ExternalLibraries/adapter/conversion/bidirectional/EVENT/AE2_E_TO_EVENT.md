# AE2_E_TO_EVENT

```{index} single: AE2_E_TO_EVENT
```

<img width="1172" height="190" alt="image" src="https://github.com/user-attachments/assets/02b7c06e-111f-4166-ac20-aebdf89c9956" />

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
Der Funktionsblock AE2_E_TO_EVENT ist ein Composite-Funktionsblock, der zur Konvertierung von AE2-Adapter-Signalen in Ereignisse dient. Er ermöglicht die bidirektionale Kommunikation zwischen Adapter-basierten Komponenten und ereignisgesteuerten Funktionsblöcken.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ** (Request to Adapter): Startet die Konvertierung und sendet eine Anfrage an den Adapter

### **Ereignis-Ausgänge**
- **CNF** (Confirmation from Adapter): Bestätigt den erfolgreichen Abschluss der Konvertierung

### **Daten-Eingänge**
*Keine Daten-Eingänge vorhanden*

### **Daten-Ausgänge**
*Keine Daten-Ausgänge vorhanden*

### **Adapter**
- **AE2_IN** (Adapter Input): Bidirektionaler AE2-Adapter-Eingang für die Kommunikation mit AE2-kompatiblen Komponenten

## Funktionsweise
Der Funktionsblock arbeitet als einfacher Konverter zwischen dem AE2-Adapter-Protokoll und dem standardmäßigen 4diac-Ereignissystem. Bei Empfang eines REQ-Ereignisses wird eine Anfrage über den AE2-Adapter gesendet. Die Antwort des Adapters wird über das EO1-Signal empfangen und als CNF-Ereignis ausgegeben.

## Technische Besonderheiten
- Implementiert als Composite-Funktionsblock
- Verwendet bidirektionale AE2-Adapter-Kommunikation
- Einfache Ereignisweiterleitung ohne Datenmanipulation
- Position des CNF-Ausgangs ist fest auf Y-Position 46 definiert

## Zustandsübersicht
Der Funktionsblock verfügt über zwei Hauptzustände:
1. **Wartezustand**: Keine aktive Konvertierung
2. **Aktivzustand**: Konvertierung läuft (nach REQ-Eingang bis CNF-Ausgabe)

## Anwendungsszenarien
- Integration von AE2-kompatiblen Geräten in 4diac-Steuerungen
- Bridge-Funktionalität zwischen verschiedenen Kommunikationsprotokollen
- Einfache Ereigniskonvertierung in Automatisierungssystemen
- Protokollumsetzung in verteilten Steuerungssystemen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen Adapter-Konvertern zeichnet sich AE2_E_TO_EVENT durch seine spezifische Ausrichtung auf das AE2-Adapter-Protokoll aus. Während allgemeine Adapter-Konverter verschiedene Protokolle unterstützen, ist dieser Baustein speziell für die bidirektionale AE2-Kommunikation optimiert.

## Fazit
Der AE2_E_TO_EVENT Funktionsblock bietet eine zuverlässige und einfache Lösung zur Integration von AE2-Adaptern in ereignisgesteuerte 4diac-Systeme. Seine klare Schnittstellendefinition und direkte Funktionsweise machen ihn zu einem praktischen Werkzeug für Protokollkonvertierungen in industriellen Automatisierungsanwendungen.