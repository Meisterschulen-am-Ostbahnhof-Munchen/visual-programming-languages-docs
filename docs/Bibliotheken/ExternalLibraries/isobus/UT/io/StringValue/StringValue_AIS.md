# StringValue_AIS


![StringValue_AIS](./StringValue_AIS.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **StringValue_AIS** ist ein Dienstschnittstellen-Baustein (Service Interface Function Block) zur Bereitstellung von Zeichenketten-Eingabedaten (String). Er dient als Schnittstelle zwischen einer externen Ressource (z. B. ISOBUS Universal Terminal) und der Steuerungslogik. Der Baustein initialisiert die Kommunikation, verarbeitet Anforderungen und gibt Statusinformationen an die Applikation weiter.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Ereignis | Typ | Mit Variablen | Beschreibung |
|----------|-----|---------------|--------------|
| INIT | EInit | QI, PARAMS, u16ObjId | Initialisiert den Dienst und übergibt Qualifier, Parameter und Objekt-ID. |
| REQ | Event | QI | Fordert eine Datenabfrage oder -verarbeitung an. |

### **Ereignis-Ausgänge**
| Ereignis | Typ | Mit Variablen | Beschreibung |
|----------|-----|---------------|--------------|
| INITO | EInit | QO, STATUS | Bestätigt die Initialisierung und liefert Statusinformationen. |

### **Daten-Eingänge**
| Variable | Typ | Initialwert | Beschreibung |
|----------|-----|-------------|--------------|
| QI | BOOL | – | Qualifier für Ereignisse (TRUE = aktiv). |
| PARAMS | STRING | – | Dienstparameter (z. B. Konfigurationsdaten). |
| u16ObjId | UINT | ID_NULL | Objekt-ID, die im Protokoll referenziert wird. |

### **Daten-Ausgänge**
| Variable | Typ | Beschreibung |
|----------|-----|--------------|
| QO | BOOL | Ausgangsqualifier (Bestätigung des Dienstes). |
| STATUS | STRING | Statusmeldung des Dienstes (z. B. Fehlertext oder Erfolgsmeldung). |

### **Adapter**
| Adapter | Typ | Richtung | Beschreibung |
|---------|-----|----------|--------------|
| IN | adapter::types::unidirectional::AIS | Eingang | Unidirektionaler Adapter für den Datenaustausch mit einer externen Ressource (z. B. Hardware-Schnittstelle). |

## Funktionsweise
Der Baustein **StringValue_AIS** kapselt einen internen Dienstbaustein **StringValue_IS** und steuert dessen Ereignis- und Datenflüsse. Bei einem INIT-Ereignis werden die Eingangsparameter (QI, PARAMS, u16ObjId) an den internen Baustein weitergeleitet, der die Initialisierung der Kommunikation durchführt. Der Ereignisausgang INITO signalisiert den Erfolg (QO, STATUS).

Ein REQ-Ereignis löst eine weitere Abfrage aus – der interne Baustein sendet die Anforderung (z. B. Lesen eines String-Werts) über den Adapter **IN** an die externe Ressource. Die Antwort wird asynchron über den Adapter empfangen (Ereignis IND oder CNF) und als STATUS-/QO-Ausgang zurückgegeben.

Die Verknüpfungen sind im FB-Netzwerk fest verdrahtet:
- **INIT** und **REQ** werden auf den internen Baustein **StringValue_IS** geführt.
- Die Antwortereignisse **IND** und **CNF** des internen Bausteins werden auf den Adapter-Ausgang **IN.E1** gelegt.
- Die Datenleitungen **QI**, **PARAMS**, **u16ObjId** speisen den internen Baustein, während **IN.D1** (vom Adapter) und **STATUS**/ **QO** an die Ausgänge des Bausteins weitergegeben werden.

## Technische Besonderheiten
- Der Baustein ist als **Service Interface Function Block (SIFB)** konzipiert und eignet sich für die Einbindung in eine ISOBUS-konforme Steuerungsumgebung.
- Die Schnittstelle verwendet einen **unidirektionalen Adapter (AIS)**, der ausschließlich Daten von der Ressource zur Steuerung überträgt.
- Der Initialwert von `u16ObjId` ist auf `ID_NULL` gesetzt – ein Platzhalter, der im Initialisierungsschritt durch eine gültige Objekt-ID ersetzt werden muss.
- Die Implementierung ist unter der **Eclipse Public License 2.0** lizenziert.
- Der Baustein nutzt einen internen Type-Hash-Mechanismus zur Integritätsprüfung.

## Zustandsübersicht
Eine explizite Zustandsmaschine ist im XML nicht dargestellt. Der Baustein arbeitet ereignisgesteuert:
- **IDLE**: Warten auf INIT.
- **INIT durchgeführt**: Initialisierung abgeschlossen, wartet auf REQ.
- **IN Bearbeitung**: Nach REQ wird die Anfrage an den Adapter gesendet; die Antwort erfolgt asynchron.

Die Rückmeldung über INITO signalisiert den Abschluss der Initialisierung, während der STATUS-Ausgang den aktuellen Zustand des Dienstes widerspiegelt.

## Anwendungsszenarien
- **ISOBUS UT-Anbindung**: Einlesen eines Textfeldes (z. B. Maschinenname, Feldbezeichnung) von einem Universal Terminal.
- **Konfigurationsschnittstelle**: Übernahme von String-Parametern aus einem übergeordneten Steuerungssystem.
- **Datenprotokollierung**: Erfassung von externen Zeichenketten (z. B. Barcode-Scanner, Seriennummern) für die Weiterverarbeitung.

## Vergleich mit ähnlichen Bausteinen
- **IntegerValue_AIS**: Analog aufgebaut, jedoch für Integer-Daten. Unterscheidet sich nur im Datentyp des Ausgangswerts.
- **CommandValue_AIS**: Bietet bidirektionale Kommunikation (Senden/Empfangen) und erwartet ein Kommando-Format.
- **StringValue_AIS** ist speziell auf den Empfang von Zeichenketten optimiert und erfordert keine Rückantwort außer Status.

## Fazit
Der **StringValue_AIS** ist ein spezialisierter Dienstschnittstellen-Baustein für den Empfang von String-Daten über einen unidirektionalen Adapter. Er vereinfacht die Einbindung externer Textquellen in Automatisierungssysteme und bietet eine saubere Trennung zwischen Kommunikationsdiensten und Applikationslogik. Dank der standardisierten Schnittstelle (Ereignis-/Datenanschlüsse) lässt er sich flexibel in 4diac-IDE-Projekte integrieren.