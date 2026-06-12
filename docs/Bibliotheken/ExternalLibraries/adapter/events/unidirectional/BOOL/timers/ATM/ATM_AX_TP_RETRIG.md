# ATM_AX_TP_RETRIG


![ATM_AX_TP_RETRIG](./ATM_AX_TP_RETRIG.svg)

* * * * * * * * * *
## Einleitung
Der `ATM_AX_TP_RETRIG` ist ein retriggerbarer Impuls-Timer-Funktionsblock. Er erzeugt einen Impuls von definierter Dauer am Ausgang, wenn der Eingang auf TRUE wechselt. Während des laufenden Impulses können weitere Trigger den Timer neu starten (Retrigger-Funktion). Ein Reset-Eingang beendet den Impuls sofort. Der Baustein verwendet standardisierte Adapter für Ein- und Ausgang, was eine flexible Anbindung in modularen Steuerungssystemen ermöglicht.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **R** (Event) – Reset: Setzt den Timer zurück und beendet den laufenden Impuls.

### **Ereignis-Ausgänge**
- **Q.E1** (Event) – Ausgangs-Event: Wird bei Änderung des Impulszustands (Beginn oder Ende) über den Adapter Q ausgelöst.

### **Daten-Eingänge**
- **IN.D1** (BOOL) – Triggereingang: Bei einer steigenden Flanke und TRUE-Wert startet der Timer.
- **PT.D1** (TIME) – Impulsdauer: Gibt die Zeit an, für die der Ausgang Q nach einem Trigger auf TRUE gesetzt wird.

### **Daten-Ausgänge**
- **Q.D1** (BOOL) – Impulsausgang: Zeigt während der Impulsdauer TRUE an, sonst FALSE.

### **Adapter**
- **IN** (Socket, Typ AX) – Eingangsadapter: Koppelt das Triggerevent (E1) und den boolschen Triggerwert (D1).
- **PT** (Socket, Typ ATM) – Zeitadapter: Liefert die Impulsdauer als TIME-Wert (D1).
- **Q** (Plug, Typ AX) – Ausgangsadapter: Stellt den Impulszustand (D1) und ein Ereignis bei Zustandsänderung (E1) bereit.

## Funktionsweise
Der Baustein verwendet intern den Standard-Funktionsblock `E_TP_RETRIG`. Ein Ereignis am Eingang **IN** (steigende Flanke von IN.E1) startet den Timer, sofern **IN.D1** = TRUE ist. Der Ausgang **Q.D1** wird für die in **PT.D1** angegebene Zeit auf TRUE gesetzt. Während dieser Zeit löst ein erneuter Trigger (wiederholtes IN.E1 mit IN.D1 = TRUE) einen Retrigger aus: Der Timer wird zurückgesetzt und der Impuls beginnt von vorn. Ein Ereignis am Reset-Eingang **R** beendet den Impuls sofort, **Q.D1** wird FALSE. Nach Ablauf der Impulsdauer ohne erneuten Trigger wechselt **Q.D1** automatisch zurück auf FALSE.

## Technische Besonderheiten
- **Retriggerbar**: Mehrfach-Trigger während eines laufenden Impulses starten den Timer neu, ohne den Impuls zu verlängern.
- **Adapterbasierte Schnittstelle**: Über die Adapter IN, PT und Q wird eine saubere Trennung von Ereignis- und Datenkommunikation erreicht.
- **Interner Standardbaustein**: Die eigentliche Timerlogik wird vom IEC 61499-konformen `E_TP_RETRIG` ausgeführt.
- **Unidirektionale Adapter**: Sowohl AX- als auch ATM-Adapter sind unidirektional ausgelegt, was die Datenflussrichtung klar definiert.

## Zustandsübersicht
Der Baustein kennt zwei Hauptzustände:

| Zustand  | Q.D1  | Beschreibung                                                     |
|----------|-------|------------------------------------------------------------------|
| **IDLE** | FALSE | Ruhezustand, kein Impuls aktiv.                                  |
| **TIMING** | TRUE  | Impuls läuft, Timer zählt die Dauer PT herab.                    |

**Übergänge:**
- IDLE → TIMING: Trigger (IN.E1 mit IN.D1 = TRUE)
- TIMING → TIMING (Retrigger): Erneuter Trigger startet Timer neu.
- TIMING → IDLE: Timer abgelaufen oder Reset (R)
- IDLE → IDLE: Reset ohne Wirkung

## Anwendungsszenarien
- **Impulssteuerung für Aktoren**: Ansteuerung von Ventilen, Lampen oder Motoren, die bei einem Startsignal für eine definierte Zeit aktiviert werden.
- **Sicherheitsanwendungen**: Retriggerbare Impulse ermöglichen eine erneute Anforderung während einer laufenden Aktion, z. B. bei Taster-Wiederholung.
- **Modulare Automatisierungssysteme**: Einsatz in Kombination mit anderen Adapter-basierten Komponenten zur einheitlichen Kommunikation über AX/ATM-Schnittstellen.

## Vergleich mit ähnlichen Bausteinen
- *E_TP (nicht retriggerbar)*: Ignoriert einen erneuten Trigger während des laufenden Impulses; einmal gestartet, läuft der Impuls immer vollständig ab.
- *E_TP_RETRIG (Standard)*: Gleiche Timerlogik, jedoch ohne Adapter-Schnittstelle – direkt über Ereignis- und Dateneingänge angeschlossen.
- *TON / TOF*: Andere Timer-Typen; TON verzögert das Einschalten, TOF verzögert das Ausschalten – beide erzeugen keine Impulse.

## Fazit
Der `ATM_AX_TP_RETRIG` kombiniert die bewährte retriggerbare Impulsfunktion mit einer adapterbasierten Schnittstelle. Durch die Verwendung standardisierter AX- und ATM-Adapter ist er besonders gut für modulare und wiederverwendbare Steuerungslösungen geeignet. Die Retrigger-Eigenschaft bietet Flexibilität in Anwendungen, bei denen ein Impuls bei erneuter Anforderung neu gestartet werden muss.