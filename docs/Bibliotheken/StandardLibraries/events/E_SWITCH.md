# E_SWITCH

```{index} single: E_SWITCH
```

<img width="1139" height="202" alt="E_SWITCH" src="https://user-images.githubusercontent.com/69573151/203071621-eb1065f1-d902-4120-95a3-0c50a7fcc66a.png">

* * * * * * * * * *

## 🎧 Podcast

* [E_SWITCH: Die Weiche der Automatisierung – Warum Einfachheit IEC 61499 revolutioniert](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/E_SWITCH-Die-Weiche-der-Automatisierung--Warum-Einfachheit-IEC-61499-revolutioniert-e3681fl)
* [E_SWITCH: The Unsung Hero of Industrial Automation's Modular Design](https://podcasters.spotify.com/pod/show/iec-61499-prime-course-en/episodes/E_SWITCH-The-Unsung-Hero-of-Industrial-Automations-Modular-Design-e367npq)
* [Unpacking E_T_FF_SR: The Secret Toggle Switch of Industrial Control Systems](https://podcasters.spotify.com/pod/show/iec-61499-prime-course-en/episodes/Unpacking-E_T_FF_SR-The-Secret-Toggle-Switch-of-Industrial-Control-Systems-e367ntv)

## 📺 Video

* [Ereignisschalter E_SWITCH aus der IEC 61499 (Übung 86)](https://www.youtube.com/watch?v=Gev-kGR4-Tc)

## Einleitung
Der `E_SWITCH` (Event Switch) ist ein grundlegender Funktionsbaustein nach IEC 61499, der als bedingte Ereignisweiche oder 1-zu-2-Demultiplexer fungiert. Er leitet ein einzelnes Eingangereignis (`EI`) basierend auf dem Zustand einer booleschen Steuervariable (`G`) an einen von zwei Ausgängen weiter.

## Schnittstellenstruktur

### **Ereignis-Eingänge:**
- **EI (Event Input)**: Das Eingangereignis, das weitergeleitet werden soll.
    - **Verbundene Daten**: `G`

### **Ereignis-Ausgänge:**
- **EO0**: Der erste Ereignisausgang.
- **EO1**: Der zweite Ereignisausgang.

### **Daten-Eingänge:**
- **G (Guard)**: Die boolesche Bedingung, die die Weiche steuert (Datentyp: `BOOL`).

## Funktionsweise
1.  **Ereignisempfang**: Der Baustein wartet auf ein Ereignis am Eingang `EI`.
2.  **Prüfung der Bedingung**: Wenn das `EI`-Ereignis eintrifft, wird der Wert der Datenvariable `G` ausgewertet.
3.  **Bedingte Weiterleitung**:
    - **Wenn `G` = `FALSE` ist**: Das Ereignis wird an den Ausgang `EO0` weitergeleitet.
    - **Wenn `G` = `TRUE` ist**: Das Ereignis wird an den Ausgang `EO1` weitergeleitet.

Das Ereignis am Eingang `EI` wird also immer an genau einen der beiden Ausgänge geleitet, abhängig von der Steuerbedingung `G`.

## Technische Besonderheiten
- **Ereignisweiche**: Dient als grundlegendes "Switch" oder "If-Else"-Konstrukt für den Ereignisfluss.
- **Zustandslos**: Der Baustein selbst hat keinen internen Speicher; seine Entscheidung basiert ausschließlich auf dem Wert von `G` im Moment des `EI`-Ereignisses.

## Anwendungsszenarien
- **Bedingte Logik**: Ausführen von alternativen Aktionen basierend auf einer Bedingung. Wenn `G` wahr ist, führe Aktion A (`EO1`) aus, ansonsten führe Aktion B (`EO0`) aus.
- **Modusabhängige Verarbeitung**: Weiterleiten von Befehlen an unterschiedliche Verarbeitungspfade, je nachdem, ob sich das System in einem "Automatik"-Modus (`G=TRUE`) oder "Hand"-Modus (`G=FALSE`) befindet.
- **Fehlerbehandlung**: Weiterleiten eines Sensor-Ereignisses entweder an die normale Verarbeitungslogik (`G=FALSE` für "kein Fehler") oder an eine Fehlerbehandlungsroutine (`G=TRUE` für "Fehler erkannt").

## Vergleich mit ähnlichen Bausteinen

| Feature        | E_SWITCH | E_SELECT | E_DEMUX |
|---------------|----------|----------|---------|
| Auswahlkriterium | Boolesch (`G`) | Boolesch (`G`) | Index (`K`) |
| Richtung      | 1:2 (Demultiplexer) | 2:1 (Multiplexer) | 1:n (Demultiplexer) |
| Zustandsmodell | BasicFB | BasicFB | BasicFB/Generic |

## Fazit
Der `E_SWITCH`-Baustein ist ein fundamentaler und weit verbreiteter Baustein zur Implementierung von bedingten Verzweigungen in der ereignisgesteuerten Logik von IEC 61499. Seine Einfachheit und klare Funktion als "If-Else"-Weiche für Ereignisse machen ihn zu einem unverzichtbaren Werkzeug für die Erstellung von flexibler und robuster Steuerungssoftware.