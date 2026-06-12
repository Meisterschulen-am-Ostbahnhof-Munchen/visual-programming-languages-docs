# AUI_D_FF_TMIN


![AUI_D_FF_TMIN](./AUI_D_FF_TMIN.svg)

* * * * * * * * * * *
## Einleitung

Der Funktionsblock **AUI_D_FF_TMIN** realisiert ein datenverriegelndes D-Flipflop (Data Latch) mit einer minimalen zeitlichen Sperre zwischen zwei aufeinanderfolgenden Ausgabeereignissen (*Minimum inter‑disposal Time*). Er dient dazu, Werte über den unidirektionalen **AUI**‑Adapter zu übernehmen und mit einer definierten Mindestverzögerung weiterzugeben, um eine übermäßig schnelle Ereignisfolge am Ausgang zu vermeiden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Kommentar |
|----------|-----------|
| **INIT** | Initialisierungsanforderung; konfiguriert den Block mit dem Parameter `Tmin`. |

### **Ereignis-Ausgänge**

| Ereignis | Kommentar |
|----------|-----------|
| **INITO** | Bestätigung der erfolgreichen Initialisierung. |

### **Daten-Eingänge**

| Variable | Typ   | Kommentar |
|----------|-------|-----------|
| **Tmin** | TIME | Minimale Zeitdauer, die zwischen zwei Ausgabeereignissen (`EO`) mindestens verstreichen muss. |

### **Daten-Ausgänge**

*Keine direkten Datenausgänge – die Ausgabewerte werden über den Adapter `Q` bereitgestellt.*

### **Adapter**

| Richtung | Name | Typ | Kommentar |
|----------|------|-----|-----------|
| **Plug** (Ausgang) | **Q** | `adapter::types::unidirectional::AUI` | Liefert den verriegelten Datenwert (Ereignis‑ und Datenleitung). |
| **Socket** (Eingang) | **I** | `adapter::types::unidirectional::AUI` | Empfängt den zu verriegelnden Datenwert (Ereignis‑ und Datenleitung). |

## Funktionsweise

1. **Initialisierung**  
   Über den Ereigniseingang `INIT` wird der Block initialisiert und die Mindestzeit `Tmin` festgelegt.

2. **Datenübernahme**  
   Jedes Ereignis, das am Adaptereingang `I` über die Ereignisleitung `I.E1` eintrifft, übernimmt den zugehörigen Datenwert `I.D1` in das Flipflop. Der übernommene Wert wird sofort intern gespeichert.

3. **Ausgabe mit Mindestzeit**  
   Die Ausgabe des gespeicherten Werts erfolgt erst dann als Ereignis auf `Q.E1` und Datenwert auf `Q.D1`, wenn seit dem letzten Ausgabeereignis mindestens die Zeit `Tmin` vergangen ist. Tritt vor Ablauf dieser Frist ein neues Übernahmeereignis ein, so wird der neue Wert gespeichert und die Ausgabe weiter verzögert, bis die Mindestzeit eingehalten ist.

4. **Zustandssicherung**  
   Der Block verhält sich wie ein flankengetriggertes D‑Flipflop, bei dem jeder gültige Takt (Ereignis auf `I.E1`) den aktuellen Datenwert übernimmt, die tatsächliche Weitergabe jedoch zeitlich gedrosselt ist.

## Technische Besonderheiten

- **Adapterbasierte Ein‑/Ausgabe** – Der Baustein verwendet ausschließlich den standardisierten unidirektionalen **AUI**‑Adapter. Dadurch ist er leicht in bestehende Adapter‑orientierte Architekturen integrierbar.
- **Wiederverwendung von Basis‑Bausteinen** – Intern wird der IEC‑61499‑Baustein `E_D_FF_ANY_TMIN` eingesetzt, der die zeitliche Drosselung implementiert. Der vorliegende Block kapselt diesen und vereinfacht die Anbindung über Adapter.
- **Keine eigenen Zustandsautomaten** – Das Verhalten wird vollständig durch den inneren Baustein bestimmt; der äußere FB ist rein konfigurativ und verbindend.

## Zustandsübersicht

Der Funktionsblock besitzt keinen extern sichtbaren Zustandsautomaten (ECC). Intern kann der verwendete `E_D_FF_ANY_TMIN` folgende implizite Zustände aufweisen:

| Zustand | Beschreibung |
|---------|--------------|
| **Idle** | Wartet auf ein Ereignis am Eingang `I`. |
| **Getaktet** | Daten wurden übernommen; Ausgabe wird bis zum Ablauf von `Tmin` zurückgehalten. |
| **Ausgabe** | Mindestzeit eingehalten – Ausgabeereignis wird gesendet. |

Diese Zustände sind für den Anwender transparent.

## Anwendungsszenarien

- **Sensorwert‑Glättung** – Verhindert, dass ein Sensor, der in kurzen Abständen Messwerte liefert, den nachfolgenden Verarbeitungsblock mit Ereignissen überflutet.
- **Aktor‑Ansteuerung mit Mindestschaltzeit** – Stellt sicher, dass ein Aktor (z. B. ein Ventil) nur nach einer definierten Mindestpause geschaltet werden kann, um Verschleiß zu reduzieren.
- **Datenflussbegrenzung in Kommunikationsleitungen** – Drosselt die Ausgaberate eines Datenstroms, um eine Überlastung des Empfängers zu vermeiden.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Merkmal |
|----------|---------|
| **E_D_FF** (Standard‑D‑Flipflop) | Keine Zeitbeschränkung; jedes Ereignis wird sofort ausgegeben. |
| **E_D_FF_ANY_TMIN** | Gleiches Verhalten, jedoch ohne Adapter‑Kapselung; direkte ereignis‑/datenbasierte Anbindung. |
| **AUI_D_FF_TMIN** (dieser Block) | Kombiniert die D‑Flipflop‑Funktionalität mit einer zeitlichen Drosselung und bietet eine adapterbasierte Schnittstelle. |

## Fazit

Der **AUI_D_FF_TMIN** ist ein nützlicher Funktionsblock, wenn Daten in zeitlich kontrollierten Abständen weitergegeben werden sollen. Er vereinfacht die Implementierung von Drosselungslogiken in adapterbasierten IEC‑61499‑Systemen und eignet sich besonders für Anwendungen in der Landtechnik und anderen zeitkritischen Steuerungsumgebungen.