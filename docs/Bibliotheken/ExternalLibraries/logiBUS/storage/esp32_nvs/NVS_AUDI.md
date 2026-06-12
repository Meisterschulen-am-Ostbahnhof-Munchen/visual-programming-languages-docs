# NVS_AUDI


![NVS_AUDI](./NVS_AUDI.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **NVS_AUDI** ermöglicht das Speichern und Laden von **UDINT**-Daten im **Non-Volatile Storage (NVS)** eines ESP32-Mikrocontrollers. Die Daten werden über einen eindeutigen **Schlüssel (KEY)** adressiert. Der Baustein verwendet ein **unidirektionales AUDI-Adapter-Interface** zur Kommunikation mit dem NVS: Über einen Eingangsadapter (Socket) wird der zu speichernde Wert empfangen, über einen Ausgangsadapter (Plug) wird der gelesene Wert bereitgestellt.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Name  | Typ   | Mitgeführte Daten         | Kommentar                     |
|-------|-------|---------------------------|-------------------------------|
| INIT  | EInit | QI, KEY, DEFAULT_VALUE    | Initialisiert den Dienst      |

### **Ereignis-Ausgänge**

| Name  | Typ   | Mitgeführte Daten | Kommentar                        |
|-------|-------|-------------------|----------------------------------|
| INITO | EInit | QO, STATUS        | Bestätigung der Initialisierung  |

### **Daten-Eingänge**

| Name          | Typ    | Kommentar                                        |
|---------------|--------|--------------------------------------------------|
| QI            | BOOL   | Ereignis-Eingangs-Qualifikator                   |
| KEY           | STRING | Schlüsselname für den NVS-Zugriff                |
| DEFAULT_VALUE | UDINT  | Standardwert, falls kein Wert im NVS vorhanden   |

### **Daten-Ausgänge**

| Name   | Typ    | Kommentar                    |
|--------|--------|------------------------------|
| QO     | BOOL   | Ereignis-Ausgangs-Qualifikator |
| STATUS | STRING | Dienststatus (Fehler/Ok)     |

### **Adapter**

| Name     | Typ                                 | Kommentar                          |
|----------|--------------------------------------|------------------------------------|
| AUDI_IN  | adapter::types::unidirectional::AUDI | Wert zum Speichern (SET)           |
| AUDI_OUT | adapter::types::unidirectional::AUDI | Gespeicherter/geladener Wert (GETO)|

## Funktionsweise
Beim Eintreffen des **INIT**-Ereignisses wird der interne NVS-Baustein initialisiert (übergeben werden QI, KEY und DEFAULT_VALUE). Nach erfolgreicher Initialisierung feuert **INITO** und gleichzeitig wird ein **GET**-Auftrag an den NVS gesendet, um den gespeicherten Wert zu laden. Das Ergebnis des GET-Vorgangs wird über **AUDI_OUT** bereitgestellt (Daten auf D1, Ereignis auf E1).

Wird über den **AUDI_IN**-Adapter ein Ereignis (E1) mit einem Wert (D1) empfangen, so wird ein **SET**-Auftrag an den NVS gesendet, um den Wert unter dem aktuellen KEY zu speichern. Nach dem Speichern feuert **SETO** und das Ergebnis wird ebenfalls über **AUDI_OUT** quittiert.

Sowohl nach dem Laden als auch nach dem Speichern wird der Status (QO, STATUS) über die Ausgänge aktualisiert.

## Technische Besonderheiten
- Der Baustein nutzt den **unidirektionalen AUDI-Adapter**, der eine einfache, stream-basierte Datenübergabe erlaubt: Ein Wert wird gesendet (SET) und ein Wert wird empfangen (GETO).
- Intern wird der FB `logiBUS::storage::esp32_nvs::NVS` verwendet, der die eigentliche NVS-Operation auf dem ESP32 ausführt.
- Der Standard-Datentyp ist **UDINT** (unsigned 32‑Bit).
- Es werden keine zusätzlichen Zustände oder Zeitgeber benötigt; der FB arbeitet rein ereignisgesteuert.
- Das Attribut **TypeHash** ist mit einem leeren String belegt – es kann für Integritätsprüfungen verwendet werden.

## Zustandsübersicht
Da im XML keine explizite Zustandsmaschine definiert ist, ergibt sich der Ablauf aus den Ereignissen:

1. **Initialisierungsphase** – INIT empfangen → NVS-INIT → NVS-GET ausgelöst.  
   Danach: Bereit (wartet auf SET oder erneuten GET durch erneutes INIT).
2. **Speicherphase** – Ereignis über AUDI_IN (E1) → NVS-SET → Wert wird geschrieben.
3. **Lesevorgang** – Automatisch nach INIT oder durch erneutes INIT.

Die Ausgabe über AUDI_OUT erfolgt nach jedem Lese- oder Schreibvorgang.

## Anwendungsszenarien
- Speichern von **Konfigurationsparametern** (z. B. Grenzwerte, Betriebsmodi) im NVS, die auch nach Netzausfall erhalten bleiben.
- **Zählerstände** oder **Kalibrierdaten** in industriellen Steuerungen auf ESP32-Basis.
- **Persistente Zustände** von Automatisierungsprozessen, die über einen Schlüssel eindeutig identifiziert werden.
- Austausch von Daten zwischen verschiedenen FBs über den AUDI-Adapter, ohne direkt auf den NVS zuzugreifen.

## Vergleich mit ähnlichen Bausteinen
- **NVS (ohne Adapter)**: Bietet direkten Zugriff auf NVS über einzelne Ereignisse und Datenports, benötigt aber mehr Verdrahtungsaufwand.
- **NVS_AUDI** kapselt die NVS-Operationen hinter einem standardisierten Adapter-Interface. Dadurch wird der Baustein leichter austauschbar und die Datenübergabe vereinheitlicht (z. B. mit anderen Speicherbausteinen, die ebenfalls AUDI-Adapter verwenden).
- Andere Speicherbausteine (z. B. **Retain**, **SD‑Card**) unterscheiden sich in der Hardware-Anbindung und Latenz; NVS ist speziell für den ESP32 optimiert.

## Fazit
Der **NVS_AUDI**-Funktionsblock stellt eine elegante Lösung zur persistenten Speicherung von UDINT-Daten auf dem ESP32 dar. Durch die Integration des AUDI-Adapter-Interfaces wird die Anbindung an andere Bausteine vereinfacht und der Code klarer strukturiert. Er eignet sich besonders für Anwendungen, die einen standardisierten Datenaustausch zwischen Speicher- und Verarbeitungskomponenten erfordern.