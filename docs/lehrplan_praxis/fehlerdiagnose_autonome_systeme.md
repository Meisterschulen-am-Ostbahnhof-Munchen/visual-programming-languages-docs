# 🔍 Fehlerdiagnose in automatisierten & autonomen Systemen

> 📌 **Quellennachweis & Rechtsgrundlage:**  
> **Quelle:** *Rahmenlehrplan für die Vorbereitung auf die Meisterprüfung im Land- und Baumaschinenmechatroniker-Handwerk*  
> **Herausgeber:** LandBauTechnik-Bundesverband e. V., Alfredstraße 102, 45131 Essen (Stand: 25.02.2025)  
> **Verordnung:** *Meisterprüfungsverordnung (LandBauMechMstrV)* vom 09.09.2024 (BGBl. 2024 I Nr. 277, in Kraft ab 01.08.2025)

---


**Rahmenlehrplan-Kategorie:** Teil I LE 2.6 (20 UE) | Teil II LE 1.3 (100 UStd.)  
**Kernbereich:** Systematische Fehlersuche in visuellen Steuerungsarchitekturen.

---

## 1. Online-Debugging & Signalbeobachtung (Watchpoints)

### Diagnosestrategie im 4diac IDE
- **Monitoring-Modus:** Aufschaltung der Entwicklungsumgebung auf die laufende Runtime (FORTE / ESP32).
- **Visualisierung des Signalflusses:** Farbige Markierung aktiver Event-Pfade und Echzeit-Anzeige aller Daten-Variablen.
- **Setzen von Watchpoints:** Überwachung kritischer Zustände (z. B. Not-Halt-Auslösung, LiDAR-Hinderniserkennung).

---

## 2. Zustandsmaschinen (Execution Control Chart - ECC) Analyse

### Fehlersuche in ECCs
- **Zustandsüberprüfungen:** Steckt der Automat in einem unvollständigen Übergang (Transition) fest?
- **Bedingungsprüfung:** Überprüfung von logischen Bedingungen (z. B. `Sensor_OK AND Safety_Interlock`).
- **Fehlerprotokollierung:** Auswertung von Diagnose-Events und Senden von Fehler-PGNs über den CAN-Bus.
