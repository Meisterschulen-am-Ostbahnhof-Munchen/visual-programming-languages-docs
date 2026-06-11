# IA_COGSOGRapidUpdate


![IA_COGSOGRapidUpdate](./IA_COGSOGRapidUpdate.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **IA_COGSOGRapidUpdate** dient als ISOBUS-Adapter für die NMEA 2000 PGN 129026 Messages „Course Over Ground (COG)“ und „Speed Over Ground (SOG)“ mit Unterstützung für schnelle Aktualisierungen (Rapid Update). Er entkoppelt die ISOBUS-Kommunikation und stellt die empfangenen Navigationsdaten sowie einen Timeout-Status über standardisierte Adapter-Schnittstellen bereit. Der Baustein wurde auf Basis der Eclipse Public License 2.0 entwickelt und ist für den Einsatz in landwirtschaftlichen Steuerungssystemen (TECU) optimiert.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Ereignis | Typ | Kommentar |
|----------|-----|-----------|
| INIT | EInit | Service-Initialisierung, ausgelöst durch Eingang QI |

### **Ereignis-Ausgänge**
| Ereignis | Typ | Kommentar |
|----------|-----|-----------|
| INITO | EInit | Initialisierungsbestätigung, liefert QO und STATUS |

### **Daten-Eingänge**
| Variable | Typ | Kommentar |
|----------|-----|-----------|
| QI | BOOL | Eingangsqualifikator für die Initialisierung |

### **Daten-Ausgänge**
| Variable | Typ | Kommentar |
|----------|-----|-----------|
| QO | BOOL | Ausgangsqualifikator (Initialisierungsstatus) |
| STATUS | STRING | Statusmeldung (z. B. Fehlertext oder „OK“) |

### **Adapter**
| Adapter-Name | Typ | Kommentar |
|--------------|-----|-----------|
| COG | adapter::types::unidirectional::AUI | Kurs über Grund (Course Over Ground) |
| SOG | adapter::types::unidirectional::AUI | Geschwindigkeit über Grund (Speed Over Ground) |
| TIMEOUT | adapter::types::unidirectional::AX | Timeout-Status (aktiv bei fehlender Aktualisierung) |
| SID | adapter::types::unidirectional::AUS | Sequenz-ID (lfd. Nummer des Datensatzes) |
| COG_REF | adapter::types::unidirectional::AB | Referenz für den Kurs (z. B. True/Magnetic) |

## Funktionsweise
1. **Initialisierung**  
   Durch ein Ereignis an **INIT** wird der Baustein aktiviert. Der Eingang **QI** steuert den Start. Nach erfolgreicher Initialisierung wird **INITO** ausgelöst und die Ausgänge **QO** (TRUE bei Erfolg) und **STATUS** gesetzt.

2. **ISOBUS-Nachrichtenverarbeitung**  
   Der interne Kern (FB `I_CORE` vom Typ `isobus::tecu::I_COGSOGRapidUpdate`) empfängt kontinuierlich die NMEA 2000 PGN 129026-Nachrichten. Sobald neue Daten vorliegen, werden folgende Werte über die entsprechenden Adapter ausgegeben:
   - **COG**: Kurs über Grund (z. B. in 0,01°-Schritten)
   - **SOG**: Geschwindigkeit über Grund (z. B. in 0,01 km/h)
   - **SID**: Sequenz-ID zur Synchronisation
   - **COG_REF**: Referenz (True oder Magnetic)

3. **Timeout-Überwachung**  
   Falls innerhalb einer konfigurierten Zeitspanne keine gültige Nachricht empfangen wird, setzt der Baustein den **TIMEOUT**-Adapter auf aktiv. Dieses Ereignis kann von der Anwendung genutzt werden, um Fehlerzustände oder Plausibilitätsprüfungen auszulösen.

4. **Ausgabezyklen**  
   Die Adapter **COG**, **SOG**, **SID** und **COG_REF** werden bei jedem gültigen Daten-Empfang gemeinsam getriggert (Ereignisverbindung `IND`). Der **TIMEOUT**-Adapter wird unabhängig davon bei Timeout ausgelöst.

## Technische Besonderheiten
- **NMEA 2000 PGN 129026** – Der Baustein ist speziell für die Interpretation dieser PGN ausgelegt, die rapide Aktualisierungen von COG und SOG ermöglicht.
- **Adapter statt direkter Ein-/Ausgänge** – Alle Navigationsdaten werden über unidirektionale Adapter (Typ `unidirectional::AUI`, `AX` etc.) bereitgestellt, was eine flexible Weiterverarbeitung und Kapselung in übergeordneten Netzwerken erlaubt.
- **Lizenz und Herkunft** – Der Baustein ist unter der Eclipse Public License 2.0 verfügbar und wurde von **HR Agrartechnik GmbH** entwickelt (Version 1.0, 19.04.2026, Autor: Franz Höpfinger).
- **Integration in isobus::tecu** – Der FB ist Bestandteil der Bibliothek `isobus::tecu` und setzt auf einer hardwarenahen ISOBUS-Implementierung auf.

## Zustandsübersicht
Der Funktionsblock besitzt keine explizit modellierten Zustände, dennoch lassen sich folgende Betriebsphasen ableiten:

| Zustand | Beschreibung |
|---------|--------------|
| **Inaktiv** | INIT noch nicht ausgelöst oder QI = FALSE |
| **Initialisierend** | Nach INIT, bis INITO mit QO gemeldet wird |
| **Aktiv (Daten empfangen)** | Regelmäßiger Empfang von PGN 129026, Aktualisierung der Adapter |
| **Timeout** | Keine gültige Nachricht innerhalb der Timeout-Schwelle – TIMEOUT-Adapter aktiv |
| **Fehler** | Initialisierung fehlgeschlagen (STATUS = Fehlertext) |

## Anwendungsszenarien
- **Landwirtschaftliche Zugmaschinen** – Bereitstellung von Kurs- und Geschwindigkeitsdaten für automatische Lenksysteme oder Applikationskarten.
- **ISOBUS-basierte Steuergeräte** – Einbindung in ein TECU-Netzwerk zur Auswertung von GPS/GNSS-Daten.
- **Schnelle Regelkreise** – Nutzung der Rapid-Update-Funktion für dynamische Führungsgrößen (z. B. bei teilflächenspezifischer Behandlung).
- **Fehlerüberwachung** – Einsatz des TIMEOUT-Adapters zur Erkennung von Datenausfällen und zur Aktivierung von Redundanzmechanismen.

## Vergleich mit ähnlichen Bausteinen
Es gibt allgemeine ISOBUS-Adapter für COG/SOG (z. B. `I_COGSOG`), die jedoch keine Rapid-Update-Unterstützung bieten. Der **IA_COGSOGRapidUpdate** ist speziell auf PGN 129026 ausgelegt und stellt zusätzlich die Sequenz-ID sowie den Timeout-Status bereit. Ähnliche Bausteine wie `I_COGSOGStd` verwenden möglicherweise eine langsamere Aktualisierungsrate oder fehlende Timeout-Erkennung. Die Verwendung von Adapter-Schnittstellen (statt fester Datenport) erhöht die Flexibilität, erfordert aber eine entsprechende Adapter-Konfiguration im übergeordneten Projekt.

## Fazit
Der **IA_COGSOGRapidUpdate** ist ein spezialisierter, lizenzrechtlich freier ISOBUS-Adapter für hochfrequente Navigationsdaten. Er kapselt die komplexe NMEA-2000-Kommunikation und bietet standardisierte Adapterausgänge für Kurs, Geschwindigkeit, Sequenz-ID und Timeout. Durch seine klare Initialisierungslogik und die Möglichkeit zur Fehlerüberwachung eignet er sich ideal für Echtzeit-Anwendungen in der Agrartechnik. Die Nutzung der Adapter-Technologie ermöglicht eine saubere Modularisierung und Wiederverwendbarkeit in unterschiedlichsten Steuerungsarchitekturen.