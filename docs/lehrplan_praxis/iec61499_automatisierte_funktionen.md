# ⚡ Automatisierte Funktionen mit IEC 61499

> 📌 **Quellennachweis & Rechtsgrundlage:**  
> **Quelle:** *Rahmenlehrplan für die Vorbereitung auf die Meisterprüfung im Land- und Baumaschinenmechatroniker-Handwerk*  
> **Herausgeber:** LandBauTechnik-Bundesverband e. V., Alfredstraße 102, 45131 Essen (Stand: 25.02.2025)  
> **Verordnung:** *Meisterprüfungsverordnung (LandBauMechMstrV)* vom 09.09.2024 (BGBl. 2024 I Nr. 277, in Kraft ab 01.08.2025)

---


**Rahmenlehrplan-Kategorie:** Teil I LE 1.4 (40 UE) | Teil II LE 1.1 (160 UStd.)  
**Kernbereich:** Grafische Funktionsentwicklung für vernetzte mechatronische Systeme.

---

## 1. Ereignisgesteuerte Architektur (Events & Data)

### Unterschied zu klassischen PLC-Sprachen (IEC 61131-3)
- **Klassisch (Zyklisch):** Das Programm wird ständig in einer festen Schleife abgearbeitet.
- **IEC 61499 (Ereignisgesteuert):** Die Ausführung eines Funktionsbausteins (FB) wird ausschließlich durch explizite **Events** getriggert. Dies reduziert die Bus- und Prozessorlast drastisch und ermöglicht erst echte Verteilbarkeit.

### Struktur eines IEC 61499 Funktionsbausteins
- **Event-Eingänge (`INIT`, `REQ`):** Starten die interne Verarbeitung.
- **Event-Ausgänge (`INITO`, `CNF`):** Signalisiert den Abschluss einer Verarbeitung an nachgelagerte Bausteine.
- **Daten-Eingänge & -Ausgänge (`WITH`-Verknüpfung):** Kopplung von Ereignissen an Datenwerte (z. B. Sensorwerte, Sollwerte).

---

## 2. Praktische Umsetzung im Meisterprüfungsprojekt

### Anwendungsbeispiel: Automatische Ventilstellung & Hubwerksregelung
1. **Sensor-Baustein:** Erfasst den aktuellen Druck ($p$) und Position ($s$).
2. **Regler-Baustein (PID / Hysterese):** Grafisch im 4diac IDE verbunden.
3. **Aktor-Baustein (PWM / CAN-Output):** Steuert das Proportionalventil an.
4. **Visualisierung (ISOBUS VT / ISO-Designer):** Ereignisse und Werte werden direkt an die VT-Objekte übergeben.
