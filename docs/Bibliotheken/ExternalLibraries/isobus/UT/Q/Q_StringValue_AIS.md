# Q_StringValue_AIS


![Q_StringValue_AIS](./Q_StringValue_AIS.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein **Q_StringValue_AIS** realisiert den Dienst "Command Change String Value" gemäß ISO 11783-6 (Teil 6, Abschnitt F.24). Er dient dazu, über ein ISOBUS-Netzwerk einen neuen String-Wert an ein angeschlossenes Gerät zu senden. Der Baustein kapselt die gesamte Logik zur Initialisierung, zum Senden des Befehls und zur Rückmeldung des Ergebnisses. Die Eingabe des neuen String-Werts erfolgt über einen unidirektionalen Adapter (AIS), der die eigentlichen Daten bereitstellt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ   | Kommentar                                       |
|----------|-------|-------------------------------------------------|
| INIT     | EInit | Service-Initialisierung, setzt die Objekt-ID    |

### **Ereignis-Ausgänge**

| Ereignis | Typ   | Kommentar                                         |
|----------|-------|---------------------------------------------------|
| INITO    | EInit | Bestätigung der erfolgreichen Initialisierung      |
| CNF      | Event | Bestätigung des angeforderten Dienstes (Ergebnis) |

### **Daten-Eingänge**

| Name     | Typ  | Initialwert | Kommentar                     |
|----------|------|-------------|-------------------------------|
| u16ObjId | UINT | ID_NULL     | Objekt-ID des zu ändernden Werts |

### **Daten-Ausgänge**

| Name      | Typ   | Kommentar                                          |
|-----------|-------|----------------------------------------------------|
| STATUS    | STRING| Dienst-Status (z. B. "IDLE", "BUSY", "ERROR")      |
| s16result | INT   | Rückgabewert (siehe Beschreibung des Dienstes)      |

### **Adapter**

| Name       | Typ                                | Kommentar                        |
|------------|------------------------------------|----------------------------------|
| pau8String | adapter::types::unidirectional::AIS | Liefert den neuen String-Wert  |

## Funktionsweise

Der Baustein enthält intern eine Instanz des Funktionsbausteins `Q_StringValue` (aus der Bibliothek `isobus::UT::Q`), die die eigentliche ISOBUS-Kommunikation durchführt. Die Verdrahtung erfolgt folgendermaßen:

1. **Initialisierung**: Ein INIT-Ereignis am Eingang aktiviert den internen `Q_StringValue`-Baustein. Die mitgegebene `u16ObjId` wird an diesen weitergeleitet.
2. **Auslösen des Dienstes**: Sobald der Adapter `pau8String` ein Ereignis (E1) empfängt, wird das REQ-Ereignis des internen Bausteins ausgelöst. Gleichzeitig wird der Stringwert über den Datenausgang D1 des Adapters an `Q_StringValue.pau8String` übergeben.
3. **Rückmeldung**: Nach Abschluss der Verarbeitung gibt der interne Baustein die Ereignisse `INITO` und `CNF` aus, deren Ausgangsdaten (`STATUS`, `s16result`) direkt an die entsprechenden Ausgänge des Gesamtbausteins durchgereicht werden.

Die gesamte Logik ist somit in dem enthaltenen `Q_StringValue`-Baustein implementiert; der `Q_StringValue_AIS` dient als spezialisierte Hülle mit einem Adaptereingang.

## Technische Besonderheiten

- Der Baustein folgt der **ISO 11783-6** (ISOBUS) Spezifikation, Teil 6, Dienst "Command Change String Value".
- Die Implementierung verwendet einen **unidirektionalen Adapter** (`adapter::types::unidirectional::AIS`), der nur Daten vom Host zum Baustein überträgt. Dies vereinfacht die Integration in Steuerungssysteme, bei denen der neue Stringwert asynchron bereitgestellt wird.
- Der initiale Wert von `u16ObjId` ist `ID_NULL` – dies muss vor der ersten Verwendung auf eine gültige Objekt-ID gesetzt werden.
- Die Ausgänge `STATUS` und `s16result` liefern den Status und den Rückgabewert des Dienstes, sobald das `CNF`-Ereignis ausgelöst wird. Die genauen Werte sind in der zugrunde liegenden Dienstbeschreibung definiert.

## Zustandsübersicht

Der Baustein selbst besitzt keinen expliziten internen Automaten, da die Zustandslogik vollständig im enthaltenen `Q_StringValue` abläuft. Im Wesentlichen können folgende Phasen unterschieden werden:

- **Idle**: Nach dem Start oder nach einer erfolgreichen/fehlgeschlagenen Ausführung – der Baustein wartet auf ein INIT oder ein Ereignis am Adapter.
- **Initialisierung**: Aktiv durch INIT, bis das INITO-Ereignis gesendet wird.
- **Dienst aktiv**: Nach Auslösen durch den Adapter, bis das CNF-Ereignis eintrifft.
- **Fehler**: Bei ungültigen Parametern oder Kommunikationsfehlern wird ein entsprechender Status/Rückgabewert geliefert.

## Anwendungsszenarien

- **ISOBUS-Kommando:** Ändern eines String-Parameters an einem landwirtschaftlichen Gerät (z. B. Maschinenname, Aufgabe, Variablenname) über das ISOBUS-Netzwerk.
- **Steuerungssysteme:** Anbindung an eine SPS oder ein HMI, das den neuen String-Wert über einen Adapter bereitstellt (beispielsweise aus einer Textbox, einem Datenbankfeld oder einem Kommunikationskanal).
- **Testumgebungen:** Simulieren des Dienstes zu Entwicklungs- und Testzwecken.

## Vergleich mit ähnlichen Bausteinen

Der `Q_StringValue_AIS` ist eine spezialisierte Variante des Bausteins `Q_StringValue`, der bereits die gesamte ISOBUS-Kommunikation enthält. Der Unterschied liegt in der Eingabeschnittstelle: Während `Q_StringValue` den String-Wert über einen normalen Daten-Eingang `pau8String` (vom Typ `STRING`-Array) entgegennimmt, verwendet `Q_StringValue_AIS` einen **Adapter** (AIS), der asynchron Daten liefern kann. Der Adapter ermöglicht eine lose Kopplung und erleichtert die Wiederverwendung in unterschiedlichen Kontexten, z. B. wenn der Stringwert von einem anderen, unabhängigen Baustein bereitgestellt wird.

Weitere ähnliche Bausteine aus der ISO 11783-6-Familie behandeln andere Datentypen (z. B. `Q_NumberValue_AIS` für numerische Werte).

## Fazit

Der `Q_StringValue_AIS` ist ein praktischer, standardkonformer Funktionsbaustein zur Änderung von String-Werten im ISOBUS-Kontext. Durch die Verwendung eines Adapters wird die Integration flexibel und modular. Er eignet sich besonders für Anwendungen, bei denen der neue Wert asynchron oder von externen Quellen bereitgestellt wird. Die klare Trennung von Initialisierung und Dienstausführung sowie die standardisierten Ausgänge erleichtern die Fehlersuche und Wiederverwendung.