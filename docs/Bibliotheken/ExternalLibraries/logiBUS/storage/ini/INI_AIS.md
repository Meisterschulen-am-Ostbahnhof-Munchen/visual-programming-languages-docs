# INI_AIS


![INI_AIS](./INI_AIS.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **INI_AIS** dient zum Laden und Speichern von Zeichenketten (STRING) aus einer `settings.ini`-Datei. Dabei wird über einen Abschnittsnamen (Section) und einen Schlüssel (Key) auf den gewünschten Wert zugegriffen. Die Schnittstelle ist über unidirektionale AIS-Adapter realisiert, sodass der Baustein sowohl Werte lesen als auch schreiben kann.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name  | Typ    | Beschreibung                         |
|-------|--------|--------------------------------------|
| INIT  | EInit  | Service-Initialisierung              |

### **Ereignis-Ausgänge**

| Name  | Typ    | Beschreibung                         |
|-------|--------|--------------------------------------|
| INITO | EInit  | Bestätigung der Initialisierung      |

### **Daten-Eingänge**

| Name          | Typ    | Beschreibung                                              |
|---------------|--------|-----------------------------------------------------------|
| QI            | BOOL   | Qualifikator für den Ereigniseingang                       |
| SECTION       | STRING | Name des Abschnitts in der Konfigurationsdatei             |
| KEY           | STRING | Name des Schlüssels im angegebenen Abschnitt              |
| DEFAULT_VALUE | STRING | Standardwert, falls der Eintrag nicht existiert            |

### **Daten-Ausgänge**

| Name   | Typ    | Beschreibung                         |
|--------|--------|--------------------------------------|
| QO     | BOOL   | Qualifikator für den Ereignisausgang  |
| STATUS | STRING | Statusmeldung (z. B. Fehlertext)      |

### **Adapter**

| Name    | Typ                          | Richtung  | Beschreibung                                        |
|---------|------------------------------|-----------|-----------------------------------------------------|
| AIS_OUT | adapter::types::unidirectional::AIS | Plug      | Ausgang für den gelesenen Wert (GETO)               |
| AIS_IN  | adapter::types::unidirectional::AIS | Socket    | Eingang für den zu speichernden Wert (SET)          |

## Funktionsweise

Der Baustein enthält intern eine Instanz des Funktionsblocks `INI` (aus der Bibliothek `eclipse4diac::storage`). Die Abläufe sind wie folgt:

1. **Initialisierung (INIT)**  
   - Die Daten `QI`, `SECTION`, `KEY` und `DEFAULT_VALUE` werden an den internen INI-Baustein weitergeleitet.
   - Der INIT-Ereignisimpuls startet den INI-Baustein.
   - Nach Abschluss liefert INI das Ereignis `INITO` zurück, das nach außen als `INITO` des INI_AIS ausgegeben wird. Gleichzeitig werden die Ausgänge `QO` und `STATUS` übernommen.
   - Unmittelbar nach der Initialisierung wird im INI-Baustein automatisch der `GET`-Dienst ausgelöst, um den Wert aus der `settings.ini` zu lesen.

2. **Lesen eines Wertes (über AIS_OUT)**  
   - Der gelesene Wert erscheint am Datenausgang `VALUEO` des INI-Bausteins und wird auf den Datenausgang `D1` des Adapter-Plugs `AIS_OUT` gelegt.
   - Das Ereignis `GETO` des INI-Bausteins wird auf den Ereigniseingang `E1` von `AIS_OUT` übertragen, sodass der empfangende Baustein den Wert abholen kann.

3. **Schreiben eines Wertes (über AIS_IN)**  
   - Ein externer Baustein kann über den Adapter-Socket `AIS_IN` einen Wert (Ereignis `E1` mit Daten `D1`) an den INI_AIS senden.
   - Dieses Ereignis triggert den `SET`-Dienst des internen INI-Bausteins. Der ankommende Wert wird an den Dateneingang `VALUE` von INI übergeben.
   - Nach erfolgreichem Schreiben sendet INI das Ereignis `SETO`, welches an den Ereignisausgang `E1` von `AIS_OUT` weitergeleitet wird. Der geschriebene Wert wird gleichzeitig auch über `VALUEO` zurückgegeben, sodass der schreibende Baustein den Wert bestätigt bekommt.

## Technische Besonderheiten

- **Interne Vernetzung:** Der Baustein nutzt den bereits existierenden `INI`-Baustein und kapselt dessen komplexe Schnittstelle in einer einfacheren, adapterbasierten Form.
- **Unidirektionale AIS-Adapter:** Der Datenaustausch erfolgt über AIS-Schnittstellen, die eine lose Kopplung zwischen den Bausteinen ermöglichen. Der `AIS_IN`-Socket ist für das Empfangen von Schreibaufträgen, der `AIS_OUT`-Plug für das Senden von Leseergebnissen zuständig.
- **Automatischer Lesezugriff:** Nach der Initialisierung wird sofort der gespeicherte Wert gelesen und über den Ausgang bereitgestellt – ohne separate GET-Anforderung.
- **Fehlerbehandlung:** Statusmeldungen werden über den `STATUS`-Ausgang kommuniziert (z. B. Datei nicht gefunden, Abschnitt/Schlüssel nicht vorhanden).

## Zustandsübersicht

Der Baustein besitzt keine explizit programmierten Zustände. Der interne INI-Baustein übernimmt die Zustandsverwaltung. Aus Sicht des Benutzers ergeben sich folgende Betriebsphasen:

- **Initialisiert (nach INIT – INITO):** Der Baustein ist bereit, Werte zu lesen und zu schreiben. Der Wert des angegebenen Schlüssels wurde bereits einmal gelesen und steht am `AIS_OUT`-Ausgang zur Verfügung.
- **Schreibvorgang (über AIS_IN):** Ein externer Befehl löst einen Schreibzugriff aus. Nach Abschluss ist der neue Wert über `AIS_OUT` abrufbar.
- **Lesezugriff:** Erfolgt implizit nach jedem INIT und wird nicht explizit gesteuert.

## Anwendungsszenarien

- **Persistente Konfigurationsdaten:** Speichern von Parametern wie Geräteadressen, Grenzwerten oder Betriebsmodi in einer INI-Datei.
- **Plug-and-Play-fähige Module:** Module, die über den AIS-Adapter ihre Konfiguration lesen und bei Bedarf überschreiben – ohne feste Verkabelung der Datenpfade.
- **Initialisierungswerte:** Auslesen von Standardwerten beim Systemstart, die über die `settings.ini`-Datei angepasst werden können.

## Vergleich mit ähnlichen Bausteinen

| Baustein      | Beschreibung                                                                 |
|---------------|-------------------------------------------------------------------------------|
| INI           | Direkter Zugriff auf INI-Dateien mit separaten Ereignissen für GET und SET.   |
| **INI_AIS**   | Erweitert INI um eine adapterbasierte Schnittstelle, die das Koppeln anderer Bausteine vereinfacht und die Handhabung von Lese- und Schreiboperationen integriert. |

- Im Gegensatz zum bloßen `INI`-Baustein bietet INI_AIS eine einheitliche, ereignisorientierte Schnittstelle für lesende und schreibende Komponenten.
- Die Verwendung von Adaptern ermöglicht eine flexible Verbindung in größeren Automatisierungsnetzwerken, ohne dass die Datenleitungen einzeln verdrahtet werden müssen.

## Fazit

Der **INI_AIS**-Funktionsblock ist eine praktische Erweiterung des Basis-`INI`-Bausteins, der die Nutzung von Konfigurationsdateien in Automatisierungsprojekten deutlich vereinfacht. Durch die Integration von Lese- und Schreibvorgängen in einer einzigen Adapter-Schnittstelle wird der Systementwurf modularer und klarer. Der Baustein eignet sich besonders für Szenarien, in denen mehrere Komponenten auf denselben Datenspeicher zugreifen müssen.