# IA_VDS


![IA_VDS](./IA_VDS.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **IA_VDS** ist ein ISOBUS-Adapter für die Fahrzeugrichtung und -geschwindigkeit (Vehicle Direction/Speed) gemäß ISO 11783-7 (PGN 65256). Er kapselt den Zugriff auf die entsprechenden CAN-Bus-Daten und stellt sie als zeitgemäße 4diac‑Adapter-Schnittstellen zur Verfügung. Der Baustein wird über ein INIT-Ereignis initialisiert und liefert anschließend kontinuierlich Navigationsgeschwindigkeit, Kompassrichtung, Höhe sowie einen Timeout-Status.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ   | Beschreibung |
|----------|-------|--------------|
| INIT     | EInit | Initialisiert den Baustein. Erwartet den Qualifier QI. |

### **Ereignis-Ausgänge**

| Ereignis | Typ   | Beschreibung |
|----------|-------|--------------|
| INITO    | EInit | Bestätigt die erfolgreiche Initialisierung. Liefert QO und STATUS. |

### **Daten-Eingänge**

| Name | Typ    | Beschreibung |
|------|--------|--------------|
| QI   | BOOL   | Event‑Input Qualifier (TRUE = Initialisierung aktiv). |

### **Daten-Ausgänge**

| Name   | Typ    | Beschreibung |
|--------|--------|--------------|
| QO     | BOOL   | Event‑Output Qualifier (TRUE = Initialisierung ok). |
| STATUS | STRING | Meldungstext (z. B. Fehlerbeschreibung oder “Ready”). |

### **Adapter**

| Adapter      | Typ  | Beschreibung |
|--------------|------|--------------|
| NAV_SPEED    | AUI  | Navigationsbasierte Fahrzeuggeschwindigkeit (unidirektional, Empfänger). |
| BEARING      | AUI  | Kompassrichtung (unidirektional, Empfänger). |
| ALTITUDE     | AUI  | Höhe über dem Meeresspiegel (unidirektional, Empfänger). |
| TIMEOUT      | AX   | Timeout‑Status (unidirektional, Empfänger). |

Alle Adapter sind als Plugs (out‑going) realisiert – der IA_VDS sendet die Daten an die angeschlossenen Senken.

## Funktionsweise

Der Baustein enthält intern einen weiteren Funktionsblock **I_VDS** (aus der Bibliothek `isobus::tecu`), der die eigentliche ISOBUS‑Kommunikation abwickelt. Beim Eintreffen des INIT‑Ereignisses wird die Initialisierung von I_VDS angestoßen. Nach erfolgreicher Initialisierung meldet I_VDS dies über sein INITO‑Ereignis, welches an den INITO‑Ausgang des IA_VDS weitergeleitet wird. Zeitgleich beginnt I_VDS, zyklisch die Werte für NavigationBasedVehicleSpeed, CompassBearing und Altitude zu aktualisieren. Diese werden über die zugehörigen Adapter (NAV_SPEED, BEARING, ALTITUDE) ausgegeben, sobald das Ereignis IND von I_VDS eintrifft. Tritt ein Timeout auf (z. B. CAN‑Bus‑Fehler), wird dies über den Adapter TIMEOUT gemeldet.

## Technische Besonderheiten

- Der Baustein setzt auf dem **Eclipse Public License 2.0 (EPL‑2.0)** auf und ist als ISOBUS‑Adapter für PGN 65256 konzipiert.
- Die Daten werden asynchron über eigene Ereignisse (IND) an die Adapter‑Ausgänge verteilt, was eine entkoppelte Verarbeitung in der 4diac‑Umgebung ermöglicht.
- Der interne Block I_VDS ist in der Bibliothek `isobus::tecu` implementiert und für den direkten Buszugriff optimiert.
- Der Timeout‑Status wird mit einem eigenen Adapter (Typ AX) bereitgestellt, um Fehlerbehandlung klar vom normalen Datenstrom zu trennen.

## Zustandsübersicht

Der IA_VDS besitzt keinen expliziten Zustandsautomaten, sein Verhalten wird durch den internen I_VDS bestimmt:

1. **Initial** – Noch kein INIT empfangen.
2. **Initialisierung läuft** – Nach INIT, solange I_VDS noch nicht bereit.
3. **Aktiv** – Nach erfolgreicher Initialisierung (INITO = TRUE). Werte werden regelmäßig aktualisiert.
4. **Fehler** – Bei Timeout oder ungültigen Busdaten (STATUS enthält Fehlermeldung, QO = FALSE).

## Anwendungsszenarien

- **Landmaschinensteuerung** – Integration von Fahrgeschwindigkeit, Fahrtrichtung und Höhe in Steuerungslogiken (z. B. für teilflächenspezifische Applikation).
- **ISOBUS‑Netzwerkanbindung** – Als Adapter in 4diac‑Applikationen, die ISOBUS‑Daten von einem Traktor oder Erntefahrzeug nutzen.
- **Telemetrie‑Systeme** – Weiterleitung der VDS‑Daten an übergeordnete Systeme (Cloud, Display).

## Vergleich mit ähnlichen Bausteinen

- **I_TC** (ISOBUS Traktorsteuerung) – Liefert allgemeine Traktordaten (Geschwindigkeit, Zapfwellendrehzahl, Hubwerk) über ähnliche Adapter, aber nicht spezifisch die VDS‑PGN.
- **I_GNSS** (ISOBUS GNSS‑Adapter) – Stellt GPS‑basierte Positionsdaten bereit, jedoch ohne Fokus auf Richtung/Geschwindigkeit über CAN.
- **IA_VDS** ist auf die reine Fahrzeugrichtungs‑/Geschwindigkeitsinformation (PGN 65256) spezialisiert und besonders schlank in der Schnittstelle.

## Fazit

Der **IA_VDS** ist ein praktischer Baustein, um die ISO‑11783‑7‑spezifischen Fahrzeugdaten (Richtung/Geschwindigkeit) einfach in eine 4diac‑Applikation einzubinden. Durch die adapterbasierte Ausgabe bleibt die Architektur modular und erweiterbar. Die Unterteilung in Daten‑ und Timeout‑Adapter erleichtert die robuste Fehlerbehandlung. Ideal für alle Anwendungen, die eine präzise, busbasierte Fahrzeugdynamik benötigen.