# AX_TP_RETRIG


![AX_TP_RETRIG](./AX_TP_RETRIG.svg)

* * * * * * * * * *

## Einleitung

Der Baustein **AX_TP_RETRIG** ist ein standardisierter Timer-Funktionsbaustein (Puls) in einer retriggerbaren Ausführung. Er erzeugt auf den Adapterausgang **Q** einen Impuls von der Dauer **PT**, sobald das Eingangssignal **IN** eine steigende Flanke (Ereignis REQ) empfängt. Der Impuls wird bei jedem neuen REQ-Ereignis neu gestartet (Retrigger). Ein Reset über den Ereigniseingang **R** setzt die Impulszeit **PT** vor und setzt den Timer zurück.

Der Baustein ist für den Einsatz in IEC 61499‑basierten Automatisierungssystemen konzipiert und nutzt das AX‑Adapter‑Interface für eine effiziente, unidirektionale Signalübertragung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
|----------|--------------|
| **R** | Reset – Setzt die Impulszeit **PT** vor und beendet einen laufenden Impuls sofort. |

### **Ereignis-Ausgänge**

Keine eigenen Ereignisausgänge – die Ausgabe erfolgt über den Adapter **Q** (Ereignis **E1**).

### **Daten-Eingänge**

| Name | Typ   | Beschreibung |
|------|-------|--------------|
| **PT** | TIME | Impulsdauer (Pulszeit). |

### **Daten-Ausgänge**

Keine eigenen Datenausgänge – die Ausgabe des Impulszustands erfolgt über den Adapter **Q** (Datenwert **D1**).

### **Adapter**

| Name | Typ | Richtung | Beschreibung |
|------|-----|----------|--------------|
| **IN** | `adapter::types::unidirectional::AX` | Socket | Eingang – Empfängt das Startsignal (Ereignis **E1**) und den logischen Wert (**D1**). Eine steigende Flanke auf **E1** triggert den Impuls. |
| **Q** | `adapter::types::unidirectional::AX` | Plug | Ausgang – Gibt den Impuls aus: Solange der Impuls aktiv ist, ist **D1** = `TRUE`, sonst `FALSE**. Das Ereignis **E1** wird bei jedem Zustandswechsel gesendet. |

## Funktionsweise

1. **Initialzustand** – **Q.D1** ist `FALSE`, kein Impuls aktiv.
2. **Start** – Bei einem Ereignis **IN.E1** (steigende Flanke wird als REQ interpretiert) startet der Baustein einen Impuls der Dauer **PT**. **Q.D1** wird sofort auf `TRUE` gesetzt, das Ereignis **Q.E1** wird gesendet.
3. **Retrigger** – Während der Impuls noch aktiv ist, führt ein erneutes **IN.E1** dazu, dass der Timer zurückgesetzt wird und der Impuls für die volle Dauer **PT** neu beginnt. **Q.D1** bleibt während des gesamten Impulses `TRUE`.
4. **Impulsende** – Nach Ablauf von **PT** (ohne erneuten Trigger) wird **Q.D1** auf `FALSE` zurückgesetzt und **Q.E1** erneut gesendet.
5. **Reset** – Das Ereignis **R** beendet einen laufenden Impuls sofort und setzt **Q.D1** auf `FALSE`. Gleichzeitig wird **PT** mit dem aktuellen Wert am Eingang **PT** vorgesetzt (kann für eine neue Impulsdauer genutzt werden).

## Technische Besonderheiten

- **Retriggerbarkeit** – Im Gegensatz zu einfachen Timer-Bausteinen wird ein laufender Impuls durch einen neuen Startimpuls nicht abgebrochen, sondern verlängert (Timer-Neustart).
- **Adapterschnittstelle** – Statt einzelner Ereignis-/Datenports wird das AX‑Adapter‑Interface verwendet, das eine standardisierte, unidirektionale Verbindung ermöglicht. Dadurch vereinfacht sich die Verschaltung in Adapter‑basierten Architekturen.
- **Lizenz** – Der Baustein ist unter der **Eclipse Public License 2.0** veröffentlicht (siehe Copyright‑Hinweise).
- **Implementierung** – Intern wird der IEC‑61499‑Standardbaustein **E_TP_RETRIG** genutzt, der über das Netzwerk eingebunden ist.

## Zustandsübersicht

Der Baustein durchläuft folgende Zustände (basierend auf dem internen Timer‑Baustein):

| Zustand | Beschreibung |
|---------|--------------|
| **IDLE** | Kein Impuls aktiv; **Q.D1** = `FALSE`. |
| **RUNNING** | Impuls aktiv; **Q.D1** = `TRUE`. Der Timer läuft für die Dauer **PT**. Bei erneutem Trigger wird der Timer zurückgesetzt (bleibt im Zustand RUNNING). |
| **TIMEOUT** | Impuls beendet; Wechsel zurück zu IDLE. |

Hinweis: Der Reset (Ereignis **R**) führt immer sofort in den Zustand IDLE.

## Anwendungsszenarien

- **Steuerung von Ausgangssignalen mit fester Impulsdauer** – z. B. Ansteuerung eines Relais, das für eine definierte Zeit geschaltet wird.
- **Taktgeber mit Nachtriggerung** – Wenn während eines Impulses ein erneutes Startsignal eintrifft, soll die Impulsdauer verlängert werden (z. B. bei einem manuellen Taster, der länger gedrückt wird).
- **Sicherheitsverriegelungen** – Ein Alarm oder eine Aktion soll für eine Mindestdauer aktiv bleiben, auch wenn der auslösende Zustand kurzzeitig verschwindet.
- **Zeitgesteuerte Freigaben** – z. B. eine Maschinenbewegung, die nach einem Startsignal für die Dauer **PT** ausgeführt wird, aber bei erneutem Startimpuls neu beginnt.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Eigenschaft |
|----------|-------------|
| **AX_TP_RETRIG** | Retriggerbarer Puls-Timer mit AX‑Adapter. |
| **E_TP** (Standard IEC 61499) | Einfacher Puls-Timer, nicht retriggerbar – ein erneuter Start während des Impulses wird ignoriert. |
| **E_TP_RETRIG** | Retriggerbare Version ohne Adapter (reine Event/Daten‑Schnittstelle). |
| **E_DELAY** (Verzögerung) | Verzögert ein Signal um eine feste Zeit, erzeugt aber keinen Impuls fester Dauer. |

Der **AX_TP_RETRIG** kombiniert die Retrigger‑Funktionalität mit der kompakten Adapter‑Schnittstelle und eignet sich daher besonders für modulare, adapterbasierte Systeme.

## Fazit

Der **AX_TP_RETRIG** ist ein flexibler und standardisierter Timer‑Funktionsbaustein für IEC 61499‑Anwendungen. Seine Retrigger‑Eigenschaft macht ihn ideal für Situationen, in denen ein Impuls bei wiederholten Startbefehlen verlängert werden soll. Die Verwendung des AX‑Adapter‑Interfaces vereinfacht die Anbindung an andere Adapter‑basierte Komponenten und fördert eine saubere, modulare Systemarchitektur. Durch die klare Trennung von Ereignis- und Datenflüssen sowie die Einhaltung des Standards eignet sich der Baustein für den zuverlässigen Einsatz in industriellen Steuerungssystemen.