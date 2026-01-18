# AX_FB_TOF

```{index} single: AX_FB_TOF
```

<img width="962" height="243" alt="image" src="https://github.com/user-attachments/assets/d92dd0e6-fa14-499e-8a97-5c1432d0df3e" />

* * * * * * * * * *

## Einleitung
**Wichtiger Hinweis: Dieser Baustein funktioniert nur korrekt, wenn er zyklisch aufgerufen wird.**

AX_FB_TOF ist ein standardisierter Timer-Funktionsblock gemäß IEC 61131-3, der eine Ausschaltverzögerung (Off-Delay Timing) realisiert. Der Baustein hält das Ausgangssignal nach dem Abschalten des Eingangssignals für eine definierte Zeitdauer aufrecht.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ** (Event): Normal Execution Request (übernimmt den Wert von PT); ruft den Baustein auf (muss zyklisch aufgerufen werden)

### **Ereignis-Ausgänge**
- Keine direkten Ereignisausgänge vorhanden

### **Daten-Eingänge**
- **PT** (TIME): Prozesszeit - definiert die Dauer der Ausschaltverzögerung

### **Daten-Ausgänge**
- **ET** (TIME): Abgelaufene Zeit (Elapsed Time)

### **Adapter**
- **IN** (Socket): Empfängt Eingangsereignisse und -daten (Typ: `adapter::types::unidirectional::AX`)
- **Q** (Plug): Sendet Ausgangsereignisse und -daten (Typ: `adapter::types::unidirectional::AX`)

## Funktionsweise
Der AX_FB_TOF-Block arbeitet als Ausschaltverzögerungstimer:
1. Wenn der Eingang am IN-Adapter TRUE wird, schaltet der Ausgang am Q-Adapter sofort auf TRUE.
2. Wenn der Eingang am IN-Adapter von TRUE auf FALSE wechselt, startet der interne Timer.
3. Der Ausgang am Q-Adapter bleibt TRUE, solange der Timer läuft und PT noch nicht erreicht wurde.
4. Nach Ablauf der Zeit PT wechselt der Ausgang am Q-Adapter auf FALSE.
5. Der Datenausgang ET zeigt die Zeit an, die seit dem Abfallen des Eingangssignals vergangen ist.
6. Wird der Eingang am IN-Adapter wieder TRUE, während der Timer läuft, wird der Timer zurückgesetzt und Q bleibt TRUE.

## Technische Besonderheiten
- Implementiert auf Basis des IEC 61131-3 TOF-Standards
- Verwendet unidirektionale Adapter für die Integration in moderne Steuerungskonzepte
- Bietet einen ET-Ausgang zur Überwachung der verbleibenden Verzögerungszeit
- Robuste Implementierung für zuverlässige Nachlaufsteuerungen

## Zustandsübersicht
1. **Inaktiv**: IN ist FALSE, Q ist FALSE, ET ist 0.
2. **Aktiv**: IN ist TRUE, Q ist TRUE, ET ist 0.
3. **Verzögerungsphase**: IN wechselt auf FALSE, Timer läuft, Q bleibt TRUE, ET steigt.
4. **Abgelaufen**: ET erreicht PT, Q wechselt auf FALSE.

## Anwendungsszenarien
- Nachlaufsteuerungen (z. B. Lüftersteuerung nach dem Abschalten eines Geräts)
- Entprellung von Signalen, die kurzzeitig abfallen könnten
- Sicherstellung von Mindestlaufzeiten nach einem Stopp-Befehl

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu ereignisbasierten Timern wie [AX_TOF](../../events/unidirectional/timers/AX_TOF.md) folgt dieser Baustein dem klassischen SPS-Verhalten nach IEC 61131-3 und bietet zusätzlich den ET-Statusausgang.

## Fazit
AX_FB_TOF ist der ideale Baustein für alle Anwendungen, die eine präzise Ausschaltverzögerung mit Statusrückmeldung über die abgelaufene Zeit erfordern.
